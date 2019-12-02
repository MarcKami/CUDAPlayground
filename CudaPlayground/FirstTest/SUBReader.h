/*
 * Copyright 2019-2020 Marc Martos.  All rights reserved.
 */

#pragma once

#include "SUB.h"

class SUBReader {
public:
	SUB* api;
	sub_handle* subHandle;
	const char* url;
	int streamNumber;
	int streamCount;
	bool isPlaying;
	uint8_t* dst;
	FrameInfo info;
	int numberOfUnsuccessfulReceives;

	SUBReader(SUB* _api, const char* _url);

};
