<?php

spl_autoload_register("KSVAutoload");

function KSVAutoload($class) {
    if ($class == "KSV") {
        require_once __DIR__ . "/KSV.php";
    }else{
        var_dump($class);
    }
}