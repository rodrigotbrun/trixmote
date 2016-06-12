<?php
namespace Trixmote;
use Trixmote\Blocks\TypeBlock;

/**
 * Class Trixmote
 */
class Trixmote {

    /**
     * @var string Extensão do arquivo
     */
    private $fileExtension = "trix";

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
                if (substr($this->logFile, ((strlen($this->fileExtension) + 1) * -1), (strlen($this->fileExtension) + 1)) === ".{$this->fileExtension}") {
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
            $out = [];
            preg_match_all("/\[.*\]/", $file, $out);
            $out = reset($out);
            $i = 0;
            foreach ($out as $b) {
                $out[$i] = TypeBlock::detectTypeBlock($b);
                $i++;
            }

            return $out;
        }
    }


}