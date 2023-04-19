import serial

print("HI")
try:
    ser = serial.Serial("COM7",9600)
    ser.write(b'C')
    x=1
    while True:
        print(x)
        data = ser.readline(1024)
        if data:
            print(data)
            break
        x+=1

except TimeoutError:
    print("error")
finally:
    print("done")
