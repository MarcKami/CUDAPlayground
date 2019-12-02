/*
 * Copyright 2019-2020 Marc Martos.  All rights reserved.
 */

#pragma once

 // System includes
#include <Windows.h>
#include <cstdint>
#include <cstddef> // size_t

struct FrameInfo {
	int64_t timestamp;
	uint8_t* dsi;
	int dsi_size;
};

struct StreamDesc {
	uint32_t MP4_4CC;
	uint32_t tileNumber;
	uint32_t quality;
};

// opaque handle to a signals pipeline
struct sub_handle;

class SUB {
public:
	SUB();

	typedef sub_handle* (*sub_create)(const char* name);
	sub_create create;

	// Destroys a pipeline. This frees all the resources.
	typedef void(*sub_destroy)(sub_handle* h);
	sub_destroy destroy;

	// Returns the number of compressed streams.
	typedef int(*sub_get_stream_count)(sub_handle* h);
	sub_get_stream_count get_stream_count;

	// Returns the 4CC of a given stream. Desc is owned by the caller.
	typedef bool(*sub_get_stream_info)(sub_handle* h, int streamIndex, struct streamDesc* desc);
	sub_get_stream_info get_stream_info;

	// Plays a given URL.
	typedef bool(*sub_play)(sub_handle* h, const char* URL);
	sub_play play;

	// Copy the next received compressed frame to a buffer.
	// Returns: the size of compressed data actually copied,
	// or zero, if no frame was available for this stream.
	// If 'dst' is null, the frame will not be dequeued, but its size will be returned.
	typedef size_t(*sub_grab_frame)(sub_handle* h, int streamIndex, uint8_t* dst, size_t dstLen, FrameInfo* info);
	sub_grab_frame grab_frame;
};
