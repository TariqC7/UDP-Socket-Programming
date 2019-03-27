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
    int main()
    {
      fd_set original_socket;
      fd_set original_stdin;
      fd_set readfds;
      fd_set writefds;
      struct timeval tv;
      int numfd;
      int socket_fd, bytes_read;
      unsigned int address_length;
      char recieve_data[MAX_LENGTH],send_data[MAX_LENGTH];
      struct sockaddr_in server_address , client_address;
      if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) 
      {
          error("socket()");
      }
      int flags = fcntl(socket_fd, F_GETFL);
      flags |= O_NONBLOCK;
      fcntl(socket_fd, F_SETFL, flags);
      //fcntl(socket_fd, F_SETFL, O_NONBLOCK); //set socket to non-blocking
      // clear the set ahead of time
      FD_ZERO(&original_socket);
      FD_ZERO(&original_stdin);
      
      
