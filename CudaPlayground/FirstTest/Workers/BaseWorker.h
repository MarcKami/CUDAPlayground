/*
 * Copyright 2019-2020 Marc Martos.  All rights reserved.
 */

#pragma once

#include "Token.h"

enum WorkerType { Init, Run, End };

class BaseWorker {
public:
	Token* token;
	//WorkerType type;

	//BaseWorker(WorkerType _type);
};
