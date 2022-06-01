#include "Server.h"
#include <string>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <pthread.h>

#include "Message.h"
#include "Socket.h"
// #include "InputInfo.h"
#include "ServerGame.h"

#pragma region STATIC ATTRIBUTES

ServerGame *Server::_game = nullptr;
volatile bool Server::_inputRegistered = false;
// InputInfo* Server::_playersInput = nullptr;
volatile bool Server::_gameEnd = false;

#pragma endregion

Server::Server(const char *s, const char *p)
{
    _socket = new Socket(s, p);
    _socket->Bind();

    _clients.reserve(MAX_PLAYERS);
    // _playersInput = new InputInfo[MAX_PLAYERS];
}

// Receives and processes messages from clients
void Server::ProcessMessages()
{
    std::cout << "Snake server is running\n"
              << "Waiting for players to join\n";
    int playersReady = 0;
    int inputRecv = 0;
    int id = 1;
    while (true) // receive messages
    {
        Socket *client;
        Message msg;
        _socket->recv(msg, client);

        switch (msg._type)
        {
        case Message::LOGIN:
            if (_clients.size() < MAX_PLAYERS) // add player
            {
                _clients.push_back(client);
                std::cout << "Player " << _clients.size() << " joined the game\n";

                Message ms(Message::INIT);                // notify client to init game and send player id
                ms._player = (_clients.size() - 1) + '0'; // client is last player to join
                _socket->send(ms, *client);

                if (_gameEnd)
                    _gameEnd = false; // game thread can run
            }
            else
            {
                // TODO: send message to stop game as player can't join
                std::cout << "Maximum number of players reached\n";
            }
            break;

        case Message::READY:
            playersReady++;
            if (playersReady == MAX_PLAYERS) // ready to start game
            {
                CreateGameThread(); // Thread to run game
                SendToClients(Message(Message::START));
                std::cout << "Game ready\n";
            }
            break;

        // case Message::INPUT:
        //     inputRecv++;
        //     _playersInput[(msg._player-'0')] = InputInfo(msg._inputInfo);

        //     if(inputRecv == MAX_PLAYERS) //game update can be run
        //     {
        //         inputRecv = 0;
        //         _inputRegistered = true;
        //     }
        //     //std::cout << "Input received\n";
        // break;
        case Message::NEXT_DIALOGUE:
        {
            Message ms(Message::NEW_DIALOGUE, (id + 1), (id + 2));
            id += 2;

            _socket->send(ms, *client);
        }
        break;

        case Message::LOGOUT:
            for (int i = 0; i < _clients.size(); i++) // delete player from saved clients
            {
                if (*_clients[i] == *client)
                {
                    _clients.erase(_clients.begin() + i);

                    int id = (msg._player - '0') + 1;
                    std::cout << "Player " << id << " exited game" << std::endl;
                    break;
                }
            }
            _gameEnd = true;
            playersReady = 0;
            inputRecv = 0;
            break;
        }
    }
}

// Sends a message to all clients connected to the server
void Server::SendToClients(Message msg)
{
    for (Socket *sock : _clients)
    {
        _socket->send(msg, *sock);
    }
}

// Creates and sets the thread that runs the game on the server
void Server::CreateGameThread()
{
    pthread_t gameThread; // thread
    pthread_attr_t attr;

    _game = new ServerGame(this);
    _game->Init(); // initialize game before setting thread

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int res = pthread_create(&gameThread, &attr, RunGame, NULL);

    if (res != 0)
        std::cout << "Error, Thread was not created\n";
}

// Thread function that runs the game server side
void *Server::RunGame(void *)
{
    /// ***     FOR TEST: COMMENT PLAYER LOST CONDITION    *** ///
    while (!_gameEnd)
    {
        if (_inputRegistered)
        {
            _inputRegistered = false;
            // _game->SetInputInfo(_playersInput);
            _game->Update();
        }
    }
    pthread_exit(NULL);
}

Server::~Server()
{
    if (_game != nullptr)
    {
        delete _game;
        _game = nullptr;
    }

    delete _socket;
    _socket = nullptr;

    // delete [] _playersInput;
}