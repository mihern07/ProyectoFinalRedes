#ifndef _H_Renderer_H_
#define _H_Renderer_H_

class SDL_Renderer;
class SDL_Texture;

class Renderer 
{
public:

    /**
     * Initialises renderer
     * @return true if initialization failed
     */
    static bool Init();

    /**
     * Clears the window by painting it all with one color
     * @param color Color to paint the window
     */
    static void Clear(int color);

    /**
     * Updates the window to the current display buffer
     */
    static void Present();

    /**
     * Releases SDL resources
     */
    static void Release();

    /**
     * @return screen width
     */
    static inline int GetScreenWidth(){ return _screenWidth; };

    /**
     * @return screen height
     */
    static inline int GetScreenHeight(){ return _screenHeight; };

    /**
     * @return SDL renderer
     */
    static inline SDL_Renderer* GetRenderer(){ return _pRenderer; };

    /**
     * Loads an image texture
     * @return image texture 
     */
    // static SDL_Texture* LoadImage(const char* path, int* width, int* height);

private:

    static SDL_Renderer* _pRenderer;
    static int _screenWidth;
    static int _screenHeight;
};
#endif