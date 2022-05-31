#include "Input.h"
#include "InputListener.h"
#include <SDL2/SDL_events.h>
#include <iostream>
#include <list>

#pragma region STATIC ATTRIBUTES

InputListener Input::_inputListener;

#pragma endregion

#pragma region SINGLETON

//Initilize input
void Input::Init()
{
   _inputListener.Init();
}

//Registers new input info
void Input::Tick()
{
    std::list<SDL_Event>eventList = _inputListener.GetInput();
    
    for(auto event : eventList)
    {
        if(event.type == SDL_KEYDOWN)
        {
             IsKeyDown(event);   
        }
        else if(event.type == SDL_KEYUP)
            IsKeyUp(event);
    }   
}

void Input::Release()
{
}

#pragma endregion

#pragma region KEY MANAGEMENT

//Set key to true if pressed
void Input::IsKeyDown(const SDL_Event & event)
{
    
    switch (event.key.keysym.sym)
    {
    //button keys
    default:

    break;
    }
}

//Set key to false if not pressed anymore
void Input::IsKeyUp(const SDL_Event & event)
{
    switch (event.key.keysym.sym)
    {
    default:
        break;
    }
}

#pragma endregion