import serial

# try:
#     ser = serial.Serial("COM7",9600)
#     ser.write(b'hello')
#     x=1
#     # while True:
#     #     data = ser.readline(1024)
#     #     if data:
#     #         print(data)
#     #         break
#     #     if(x>100):
#     #         break
#     #     x+=1

# except TimeoutError:
#     print("error")
# finally:
#     print("done")

class BluetoothBot():
    def __init__(self):
        self.ser = serial.Serial("COM7",9600)
    def send_current_track(self,track):
        track_bytes = track.encode('utf-8') 
        self.ser.write(track_bytes)
    
    