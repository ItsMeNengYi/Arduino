from spotify import SpotifyBot
from bluetooth import BluetoothBot
import sys

spot = SpotifyBot()
blue = BluetoothBot()

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
            return
        print("ERROR",sys.exc_info()[0])
        main()


main()
