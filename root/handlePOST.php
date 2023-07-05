#!/usr/bin/php-cgi7.4
<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);

$uploadDirectory = $_SERVER['DOCUMENT_ROOT'] . $_SERVER['PATH_DIR']; // Diretório de upload
$fileName = $_FILES['fileUpload']['name']; // Nome original do arquivo

// Verifique se o diretório de upload existe, caso contrário, crie-o
if (!file_exists($uploadDirectory)) {
    mkdir($uploadDirectory, 0777, true);
}

// Caminho completo do arquivo de destino
$destination = $uploadDirectory . $fileName;

// Move o arquivo temporário para o diretório de destino
if (move_uploaded_file($_FILES['fileUpload']['tmp_name'], $destination)) {
    echo 'Arquivo salvo com sucesso em ' . $destination;
} else {
    echo 'Ocorreu um erro ao salvar o arquivo.';
}

?>
