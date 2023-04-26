import serial

try:
    ser = serial.Serial("COM7",9600)
    for x in range(10):
        ser.write(b'C')
    x=1
    while True:
        ser.write(b'C')
        data = ser.readline(1024)
        if data:
            print(data)
            break
        x+=1

except TimeoutError:
    print("error")
finally:
    print("done")
