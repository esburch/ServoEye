
/*
   Smooth servo rotation using a sinus square function.
   ATTENTION: THIS SKETCH USES THE DELAY FUNCTION
   More infos: http://letsmakerobots.com/node/31697
   created by NilsB
*/

#include <Servo.h>

int blinkTimerInMillies = 5;
const int blinkTableEntries = 21;
const int blinkTable[] = {
  45, 50, 55, 60,
  61, 61, 62, 63,
  64, 66, 67, 69,
  71, 73, 75, 77,
  79, 80, 80, 80, 75

};

const int eyeTimerInMillies = 8;
const int eyeTableEntries = 77;
const int eyeTable[] = {
  45, 45, 45, 46, 46, 46, 47,
  47, 48, 49, 50, 51, 52, 54,
  55, 57, 59, 61, 63, 65, 67,
  68, 70, 72, 74, 76, 78, 80,
  81, 83, 84, 85, 86, 87, 88,
  88, 89, 89, 90, 90, 91, 91,
  92, 92, 93, 94, 95, 96, 97,
  99, 100, 102, 104, 106, 108,
  110, 112, 113, 115, 117, 119,
  121, 123, 125, 126, 128, 129,
  130, 131, 132, 133, 133, 134,
  134, 135, 135, 135
};

const int openPin = A2;     // the number of the pushbutton pin
int openState = 0;         // variable for reading the pushbutton status
int lastOpenState = 0;

const int closePin = A0;
int closeState = 0;
int lastCloseState = 0;

const int runPin = A4;
int runState = 0;
int lastRunState = 0;

const int ledPin =  13;

Servo blinkServo;
Servo shiftServo;
Servo xServo;
Servo yServo;

void setup() {

  setupBlinkServo();
  setupShiftServo();
  setupEyeServo();
  pinMode(openPin, INPUT_PULLUP);
  pinMode(closePin, INPUT_PULLUP);
  pinMode(runPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}


void loop() {

  openState = digitalRead(openPin);
  closeState = digitalRead(closePin);
  runState = digitalRead(runPin);

  if (openState == HIGH && lastOpenState == LOW) {
    attach();
    blinkTimerInMillies = 20;
    open();
    delay(200);
  }
  else if (closeState == HIGH && lastCloseState == LOW) {
    attach();
    close();
    delay(200);
  }
  else if (runState == HIGH && lastRunState == LOW) {
    attach();
    delay(600);
    open();
    close();
    open();
    delay(200);
    lookUp();
    delay(200);
    lookUpDown();
    delay(200);
    neutral();
    delay(200);
    lookLeft();
    delay(200);
    lookLeftRight();
    delay(200);
    neutral();
    delay(200);
    blinkTimerInMillies = 20;
    close();
    blinkTimerInMillies = 5;
    delay(200);

    }
  else {

  }
  detach();
  lastOpenState = openState;
  lastCloseState = closeState;
  lastRunState = runState;

}

/***********************************
********* Stop/Start Function ******
***********************************/
void detach() {

  stopXMove();
  stopYMove();
  //stopBlinkMove();
  stopShiftMove();
}

void attach() {

  setupEyeServo();
  setupBlinkServo();
  setupShiftServo();

}


/***********************************
********* Blink Functions **********
***********************************/
void open()
{
  for (int angleIndex = 0; angleIndex < blinkTableEntries; angleIndex++) {
    moveBlinkServoTo(angleBlink(angleIndex));
    waitBlink();
  }

  waitLongBlink();

}

void close()
{
  for (int angleIndex = blinkTableEntries - 1; angleIndex >= 0; angleIndex--) {
    moveBlinkServoTo(angleBlink(angleIndex));
    waitBlink();
  }

  waitLongBlink();

}

void moveBlinkServoTo(int angle) {
  Serial.println(angle);
  blinkServo.write(angle);
}

int angleBlink(int index) {
  return blinkTable[index];
}

void stopBlinkMove() {
  blinkServo.detach();
}

void setupBlinkServo() {
  blinkServo.attach(11);
  blinkServo.write(60);
}

void waitBlink() {
  delay(blinkTimerInMillies);
}

void waitLongBlink() {
  delay(5 * blinkTimerInMillies);
}

/***********************************
********* Shift Functions **********
***********************************/

void up()
{
  shiftServo.write(160);
}

void down()
{

  shiftServo.write(120);
}

void neutral()
{
  shiftServo.write(140);
  xServo.write(90);
  yServo.write(90);
}

void setupShiftServo() {
  shiftServo.attach(10);
  shiftServo.write(140);
}

void stopShiftMove() {
  shiftServo.detach();
}

/***********************************
********** Eye Functions ***********
***********************************/

void lookDown()
{
  down();
  for (int angleIndex = 38; angleIndex < eyeTableEntries - 1; angleIndex++) {
    moveYEyeServoTo(angleEye(angleIndex));
    waitEye();
  }
  waitLongEye();
}

void lookUp()
{
  up();
  for (int angleIndex = 38; angleIndex >= 0; angleIndex--) {
    moveYEyeServoTo(angleEye(angleIndex));
    waitEye();
  }

  waitLongEye();

}

void lookUpDown()
{
  up();
  for (int angleIndex = 0; angleIndex < eyeTableEntries - 1; angleIndex++) {
    moveYEyeServoTo(angleEye(angleIndex));
    waitEye();
    down();
  }

  waitLongEye();
}

void lookDownUp()
{
  for (int angleIndex = eyeTableEntries - 1; angleIndex >= 0; angleIndex--) {
    moveYEyeServoTo(angleEye(angleIndex));
    waitEye();
  }

  waitLongEye();
}

void lookLeft()
{
  for (int angleIndex = 38; angleIndex < eyeTableEntries - 1; angleIndex++) {
    moveXEyeServoTo(angleEye(angleIndex));
    waitEye();
  }

  waitLongEye();
}

void lookRight()
{
  for (int angleIndex = 38; angleIndex >= 0; angleIndex--) {
    moveXEyeServoTo(angleEye(angleIndex));
    waitEye();
  }

  waitLongEye();

}

void lookLeftRight()
{
  for (int angleIndex = 0; angleIndex < eyeTableEntries - 1; angleIndex++) {
    moveXEyeServoTo(angleEye(angleIndex));
    waitEye();
  }

  waitLongEye();
}

void lookRightLeft()
{
  for (int angleIndex = eyeTableEntries - 1; angleIndex >= 0; angleIndex--) {
    moveXEyeServoTo(angleEye(angleIndex));
    waitEye();
  }

  waitLongEye();
}

void moveYEyeServoTo(int angle) {
  Serial.println(angle);
  yServo.write(angle);
}

void moveXEyeServoTo(int angle) {
  Serial.println(angle);
  xServo.write(angle);
}


int angleEye(int index) {
  return eyeTable[index];
}

void stopYMove() {
  yServo.detach();
}

void stopXMove() {
  xServo.detach();
}

void setupEyeServo() {
  yServo.attach(9);
  yServo.write(90);
  xServo.attach(6);
  xServo.write(90);
}

void waitEye() {
  delay(eyeTimerInMillies);
}

void waitLongEye() {
  delay(5 * eyeTimerInMillies);
}
