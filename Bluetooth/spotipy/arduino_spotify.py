from spotify import SpotifyBot
from bluetooth import BluetoothBot
import time

spot = SpotifyBot()
blue = BluetoothBot()


current_playing = spot.get_current_track()
blue.send_current_track(current_playing)
start_time = time.time()
while (True):
    current_time = time.time() 
    elapsed_time = current_time - start_time
    # if(input()):
    #     print("END")
    #     blue.close()
    #     break
    # spot.run_command(blue.get_command())
    if(current_playing!=spot.get_current_track()):
        current_playing = spot.get_current_track()
        blue.send_current_track(current_playing)

    time.sleep(1)

