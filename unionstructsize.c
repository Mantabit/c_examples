#include <stdio.h>
#include <stdlib.h>

union lcdport{
	char value;
	struct {
		char a:1;
		char b:1;
		char c:1;
		char d:1;
		char e:1;
		char f:1;
		char g:1;
		char h:1;
	};
};

struct lcdport_alt{
	char a:1;
	char b:1;
	char c:1;
	char d:1;
	char e:1;
	char f:1;
	char g:1;
	char h:1;
};

int main(int argc, char** argv){
	printf("Size of char %d\n",sizeof(char));
	printf("Size of union %d\n",sizeof(union lcdport));
	printf("Size of struct: %d\n",sizeof(struct lcdport_alt));
/*
	Output:
	Size of char 1
	Size of union 1
	Size of struct 1
*/
	return EXIT_SUCCESS;
}
