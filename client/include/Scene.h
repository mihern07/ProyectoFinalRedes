#pragma once

#include "SDL2/SDL.h"

class Texture;
class Button;
class Scene
{
public:
    Scene();
    ~Scene();
    void initScene();

    void update();
    // void changeDialog();

    void nextDialogue(int dialogue1, int dialogue2, bool input);

    void newDecision(int button1, int button2, int button3, bool input);

    void setInput(bool aux);

private:
    bool canInput;
    bool showButton;

    Texture *text1;
    Texture *text2;

    SDL_Rect destLine1;
    SDL_Rect destLine2;

    Button *b1;
    Button *b2;
    Button *b3;
};