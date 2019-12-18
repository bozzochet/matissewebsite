import requests
import shutil
import os
import time

shutil.rmtree("Download")
os.mkdir("Download")
shutil.copy("ROOT/Neutron.root",time.strftime('Download/Neutron_%m-%d-%Y.root'))
