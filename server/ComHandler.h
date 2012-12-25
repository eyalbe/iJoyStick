
#include <winsock2.h>
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include "Feeder.h"

#pragma comment(lib, "ws2_32.lib")

#ifndef COMHANDLER_H_
#define COMHANDLER_H_

class ComHandler{

public:
	bool ready_to_listen;
	
	ComHandler();
	int start_listen(Feeder* f);
	void closeSoc();

private:
	int fd;						/* socket descriptor */
	struct sockaddr_in srv;		/* used by bind() */
	struct sockaddr_in cli;		/* used by accept() */
	int newfd;					/* returned by accept() */
	int cli_len; // = sizeof(cli);	/* used by accept() */
	char user_input[101];

	void make_data(char*, int*);	
};

#endif