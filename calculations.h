const float MIN_BPM = 12.0;
const float MAX_BPM = 22.0;
const float MAX_BREATH_DELAY = 1666;

float BPM = 0.0;
float BPS = 0.0;
float TI = 0.0;
float TE = 0.0;
float pwm_factor = 0.0;

int delay_valueTI = 0;
int delay_valueTE = 0;

int scaled_pwm_min = 0;
int scaled_pwm_max = 0;

float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void convertBPS() {

  //converts the given BPS to respective Delay values as per POT_1 value

  float dummy_POT1 = analogRead(POT_1);
  BPM = mapf(dummy_POT1, 0.0, 1023.0, 12.0, 22.0);


  BPS = 60 / BPM;
  TI = BPS / 3.0;
  TE = BPS * (2.0 / 3.0);
  //for converting it into milliseconds
  delay_valueTI = TI * 1000;
  delay_valueTE = TE * 1000;
  if (BPM != MIN_BPM) {
    //find new pwm factor.
    pwm_factor = MAX_BREATH_DELAY / delay_valueTI;


  }
  else {
    //max PWM factor is always 1.83 for max range of 22.
    pwm_factor = 1.83;

  }
    Serial.println("delay_valueTI");
    Serial.println(delay_valueTI);

  scaled_pwm_min = 25 * pwm_factor;
  scaled_pwm_max = 128 * pwm_factor; //assuming it reaches the 100% compression at 128
  //Serial.println("scaled_pwm_min");
  //  Serial.println(scaled_pwm_min);
  //  Serial.println("scaled_pwm_max");
  //  Serial.println(scaled_pwm_max);
delay(500);
}
