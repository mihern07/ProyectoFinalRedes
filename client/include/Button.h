#pragma once

#include <SDL2/SDL.h>
class Texture;
class Rectangle;

class Button
{
public:
    Button(int auxNum);
    ~Button();

    void render();
    void changeButton();

    Rectangle *getRect();
private:
    SDL_Rect dest;

    int numButton;
    Texture *buttonText;
    Rectangle *rect;
};