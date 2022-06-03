#include "Scene.h"

#include <SDL2/SDL.h>

#include "SDLUtils.h"
#include "macros.h"
#include "InputHandler.h"

#include "Client.h"

#include "Rectangle.h"
#include "Button.h"

using namespace std;

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::initScene()
{

    // Initialise the SDLGame singleton
    SDLUtils::init("Quiz SUPER TRENDY (Pulsa ESC para salir)", 800, 600,
                   "../resources/config/sdlutilsdemo.resources.json");

    // reference to the SDLUtils Singleton.
    auto &sdl = *SDLUtils::instance();

    // show the cursor
    sdl.showCursor();

    // store the 'renderer' in a local variable, just for convenience
    SDL_Renderer *renderer = sdl.renderer();

    // Dialog Box
    auto &dialogBox = sdl.images().at("textBox");

    auto &rancia = sdl.images().at("rancia");
    auto &pijaFlip = sdl.images().at("pijaFlip");
    auto &deprimida = sdl.images().at("deprimida");
    
    auto &canInputText = sdl.msgs().at("textInput");

    auto &textLine1 = sdl.msgs().at("mainText0");
    auto &textLine2 = sdl.msgs().at("mainText1");

    text1 = &textLine1;
    text2 = &textLine2;

    // Constants
    auto winWidth = sdl.width();
    auto winHeight = sdl.height();

    SDL_Rect destDialogueBox = SDL_Rect{(winWidth - dialogBox.width() * 2) / 2, (winHeight - dialogBox.height() * 2), dialogBox.width() * 2, dialogBox.height() * 2};
    SDL_Rect destRancia = SDL_Rect{20, winHeight - (rancia.height() * 4) - dialogBox.height() * 2 + 12, rancia.width() * 4, rancia.height() * 4};
    SDL_Rect destDeprimida = SDL_Rect{40 + rancia.width() + deprimida.width() / 2, winHeight - (deprimida.height() * 4) - dialogBox.height() * 2 + 12, deprimida.width() * 4, deprimida.height() * 4};

    SDL_Rect destPija = SDL_Rect{winWidth - pijaFlip.width() * 4 - 40, winHeight - (pijaFlip.height() * 4) - dialogBox.height() * 2 + 12, pijaFlip.width() * 4, pijaFlip.height() * 4};

    destLine1 = SDL_Rect{45, winHeight - dialogBox.height() - 40, textLine1.width(), textLine1.height()};
    destLine2 = SDL_Rect{45, winHeight - dialogBox.height() - 40 + textLine1.height() + 10, textLine2.width(), textLine2.height()};

    // Button
    Rectangle *button = new Rectangle{destDialogueBox.x, destDialogueBox.y, destDialogueBox.w, destDialogueBox.h};
    Point *mousePosition = new Point{0, 0};

    b1 = new Button(1);
    b2 = new Button(2);
    b3 = new Button(3);

    // reference to the input handler
    auto &ih = *InputHandler::instance();

    Client::Init("127.0.0.1", "7777", this);

    // a boolean to exit the loop
    bool exit_ = false;

    sdl.clearRenderer();

    sdl.presentRenderer();

    while (!Client::InitGame() && !exit_)
    {
        ih.refresh();

        if (ih.isKeyDown(SDLK_ESCAPE))
            exit_ = true;
    }

    if (!exit_)
    {
        Client::SendGameReady();

        while (!Client::StartGame() && !exit_)
        {
            ih.refresh();

            if (ih.isKeyDown(SDLK_ESCAPE))
                exit_ = true;
        }
    }

    // start the music in a loop
    sdl.musics().at("beat").play();

    showButton = false;
    while (!exit_)
    {
        Uint32 startTime = sdl.currRealTime();

        // update the event handler
        ih.refresh();

        // button checking
        if (ih.mouseButtonDownEvent())
        {
            auto mouseAux = ih.getMousePos();
            mousePosition->x = mouseAux.first;
            mousePosition->y = mouseAux.second;

            if (showButton && canInput)
            {
                if (PointInRect(mousePosition, b1->getRect()))
                {
                    Client::sendDecisionChosen(1);
                }
                else if (PointInRect(mousePosition, b2->getRect()))
                {
                    Client::sendDecisionChosen(2);
                }
                else if (PointInRect(mousePosition, b3->getRect()))
                {
                    Client::sendDecisionChosen(3);
                }
            }
            else if (canInput && PointInRect(mousePosition, button))
            {
                Client::sendNextDialogue();
            }
        }

        // exit when you press ESCAPE
        if (ih.isKeyDown(SDLK_ESCAPE))
            exit_ = true;

        // clear screen
        sdl.clearRenderer();

        // render images
        dialogBox.render(destDialogueBox);

        deprimida.render(destDeprimida);
        rancia.render(destRancia);
        pijaFlip.render(destPija);

        text1->render(destLine1);
        text2->render(destLine2);

        if (showButton)
        {
            b1->render();
            b2->render();
            b3->render();
        }

        if (canInput)
            canInputText.render(0, 0);

        // present new frame
        sdl.presentRenderer();

        Uint32 frameTime = sdl.currRealTime() - startTime;

        if (frameTime < 20)
            SDL_Delay(20 - frameTime);
    }

    delete mousePosition;
    delete button;

    // Release client resources
    Client::Release();

    // stop the music
    Music::haltMusic();
}

void Scene::update()
{
    // a boolean to exit the loop
    bool exit_ = false;
}

// Changes the main dialogue
void Scene::nextDialogue(int dialogueNum1, int dialogueNum2, bool input)
{
    canInput = input;
    // DEBUG
    string aux = "mainText" + to_string(dialogueNum1);
    cout << aux << "\n";

    text1 = &sdlutils().msgs().at("mainText" + to_string(dialogueNum1));
    text2 = &sdlutils().msgs().at("mainText" + to_string(dialogueNum2));
    destLine1.w = text1->width();
    destLine1.h = text1->height();
    destLine2.w = text2->width();
    destLine2.h = text2->height();
    showButton = false;
}

// Shows buttons and changes their content
void Scene::newDecision(int button1, int button2, int button3, bool input)
{
    canInput = input;

    showButton = true;
    b1->changeButton(button1);
    b2->changeButton(button2);
    b3->changeButton(button3);
}

void Scene::setInput(bool aux)
{
    canInput = aux;
}