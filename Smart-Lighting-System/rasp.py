import serial

'''
    Reads data coming from the Arduino via serial 
    connection and controls the LEDs.
'''

# Configure the serial port
ser = serial.Serial('/dev/ttyACM0', 9600) # TODO Replace '/dev/ttyACM0' with the serial port of your Arduino

# TODO Control the LEDs based on the data received.
def control_leds():
    pass

# Read data from the serial port
while True:
    data = ser.readline().decode('utf-8').strip()
    control_leds()
    print(data)