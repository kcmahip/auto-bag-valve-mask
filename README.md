# auto-bag-valve-mask
Automatically controlled bag valve mask which helps free up trained medical personnels and can attend to some patients somewhere else. 
I
t assumes that the full compression (full volume air pressed) happens at 12 BPM: 1666ms (inhale time) at  128 PWM value. This PWM value has to be under 128 but can be any range. But best is to keep at 128 by changing the mechanical dimensions, most probably reducing the distance of the shaft.

So from arduino we have to give 1666ms delay and 128 pwm value. If Voltage of motor, load etc is constant, mechanically we should achieve full compression.

Once this is done, all the PWM values are scaled in certain ratios so that there is adjustable Volume and BPM.


1st Testing version uses DC motor, a mechanical setup to convert DC motor rotations to BVM compressions and a BVM. Start & Stop buttons. 


Adjustable Parameters: 
BPM(Breaths Per Minute) & Tidal Volume Via. Potentiometer. 
I:E Ratio by changing it software. 

Min BPM: 12.
Max BPM: 22.

TODO:
Adjust Mechanical system, shaft length, vibrations 
I:E Ratio change by Potentiometer.

Still in initial phase. This is NOT a DIY Ventilator. 
