// Copy and paste the code into Ardunio IDE in order to edit. Make sure to push changes to github as well!
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

// clockwise backward
// counterclockwise forward
int motorLPower = 0;
int motorLpin1;
int motorLPWM;
int motorLpin2;
int motorRpin1;
int motorRPWM;
int motorRpin2;
int motorRPower = 0;
int motorMPower = 0;
int motorMpin1;
int motorMpin2;
int motorMPWM = 0;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(250000); // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600);   // Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
  // Need the pin numbers for these motors
  pinMode(motorLpin1, OUTPUT);
  pinMode(motorLpin2, OUTPUT);
  pinMode(motorRpin1, OUTPUT);
  pinMode(motorRpin2, OUTPUT);
  pinMode(motorMpin1, OUTPUT);
  pinMode(motorMpin2, OUTPUT);
}

void loop()
{
  Dabble.processInput(); // this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  float y = GamePad.getYaxisData();
  float x = GamePad.getXaxisData();

  // as the x gets greater L power motor needs to be greater than R
  // as y gets greater
  int motorDifference = 0;
  int motorPower = 0;
  if (y == 0)
  {
    analogWrite(motorMPWM, motorPower);
  }
  else if (y > 0)
  {
    motorDifference = int((18 * x));
    motorPower = int((39 * y));
    // Both Motor Needs to be forward
    digitalWrite(motorLpin1, HIGH);
    digitalWrite(motorLpin2, LOW);
    digitalWrite(motorRpin1, HIGH);
    digitalWrite(motorRpin2, LOW);
    digitalWrite(motorMpin1, HIGH);
    digitalWrite(motorMpin2, LOW);
    if (y == 7)
    {
      analogWrite(motorLPWM, 255);
      analogWrite(motorMPWM, 255);
      analogWrite(motorRPWM, 255);
    }
    else if (x > 0)
    {
      if (motorPower - motorDifference < 0)
      {
        digitalWrite(motorRpin1, LOW);
        digitalWrite(motorRpin2, HIGH);
      }
      analogWrite(motorMPWM, motorPower);
      analogWrite(motorLPWM, motorPower);
      analogWrite(motorRPWM, abs(motorPower - motorDifference));
    }
    else
    {
      if (motorPower - motorDifference < 0)
      {
        digitalWrite(motorLpin1, LOW);
        digitalWrite(motorLpin2, HIGH);
      }
      analogWrite(motorMPWM, motorPower);
      analogWrite(motorLPWM, abs(motorPower - motorDifference));
      analogWrite(motorRPWM, motorPower);
    }
  }
  else
  {
    // Both Motor Needs to be backward
    digitalWrite(motorLpin1, LOW);
    digitalWrite(motorLpin2, HIGH);
    digitalWrite(motorRpin1, LOW);
    digitalWrite(motorRpin2, HIGH);
    digitalWrite(motorMpin1, LOW);
    digitalWrite(motorMpin2, HIGH);
    motorDifference = int((18 * x));
    motorPower = int((39 * abs(y)));
    if (y == -7)
    {
      analogWrite(motorLPWM, 255);
      analogWrite(motorRPWM, 255);
      analogWrite(motorMPWM, 255);
    }
    else if (x > 0)
    {
      if (motorPower - motorDifference < 0)
      {
        digitalWrite(motorRpin1, HIGH);
        digitalWrite(motorRpin2, LOW);
      }
      analogWrite(motorLPWM, motorPower);
      analogWrite(motorRPWM, motorPower);
      analogWrite(motorMPWM, motorPower);
      analogWrite(motorRPWM, abs(motorPower - motorDifference));
    }
    else
    {
      if (motorPower - motorDifference < 0)
      {
        digitalWrite(motorRpin1, LOW);
        digitalWrite(motorRpin2, HIGH);
      }
      analogWrite(motorLPWM, abs(motorPower - motorDifference));
      analogWrite(motorRPWM, motorPower);
      analogWrite(motorMPWM, motorPower);
    }
  }

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
    analogWrite(motorMPWM, 0);
    // digitalWrite(motorControl2, HIGH);
    delay(50);
  }

  if (GamePad.isCirclePressed())
  {
    Serial.print("Circle");
    analogWrite(motorMPWM, 0);
    //  digitalWrite(motorControl1, HIGH);
    delay(50);
  }

  if (GamePad.isCrossPressed())
  {
    Serial.print("Cross");
    analogWrite(motorMPWM, 0);
    digitalWrite(motorLpin1, HIGH);
    digitalWrite(motorLpin2, LOW);
    digitalWrite(motorRpin1, LOW);
    digitalWrite(motorRpin2, HIGH);
    analogWrite(motorLPWM, 255);
    analogWrite(motorRPWM, 255);
    delay(20);
  }

  if (GamePad.isTrianglePressed())
  {
    Serial.print("Triangle");
    analogWrite(motorMPWM, 0);
    digitalWrite(motorLpin1, LOW);
    digitalWrite(motorLpin2, HIGH);
    digitalWrite(motorRpin1, HIGH);
    digitalWrite(motorRpin2, LOW);
    analogWrite(motorLPWM, 255);
    analogWrite(motorRPWM, 255);
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
  int r = GamePad.getRadius();
  Serial.print("Radius: ");
  // Serial.print(b);
  Serial.print('\t');
  // float x = GamePad.getXaxisData();
  Serial.print("x_axis: ");
  Serial.print(x);
  Serial.print('\t');
  // float y = GamePad.getYaxisData();
  Serial.print("y_axis: ");
  Serial.println(y);
  Serial.println();
}
