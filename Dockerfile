FROM debian:stretch

# Install required system packages
RUN apt-get update && apt-get install -y \
    apt-utils \
    automake \
    g++ \
    make \
    libtool \
    pkg-config \
    doxygen \
    libdb++-dev \
    curl \
    bsdmainutils \
    libboost-all-dev \
    libssl-dev \
    libevent-dev

# Install Berkeley DB 4.8
RUN curl -L http://download.oracle.com/berkeley-db/db-4.8.30.tar.gz | tar -xz -C /tmp && \
    cd /tmp/db-4.8.30/build_unix && \
    ../dist/configure --enable-cxx --includedir=/usr/include/bdb4.8 --libdir=/usr/lib && \
    make -j$(nproc) && make install && \
    cd / && rm -rf /tmp/db-4.8.30

RUN useradd -mU vestx

COPY . /tmp/vestx/

RUN cd /tmp/vestx && \
    ./autogen.sh && \
    ./configure --without-gui --prefix=/usr && \
    make -j$(nproc) && \
    make check && \
    make install && \
    cd / && rm -rf /tmp/vestx

# Remove unused packages
RUN apt-get remove -y \
    automake \
    g++ \
    make \
    libtool \
    pkg-config \
    doxygen \
    libdb++-dev \
    curl \
    bsdmainutils \
    libboost-all-dev \
    libssl-dev \
    libevent-dev

USER vestx:vestx

RUN mkdir /home/vestx/.vestx && \
    touch /home/vestx/.vestx/vestx.conf

VOLUME [ "/home/vestx/.vestx" ]

EXPOSE 62583
EXPOSE 8332
EXPOSE 18332

ENTRYPOINT ["/usr/bin/vestxd", "--conf=/home/vestx/.vestx/vestx.conf"]
