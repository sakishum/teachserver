#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <time.h>
#define SERV_IP "192.168.101.54"
#define SERV_PORT 9999 
#define CON_NUM 1000
int main(int argc, char* argv[]){
    int cntFd[CON_NUM] = {0};
    int i = 0;
    for( i = 0; i< CON_NUM; ++i) {
        cntFd[i] = socket(AF_INET, SOCK_STREAM, 0);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(SERV_IP);
    addr.sin_port = htons(SERV_PORT);

    for( i = 0; i< CON_NUM; ++i) {
        connect(cntFd[i], (struct sockaddr*)&addr, sizeof(struct sockaddr));
    }
    while(1) {
        sleep(5);
        printf("xxxx\n");
        char buf[1024] = {0};
        unsigned int a = 128;
        memcpy(buf, &a, sizeof(unsigned int));
        for( i = 0; i< CON_NUM; ++i) {
            send(cntFd[i], buf, sizeof(unsigned int) + 128, 0);
        }
    }

    for( i = 0; i< CON_NUM; ++i) {
        close(cntFd[i]);
    }

    return 0;
}
