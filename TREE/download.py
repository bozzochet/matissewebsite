#!/usr/local/bin/python3
import requests
import shutil
import os
import time

shutil.rmtree("Download")
os.mkdir("Download")
shutil.copy("/var/www/html/TREE/ROOT/SFSTree.root",time.strftime('/var/www/html/TREE/Download/SFSTree_%m-%d-%Y.root'))
shutil.copy("/var/www/html/TREE/ROOT/TiltTree.root",time.strftime('/var/www/html/TREE/Download/TiltTree_%m-%d-%Y.root'))
shutil.copy("/var/www/html/TREE/ROOT/SSNTree.root",time.strftime('/var/www/html/TREE/Download/SSNTree_%m-%d-%Y.root'))
shutil.copy("/var/www/html/TREE/ROOT/MonthlyTree.root",time.strftime('/var/www/html/TREE/Download/MonthlyTree_%m-%d-%Y.root'))
shutil.copy("/var/www/html/TREE/ROOT/SmoothedTree.root",time.strftime('/var/www/html/TREE/Download/SmoothedTree_%m-%d-%Y.root'))
shutil.copy("/var/www/html/TREE/ROOT/NeutronTree.root",time.strftime('/var/www/html/TREE/Download/NeutronTree_%m-%d-%Y.root'))
