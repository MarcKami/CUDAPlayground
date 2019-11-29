#include "SUB_API.h"
#include <stdio.h>

SUB_API::SUB_API() {
	HINSTANCE hDLL;
	hDLL = LoadLibrary("signals-unity-bridge.dll");
	if (hDLL != NULL) {
		create = (sub_create)GetProcAddress(hDLL, "sub_create");

		destroy = (sub_destroy)GetProcAddress(hDLL, "sub_destroy");

		get_stream_count = (sub_get_stream_count)GetProcAddress(hDLL, "sub_get_stream_count");

		get_stream_info = (sub_get_stream_info)GetProcAddress(hDLL, "sub_get_stream_info");

		play = (sub_play)GetProcAddress(hDLL, "sub_play");

		grab_frame = (sub_grab_frame)GetProcAddress(hDLL, "sub_grab_frame");;

		FreeLibrary(hDLL);
		printf("Signals Unity Bridge DLL Success.\n");
	} else {
		printf("¡Error Loading Signals Unity Bridge DLL !\n");
	}
}