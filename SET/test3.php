<?php
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);
$file = '/var/www/html/SET/Output.txt';
$mf = fopen($file, 'w');
fwrite($mf, 'hi');
fclose($mf);
echo $file;
?>