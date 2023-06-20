// This file is part of the course TPV2@UCM - Samir Genaim

#include "sdl_utils.h"
#include <cassert>

SDLUtils::SDLUtils() :
		SDLUtils("SDL Demo", 600, 400) {
}

SDLUtils::SDLUtils(std::string windowTitle, int width, int height) :
		windowTitle_(windowTitle), //
		width_(width), //
		height_(height) {

	initWindow();
	initSDLExtensions();
}

SDLUtils::SDLUtils(std::string windowTitle, int width, int height,
		std::string filename) :
		SDLUtils(windowTitle, width, height) {
	loadReasources(filename);
}

SDLUtils& SDLUtils::GetInstance()
{
	return *SDLUtils::instance;
}

SDLUtils::~SDLUtils() {
	closeSDLExtensions();
	closeWindow();
}

void SDLUtils::initWindow() {
	// initialise SDL
	int sdlInit_ret = SDL_Init(SDL_INIT_EVERYTHING);
	assert(sdlInit_ret == 0);

	// Create window
	window_ = SDL_CreateWindow(windowTitle_.c_str(),
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, width_, height_, SDL_WINDOW_SHOWN);
	assert(window_ != nullptr);

	// Create the renderer
	renderer_ = SDL_CreateRenderer(window_, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	assert(renderer_ != nullptr);

	// hide cursor by default
	hideCursor();

}

void SDLUtils::closeWindow() {

	// destroy renderer and window
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);

	SDL_Quit(); // quit SDL
}

void SDLUtils::initSDLExtensions() {

	//// initialize SDL_ttf
	//int ttfInit_r = TTF_Init();
	//assert(ttfInit_r == 0);

	//// initialize SDL_image
	//int imgInit_ret = IMG_Init(
	//		IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
	//assert(imgInit_ret != 0);

	//// initialize SDL_Mixer
	//int mixOpenAudio = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	//assert(mixOpenAudio == 0);
	//int mixInit_ret = Mix_Init(
	//		MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
	//assert(mixInit_ret != 0);
	//SoundEffect::setNumberofChannels(8); // we start with 8 channels

}

void SDLUtils::closeSDLExtensions() {

	//musics_.clear();
	//sounds_.clear();
	//msgs_.clear();
	//images_.clear();
	//fonts_.clear();

	//Mix_Quit(); // quit SDL_mixer
	//IMG_Quit(); // quit SDL_image
	//TTF_Quit(); // quit SDL_ttf
}

