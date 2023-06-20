// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL.h>
#include <string>
#include <map>

class SDLUtils{


public:

	// we abstract away the actual data structure we use for
	// tables. All we assume is that is has the following
	// methods
	//
	//   emplace(key,value)
	//   at(key)
	//   clear()
	//

	

	static bool Init();

	static SDLUtils& GetInstance();


	virtual ~SDLUtils();

	// cannot copy/move
	SDLUtils(SDLUtils&) = delete;
	SDLUtils(SDLUtils&&) = delete;
	SDLUtils& operator=(SDLUtils&) = delete;
	SDLUtils& operator=(SDLUtils&&) = delete;

	// access to the underlying SDL_Window -- in principle not needed
	inline SDL_Window* getWindow() {
		return window_;
	}

	// access to the underlying SDL_Renderer -- needed when creating textures
	// other than those initialized in this class
	inline SDL_Renderer* getRenderer() {
		return renderer_;
	}

	// clear the renderer with a given SDL_Color
	inline void clearRenderer(SDL_Color bg) {
		SDL_SetRenderDrawColor(renderer_, bg.r, bg.g, bg.b, bg.a);
		SDL_RenderClear(renderer_);
	}

	// present the current content of the renderer
	inline void presentRenderer() {
		SDL_RenderPresent(renderer_);
	}

	// the window's width
	inline int width() {
		return width_;
	}

	// the window's height
	inline int height() {
		return height_;
	}

	// toggle to full-screen/window mode
	inline void toggleFullScreen() {
		auto flags = SDL_GetWindowFlags(window_);
		if (flags & SDL_WINDOW_FULLSCREEN) {
			SDL_SetWindowFullscreen(window_, 0);
		} else {
			SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
		}
	}

	// show the cursor when mouse is over the window
	inline void showCursor() {
		SDL_ShowCursor(1);
	}

	// hide the cursor when mouse is over the window
	inline void hideCursor() {
		SDL_ShowCursor(0);
	}

	// Access to real time
	inline Uint32 currRealTime() const {
		return SDL_GetTicks();
	}

private:

	static SDLUtils* instance;


	SDLUtils();
	SDLUtils(std::string windowTitle, int width, int height);
	SDLUtils(std::string windowTitle, int width, int height,
			std::string filename);

	void initWindow();
	void closeWindow();
	void initSDLExtensions(); // initialize resources (fonts, textures, audio, etc.)
	void closeSDLExtensions(); // free resources the
	void loadReasources(std::string filename); // load resources from the json file

	std::string windowTitle_; // window title
	int width_; // window width
	int height_; // window height

	SDL_Window *window_; // the window
	SDL_Renderer *renderer_; // the renderer
};
