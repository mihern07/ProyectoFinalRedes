#include "Scene.h"

#include <SDL2/SDL.h>

#include "SDLUtils.h"
#include "macros.h"
#include "InputHandler.h"

#include "Client.h"

#include "Rectangle.h"

using namespace std;

Scene::Scene()
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

    auto &textLine1 = sdl.msgs().at("mainText2");
    auto &textLine2 = sdl.msgs().at("mainText2");
    // Texture pressAnyKey(renderer, "Press any key to exit",
    //                     sdl.fonts().at("ZACHARY24"), build_sdlcolor(0x112233ff),
    //                     build_sdlcolor(0xffffffff));

    // some coordinates
    auto winWidth = sdl.width();
    auto winHeight = sdl.height();

    SDL_Rect destDialogBox = SDL_Rect{(winWidth - dialogBox.width() * 2) / 2, (winHeight - dialogBox.height() * 2), dialogBox.width() * 2, dialogBox.height() * 2};
    SDL_Rect destRancia = SDL_Rect{20, winHeight - (rancia.height() * 4) - dialogBox.height() * 2 + 12, rancia.width() * 4, rancia.height() * 4};
    SDL_Rect destDeprimida = SDL_Rect{40 + rancia.width() + deprimida.width() / 2, winHeight - (deprimida.height() * 4) - dialogBox.height() * 2 + 12, deprimida.width() * 4, deprimida.height() * 4};

    SDL_Rect destPija = SDL_Rect{winWidth - pijaFlip.width() * 4 - 40, winHeight - (pijaFlip.height() * 4) - dialogBox.height() * 2 + 12, pijaFlip.width() * 4, pijaFlip.height() * 4};

    SDL_Rect destLine1 = SDL_Rect{45, winHeight - dialogBox.height() - 65, textLine1.width(), textLine1.height()};
    SDL_Rect destLine2 = SDL_Rect{45, winHeight - dialogBox.height() - 65 + textLine1.height() + 10, textLine1.width(), textLine1.height()};
    SDL_Rect destLine3 = SDL_Rect{45, winHeight - dialogBox.height() - 65 + textLine1.height() + textLine2.height() + 10, textLine1.width(), textLine1.height()};

    // Button
    Rectangle *button = new Rectangle{destDialogBox.x, destDialogBox.y, destDialogBox.w, destDialogBox.h};
    Point *mousePosition = new Point{0, 0};

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
            if (PointInRect(mousePosition, button))
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

        // render Hello SDL
        // helloSDL.render(x1, y1);
        // if (x1 + helloSDL.width() > winWidth)
        // 	helloSDL.render(x1 - winWidth, y1);
        // x1 = (x1 + 5) % winWidth;

        // render the SDLogo
        dialogBox.render(destDialogBox);

        deprimida.render(destDeprimida);
        rancia.render(destRancia);
        pijaFlip.render(destPija);

        textLine1.render(destLine1);
        textLine2.render(destLine2);
        textLine2.render(destLine3);

        // render Press Any Key
        // pressAnyKey.render(x0, y0);

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

void Scene::newScene()
{
}

void Scene::update()
{

    // a boolean to exit the loop
    bool exit_ = false;
}

// Change to the next dialog
void Scene::nextDialogue(std::string dialogue1, std::string dialogue2)
{
}

void Scene::newDecision()
{
}

// void Scene::changePlayer1Image(Texture newTexture)
// {
//     player1Image = newTexture;
// }

// void Scene::changePlayer2Image(Texture newTexture)
// {
//     player2Image = newTexture;
// }