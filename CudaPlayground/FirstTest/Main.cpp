/*
 * Copyright 2019-2020 Marc Martos.  All rights reserved.
 */

#include "API/B2D.h"
#include "Workers/Readers/SUBReader.h"
#include "Workers/Codecs/PCDecoder.h"

 // System includes
#include <stdio.h>

int main(void) {
	printf("Start\n");

	SUB sub;

	SUBReader reader(&sub, "https://vrt-pcl2dash.viaccess-orca.com/loot/vrtogether.mpd");
	PCDecoder dec;
	if (dec.decoder != nullptr) {
		reader.token = &Token(1);
		for (int i = 0; i < 10; ++i) {
			reader.Update();
			//dec.token = reader.token;
			//dec.Update();
		}
		reader.Stop();
		//dec.Stop();
	}
	
	printf("End\n");

	return 0;
}