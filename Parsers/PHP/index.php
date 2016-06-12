<?php

require_once __DIR__ . "/vendor/autoload.php";
require_once __DIR__ . "/parser_autoload.php";

$trixmote = new \Trixmote\Trixmote(__DIR__ . "/examples/example1.trix");


$commands = $trixmote->listCommandsTrace();
$o = "#Comandos
";

if(count($commands) > 0){

    foreach($commands as $c){
        if(get_class($c) == \Trixmote\Blocks\MouseClickBlock::class){
            $button = ($c->getMouseButton() == "left-click")?("Esquerdo"):("Direito");
            $o .= "1. Clicar na tela com o botão {$button} do mouse, no ponto x = {$c->getPoint()->getX()}, y = {$c->getPoint()->getY()}
";
        }else if(get_class($c) == \Trixmote\Blocks\MouseDragBlock::class){
            $button = ($c->getMouseButton() == "left-click")?("Esquerdo"):("Direito");
            $points = $c->getPoints();
            $start = reset($points);
            $end = end($points);
            $o .= "1. Clicar na tela com o botão {$button} do mouse, no ponto x = {$start->getX()}, y = {$start->getY()} e arrastar até o ponto  x = {$end->getX()}, y = {$end->getY()}
";
        }else if(get_class($c) == \Trixmote\Blocks\ClipboardBlock::class){
            $o .= "1. Enviar para area de transferência o texto \"*{$c->getContentWithoutLineBreaks()}*\"
";
        }else if(get_class($c) == \Trixmote\Blocks\KeyboardSimpleKeyBlock::class){
            $o .= "1. Inserir o caractere \"*{$c->getKey()}*\"
";
        }else if(get_class($c) == \Trixmote\Blocks\KeyboardModifierKeyBlock::class){

        }
    }

}


$md = new \cebe\markdown\Markdown();
echo $md->parse($o);