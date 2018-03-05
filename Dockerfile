FROM ubuntu:16.04

MAINTAINER Parpibaev Artur
RUN apt-get update && apt-get install -y gcc
RUN apt-get -y install libevent-dev

ADD . .

RUN RUN cc -o highload *.c

EXPOSE 80

CMD ./highload