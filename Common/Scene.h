#pragma once

class Scene
{
public:
    void newScene();

    void update();
    // void changeDialog();

    void nextDialog();

    void newDecision();


    void changePlayer1Image();
    void changePlayer2Image();

private:
    char player1;
    char player2;

    // Texture player1Image;
    // Texture player2Image;

};