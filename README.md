
# xFitter-Docker
xFitter-Docker is a docker container featuring the latest version of xfitter, from the master branch, and many standard HEP software packages for rendering.
It allows for easy use of xfitter no matter the system or configuration.


# Installation
Under most situations you do you need to build this project, instead use docker hub to pull the image
```
    docker pull jbrandons/xfitter:wip
```

# Usage
The simplest method to run this would be to have your xfitter files, including any data files needed in the same folder. Then run
```
    docker run --rm -it -v /host/path/to/data:/data jbrandons/xfitter:wip
```
this will be the same as running `xfitter` and `xfitter-draw output/` from the `/host/path/to/data` folder. When done you will have the pdf files in the `/host/path/to/data/output` file on the host.

## PDF files
If you need to include custom / unreleased PDF files for lhapdf that can be done by either placing the tarballs into a folder or linking the host's lhpdf data dir to the containers `/pdffiles` folder. To link the folders add `-v /host/path/to/pdf/data:/pdffiles` to the command
```
    docker run --rm -it -v /host/path/to/data:/data -v /host/pdf/files:/pdffiles jbrandons/xfitter:wip
```
Note: tarballs must end in either `.tar.gz` or `.tgz`

## Entering the container
You are able to enter the container by adding any argument after `xfitter:wip`. To get into bash use
```
    docker run --rm -it -v /host/path/to/data:/data jbrandons/xfitter:wip bash
```

# Included Software Versions
|Software|Version|
|--------|-------|
|root|6.12/07|
|lhapdf|6.2.3|
|hathor|2.0|
|hoppet|1.2.0|
|applgrid|1.5.34|
|qcdnum|17-01-14|
|apfel|3.0.4|
|mela|2.0.1|
|apfelgrid|1.0.1|
|apfelxx|4.0.0|

# Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change