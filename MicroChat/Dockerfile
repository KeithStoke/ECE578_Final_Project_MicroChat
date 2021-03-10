FROM yg397/thrift-microservice-deps:xenial

ARG NUM_CPUS=2

COPY ./ /microchat
RUN cd /microchat \
    && mkdir -p build \
    && cd build \
    && cmake .. \
    && make -j${NUM_CPUS} \
    && make install

WORKDIR /microchat