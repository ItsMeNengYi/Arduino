from flask import Flask, request, url_for, session, redirect
import spotipy
from spotipy.oauth2 import SpotifyClientCredentials


class SpotifyBot():
    def __init__(self):
        client_id = "2590a24f719846b5bca0202a6d738489"
        client_secret = "025fa563fa4048a9a8a404ee817454af"
        redirect_uri = "https://google.com"
        scope = "user-read-playback-state user-modify-playback-state"
        self.device_name = "DESKTOP-CI79GB0"
        device_id = 0

        oauth = spotipy.oauth2.SpotifyOAuth(client_id=client_id,client_secret=client_secret,redirect_uri=redirect_uri,scope=scope)
        token = oauth.get_access_token()["access_token"]    
        self.bot = spotipy.Spotify(auth=token)
    def get_device_id(self):
        for device in self.bot.devices()["devices"]:
            if device["name"] == self.device_name:
                self.device_id = device["id"]
        print(f"Device id:{self.device_id}")
        return self.device_id
        
    def get_current_track(self):
        current = self.bot.current_user_playing_track()
        track_name =  current["item"]["name"]
        print(f"Current playing:{track_name}")
        return track_name

    def get_current_track_artist(self):
        current = self.bot.current_user_playing_track()
        artist_name = current["item"]["album"]["artists"][0]["name"]
        print(f"Artist name:{artist_name}")
        return artist_name

    def next_track(self):
        print("Skipping...")
        self.bot.next_track()

    def prev_track(self):
        print("Previous track...")
        self.bot.previous_track()

    def pause(self):
        print("Pausing...")
        self.bot.pause_playback()
    
    def set_vol(self):
        print("Vol up")
        self.bot.volume(50,self.device_id)

    
    def run_command(self,command):
        #   'O' = default, none
        #   'N' = next track
        #   'P' = prev track
        #   'S' = pause track
        #   'V' = set volume
        #   'U' = volume up
        #   'D' = volume down
        if command == 'O':
            return
        if command == 'N':
            self.next_track()
            return
        if command == 'P':
            self.prev_track()
            return
        if command == 'S':
            self.pause()
            return
        if command == 'V':
            self.set_vol()
            return
        return

