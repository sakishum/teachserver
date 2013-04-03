#include "Evloop.h"

struct ev_loop* Evloop::loop = NULL;
struct ev_io_info Evloop::ioarray[MAXFD];
AtomicT<int> Evloop::clientcount;

Evloop::Evloop(string ip, int port) {
    ip_ = ip;
    port_ = port;
    listenfd_ = socket(AF_INET, SOCK_STREAM, 0);
    setnonblock (listenfd_);
    setreuseaddr (listenfd_);
    setnodelay (listenfd_);
    for (int i = 0; i< MAXFD; ++i) {
        ioarray[i].io = NULL;
    }
}

Evloop::~Evloop() {
    close(listenfd_);
}

int Evloop::startlisten() {
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip_.c_str());
    //inet_pton (AF_INET, ip_.c_str(), &servaddr.sin_addr.s_addr);
    //servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
    servaddr.sin_port = htons(port_);
    if (0 != bind(listenfd_, (struct sockaddr*)&servaddr, sizeof(struct sockaddr))) {
        LOG(ERROR) << "bind error" << endl;;
        abort(); //致命错误
        return -1;
    }
    listen(listenfd_, 10);
    return listenfd_;
}

int Evloop::work() {
    //建立监听
    startlisten();
    ev_io ev_io_watcher;
    //ev_timer timer;
    Evloop::loop = ev_loop_new(EVBACKEND_EPOLL);

    ev_io_init(&ev_io_watcher, accept_cb, listenfd_, EV_READ);

    ev_io_start(Evloop::loop,&ev_io_watcher); 
#if 0
    //定时器
    ev_timer_init(&timer, time_cb, 5, 5);
    ev_timer_start(Evloop::loop,&timer); 
#endif
    LOG(INFO)<< "ev_loop started";

    //libev event loop
    ev_loop(Evloop::loop, 0);

    ev_loop_destroy(Evloop::loop);
    return 0;
}

/**
 * @brief 接受客户端回调函数
 */
void Evloop::accept_cb(struct ev_loop *loop, ev_io *w, int revents) {
    struct sockaddr_in clientaddr;
    socklen_t socklen = 0;
    int newfd = accept(w->fd, (struct sockaddr*)&clientaddr, &socklen);
    if ( 0 >= newfd) {
        return;
    }

    LOG(INFO) << " get a new client fd = " << newfd ;
    Evloop::setnonblock(newfd);

    Evloop::ioarray[newfd].io = (ev_io*)malloc(sizeof(ev_io));
    Evloop::ioarray[newfd].lasttime = ev_time();

    ev_io_init(Evloop::ioarray[newfd].io, recv_cb, newfd, EV_READ);
    ev_io_start(loop, Evloop::ioarray[newfd].io);
    Evloop::clientcount++;
    return;
}

/**
 * @brief 接受数据回调函数
 */
void Evloop::recv_cb(struct ev_loop *loop, ev_io *w, int revents) {
    //从内存池中取出一个buf
    Buf* buf = SINGLE->bufpool.malloc();
    if (NULL == buf) {
        printf("null buf\n");
        return;
    }

    //收包头长度
    int i = recv_v(w->fd, buf->ptr(), sizeof(int));
    if ( sizeof(int) != i) {
        LOG(ERROR) << w->fd <<":recv head error! actually received len = "<< i <<endl;;
        Evloop::closefd(w->fd);
        return;
    }

    //收包体
    int *p = (int*)buf->ptr();
    i = recv_v(w->fd, (char*)buf->ptr() + sizeof(int), *p - sizeof(unsigned int));

    if ( (*p - sizeof(unsigned int)) != i) {
        LOG(ERROR) << w->fd <<":recv body error! hope = "<< *p <<" actually received len = "<< i <<endl;;
        Evloop::closefd(w->fd);
        return;
    }
    
    Evloop::ioarray[w->fd].lasttime = ev_time();
    buf->setfd(w->fd);
    //将buf压入队列
    SINGLE->recvqueue.enqueue(buf);
    return;
}

void Evloop::setnonblock(int fd) {
  fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
}

void Evloop::setreuseaddr(int fd)
{
    int reuse = 1;
    setsockopt (fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof (reuse));
}

void Evloop::setnodelay (int fd)
{
    int nodelay = 1;
    setsockopt (fd, IPPROTO_TCP, TCP_NODELAY, &nodelay, sizeof (nodelay));
}

void Evloop::closefd(int fd) {
    LOG(INFO) << "[" << fd << "] disconnected!"<<endl;
    close(fd);
    ev_io_stop(loop, Evloop::ioarray[fd].io);
    free(Evloop::ioarray[fd].io);
    Evloop::ioarray[fd].io = NULL;
    Evloop::clientcount--;
    ROOMMANAGER->del_client(fd);
}

void Evloop::time_cb(struct ev_loop* loop, struct ev_timer *timer, int revents) {
    ev_tstamp now = ev_time();
    for(register int i = 0; i < MAXFD; ++i ) {
        if (NULL != ioarray[i].io) {
            //检测超时断开
            if (TIMEOUT < now - ioarray[i].lasttime) {
                LOG(INFO) << i << " now: "<< now << " last recv data:" << ioarray[i].lasttime ;
                //Evloop::closefd(i);
            }
        }
    }
    return;
}

int Evloop::getClientCount() {
    return Evloop::clientcount.value();
}
