#include <stdio.h>

int gSummand;

void setSummand(int summand){
		gSummand=summand;
}

int add(int summand){
	return summand+gSummand;
}

void __attribute__ ((constructor)) initLibrary(void){
	printf("Library was initialized\n");
	gSummand=0;
}

void __attribute__ ((destructor)) cleanUpLibrary(void){
	printf("Library is exited\n");
}
