FROM debian
COPY test.sh /home/test/
COPY file1_lab /home/test/
COPY file2_lab /home/test/
RUN useradd user1
RUN chown user1:user1 /home/test/file1_lab
cmd su - user1