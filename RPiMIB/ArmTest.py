import Slush
b = Slush.sBoard()

current = 45 # 77
current2 = 40
microStepping = 1
shoulderM = Slush.Motor(0)
elbowM = Slush.Motor(1)
wristM = Slush.Motor(2)

shoulderM.resetDev()
shoulderM.setCurrent(current,current,current,current)
shoulderM.setMicroSteps(microStepping)
shoulderM.setMaxSpeed(200 * microStepping)
#m1.setOverCurrent(375 * 11)
shoulderM.setOverCurrent(6000)

elbowM.resetDev()
elbowM.setCurrent(current2,current2,current2,current2)
elbowM.setMicroSteps(microStepping)
elbowM.setMaxSpeed(200 * microStepping * 5)
elbowM.setOverCurrent(4000)

wristM.resetDev()
wristM.setCurrent(current2,current2,current2,current2)
wristM.setMicroSteps(microStepping)
wristM.setMaxSpeed(200 * microStepping * 5)
wristM.setOverCurrent(4000)


shoulderM.move(-100) #(-) is up
#elbowM.move(500) #(-) up
#wristM.move(-300) #(-) up
while shoulderM.isBusy() or elbowM.isBusy():
    continue

#shoulderM.free()
#elbowM.free()
