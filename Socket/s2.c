#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_NAME "mySocket.socket"

void printError(int a){
	if(a=-1){
		perror("Couldn't create socket\n");
		exit(EXIT_FAILURE);
	}
}

void writeerror(int a){
	if(a=-1){
		perror("Error in writing\n");
		exit(EXIT_FAILURE);
	}
}

void readerror(int a){
	if(a=-1){
		perror("Error in read\n");
		exit(EXIT_FAILURE);
	}
}


void Error(int a){
	if(a=-1){
		perror("Server Down Error\n");
		exit(EXIT_FAILURE);
	}
}


void binderror(int a){
	if(a=-1){
		perror("Bind error\n");
		exit(EXIT_FAILURE);
	}
}

void listenError(int a){
	if(a=-1){
	perror("Listen Error\n");
	exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[]) {
	struct sockaddr_un servername;
	int dflag = 0;
	int csocket;
	int ret;
	int index = 0;
	int data_socket;
	char buff[7];

	csocket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
	printError(csocket);

	memset(&servername, 0, sizeof(servername));
	servername.sun_family = AF_UNIX;
	strncpy(servername.sun_path, SOCKET_NAME, sizeof(servername.sun_path) - 1);

	ret = bind(csocket, (const struct sockaddr *) &servername, sizeof(servername));

	binderror(ret);

	ret = listen(csocket, 100);
	listenError(ret);

	while(1) {
		data_socket = accept(csocket, NULL, NULL);
		if(data_socket == -1) {
			perror("couldn't accept\n");
			exit(EXIT_FAILURE);
		}

		index = 0;
		int curindex = index;
		while(1) {
			ret = read(data_socket, buff, sizeof(buff));
			readerror(ret);

			buff[sizeof(buff) - 1] = 0;
			curindex = buff[0];

			if(!strncmp(buff, "DOWN", sizeof(buff))) {
				dflag = 1;
				break;
			}

			//buff contains the string with the 0th idx as the index of the string
			printf("String sent by client: \n");		
			
			for(int i = 0; i <6; i++) {
				if(i==0) printf("%d ",buff[i]);
				else printf("%c",buff[i]);
			}

			printf("\n");
			sprintf(buff, "%d", curindex);
			printf("Acknowledge id = %s\n", buff);		

			if(curindex == index + 5) {
				index = curindex;
				ret = write(data_socket, buff, sizeof(buff));
			}	

			if(curindex >= 50) break;
		}
		
		

		close(data_socket);

		if(dflag) {
			printf("SHUTTING SERVER");
			close(csocket);
			unlink(SOCKET_NAME);
			exit(EXIT_SUCCESS);
			break;
		}
		
		if(ret == -1) {
			perror("write");
			exit(EXIT_FAILURE);
		}
	}

	return 0;
}