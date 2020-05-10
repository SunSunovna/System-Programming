#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

using namespace std;

int main()
{
    int sock;
    int bytes_read;
    struct sockaddr_in addr;
    struct sockaddr_in client;
    char buff[1024];

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(4200);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
        perror("bind");
        exit(2);
        }

    socklen_t clientlen = sizeof(client);

    while(1)
    {   
        memset(buff, '\0', sizeof(buff));
        cout<<"Server wait\n";
        bytes_read=recvfrom(sock,buff,1024,0,(struct sockaddr *)&client, &clientlen);
        cout<<buff<<endl;
        sendto(sock, buff, sizeof(buff), 0,(struct sockaddr *)&client, sizeof(client));
    }
    close(sock);

    return 0;
}