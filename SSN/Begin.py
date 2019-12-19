
import requests
import os
import time
import shutil

url = 'http://www.sidc.be/silso/DATA/EISN/EISN_current.txt'
r = requests.get(url, allow_redirects=True)
#sovrascrive il mese monthly
open('/var/www/html/SSN/SSN_Monthly.txt', 'wb').write(r.content)


url2 = 'http://www.sidc.be/silso/DATA/SN_d_tot_V2.0.txt'
r2 = requests.get(url2, allow_redirects=True)
#sovrascrive il mese monthly
open('/var/www/html/SSN/SSN_web.txt', 'wb').write(r2.content)

filenames = ['SSN_web.txt', 'SSN_Monthly.txt']
with open('/var/www/html/SSN/SSN_History.txt', 'w') as outfile:
    for fname in filenames:
        with open(fname) as infile:
            for line in infile:
                outfile.write(line)
#merge i 2 file--> Ottengo lo storico aggiornato al mese corrente
shutil.copy('/var/www/html/SSN/SSN_Monthly.txt', "/var/www/html/SSN/backup/SSN_MonthlyP.txt")
