//CLIENT
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h> //host struct
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>//use select() for multiplexing
#include <sys/fcntl.h> // for non-blocking
#define MAX_LENGTH 1024
#define HOST "localhost" //127.0.0.1

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
  int socket_fd,bytes_recieved;
  unsigned int address_length;
  struct sockaddr_in server_address;
  struct hostent *host;
  char send_data[MAX_LENGTH],recieve_data[MAX_LENGTH];
  host = (struct hostent *) gethostbyname((char *)HOST);//127.0.0.1
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
  
