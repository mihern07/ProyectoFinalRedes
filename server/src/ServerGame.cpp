#include <server/include/ServerGame.h>
// #include "InputInfo.h"
#include "Server.h"
#include "Message.h"

#include <iostream>

ServerGame::ServerGame(Server* server) : _server(server)
{

}

//Initializes game (tilemap, players, fruit)
void ServerGame::Init()
{
    InitPlayers();
}

//Updates active GameObjects
void ServerGame::Update()
{
    // for(auto* go : _gameObjects)
    //     go->Update();
}

// Sends message to all clients
void ServerGame::SendToClients(Message msg)
{
    _server->SendToClients(msg);
}

ServerGame::~ServerGame()
{
    //delete GameObjects allocated memory
    // for (auto go : _gameObjects)
    //     delete go;

    // _gameObjects.clear();
}