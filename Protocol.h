#ifndef PROTOCOL_H_
#define PROTOCOL_H_
#pragma pack(1)
typedef struct msg{
    int len;
    char buf[512];
}msg;
#pragma pack()
#endif
