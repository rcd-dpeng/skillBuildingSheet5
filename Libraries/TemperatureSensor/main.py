#!/usr/bin/python3

import TemperatureSensor

tempSensor = TemperatureSensor.TemperatureSensor()
	
tempF = tempSensor.getTemperatureInFahrenheit()
tempC = tempSensor.getTemperatureInCelsius()

print("Temperature in Fahrenheit is : %.2f F" %tempF)
print("Temperature in Fahrenheit is : %.2f C" %tempC)

input("Press any key to exit")
exit()
