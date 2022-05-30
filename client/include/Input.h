#ifndef _H_Input_H_
#define _H_Input_H_

class InputListener;
union SDL_Event;

class Input 
{
public:

    /**
     * Initilize input
     */
    static void Init();

    /**
     * Registers new input info
     */
    static void Tick();

    /**
     * Releases input resources
     */
    static void Release();

private:

    /**
     * Set key to true if pressed
     * @param event SDL event with key info
     */
    static void IsKeyDown(const SDL_Event & event);

    /**
     * Set key to false if not pressed anymore
     * @param event SDL event with key info
     */
    static void IsKeyUp(const SDL_Event & event);

    static InputListener _inputListener;
};
#endif