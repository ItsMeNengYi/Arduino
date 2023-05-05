from spotify import SpotifyBot
from bluetooth import BluetoothBot
import time

spot = SpotifyBot()
blue = BluetoothBot()


current_playing = spot.get_current_track()
blue.send_current_track(current_playing)
try:
    while (True):
        spot.run_command(blue.get_command())
        if(current_playing!=spot.get_current_track()):
            current_playing = spot.get_current_track()
            blue.send_current_track(current_playing)

except:
    blue.close()
