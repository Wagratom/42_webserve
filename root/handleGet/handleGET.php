#!/usr/bin/php-cgi

<!DOCTYPE html>
<html>
	<head>
		<title>Seu input</title>
	</head>
	<body>
	<?php
	$get = $_GET;
	foreach ($get as $key => $value) {
		echo "<p><strong>Sua entrada:</strong> <strong>$key</strong><br><strong>Seu input:</strong> <strong>$value</strong></p>\n";
	}
	$output = ob_get_contents();
	$contentLength = strlen($output);
	header("Content-Length: $contentLength");
	// while (1);
	?>
	</body>
</html>
