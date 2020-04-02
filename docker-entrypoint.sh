#!/bin/bash
set -e

# Setup xfitter
source ${XFITTER_INSTALL_DIR}/setup.sh

# Fix issue with singularity not honoring WORDDIR in docker
cd /run

# Allow people to add lhapdf data files
if [ -d /pdffiles ] && [ "$(ls /pdffiles)" ]; then
    lhapdfdatadir=$(lhapdf-config --datadir)

    if [ -f /pdffiles/lhapdf.conf ] && [ -f /pdffiles/pdfsets.index ]; then
        echo "Found lhapdf data dir, linking"
        rm -rf $lhapdfdatadir
        ln -s /pdffiles $lhapdfdatadir
    elif [ -f /pdffiles/*.tar.gz ] || [ -f /pdffiles/*.tgz ]; then
        echo "Extracting pdf data files into $lhapdfdatadir"
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