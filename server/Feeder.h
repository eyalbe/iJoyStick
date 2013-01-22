#include "stdafx.h"
#include "inc/public.h"
#include "inc/vjoyinterface.h"
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#pragma comment( lib, "VJOYINTERFACE" )

#ifndef FEEDER_H_
#define FEEDER_H_

class Feeder{

public:
	Feeder();
	int get_device();
	void feed(char*);
	void reset();

private:
	USHORT X, Y, Z, ZR, XR;		// Position of several axes
	JOYSTICK_POSITION	iReport;		// The structure that holds the full position data
	BYTE id;				// ID of the target vjoy device (Default is 1)
	UINT iInterface;			// Default target vJoy device
	BOOL ContinuousPOV;		// Continuous POV hat (or 4-direction POV Hat)
	INPUT key;

};

#endif
