<?php

namespace Trixmote\Model;

/**
 * Class Point
 * @package Trixmote\Model
 */
class Point {

    /**
     * @var double
     */
    private $x;

    /**
     * @var double
     */
    private $y;

    /**
     * Point constructor.
     * @param float $x
     * @param float $y
     */
    public function __construct($x, $y) {
        $this->x = $x;
        $this->y = $y;
    }

    /**
     * @return float
     */
    public function getX() {
        return $this->x;
    }

    /**
     * @return float
     */
    public function getY() {
        return $this->y;
    }

}