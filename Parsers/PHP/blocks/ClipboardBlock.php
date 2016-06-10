<?php

namespace Trixmote\Blocks;

/**
 * Class ClipboardBlock
 */
class ClipboardBlock extends TypeBlock {

    const FORMAT = "/\[t:\[[0-9a-zA-Z\=\-\.]+\]\]/";
    
    /**
     * @return String Identificador do bloco
     */
    public function getBlockID() {
        return "c";
    }
}