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
