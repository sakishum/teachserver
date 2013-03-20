#include "Evloop.h"

Evloop::Evloop() {
    listenfd_ = socket(AF_INET, SOCK_STREAM, 0);
}

Evloop::~Evloop() {
    close(listenfd_);
}

int Evloop::startlisten() {
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(SERVADDR);
    servaddr.sin_port = htons(CONFIG->server_port);
    if (0 != bind(listenfd_, (struct sockaddr*)&servaddr, sizeof(struct sockaddr))) {
        LOG(ERROR) << "bind error";
        return -1;
    }
    listen(listenfd_, 10);
    return listenfd_;
}

int Evloop::work() {
    startlisten();
    ev_io ev_io_watcher;
    struct ev_loop *loop = ev_loop_new(EVBACKEND_EPOLL);

    ev_io_init(&ev_io_watcher, accept_cb, listenfd_, EV_READ);

    ev_io_start(loop,&ev_io_watcher); 
    LOG(INFO)<< "ev_loop started";

    ev_loop(loop, 0);

    ev_loop_destroy(loop);
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
    ev_io* ev_io_watcher = (ev_io*)malloc(sizeof(ev_io));
    ev_io_init(ev_io_watcher, recv_cb, newfd, EV_READ);
    ev_io_start(loop, ev_io_watcher);
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
    if ( 0 >= i) {
        printf("disconnect\n");
        close(w->fd);
        ev_io_stop(loop, w);
        free(w);
        return;
    }

    //收包体
    int *p = (int*)buf->ptr();
    i = recv_v(w->fd, (char*)buf->ptr() + sizeof(int), *p);

    buf->setfd(w->fd);
    //将buf压入队列
    SINGLE->sockqueue.enqueue(buf);
    return;
}
