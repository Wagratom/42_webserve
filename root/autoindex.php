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
		// Obtém o valor da variável de ambiente "listFiles"
		$listFiles = getenv('listFiles');

		// Divide a string em uma matriz de arquivos
		$files = explode("\n", $listFiles);

		// Remove o último elemento vazio da matriz
		array_pop($files);

		// Ordena a matriz alfabeticamente
		sort($files);

		// Exibe a lista de arquivos e diretórios como links
		foreach ($files as $file) {
			$isDirectory = is_dir($file);
			$fileType = $isDirectory ? "directory" : "file";
			$fileIcon = $isDirectory ? "directory-icon" : "file-icon";
			echo "<li><span class=\"$fileIcon\"></span><a href=\"$file\">$file</a></li>";
		}
		?>
	</ul>
</body>
</html>
