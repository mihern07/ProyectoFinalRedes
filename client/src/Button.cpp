#include "Button.h"
#include <iostream>
#include "SDLUtils.h"
#include "Rectangle.h"

Button::Button(int auxNum)
{
    numButton = auxNum;
    buttonText = &sdlutils().msgs().at("mainText" + std::to_string(numButton));
    int width = sdlutils().width();
    int height = sdlutils().height();

    switch (numButton)
    {
    case 1:
        dest = SDL_Rect{width / 2 - (buttonText->width()/5), height / 4 - 30, buttonText->width(), buttonText->height()};
        break;
    case 2:
        dest = SDL_Rect{width / 2 - (buttonText->width()/5), height / 4 + 90, buttonText->width(), buttonText->height()};
        break;
    case 3:
        dest = SDL_Rect{width / 2 - (buttonText->width()/5), height / 4 + 210, buttonText->width(), buttonText->height()};
        break;
    default:
        dest = SDL_Rect{width / 2 - (buttonText->width()/5), height / 4 + 210, buttonText->width(), buttonText->height()};
        break;
    }

    rect = new Rectangle{dest.x, dest.y, dest.w, dest.h};
}

Button::~Button()
{
    delete buttonText;
    delete rect;
}

void Button::render()
{
    buttonText->render(dest);
}

void Button::changeButton(int buttonId)
{
    numButton = buttonId;
    buttonText = &sdlutils().msgs().at("mainText" + std::to_string(numButton));
    dest.w = buttonText->width();
    dest.h = buttonText->height();
}

Rectangle *Button::getRect()
{
    return rect;
}