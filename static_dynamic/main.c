#include <stdio.h>
#include "answer.h"
#include "add.h"
#include <stdlib.h>

int main(int argc,char** argv){
	setSummand(5);
	printf("5+7=%d\n",add(7));
	printf("Answer is given by:%d\n",answer());
	return EXIT_SUCCESS;
}
