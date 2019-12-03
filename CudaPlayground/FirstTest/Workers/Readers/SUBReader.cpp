#include "SUBReader.h"

// System includes
#include <stdio.h>

SUBReader::SUBReader(SUB* _api, const char* _url) : sub(_api), 
													url(_url),
													currentBuffer(nullptr),
													info(&FrameInfo()),
													isPlaying(false),
													numberOfUnsuccessfulReceives(0),
													streamCount(0),
													streamNumber(0){
	subHandle = sub->create("MyPipeline");
	if (subHandle != nullptr) {
		printf("SubReader: sub.create(%s) successful.\n", url);
		isPlaying = sub->play(subHandle, url);
		if (!isPlaying) {
			printf("SubReader: sub_play(%s) failed, will try again later\n", url);
		} else {
			streamCount = sub->get_stream_count(subHandle);
			printf("SubReader: streamCount = %d\n", streamCount);
		}
	} else
		printf("SUBReader: sub_create(%s) failed\n", url);
}

void SUBReader::Stop() {
	token = nullptr;
	subHandle = nullptr;
	Cleaner();
}

void SUBReader::UnsuccessfulCheck(int _size) {
	if (_size == 0) {
		numberOfUnsuccessfulReceives++;
		if (numberOfUnsuccessfulReceives > 2000) {
			printf("SubReader %s: Too many receive errors. Closing SUB player, will reopen.\n", url);
			subHandle = nullptr;
			isPlaying = false;
			numberOfUnsuccessfulReceives = 0;
		}
		return;
	}
	numberOfUnsuccessfulReceives = 0;
}

void SUBReader::RetryPlay() {
	if (isPlaying) return;
	if (subHandle == nullptr) {
		subHandle = sub->create("MyPipeline");
		if (subHandle == nullptr) {
			printf("SubReader: retry sub.create(%s) call failed again.\n", url);
		} else {
			printf("SubReader: retry sub.create(%s) successful.\n", url);
		}
	} else {
		isPlaying = sub->play(subHandle, url);
		if (!isPlaying) {
			printf("SubReader: sub_play(%s) failed, will try again later\n", url);
		} else {
			printf("SubReader: retry sub.play(%s) successful.\n", url);
			streamCount = sub->get_stream_count(subHandle);
			//printf("SubReader: streamCount = %d\n", streamCount);
		}
	}
}

void SUBReader::Cleaner() {
	size_t iSizeB = 1048576 * sizeof(cwipc_point); // 1 million points buffer
	currentBuffer = (uint8_t*)malloc(iSizeB);
	info = (FrameInfo*)malloc(sizeof(FrameInfo));
}

void SUBReader::Update() {
	if (token != nullptr) {  // Wait for token
		RetryPlay();

		Cleaner();

		// Attempt to receive, if we are playing
		size_t bytesNeeded = (size_t)sub->grab_frame(subHandle, streamNumber, nullptr, 0, info); // Get buffer length.
		printf("bytesNeeded: %d\n", (int)bytesNeeded);
		// If we are not playing or if we didn't receive anything we restart after 1000 failures.
		UnsuccessfulCheck(bytesNeeded);
		if (bytesNeeded != 0) {
			int bytesRead = sub->grab_frame(subHandle, streamNumber, currentBuffer, bytesNeeded, info);
			if (bytesRead == bytesNeeded) {
				printf("SUBReader: Grabed frame!\n");
				// All ok, yield to the next process				
				token->currentBuffer = currentBuffer;
				token->currentSize = bytesRead;
				token->info = info;
				return;
			} else
				printf("SUBReader: sub_grab_frame returned %d bytes after promising %d\n", bytesRead, (int)bytesNeeded);
		}
		
	}
}