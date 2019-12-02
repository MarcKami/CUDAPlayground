#include "SUBReader.h"

// System includes
#include <stdio.h>

SUBReader::SUBReader(SUB* _api, const char* _url) : api(_api), url(_url) {
	subHandle = api->create("MyPipeline");
	if (subHandle != NULL) {
		//printf("SubReader: sub.create() successful.\n");
		isPlaying = api->play(subHandle, url);
		if (!isPlaying) {
			//printf("SubReader: sub_play() failed, will try again later\n");
		} else {
			streamCount = api->get_stream_count(subHandle);
			//printf("SubReader: streamCount = %d\n", streamCount);
		}
	} else
		printf("PCSUBReader: sub_create() failed\n");
}