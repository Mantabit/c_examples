#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
/*
 * sig_atomic_t describes an integer which can be accessed as an atomic entity even in
 * the case of signal interrupts
*/
volatile sig_atomic_t alarm_fired=0;
volatile sig_atomic_t end_program=0;



/*
 * Don't call printf() in a signal handler since it is neither reentrant nor thread-safe
 * and therefore also not interrupt-safe
*/
void catch_alarm(int sig){
	alarm_fired=1;
}

void catch_sigint(int sig){
	end_program=1;
}

unsigned int alarm (unsigned int seconds)
{
  struct itimerval new;
  struct itimerval old;
  new.it_interval.tv_usec = 0;
  new.it_interval.tv_sec = (long int) seconds;
  new.it_value.tv_usec = 0;
  new.it_value.tv_sec = (long int) seconds;
  if (setitimer (ITIMER_REAL, &new, &old) < 0)
    return 0;
  else
    return old.it_value.tv_sec;
}

int main(int argc,char* arv[]){
	static struct timespec tik,tok;
	//store the start time in tik
	clock_gettime(CLOCK_MONOTONIC,&tik);
	//register the alarm handler
	signal(SIGALRM,catch_alarm);
	signal(SIGINT,catch_sigint);
	//set the alarm
	alarm(2);
	while(1){
		if(alarm_fired){
			clock_gettime(CLOCK_MONOTONIC,&tok);
			long deltaT=(tok.tv_sec-tik.tv_sec)*1e9-(tok.tv_nsec-tik.tv_nsec);
			printf("alarm has been fired, current time: %'lu\n",deltaT);
			fflush(stdout);
			alarm_fired=0;
		}
		if(end_program){
			printf("end_program flag has been set, exiting program...\n");
			return EXIT_SUCCESS;
		}
	}
	return EXIT_SUCCESS;
}
