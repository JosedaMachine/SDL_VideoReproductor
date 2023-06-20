#include "VideoSource.h"

#include <iostream>

//FFMPEG Libaries
extern "C" {
	#include <libavformat/avformat.h>
	#include <libavcodec/avcodec.h>
	#include <libavutil/imgutils.h>
	#include <libswscale/swscale.h>
}

VideoSource::VideoSource(const char* filename, bool loop)
	: m_Loop(loop)
{
	//Allocate memory to the format context
	m_Format_Context = avformat_alloc_context();

	// open video file 
	if (avformat_open_input(&m_Format_Context, filename, NULL, NULL) != 0) {
		std::cout << "Couldn't open input stream.\n" << std::endl;
		//return -1;
		return;
	}

	// find the stream
	if (avformat_find_stream_info(m_Format_Context, NULL) < 0) {
		std::cout << "Couldn't find stream information.\n" << std::endl;
		//return -1;
		return;
	}

	m_VideoIndex = av_find_best_stream(m_Format_Context, AVMEDIA_TYPE_VIDEO, -1, -1,
		nullptr, 0);

	if (m_VideoIndex < 0) {
		std::cout << "Didn't find a video stream.\n" << std::endl;
		//return -1;
		return;
	}

	// find the decoder
	m_CODEC = avcodec_find_decoder(m_Format_Context->streams[m_VideoIndex]->codecpar->codec_id);
	if (m_CODEC == nullptr) {
		std::cout << "Codec not found." << std::endl;
		//return -1;
		return;
	}

	// allocate and initialise the codec context
	m_Code_Context = avcodec_alloc_context3(m_CODEC);
	if (avcodec_parameters_to_context(m_Code_Context,
		m_Format_Context->streams[m_VideoIndex]->codecpar) < 0) {
		std::cout << "Could not fill the codec conetxt." << std::endl;
		//return -1;
		return;
	}

	if (avcodec_open2(m_Code_Context, m_CODEC, NULL) < 0) {
		std::cout << "Could not open codec." << std::endl;
		//return -1;
		return;
	}

	// allocate and initialise the output buffer
	m_Frame = av_frame_alloc();
	m_FrameYUV = av_frame_alloc();

	m_OutBuffer =static_cast<unsigned char*>(av_malloc(static_cast<std::size_t>(av_image_get_buffer_size(
																	AV_PIX_FMT_YUV420P, m_Code_Context->width,
																	m_Code_Context->height, 1))));

	av_image_fill_arrays(m_FrameYUV->data, m_FrameYUV->linesize, m_OutBuffer,
		AV_PIX_FMT_YUV420P, m_Code_Context->width, m_Code_Context->height, 1);

	// allocate the memory where the frame (before decoding) is loaded
	m_Packet = static_cast<AVPacket*>(av_malloc(sizeof(AVPacket)));

	//Output file information
	//av_dump_format(pFormatCtx, 0, files.back().first, 0);

	// allocate scaling/conversion context
	m_ImageTransform_Context = sws_getContext(m_Code_Context->width, m_Code_Context->height,
		m_Code_Context->pix_fmt, m_Code_Context->width, m_Code_Context->height,
		AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

	//Calculate frame rate
	m_TimePerFrame = static_cast<uint32_t>(1000.0
		/ av_q2d(m_Format_Context->streams[m_VideoIndex]->r_frame_rate));
}

VideoSource::~VideoSource()
{
}
