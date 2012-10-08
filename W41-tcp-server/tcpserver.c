/*
 * tcpserver.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

void error(char *msg)
{
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, clientfd, portno, clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	char *reply = "hallo\n";

	if (argc < 2) {
		fprintf(stderr, "ERROR, no port specified\n");
		exit(0);
	}
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		error("ERROR, cannot open socket\n");
		exit(0);
	}
	memset(&serv_addr, 0, sizeof(serv_addr));
	portno = atoi(argv[1]);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		error("ERROR, cannot bind socket\n");
		exit(0);
	}
	n = listen(sockfd, 5);
	if (n) {
		error("ERROR, cannot listen on socket\n");
		exit(0);
	}

	clilen = sizeof(cli_addr);
	clientfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (clientfd < 0){
		error("ERROR, cannot accept on socket\n");
		exit(0);
	}
	printf("Client socket fd %d.\n",clientfd);

	// read from socket
	n = recv(clientfd, buffer, sizeof(buffer) - 1, 0);
	printf("%d bytes received\n", n);
	buffer[n] = 0;
	printf("msg: %s\n", buffer);

	// write ACK message to the client
	n = send(clientfd, reply, strlen(reply), 0);
	printf("%d bytes sent\n", n);

	return 0;
}
