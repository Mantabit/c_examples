#compile the source files into static object files
gcc -c main.c -o main.o
gcc -c add.c -o static/add.o
gcc -c answer.c -o static/answer.o

#compile the source files into dynamic object files
gcc -c add.c -fPIC -o dynamic/add.o
gcc -c answer.c -fPIC -o dynamic/answer.o

#create static library
ar rcs static/libstatic.a static/answer.o static/add.o

#create dynamic library
gcc -shared dynamic/add.o dynamic/answer.o -o dynamic/libdynamic.so

#link using static library
gcc main.o -Lstatic -lstatic -o main_static.out

#link using dynamic library
gcc main.o -Ldynamic -ldynamic -o main_dynamic.out

