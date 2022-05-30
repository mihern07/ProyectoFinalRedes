#ifndef _H_Socket_H_
#define _H_Socket_H_
#include <sys/socket.h>

//FORWARD DECLARATIONS
class Socket;
class Message;

/**
 * Compares two sockets to determine if they are the same
 */
bool operator== (const Socket &s1, const Socket &s2);

class Socket
{
public:

    Socket(const char * address, const char * port);
    
    Socket(struct sockaddr * _sa, socklen_t _sa_len);

    ~Socket();

    friend bool operator== (const Socket &s1, const Socket &s2);

    int recv(Message &obj, Socket * &sock);

    int send(Message &obj, const Socket& sock);

    int Bind();

private:

    static const int32_t MAX_MESSAGE_SIZE = 32768;

    int sd;

    struct sockaddr sa;
    socklen_t       sa_len;

};
#endif