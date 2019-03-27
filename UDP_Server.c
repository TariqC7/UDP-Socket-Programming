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
       FD_ZERO(&readfds);
      FD_ZERO(&writefds);
      // adding descriptors to the set (0 - stands for STDIN)
      FD_SET(socket_fd, &original_socket);//instead of 0 put socket_fd
      FD_SET(socket_fd, &readfds);
      FD_SET(0,&original_stdin);
      FD_SET(0, &writefds);
      // since we got s2 second, it's the "greater", so we use that for
      // the n param in select()
      numfd = socket_fd + 1;
      // wait until either socket has data ready to be recv()d (timeout 10.5 secs)
      tv.tv_sec = 10;
      tv.tv_usec = 500000;
      server_address.sin_family = AF_INET;
      server_address.sin_port = htons(5000);
      server_address.sin_addr.s_addr = INADDR_ANY;
      bzero(&(server_address.sin_zero),8);
      if (bind(socket_fd,(struct sockaddr *)&server_address, sizeof(struct sockaddr)) == -1)
      {
          error("bind()");
      }
      address_length = sizeof(struct sockaddr);
      printf("\nUDP_Server Waiting for client to respond...\n");
      fflush(stdout);
      
      
      
      
