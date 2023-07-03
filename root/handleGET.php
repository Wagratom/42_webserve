#!/usr/bin/php-cgi
<?php
echo "\nGET\n";

$get = $_GET;
foreach ($get as $key => $value) {
	echo "$key => $value\n";
}
?>
