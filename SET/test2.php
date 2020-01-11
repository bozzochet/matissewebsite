<?php
echo "TEST";
echo "\n";
$location = file_get_contents('Output.txt');
echo $location;

//Name
$filename = "Output2.txt";
//change permission of file
chmod($filename,0777);
//Pointer
$file = fopen( $filename, "w" );
if( $file == false )
{
   echo ( "Error in opening new file" );
   exit();
}

fwrite( $file, "This is  a simple test\n" );
fclose( $file );

echo "COMPLETED";
//file_put_contents('/SET/Output.txt' , $write , FILE_APPEND);
?>

