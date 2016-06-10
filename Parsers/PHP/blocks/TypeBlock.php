<?php

namespace Trixmote\Blocks;

abstract class TypeBlock {

    /**
     * @var string Bloco de informação
     */
    private $stringBlock;

    /**
     * TypeBlock constructor.
     * 
     * @param $blockString
     */
    public function __construct($blockString) {
        $this->stringBlock = $blockString;
    }

    /**
     * @return String Identificador do bloco
     */
    public abstract function getBlockID();

}