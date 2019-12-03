/*
 * Copyright 2019-2020 Marc Martos.  All rights reserved.
 */

#pragma once

#include <cwipc_util/api.h>
#include "../API/SUB.h"

class Token {
public:
	Token(int forks = 1) { totalForks = forks; }
	Token(uint8_t* _currentBuffer, int _currentSize, cwipc* _currentPointcloud) { currentBuffer = _currentBuffer; currentSize = _currentSize; currentPointcloud = _currentPointcloud; }

	int totalForks;
	int currentForks;
	cwipc* currentPointcloud;
	uint8_t* currentBuffer;
	int currentSize;
	//uint64_t latency;
	FrameInfo* info;
};
