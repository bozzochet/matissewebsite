import requests
import shutil
import os
import time

shutil.rmtree("Download")
os.mkdir("Download")
m =int(time.strftime('%m'))
d =int(time.strftime('%d'))

shutil.copy("ForceFieldARRAY.root",time.strftime('Download/ForceField_'+str(m)+'-'+str(d)+'-'+'%Y.root'))
