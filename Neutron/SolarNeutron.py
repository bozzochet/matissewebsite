import requests
import shutil
import datetime
import os
import time
from SFS import g2j
from requests.exceptions import RequestException
from contextlib import closing
from bs4 import BeautifulSoup
from mathematicians import simple_get

now = datetime.datetime.now()
#------------------NM Station----------
with open('/var/www/html/Neutron/NMStations.txt') as fp:
   line = fp.readline()

print(line)
stat = line.split()

#sline contiene i nomi delle stazioni
for i in range(len(stat)):
 NM = "http://www.nmdb.eu/nest/draw_graph.php?formchk=1&stations[]="+stat[i]+"&tabchoice=1h&dtype=corr_for_efficiency&tresolution=43200&yunits=0&date_choice=bydate&start_day=1&start_month=1&start_year=1960&start_hour=0&start_min=0&end_day=4&end_month=12&end_year=2019&end_hour=23&end_min=59&output=ascii"
 year = str(now.year)
 month = str(now.month)
 day = str(now.day)
 print(year+month+day)
 NM = NM.replace("end_year=2019","end_year="+year)
 NM= NM.replace("end_month=12","end_month="+month)
 NM= NM.replace("end_day=4","end_day="+day)
 url = simple_get(NM)
 print(NM)
 html = BeautifulSoup(url, 'html.parser')
 pathP = "/var/www/html/Neutron/Update/"+stat[i]+"P.txt"
 path ="/var/www/html/Neutron/"+ stat[i]+".txt"

 f = open(pathP, "w")
 for i, pre in enumerate(html.select('pre')):
    f.write("%s" %(pre.text))
 f.close()

#elimino righe inutili
 lines1 = tuple(open(pathP, "r"))
 with open(pathP, "w+") as file:
  for i in range(len(lines1)):
    if i > 25:
        file.write(lines1[i])
#su OuluP.txt ho scaricato i dati correnti devo confrontarli con Oulu.txt storico


 lines2 = tuple(open(path,"r"))
#lines 2 più corta
 lines1 = tuple(open(pathP, "r"))

#appendo la differenza allo storico
#evito conteggio di linee vuote
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

 print(n1)
 print(n2)
#per evitare spazi indesiderati iniziali
 file = open(path, "a")
 for j in range(n2,n1):
   sline = lines1[j].split()
   if len(sline) == 2:
    year  = int(lines1[j][0]+lines1[j][1]+lines1[j][2]+lines1[j][3])
    month = int(lines1[j][5]+lines1[j][6])
    day   = int(lines1[j][8]+lines1[j][9])
    value = sline[1][9]
    for i in range(10,len(sline[1])):
       value += sline[1][i]
    a = str(g2j(year,month,day))
    file.write(a + "  " + value + "\n")
   if len(sline) != 2:
      year  = int(lines1[j][0]+lines1[j][1]+lines1[j][2]+lines1[j][3])
      month = int(lines1[j][5]+lines1[j][6])
      day   = int(lines1[j][8]+lines1[j][9])
      a = str(g2j(year,month,day))
      file.write(a + "  " + sline[2] + "\n")
