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
#------------------INVK----------
INVK = "http://www.nmdb.eu/nest/draw_graph.php?formchk=1&stations[]=INVK&tabchoice=1h&dtype=corr_for_efficiency&tresolution=43200&yunits=0&date_choice=bydate&start_day=1&start_month=1&start_year=1960&start_hour=0&start_min=0&end_day=4&end_month=12&end_year=2019&end_hour=23&end_min=59&output=ascii"
year = str(now.year)
month = str(now.month)
day = str(now.day)
print(year+month+day)
INVK = INVK.replace("end_year=2019","end_year="+year)
INVK= INVK.replace("end_month=12","end_month="+month)
INVK= INVK.replace("end_day=4","end_day="+day)
url = simple_get(INVK)
print(INVK)
html = BeautifulSoup(url, 'html.parser')
f = open(time.strftime('Update/INVKP.txt'), "w")
for i, pre in enumerate(html.select('pre')):
    f.write("%s" %(pre.text))
f.close()

#elimino righe inutili
lines1 = tuple(open('Update/INVKP.txt', "r"))
with open('Update/INVKP.txt', "w+") as file:
 for i in range(len(lines1)):
    if i > 25:
        file.write(lines1[i])
#su OuluP.txt ho scaricato i dati correnti devo confrontarli con Oulu.txt storico


lines2 = tuple(open("INVK.txt","r"))
#lines 2 più corta
lines1 = tuple(open('Update/INVKP.txt', "r"))

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
file = open(('INVK.txt'), "a")
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

#-----------KERG----
KERG = "http://www.nmdb.eu/nest/draw_graph.php?formchk=1&stations[]=KERG&tabchoice=1h&dtype=corr_for_efficiency&tresolution=43200&yunits=0&date_choice=bydate&start_day=1&start_month=1&start_year=1960&start_hour=0&start_min=0&end_day=4&end_month=12&end_year=2019&end_hour=23&end_min=59&output=ascii"
year = str(now.year)
month = str(now.month)
day = str(now.day)
print(year+month+day)
KERG = KERG.replace("end_year=2019","end_year="+year)
KERG= KERG.replace("end_month=12","end_month="+month)
KERG= KERG.replace("end_day=4","end_day="+day)
url = simple_get(KERG)
print(KERG)
url = simple_get(KERG)
html = BeautifulSoup(url, 'html.parser')
f = open(time.strftime('Update/KERGP.txt'), "w")
for i, pre in enumerate(html.select('pre')):
    f.write("%s" %(pre.text))
f.close()

#elimino righe inutili
lines1 = tuple(open('Update/KERGP.txt', "r"))
with open('Update/KERGP.txt', "w+") as file:
 for i in range(len(lines1)):
    if i > 25:
        file.write(lines1[i])
#su OuluP.txt ho scaricato i dati correnti devo confrontarli con Oulu.txt storico


lines2 = tuple(open("KERG.txt","r"))
#lines 2 più corta
lines1 = tuple(open('Update/KERGP.txt', "r"))

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
     with open("KERG.txt", "a") as file:
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

#--------------MOSC----------------------------------------------
MOSC = "http://www.nmdb.eu/nest/draw_graph.php?formchk=1&stations[]=MOSC&tabchoice=1h&dtype=corr_for_efficiency&tresolution=43200&yunits=0&date_choice=bydate&start_day=1&start_month=1&start_year=1960&start_hour=0&start_min=0&end_day=4&end_month=12&end_year=2019&end_hour=23&end_min=59&output=ascii"
year = str(now.year)
month = str(now.month)
day = str(now.day)
print(year+month+day)
MOSC = MOSC.replace("end_year=2019","end_year="+year)
MOSC= MOSC.replace("end_month=12","end_month="+month)
MOSC= MOSC.replace("end_day=4","end_day="+day)
url = simple_get(MOSC)
print(MOSC)
html = BeautifulSoup(url, 'html.parser')
f = open(time.strftime('Update/MOSCP.txt'), "w")
for i, pre in enumerate(html.select('pre')):
    f.write("%s" %(pre.text))
f.close()

#elimino righe inutili
lines1 = tuple(open('Update/MOSCP.txt', "r"))
with open('Update/MOSCP.txt', "w+") as file:
 for i in range(len(lines1)):
    if i > 25:
        file.write(lines1[i])
#su OuluP.txt ho scaricato i dati correnti devo confrontarli con Oulu.txt storico


lines2 = tuple(open("MOSC.txt","r"))
#lines 2 più corta
lines1 = tuple(open('Update/MOSCP.txt', "r"))


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
     with open("MOSC.txt", "a") as file:
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
#--------APTY-----------------------------
APTY = "http://www.nmdb.eu/nest/draw_graph.php?formchk=1&stations[]=APTY&tabchoice=1h&dtype=corr_for_efficiency&tresolution=43200&yunits=0&date_choice=bydate&start_day=1&start_month=1&start_year=1960&start_hour=0&start_min=0&end_day=4&end_month=12&end_year=2019&end_hour=23&end_min=59&output=ascii"
year = str(now.year)
month = str(now.month)
day = str(now.day)
print(year+month+day)
APTY = APTY.replace("end_year=2019","end_year="+year)
APTY= APTY.replace("end_month=12","end_month="+month)
APTY= APTY.replace("end_day=4","end_day="+day)
url = simple_get(APTY)
print(APTY)
html = BeautifulSoup(url, 'html.parser')
f = open(time.strftime('Update/APTYP.txt'), "w")
for i, pre in enumerate(html.select('pre')):
    f.write("%s" %(pre.text))
f.close()

#elimino righe inutili
lines1 = tuple(open('Update/APTYP.txt', "r"))
with open('Update/APTYP.txt', "w+") as file:
 for i in range(len(lines1)):
    if i > 25:
        file.write(lines1[i])
#su OuluP.txt ho scaricato i dati correnti devo confrontarli con Oulu.txt storico


lines2 = tuple(open("APTY.txt","r"))
#lines 2 più corta
lines1 = tuple(open('Update/APTYP.txt', "r"))

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
     with open("APTY.txt", "a") as file:
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
