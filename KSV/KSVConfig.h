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

// Lista de teclas de função
#define KSV_MDF_KEYS                 {54, 55, 56, 57, 58, 59, 60, 61, 62, 63}
#define KSV_MDF_MEMORY_ALLOCATION    10 // Little GB!!  Temporário...

#endif //KSV_KSVCONFIG_H
