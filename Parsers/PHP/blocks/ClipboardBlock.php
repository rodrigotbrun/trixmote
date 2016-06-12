<?php

namespace Trixmote\Blocks;

/**
 * Class ClipboardBlock
 */
class ClipboardBlock extends TypeBlock {

    const FORMAT = "/\[t:\[[0-9a-zA-Z\=\-\.]+\]\]/";

    /**
     * @var string Conteudo da area de transferencia
     */
    private $content;

    public function __construct($bs){
        parent::__construct($bs);
        $this->content = "";

        preg_match_all('/\[[0-9a-zA-Z\=\-\.]+\]/', $bs, $this->content);
        $this->content = reset($this->content);
        $this->content = reset($this->content);
        $this->content = str_replace(['[',']'],'', $this->content);
        $this->content = base64_decode($this->content);
    }

    /**
     * @return String Identificador do bloco
     */
    public function getBlockID() {
        return "c";
    }

    /**
     * @return string
     */
    public function getContent()
    {
        return $this->content;
    }

    /**
     * @return string
     */
    public function getContentWithoutLineBreaks()
    {
        return str_replace(['\n'], '', $this->content);
    }

}