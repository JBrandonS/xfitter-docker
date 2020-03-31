FROM rootproject/root-ubuntu16:latest
LABEL maintainer="Brandon Stevenson <stevensonb@smu.edu>"
LABEL version="0.1"
LABEL description="An xFitter container that will autorun xfitter and xfitter-draw on the /data dir"

USER root
WORKDIR /root

RUN apt-get update -qq \
    && apt-get upgrade -y -qq \
    && apt-get install -y -qq --no-install-recommends wget libyaml-dev libyaml-cpp-dev ghostscript \
    && apt-get install -y -qq --no-install-recommends fonts-liberation texlive-latex-base texlive-fonts-recommended texlive-fonts-extra texlive-latex-extra \
    && rm -rf /packages /var/lib/apt/lists/*

COPY install-xfitter-master install-xfitter
RUN chmod +x install-xfitter \
    && ./install-xfitter master \
    && rm -rf /root/xfitter-master/.git /root/xfitter-master/examples \
    && rm -f /root/deps/*.tar.gz /root/deps/*.tgz 

COPY docker-entrypoint.sh /
RUN chmod +x /docker-entrypoint.sh

VOLUME [ "/data" ]
VOLUME [ "/pdffiles" ]

WORKDIR /data
ENTRYPOINT [ "/docker-entrypoint.sh" ]
CMD [ "xfitter" ]