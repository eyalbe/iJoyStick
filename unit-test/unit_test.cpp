
#include "ComHandler.h"


int main(){
	Feeder* f = new Feeder();
	ComHandler* c = new ComHandler();

	//arrays for tests
	int arr[] = {0,0,0};

	//test method make data in ComHandler class.
	//test1
	c->make_data("132000", arr);
	if(arr[0] == 1 && arr[1] == 32000)
		printf("make data test 1 ok.\n");
	else
		printf("make data test 1 faild.\n");
	//test2
		c->make_data("25345", arr);
	if(arr[0] == 2 && arr[1] == 5345)
		printf("make data test 2 ok.\n");
	else
		printf("make data test 2 faild.\n");
	//test3
		c->make_data("315", arr);
	if(arr[0] == 3 && arr[1] == 1 && arr[2] == 5)
		printf("make data test 3 ok.\n");
	else
		printf("make data test 3 faild.\n");
	//test4
		c->make_data("306", arr);
	if(arr[0] == 3 && arr[1] == 0 && arr[2] == 6)
		printf("make data test 4 ok.\n");
	else
		printf("make data test 4 faild.\n");
	//test5
		c->make_data("4", arr);
	if(arr[0] == 4)
		printf("make data test 5 ok.\n");
	else
		printf("make data test 5 faild.\n");
	//test6
		c->make_data("513", arr);
	if(arr[0] == 5 && arr[1] == 1 && arr[2] == 3)
		printf("make data test 6 ok.\n");
	else
		printf("make data test 6 faild.\n");
	//test7
		c->make_data("509", arr);
	if(arr[0] == 5 && arr[1] == 0 && arr[2] == 9)
		printf("make data test 7 ok.\n");
	else
		printf("make data test 7 faild.\n");
	//test8
		c->make_data("112", arr);
	if(arr[0] == 1 && arr[1] == 12)
		printf("make data test 8 ok.\n");
	else
		printf("make data test 8 faild.\n");

	//test method feed in class Feeder.
	//test1
	arr[0] = 1; arr[1] = 5000; arr[2] = 100;
	f->feed(arr);
	//need to print: feeding x with value 5000.

	//test2
	arr[0] = 3; arr[1] = 1; arr[2] = 7;
	f->feed(arr);
	//need to print: press button no 7.

	//test3
	arr[0] = 3; arr[1] = 0; arr[2] = 2;
	f->feed(arr);
	//need to print: release button no 2.

	//test4
	arr[0] = 4; arr[1] = 11; arr[2] = 12;
	f->feed(arr);
	//need to print: reset all controls.

	//test5
	arr[0] = 2; arr[1] = 30000; arr[2] = 100;
	f->feed(arr);
	//need to print: feeding y with value 30000.

	getc(stdin);
	return 0;		
}