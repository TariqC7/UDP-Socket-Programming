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
