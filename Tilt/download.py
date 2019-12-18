import requests
import shutil
import os
import time

shutil.rmtree("Download")
os.mkdir("Download")
shutil.copy("ROOT/TILT.root",time.strftime('Download/Tilt_%m-%d-%Y.root'))
