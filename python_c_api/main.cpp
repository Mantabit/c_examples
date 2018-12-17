#include <python3.6/Python.h>
#include <python3.6/listobject.h>
#include <stdlib.h>
#include <fstream>
#include <unistd.h>
#include <math.h>

#define N_LIST 100

using namespace std;

double f=50;
double ang_frequency=2*M_PI*f;
double dt=1/(f*N_LIST);

int main(int argc,char** argv){
    char currentdir[200];
    getcwd(currentdir,200);
    strcat(currentdir,"/bin/Debug");
    printf("%s\n",currentdir);
    if(setenv("PYTHONPATH",currentdir,0)!=0){
        printf("Could not set PYTHONPATH\n");
    };
    //start the python interpreter
    Py_Initialize();

    PyObject* modulename=PyUnicode_FromString("Module");
    PyObject* module=PyImport_Import(modulename);
    Py_DECREF(modulename);
    if(module!=NULL){
        PyObject* py_function=PyObject_GetAttrString(module,"plotFunction");
        double c_argx=5.5;
        //create a python list object and pass to function
        PyObject* py_listy=PyList_New(N_LIST);
        PyObject* py_listx=PyList_New(N_LIST);
        for(int i=0; i<N_LIST; i++){
            double c_currentdouble=sin(i*dt*ang_frequency);
            double c_currenttime=dt*i;
            PyObject* py_currentdoubley=Py_BuildValue("d",c_currentdouble);
            PyObject* py_currenttime=Py_BuildValue("d",c_currenttime);
            PyList_SetItem(py_listy,i,py_currentdoubley);
            PyList_SetItem(py_listx,i,py_currenttime);
        }
        if(py_function&&PyCallable_Check(py_function)){
            //PyObject* res=PyObject_CallFunction(py_function,"d",c_argx);
            pid_t pid=fork();
            if(pid==0){
                PyObject* res=PyObject_CallFunctionObjArgs(py_function,py_listx,py_listy,NULL);
                return EXIT_SUCCESS;
            }
        }
        else{
            printf("Could not create function object.");
            printf("\n%d",py_function);
            return EXIT_FAILURE;
        }
    }
    else{
        printf("Cannot find module.");
        return EXIT_FAILURE;
    }
    printf("Exiting program\n");
}
