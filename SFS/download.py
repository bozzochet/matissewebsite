import requests
import shutil
import os
import time

shutil.rmtree("/var/www/html/SFS/Download")
os.mkdir("/var/www/html/SFS/Download")
shutil.copy("/var/www/html/SFS/ROOT/SFS.root",time.strftime('/var/www/html/SFS/Download/SFS_%m-%d-%Y.root'))
