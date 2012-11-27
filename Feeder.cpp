#include "Feeder.h"

Feeder::Feeder(){
	id=1;
	iInterface=1;
	ContinuousPOV=FALSE;
}

int Feeder::get_device(){
	//int count=0;

	// Get the driver attributes (Vendor ID, Product ID, Version Number)
	if (!vJoyEnabled())
	{
		_tprintf("vJoy driver not enabled: Failed Getting vJoy attributes.\n");
		return -2;
	}
	else
	{
		_tprintf("Vendor: %S\nProduct :%S\nVersion Number:%S\n", TEXT(GetvJoyManufacturerString()),  TEXT(GetvJoyProductString()), TEXT(GetvJoySerialNumberString()));
	};

	// Get the state of the requested device
	VjdStat status = GetVJDStatus(iInterface);
	switch (status)
	{
	case VJD_STAT_OWN:
		_tprintf("vJoy Device %d is already owned by this feeder\n", iInterface);
		break;
	case VJD_STAT_FREE:
		_tprintf("vJoy Device %d is free\n", iInterface);
		break;
	case VJD_STAT_BUSY:
		_tprintf("vJoy Device %d is already owned by another feeder\nCannot continue\n", iInterface);
		return -3;
	case VJD_STAT_MISS:
		_tprintf("vJoy Device %d is not installed or disabled\nCannot continue\n", iInterface);
		return -4;
	default:
		_tprintf("vJoy Device %d general error\nCannot continue\n", iInterface);
		return -1;
	};

	// Check which axes are supported
	BOOL AxisX  = GetVJDAxisExist(iInterface, HID_USAGE_X);
	BOOL AxisY  = GetVJDAxisExist(iInterface, HID_USAGE_Y);
	BOOL AxisZ  = GetVJDAxisExist(iInterface, HID_USAGE_Z);
	BOOL AxisRX = GetVJDAxisExist(iInterface, HID_USAGE_RX);
	BOOL AxisRZ = GetVJDAxisExist(iInterface, HID_USAGE_RZ);
	// Get the number of buttons and POV Hat switchessupported by this vJoy device
	int nButtons  = GetVJDButtonNumber(iInterface);
	int ContPovNumber = GetVJDContPovNumber(iInterface);
	int DiscPovNumber = GetVJDDiscPovNumber(iInterface);

	// Print results
	_tprintf("\nvJoy Device %d capabilities:\n", iInterface);
	_tprintf("Numner of buttons\t\t%d\n", nButtons);
	_tprintf("Numner of Continuous POVs\t%d\n", ContPovNumber);
	_tprintf("Numner of Descrete POVs\t\t%d\n", DiscPovNumber);
	_tprintf("Axis X\t\t%s\n", AxisX?"Yes":"No");
	_tprintf("Axis Y\t\t%s\n", AxisX?"Yes":"No");
	_tprintf("Axis Z\t\t%s\n", AxisX?"Yes":"No");
	_tprintf("Axis Rx\t\t%s\n", AxisRX?"Yes":"No");
	_tprintf("Axis Rz\t\t%s\n", AxisRZ?"Yes":"No");

	// Acquire the target
	if ((status == VJD_STAT_OWN) || ((status == VJD_STAT_FREE) && (!AcquireVJD(iInterface))))
	{
		_tprintf("Failed to acquire vJoy device number %d.\n", iInterface);
		return -1;
	}
	else
	{
		_tprintf("Acquired: vJoy device number %d.\n", iInterface);
	}
	return 0;
}

void Feeder::feed(int* data_array){
	/*
		data_array[0] = action: setX, setY, Button...
		data_array[1] = value:	if setX/setY than set value.
								if Buttton then 1=push, 0=release.
		data_array[2] = b.n:	the Button number.
	*/

	switch (data_array[0])
	{
	case(1):
			SetAxis(data_array[1], iInterface, HID_USAGE_X);
	break;
	case(2):
			SetAxis(data_array[1], iInterface, HID_USAGE_Y);
	break;
	case(3):
			if (data_array[1] == 0)
				SetBtn(FALSE, iInterface, data_array[2]);
			else
				SetBtn(TRUE, iInterface, data_array[2]);
	break;
	case(4):
		reset();
	break;
	}
		//SetAxis(Z, iInterface, HID_USAGE_Z);
		//SetAxis(XR, iInterface, HID_USAGE_RX);
		//SetAxis(ZR, iInterface, HID_USAGE_RZ);
}

void Feeder::reset(){
	ResetVJD(iInterface);
}