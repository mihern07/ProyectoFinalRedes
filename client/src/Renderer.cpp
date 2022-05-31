#include "Renderer.h"
#include "Platform.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#pragma region  STATIC ATTRIBUTES

SDL_Renderer* Renderer::_pRenderer = nullptr;
int Renderer::_screenWidth = 0;
int Renderer::_screenHeight = 0;

#pragma endregion

//Initialises renderer
bool  Renderer::Init()
{
    SDL_Window* pWindow = Platform::GetWindow();
    _pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

    if(_pRenderer == nullptr)
    {
        std::cout << "Renderer could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
        return false;
    }
    else
    {
        SDL_SetRenderDrawColor(_pRenderer, 0, 0, 0, 255); //Background color = black
        SDL_GetWindowSize(pWindow, &_screenWidth, &_screenHeight);
        return true;
    }
}

// Updates the window to the current display buffer
void Renderer::Present()
{
    SDL_RenderPresent(_pRenderer);
}

//Clears the window by painting it all with one color
void Renderer::Clear(int color)
{
    SDL_SetRenderDrawColor(_pRenderer, 
    (color >> 8 * 3) & 0xFF, (color >> 8* 2) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);

    SDL_RenderClear(_pRenderer);
}

//Loads and returns an image texture
// SDL_Texture* Renderer::LoadImage(const char* path, int* width, int* height)
// {
//     SDL_Surface* image = SDL_LoadBMP(path); //load file
    
//     if(image == nullptr)
//         std::cout << "Unable to load image! \nSDL_Error: " << SDL_GetError() << '\n';
    
//     SDL_Texture* texture = SDL_CreateTextureFromSurface(_pRenderer, image); //create texture

//     if(texture == nullptr)
//         std::cout << "Unable to create texture! \nSDL_Error: " << SDL_GetError() << '\n';


//     //set surface width & height
//     *width = image->w;
//     *height = image->h;

//     SDL_FreeSurface(image); //free temp surface
//     image = nullptr;

//     return texture;
// }

//Release SDL renderer resources
void Renderer::Release()
{
    SDL_DestroyRenderer(_pRenderer);
    _pRenderer = nullptr;
}