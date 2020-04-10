#include "res.h"

#include "calculations.h"

/*
   added adjustments for BPM and the Tidal Volume
   Readme:

   BPS: = 60/BPM
   TI=BPS/3
   T0=BPS*(2/3)
   EG: BPS=60/10(10bpm)=6
   TI=6/3=2;
   T0=6*2/3=4
   TI=2, TE=4;

  Change these const int values for delays and homing speed as required
  Change
    while(digitalRead(HOME_LIMIT))
    To

    while(!digitalRead(HOME_LIMIT))
    for Active Hight Limit switch
    In returnToHome Function.

  //int dummy_Pot1=255; //uncomment this line if you want to test without POT



*/

const int HOMING_SPEED = 80; //change to adjust
const int waitAfterForward = 100; //change to adjust millisecnds~ 0.1s
const int waitAfterBackward = 100;

int current_pwm = 0;


void returnToHome() {

  if (!digitalRead(HOME_LIMIT)) {
    //while homing limit switch is not triggered, move motor reverse slowly

    while (!limit) {
      // statement
      Serial.println("Homing in process...");
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(PWM, HOMING_SPEED);
      delay(100);
    }
    Serial.println("Homing done!");
    discStop();
    limit = 0;
    at_home = 1; //homing complete
  }
  else {
    at_home=1;
  }
}
void updateValues() {
  convertBPS();

  int dummy_Pot2 = analogRead(POT_2);
  //  int dummy_Pot1=255; //uncomment this line if you want to test without POT
  //  Serial.print("POT1");
  //  Serial.println(dummy_Pot1);

  current_pwm = map(dummy_Pot2, 0, 1023, scaled_pwm_min, scaled_pwm_max); //need to re-think from_mapping values.
  Serial.println("Current PWM");
  Serial.println(current_pwm);

}

void initInterrupts() {
  //interruptsfor buttons
  attachInterrupt(digitalPinToInterrupt(HOME_LIMIT), homeRoutine, RISING);
  attachInterrupt(digitalPinToInterrupt(STOP), haltRoutine, CHANGE);

}


void discRotateFWD() {
  //check polarity of output/input pins if the motor goes reverse first.
  analogWrite(PWM, current_pwm);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}


void discRotateBWD() {
  //return at half the rate for 1:2 I:E ratio
  analogWrite(PWM, current_pwm / 2);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}



void haltRoutine() {
  stop_flag = 1;
  discStop();

  Serial.println("STOP");
}

void homeRoutine() {
  limit = 1;
  Serial.println("Limit reached!");
}


void startRoutine() {
  Serial.println("START");
  disable = 0;
  start_flag = 1;
}

void initPins() {
  //home_limit is internal pullup 5V, 20K pull up resistor from controller.
  pinMode(HOME_LIMIT, INPUT);
  pinMode(STOP, INPUT);
  pinMode(START, INPUT);

  //set motor control pins output
  pinMode(PWM, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  Serial.println("Initialization done!");
}

void setup()
{

  Serial.begin(9600);
  analogReference(DEFAULT);
  initPins();
  initInterrupts();
  //for START INT:

  //initializations finish
  delay(500);
  returnToHome();


}


void discStop() {
  Serial.println("Disc Stopped");
  analogWrite(PWM, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}


void loop()
{
  updateValues();

  if (!digitalRead(START)) {
    startRoutine();
  }
  if (stop_flag) {
    at_home = 0;
    returnToHome();
    disable = 1;
    stop_flag = 0;
    Serial.println("STOP TRIGGERD");
  }

  //if start button is on and homing is done
  if ((!disable) && (start_flag) && (at_home)) {
    Serial.println("Inside rotation ");

    //cycle as per PWM value
    //assume position is not at home everytime for flag errors

    updateValues(); //get new values
    //until the stop button is pressed, do rotations.

    while (!stop_flag) {
      Serial.println("Inside rotation while");
      updateValues();
      discRotateFWD(); //start rotation forward
      delay(delay_valueTI);  //inhale value
      discStop(); //stop disc momentarily
      delay(waitAfterForward); //wait time after forward cycle, change as required in declaration in top of pgm
      while (!digitalRead(HOME_LIMIT)) {
        discRotateBWD();
      }
      //    discRotateBWD();
      //    delay(delay_valueTE);
      discStop();
      delay(waitAfterBackward);
    }

  }

}
