import Slush
from Slush.Devices import L6470Registers as LReg
from .slush_manager import slush_board as b
b = Slush.sBoard()

class Stepper(Slush.Motor):

    # Stepper constructor, if no parameter is specified they will default
    # to given values
    
    def __init__(self, **kwargs):
        super().__init__(kwargs.get("port", 0))
        self.resetDev()
        self.micro_steps = kwargs.get("micro_steps", 64)
        self.set_micro_steps(self.micro_steps)
        self.setCurrent(kwargs.get("runCurrent", 20),
                        kwargs.get("accelCurrent", 20),
                        kwargs.get("deaccelCurrent", 20),
                        kwargs.get("holdCurrent", 20))
        self.steps_per_unit = kwargs.get("steps_per_unit", 200 / 25.4)
        self.speed = kwargs.get("speed", 1)
        self.set_speed(self.speed)
        self.getParam(LReg.CONFIG) == 0x2e88
        # Allow for GPIO on the slushengine

    def get_micro_steps(self):
        return self.micro_steps

    def set_micro_steps(self, micro_steps):
        self.micro_steps = micro_steps

    def set_speed(self, speed):
        self.speed = speed * self.steps_per_unit
        self.set_max_speed(self.speed)

    def home(self, direction):
        self.run(direction, self.speed)

        while self.read_switch() == False:
            continue

        self.hard_stop()
        self.set_as_home()
 
    def read_switch(self):
        if self.getStatus() & 0x4: return 1
        else: return 0

    #relative move that blocks movement
    def relative_move(self, distance):
        number_of_steps = distance * self.micro_steps * self.steps_per_unit
        self.move(int(number_of_steps))
        self.wait_move_finish()

    #start relative move that does not block movements
    def start_relative_move(self, distance):
        number_of_steps = distance * self.micro_steps * self.steps_per_unit
        self.move(int(number_of_steps))

    #goes to position while blocking other movements
    def go_to_position(self, distance):
        number_of_steps = distance * self.micro_steps * self.steps_per_unit
        self.go_to(int(number_of_steps))
        self.wait_move_finish()

    #goes to position with no blocking
    def start_go_to_position(self, distance):
        number_of_steps = distance * self.micro_steps * self.steps_per_unit
        self.go_to(int(number_of_steps))

    def get_GPIO_state(self, port, pin):
        return b.get_IO_state(port, pin)

    def set_GPIO_state(self, port, pin, state):
        return b.set_IO_state(port, pin, state)

    def stop(self):
        self.hard_stop()

    def hard_stop(self):
        self.hardStop()

    def go_To(self,number_of_steps):
        self.gotTo(number_of_steps)

    def wait_move_finish(self):
        self.waitMoveFinish()

    def set_as_home(self):
        self.setAsHome()

    def set_max_speed(self,speed):
        self.setMaxSpeed(speed)

    
    
