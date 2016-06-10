<?php


/**
 * Class KSV
 */
class KSV {

    /**
     * @var string Extensão do arquivo
     */
    private $fileExtension = "ksvl";

    /**
     * @var string Arquivo de log para Parser
     */
    private $logFile = null;

    /**
     * @var string
     */
    private $outputFileTraces = "output/";

    /**
     * KSV constructor.
     *
     * @param $logFile
     */
    public function __construct($logFile) {
        $this->logFile = $logFile;
    }

    /**
     * Retorna um texto em MARKDOWN com a pilha de comandos do arquivo log.
     */
    public function listCommandsTrace() {
        $blocks = $this->getListOfBlocks();





        return $blocks;
    }

    private function validateLogFile() {
        if (!empty($this->logFile)) {
            if (file_exists($this->logFile) && !is_dir($this->logFile)) {
                if (substr($this->logFile, -5, 5) === ".{$this->fileExtension}") {
                    if (is_readable($this->logFile)) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    private function openFile() {
        return file_get_contents($this->logFile);
    }

    private function getListOfBlocks() {
        if ($this->validateLogFile()) {
            $file = $this->openFile();

            $stringBlocks = str_replace("\0\n", "", $file);
//            $stringBlocks = preg_split("/^\[(\{|~|[a-zA-Z]){1}.*\]/", $stringBlocks);


            return $stringBlocks;
        }
    }


}