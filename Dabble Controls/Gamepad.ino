//Copy and paste the code into Ardunio IDE in order to edit. Make sure to push changes to github as well!
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

int motor1Power = 0;
int motor2Power = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(250000);      // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600);      //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
  //Need the pin numbers for these motors
  pinMode(motorControl1, OUTPUT);
  pinMode(motorContorl2, OUTPUT);
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  Serial.print("KeyPressed: ");
  if (GamePad.isUpPressed())
  {
    Serial.print("UP");
  }

  if (GamePad.isDownPressed())
  {
    Serial.print("DOWN");
  }

  if (GamePad.isLeftPressed())
  {
    Serial.print("Left");
  }

  if (GamePad.isRightPressed())
  {
    Serial.print("Right");
  }

  if (GamePad.isSquarePressed())
  {
    Serial.print("Square");
    digitalWrite(motorControl2, HIGH);
    delay(50);
  }

  if (GamePad.isCirclePressed())
  {
    Serial.print("Circle");
    digitalWrite(motorControl1, HIGH);
    delay(50);
  }

  if (GamePad.isCrossPressed())
  {
    Serial.print("Cross");
    digitalWrite(motorControl2, LOW);
    delay(20);
  }

  if (GamePad.isTrianglePressed())
  {
    Serial.print("Triangle");
    digitalWrite(motorControl2, LOW);
    delay(20);
  }

  if (GamePad.isStartPressed())
  {
    Serial.print("Start");
  }

  if (GamePad.isSelectPressed())
  {
    Serial.print("Select");
  }
  Serial.print('\t');

  int a = GamePad.getAngle();
  Serial.print("Angle: ");
  Serial.print(a);
  Serial.print('\t');
  int b = GamePad.getRadius();
  Serial.print("Radius: ");
  Serial.print(b);
  Serial.print('\t');
  float x = GamePad.getXaxisData();
  Serial.print("x_axis: ");
  Serial.print(x);
  Serial.print('\t');
  float y = GamePad.getYaxisData();
  Serial.print("y_axis: ");
  Serial.println(y);
  Serial.println();
if(abs(x) != 7){
  motor2Power = int((2.20 ^ abs(x)));
}else{
  motor2Power = 255;
}
if(abs(y) ! = 7){
  motor1Power = int((2.20 ^ abs(y)));
}else{
motor1Power = 255;
}
//will update with the correct pins and motors with their corresponding assignments.
  analogWrite(motorControl, motor1Power);
  analogWrite(motorControl, motor2Power);


  



}
