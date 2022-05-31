#include "Client.h"
#include "Socket.h"
#include "Message.h"
#include <iostream>
#include <pthread.h>

#pragma region STATIC ATTRIBUTES

Socket* Client::_socket = nullptr;
volatile bool Client::_startGame = false;
volatile bool Client::_initGame = false;
char Client::_id = '0';

#pragma endregion

//Initializes client's resources for connection with server
void Client::Init(const char * s, const char * p)
{
    _socket = new Socket(s, p);

    //Create thread to receive messages from server
    pthread_t recvThread;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int res = pthread_create(&recvThread, &attr, net_thread, NULL);

    if(res != 0)
        std::cout << "Error, Thread was not created\n";

    Login(); //login to server
}

#pragma region SEND MESSAGES

//Login to game server
void Client::Login()
{
    Message msg(Message::LOGIN);
    _socket->send(msg, *_socket);   
}

//Logout from game server
void Client::Logout()
{
    Message msg(Message::LOGOUT);
    msg._player = _id;
    _socket->send(msg, *_socket);  
}

//Notify server game is ready to start
void Client::SendGameReady()
{
    Message msg(Message::READY);
    _socket->send(msg, *_socket);
}

#pragma endregion

//Method for receiving messages through thread
void* Client::net_thread(void*)
{
    while (true)
    {
        Socket* server;
        Message msg;
        _socket->recv(msg, server);

        if(msg._type == Message::INIT) //game init
        {
            _id = msg._player;
            _initGame = true;
        }
        else if(msg._type == Message::START) //game start
        {
            _startGame = true;
        }
    }
    
}

//Releases resources
void Client::Release()
{
    Logout();
    delete _socket;
    _socket = nullptr;
}