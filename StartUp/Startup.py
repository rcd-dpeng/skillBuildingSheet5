#!/usr/bin/python3

# ////////////////////////////////////////////////////////////////
# //                     IMPORT STATEMENTS                      //
# ////////////////////////////////////////////////////////////////

from pidev.stepper import stepper

# Init a 200 steps per revolution stepper on Port 0
S0 = stepper(port=0, micro_steps=32, hold_current=20, run_current=20, accel_current=20, deaccel_current=20,
             steps_per_unit=200, speed=10)

# Init a 1036 steps per revolution stepper on Port 1 - this is for a stepper with a 5.18:1 planetary transmission
# https://www.omc-stepperonline.com/economy-planetary-gearbox/nema-17-stepper-motor-bipolar-l48mm-w-gear-raio-51-planetary-gearbox-17hs19-1684s-pg5.html?mfp=161-motor-nema-size%5BNema%2017%5D
s1 = stepper(port=1, micro_steps=32, hold_current=20, run_current=20, accel_current=20, deaccel_current=20,
             steps_per_unit=1038, speed=10)

# Init a 200 steps per revolution stepper on Port 2 with a lead screw that moves 8mm per revolution
# (200 steps/1 rev)* (1 rev/8 mm) which simplifies to 25 steps/mm giving us 25 for our steps_per_unit value
# https://www.pololu.com/product/2268
s2 = stepper(port=2, micro_steps=32, hold_current=20, run_current=20, accel_current=20, deaccel_current=20,
             steps_per_unit=25, speed=10)

s0.relative_move(1)
s1.relative_move(1)
s2.relative_move()