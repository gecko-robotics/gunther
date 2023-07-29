FROM debian:latest AS buildimg

RUN apt -y update && \
    apt -y install git cmake build-essential; \
    mkdir -p /src/build

COPY ./CMakeLists.txt /src
COPY ./*.cpp /src

WORKDIR /src/build

RUN cmake .. ; \
    make;

CMD ["/src/build/main"]