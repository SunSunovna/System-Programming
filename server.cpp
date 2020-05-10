#include <iostream>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>

using namespace std;

bool end_flag=false;

void* client_sock(void* client_data)
{
    int sock = *(int*) client_data; 
    char buf[1024];
    int bytes_read=0;

    while(1)
    {
        bytes_read = recv(sock, buf, 1024, 0); 
        if(bytes_read <= 0) break;
        cout<<buf<<endl; 
        send(sock, buf, bytes_read, 0); 
    }
        
    close(sock); 
    cout<<"client end!\n";

    return nullptr;    
}


void* listener(void* atr)
{
    pthread_t tid; 
    int sock=0;
    int listen_sock=0;
    struct sockaddr_in addr;
    listen_sock = socket(AF_INET, SOCK_STREAM, 0); 

    if(listener < 0)
    {
        cout<<"socket\n";
        exit(1);
    }

    addr.sin_family = AF_INET; 
    addr.sin_port = htons(4200); 
    addr.sin_addr.s_addr = htonl(INADDR_ANY); 

    if(bind(listen_sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
    {
        cout<<"bind\n";
        exit(2);
    }

    listen(listen_sock, 5); 

    while(1)
    {
        if (end_flag)
        {
            close(listen_sock);
            return nullptr;
        }
        sock = accept(listen_sock, NULL, NULL); 
        if(sock < 0)
        {
            cout<<"accept";
            exit(3);
        }

        pthread_create(&tid,nullptr,&client_sock,&sock); 
        pthread_detach(tid);
    }

    cout<<"listener end!\n";

    return nullptr;
}

int main()
{
    pthread_t tid; 
    string buff;

    pthread_create(&tid,nullptr,&listener,nullptr); 
    pthread_detach(tid);  
    cout<<"server start!\n";
    while(1)
    {
        cin>>buff;
        if (buff=="q")
        {
            end_flag=true;
            sleep(1);
            break;
        }
    }    
    
    return 0;
}