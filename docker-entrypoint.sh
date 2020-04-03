#!/bin/bash
set -e

# Setup xfitter
source ${XFITTER_INSTALL_DIR}/setup.sh

# Fix issue with singularity not honoring WORKDIR in docker
if [ -d /run ]; then cd /run; fi

# Allow people to add lhapdf data files
if [ -d /pdfdata ] && [ "$(ls /pdfdata)" ]; then
    if [ -f /pdfdata/lhapdf.conf ] && [ -f /pdfdata/pdfsets.index ]; then
        export LHAPDF_DATA_PATH=/pdfdata
    else
        echo "Invalid PDF folder found at /pdfdata. Please check your bindings."
    fi
fi

if [ "$1" = 'xfitter' ]; then
    exec xfitter "$@"
    exec xfitter-draw output/
fi

# If the first arg is not xfitter we just run that
exec "$@"