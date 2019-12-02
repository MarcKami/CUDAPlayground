/*
 * Copyright 2019-2020 Marc Martos.  All rights reserved.
 */

#include "SUB.h"
#include "B2D.h"
#include "SUBReader.h"

 // System includes
#include <stdio.h>

int main(void) {
	printf("Start\n");

	SUB sub;
	B2D b2d;

	SUBReader entity(&sub, "http://vrt-pcl2dash.viaccess-orca.com/loot/vrtogether.mpd");

	printf("End\n");

	return 0;
}