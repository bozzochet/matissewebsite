import requests
import shutil
import os
import time

shutil.rmtree("/var/www/html/SET/Download")
os.mkdir("/var/www/html/SET/Download")
shutil.copy("/var/www/html/SET/NM_Set1.txt",time.strftime('/var/www/html/SET/Download/TEST.txt'))
