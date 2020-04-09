# xFitter-Docker
xFitter-Docker is a unofficial docker container featuring the latest version of [xFitter](https://www.xfitter.org/xFitter/), from the master branch for the [main repo](https://gitlab.cern.ch/fitters/xfitter), and as well as many standard HEP software packages needed for processing.

This allows for easy use of an up-to-date xFitter across all systems and configurations.

# Installation
Prebuilt images for this project are available in docker-hub under [jbrandons/xfitter](https://hub.docker.com/r/jbrandons/xfitter). You can pull this project from any internet connected PC with
```
    docker pull jbrandons/xfitter
```
If you have not used Docker you may want to view the [Docker Quickstart guide](https://docs.docker.com/get-started/).

# Usage
To utilize this container you will need to point the host's xFitter data files (steering.txt, etc) to the container's `/run` directory and any target data files into `/data`. 

If no `/run/datafiles` directory exists the initialization script will create a symlink from `/data` to `/run/datafiles` to allow running of unmodified steering files. If your steering file is not setup to look for data in `datafiles` you will need to modify it.

From within your xFitter data folder you can run the follow command:
```
    docker run -it -v $(pwd):/run -v /host/data:/data jbrandons/xfitter
```
This will result in the same output as running  `xfitter` and `xfitter-draw output/` from the current working directory, and all outputs will correctly be placed in the `output/` folder on the host machine.

## PDF files
In order to reduce the size of the container the only PDF dataset included is CT10. 

The best method to provide other datasets is to bind the host's LHAPDF data directory files to the containers `/pdfdata` directory. This can be done by adding `-v $(lhapdf-config --datadir):/pdfdata` before the image name in the run command.
```
    docker run -it -v $(pwd):/run -v /host/data:/data -v $(lhapdf-config --datadir):/pdfdata jbrandons/xfitter
```
 You can download the pdf datasets from [here](http://lhapdfsets.web.cern.ch/lhapdfsets/current/) and extract all of them into a single directory if you do not have LHAPDF installed on the host machine. You will also need the `lhapdf.conf` and `pdfsets.index` files in this directory. 
 
 If you enter the container you can use `lhapdf install` to download the datasets before running xFitter. If you plan on downloading the datasets and you have access to the CERN CVMFS you may want to mount it with `-v /cvmfs/sft.cern.ch/:/cvmfs/sft.cern.ch/`. As both of these methods require entering the container and downloading the datasets before each run it is not recommended. 
 
 As singularity runs containers in a read only format it is not possible to download these files from within the container without first mounting an existing `/pdfdata` directory. If you do not have an existing directory on the host machine you may bootstrap one with the following:
Mount the desired directory to `/pdffiles`, enter the container, and run `cp -r $(lhapdf-config --datadir) /pdfdata && export LHAPDF_DATA_PATH=/pdfdata`. You will only need to do this once.
 

## Entering the container
You may enter the container by appending an available shell after the container name, to launch `bash` run
```
    docker run -it -v /host/path/to/data:/data jbrandons/xfitter bash
```
Note: You must have `-it` in this command to be able to see and interact with the container

# Singularity
This project has been tested on a mainframe with [singularity](https://sylabs.io/docs/) installed.

To run in a folder with the xFitter data and files, as in the first usage example, use the following command
```
    singularity run -B $(pwd):/run -B $(pwd)/../data:/data docker://jbrandons/xfitter
```

You can enter the container by adding `bash` after `docker://jbrandons/xfitter` or changing the `run` argument to `shell`. 

If you enter the container using the `exec` or `shell` option, you will need to manually setup the xFitter environment. See the `docker-entrypoint.sh` script for an idea on how to do this.

# Included Software Versions
|Software|Version|
|--------|-------|
|[ubuntu](https://ubuntu.com/)|16.04.6 LTS|
|[root](https://root.cern.ch/)|6.12/07|
|[lhapdf](https://lhapdf.hepforge.org/)|6.2.3|
|[hathor](https://www-zeuthen.desy.de/~moch/hathor/)|2.0|
|[hoppet](https://hoppet.hepforge.org)|1.2.0|
|[applgrid](https://applgrid.hepforge.org/)|1.5.34|
|[qcdnum](https://www.nikhef.nl/~h24/qcdnum/)|17-01-14|
|[apfel](https://apfel.hepforge.org/)|3.0.4|
|[mela](https://apfel.hepforge.org/mela.html)|2.0.1|
|[apfelgrid](https://github.com/zenaiev/APFELgrid)|1.0.1|
|[apfelxx](https://github.com/vbertone/apfelxx/)|4.0.0|

# Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
