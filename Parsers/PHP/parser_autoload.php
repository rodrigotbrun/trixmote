<?php

spl_autoload_register("KSVAutoload");

function KSVAutoload($class) {
    if ($class == "Trixmote") {
        require_once __DIR__ . "/Trixmote.php";
    } else {
        $class = str_replace("Trixmote\\", "", $class);
        $e = explode('\\', $class);

        $className = end($e);
        unset($e[count($e) - 1]);

        $e = array_map('strtolower', $e);

        $classFile = __DIR__ . "/" . implode($e, "/") . "/" . $className . ".php";

        if (file_exists($classFile) && !is_dir($classFile))
            require_once $classFile;
    }
}