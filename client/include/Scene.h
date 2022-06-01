#pragma once
#include <string>

class Scene
{
public:
    Scene();
    void initScene();
    void newScene();

    void update();
    // void changeDialog();

    void nextDialog(std::string dialogue1, std::string dialogue2);

    void newDecision();

    void changePlayer1Image();
    void changePlayer2Image();

private:
    char player1;
    char player2;

    // Texture player1Image;
    // Texture player2Image;
};