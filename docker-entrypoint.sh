#!/bin/bash
set -e

# Setup xFitter
source ${XFITTER_INSTALL_DIR}/setup.sh

# Fix issue with singularity not honoring WORKDIR in docker
if [ -d /run ]; then cd /run; fi

# Allow people to add LHAPDF data files
if [ -d /pdfdata ] && [ "$(ls /pdfdata)" ]; then
    if [ -f /pdfdata/lhapdf.conf ] && [ -f /pdfdata/pdfsets.index ]; then
        echo "Found LHAPDF data in /pdfdata, telling LHAPDF to use this directory."
        echo "Note: lhapdf-config --datadir will not be updated to this path. Don't panic."
        export LHAPDF_DATA_PATH=/pdfdata
    else
        echo "Invalid PDF folder found at /pdfdata. Please check your bindings."
        sleep 3
    fi
fi

# Add a symlink to the /data directory to prevent the need of modifying steering files
createdSymlink=0
if [ -d /data ] && [ "$(ls /data)" ] && [ ! -d /run/datafiles ]; then
    echo "Linking /data to /run/datafiles."
    ln -s /data /run/datafiles && createdSymlink=1
fi

# If the first argument is xfitter (the default) we run xfitter and xffiter-draw
# Otherwise we just run the commands provided
if [ "$1" = 'xfitter' ]; then
    xfitter
    xfitter-draw output/
else
    "$@"
fi

# Clean up symlink if we made one
if [[ createdSymlink -eq 1 ]]; then
    unlink /run/datafiles
fi