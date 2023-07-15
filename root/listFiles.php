#!/usr/bin/php-cgi

<!DOCTYPE html>
<html>
<head>
	<title>Lista de Arquivos</title>
	<style>
		body {
			text-align: center;
		}
		table {
			border-collapse: collapse;
			margin-left: auto;
			margin-right: auto;
		}
		th, td {
			padding: 5px;
			border: 1px solid black;
		}
		th {
			text-align: left;
		}
		td {
			vertical-align: middle;
		}
		td.filename {
			text-align: left;
			margin-right: 10px;
		}
		td.button {
			margin-right: 10px;
		}
		button {
			margin-top: 1px;
		}
	</style>
</head>
<body>
	<h1>Lista de Arquivos</h1>
	<table>
		<tr>
			<th>Nome do Arquivo</th>
			<th>Excluir</th>
		</tr>
		<?php
		// Obtém a lista de arquivos no caminho especificado
		$files = scandir("../uploads");
		// Exibe a lista de arquivos com botões de delete
		foreach ($files as $file) {
			if ($file === "." || $file === "..") {
				continue;
			}
			echo "<tr>";
			echo "<td class=\"filename\">$file</td>";
			echo "<td class=\"button\"><button onclick=\"deleteFile('$file')\">Delete</button></td>";
			echo "</tr>";
		}
		?>

	</table>

	<script>
		function deleteFile(filename) {
			var xhr = new XMLHttpRequest();
			xhr.open("DELETE", "http://localhost:8080/delete/" + filename, true);
			xhr.setRequestHeader('X-HTTP-Method-Override', 'DELETE');
			xhr.onreadystatechange = function() {
				if (xhr.readyState === 4 && xhr.status === 200) {
					// A resposta foi recebida com sucesso
					// Faça algo se necessário
				}
			};
			xhr.send();
		}
	</script>
</body>
</html>

<?php
$output = ob_get_contents();
$contentLength = strlen($output);
header("Content-Length: $contentLength");
?>

