<?php

namespace Trixmote\Blocks;

/**
 * Class MouseClickBlock
 */
class MouseClickBlock extends TypeBlock {

    const FORMAT = "/\[c:[0-9]+:[0-9\.]+x[0-9\.]+\[.*\]\]/";
    
    /**
     * @return String Identificador do bloco
     */
    public function getBlockID() {
        return "c";
    }
}