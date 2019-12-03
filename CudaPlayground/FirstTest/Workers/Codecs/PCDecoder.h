/*
 * Copyright 2019-2020 Marc Martos.  All rights reserved.
 */

#pragma once

#include <cwipc_util/api.h>
#include <cwipc_codec/api.h>
#include "../BaseWorker.h"

class PCDecoder : public BaseWorker {
public:
	cwipc_decoder* decoder;
	cwipc* pointcloud;

	PCDecoder();

	void Stop();

	void Update();
};
