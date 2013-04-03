#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <arpa/inet.h>


#include "protocol.h"
#define SERV_IP "127.0.0.1"
#define SERV_PORT 9999 

int main(int argc, char* argv[]){
    int cntFd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(SERV_IP);
    addr.sin_port = htons(SERV_PORT);

    connect(cntFd, (struct sockaddr*)&addr, sizeof(struct sockaddr));
    char buf[1024] = {0};

    MSG_HEAD head;
    struct sLogin loginreq;
    loginreq.type = MCT_TEACHER;

    snprintf(loginreq.username, sizeof(loginreq.username), "%s", "张三");
    snprintf(loginreq.password, sizeof(loginreq.password), "%s", "123456");

    head.cLen = sizeof(MSG_HEAD) + sizeof(struct sLogin);
    head.cType = CT_Login;
    memcpy(buf, &head, sizeof(MSG_HEAD));
    memcpy(buf + sizeof(MSG_HEAD), &loginreq, sizeof(struct sLogin));
    send( cntFd, buf, head.cLen, 0);

    memset(buf, '\0', 1024);

    recv(cntFd, buf, 1024, 0);
                    //CT_LoginReuslt
    MSG_HEAD* x = (MSG_HEAD*)buf;

    struct sLoginOutResult loginresp;
    memcpy(&loginresp, buf + sizeof(MSG_HEAD), sizeof(loginresp));
    printf("%d  %s\n", loginresp.succeed, loginresp.message);

    close(cntFd);
    return 0;
}
