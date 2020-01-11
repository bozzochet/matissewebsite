<?php
ini_set('display_errors', true);
error_reporting(E_ALL);
echo "Select Stations to plot \n";
//$mes=exec("sxource /var/www/html/root/root/bin/thisroot.sh");
//$message=shell_exec("sudo /var/www/html/FFModel/FF");
shell_exec("/var/www/html/SET/shell.sh");

//$message=exec( T_ECHO (DA2344) );
//echo $message;
echo "completed";
?>