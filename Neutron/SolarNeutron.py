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
#------------------OULU----------
OULU = "http://www.nmdb.eu/nest/draw_graph.php?formchk=1&stations[]=OULU&tabchoice=1h&dtype=corr_for_pressure&tresolution=43200&yunits=0&date_choice=bydate&start_day=1&start_month=1&start_year=1960&start_hour=0&start_min=0&end_day=4&end_month=12&end_year=2019&end_hour=23&end_min=59&output=ascii"
year = str(now.year)
month = str(now.month)
day = str(now.day)
print(year+month+day)
OULU = OULU.replace("end_year=2019","end_year="+year)
OULU= OULU.replace("end_month=12","end_month="+month)
OULU= OULU.replace("end_day=4","end_day="+day)
url = simple_get(OULU)
print(OULU)
html = BeautifulSoup(url, 'html.parser')
f = open(time.strftime('/var/www/html/Neutron/Update/OuluP.txt'), "w")
for i, pre in enumerate(html.select('pre')):
    f.write("%s" %(pre.text))
f.close()

#elimino righe inutili
lines1 = tuple(open('/var/www/html/Neutron/Update/OuluP.txt', "r"))
with open('/var/www/html/Neutron/Update/OuluP.txt', "w+") as file:
 for i in range(len(lines1)):
    if i > 25:
        file.write(lines1[i])
#su OuluP.txt ho scaricato i dati correnti devo confrontarli con Oulu.txt storico


lines2 = tuple(open("/var/www/html/Neutron/Oulu.txt","r"))
#lines 2 più corta
lines1 = tuple(open('/var/www/html/Neutron/Update/OuluP.txt', "r"))

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
file = open(('/var/www/html/Neutron/Oulu.txt'), "a")
for j in range(n2,n1):
   sline = lines1[j].split()
   #print(lines1[j][0]+lines1[j][1]+lines1[j][2]+lines1[j][3])
   if len(sline) == 2:
    year  = int(lines1[j][0]+lines1[j][1]+lines1[j][2]+lines1[j][3])
    month = int(lines1[j][5]+lines1[j][6])
    day   = int(lines1[j][8]+lines1[j][9])
    value = sline[1][9]
    for i in range(10,len(sline[1])):
       value += sline[1][i]
    #print(str(g2j(year,month,day)))
    a = str(g2j(year,month,day))
    file.write(a + "  " + value + "\n")
   if len(sline) != 2:
      year  = int(lines1[j][0]+lines1[j][1]+lines1[j][2]+lines1[j][3])
      month = int(lines1[j][5]+lines1[j][6])
      day   = int(lines1[j][8]+lines1[j][9])
      #print(str(g2j(year,month,day)))
      a = str(g2j(year,month,day))
      file.write(a + "  " + sline[2] + "\n")

#chiudo e salvo file
file.close();

#-----------JUNG----
JUNG = "http://www.nmdb.eu/nest/draw_graph.php?formchk=1&stations[]=JUNG&tabchoice=1h&dtype=corr_for_pressure&tresolution=43200&yunits=0&date_choice=bydate&start_day=1&start_month=1&start_year=1960&start_hour=0&start_min=0&end_day=4&end_month=12&end_year=2019&end_hour=23&end_min=59&output=ascii"
year = str(now.year)
month = str(now.month)
day = str(now.day)
print(year+month+day)
JUNG = JUNG.replace("end_year=2019","end_year="+year)
JUNG= JUNG.replace("end_month=12","end_month="+month)
JUNG= JUNG.replace("end_day=4","end_day="+day)
url = simple_get(JUNG)
print(JUNG)
url = simple_get(JUNG)
html = BeautifulSoup(url, 'html.parser')
f = open(time.strftime('/var/www/html/Neutron/Update/JungP.txt'), "w")
for i, pre in enumerate(html.select('pre')):
    f.write("%s" %(pre.text))
f.close()

#elimino righe inutili
lines1 = tuple(open('/var/www/html/Neutron/Update/JungP.txt', "r"))
with open('/var/www/html/Neutron/Update/JungP.txt', "w+") as file:
 for i in range(len(lines1)):
    if i > 25:
        file.write(lines1[i])
#su OuluP.txt ho scaricato i dati correnti devo confrontarli con Oulu.txt storico


lines2 = tuple(open("/var/www/html/Neutron/Jung.txt","r"))
#lines 2 più corta
lines1 = tuple(open('/var/www/html/Neutron/Update/JungP.txt', "r"))

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
for j in range(n2,n1):
     with open("/var/www/html/Neutron/Jung.txt", "a") as file:
         sline = lines1[j].split()
         if len(sline) == 2:
           year  = int(lines1[j][0]+lines1[j][1]+lines1[j][2]+lines1[j][3])
           month = int(lines1[j][5]+lines1[j][6])
           day   = int(lines1[j][8]+lines1[j][9])
           value = sline[1][9]
           for i in range(10,len(sline[1])):
              value += sline[1][i]
           print(str(g2j(year,month,day)) + "    " + str(len(sline)) )
           a = str(g2j(year,month,day))
           file.write(a + "  " + value + "\n")
         if len(sline) != 2:
           year  = int(lines1[j][0]+lines1[j][1]+lines1[j][2]+lines1[j][3])
           month = int(lines1[j][5]+lines1[j][6])
           day   = int(lines1[j][8]+lines1[j][9])
           print(str(g2j(year,month,day)) + "    " + str(len(sline)) )
           a = str(g2j(year,month,day))
           file.write(a + "  " + sline[2] + "\n")

#chiudo e salvo file
file.close();

#--------------NEWK----------------------------------------------
NEWK = "http://www.nmdb.eu/nest/draw_graph.php?formchk=1&stations[]=NEWK&tabchoice=1h&dtype=corr_for_pressure&tresolution=43200&yunits=0&date_choice=bydate&start_day=1&start_month=1&start_year=1960&start_hour=0&start_min=0&end_day=4&end_month=12&end_year=2019&end_hour=23&end_min=59&output=ascii"
year = str(now.year)
month = str(now.month)
day = str(now.day)
print(year+month+day)
NEWK = NEWK.replace("end_year=2019","end_year="+year)
NEWK= NEWK.replace("end_month=12","end_month="+month)
NEWK= NEWK.replace("end_day=4","end_day="+day)
url = simple_get(NEWK)
print(NEWK)
html = BeautifulSoup(url, 'html.parser')
f = open(time.strftime('/var/www/html/Neutron/Update/NewkP.txt'), "w")
for i, pre in enumerate(html.select('pre')):
    f.write("%s" %(pre.text))
f.close()

#elimino righe inutili
lines1 = tuple(open('/var/www/html/Neutron/Update/NewkP.txt', "r"))
with open('/var/www/html/Neutron/Update/NewkP.txt', "w+") as file:
 for i in range(len(lines1)):
    if i > 25:
        file.write(lines1[i])
#su OuluP.txt ho scaricato i dati correnti devo confrontarli con Oulu.txt storico


lines2 = tuple(open("/var/www/html/Neutron/Newk.txt","r"))
#lines 2 più corta
lines1 = tuple(open('/var/www/html/Neutron/Update/NewkP.txt', "r"))


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
for j in range(n2,n1):
     with open("/var/www/html/Neutron/Newk.txt", "a") as file:
         sline = lines1[j].split()
         if len(sline) == 2:
           year  = int(lines1[j][0]+lines1[j][1]+lines1[j][2]+lines1[j][3])
           month = int(lines1[j][5]+lines1[j][6])
           day   = int(lines1[j][8]+lines1[j][9])
           value = sline[1][9]
           for i in range(10,len(sline[1])):
              value += sline[1][i]
           print(str(g2j(year,month,day)) + "    " + str(len(sline)) )
           a = str(g2j(year,month,day))
           file.write(a + "  " + value + "\n")
         if len(sline) != 2:
           year  = int(lines1[j][0]+lines1[j][1]+lines1[j][2]+lines1[j][3])
           month = int(lines1[j][5]+lines1[j][6])
           day   = int(lines1[j][8]+lines1[j][9])
           print(str(g2j(year,month,day)) + "    " + str(len(sline)) )
           a = str(g2j(year,month,day))
           file.write(a + "  " + sline[2] + "\n")

#chiudo e salvo file
file.close();
#--------Kiel-----------------------------
KIEL = "http://www.nmdb.eu/nest/draw_graph.php?formchk=1&stations[]=KIEL&tabchoice=1h&dtype=corr_for_pressure&tresolution=43200&yunits=0&date_choice=bydate&start_day=1&start_month=1&start_year=1960&start_hour=0&start_min=0&end_day=4&end_month=12&end_year=2019&end_hour=23&end_min=59&output=ascii"
year = str(now.year)
month = str(now.month)
day = str(now.day)
print(year+month+day)
KIEL = KIEL.replace("end_year=2019","end_year="+year)
KIEL= KIEL.replace("end_month=12","end_month="+month)
KIEL= KIEL.replace("end_day=4","end_day="+day)
url = simple_get(KIEL)
print(KIEL)
html = BeautifulSoup(url, 'html.parser')
f = open(time.strftime('/var/www/html/Neutron/Update/KielP.txt'), "w")
for i, pre in enumerate(html.select('pre')):
    f.write("%s" %(pre.text))
f.close()

#elimino righe inutili
lines1 = tuple(open('/var/www/html/Neutron/Update/KielP.txt', "r"))
with open('/var/www/html/Neutron/Update/KielP.txt', "w+") as file:
 for i in range(len(lines1)):
    if i > 25:
        file.write(lines1[i])
#su OuluP.txt ho scaricato i dati correnti devo confrontarli con Oulu.txt storico


lines2 = tuple(open("/var/www/html/Neutron/Kiel.txt","r"))
#lines 2 più corta
lines1 = tuple(open('/var/www/html/Neutron/Update/KielP.txt', "r"))

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

#per evitare spazi indesiderati iniziali
print(n1)
print(n2)
for j in range(n2,n1):
     with open("/var/www/html/Neutron/Kiel.txt", "a") as file:
         sline = lines1[j].split()
         if len(sline) == 2:
           year  = int(lines1[j][0]+lines1[j][1]+lines1[j][2]+lines1[j][3])
           month = int(lines1[j][5]+lines1[j][6])
           day   = int(lines1[j][8]+lines1[j][9])
           value = sline[1][9]
           for i in range(10,len(sline[1])):
              value += sline[1][i]
           print(str(g2j(year,month,day)) + "    " + str(len(sline)) )
           a = str(g2j(year,month,day))
           file.write(a + "  " + value + "\n")
         if len(sline) != 2:
           year  = int(lines1[j][0]+lines1[j][1]+lines1[j][2]+lines1[j][3])
           month = int(lines1[j][5]+lines1[j][6])
           day   = int(lines1[j][8]+lines1[j][9])
           print(str(g2j(year,month,day)) + "    " + str(len(sline)) )
           a = str(g2j(year,month,day))
           file.write(a + "  " + sline[2] + "\n")

#chiudo e salvo file
file.close();
