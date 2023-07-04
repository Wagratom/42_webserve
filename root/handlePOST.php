#!/usr/bin/php-cgi7.4
<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);

echo "SERVER";

$envs = $_SERVER;
foreach ($envs as $key => $value) {
	echo "$key => $value\n";
}

echo "\nFILES\n";
echo "name: " . $_FILES['fileUpload']['name']. "\n";     // Output: Novo Documento de Texto.txt
echo "type: " . $_FILES['fileUpload']['type']. "\n";     // Output: text/plain
echo "tmp_name: " . $_FILES['fileUpload']['tmp_name']. "\n"; // Output: /tmp/phpahYR1V
echo "error: " . $_FILES['fileUpload']['error']. "\n";    // Output: 0
echo "size: " . $_FILES['fileUpload']['size']. "\n";     // Output: 11
$fileContent = file_get_contents($_FILES['fileUpload']['tmp_name']);
echo $fileContent;

echo "\nsair\n"
?>
