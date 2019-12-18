import requests
import shutil
import os
import time

shutil.rmtree("Download")
os.mkdir("Download")
shutil.copy("ROOT/SolarSmoothed.root",time.strftime('Download/SolarSmoothed_%m-%d-%Y.root'))
