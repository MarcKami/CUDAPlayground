#include "PCDecoder.h"

PCDecoder::PCDecoder() :	decoder(nullptr),
							pointcloud(nullptr) {
	char* message = NULL;
	decoder = cwipc_new_decoder(&message, CWIPC_API_VERSION);
	if (decoder == nullptr)
		printf("PCDecoder: cwipc_new_decoder creation failed\n"); // Should not happen, should throw exception
}

void PCDecoder::Stop() {
	token = nullptr;
	decoder = nullptr;
	pointcloud = nullptr;
}

void PCDecoder::Update() {
	if (token != nullptr) {
		decoder->feed(token->currentBuffer, token->currentSize);
		if (decoder->available(true)) {
			pointcloud = decoder->get();
			if (pointcloud != nullptr) {
				printf("PCDecoder: PC decoded.\n");
				token->currentPointcloud = pointcloud;
			} else {
				printf("PCDecoder: cwipc_decoder: available() true, but did not return a pointcloud\n");
			}

		} else
			printf("PCDecoder: cwipc_decoder: no pointcloud available currentSize %d\n", token->currentSize);
	}
}