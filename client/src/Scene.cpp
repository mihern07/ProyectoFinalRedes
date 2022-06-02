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
    SDLUtils::init("Proyecto Redes", 800, 600,
                   "../resources/config/sdlutilsdemo.resources.json");

    // reference to the SDLUtils Singleton. You could use it as a pointer as well,
    // I just prefer to use . instead of ->, it is just a matter of taste, nothing
    // else!
    //
    // you can also use the inline method sdlutils() that simply returns the value
    // of *SDLUtils::instance() --- it is defined at the end of SDLUtils.h
    //
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

    auto &textLine1 = sdl.msgs().at("mainText0");
    auto &textLine2 = sdl.msgs().at("mainText1");
    auto &textLine3 = sdl.msgs().at("mainText3");

    text1 = &textLine1;
    text2 = &textLine2;
    text3 = &textLine3;

    //Constants
    auto winWidth = sdl.width();
    auto winHeight = sdl.height();

    SDL_Rect destDialogueBox = SDL_Rect{(winWidth - dialogBox.width() * 2) / 2, (winHeight - dialogBox.height() * 2), dialogBox.width() * 2, dialogBox.height() * 2};
    SDL_Rect destRancia = SDL_Rect{20, winHeight - (rancia.height() * 4) - dialogBox.height() * 2 + 12, rancia.width() * 4, rancia.height() * 4};
    SDL_Rect destDeprimida = SDL_Rect{40 + rancia.width() + deprimida.width() / 2, winHeight - (deprimida.height() * 4) - dialogBox.height() * 2 + 12, deprimida.width() * 4, deprimida.height() * 4};

    SDL_Rect destPija = SDL_Rect{winWidth - pijaFlip.width() * 4 - 40, winHeight - (pijaFlip.height() * 4) - dialogBox.height() * 2 + 12, pijaFlip.width() * 4, pijaFlip.height() * 4};

    SDL_Rect destLine1 = SDL_Rect{45, winHeight - dialogBox.height() - 65, textLine1.width(), textLine1.height()};
    SDL_Rect destLine2 = SDL_Rect{45, winHeight - dialogBox.height() - 65 + textLine1.height() + 10, textLine2.width(), textLine2.height()};
    SDL_Rect destLine3 = SDL_Rect{45, winHeight - dialogBox.height() - 65 + textLine1.height() + textLine2.height() + 10, textLine3.width(), textLine3.height()};

    // Button
    Rectangle *button = new Rectangle{destDialogueBox.x, destDialogueBox.y, destDialogueBox.w, destDialogueBox.h};
    Point *mousePosition = new Point{0, 0};

    b1 = new Button(1);
    b2 = new Button(2);
    b3 = new Button(3);

    // reference to the input handler (we could use a pointer, I just . rather than ->).
    // you can also use the inline method ih() that is defined in InputHandler.h
    auto &ih = *InputHandler::instance();

    Client::Init("127.0.0.1", "7777", this);

    while (!Client::InitGame())
    {
    }

    Client::SendGameReady();

    while (!Client::StartGame())
    {
    }

    // start the music in a loop
    // sdl.musics().at("beat").play();

    // a boolean to exit the loop
    bool exit_ = false;

    showButton = true;
    while (!exit_)
    {
        Uint32 startTime = sdl.currRealTime();

        // update the event handler
        ih.refresh();

        if (ih.mouseButtonDownEvent())
        {
            auto mouseAux = ih.getMousePos();
            mousePosition->x = mouseAux.first;
            mousePosition->y = mouseAux.second;

            if (showButton)
            {
                if (PointInRect(mousePosition, b1->getRect()))
                {
                    cout << "boton1\n";
                }
                else if (PointInRect(mousePosition, b2->getRect()))
                {
                    cout << "boton2\n";
                }
                else if (PointInRect(mousePosition, b3->getRect()))
                {
                    cout << "boton3\n";
                }
            }
            else if (PointInRect(mousePosition, button))
            {

                Client::sendNextDialogue();
                std::cout << "Odio Linux y odio a Poletti\n";
            }
        }

        // exit when you press ESCAPE
        if (ih.isKeyDown(SDLK_ESCAPE))
            exit_ = true;

        // clear screen
        sdl.clearRenderer();

        // render the SDLogo
        dialogBox.render(destDialogueBox);

        deprimida.render(destDeprimida);
        rancia.render(destRancia);
        pijaFlip.render(destPija);

        text1->render(destLine1);
        text2->render(destLine2);
        text3->render(destLine3);

        if (showButton)
        {
            b1->render();
            b2->render();
            b3->render();
            // cout << "renderizo cosas\n";
        }

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

// Cambia al siguiente dialogo
void Scene::nextDialogue(int dialogueNum1, int dialogueNum2)
{
    //DEBUG
    string aux = "mainText" + to_string(dialogueNum1);
    cout << aux << "\n";


    text1 = &sdlutils().msgs().at("mainText" + to_string(dialogueNum1));
    text2 = &sdlutils().msgs().at("mainText" + to_string(dialogueNum2));
}

void Scene::newDecision()
{
    b1->changeButton();
    b2->changeButton();
    b3->changeButton();
}