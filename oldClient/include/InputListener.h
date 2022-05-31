#ifndef _H_InputListener_H_
#define _H_InputListener_H_
#include <list>

union SDL_Event;

class InputListener 
{
public:

    InputListener();
    ~InputListener();

    /**
     * Adds the input listener to Platform
     */
    void Init();

    /**
     * Removes listener from platform list
     * prevents double free
     */
    void Release();

    /**
     * Saves the input event
     * @param event input event stored in list
     */
    void OnEvent(const SDL_Event& event);

    /**
     * Returns the current input information
     * @return SDL_Event input list
     */
    std::list<SDL_Event> GetInput();

private:

    std::list<SDL_Event> _events;

};
#endif