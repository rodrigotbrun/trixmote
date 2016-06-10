<?php

require_once __DIR__ . "/vendor/autoload.php";
require_once __DIR__ . "/parser_autoload.php";

$ksv = new KSV(__DIR__ . "/examples/example1.ksvl");

echo "<pre>";
var_dump($ksv->listCommandsTrace());