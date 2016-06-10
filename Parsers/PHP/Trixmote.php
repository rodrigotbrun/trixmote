<?php
namespace Trixmote;

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
            $stringBlocks = preg_match_all("/\[.*\]/", $file, $out);
            $out = reset($out);
            $i = 0;
            foreach ($out as $b) {

                if (preg_match(\Trixmote\Blocks\MouseClickBlock::FORMAT, $b)) {
                    $out[$i] = new \Trixmote\Blocks\MouseClickBlock($b);
                } else if (preg_match(\Trixmote\Blocks\MouseDragBlock::FORMAT, $b)) {
                    $out[$i] = new \Trixmote\Blocks\MouseDragBlock($b);
                } else if (preg_match(\Trixmote\Blocks\KeyboardSimpleKeyBlock::FORMAT, $b)) {
                    $out[$i] = new \Trixmote\Blocks\KeyboardSimpleKeyBlock($b);
                } else if (preg_match(\Trixmote\Blocks\KeyboardModifierKeyBlock::FORMAT, $b)) {
                    $out[$i] = new \Trixmote\Blocks\KeyboardModifierKeyBlock($b);
                } else if (preg_match(\Trixmote\Blocks\ClipboardBlock::FORMAT, $b)) {
                    $out[$i] = new \Trixmote\Blocks\ClipboardBlock($b);
                } else if (preg_match(\Trixmote\Blocks\HeaderBlock::FORMAT, $b)) {
                    $out[$i] = new \Trixmote\Blocks\HeaderBlock($b);
                } else {
                    unset($out[$i]);
                }

                $i++;
            }

            return $out;
        }
    }


}