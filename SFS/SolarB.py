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
url = simple_get("http://wso.stanford.edu/Polar.html")
html = BeautifulSoup(url, 'html.parser')
f = open(time.strftime('Download/Solar_Field_Strenght%m-%d-%Y.txt'), "w")
for i, pre in enumerate(html.select('pre')):
    f.write("%s" %(pre.text))
#lo script importa i dati - tabelle complete - e le salva con la data attuale

#elimino la prima riga per avere un format diviso in colonne
lines1 = tuple(open(time.strftime('Download/Solar_Field_Strenght%m-%d-%Y.txt'), "r"))
with open(time.strftime('Download/Solar_Field_Strenght%m-%d-%Y.txt'), "w+") as file:
 for i in range(len(lines1)):
    if i > 2:
        file.write(lines1[i])

#ho otteuto il file completo txt

#creo il file SFSN.txt converto date in julian date
lines1 = tuple(open(time.strftime('Download/Solar_Field_Strenght%m-%d-%Y.txt'), "r"))
fileN = open(time.strftime('SFSNorth.txt'), "w+")
fileS =  open(time.strftime('SFSSouth.txt'), "w+")
fileA =  open(time.strftime('SFSAvg.txt'), "w+")
fileNf = open(time.strftime('SFSNf.txt'), "w+")
fileSf =  open(time.strftime('SFSSf.txt'), "w+")
fileAf =  open(time.strftime('SFSAvgf.txt'), "w+")


#inizio dei cici for per importare i corretti valori per i grafici
for j in range(len(lines1)-1):
   year  = int(lines1[j][0]+lines1[j][1]+lines1[j][2]+lines1[j][3])
   month = int(lines1[j][5]+lines1[j][6])
   day   = int(lines1[j][8]+lines1[j][9])
   sline = lines1[j].split()
   sline[1] = sline[1].replace("N","")
   #sline[2] = sline[2].replace(sline[2][len(sline[2])-1],"")
   sline[2] = sline[2].replace("S","")
   sline[3] = sline[3].replace("A","")
   sline[3] = sline[3].replace("v","")
   sline[3] = sline[3].replace("g","")
#grafico filtrato 20nhz
   sline[6] = sline[6].replace("N","")
   sline[6] = sline[6].replace("f","")
   sline[7] = sline[7].replace("S","")
   sline[7] = sline[7].replace("f","")
   sline[8] = sline[8].replace("A","")
   sline[8] = sline[8].replace("v","")
   sline[8] = sline[8].replace("g","")
   sline[8] = sline[8].replace("f","")
   #fileN.write(str(g2j(year,month,day)) + "  " + sline[1] + "\n")
   #fileA.write(str(g2j(year,month,day)) + "  " + sline[3] + "\n")
   #fileS.write(str(g2j(year,month,day)) + "  " + sline[2] + "\n")
   print(str(g2j(year,month,day)))
   a = str(g2j(year,month,day))
   fileN.write(a + "  " + sline[1] + "\n")
   fileA.write(a  + "  " + sline[3] + "\n")
   fileS.write(a  + "  " + sline[2] + "\n")
   fileNf.write(a + "  " + sline[6] + "\n")
   fileAf.write(a  + "  " + sline[8] + "\n")
   fileSf.write(a  + "  " + sline[7] + "\n")
#chiudo e salvo file
f.close()
fileA.close()
fileN.close()
fileS.close()
