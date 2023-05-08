from spotify import SpotifyBot
from bluetooth import BluetoothBot
from keyboard import KeyboardBot
import sys

spot = SpotifyBot()
blue = BluetoothBot()
key = KeyboardBot()

def main():
    try:
        current_playing = spot.get_current_track()
        blue.send_current_track(current_playing)
        while (True):
            spot.run_command(blue.get_command())
            if(current_playing!=spot.get_current_track()):
                current_playing = spot.get_current_track()
                blue.send_current_track(current_playing)
    except:
        if(KeyboardInterrupt):
            blue.close()
            return
        print("ERROR",sys.exc_info()[0])
        main()


main()
