import sys
from collections import OrderedDict
import Slush
from Slush.Devices import L6470Registers as LReg
from .slush_manager import slush_board as b

b = Slush.sBoard()


class stepper(Slush.Motor):

    def __init__(self, **kwargs):
        """
        Constructor for a stepper motor on the Slush Engine
        he init function sets a range of parameters:
        port, micro_steps, run_current, accel_current, deaccel_current
        hold_current, steps_per_unit, speed
        :param kwargs: Reference note on constructor summary
        """
        super().__init__(kwargs.get("port", 0))
        self.port = kwargs.get("port", 0)
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
        self.getParam(LReg.CONFIG) == 0x2e88  # Allow for GPIO on the slushengine

    def print_status(self):
        """
        Print all of the registers status for the L6470 chipset, if a status has a \ means it is active low
        :return: None
        """
        chip_statuses = OrderedDict([
            ('SCK_MOD', 1),
            ('STEP_LOSS_B\\', 1),
            ('STEP_LOSS_A\\', 1),
            ('OCD\\', 1),
            ('TH_SD\\', 1),
            ('TH_WRN\\', 1),
            ('UVLO\\', 1),
            ('WRONG_CMD', 1),
            ('NOTPERF_CMD', 1),
            ('MOT_STATUS', 2),
            ('DIR', 1),
            ('SW_EVEN', 1),
            ('SW_F', 1),
            ('BUSY\\', 1),
            ('HiZ', 1)])

        byte = '{0:b}'.format(self.getStatus())

        if len(byte) != 16:  # Add leading zeroes to the byte to make it 16 bits
            diff = 16 - len(byte)
            byte = "0" * diff + byte

        print("The byte for ", str(self), "is: ", byte)

        location = 0

        for status in chip_statuses:
            data = ""
            for i in range(0, chip_statuses[status]):
                data += str(int(byte[location]))
                location += 1
            print(status + ": " + data)

    def get_micro_steps(self):
        """
        Get the number of microsteps the stepper motor is running at
        :return:
        """
        return self.micro_steps

    def set_micro_steps(self, micro_steps):
        """
        Set the number of microsteps the stepper motor runs at
        :param micro_steps: Number of microsteps of base 2 up to a maximum of 128
        :return: None
        """
        if micro_steps > 128:
            sys.exit("ERROR: Slush Engine only supports microstepping values of base 2 up to a maximum of 128")

        self.micro_steps = micro_steps
        self.setMicroSteps(micro_steps)

    def set_speed(self, speed):
        """
        Set the speed the stepper motor runs at
        :param speed: Speed the motor will run at
        :return: None
        """
        self.speed = speed * self.steps_per_unit
        self.set_max_speed(self.speed)

    def set_accel(self, acceleration):
        """
        Set the acceleration of the motor
        :param acceleration: Acceleration amount
        :return: None
        """
        self.setAccel(acceleration)

    def set_deaccel(self, deceleration):
        """
        Set the deceleration for the motor
        :param deceleration: Deceleration amount
        :return: None
        """
        self.setDecel(deceleration)

    def home(self, direction):
        """
        Home the motor
        :param direction: Direction (0 or 1) the motor should spin when homing 0-clockwise
        :return: None
        """
        self.run(direction, self.speed)

        while not self.read_switch():
            continue

        self.hard_stop()
        self.set_as_home()

    def read_switch(self):
        """
        Read the stepper motors corresponding switch
        :return: None
        """
        if self.getStatus() & 0x4:
            return 1
        else:
            return 0

    def relative_move(self, distance):
        """
        Moves a certain distance with MOVEMENTS BLOCKED (synchronise)
        :param distance:
        :return:
        """
        number_of_steps = distance * self.micro_steps * self.steps_per_unit
        self.move(int(number_of_steps))
        self.wait_move_finish()

    def start_relative_move(self, distance):
        """
        Starts moving a certain distance WITHOUT BLOCKING MOVEMENTS (a-synchronise)
        :param distance:
        :return:
        """
        number_of_steps = distance * self.micro_steps * self.steps_per_unit
        self.move(int(number_of_steps))

    def go_to_position(self, distance):
        """
        Goes to a set position WITH BLOCKING (synchronise)
        :param distance: Distance to move to
        :return: None
        """
        number_of_steps = distance * self.micro_steps * self.steps_per_unit
        self.go_to(int(number_of_steps))
        self.wait_move_finish()

    def start_go_to_position(self, distance):
        """
        begins going to a set position WITHOUT BLOCKING (a-synchronise)
        :param distance: distance to move to
        :return: None
        """
        number_of_steps = distance * self.micro_steps * self.steps_per_unit
        self.go_to(int(number_of_steps))

    @staticmethod
    def get_GPIO_state(port, pin):
        """
        Get the state of one of the GPIO pins
        :param port: GPIO port a=0, b=1
        :param pin: Pin to check, first pin=0 incrementing by one
        :return:
        """
        return b.getIOState(port, pin)

    @staticmethod
    def set_GPIO_state(port, pin, state):
        """
        Set the state of one of the GPIO pins
        :param port: GPIO port a=0, b=1
        :param pin: Pin to set, first pin=0 incrementing by one
        :param state: State you want to set the pin at
        :return: None
        """
        return b.setIOState(port, pin, state)

    '''
    If True motor with stop when sensor is high (Should be used in cases where there is a mechanical stop)
    If False motor will continue past sensor (Should be used when motor can rotate freely)
    '''

    def set_limit_hardstop(self, stop):
        """
        Set whether the Slush Engine should stop moving
        :param stop:
        :return:
        """
        try:
            self.setLimitHardStop(stop)
        except AttributeError:
            sys.exit("Update SlushEngine Code, this feature is only on recent versions")

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

    def wait_to_return(self):
        while self.isBusy():
            continue

    def __repr__(self):
        return "stepper on port" + str(self.port)

    '''
    Some other helpful functions from motor that may be used
    
    run (self, dir, spd)
    
    goToDir (self, dir,pos) #same as goTo but with direction
    
    '''
