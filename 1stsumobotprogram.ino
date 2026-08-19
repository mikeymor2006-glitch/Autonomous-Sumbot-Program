# The code below is the SumoBot program I used for the 2025 YURS SumoBot Competition.
#define PWMB 6
#define IN1B 4
#define IN2B 5
#define PWMA 11
#define IN1A 10
#define IN2A 9

int trig = 2;
int echo = 7;
long duration;
const float SOUND_SPEED = 0.0343;
float distance;

int serialpin = 5;
int serialpin2 = 4;
int sensorValue;
int sensorValue2;
int threshold2 = 200;
int threshold1 = 200;

void setup() {
  // put your setup code here, to run once:
  pinMode(PWMB, OUTPUT);
  pinMode(IN1B, OUTPUT);
  pinMode(IN2B, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(IN1A, OUTPUT);
  pinMode(IN2A, OUTPUT);
  delay(5000);

  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void moveForward(int speed) {
    digitalWrite(IN1B, LOW);
    digitalWrite(IN2B, HIGH);
    analogWrite(PWMB, speed);

    digitalWrite(IN1A, HIGH);
    digitalWrite(IN2A, LOW);
    analogWrite(PWMA, speed);

    if (distance > 50) {
      analogWrite(PWMB,0);
      analogWrite(PWMA,0);
    }
    else if (distance <= 50 && distance >= 30){
      analogWrite(PWMB, 100);
      analogWrite(PWMA, 100);
    } 
    else if (distance < 30 && distance >= 15) {
      analogWrite(PWMB, 250);
      analogWrite(PWMA, 250);
    } 
    else if (distance < 15){
    analogWrite(PWMB, 350);
    analogWrite(PWMA, 350);
    } 
  }

void moveBackward(int speed) {
  digitalWrite(IN1B, HIGH);
  digitalWrite(IN2B, LOW);
  analogWrite(PWMB, speed);

  digitalWrite(IN1A, LOW);
  digitalWrite(IN2A, HIGH);
  analogWrite(PWMA, speed);
}

void turnClockWise(int speed) {
  digitalWrite(IN1B, HIGH);
  digitalWrite(IN2B, LOW);
  analogWrite(PWMB, speed);

  digitalWrite(IN1A, HIGH);
  digitalWrite(IN2A, LOW);
  analogWrite(PWMA, speed);
}

void turnCounterClockWise(int speed) {
  digitalWrite(IN1B, LOW);
  digitalWrite(IN2B, HIGH);
  analogWrite(PWMB, speed);

  digitalWrite(IN1A, LOW);
  digitalWrite(IN2A, HIGH);
  analogWrite(PWMA, speed);
}

void calculateDistance()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * SOUND_SPEED / 2;
  Serial.print("distance: ");
  Serial.println(distance);
  delay(50);
}
void DetectingBackLine(){
     sensorValue = analogRead(serialpin);
     sensorValue2 = analogRead(serialpin2);
     if (sensorValue > threshold1) {
       Serial.println(sensorValue);
   } else if (sensorValue < threshold1) {
       Serial.println(sensorValue);
       Serial.println("this is white");
       analogWrite(PWMB, 0);
       analogWrite(PWMA, 0);
   }

    if (sensorValue2 > threshold2) {
       Serial.println(sensorValue2);
     
  } else if (sensorValue2 < threshold2) {
       Serial.println(sensorValue2);
       Serial.println("this is white");
       analogWrite(PWMB, 0);
       analogWrite(PWMA, 0);

  }
  delay(600);
}


void loop() {
  // put your main code here, to run repeatedly:
  calculateDistance();
  moveForward(200);
  DetectingBackLine();
}
