# xFitter-Docker:2.0.1
xFitter-Docker is an unofficial docker container featuring the 2.0.1 version of [xFitter](https://www.xfitter.org/xFitter/), as well as many standard HEP software packages needed for processing.

This allows for easy use of an up-to-date xFitter across all systems and configurations geared towards automated runs.

# Installation
Prebuilt images for this project are available in docker-hub under [jbrandons/xfitter](https://hub.docker.com/r/jbrandons/xfitter). You can pull this project from any internet connected PC with
```
    docker pull jbrandons/xfitter:2.0.1
```
If you have not used Docker you may want to view the [Docker Quickstart guide](https://docs.docker.com/get-started/).

# Usage
To utilize this container you will need to mount the host's xFitter data files (steering.txt, etc) to the container's `/run` directory, any target data files into `/data`, and any needed PDF files to `/pdfdata`. 

If no `/run/datafiles` directory exists the initialization script will create a symlink from `/data` to `/run/datafiles` to allow running of unmodified steering files. If your steering file is not setup to look for data in `datafiles` you will need to modify it or mount the data files accordingly.

From within your xFitter data folder you can run the follow command:
```
    docker run -v $(pwd):/run -v /host/data:/data -v /host/pdfs:/pdfdata jbrandons/xfitter:2.0.1
```
This will result in the same output as running  `xfitter` and `xfitter-draw output/` from the current working directory, and all outputs will correctly be placed in the `output/` folder on the host machine.

## Supplying xfitter-draw arguments
It is possible to provide arguments to the `xfitter-draw` command by including them after the container name. E.g. to print xfitter-draw's help use  
```
    docker run -it -v $(pwd):/run -v /host/data:/data jbrandons/xfitter:2.0.1 --help
```
This will cause the container to first run `xfitter` followed by `xfitter-draw --help`. 

If you add arguments you will need to specify the directory to use, as if you are running `xfitter-draw` from the command line. The default directory to use is `output`. E.g. to draw the PDF uncertainty bands use
```
    docker run -v $(pwd):/run -v /host/data:/data -v /host/pdfs:/pdfdata jbrandons/xfitter:2.0.1 --bands output
```

### Adding labels
Current limitations of the script mean to add labels, you will either need to include a flag argument first or call the full `xfitter-draw` command. Both commands below will result in a label being used
```
    docker run -v $(pwd):/run -v /host/data:/data -v /host/pdfs:/pdfdata jbrandons/xfitter:2.0.1 --bands output:my_label
```
```
    docker run -v $(pwd):/run -v /host/data:/data -v /host/pdfs:/pdfdata jbrandons/xfitter:2.0.1 'xfitter && xfitter-draw output:my_label'
```
## Running just xfitter
If you do not want to have `xfitter-draw` ran after `xfitter` you can supply `xfitter` as an argument
```
    docker run -v $(pwd):/run -v /host/data:/data -v /host/pdfs:/pdfdata jbrandons/xfitter:2.0.1 xfitter
```

Similarly to just run `xfitter-draw` use
```
    docker run -v $(pwd):/run -v /host/data:/data -v /host/pdfs:/pdfdata jbrandons/xfitter:2.0.1 xfitter-draw output
```

In fact, you can run any command available to the container by including it after the container name. For running an interactive command, such as `bash`, you will need to include a `-it` flag before the container name. See `Entering the container`.

## PDF files
To reduce the size of the container no PDF datasets are included. 

The best method to provide datasets is to bind the host's LHAPDF data directory files to the containers `/pdfdata` directory. This can be done by adding `-v $(lhapdf-config --datadir):/pdfdata` before the image name in the run command.
```
    docker run -v $(pwd):/run -v /host/data:/data -v $(lhapdf-config --datadir):/pdfdata jbrandons/xfitter:2.0.1
```
 If you do not have an existing directory on the host machine you may bootstrap one with the following:

* Enter the container while mounting the desired host directory to `/pdfdata`
* Run `cp -r $(lhapdf-config --datadir) /pdfdata && export LHAPDF_DATA_PATH=/pdfdata`. 
* Install any datasets you want with `lhapdf install`
  
You can then mount this folder to `/pdfdata` when running the container to have access to these datasets and use `lhapdf install` from within the container to install more at any time.

 You can also manually download the datasets from [here](http://lhapdfsets.web.cern.ch/lhapdfsets/current/) and extract them into a single directory. You will need the `lhapdf.conf` and `pdfsets.index` files in this directory, these files can be gotten from bootstrapping mentioned above. 
 
 It is possible in Docker to use `lhapdf install` to download the datasets from within the container prior to running xfitter, without mounting a `/pdfdata` folder. You will need to save the container so you do not have to download the datasets every run but this could be used to create a project orientated container that can be distributed and is simpler to run. Since Singularity runs containers in a read only format this is not possible.
 
 If you plan on downloading the datasets and you have access to the CERN CVMFS you may want to mount it with `-v /cvmfs/sft.cern.ch/:/cvmfs/sft.cern.ch/`.

# Entering the container
You may enter the container by appending an available shell after the container name. E.g. to launch `bash`:
```
    docker run -it -v $(pwd):/run -v /host/data:/data -v /host/pdfs:/pdfdata jbrandons/xfitter:2.0.1 bash
```
Note: You must have `-it` in this command to be able to see and interact with the container

# Singularity
This project has been tested on a mainframe with [Singularity](https://sylabs.io/docs/) installed.

To run in a folder with the xFitter files, as in the first usage example, use the following command
```
    singularity run -B $(pwd):/run -B /host/data:/data -B /host/pdfs:/pdfdata docker://jbrandons/xfitter:2.0.1
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
Pull requests are welcome. 

For major changes, please open an issue first to discuss what you would like to change.
