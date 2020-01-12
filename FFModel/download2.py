import requests
import shutil
import os
import time

shutil.rmtree("/var/www/html/Neutron/Download")
os.mkdir("/var/www/html/Neutron/Download")
m =int(time.strftime('%m'))
d =int(time.strftime('%d'))

shutil.copy("/var/www/html/Neutron/ROOT/Neutron.root",time.strftime('/var/www/html/Neutron/Download/Neutron_'+str(m)+'-'+str(d)+'-'+'%Y.root'))
