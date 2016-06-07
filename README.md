# ksv-trixlogger
KSV Trixlogger é um aplicativo para controle remoto de maquinas rodando sistema operacional OSX

# Bloco de informação

A estrutura de cada bloco de informação, contido no arquivo de saída (log) possui a seguinte estrutura:

`[ id : parâmetros [ texto ]]`

- Encapsulamento em `[` `]` determina o inicio e fim de cada bloco de informação;
-  O primeiro caractere de todo bloco é o `id` do bloco, que indica qual o tipo do evento capturado e consequentemente determina o restante da estrutura de parâmetros. ( um caractere seguido de um `:`);
- Os blocos podem conter N parâmetros ( separados por `:` ) ou um parâmetro do tipo *lista*, que é constituido de uma série de dados separados por um `|` pipe;
- Todo bloco de anuncio *pode* possuir uma informação genérica, livre de formatação (texto livre ou estruturado em alguns casos, veja a tabela *tipos de blocos de informação*), e possue um espaço específico dentro de cada bloco, que é no *final* do bloco antes do fechamento, também encapsulado por `[` `]`.

#### Exemplo de blocos

- `[c:1:1430.18x188.0664[left-click]]`
    - Este bloco indica um evento de clique simples com o botão esquerdo do mouse, na tela do usuário nas cordenadas 1430 x 188.

- `[d:1432.18x-78.0664|1438.12x-78.0664|1446.3x-78.0664|1461.16x-78.0664|1478.26x-78.0664|1493.13x-78.0664|1503.54x-78.0664[left-drag]]`  
    - Este bloco indica um evento de clicar e arrastar usando o botão esquerdo do mouse, possue uma lista de cordenadas X e Y percorridas pelo mouse durante o "arrastar".

- `[t:[T2xhIE11bmRvLCBCZW0gVmluZG8gYW8gS1NW]`
    - Este bloco indica que um texto foi capturado da area de transferência, e esta codificado em base64.

- - - 

#Tipos de blocos de informação

## Mouse
#### Blocos de informação para eventos de Mouse

|  ID |  Resumo     |  Descrição e dados contidos |
|:--------------:|------------|-----------------------------|
|      c:        |   Indica um evento de CLICK | - O primeiro atributo é o estado do clique, realizado pelo usuário, 1 para clique simples, 2 para clique duplo, 3 para clique triplo, etc.... <br><br> - O segundo atributo contém as cordenadas X e Y do mouse, no momento da captura do clique ( separados por `x` ). *Importante:* o valor de X ou de Y podem ser *negativos* se o usuário estiver usando dois monitores, por conta do alinhamento.<br><br> - O Terceiro parâmetro é um texto que informa qual é o botão do mouse usado |
|      d:        |   Indica um evento de CLICK AND DRAG | - Contém uma lista de cordenadas (x,y) (separados por `|` pipe) <br><br> - O Segundo parâmetro é um texto que informa qual é o botão do mouse usado para clicar e arrastar.



## Clipboard
#### Blocos de informação para rastreio de area de transferência

|  ID |  Resumo     |  Descrição e dados contidos |
|:--------------:|------------|-----------------------------|
|      t:        |   Armazena o valor capturado da area de transferência | - Não possui parâmetros, apenas o bloco de texto entre `[` `]`. O conteúdo dentro desse bloco é o que foi capturado da area de transferência do usuário, e esta codificado em base64, para garantir integridade do que foi capturado. |






























