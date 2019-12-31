import requests
import shutil
import os
import time

shutil.rmtree("Download")
os.mkdir("Download")
shutil.copy("ForceFieldARRAY.root",time.strftime('Download/ForceField_%m-%d-%Y.root'))
