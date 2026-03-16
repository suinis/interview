#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
using namespace std;

const int MAX_EVENTS = 1024;

// 设置非阻塞
void set_nonblocking(int fd) {
    int flag = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}

int main() {
    // 1. 创建epoll实例
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) return -1;
    
    // 2. 监听socket（省略创建listen_fd的逻辑）
    int listen_fd = /* 创建并绑定监听端口 */;
    set_nonblocking(listen_fd);
    
    // 3. 注册监听事件
    epoll_event ev;
    ev.events = EPOLLIN | EPOLLET; // 边缘触发
    ev.data.fd = listen_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &ev);
    
    // 4. 事件循环
    vector<epoll_event> events(MAX_EVENTS);
    while (true) {
        int n = epoll_wait(epoll_fd, events.data(), MAX_EVENTS, -1);
        for (int i = 0; i < n; ++i) {
            int fd = events[i].data.fd;
            if (fd == listen_fd) {
                // 处理新连接
                int conn_fd = accept(listen_fd, nullptr, nullptr);
                set_nonblocking(conn_fd);
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = conn_fd;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, conn_fd, &ev);
            } else if (events[i].events & EPOLLIN) {
                // 处理读事件（省略读数据逻辑）
                char buf[1024] = {0};
                read(fd, buf, sizeof(buf));
                // 读完后注册写事件（可选）
                ev.events = EPOLLOUT | EPOLLET;
                ev.data.fd = fd;
                epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &ev);
            } else if (events[i].events & EPOLLOUT) {
                // 处理写事件（省略写数据逻辑）
                write(fd, "OK", 2);
                // 写完后关闭连接
                close(fd);
                epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, nullptr);
            }
        }
    }
    close(epoll_fd);
    return 0;
}