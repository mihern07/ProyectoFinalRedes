#include "Server.h"
#include <string>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <memory>

#include "Message.h"
#include "SocketServer.h"
// #include "InputInfo.h"
#include "ServerGame.h"
#include "JSONValue2.h"
#include <SDL2/SDL.h>

#pragma region STATIC ATTRIBUTES

ServerGame *Server::_game = nullptr;
volatile bool Server::_inputRegistered = false;
// InputInfo* Server::_playersInput = nullptr;
volatile bool Server::_gameEnd = false;

#pragma endregion

Server::Server(const char *s, const char *p)
{
    _socket = new SocketServer(s, p);
    _socket->bind();

    _client1 = nullptr;
    _client2 = nullptr;
    numRegisteredClients = 0;
    maxDialogueNumber = 0;
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

    // TODO check the correctness of values and issue a corresponding
    // exception. Now we just do some simple checks, and assume input
    // is correct.

    // Load JSON configuration file. We use a unique pointer since we
    // can exit the method in different ways, this way we guarantee that
    // it is always deleted

    // int sdlInit_ret = SDL_Init(SDL_INIT_EVERYTHING);

    std::unique_ptr<JSONValue2> jValueRoot2(JSON2::ParseFromFile("../resources/config/sdlutilsdemo.resources.json"));

    // check it was loaded correctly
    // the root must be a JSON object
    if (jValueRoot2 == nullptr || !jValueRoot2->IsObject())
    {
        std::cout << "Something went wrong while load/parsing 'counter.json'";
    }

    std::cout << "All ok\n";

    // we know the root is JSONObject
    JSONObject root = jValueRoot2->AsObject();
    JSONValue2 *jValue = nullptr;
    std::cout << "Lo hace\n";

    // load messages
    jValue = root["messages"];
    if (jValue != nullptr)
    {
        if (jValue->IsArray())
        {
            msgs_.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
            for (auto &v : jValue->AsArray())
            {
                if (v->IsObject())
                {
                    JSONObject vObj = v->AsObject();
                    std::string key = vObj["idNum"]->AsString();
                    std::string txt = vObj["person"]->AsString();
                    std::string isDecision = vObj["isDecision"]->AsString();
                    std::string nextDialogue = vObj["nextDialogue"]->AsString();
                    maxDialogueNumber++;
                    neededInfo aux = neededInfo(txt, isDecision, nextDialogue);
                    msgs_.emplace(key, aux);
                }
                else
                {
                    throw "'messages' array in 'sdlutilsdemo.resources.json' includes and invalid value";
                }
            }
        }
        else
        {
            throw "'messages' is not an array in 'sdlutilsdemo.resources.json'";
        }
    }
    std::cout << "Llega al final\n";

    _client1 = nullptr;
    _client2 = nullptr;

    while (true) // receive messages
    {
        SocketServer *client = nullptr;
        Message msg;
        _socket->recv(msg, client);

        switch (msg._type)
        {
        case Message::LOGIN:
            if (numRegisteredClients < MAX_PLAYERS) // add player
            {
                if (_client1 != nullptr)
                {
                    std::cout << "Creado 2\n";
                    _client2 = client;
                }
                else
                {
                    std::cout << "Creado 1\n";
                    // std::cout<<client->sd<<"\n";
                    _client1 = client;
                    // std::cout<<_client1->sd<<"\n";
                }
                numRegisteredClients++;
                std::cout << "Player " << numRegisteredClients << " joined the game\n";

                Message ms(Message::INIT);                     // notify client to init game and send player id
                ms._player = (numRegisteredClients - 1) + '0'; // client is last player to join
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

        case Message::NEXT_DIALOGUE:
        {
            if (id + 2 <= maxDialogueNumber)
            {

                if (msgs_.at(std::to_string(id + 1)).isDecision_ == "false")
                {
                    Message msNew(Message::NEW_DIALOGUE, (id + 1), (id + 2));
                    Message msWaiting(Message::NEW_WAITING_DIALOGUE, (id + 1), (id + 2));

                    std::string personToSend = msgs_.at(std::to_string(id + 1)).person_;
                    if (personToSend == "1")
                    {
                        _socket->send(msNew, *_client1);
                        _socket->send(msWaiting, *_client2);
                    }
                    else
                    {
                        _socket->send(msNew, *_client2);
                        _socket->send(msWaiting, *_client1);
                    }

                    id += 2;
                }
                else
                {
                    // Decision decision_ = Decision(msgs_.at(st::to_string(id+1)))
                    Message msNew(Message::NEW_DECISION, (id + 1), (id + 2), (id + 3));
                    Message msWaiting(Message::NEW_WAITING_DECISION, (id + 1), (id + 2), (id + 3));

                    std::string personToSend = msgs_.at(std::to_string(id + 1)).person_;
                    if (personToSend == "1")
                    {
                        _socket->send(msNew, *_client1);
                        _socket->send(msWaiting, *_client2);
                    }
                    else
                    {
                        _socket->send(msNew, *_client2);
                        _socket->send(msWaiting, *_client1);
                    }
                }
            }
        }
        break;

        case Message::CHOSE_DECISION:
        {
            id = std::stoi(msgs_.at(std::to_string(id + msg.getNextDialogue())).nextDialogue_);
            if (id + 2 <= maxDialogueNumber)
            {
                Message msNew(Message::NEW_DIALOGUE, (id + 1), (id + 2));
                Message msWaiting(Message::NEW_WAITING_DIALOGUE, (id + 1), (id + 2));

                std::string personToSend = msgs_.at(std::to_string(id + 1)).person_;
                if (personToSend == "1")
                {
                    _socket->send(msNew, *_client1);
                    _socket->send(msWaiting, *_client2);
                }
                else
                {
                    _socket->send(msNew, *_client2);
                    _socket->send(msWaiting, *_client1);
                }
            }
        }
        break;

        case Message::LOGOUT:
            if (msg._player = 0 + '0')
            {
                int id = (msg._player - '0') + 1;
                std::cout << "Player exited game" << std::endl;
                delete _client1;
                _client1 = nullptr;
            }
            else if (msg._player == 1 + '0')
            {
                int id = (msg._player - '0') + 1;
                std::cout << "Player exited game" << std::endl;
                delete _client2;
                _client2 = nullptr;
            }
            numRegisteredClients--;
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
    if (_client1 != nullptr)
    {
        _socket->send(msg, *_client1);
    }

    if (_client2 != nullptr)
    {
        _socket->send(msg, *_client2);
    }
    // for (Socket *sock : _clients)
    // {
    //     _socket->send(msg, *sock);
    // }
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