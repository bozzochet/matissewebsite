def g2j(year, month, day):
 lines2 = tuple(open('/var/www/html/SSN/SSN_History.txt', "r"))
 fyear = []
 fmonth = []
 fday = []
 fractional = []
 for h in range(len(lines2)):
   sline2 = lines2[h].split()
   fyear.append(sline2[0])
   fmonth.append(sline2[1])
   fday.append(sline2[2])
   fractional.append(sline2[3])

#ricercare il giusto valore di fractional
 for i in range(len(fyear) - 1):
  if int(fyear[i]) == year:
   for k in range(i,len(fyear)):
    if int(fmonth[k]) == month:
     for j in range(k,len(fyear)):
      if int(fday[j]) == day:
       return(fractional[j])
       break
      break
   break
