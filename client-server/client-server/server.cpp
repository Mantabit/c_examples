#include <iostream>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

int main(int argc,char** argv)
{
    //define the port on which we are going to listen for connections
    int listening_port=1234;
    //create a socket which will be listening for connections
    //defines the protocol family, the connection type (TCP) and the protocl (usually 0)
    int listening_socket=socket(AF_INET,SOCK_STREAM,0);
    if(listening_socket<0){
        std::cout << "An error occured while creating the socket: " << strerror(errno) << std::endl;
        return(EXIT_FAILURE);
    }
    //create a sockaddr_in struct which holds IP and PORT information and initialize to zero
    struct sockaddr_in address;
    memset(&address,0,sizeof(struct sockaddr_in));
    //set the address family of the socketaddress struct
    address.sin_family=AF_INET;
    //set the port number of the socketaddress struct. The port number needs to be converted from host-byte-order to network-byte-order (big-endian)
    //for converting ints use htons (host to network short)
    address.sin_port=htons(listening_port);
    //sin_addr member of a socketaddress struct defines the IP address of that socketaddress struct. In the context of a listener-socket, it defines the IP address interfaces of the machine
    //which the port should listen to. Set this to INADDR_ANY to listen to all available network interfaces of the machine
    address.sin_addr.s_addr=htonl(INADDR_ANY);
    //bind the socket to the address
    int res=bind(listening_port,(struct sockaddr*)&address,sizeof(struct sockaddr_in));
    //test if socket binding succesful
    if(res<0){
        std::cout << "An error occured binding the socket: " << strerror(errno) << std::endl;
        return(EXIT_FAILURE);
    }
    //set the linger options. if the program is shut down, the port will remain open until the remaining messages in the port queue are sent or the lingering timeout is reached
    struct linger linger_opt;
    linger_opt.l_linger=0;
    linger_opt.l_onoff=1;
    //SOL_SOCKET indicates that the setting is to interpreted at the socket level
    //one could also choose TCP instead of SOL_SOCKET to indicate the option is meant for the TCP protocol
    setsockopt(listening_port,SOL_SOCKET,SO_LINGER,&linger_opt,sizeof(struct linger));
    //listen to connection. accept exactly one connection
    listen(listening_port,1);
    if(res<0){
        std::cout << "An error has occurred listening to the listener-socket: " << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }
    //define data types to hold the portaddress of the peer as well as the length of the portaddress of the peer
    struct sockaddr_in peer_address;
    socklen_t peer_socklen;
    //accept the next connection in the listener_port queue
    //this will return a new socket which can be used for communication with the peer
    int peer_socket=accept(listening_port,(sockaddr*)&peer_address,&peer_socklen);
    if(peer_socket<0){
        std::cout << "An error has occured accepting the peer socket: " << strerror(errno) << std::endl;
        return(EXIT_FAILURE);
    }
    //close the listening socket
    close(listening_port);

    //write a message into the socket
    write(peer_socket,"Hello!\n",7);
    //receive some data from the socket
    char buffer[1024];
    //read a maximum of 1024 character into buffer
    //returns the number of bytes read or a somehting negative in case of an error
    res=read(peer_socket,buffer,sizeof(buffer));
    if(res<0){
        std::cout << "An error has occurred reading from the socket: " << strerror(errno) << std::endl;
        return(EXIT_FAILURE);
    }
    buffer[res]=0; //set the null character at the end of the received string
    std::cout << "Received " << res << " bytes: " << buffer << std::endl;
    //close the peer-socket and exit the program
    close(peer_socket);
    return EXIT_SUCCESS;
}
