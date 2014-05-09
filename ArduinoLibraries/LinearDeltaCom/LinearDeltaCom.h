// LinearDeltaCom.h
// Written by Michael Pauly
// Version 1.1 
// Latest Revision May 4, 2014

// This library contains the functions necessary to map callbacks to the LinearDelta library.
// It uses ASCII communication to parse the following formatted commands:
//
// Input								Associated Callbacks
// ---------------------------------------------------------------------------------
// MOVE XX.XXX YY.YYY ZZ.ZZZ		=> 	moveCallback(XX.XXX,YY.YYY,ZZ.ZZZ);
// XMOVE XX.XXX						=> 	xMoveCallback(XX.XXX);
// YMOVE YY.YYY						=> 	yMoveCallback(YY.YYY);
// ZMOVE ZZ.ZZZ						=> 	zMoveCallback(ZZ.ZZZ);
// SMOOTHMOVE XX.XXX YY.YYY ZZ.ZZZ	=> 	smoothMoveCallback(XX.XXX,YY.YYY,ZZ.ZZZ);
// SPEED SS.SSS						=> 	setSpeedCallback(SS.SSS);
// SMOOTHSPEED SS.SSS				=> 	setSmoothSpeedCallback(SS.SSS);
// HOME								=> 	homeCallback();
// POSITION							=> 	requestPositionCallback();
//
// All inputs are assumed to be floats. It is not required that they have a tens digit or 3 decimal 
// precision. 

// Based off of the RobotAsciiCom library by Dr. Fisher

#ifndef LinearDeltaCom_h
#define LinearDeltaCom_h

#include "Arduino.h"

#define MAX_ASCII_MESSAGE_LENGTH 	64 // If you have longer message change this!
#define MESSAGE_TERMINATOR 			10


class LinearDeltaCom
{
  public:
    LinearDeltaCom();
	// Communication Functions
    void handleRxByte(byte newRxByte);
    void handleRxBytes(byte newRxBytes[], int length);
	// Callbacks
    void registerMoveCallback(void (* moveCallback)(float x, float y, float z));
	void registerXMoveCallback(void (* xMoveCallback)(float x));
	void registerYMoveCallback(void (* yMoveCallback)(float y));
	void registerZMoveCallback(void (* zMoveCallback)(float z));
	void registerSmoothMoveCallback(void (* smoothMoveCallback)(float x, float y, float z));
	void registerSetSpeedCallback(void (* setSpeedCallback)(float speed));
	void registerSetSmoothSpeedCallback(void (* setSmoothSpeedCallback)(float smoothSpeed));
	void registerHomeCallback(void (* homeCallback)());
	void registerRequestPositionCallback(void (requestPositionCallback)());
    
  private:
	// Communication
    char _rxMessageBuffer[MAX_ASCII_MESSAGE_LENGTH];
    int _nextOpenByteInMessageBuffer;	
    void _parseStringCommand(String command);
	// Callbacks
	void (* _moveCallback)(float x, float y, float z);
	void (* _xMoveCallback)(float x);
	void (* _yMoveCallback)(float y);
	void (* _zMoveCallback)(float z);
	void (* _smoothMoveCallback)(float x, float y, float z);
	void (* _setSpeedCallback)(float speed);
	void (* _setSmoothSpeedCallback)(float smoothSpeed);
	void (* _homeCallback)();
	void (* _requestPositionCallback)();
	// Helper
	float _str2flt(String inputString);
};

#endif
