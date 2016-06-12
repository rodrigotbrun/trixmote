<?php

namespace Trixmote\Blocks;

/**
 * Class KeyboardSimpleKeyBlock
 */
class KeyboardSimpleKeyBlock extends TypeBlock {

    const FORMAT = "/\[k:\[.+\]\]/";

    /**
     * @var string Tecla pressionada
     */
    private $key;

    public function __construct($bs){
        parent::__construct($bs);

        $this->key = "";

        preg_match_all('/\[.+\]/', $bs, $this->key);
        $this->key = reset($this->key);
        $this->key = reset($this->key);
        $this->key = str_replace(['[','k:',']'],'', $this->key);
    }

    /**
     * @return String Identificador do bloco
     */
    public function getBlockID() {
        return "k";
    }

    /**
     * @return string
     */
    public function getKey()
    {
        return $this->key;
    }

}