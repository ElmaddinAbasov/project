#ifndef NET_H
#define NET_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <cstring>
#define FIND_USER_MESSAGE "FIND_USER"
#define FIND_USER_MESSAGE_LEN(x) strlen(x)
#define CLIENT_PORT_NUMBER 3000
#define SERVER_PORT_NUMBER 3001
#define DATAGRAM_LEN 512
#define SLEEP_TIME 10
#endif
