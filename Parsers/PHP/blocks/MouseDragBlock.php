<?php

namespace Trixmote\Blocks;

/**
 * Class MouseDragBlock
 */
class MouseDragBlock extends TypeBlock {

    const FORMAT = "/\[d:([0-9\.]+x[0-9\.]+|.)+\[.*\]\]/";
    
    /**
     * @return String Identificador do bloco
     */
    public function getBlockID() {
        return "d";
    }
}