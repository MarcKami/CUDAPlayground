#pragma once
#include "SUB_API.h"

class SUB {
public:
	SUB_API* api;
	sub_handle* subHandle;
	const char* url;
	int streamNumber;
	int streamCount;
	bool isPlaying;
	uint8_t* dst;
	FrameInfo info;
	int numberOfUnsuccessfulReceives;

	SUB(SUB_API* _api, const char* _url);

};
