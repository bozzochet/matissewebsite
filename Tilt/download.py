import requests
import shutil
import os
import time

shutil.rmtree("/var/www/html/Tilt/Download")
os.mkdir("/var/www/html/Tilt/Download")
shutil.copy("/var/www/html/Tilt/ROOT/TILT.root",time.strftime('/var/www/html/Tilt/Download/Tilt_%m-%d-%Y.root'))
