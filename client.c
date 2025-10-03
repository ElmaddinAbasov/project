#include "net.h"
int main(int argc, char** argv)
{
	int cfd, res;
	struct sockaddr_in s, s2;
	socklen_t slen;
	ssize_t cnt;

	if (argc < 2)
	{
		fprintf(stderr, "ERROR: provide user\n");
		exit(1);
	}

	s.sin_family = AF_INET;
	s.sin_port = htons(CLIENT_PORT_NUMBER);
	s.sin_addr.s_addr = htons(INADDR_ANY);
	slen = sizeof(s);

	errno = 0;
	cfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (cfd == -1)
	{
		perror("ERROR: cfd = socket(AF_INET, SOCK_DGRAM, 0)\n");
		exit(2);
	}

	errno = 0;
	res = bind(cfd, (const struct sockaddr*)&s, slen);
	if (res == -1)
	{
		perror("failed to bind a socket\n");
		exit(3);
	}

        s2.sin_family = AF_INET;
        s2.sin_port = htons(SERVER_PORT_NUMBER);
        s2.sin_addr.s_addr = htons(INADDR_ANY);
        slen = sizeof(s2);

	for (;;)
	{
		errno = 0;
		cnt = sendto(cfd, FIND_USER_MESSAGE, FIND_USER_MESSAGE_LEN(FIND_USER_MESSAGE), 0, (const struct sockaddr*)&s2, slen);
		if (cnt == -1)
		{
			perror("ERROR: sendto");
			exit(4);
		}
		sleep(SLEEP_TIME);
		errno = 0;
                cnt = sendto(cfd, argv[1], strlen(argv[1]), 0, (const struct sockaddr*)&s2, slen);
                if (cnt == -1)
                {
                        perror("ERROR: sendto");
                        exit(5);
                }
		break;
	}

	errno = 0;
	res = close(cfd);
	if (res == -1)
	{
		perror("ERROR: res = close(cfd)\n");
		exit(6);
	}

	exit(0);
}
