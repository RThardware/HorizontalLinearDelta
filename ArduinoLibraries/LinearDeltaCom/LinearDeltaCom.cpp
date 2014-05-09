#include "Arduino.h"
#include "LinearDeltaCom.h"

// Communication Functions
LinearDeltaCom::LinearDeltaCom() {
	_nextOpenByteInMessageBuffer = 0;
}

/**
 * Convenience method to handle multiple bytes.
 * Just calls the handleRxByte method with each byte individually.
 */
void LinearDeltaCom::handleRxBytes(byte newRxBytes[], int length) {
	for (int i = 0; i < length; i++) {
		handleRxByte(newRxBytes[i]);
	}
}

/**
 * Handle a newly received byte.
 * If the byte is the MESSAGE_TERMINATOR process the message.
 * If the byte is not the MESSAGE_TERMINATOR then just save it.
 */
void LinearDeltaCom::handleRxByte(byte newRxByte) {
	if (newRxByte == MESSAGE_TERMINATOR) {
		// Convert the rx message buffer to a String and parse.
		_rxMessageBuffer[_nextOpenByteInMessageBuffer] = '\0';
		String rxStr = String(_rxMessageBuffer);
		_parseStringCommand(rxStr);  // The real work happens here.
		_nextOpenByteInMessageBuffer = 0;
	} else {
		// Mid message.  Save the byte.
		_rxMessageBuffer[_nextOpenByteInMessageBuffer] = newRxByte;
		_nextOpenByteInMessageBuffer++;
	}
}


/**
 * Process the complete message.
 */
void LinearDeltaCom::_parseStringCommand(String command) {
	int spaceIndex = command.indexOf(' ');
	//String commandStr;
	if (command.startsWith("MOVE ")) {
		int direction = 1;
		float coordinates[4]; 
		String moveStr = command;
		while (spaceIndex != -1 && direction < 4) {
			moveStr = moveStr.substring(spaceIndex + 1);
			coordinates[direction] = _str2flt(moveStr);
			direction++;
			spaceIndex = moveStr.indexOf(' ');
		}
		if(_moveCallback != NULL){
			_moveCallback(coordinates[1],coordinates[2],coordinates[3]);
		}
	} else if (command.startsWith("XMOVE")) {
		String xMoveStr = command.substring(spaceIndex + 1);
		if (_xMoveCallback != NULL) {
			_xMoveCallback(_str2flt(xMoveStr));
		}
	} else if (command.startsWith("YMOVE")) {
		String yMoveStr = command.substring(spaceIndex + 1);
		if (_yMoveCallback != NULL) {
			_yMoveCallback(_str2flt(yMoveStr));
		}
	} else if (command.startsWith("ZMOVE")) {
		String zMoveStr = command.substring(spaceIndex + 1);
		if (_zMoveCallback != NULL) {
			_zMoveCallback(_str2flt(zMoveStr));
		}
	} else if (command.startsWith("SMOOTHMOVE")) {
		int smoothDirection = 1;
		float smoothCoordinates[4]; 
		String smoothMoveStr = command;
		while (spaceIndex != -1 && smoothDirection < 4) {
			smoothMoveStr = smoothMoveStr.substring(spaceIndex + 1);
			smoothCoordinates[smoothDirection] = _str2flt(smoothMoveStr);
			smoothDirection++;
			spaceIndex = smoothMoveStr.indexOf(' ');
		}
		if(_smoothMoveCallback != NULL){
			_smoothMoveCallback(smoothCoordinates[1],smoothCoordinates[2],smoothCoordinates[3]);
		}
	} else if (command.startsWith("SPEED")) {
		String speedStr = command.substring(spaceIndex + 1);
		if (_setSpeedCallback != NULL) {
			_setSpeedCallback(_str2flt(speedStr));
		}
	} else if (command.startsWith("SMOOTHSPEED")) {
		String smoothSpeedStr = command.substring(spaceIndex + 1);
		if (_setSmoothSpeedCallback != NULL) {
			_setSmoothSpeedCallback(_str2flt(smoothSpeedStr));
		}
	} else if (command.startsWith("HOME")) {
		if (_homeCallback != NULL) {
			_homeCallback();
		}
	} else if (command.startsWith("POSITION")) {
		if (_requestPositionCallback != NULL) {
			_requestPositionCallback();
		}
	}
}

// Attach the callbacks
void LinearDeltaCom::registerMoveCallback(
		void (*moveCallback)(float x, float y, float z)){
	_moveCallback=moveCallback;
}

void LinearDeltaCom::registerXMoveCallback(
		void (*xMoveCallback)(float x)){
	_xMoveCallback=xMoveCallback;
}

void LinearDeltaCom::registerYMoveCallback(
		void (*yMoveCallback)(float y)){
	_yMoveCallback=yMoveCallback;
}

void LinearDeltaCom::registerZMoveCallback(
		void (*zMoveCallback)(float z)){
	_zMoveCallback=zMoveCallback;
}

void LinearDeltaCom::registerSmoothMoveCallback(
		void (*smoothMoveCallback)(float x, float y, float z)){
	_smoothMoveCallback=smoothMoveCallback;
}

void LinearDeltaCom::registerSetSpeedCallback(
		void (*setSpeedCallback)(float speed)){
	_setSpeedCallback=setSpeedCallback;
}

void LinearDeltaCom::registerSetSmoothSpeedCallback(
		void (*setSmoothSpeedCallback)(float smoothSpeed)){
	_setSmoothSpeedCallback=setSmoothSpeedCallback;
}

void LinearDeltaCom::registerHomeCallback(
		void (*homeCallback)()){
	_homeCallback=homeCallback;
}

void LinearDeltaCom::registerRequestPositionCallback(
		void (*requestPositionCallback)()){
	_requestPositionCallback=requestPositionCallback;
}
	
// Helper function
float LinearDeltaCom::_str2flt(String inputString){
	char charArray[inputString.length()+1];
	inputString.toCharArray(charArray,sizeof(charArray));
	float outputFloat=atof(charArray);
	return outputFloat;
}