#include "ClientGame.h"
#include "Renderer.h"
#include <iostream>
#include <Platform.h>
#include "Client.h"

ClientGame::ClientGame(){}

//Initializes GameObjects
void ClientGame::Init()
{    
}

//Renders active GameObjects
void ClientGame::Render()
{   
    // for(auto* go : _gameObjects)
    //     go->Render();
}

ClientGame::~ClientGame()
{
   //delete GameObjects allocated memory
    // for (auto go : _gameObjects)
    //     delete go;

    // _gameObjects.clear();
}