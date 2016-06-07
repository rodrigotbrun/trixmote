#ifndef KSV_KSVCONFIG_H
#define KSV_KSVCONFIG_H

// Limite de bytes que podem ser lidos/salvos pelo ouvinte do Clipboard.
#define KSV_CLIPBOARD_MAX_BYTES     400

// Intervalo (sleep) entre iterações do ouvinte do Clipboard. (em Milisegundos)
#define KSV_CLIPBOARD_INTERVAL      255

// Quantidade de vezes em que o KSV pode tentar registrar novamente um evento caso não tenha sucesso
#define KSV_RETRY_MAX_COUNT         3

// Imprimir no console tudo que é gravado em arquivo ou transmitido
#define KSV_LOGGER_WRITES_CONSOLE   1

#endif //KSV_KSVCONFIG_H
