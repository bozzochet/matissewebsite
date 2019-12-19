import requests
import shutil
import os
import time

shutil.rmtree("/var/www/html/SolarSmoothed/Download")
os.mkdir("/var/www/html/SolarSmoothed/Download")
shutil.copy("/var/www/html/SolarSmoothed/ROOT/SolarSmoothed.root",time.strftime('/var/www/html/SolarSmoothed/Download/SolarSmoothed_%m-%d-%Y.root'))
