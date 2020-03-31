
# About
The goal of this is to have a docker (singularity) image able to run xfitter projects allowing for easy and rapid deployment
Overall the end goal would be that this is simple enough that we can run these projects on the mainframe or local computers


# Building and Running
To build run the following in this directory
```
    docker build . -t xfitter-docker
```
You can then run xfitter with
```    
    docker run --rm -it -v /host/path/to/data:/data xfitter-docker
```    
Outputs will be placed in `/host/path/to/data` like normal

You are able to enter the container by adding any argument after `xfitter-docker` i.e.
```
    docker run --rm -it -v /host/path/to/data:/data xfitter-docker bash
```

# Current Issues
Numerous versioning (or lack thereof) issues exist