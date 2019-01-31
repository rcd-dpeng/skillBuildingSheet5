import time
import sys
import odrive
from odrive.enums import *

# Used to make using the ODrive easier Version 1.2.2
# Last update October 18, 2018 by Blake Lazarine

odrv0 = None


def find_odrive():
    global odrv0
    if odrv0 is None:
        print('ODrive Ease Lib 1.3.2')
        odrv0 = odrive.find_any()
    return odrv0


# Used to make using the ODrive easier Version 1.3.2
# Last update October 18, 2018 by Blake Lazarine

class ODriveAxis(object):

    def __init__(self, axis):
        self.axis = axis
        self.zero = 0;
        self.axis.controller.config.vel_limit = 20000

    def calibrate(self):
        self.axis.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE
        start = time.time()
        while self.axis.current_state != AXIS_STATE_IDLE:
            time.sleep(0.1)
            if time.time() - start > 15:
                print("could not calibrate, try rebooting odrive")
                return False

    def is_calibrated(self):
        return self.axis.motor.is_calibrated

    def set_vel(self, vel):
        self.axis.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL
        self.axis.controller.config.control_mode = CTRL_MODE_VELOCITY_CONTROL
        self.axis.controller.vel_setpoint = vel

    def set_vel_limit(self, vel):
        self.axis.controller.config.vel_limit = vel

    def get_vel_limit(self):
        return self.axis.controller.config.vel_limit

    def set_zero(self, pos):
        self.zero = pos

    def get_pos(self):
        return self.axis.encoder.pos_estimate - self.zero

    def get_raw_pos(self):
        return self.axis.encoder.pos_estimate

    def set_pos(self, pos):
        desired_pos = pos + self.zero
        self.axis.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL
        self.axis.controller.config.control_mode = CTRL_MODE_POSITION_CONTROL
        self.axis.controller.pos_setpoint = desired_pos

    def set_curr_limit(self, val):
        self.axis.motor.config.current_lim = val

    def get_curr_limit(self):
        return self.axis.motor.config.current_lim

    def set_current(self, curr):
        self.axis.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL
        self.axis.controller.config.control_mode = CTRL_MODE_CURRENT_CONTROL
        self.axis.controller.current_setpoint = curr

    def get_vel(self):
        return self.axis.encoder.pll_vel

    def set_pos_gain(self, val):
        self.axis.controller.config.pos_gain = val

    def get_pos_gain(self):
        return self.axis.controller.config.pos_gain

    def set_vel_gain(self, val):
        self.axis.controller.config.vel_gain = val

    def get_vel_gain(self):
        return self.axis.controller.config.vel_gain

    def set_vel_integrator_gain(self, val):
        self.axis.controller.config.vel_integrator_gain = val

    def get_vel_integrator_gain(self):
        return self.axis.controller.config.vel_integrator_gain

    def is_busy(self):
        if (abs(self.get_vel())) > 50:
            return True
        else:
            return False

    def go_to(self, pos, tolerance):
        self.set_pos(pos)
        while abs(self.get_pos() - pos) > tolerance:
            pass

    def set_calibration_current(self, curr):
        self.axis.motor.config.calibration_current = curr

    def get_calibration_current(self):
        return self.axis.motor.config.calibration_current

    # method to home ODrive using where the chassis is mechanically stopped
    # length is expected length of the track the ODrive takes
    # set length to -1 if you do not want the ODrive to check its homing
    # direction = 1 or -1 depending on which side of the track you want home to be at
    # use direction = 1 if you want the track to be of only positive location values
    def home(self, current1, current2, length=-1, direction=1, tolerance=50, delay=1):
        self.set_current(current1 * -1 * direction)
        # print('here')
        time.sleep(delay)
        # print('there')
        while self.is_busy():
            pass

        time.sleep(delay)

        self.set_zero(self.get_raw_pos())
        # print(self.get_pos())

        time.sleep(delay)

        if not length == -1:
            self.set_current(current2 * 1 * direction)
            time.sleep(delay)
            while self.is_busy():
                pass

            # end pos should be length
            if abs(self.get_pos() - length) > tolerance:
                print('ODrive could not home correctly: off by {}'.format(self.get_pos() - length))
                self.set_pos(0)
                return False

        self.set_pos(0)
        print('ODrive homed correctly')
        return True

    def home_with_vel(self, vel, length=-1, direction=1, tolerance=50, delay=1):
        self.set_vel(vel * -direction)
        time.sleep(delay)
        while self.is_busy():
            pass

        time.sleep(delay)

        self.set_zero(self.get_raw_pos())

        time.sleep(delay)

        if not length == -1:
            self.set_vel(vel * direction)
            time.sleep(delay)
            while self.is_busy():
                pass

            # end pos should be length
            if abs(self.get_pos() - length) > tolerance:
                print('ODrive could not home correctly: off by {}'.format(self.get_pos() - length))
                return False

        print('ODrive homed correctly')
        return True


if __name__ == "__main__":
    find_odrive()
    if odrv0 is None:
        sys.exit("Unable to find an odrive, the hardware trigger script")
    print(odrv0)
    odrv0.reboot()
