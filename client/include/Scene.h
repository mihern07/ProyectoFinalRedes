#pragma once

class Texture;
class Button;

class Scene
{
public:
    Scene();
    ~Scene();
    void initScene();
    void newScene();

    void update();
    // void changeDialog();

    void nextDialogue(int dialogue1, int dialogue2);

    void newDecision();

    void changePlayer1Image();
    void changePlayer2Image();

private:
    bool showButton;

    char player1;
    char player2;

    Texture *text1;
    Texture *text2;
    Texture *text3;

    Button *b1;
    Button *b2;
    Button *b3;
};