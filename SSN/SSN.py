import requests
import os
import time
import shutil
#problemi spazi
with open("SSN_History.txt", "r") as infile:
    lines = infile.readlines()
a = lines
for i in range(len(a)):
    if a[i] == "\n":
     del a[i:len(a)]
     break

fout = open("SSN_History.txt","w")
fout.writelines(a)
fout.close()
#scarico ogni giorno il daily
#parto però con il mese in backup


url = 'http://www.sidc.be/silso/DATA/EISN/EISN_current.txt'
r = requests.get(url, allow_redirects=True)
#sovrascrive il mese monthly
open('SSN_Monthly.txt', 'wb').write(r.content)

lines1 = tuple(open("backup/SSN_MonthlyP.txt","r"))
lines2 = tuple(open("SSN_Monthly.txt","r"))


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
for a in range(n1,n2):
     with open("SSN_History.txt", "a") as file:
         file.write(lines2[a])

#a questo punto lo storico contiene tutte le info da 1818 - al giorno corrente

#sovrascrivere backup
open('backup/SSN_MonthlyP.txt', 'wb').write(r.content)

#cancellare vecchio salvataggio in Download e aggiornare file con data
shutil.rmtree("Download")
os.mkdir("Download")
#shutil.copy('/Users/David/Desktop/programming/python/modules/Solar/SSN_History.txt', time.strftime("/Users/David/Desktop/programming/python/modules/Solar/Download/SSN(1-1-1818 ; %m-%d-%Y).txt"))
import re
infile = open ('SSN_History.txt', 'r')
outfile = open (time.strftime('Download/SSN1-1-1818_%m-%d-%Y.txt'), 'w')
outfile2 = open (time.strftime('Download/SSNLINE.txt'), 'w')
column1 = 3
column2 = 4
column3 = 5

for line in infile:
    if not re.match('#', line):
        line = line.strip()
        sline = line.split()
        outfile.write(sline[column1] + ' ')
        outfile.write(sline[column2] + ' ')
        outfile.write('0' + ' ')
        outfile.write(sline[column3] + '\n')
        outfile2.write(sline[column1] + ' ')
        outfile2.write(sline[column2] + ' ' + '\n')


infile.close()
outfile.close()

shutil.copy(time.strftime('Download/SSN1-1-1818_%m-%d-%Y.txt'), "Download/SSNPLOT.txt")
