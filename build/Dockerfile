FROM ubuntu:20.04
WORKDIR /opt

RUN apt-get update && apt-get install -y wget make unzip libc6-i386 netcat
RUN dpkg --add-architecture i386 && apt-get update && apt-get install -y libc6:i386 libncurses5:i386 libstdc++6:i386
RUN wget https://www.nordicsemi.com/-/media/Software-and-other-downloads/SDKs/nRF5/Binaries/nRF5SDK1230.zip && \
    unzip nRF5SDK1230.zip && \
    rm nRF5SDK1230.zip

RUN wget https://launchpad.net/gcc-arm-embedded/4.9/4.9-2015-q3-update/+download/gcc-arm-none-eabi-4_9-2015q3-20150921-linux.tar.bz2 && \
    tar xvjf gcc-arm-none-eabi-4_9-2015q3-20150921-linux.tar.bz2 && \
    rm gcc-arm-none-eabi-4_9-2015q3-20150921-linux.tar.bz2

RUN echo "GNU_INSTALL_ROOT := /opt/gcc-arm-none-eabi-4_9-2015q3" > nRF5_SDK_12.3.0_d7731ad/components/toolchain/gcc/Makefile.posix && \
    echo "GNU_VERSION := 4.9.3" >> nRF5_SDK_12.3.0_d7731ad/components/toolchain/gcc/Makefile.posix && \
    echo "GNU_PREFIX := arm-none-eabi" >> nRF5_SDK_12.3.0_d7731ad/components/toolchain/gcc/Makefile.posix
