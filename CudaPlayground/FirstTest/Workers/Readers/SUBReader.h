/*
 * Copyright 2019-2020 Marc Martos.  All rights reserved.
 */

#pragma once

#include "../../API/SUB.h"
#include "../BaseWorker.h"

class SUBReader : public BaseWorker {
public:
	SUB* sub;
	sub_handle* subHandle;
	const char* url;
	int streamNumber;
	int streamCount;
	bool isPlaying;
	uint8_t* currentBuffer;
	FrameInfo* info;
	int numberOfUnsuccessfulReceives;

	SUBReader(SUB* _api, const char* _url);

	void Stop();

	void UnsuccessfulCheck(int _size);

	void RetryPlay();

	void Cleaner();

	void Update();
};
