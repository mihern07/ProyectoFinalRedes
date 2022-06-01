#pragma once

class Texture;

class Scene
{
public:
    Scene();
    void initScene();
    void newScene();

    void update();
    // void changeDialog();

    void nextDialogue(int dialogue1,int dialogue2);

    void newDecision();

    void changePlayer1Image();
    void changePlayer2Image();

private:
    char player1;
    char player2;

    Texture* text1;
    Texture* text2;
};