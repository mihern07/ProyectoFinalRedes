#ifndef _H_ClientGame_H_
#define _H_ClientGame_H_
#include <vector>

#include "Texture.h"

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

private:
    int _xPos; // position in tilemap
    int _yPos;
    int _size; // size in pixels


    Texture *player1Texture; // image texture
    Texture *player2Texture; // image texture
    int width;
    int height;

    const char *path = "resources/images/rancia.png";
};
#endif