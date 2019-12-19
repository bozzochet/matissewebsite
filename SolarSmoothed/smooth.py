
import requests
import os
import time
import shutil
import re

url = 'http://www.sidc.be/silso/DATA/SN_m_tot_V2.0.txt'
r = requests.get(url, allow_redirects=True)
#sovrascrive o scrive il monthly
open('/var/www/html/SolarSmoothed/SSN_Monthly.txt', 'wb').write(r.content)


line = tuple(open(time.strftime('/var/www/html/SolarSmoothed/SSN_Monthly.txt'), "r"))
a = line
with open(time.strftime('/var/www/html/SolarSmoothed/SSN_Monthly.txt'), "w") as file:
 for j in range(len(a)):
   sline = a[j].split()
   if not sline[3] == '-1.0':
        file.write(a[j])

url2 = 'http://www.sidc.be/silso/DATA/SN_ms_tot_V2.0.txt'
r2 = requests.get(url2, allow_redirects=True)
#sovrascrive o scrive il 13-smoothed monthly
open('/var/www/html/SolarSmoothed/SN_13.txt', 'wb').write(r2.content)


j = 0
#cancellare +6 e -6 mesi

line = tuple(open(time.strftime('/var/www/html/SolarSmoothed/SSN_13.txt'), "r"))
a = line
with open(time.strftime('/var/www/html/SolarSmoothed/SSN_13.txt'), "w") as file:
 for j in range(len(a)):
   sline = a[j].split()
   if not sline[3] == '-1.0':
        file.write(a[j])

#creare subito il database da cui fare il grafico
import re
infile = open ('/var/www/html/SolarSmoothed/SSN_13.txt', 'r')
outfile = open ('/var/www/html/SolarSmoothed/SSN_13PLOT.txt', 'w')

for line in infile:
        line = line.strip()
        sline = line.split()
        outfile.write(sline[2] + ' ')
        outfile.write(sline[3] + ' ')
        if sline[4] == '-1.0':
            outfile.write('0' + ' '+'0 ' +'\n')
        else: outfile.write('0' + ' ' +sline[4] + ' '+'\n')

infile.close()
outfile.close()

#altro databse ploy
infile2 = open ('/var/www/html/SolarSmoothed/SSN_Monthly.txt', 'r')
outfile2 = open ('/var/www/html/SolarSmoothed/SSN_MonthlyPLOT.txt', 'w')

for lin in infile2:
        lin = lin.strip()
        sline = lin.split()
        outfile2.write(sline[2] + ' ')
        outfile2.write(sline[3] + ' ')
        if sline[4] == '-1.0':
            outfile2.write('0' + ' '+'0 ' +'\n')
        else: outfile2.write('0' + ' ' +sline[4] + ' '+'\n')

infile2.close()
outfile2.close()
