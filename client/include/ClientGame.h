#ifndef _H_ClientGame_H_
#define _H_ClientGame_H_
#include <vector>

class ClientGame 
{
public:
    ClientGame();
    ~ClientGame();

    /**
     * Initializes GameObjects
     */
    void Init();

    /**
     * Renders GameObjects
     */
    void Render();
};
#endif