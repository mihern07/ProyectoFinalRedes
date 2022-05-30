#ifndef _H_Platform_H_
#define _H_Platform_H_
#include <list>

class SDL_Window;
class InputListener;
union SDL_Event;


class Platform 
{

public:

    /**
     * Creates the SDL window
     */
    static bool Init();

    /**
     * Registers user input and sends it to input listeners
     * @return false if application is closed, if SDL_Quit
     */
    static bool Tick();

    /**
     * Releases the resources used by SDL
     */
    static void Release(); 

    /**
     * Waits for n milliseconds
     * @param ms amount of milliseconds to wait
     */
    static void Delay(int ms);

    /**
     * Add listener to list
     * @param listener to add
     */
    static void AddListener(InputListener* listener);

    /**
     * Removes specific listener from list
     * @param listener to remove
     */
    static void RemoveListener(InputListener* listener);

    /**
     * Sends the new input info to the input listeners
     * @param e SDL_Event with the input info
     */
    static void SendMessage(const SDL_Event& e);

    /**
     * Returns sdl window
     */
    inline static SDL_Window* GetWindow() { return _pWindow; };


private:

    //Screen width & height
    static const int SCREEN_WIDTH;
    static const int SCREEN_HEIGHT; 

    static SDL_Window* _pWindow; 

    static std::list<InputListener*> _listeners;
};
#endif