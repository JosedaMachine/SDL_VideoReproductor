#pragma once

#include "../ecs/Component.h"
#include <string>
#include <queue>
#include <deque>
#include "SDL.h"
#include <iostream>
#include "../game/App.h"
#include "../sdlutils/SDLUtils.h"

//Librerias de ffmpeg
extern "C" {
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h>
	#include <libavutil/imgutils.h>
	#include <libavcodec/avcodec.h>
}

struct Video {

	Video() {
		filename = "";
		timePerFrame = 0;
		videoIndex = 0;
	}

	~Video() {
		int m = 0;
	};
	//Valores para leer los frames del video
	AVFormatContext* pFormatCtx = nullptr;
	AVCodecContext* pCodecCtx = nullptr;
	AVCodec* pCodec = nullptr;
	AVFrame* pFrame = nullptr, * pFrameYUV = nullptr;
	unsigned char* out_buffer = nullptr;
	AVPacket* packet = nullptr;
	struct SwsContext* img_convert_ctx = nullptr;
	//Controlar si el video ha acabado
	int done = 0;
	bool loop = false;
	int videoIndex;
	const char* filename;
	Uint32 timePerFrame;

	SDL_Texture* actTexture(){
		return SDL_CreateTexture(sdlutils().renderer(), SDL_PIXELFORMAT_IYUV,
			SDL_TEXTUREACCESS_STREAMING, pCodecCtx->width, pCodecCtx->height);
	}
};

class VideoPlayer : public Component
{
public:
	VideoPlayer(std::deque<std::pair<const char*, std::pair<bool, int>>>& file, const Vector2D& size = Vector2D(App::camera.w, App::camera.h));
	~VideoPlayer();

	void init() override;
	void update() override;
	void render() override;
	
	/// <summary>
	/// Devuelve el numero de elementos de la cola
	/// </summary>
	/// <param name="video_"></param>
	/// <returns></returns>
	int queueSize() { return queueVideos.size(); }

	int createVideo(Video& video_);
	/// <summary>
	/// Crea los videos con todos sus atributos para ser renderizado
	/// </summary>
	/// <param name="files">cola de videos</param>
	void prepareVideos(std::deque<std::pair<const char*, std::pair<bool, int>>>& files);

	/// <summary>
	/// AÒade un nuevo video a la cola
	/// </summary>
	/// <param name="file"></param>
	/// <param name="loop">: si se reproduce en loop</param>
	/// <param name="frameRate">: frames per Second (Varia debido a los FPS del juego)</param>
	void queueVideo(const char* file, bool loop, int frameRate);

	/// <summary>
	/// Quita un video de la cola, en caso de haber m·s de uno
	/// </summary>
	void popVideo();

	/// <summary>
	/// Quita, sea la cantidad que sea, un video de la cola
	/// </summary>
	void forcePopVideo();

	/// <summary>
	/// Obtiene el sdlRect del video
	/// </summary>
	/// <returns></returns>
	SDL_Rect& getRect();

	/// <summary>
	/// 
	/// </summary>
	/// <returns>Devuelve true si la cola estÅEvacia</returns>
	bool queueEmpty();

	/// <summary>
	/// Define el booleano de control de forcePop
	/// </summary>
	/// <param name="n"></param>
	void setForcePop(bool n);

	/// <summary>
	/// Devuelve el nombre del video que se estÅEreproduciendo actualemente.
	/// </summary>
	/// <returns>Si no hay videos, se devuelve ""</returns>
	std::string getFrontName(){
		if (!queueVideos.empty()){
			const char* s = queueVideos.front().filename;
			std::string str(s);
			std::string file = s;
			return sdlutils().getNameFilePathByCutter(file, '/');
		}
		return "";
	}

private:

	void changeTexture();
	//Cola de videos
	std::deque<Video> queueVideos;	
	// sdl stuff
	int window_w, window_h;
	SDL_Texture* sdlTexture = nullptr;
	SDL_Rect sdlRect;
	SDL_Event event;
	
	//Tiempo entre frame y frame del video
	Uint32 lastUpdate;
	//Controlares de decodificaciÛn del video
	int paused = 0;
	int ret = 0;
	bool available = false, forcePop = false;
};

