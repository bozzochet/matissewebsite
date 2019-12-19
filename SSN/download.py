import requests
import shutil
import os
import time

shutil.rmtree("/var/www/html/SSN/Download")
os.mkdir("/var/www/html/SSN/Download")
shutil.copy("/var/www/html/SSN/ROOT/SSN.root",time.strftime('/var/www/html/SSN/Download/SSN_%m-%d-%Y.root'))
