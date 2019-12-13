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
print(OULU)
url = simple_get(OULU)
print(OULU)
html = BeautifulSoup(url, 'html.parser')
f = open(time.strftime('Oulu.txt'), "w")
for i, pre in enumerate(html.select('pre')):
    f.write("%s" %(pre.text))
f.close()

#elimino righe inutili
lines1 = tuple(open('Oulu.txt', "r"))
with open('Oulu.txt', "w+") as file:
 for i in range(len(lines1)):
    if i > 25:
        file.write(lines1[i])


lines1 = tuple(open('Oulu.txt', "r"))
fileOulu = open(time.strftime('Oulu.txt'), "w+")
#inizio dei cici for per importare i corretti valori per i grafici
for j in range(len(lines1)):
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
    fileOulu.write(a + "  " + value + "\n")
   if len(sline) != 2:
    year  = int(lines1[j][0]+lines1[j][1]+lines1[j][2]+lines1[j][3])
    month = int(lines1[j][5]+lines1[j][6])
    day   = int(lines1[j][8]+lines1[j][9])
    print(str(g2j(year,month,day)) + "    " + str(len(sline)) )
    a = str(g2j(year,month,day))
    fileOulu.write(a + "  " + sline[2] + "\n")
#chiudo e salvo file
fileOulu.close();

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
f = open(time.strftime('Jung.txt'), "w")
for i, pre in enumerate(html.select('pre')):
    f.write("%s" %(pre.text))
f.close()

#elimino righe inutili
lines1 = tuple(open('Jung.txt', "r"))
with open('Jung.txt', "w+") as file:
 for i in range(len(lines1)):
    if i > 25:
        file.write(lines1[i])


lines1 = tuple(open('Jung.txt', "r"))
fileJUNG = open(time.strftime('Jung.txt'), "w+")
#inizio dei cici for per importare i corretti valori per i grafici
for j in range(len(lines1)):
   sline = lines1[j].split()
   if len(sline) == 2:
    year  = int(lines1[j][0]+lines1[j][1]+lines1[j][2]+lines1[j][3])
    month = int(lines1[j][5]+lines1[j][6])
    day   = int(lines1[j][8]+lines1[j][9])
    value = sline[1][9]
    for i in range(10,len(sline[1])):
       value += sline[1][i]
    print(str(g2j(year,month,day)))
    a = str(g2j(year,month,day))
    fileJUNG.write(a + "  " + value + "\n")
   if len(sline) != 2:
      year  = int(lines1[j][0]+lines1[j][1]+lines1[j][2]+lines1[j][3])
      month = int(lines1[j][5]+lines1[j][6])
      day   = int(lines1[j][8]+lines1[j][9])
      print(str(g2j(year,month,day)))
      a = str(g2j(year,month,day))
      fileJUNG.write(a + "  " + sline[2] + "\n")
#chiudo e salvo file
fileJUNG.close();
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
f = open(time.strftime('Newk.txt'), "w")
for i, pre in enumerate(html.select('pre')):
    f.write("%s" %(pre.text))
f.close()

#elimino righe inutili
lines1 = tuple(open('Newk.txt', "r"))
with open('Newk.txt', "w+") as file:
 for i in range(len(lines1)):
    if i > 25:
        file.write(lines1[i])


lines1 = tuple(open('Newk.txt', "r"))
fileNewk = open(time.strftime('Newk.txt'), "w+")
#inizio dei cici for per importare i corretti valori per i grafici
for j in range(len(lines1)):
   sline = lines1[j].split()
   if len(sline) == 2:
    year  = int(lines1[j][0]+lines1[j][1]+lines1[j][2]+lines1[j][3])
    month = int(lines1[j][5]+lines1[j][6])
    day   = int(lines1[j][8]+lines1[j][9])
    value = sline[1][9]
    for i in range(10,len(sline[1])):
       value += sline[1][i]
    print(str(g2j(year,month,day)))
    a = str(g2j(year,month,day))
    fileNewk.write(a + "  " + value + "\n")
   if len(sline) != 2:
      year  = int(lines1[j][0]+lines1[j][1]+lines1[j][2]+lines1[j][3])
      month = int(lines1[j][5]+lines1[j][6])
      day   = int(lines1[j][8]+lines1[j][9])
      print(str(g2j(year,month,day)))
      a = str(g2j(year,month,day))
      fileNewk.write(a + "  " + sline[2] + "\n")
#chiudo e salvo file
fileNewk.close();

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
f = open(time.strftime('Kiel.txt'), "w")
for i, pre in enumerate(html.select('pre')):
    f.write("%s" %(pre.text))
f.close()
#elimino righe inutili
lines1 = tuple(open('Kiel.txt', "r"))
with open('Kiel.txt', "w+") as file:
 for i in range(len(lines1)):
    if i > 25:
        file.write(lines1[i])


lines1 = tuple(open('Kiel.txt', "r"))
fileKiel = open(time.strftime('Kiel.txt'), "w+")
#inizio dei cici for per importare i corretti valori per i grafici
for j in range(len(lines1)):
   sline = lines1[j].split()
   if len(sline) == 2:
    year  = int(lines1[j][0]+lines1[j][1]+lines1[j][2]+lines1[j][3])
    month = int(lines1[j][5]+lines1[j][6])
    day   = int(lines1[j][8]+lines1[j][9])
    value = sline[1][9]
    for i in range(10,len(sline[1])):
       value += sline[1][i]
    print(str(g2j(year,month,day)))
    a = str(g2j(year,month,day))
    fileKiel.write(a + "  " + value + "\n")
   if len(sline) != 2:
      year  = int(lines1[j][0]+lines1[j][1]+lines1[j][2]+lines1[j][3])
      month = int(lines1[j][5]+lines1[j][6])
      day   = int(lines1[j][8]+lines1[j][9])
      print(str(g2j(year,month,day)))
      a = str(g2j(year,month,day))
      fileKiel.write(a + "  " + sline[2] + "\n")
#chiudo e salvo file
fileKiel.close();
