#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_t threadsids[2];

void doSomething(void* arg){
    //get the id of the current thread
    pthread_t id=pthread_self();
    if(pthread_equal(id,threadsids[0])){
        int result=100;
        printf("First thread running!\n");
        pthread_exit(&result);
    }
    if(pthread_equal(id,threadsids[1])){
        int result=200;
        printf("Second thread running!\n");
        pthread_exit(&result);
    }
    return NULL;
}

int main()
{
    int i=0;
    int err;
    //use this array to store the results of the threads
    int results[2];

    while(i<2){
        err=pthread_create(&threadsids[i],NULL,&doSomething,NULL);
        if(err!=0){
            printf("An error occurres: %s\n",strerror(err));
        }
        else{
            printf("Thread created succesfully!\n");
        }
        i++;
    }
    //wait for thread and write content pointed to by thread return pointer to results array
    pthread_join(threadsids[0],(void**)&results);
    pthread_join(threadsids[1],(void**)(results+1));
    printf("Result of first thread: %d\n",results[0]);
    printf("Result of second thread: %d\n",results[1]);
    printf("Exiting Program\n");

    return EXIT_SUCCESS;
}
