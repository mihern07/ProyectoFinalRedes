// // This file is part of the course TPV2@UCM - Samir Genaim

// #include <SDL2/SDL.h>

// #include "sdlutils_demo.h"

// #include "InputHandler.h"
// #include "macros.h"
// #include "SDLUtils.h"

// #include "Client.h"

// using namespace std;

// void sdlutils_basic_demo()
// {

// 	// Initialise the SDLGame singleton
// 	SDLUtils::init("SDLGame Demo!", 800, 600,
// 				   "../resources/config/sdlutilsdemo.resources.json");

// 	// reference to the SDLUtils Singleton. You could use it as a pointer as well,
// 	// I just prefer to use . instead of ->, it is just a matter of taste, nothing
// 	// else!
// 	//
// 	// you can also use the inline method sdlutils() that simply returns the value
// 	// of *SDLUtils::instance() --- it is defined at the end of SDLUtils.h
// 	//
// 	auto &sdl = *SDLUtils::instance();

// 	// show the cursor
// 	sdl.showCursor();

// 	// store the 'renderer' in a local variable, just for convenience
// 	SDL_Renderer *renderer = sdl.renderer();

// 	// Dialog Box
// 	auto &dialogBox = sdl.images().at("textBox");

// 	auto &rancia = sdl.images().at("rancia");
// 	auto &pijaFlip = sdl.images().at("pijaFlip");
// 	auto &maloMaloso = sdl.images().at("maloMaloso");

// 	auto &helloSDL = sdl.msgs().at("mainText2");
// 	Texture pressAnyKey(renderer, "Press any key to exit",
// 						sdl.fonts().at("ARIAL24"), build_sdlcolor(0x112233ff),
// 						build_sdlcolor(0xffffffff));

// 	// some coordinates
// 	auto winWidth = sdl.width();
// 	auto winHeight = sdl.height();
// 	auto x0 = (winWidth - pressAnyKey.width()) / 2;
// 	auto y0 = (winHeight - pressAnyKey.height()) / 2;
// 	auto x1 = 0;
// 	auto y1 = y0 - 4 * pressAnyKey.height();

// 	SDL_Rect destDialogBox = SDL_Rect{(winWidth - dialogBox.width() * 2) / 2, (winHeight - dialogBox.height() * 2), dialogBox.width() * 2, dialogBox.height() * 2};
// 	SDL_Rect destRancia = SDL_Rect{20, winHeight - (rancia.height() * 4) - dialogBox.height() * 2 + 12, rancia.width() * 4, rancia.height() * 4};
// 	SDL_Rect destMaloMaloso = SDL_Rect{20 + rancia.width() + maloMaloso.width()/2, winHeight - (maloMaloso.height() * 4) - dialogBox.height() * 2 + 12, maloMaloso.width() * 4, maloMaloso.height() * 4};

// 	SDL_Rect destPija = SDL_Rect{winWidth - pijaFlip.width() * 4 - 40, winHeight - (pijaFlip.height() * 4) - dialogBox.height() * 2 + 12, pijaFlip.width() * 4, pijaFlip.height() * 4};



// 	// reference to the input handler (we could use a pointer, I just . rather than ->).
// 	// you can also use the inline method ih() that is defined in InputHandler.h
// 	auto &ih = *InputHandler::instance();

// 	Client::Init("127.0.0.1", "7777");

// 	while (!Client::InitGame())
// 	{
// 	}

// 	Client::SendGameReady();

// 	while (!Client::StartGame())
// 	{
// 	}

// 	// start the music in a loop
// 	// sdl.musics().at("beat").play();

// 	// a boolean to exit the loop
// 	bool exit_ = false;

// 	while (!exit_)
// 	{
// 		Uint32 startTime = sdl.currRealTime();

// 		// update the event handler
// 		ih.refresh();

// 		// exit when any key is down
// 		if (ih.keyDownEvent())
// 			exit_ = true;

// 		// clear screen
// 		sdl.clearRenderer();

// 		// render Hello SDL
// 		// helloSDL.render(x1, y1);
// 		// if (x1 + helloSDL.width() > winWidth)
// 		// 	helloSDL.render(x1 - winWidth, y1);
// 		// x1 = (x1 + 5) % winWidth;

// 		// render Press Any Key
// 		pressAnyKey.render(x0, y0);

// 		// render the SDLogo
// 		dialogBox.render(destDialogBox);

// 		maloMaloso.render(destMaloMaloso);
// 		rancia.render(destRancia);
// 		pijaFlip.render(destPija);

// 		// present new frame
// 		sdl.presentRenderer();

// 		Uint32 frameTime = sdl.currRealTime() - startTime;

// 		if (frameTime < 20)
// 			SDL_Delay(20 - frameTime);
// 	}

// 	// Release client resources
// 	Client::Release();

// 	// stop the music
// 	Music::haltMusic();
// }
