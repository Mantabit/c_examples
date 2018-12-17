#include <python3.6/Python.h>
#include <python3.6/listobject.h>
#include <stdlib.h>
#include <fstream>

#define N_LIST 10

using namespace std;

int main(int argc,char** argv){
    setenv("PYTHONPATH","/home/dvarx/c_examples/threads/pythontest/bin/Debug",0);
    //start the python interpreter
    Py_Initialize();

    PyObject* modulename=PyUnicode_FromString("Module");
    PyObject* module=PyImport_Import(modulename);
    Py_DECREF(modulename);
    if(module!=NULL){
        PyObject* py_function=PyObject_GetAttrString(module,"printList");
        double c_argx=5.5;
        //create a python list object and pass to function
        PyObject* py_list=PyList_New(N_LIST);
        for(int i=0; i<N_LIST; i++){
            PyObject* py_currentint=Py_BuildValue("i",i);
            PyList_SetItem(py_list,i,py_currentint);
        }
        if(py_function&&PyCallable_Check(py_function)){
            //PyObject* res=PyObject_CallFunction(py_function,"d",c_argx);
            PyObject* res=PyObject_CallFunctionObjArgs(py_function,py_list,NULL);
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
}
