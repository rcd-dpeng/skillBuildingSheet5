"""
@file stepperutilites.py Responsible for holding all utilities (chip statuses, predefined steppers) used with the Slush Engine
"""
from collections import OrderedDict

"""
Slush Engine Chip Statuses. These values are based of the Slush Engine Chip Status register reading
"""

"""MSB to LSB of motor controller status and index of the associated bit (16 bit number) for Slush Engine model XLT"""
CHIP_STATUSES_XLT = OrderedDict([
        ('SCK_MOD:     Step Clock Mode is an active high flag indicating that the device is working in Step-clock mode.\n\t\t\t In this case the step-clock signal should be provided through the STCK input pin.', 0),
        ('STEP_LOSS_B: Step Loss B is forced low when a stall is detected on bridge B.', 1),
        ('STEP_LOSS_A: Step Loss A is forced low when a stall is detected on bridge A.', 2),
        ('OCD:         Over Current is active low and indictes a overcurrent detection event.', 3),
        ('TH_SD:       Thermal Shutdown is active low and indicates a thermal shutdown event.', 4),
        ('TH_WRN:      Thermal Warning is active low and indicates a thermal warning event.', 5),
        ('UVLO:        Under Voltage Lock Out is active low and is set by an undervoltage lockout or reset events (power-up included).', 6),
        ('WRONG_CMD:   Wrong Command is active high and indicates that the command received by SPI does not exist.', 7),
        ('NOTPERF_CMD: Not Performed Command is active high and indicates that the command received by SPI cannot be performed.', 8),
        ('MOT_STATUS:  Motor Status (1 and 2) indicates the current motor status\n\t\t\t(0b00 = stopped, 0b01 = acceleration, 0b10 = deceleration, 0b11 = constant speed.', (9, 10)),
        ('DIR:         Direction indicates the current motor direction (1 = Forward, 0 = Reverse).', 11),
        ('SW_EVN:      Switch Turn On Event is active high and indicates a switch turn-on event (SW input falling edge).', 12),
        ('SW_F:        Switch Input Status reports the switch input status (low for open and high for closed).', 13),
        ('BUSY:        Device Busy is low when a constant speed, positioning or motion command is\n\t\t\tunder execution and is released (high) after the command has been completed.', 14),
        ('HiZ:         High Z (Impedance) State flag is high, it indicates that the bridges are in high impedance state.', 15)])

"""MSB to LSB of motor controller status and index of the associated bit (16 bit number) for Slush Engine Model D"""
CHIP_STATUSES_D = OrderedDict([
        ('STEP_LOSS_B: Step Loss B is forced low when a stall is detected on bridge B.', 0),
        ('STEP_LOSS_A: Step Loss A is forced low when a stall is detected on bridge A.', 1),
        ('OCD:         Over Current is active low and indicates a overcurrent detection event.', 2),
        ('TH_STATUS:   Thermal Shutdown (bit 3) is active low and indicates a thermal shutdown event.\nThermal Warning (bit 4) is active low and indicates a thermal warning event.', (3,4)),
        ('UVLO_ADC\\', 5),
        ('UVLO:        Under Voltage Lock Out is active low and is set by an undervoltage lockout or reset events (power-up included).', 6),
        ('SCK_MOD:     Step Clock Mode is an active high flag indicating that the device is working in Step-clock mode.\n\t\t\t In this case the step-clock signal should be provided through the STCK input pin.', 7),

        ('CMD_ERROR:   Wrong Command is active high and indicates that the command received by SPI does not exist.', 8),
        ('MOT_STATUS:  Motor Status (1 and 2) indicates the current motor status\n\t\t\t(0b00 = stopped, 0b01 = acceleration, 0b10 = deceleration, 0b11 = constant speed.', (9, 10)),
        ('DIR:         Direction indicates the current motor direction (1 = Forward, 0 = Reverse).', 11),
        ('SW_EVN:      Switch Turn On Event is active high and indicates a switch turn-on event (SW input falling edge).', 12),
        ('SW_F:        Switch Input Status reports the switch input status (low for open and high for closed).', 13),
        ('BUSY:        Device Busy is low when a constant speed, positioning or motion command is\n\t\t\tunder execution and is released (high) after the command has been completed.', 14),
        ('HiZ:         High Z (Impedance) State flag is high, it indicates that the bridges are in high impedance state.', 15)])

"""
Predefined Stepper Motors.

These are Stepper Motors where the settings are known and have been optimized. The aforementioned values are held in a dictionary.
"""

"""Nema 17 Stepper Motor Settings"""
NEMA_17 = {
    'hold_current': 8,
    'run_current': 10,
    'acc_current': 10,
    'dec_current': 10,
    'max_speed': 525,
    'min_speed': 0,
    'micro_steps': 32,
    'threshold_speed': 1000,
    'over_current': 2000,
    'stall_current': 2187.5,
    'accel': 0x50,
    'decel': 0x10,
    'low_speed_opt': False,
    'slope': [0x562, 0x010, 0x01F, 0x01F]
    }

"""Nema 23 Stepper Motor settings"""
NEMA_23 = {
    'hold_current': 8,
    'run_current': 51,
    'acc_current': 51,
    'dec_current': 51,
    'max_speed': 500,
    'min_speed': 100,
    'micro_steps': 2,
    'threshold_speed': 1000,
    'over_current': 1500,
    'stall_current': 1531.25,
    'accel': 0x10,
    'decel': 0x10,
    'low_speed_opt': False,
    'slope': [0x102, 0xB0B, 0x0E1, 0x0E1]
    }

"""Nema 23 Planetary Stepper Motor settings"""
NEMA_23_PLANETARY = {
    'hold_current': 8,
    'run_current': 43,
    'acc_current': 43,
    'dec_current': 43,
    'max_speed': 500,
    'min_speed': 0,
    'micro_steps': 2,
    'threshold_speed': 1000,
    'over_current': 3000,
    'stall_current': 3031.25,
    'accel': 0x01,
    'decel': 0x01,
    'low_speed_opt': False,
    'slope': [0x08BB, 0x02A, 0x06F, 0x06F]
    }
