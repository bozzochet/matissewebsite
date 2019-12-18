import requests
import shutil
import os
import time
from SFS import g2j
from requests.exceptions import RequestException
from contextlib import closing
from bs4 import BeautifulSoup
from mathematicians import simple_get
#cancellare vecchio salvataggio in Download e aggiornare file con data
shutil.rmtree("Download")
os.mkdir("Download")
url = simple_get("http://wso.stanford.edu/Tilts.html")
html = BeautifulSoup(url, 'html.parser')
f = open(time.strftime('Download/Solar-TILT_ANGLE%m-%d-%Y.txt'), "w")
for i, pre in enumerate(html.select('pre')):
    f.write("%s" %(pre.text))
#lo script importa i dati - tabelle complete - e le salva con la data attuale

#elimino la prima riga per avere un format diviso in colonne
lines1 = tuple(open(time.strftime('Download/Solar-TILT_ANGLE%m-%d-%Y.txt'), "r"))
with open(time.strftime('Download/Solar-TILT_ANGLE%m-%d-%Y.txt'), "w+") as file:
 for i in range(len(lines1)):
    if i > 1:
        file.write(lines1[i])

#ho otteuto il file completo txt

#creo il file SFSN.txt converto date in julian date
lines1 = tuple(open(time.strftime('Download/Solar-TILT_ANGLE%m-%d-%Y.txt'), "r"))
fileRav = open(time.strftime('Tilt_R_av.txt'), "a")
fileRn =  open(time.strftime('Tilt_R_n.txt'), "a")
fileRs =  open(time.strftime('Tilt_R_s.txt'), "a")
fileLav = open(time.strftime('Tilt_L_av.txt'), "a")
fileLn =  open(time.strftime('Tilt_L_n.txt'), "a")
fileLs =  open(time.strftime('Tilt_L_s.txt'), "a")
lines2 = tuple(open(('Tilt_L_n.txt'), "r"))

n1 = len(lines1)
n2 = len(lines2)

if n1 != 0:
 for i in range(n1):
    if lines1[i] == "\n":
        n1 -= 1
if n2 != 0:
 for i in range(n2):
    if lines2[i] == "\n":
        n2 -= 1
#splitto in colonne le varie righe aggiungo solo la differenza
for j in range(n2,n1):
   sline = lines1[j].split()
   year  = int(sline[2][0]+sline[2][1]+sline[2][2]+sline[2][3])
   month = int(sline[2][5]+sline[2][6])
   day   = int(sline[2][8]+sline[2][9])
   print(str(g2j(year,month,day)))
   a = str(g2j(year,month,day))
   fileRav.write(a + "  " + sline[4] + "\n")
   fileRn.write(a  + "  " + sline[5] + "\n")
   fileRs.write(a  + "  " + sline[6] + "\n")
   fileLav.write(a + "  " + sline[7] + "\n")
   fileLn.write(a  + "  " + sline[8] + "\n")
   fileLs.write(a  + "  " + sline[9] + "\n")
#chiudo e salvo file
f.close()
fileRav.close()
fileRn.close()
fileRs.close()
fileLav.close()
fileLn.close()
fileLs.close()
