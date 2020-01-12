<?php
$line = "OULU JUNG NEWK ROME MOSC ";
echo $line;
$stations = explode(" ", $line);                                               

$result = sizeof($stations);                                                   
$myfile = fopen("STAZIONI4.txt", "w") or die("Unable to open file!");            
 for ($i = 0; $i < $result; $i++) {                                            

 $txt = $stations[$i];                                                         

 fwrite($myfile, $txt);                                                        

 fwrite($myfile, "\n");                                                        

}
//echo $message;
echo "\n COMPLETED";

exec("cp STAZIONI4.txt /var/www/html/FFModel/David.txt &&  cp STAZIONI4.txt /var/www/html/FFModel/DavidPelosi.txt");
exec("source /var/www/html/root/root/bin/thisroot.sh && /var/www/html/FFModel/FF");
//exec("FF");
echo "RUN secondo comando EXE RUN";
?>
