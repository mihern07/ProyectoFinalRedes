#include "Button.h"
#include <iostream>
#include "SDLUtils.h"
#include "Rectangle.h"

Button::Button(int auxNum)
{
    numButton = auxNum;
    buttonText = &sdlutils().msgs().at("button" + std::to_string(numButton));
    int width = sdlutils().width();
    int height = sdlutils().height();

    std::cout << "Button" + std::to_string(numButton);
    switch (numButton)
    {
    case 1:
        dest = SDL_Rect{width / 2 - (buttonText->width() / 2), height / 4, buttonText->width(), buttonText->height()};
        break;
    case 2:
        dest = SDL_Rect{width / 2 - (buttonText->width() / 2), height * 2 / 4, buttonText->width(), buttonText->height()};
        break;
    case 3:
        dest = SDL_Rect{width / 2 - (buttonText->width() / 2), height * 3 / 4, buttonText->width(), buttonText->height()};
        break;
    default:
        dest = SDL_Rect{width / 2 - (buttonText->width() / 2), height * 2 / 4, buttonText->width(), buttonText->height()};
        break;
    }

    rect = new Rectangle{dest.x,dest.y,dest.w,dest.h};
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
}

Rectangle* Button::getRect()
{
    return rect;
}