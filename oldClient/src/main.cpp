#include <iostream>
#include "Platform.h"
#include "Renderer.h"
#include "Input.h"
#include "ClientGame.h"
#include <time.h>
#include <SDL2/SDL.h>
#include "Client.h"

#include "Scene.h"

int main() 
{
    std::cout << "Initializing...\n";

    //Initialize SDL 
    if(!Platform::Init())
        return 1;
    if(!Renderer::Init())
        return 1;
    Input::Init();

    ClientGame game; 
    Client::Init("127.0.0.1", "7777");

    bool applicationClosed = false;
    
    while(!Client::InitGame() && !applicationClosed) 
    {    
        if(!Platform::Tick()) 
            applicationClosed = true;
    }

    if(!applicationClosed)
    {
        game.Init(); //initialize GameObjects

        std::cout << "Waiting for other players\n";

        Client::SendGameReady(); //game is ready 

        while(!Client::StartGame() && !applicationClosed) //wait until server is ready
        {
            if(!Platform::Tick()) 
                applicationClosed = true;
        }

        std::cout << "Start game\n";
        
        

        //game loop
        while(!applicationClosed && Platform::Tick())
        {
            Input::Tick(); //register input
    
            // Client::SendInput(Input::GetInputInfo());
    
            //Render
            Renderer::Clear(0); //clears last frame
            game.Render();  //render new frame
            Renderer::Present(); //display the new frame buffer  
            Platform::Delay(125); 
        }
    }

    //Release client resources
    Client::Release();

    //Release SDL
    Input::Release();   
    Renderer::Release();
    Platform::Release();
        
    std::cout << "Game closed\n";

    return 0;
}