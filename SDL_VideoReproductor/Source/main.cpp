#include <SDL.h>

#include <iostream>

extern "C" {

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>

}

int main(int argc, char* argv[]) {

	// Inicializar el formato de FFmpeg
	avformat_network_init();

	// Obtener la versión de FFmpeg
	const char* ffmpegVersion = av_version_info();

	// Imprimir la versión de FFmpeg
	std::cout << "Hello, FFmpeg!" << std::endl;
	std::cout << "FFmpeg version: " << ffmpegVersion << std::endl;


	// Inicializar SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL no pudo inicializarse. Error: %s\n", SDL_GetError());
		return 1;
	}

	// Crear una ventana
	SDL_Window* window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("No se pudo crear la ventana. Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	// Crear un renderer para la ventana
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL) {
		printf("No se pudo crear el renderer. Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	// Color de fondo (azul claro)
	SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255); // RGB: (173, 216, 230)

	// Limpiar la ventana con el color de fondo
	SDL_RenderClear(renderer);

	// Actualizar la ventana
	SDL_RenderPresent(renderer);

	// Esperar 3 segundos
	SDL_Delay(3000);

	// Liberar recursos y salir
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
