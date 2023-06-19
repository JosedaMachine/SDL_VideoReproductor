#pragma once
#include <stdint.h>

struct AVFormatContext;
struct AVCodecContext;
struct AVCodec;
struct AVFrame;
struct AVPacket;
struct SwsContext;

class VideoSource
{
public:
	VideoSource(const char* filename, bool loop = false);

	~VideoSource();

	bool IsLooping() const {
		return m_Loop;
	};

private:
	bool m_Loop;
	int m_VideoIndex;
	uint32_t m_TimePerFrame;
	unsigned char* m_OutBuffer;
	AVFormatContext* m_Format_Context = nullptr;
	AVCodecContext* m_Code_Context = nullptr;
	SwsContext* m_ImageTransform_Context = nullptr;
	const AVCodec* m_CODEC = nullptr;
	AVFrame* m_Frame = nullptr, *m_FrameYUV = nullptr;
	AVPacket* m_Packet = nullptr;
};
