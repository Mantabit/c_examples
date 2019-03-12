#include <stdio.h>
#include <stdlib.h>

int main(int argc,char** argv){
	printf("Size of char: %lu\n",sizeof(char));
	printf("Size of short: %lu\n",sizeof(short));
	printf("Size of int: %lu\n",sizeof(int));
	printf("Size of long: %lu\n",sizeof(long));
	
	long* data=malloc(sizeof(long));
	*data=0;
	/*
	 * By using a char (byte) pointer, one can access each byte individually
	 * via pointer arithmetic
	 */
	char* dataptr=(char*)(data);
	*dataptr=0xFF;
	*(dataptr+2)=0xFF;
	
	printf("Hexadecimal output: 0x%08lX\n",*data);
	
	free(data);
	return EXIT_SUCCESS;
}
