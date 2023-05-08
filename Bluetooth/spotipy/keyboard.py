import pyautogui as py

class KeyboardBot():
    def __init__(self):
        pass
    def next_track(self):
        print("Skipping...")
        py.press('nexttrack') 

    def Prev_track(self):
        print("Previous track...")
        py.press('prevtrack') 

    def play(self):
        print("Pausing...")
        py.press('playpause') 

    def pause(self):
        print("Pausing...")
        py.press('playpause') 
    
    def vol_up(self):
        print("Vol up")
        py.press('volumeup') 
            
    def vol_down(self):
        print("Vol down")
        py.press('volumedown') 
    
    def run_command(self,command):
        #   'O' = default, none
        #   'N' = next track
        #   'P' = prev track
        #   'S' = pause track
        #   'V' = set volume
        #   'U' = volume up
        #   'D' = volume down
        if command == 'N':
            self.next_track()
            return
        if command == 'P':
            self.Prev_track()
            return
        if command == 'S':
            self.pause()
            return
        if command == 'S':
            self.play()
            return
        if command == 'U':
            self.vol_up()
            return
        if command == 'D':
            self.vol_down()
            return
        return
