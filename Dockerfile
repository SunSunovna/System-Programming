FROM debian
RUN apt update
RUN apt upgrade
RUN apt install build-essential -y
COPY lab3.cpp /


