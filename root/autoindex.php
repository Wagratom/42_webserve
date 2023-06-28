#!/usr/bin/php

<!DOCTYPE html>
<html>
<head>
	<title>Lista de Arquivos</title>
	<style>
		body {
			font-family: Arial, sans-serif;
			margin: 20px;
		}
		h1 {
			margin-bottom: 20px;
		}
		ul {
			list-style-type: none;
			padding: 0;
		}
		li {
			margin-bottom: 5px;
		}
		a {
			text-decoration: none;
			color: #337ab7;
		}
		.directory-icon::before {
			content: "📁";
			margin-right: 5px;
		}
		.file-icon::before {
			content: "📄";
			margin-right: 5px;
		}
	</style>
</head>
<body>
	<h1>Lista de Arquivos</h1>
	<ul>
	<?php
	// Obtém o valor da variável de ambiente "PATHDIR"
	$pathDir = getenv('PATHDIR');

	// Verifica se o diretório existe
	if (!is_dir($pathDir)) {
	    echo "Diretório inválido";
	    exit;
	}

	// Obtém a lista de arquivos e diretórios no diretório especificado
	$files = scandir($pathDir);

	// Remove os diretórios "." e ".." da lista
	$files = array_diff($files, array('.', '..'));

	// Ordena a lista alfabeticamente
	sort($files);

	// Exibe a lista de arquivos e diretórios como links
	foreach ($files as $file) {
	    $filePath = $pathDir . '/' . $file;
	    $isDirectory = is_dir($filePath);
	    $fileType = $isDirectory ? "directory" : "file";
	    $fileIcon = $isDirectory ? "directory-icon" : "file-icon";
	    echo "<li><span class=\"$fileIcon\"></span><a href=\"$filePath\">$file</a></li>";
	}
	?>

	</ul>
</body>
</html>
