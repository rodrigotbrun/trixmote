<?php

namespace Trixmote\Blocks;

/**
 * Class KeyboardModifierKeyBlock
 */
class KeyboardModifierKeyBlock extends TypeBlock {

    const FORMAT = "/\[\{.*[m:\[\]a-zA-Z]+\}\]/";
    
    /**
     * @return String Identificador do bloco
     */
    public function getBlockID() {
        return "m";
    }
}