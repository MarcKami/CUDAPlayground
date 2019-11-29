#include "SUB_API.h"
#include "SUB.h"
#include <stdio.h>

int main(void) {
	printf("Start\n");

	SUB_API sub_api;

	SUB entity(&sub_api, "http://vrt-pcl2dash.viaccess-orca.com/loot/vrtogether.mpd");

	printf("End\n");

	return 0;
}