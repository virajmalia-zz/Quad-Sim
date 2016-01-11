// DO NOT OPEN THIS FILE DIRECTLY IN THE IDE: OPEN MotorTestingProgram_vX_X instead and this will appear as a tab
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// This mode is intended to allow programming of the ESC's with respect to different parameters available to program. It was
// developed using a "EMAX" brushless motor ESC, but many other ESC's use very similar calibration routines.
// Refer to your ESC's instructions in the datasheet (if you are fortunate enough to have any) for more information on how this proceedure
// should be performed, and modify the code as needed using the code below as an example.
// To adjust range of signal widths, adjust value of "lowServo" and "highServo". Note that the Arduino has limitations
// on supported servo signal lengths, so these should only be changed with these limitations in mind. 
// See the Arduino Servo.h library code for more information.
void programMode(){
  Serial.println(" ");
  Serial.println("Starting Program Mode...");
  m1.writeMicroseconds(lowServo);
  Serial.println("Type 1 to exit calibration mode:");
  Serial.println("DISCONNECT ESC'S FROM POWER!! Then type -1 to continue.");
  while (Serial.available() <= 0) {} // Wait till user responds before doing anything
  incomingByte = Serial.parseInt(); // read the incoming byte:
  if (incomingByte == -1) {
    Serial.println("ALL THROTTLES BEING SET TO 100%");  // High signal is used to make ESC enter programming mode
    delay(2000); // pause to let people react if it's a mistake (i.e. get away from the motor)
    m1.writeMicroseconds(highServo);
    Serial.println("CONNECT POWER TO ESC:");
    Serial.println("ENTER ANYTHING (E.G. 0) TO SELECT A PARAMETER TO PROGRAM"); // For ESCs that can be programmed using PWM(beep method).
    //  Enter anything after the beep pattern of the parameter to be programmed.
    while (Serial.available() <= 0) {
    } // Wait till user responds before doing anything
    m1.writeMicroseconds(lowServo); //Standard procedure to select a parameter
    int temp=Serial.parseInt();
    delay(1000);
    Serial.println("PARAMETER SELECTED. ENTER ANYTHING (E.G. 0) TO SELECT A SETTING");  //  Enter anything after the beep pattern of the setting to be selected.
    while (Serial.available() == temp) {
    } // Wait till user responds before doing anything. ENTER THE SAME KEY THAT WAS USED TO SELECT THE PARAMETER
    m1.writeMicroseconds(highServo);  //Standard procedure to select a setting.
    delay(1000);
    Serial.println("Setting selected");
    Serial.println(" ");
    instructFlag = HIGH;
  }
  else {
    m1.writeMicroseconds(lowServo);
    instructFlag = HIGH;
    timeNow = micros(); // get current time in MICROSECONDS. Used on next print command (assuming no blade pass interrupt occurs first)
    printFlag = 1;
  }
}
