#include "InputListener.h"
#include "Platform.h"
#include <SDL2/SDL_events.h>
#include <iostream>

InputListener::InputListener()
{
   
}

//Adds the input listener to Platform
void InputListener::Init()
{
    Platform::AddListener(this);
}

//Removes listener from pltform list
void InputListener::Release()
{
    Platform::RemoveListener(this);
}

InputListener::~InputListener()
{
    _events.clear();
}

//Saves the input event on event list
void InputListener::OnEvent(const SDL_Event& event)
{
        _events.push_back(event);
}

//Returns the current input information
std::list<SDL_Event> InputListener::GetInput()
{
    std::list<SDL_Event> auxList(_events);
	_events.clear();

	return auxList;
}