import requests
import shutil
import os
import time

shutil.rmtree("Download")
os.mkdir("Download")
shutil.copy("ROOT/SSN.root",time.strftime('Download/SSN_%m-%d-%Y.root'))
