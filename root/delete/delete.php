#!/usr/bin/php-cgi
<?php
if (isset($_GET['filename'])) {
    $file = $_GET['filename'];
    // Sanitize the file parameter to prevent directory traversal attacks
    $file = basename($file);
    // Define the directory where the file should be located
    $targetDirectory = '../../uploads/';

    // Full path to the file
    $filePath = $targetDirectory . $file;

    // Check if the file exists and is within the target directory
    if (file_exists($filePath) && strpos(realpath($filePath), realpath($targetDirectory)) === 0) {
        // Use unlink() to delete the file
        if (unlink($filePath)) {
            echo "Arquivo apagado com sucesso: " . $file;
        } else {
            echo "Não foi possível apagar o arquivo.";
        }
    } else {
        echo "Arquivo inválido ou não encontrado.";
    }
}
?>
