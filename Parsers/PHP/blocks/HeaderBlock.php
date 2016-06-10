<?php

namespace Trixmote\Blocks;

/**
 * Class HeaderBlock
 */
class HeaderBlock extends TypeBlock {

    const FORMAT = "/\[\~.*\~\]/";
    
    /**
     * @return String Identificador do bloco
     */
    public function getBlockID() {
        return "";
    }
}