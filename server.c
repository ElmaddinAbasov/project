#include "net.h"
#include "db.h"
#include "queries.h"

int main()
{
        int cfd, res;
        struct sockaddr_in s, s2;
        socklen_t slen;
        ssize_t cnt;
	char buffer[DATAGRAM_LEN];
	pqxx::result r;

        data_base db("users");

        db.query(queries[create_table]);
        db.populate_table();

        s.sin_family = AF_INET;
        s.sin_port = htons(SERVER_PORT_NUMBER);
        s.sin_addr.s_addr = htons(INADDR_ANY);
        slen = sizeof(s);

        errno = 0;
        cfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (cfd == -1)
        {
                perror("ERROR: SERVER cfd = socket(AF_INET, SOCK_DGRAM, 0)\n");
                exit(1);
        }

        errno = 0;
        res = bind(cfd, (const struct sockaddr*)&s, slen);
        if (res == -1)
        {
                perror("ERROR: SERVER failed to bind a socket\n");
                exit(2);
        }
	
	for (;;)
	{
		sleep(SLEEP_TIME);
		errno = 0;
		cnt = recvfrom(cfd, buffer, DATAGRAM_LEN, 0, NULL, NULL);
		if (cnt == -1)
		{
			perror("ERROR: SERVER recvfrom()\n");
			exit(3);
		}
		if (0 == strcmp(buffer, FIND_USER_MESSAGE))
		{
			printf("%s\n", buffer);
			*buffer = 0;
			sleep(SLEEP_TIME);
			cnt = recvfrom(cfd, buffer, DATAGRAM_LEN, 0, NULL, NULL);
			if (cnt == -1)
			{
				perror("ERROR: SERVER recvfrom()\n get user name");
				exit(4);
			}
			*(buffer + cnt) = 0;
			printf("%s\n", buffer);
			break;
		}
	}

	r = db.query(queries[select_user]);
	for (const pqxx::row row : r)
	{
		if (0 == strcmp(row["name"].c_str(), buffer))
		{
			printf("We found user - %s\n", row["name"].c_str());
			break;
		}
	}
        errno = 0;
        res = close(cfd);
        if (res == -1)
        {
                perror("ERROR: SERVER res = close(cfd)\n");
                exit(5);
        }
        exit(0);
}

