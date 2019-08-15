# Installing MPICH #

Download the latest version of MPICH on the MPICH [website](https://www.mpish.org). Install using the following commands:

```bash
tar -xzvf mpich-3.2.2.tar.gz
cd mpich-3.2.2
./configure --prefix/where/to/install/mpich
make
make install
#append the binary directory the the current PATH
echo "PATH=\$PATH:/where/to/install/mpich/bin" >> ~/.bashrc
```
Compile the examples provided in `mpich-3.2.2/examples`.

