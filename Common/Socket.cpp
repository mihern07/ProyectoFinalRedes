#include "Socket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#include <iostream>
#include <stdexcept>

#include <ostream>
#include <string.h>
#include "Message.h"


Socket::Socket(const char * address, const char * port):sd(-1)
{
    //Construir un socket de tipo AF_INET y SOCK_DGRAM usando getaddrinfo.
    //Con el resultado inicializar los miembros sd, sa y sa_len de la clase

    struct addrinfo hints;
    struct addrinfo* res;

    memset((void*) &hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    int rc = getaddrinfo(address, port, &hints, &res);
    if(rc < 0)
        std::cout << "Conexion error" << std::endl;
    
    sa = *res->ai_addr;
    sa_len = res->ai_addrlen;

    sd = socket(res->ai_family, res->ai_socktype, 0);    
    if(sd < 0)
        std::cout << "Error creating socket" << std::endl;

    freeaddrinfo(res);
}

Socket::Socket(struct sockaddr * _sa, socklen_t _sa_len):sd(-1), sa(*_sa),
        sa_len(_sa_len)
{

}


bool operator== (const Socket &s1, const Socket &s2)
{     
    struct sockaddr_in* sock1 = (struct sockaddr_in*) s1.sa.sa_data; 
    struct sockaddr_in* sock2 = (struct sockaddr_in*) s2.sa.sa_data;
            
    return(sock1->sin_family == sock2->sin_family && 
    sock1->sin_port == sock2->sin_port &&
    sock1->sin_addr.s_addr == sock2->sin_addr.s_addr);
}

int Socket::Bind()
{
    return ::bind(sd, (const struct sockaddr *) &sa, sa_len);
}

int Socket::recv(Message &obj, Socket * &sock)
{
    
    struct sockaddr sa;
    socklen_t sa_len = sizeof(struct sockaddr);

    char buffer[MAX_MESSAGE_SIZE];

    ssize_t bytes = ::recvfrom(sd, buffer, MAX_MESSAGE_SIZE, 0, &sa, &sa_len);


    if ( bytes <= 0 )
    {
        std::cout << "RETURN\n";
        return -1;
    }

    if ( sock != 0 )
    {
        sock = new Socket(&sa, sa_len);
    }

    obj.from_bin(buffer);
    
    return 0;
}


int Socket::send(Message& obj, const Socket& sock)
{
    //Serializar el objeto
    //Enviar el objeto binario a sock usando el socket sd

    obj.to_bin();

    int data = sendto(sd, (void*)obj.data(), obj.size(), 0, (struct sockaddr*)&sock.sa, sock.sa_len);

    if(data <= 0)
        return -1;
    return 0;
}

Socket::~Socket()
{
    
}