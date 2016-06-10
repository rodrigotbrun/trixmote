<?php

namespace Trixmote\Blocks;

/**
 * Class KeyboardSimpleKeyBlock
 */
class KeyboardSimpleKeyBlock extends TypeBlock {

    const FORMAT = "/\[k:\[.+\]\]/";
    
    /**
     * @return String Identificador do bloco
     */
    public function getBlockID() {
        return "k";
    }
}