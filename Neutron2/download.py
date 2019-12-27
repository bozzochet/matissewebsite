import requests
import shutil
import os
import time

shutil.rmtree("/var/www/html/Neutron2/Download")
os.mkdir("/var/www/html/Neutron2/Download")
shutil.copy("/var/www/html/Neutron2/ROOT/Neutron.root",time.strftime('/var/www/html/Neutron2/Download/Neutron2_%m-%d-%Y.root'))
