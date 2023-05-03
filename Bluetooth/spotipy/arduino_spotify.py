from spotify import SpotifyBot
from bluetooth import BluetoothBot
import time

spot = SpotifyBot()
blue = BluetoothBot()


current_playing = spot.get_current_track()
blue.send_current_track(current_playing)
start_time = time.time()
while (True):
    if(current_playing!=spot.get_current_track()):
        current_playing = spot.get_current_track()
        blue.send_current_track(current_playing)
    
    current_time = time.time() 
    elapsed_time = current_time - start_time
    if(elapsed_time>2*60):
        break
    time.sleep(1)