import sys
import Slush
from Slush.Devices import L6470Registers as LReg
from .slush_manager import slush_board as b
b = Slush.sBoard()

class stepper(Slush.Motor):

    '''
    The init function sets a range of parameters:
    port, micro_steps, run_current, accel_current, deaccel_current
    hold_current, steps_per_unit, speed

    There are 2 ways to change them:
    1) in the constructor ex) arm = stepper (port = 0, run_current = 5)
    2) change it within main code by calling set functions ex) arm.set_speed(100)
    '''

    def __init__(self, **kwargs):
        super().__init__(kwargs.get("port", 0))
        self.resetDev()
        self.micro_steps = kwargs.get("micro_steps", 64)
        self.set_micro_steps(self.micro_steps)
        self.setCurrent(kwargs.get("hold_current", 20),
                        kwargs.get("run_current", 20),
                        kwargs.get("accel_current", 20),
                        kwargs.get("deaccel_current", 20))
        self.steps_per_unit = kwargs.get("steps_per_unit", 200 / 25.4)
        self.speed = kwargs.get("speed", 1)
        self.set_speed(self.speed)
        self.getParam(LReg.CONFIG) == 0x2e88
        # Allow for GPIO on the slushengine

    '''
    these are the functions used to change parameters
    '''
    def get_micro_steps(self):
        return self.micro_steps

    def set_micro_steps(self, micro_steps):
        if(micro_steps > 128):
            sys.exit("ERROR: Slush Engine only supports microstepping values of base 2 up to a maximum of 128")

        self.micro_steps = micro_steps
        self.setMicroSteps(micro_steps)

    def set_speed(self, speed):
        self.speed = speed * self.steps_per_unit
        self.set_max_speed(self.speed)

    def set_accel(self, acceleration):
        self.setAccel(acceleration)

    def set_deaccel(self, deceleration):
        self.setDecel(deceleration)

    '''
    -moves until the switch is triggered
    -dependent on a direction: 0 or 1
    '''
    def home(self, direction):
        self.run(direction, self.speed)

        while self.read_switch() == False:
            continue

        self.hard_stop()
        self.set_as_home()

    '''
    reads the switch in the respective port
    '''

    def read_switch(self):
        if self.getStatus() & 0x4: return 1
        else: return 0

    '''
    moves a certain distance with movements blocked (synchronise)
    '''
    def relative_move(self, distance):
        number_of_steps = distance * self.micro_steps * self.steps_per_unit
        self.move(int(number_of_steps))
        self.wait_move_finish()

    '''
    starts moving a certain distance without blocking movements (a-synchronise)
    '''
    def start_relative_move(self, distance):
        number_of_steps = distance * self.micro_steps * self.steps_per_unit
        self.move(int(number_of_steps))

    '''
    Goes to a set position with blocking (synchronise)
    '''
    def go_to_position(self, distance):
        number_of_steps = distance * self.micro_steps * self.steps_per_unit
        self.go_to(int(number_of_steps))
        self.wait_move_finish()


    '''
    begins going to a set position without blocking (a-synchronise)
    '''
    def start_go_to_position(self, distance):
        number_of_steps = distance * self.micro_steps * self.steps_per_unit
        self.go_to(int(number_of_steps))


    '''
    returns the state of a sensor/switch  
    port:   a = 0; b = 1
    pin: first pin = 0, goes up by 1 per pin
    '''
    def get_GPIO_state(self, port, pin):
        return b.getIOState(port, pin)

    def set_GPIO_state(self, port, pin, state):
        return b.setIOState(port, pin, state)

    '''
    hard stops the motor
    '''
    def stop(self):
        self.hard_stop()

    '''
    helper Functions:
    motor.py is Camel Case
    stepper.py is underscore
    
    stepper extends motors so must adjust the functions accordingly
    '''
    def hard_stop(self):
        self.hardStop()

    def go_to(self, number_of_steps):
        self.goTo(number_of_steps)

    def wait_move_finish(self):
        self.waitMoveFinish()

    def set_as_home(self):
        self.setAsHome()

    def set_max_speed(self, speed):
        self.setMaxSpeed(speed)

    '''
    Some other helpful functions from motor that may be used
    
    run (self, dir, spd)
    
    goToDir (self, dir,pos) #same as goTo but with direction
    
    '''
