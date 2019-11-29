#include "SUB.h"
#include <stdio.h>

SUB::SUB(SUB_API* _api, const char* _url) : api(_api), url(_url) {
	printf("Calling SUB\n");
	subHandle = api->create("MyPipeline");
	printf("DEBUG\n");
	if (subHandle != NULL) {
		printf("SubReader: sub.create() successful.");
		isPlaying = api->play(subHandle, url);
		if (!isPlaying) {
			printf("SubReader: sub_play() failed, will try again later");
		} else {
			streamCount = api->get_stream_count(subHandle);
			printf("SubReader: streamCount = %d\n", streamCount);
		}
	} else
		printf("PCSUBReader: sub_create() failed");
}