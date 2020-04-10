//potentiometers

#define POT_1 A0 //for Adjusting the BPM
#define POT_2 A1 //for adjusting the Tidal Volume
#define START 4
#define STOP 3
#define HOME_LIMIT 2

#define PWM 6
#define IN1 7
#define IN2 8

bool at_home=0;
volatile int stop_flag=0;
volatile int disable=1;
volatile int start_flag=1;
volatile int timer_up=0;
volatile int dir=0;
volatile int limit=0;
int time_multiplier=0;
int duty_value = 0;
unsigned long int time_value=0;
