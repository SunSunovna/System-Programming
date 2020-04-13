FROM debian
RUN apt update
RUN apt upgrade
RUN apt install build-essential -y
RUN mkdir /home/746-saa1
COPY lab4.cpp /home/746-saa1/lab4.cpp 
COPY lab4_1.cpp /home/746-saa1/lab4_1.cpp
COPY dir_lab4 /home/746-saa1/dir_lab4
