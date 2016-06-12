<?php

namespace Trixmote\Blocks;

/**
 * Class KeyboardModifierKeyBlock
 */
class KeyboardModifierKeyBlock extends TypeBlock
{

    const FORMAT = "/\[\{.*[m:\[\]a-zA-Z]+\}\]/";

    /**
     * @var TypeBlock[] lista de comandos do grupo
     */
    private $commands;

    public function __construct($bs){
        parent::__construct($bs);
        $commands = [];

        $bs = str_replace(['[{','}]'], '', $bs);

        $out = [];
        preg_match_all("/\[.*\]/", $file, $out);
        $out = reset($out);
        $i = 0;
        foreach ($out as $b) {
            $out[$i] = TypeBlock::detectTypeBlock($b);
            $i++;
        }

        exit($bs);
    }

    /**
     * @return String Identificador do bloco
     */
    public function getBlockID()
    {
        return "m";
    }
}