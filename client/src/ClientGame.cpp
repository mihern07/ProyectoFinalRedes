#include "ClientGame.h"
#include "Renderer.h"
#include <iostream>
#include <Platform.h>
#include "Client.h"

ClientGame::ClientGame() {}

// Initializes GameObjects
void ClientGame::Init()
{
    // _srcRect = new SDL_Rect { 0,0,1,1};
    // player1Texture = new Texture(Renderer::GetRenderer(),path);

    // player1Texture = Renderer::LoadImage(path, &width, &height); // load texture
    // _destRectP1 = new SDL_Rect{0, 0, width, height};              // source texture rect
}

// Renders active GameObjects
void ClientGame::Render()
{
    // player1Texture->render(0,0);
    // SDL_RenderCopy(Renderer::GetRenderer(), player1Texture, _srcRect, _destRectP1);
}

ClientGame::~ClientGame()
{
    // delete GameObjects allocated memory
    //  for (auto go : _gameObjects)
    //      delete go;

    // _gameObjects.clear();
}
