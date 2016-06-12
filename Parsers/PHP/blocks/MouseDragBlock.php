<?php

namespace Trixmote\Blocks;

use Trixmote\Model\Point;

/**
 * Class MouseDragBlock
 */
class MouseDragBlock extends TypeBlock {

    const FORMAT = "/\[d:([0-9\.]+x[0-9\.]+|.)+\[.*\]\]/";

    /**
     * @var Point Coordenada na tela, indicando o local do clique.
     */
    private $points = [];

    /**
     * @var string Botão do mouse usado no clique
     */
    private $mouseButton;

    /**
     * MouseClickBlock constructor.
     *
     * @param $bs Bloco de evento de clique
     */
    public function __construct($bs) {
        parent::__construct($bs);
        $mouseButton = [];
        $points = [];

        preg_match('/([0-9\.]+x[0-9\.]+\|*)+/', $bs, $points);

        preg_match('/\[[a-zA-Z\-]+\]/', $bs, $mouseButton);

        $points = reset($points);
        $points = explode("|", $points);

        $mouseButton = str_replace(['[', ']'], '', reset($mouseButton));

        $this->points = array_map('\Trixmote\Blocks\MouseDragBlock::strToPoint', $points);
        $this->mouseButton = $mouseButton;
    }

    /**
     * @param $str String point
     *
     * @return Point coordenada da tela
     */
    public static function strToPoint($str) {
        $e = explode('x', $str);
        return new Point((double)$e[0], (double)$e[1]);
    }

    /**
     * @return String Identificador do bloco
     */
    public function getBlockID() {
        return "d";
    }

    /**
     * @return Point
     */
    public function getPoints()
    {
        return $this->points;
    }

    /**
     * @return string
     */
    public function getMouseButton()
    {
        return $this->mouseButton;
    }

}