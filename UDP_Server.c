//SERVER
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <errno.h>
    #include <string.h>
    #include <stdlib.h>
    #include <sys/select.h>//use select() for multiplexing
    #include <sys/fcntl.h> // for non-blocking
    #define MAX_LENGTH 1024
    /* Select() params
     * int select(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
     * FD_SET(int fd, fd_set *set);
     * FD_CLR(int fd, fd_set *set);
     * FD_ISSET(int fd, fd_set *set);
     * FD_ZERO(fd_set *set);
    */
    void error(char *message)
    {
        perror(message);
        exit(1);
    }
