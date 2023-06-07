#!/usr/bin/php-cgi
<?php
$login = getenv("LOGIN");
if ($login !== false) {
    echo "Valor do login: " . $login;
} else {
    echo "Variável de ambiente 'LOGIN' não definida.";
}
?>
