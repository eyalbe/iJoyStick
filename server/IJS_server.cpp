#include "ComHandler.h"

int main(){
	
	Feeder* f = new Feeder();
	if (f->get_device() != 0){
		printf("cannot acquire device...\n");
		getc(stdin);
		return 0;
	}
	else
		printf("target device acquired...\n");
	ComHandler* h = new ComHandler();
	if (h->ready_to_listen == TRUE){
		printf("ready to listen...\n");
		h->start_listen(f);
	}
	else{
		printf("not ready to listen...\n");
		getc(stdin);
	}
	h->closeSoc();
	delete(f);
	delete(h);
	return 0;
}