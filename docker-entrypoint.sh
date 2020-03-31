#!/bin/bash
set -e

# Settup xfitter
source /root/setup.sh

# Allow people to add lhapdf data files
# This can be done in two formats, 
#    linking to a complete local lhapdf/share/lhapdf install, with config files and pdf's extracted
#    linking to a folder of tarballs, these must be in either tar.gz or .tgz file types
if [ "$(ls /pdffiles)" ]; then
    lhapdfdatadir=$(lhapdf-config --datadir)

    if [ -f /pdffiles/lhapdf.conf ] && [ -f /pdffiles/pdfsets.index ]; then
        echo "Found lhapdf data dir, linking"
        rm -rf $lhapdfdatadir
        ln -s /pdffiles $lhapdfdatadir
    elif [ -f /pdffiles/*.tar.gz ] || [ -f /pdffiles/*.tgz ]; then
        echo "extracting pdf data files into $lhapdfdatadir"
        for file in $(find /pdffiles -name '*.tar.gz' -o -name '*.tgz'); do basename $file && tar xzf $file -C $lhapdfdatadir; done
    else
        echo "Unknown data in /pdffiles, unable to do anything."
    fi
fi

if [ "$1" = 'xfitter' ]; then
    exec xfitter "$@"
    exec xfitter-draw output/
fi

# If the first arg is not xfitter we just run that
exec "$@"