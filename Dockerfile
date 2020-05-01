FROM rootproject/root-ubuntu16:latest
LABEL maintainer="Brandon Stevenson <stevensonb@smu.edu>"

USER root
ENV XFITTER_VERSION 2.0.1
ENV XFITTER_INSTALL_DIR /opt/xfitter
WORKDIR $XFITTER_INSTALL_DIR

RUN apt-get update -qq \
    && apt-get install -y --no-install-recommends wget libyaml-dev libyaml-cpp-dev ghostscript fonts-liberation texlive-latex-base texlive-fonts-recommended texlive-latex-extra vim-tiny \
    && rm -rf /packages /var/lib/apt/lists/*

RUN wget https://raw.githubusercontent.com/JBrandonS/install-xfitter/master/install-xfitter \
    && chmod +x install-xfitter \
    && ./install-xfitter ${XFITTER_VERSION} \
    && chmod -R 755 ${XFITTER_INSTALL_DIR} \
    && ln -s /usr/bin/vim.tiny /usr/bin/vim \
    && rm -rf install-xfitter install.log run deps/lhapdf/share/LHAPDF/NNPDF30_nlo_as_0118

COPY docker-entrypoint.sh /
RUN chmod +x /docker-entrypoint.sh

VOLUME [ "/run" ]
VOLUME [ "/data" ]
VOLUME [ "/pdfdata" ]

WORKDIR /run
ENTRYPOINT [ "/docker-entrypoint.sh" ]
CMD [ "xfitter", "&&", "xfitter-draw", "output" ]
