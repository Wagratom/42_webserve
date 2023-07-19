#!/usr/bin/php-cgi
<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);

while (1);
// Verifica se há um arquivo enviado no POST
if (isset($_FILES['fileUpload'])) {
	$uploadDirectory = '../../uploads/';					// Diretório de upload
	$fileName = $_FILES['fileUpload']['name'];			// Nome original do arquivo
	$tempFilePath = $_FILES['fileUpload']['tmp_name'];	// Caminho completo do arquivo temporário

	// Exibe informações sobre o arquivo temporário antes de salvar
    print_r($_FILES['fileUpload']);
    echo "<br>";

    // Ler o conteúdo do arquivo temporário (opcional, apenas para fins de visualização)
    $fileContent = file_get_contents($tempFilePath);
    echo 'Conteúdo do arquivo temporário:<br>';
    echo '<pre>' . htmlspecialchars($fileContent) . '</pre>'; // Use htmlspecialchars para exibir o conteúdo com caracteres especiais corretamente.

    // Verifique se o diretório de upload existe, caso contrário, crie-o
    if (!file_exists($uploadDirectory)) {
        mkdir($uploadDirectory, 0777, true);
    }

    // Caminho completo do arquivo de destino
    $destination = $uploadDirectory . $fileName;

    // Move o arquivo temporário para o diretório de destino
    if (move_uploaded_file($tempFilePath, $destination)) {
        echo 'Arquivo salvo com sucesso em ' . $destination;
    } else {
        echo "Ocorreu um erro ao salvar o arquivo.\n";
    }
}
?>
