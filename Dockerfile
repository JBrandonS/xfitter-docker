FROM rootproject/root-ubuntu16:latest
LABEL maintainer="Brandon Stevenson <stevensonb@smu.edu>"

USER root
ENV XFITTER_INSTALL_DIR /opt/xfitter
WORKDIR $XFITTER_INSTALL_DIR

RUN apt-get update -qq \
    && apt-get install -y -qq --no-install-recommends wget libyaml-dev libyaml-cpp-dev ghostscript \
    && apt-get install -y -qq --no-install-recommends fonts-liberation texlive-latex-base texlive-fonts-recommended texlive-fonts-extra texlive-latex-extra \
    && apt-get install -y -qq --no-install-recommends vim \
    && rm -rf /packages /var/lib/apt/lists/*

COPY install-xfitter-master install-xfitter
RUN chmod +x install-xfitter \
    && ./install-xfitter master \
    && rm -rf ${XFITTER_INSTALL_DIR}/xfitter-master/.git ${XFITTER_INSTALL_DIR}/xfitter-master/examples \
    && rm -f ${XFITTER_INSTALL_DIR}/deps/*.tar.gz ${XFITTER_INSTALL_DIR}/deps/*.tgz \
    && chmod -R 755 ${XFITTER_INSTALL_DIR}

COPY docker-entrypoint.sh /
RUN chmod +x /docker-entrypoint.sh

VOLUME [ "/run" ]
VOLUME [ "/data" ]
VOLUME [ "/pdfdata" ]

WORKDIR /run
ENTRYPOINT [ "/docker-entrypoint.sh" ]
CMD [ "xfitter" ]