import requests
import shutil
import os
import time

shutil.rmtree("Download")
os.mkdir("Download")
shutil.copy("ROOT/SFS.root",time.strftime('Download/SFS_%m-%d-%Y.root'))
