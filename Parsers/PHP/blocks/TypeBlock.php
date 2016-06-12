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
    public function __construct($bs) {
        $this->stringBlock = $bs;
    }

    /**
     * @return String Identificador do bloco
     */
    public abstract function getBlockID();

    public static function detectTypeBlock($b){
        if (preg_match(\Trixmote\Blocks\MouseClickBlock::FORMAT, $b)) {
            return new \Trixmote\Blocks\MouseClickBlock($b);
        } else if (preg_match(\Trixmote\Blocks\MouseDragBlock::FORMAT, $b)) {
            return new \Trixmote\Blocks\MouseDragBlock($b);
        } else if (preg_match(\Trixmote\Blocks\ClipboardBlock::FORMAT, $b)) {
            return new \Trixmote\Blocks\ClipboardBlock($b);
        } else if (preg_match(\Trixmote\Blocks\KeyboardModifierKeyBlock::FORMAT, $b)) {
            return new \Trixmote\Blocks\KeyboardModifierKeyBlock($b);
        } else if (preg_match(\Trixmote\Blocks\KeyboardSimpleKeyBlock::FORMAT, $b)) {
            return new \Trixmote\Blocks\KeyboardSimpleKeyBlock($b);
        } else if (preg_match(\Trixmote\Blocks\HeaderBlock::FORMAT, $b)) {
            return new \Trixmote\Blocks\HeaderBlock($b);
        }
    }
}