<?php

namespace Trixmote\Blocks;

use Trixmote\Model\Point;

/**
 * Class MouseClickBlock
 */
class MouseClickBlock extends TypeBlock {

    const FORMAT = "/\[c:[0-9]+:[0-9\.]+x[0-9\.]+\[.*\]\]/";

    /**
     * @var int Quantidade de cliques sequenciais
     */
    private $clickCount = 1;

    /**
     * @var Point Coordenada na tela, indicando o local do clique.
     */
    private $point = NULL;

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
        $clickCount = [];
        $mouseButton = [];
        $point = [];

        preg_match('/c:[0-9]+/', $bs, $clickCount);
        preg_match('/[0-9]+/', reset($clickCount), $clickCount);

        preg_match('/[0-9\.]+x[0-9\.]+/', $bs, $point);

        preg_match('/\[[a-zA-Z\-]+\]/', $bs, $mouseButton);

        $point = reset($point);
        $point = explode("x", $point);

        $mouseButton = str_replace(['[', ']'], '', reset($mouseButton));

        $this->point = new Point((double)$point[0], (double)$point[1]);
        $this->clickCount = ((int)reset($clickCount));
        $this->mouseButton = $mouseButton;
    }

    /**
     * @return int
     */
    public function getClickCount() {
        return $this->clickCount;
    }

    /**
     * @return Point
     */
    public function getPoint() {
        return $this->point;
    }

    /**
     * @return String Identificador do bloco
     */
    public function getBlockID() {
        return "c";
    }
}