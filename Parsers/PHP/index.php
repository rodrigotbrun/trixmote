<?php

require_once __DIR__ . "/vendor/autoload.php";
require_once __DIR__ . "/parser_autoload.php";

$ksv = new \Trixmote\Trixmote(__DIR__ . "/examples/example1.trix");


echo "<pre>";
var_dump($ksv->listCommandsTrace());