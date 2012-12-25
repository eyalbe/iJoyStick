
#include "ComHandler.h"

ComHandler::ComHandler(){
	cli_len = sizeof(cli);
	ready_to_listen = FALSE;
	WSADATA Data;

	int status = WSAStartup(MAKEWORD(2, 2), &Data);
	if(status != 0){
		printf("ERROR: WSAStartup unsuccessful");
		return;
	}
	if ((fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
		perror("cannot create socket");
		return;
	}
	srv.sin_family = AF_INET; /* use the Internet addr family */
	srv.sin_port = htons(6000); /* bind socket ‘fd’ to port 5555*/

	/* bind: a client may connect to any of my addresses */
	srv.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(fd, (struct sockaddr*) &srv, sizeof(srv)) < 0) {
		perror("cannot bind socket");
		return;
	}
	if(listen(fd, 1) < 0){
		perror("cannot listen socket");
		return;
	}
	ready_to_listen = TRUE;
}

int ComHandler::start_listen(Feeder* f){
	newfd = accept(fd, (struct sockaddr*) &cli, &cli_len);
	if(newfd < 0) {
		perror("cannot accept connection on socket");
		return 1;
	}
	printf("listening...\n");
	int count = 0;
	int data_array[] = {0,0,0};
	user_input[6] = '\0';
	while(TRUE){
		count = 0;
		while(1){
			count += recv(newfd, user_input+count, 1, 0);
			if(user_input[count-1] == '\n'){
				user_input[count-1] = '\0';
				break;
			}
		}
		make_data(user_input, data_array);
		f->feed(data_array);
	}
	return 0;
}

void ComHandler::make_data(char* str, int* arr){
	switch (str[0])
	{
	case('1'):
		arr[0] = 1;
		arr[1] = atoi(str+1);
		//if (str[1] == '-')
			//arr[1] *= -1;
	break;
	case('2'):
		arr[0] = 2;
		arr[1] = atoi(str+1);
	break;
	case('3'):
		arr[0] = 3;
		arr[1] = str[1]-48;
		arr[2] = str[2]-48;
	break;
	case('4'):
		arr[0] = 4;
	break;
	case('5'):
		arr[0] = 5;
		arr[1] = str[1]-48;
		arr[2] = str[2]-48;
	break;
	}
}

void ComHandler::closeSoc(){
	closesocket(fd);
}