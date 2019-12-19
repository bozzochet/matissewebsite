import requests
import shutil
import os
import time

shutil.rmtree("/var/www/html/Neutron/Download")
os.mkdir("/var/www/html/Neutron/Download")
shutil.copy("/var/www/html/Neutron/ROOT/Neutron.root",time.strftime('/var/www/html/Neutron/Download/Neutron_%m-%d-%Y.root'))
