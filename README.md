
# xFitter-Docker
xFitter-Docker is a docker container featuring the latest version of [xfitter](https://www.xfitter.org/xFitter/), from the master branch for the [main repo](https://gitlab.cern.ch/fitters/xfitter), and as well as many standard HEP software packages needed for processing.
This allows for easy use of an up-to-date xfitter across all systems and configurations.

# Installation
Prebuilt images for this project are available in docker-hub under [jbrandons/xfitter](https://hub.docker.com/r/jbrandons/xfitter). You can pull this project from any internet connected PC with
```
    docker pull jbrandons/xfitter
```

# Usage
To utilize this container you will need to point the xfitter data files (steering.txt, ewparam.txt, etc) to the containers `/run` directory and any target data files into the `/data`. This will become your base path and the target data must be in this folder or a subfolder or it.

From within this folder you can run the follow:
```
    docker run --rm -it -v $(pwd):/run -v /host/data:/data jbrandons/xfitter
```
This will result in the same output as running  `xfitter` and `xfitter-draw output/` from the `/run` folder, and all outputs will correctly be placed in the `/run/output/` folder on the host machine.

## PDF files
lhapdf will pull any needed pdf datasets automatically from its [repo](http://lhapdfsets.web.cern.ch/lhapdfsets/current/).
You can speed up the run time of the container by providing pre-downloaded tarballs or by linking to an existing lhapdf data directory on the host machine.

Binding the host's lhapdf data directory can be done by adding `-v $(lhapdf-config --datadir):/pdffiles` before the image name in the run
PDF tarballs must end in either `.tar.gz` or `.tgz` and can be added by placing them all inside a directory and binding with `-v /host/pdffiles:/pdffiles`

```
    docker run --rm -it -v $(pwd):/run -v /host/data:/data -v $(lhapdf-config --datadir):/pdffiles jbrandons/xfitter
```

## Entering the container
You may enter the container by appending an available shell after the container name, to launch bash run
```
    docker run --rm -it -v /host/path/to/data:/data jbrandons/xfitter bash
```
Note: You must have `-it` in this command to be able to see and interact with the container

# Singularity
This project has been tested on a mainframe with [singularity](https://sylabs.io/docs/) installed.

To run in a folder with the xfitter data and files, as in the first example in Usage, use the following command
```
    singularity run -B $(pwd):/run -B $(pwd)/../data:/data docker://jbrandons/xfitter
```

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
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change