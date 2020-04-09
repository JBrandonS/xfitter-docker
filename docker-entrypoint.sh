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
if [ -d /data ] && [ "$(ls /data)" ] && [ ! -d /run/datafiles ]; then
    echo "Linking /data to /run/datafiles"
    ln -s /data /run/datafiles
fi

if [ "$1" = 'xfitter' ]; then
    exec xfitter "$@"
    exec xfitter-draw output/
fi

# If the first arg is not xfitter we just run that
exec "$@"