// This sketch tests the LinearDeltaCom library by simulating the serial ASCII imputs.

// Based heavily on the Unit Testing example of the deltaCom library by Dr. Fisher.

#include <LinearDeltaCom.h>

LinearDeltaCom deltaCom;

void setup() {
  Serial.begin(115200);
  delay(100);
  deltaCom.registerMoveCallback(moveCallback);
  deltaCom.registerXMoveCallback(xMoveCallback);
  deltaCom.registerYMoveCallback(yMoveCallback);
  deltaCom.registerZMoveCallback(zMoveCallback);
  deltaCom.registerSmoothMoveCallback(smoothMoveCallback);
  deltaCom.registerSetSpeedCallback(setSpeedCallback);
  deltaCom.registerSetSmoothSpeedCallback(setSmoothSpeedCallback);
  deltaCom.registerHomeCallback(homeCallback);
  deltaCom.registerRequestPositionCallback(requestPositionCallback);
 }

void loop() {
  
  Serial.print("Test 1: Move");
  test1();
  Serial.println("");
  Serial.print("Test 2: X Move");
  test2();
  Serial.println("");
  Serial.print("Test 3: Y Move");
  test3();
  Serial.println("");
  Serial.print("Test 4: Z Move");
  test4();
  Serial.println("");
  Serial.print("Test 5: Smooth Move");
  test5();
  Serial.println("");
  Serial.print("Test 6: Set Speed");
  test6();
  Serial.println("");
  Serial.print("Test 7: Set Smooth Speed");
  test7();
  Serial.println("");
  Serial.print("Test 8: Home");
  test8();
  Serial.println("");
  Serial.print("Test 9: Position Request");
  test9();
  Serial.println("");
  // Output should be... (ignoring line breaks)
  // Test 1: Move 
  // Move command: 1.111 2.222 3.333
  // Test 2: X Move 
  // X Move command: 1.234
  // Test 3: Y Move 
  // Y Move command: 2.345
  // Test 4: Z Move 
  // Z move command: 3.456
  // Test 5: Smooth Move 
  // Smooth move command: 3.333 6.666 9.999
  // Test 6: Set speed 
  // Set speed command: 22
  // Test 7: Set Smooth Speed 
  // Set smooth speed command: 55
  // Test 8: Home 
  // Home command
  // Test 9: Position Request 
  // Request position command
  
  while(1);
}


// Callback Functions
void moveCallback(float x, float y, float z){
	Serial.println();
	Serial.print("Move command: ");
	Serial.print(x,3);
	Serial.print(" ");
	Serial.print(y,3);
	Serial.print(" ");
	Serial.print(z,3);
	Serial.print(" ");
	Serial.println();
}
	
void xMoveCallback(float x){
	Serial.println();
	Serial.print("X Move command: ");
	Serial.print(x,3);
	Serial.print(" ");
	Serial.println();
}

void yMoveCallback(float y){
	Serial.println();
	Serial.print("Y Move command: ");
	Serial.print(y,3);
	Serial.print(" ");
	Serial.println();
}

void zMoveCallback(float z){
	Serial.println();
	Serial.print("Z Move command: ");
	Serial.print(z,3);
	Serial.print(" ");
	Serial.println();
}

void smoothMoveCallback(float x, float y, float z){
	Serial.println();
	Serial.print("Smooth move command: ");
	Serial.print(x,3);
	Serial.print(" ");
	Serial.print(y,3);
	Serial.print(" ");
	Serial.print(z,3);
	Serial.print(" ");
	Serial.println();
}

void setSpeedCallback(float speed){
	Serial.println();
	Serial.print("Set speed command: ");
	Serial.print(speed,3);
	Serial.print(" ");
	Serial.println();
}

void setSmoothSpeedCallback(float smoothSpeed){
	Serial.println();
	Serial.print("Set smooth speed command: ");
	Serial.print(smoothSpeed,3);
	Serial.print(" ");
	Serial.println();
}

void homeCallback(){
	Serial.println();
	Serial.print("Home command");
	Serial.print(" ");
	Serial.println();
}

void requestPositionCallback(){
	Serial.println();
	Serial.print("Request position command");
	Serial.print(" ");
	Serial.println();
}

// Test Functions
void test1(){
	byte testMessage[] = "MOVE 1.111 2.222 3.333";
	testMessage[22] = '\n';
	deltaCom.handleRxBytes(testMessage,23);
}
void test2(){
	byte testMessage[] = "XMOVE 1.234";
	testMessage[11] = '\n';
	deltaCom.handleRxBytes(testMessage,12);
}
void test3(){
	byte testMessage[] = "YMOVE 2.345";
	testMessage[11] = '\n';
	deltaCom.handleRxBytes(testMessage,12);
}
void test4(){
	byte testMessage[] = "ZMOVE 3.456";
	testMessage[11] = '\n';
	deltaCom.handleRxBytes(testMessage,12);
}
void test5(){
	byte testMessage[] = "SMOOTHMOVE 3.333 6.666 9.999";
	testMessage[28]='\n';
	deltaCom.handleRxBytes(testMessage,29);
}
void test6(){
	byte testMessage[] = "SPEED 22";
	testMessage[8]='\n';
	deltaCom.handleRxBytes(testMessage,9);
}
void test7(){
	byte testMessage[] = "SMOOTHSPEED 55";
	testMessage[14]='\n';
	deltaCom.handleRxBytes(testMessage,15);
}
void test8(){
	byte testMessage[] = "HOME";
	testMessage[4]='\n';
	deltaCom.handleRxBytes(testMessage,5);
}
void test9(){
	byte testMessage[] = "POSITION";
	testMessage[8]='\n';
	deltaCom.handleRxBytes(testMessage,9);
}