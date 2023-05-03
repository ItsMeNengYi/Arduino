import serial

class BluetoothBot():
    def __init__(self):
        self.ser = serial.Serial("COM7",9600)
    def send_current_track(self,track):
        self.ser.write(b"[")
        track_bytes = track.encode('utf-8') 
        self.ser.write(track_bytes)
        self.ser.write(b"]")

    def get_command(self):
        data = self.ser.readline(1024)
        if data:
            return data
        return 'O'
    def close(self):
        self.ser.close()

            

    