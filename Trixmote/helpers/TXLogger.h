#ifndef TRIX_LOGGER_H
#define TRIX_LOGGER_H

#include <string>
#include <time.h>
#include <fstream>

class TXLogger {

    static TXLogger *s_instance;
    const char *filePath;
    FILE *file;

public:
    int blockNewLineOnGroups;

    TXLogger() {
    }

    virtual ~TXLogger() {
        closeLogFile();
    }

    // Log de INFORMACAO para console
    static void i(std::string message);

    // Log de ERROR para console
    static void e(std::string message);

    // Log de AVISO para console
    static void w(std::string message);

    // Log de DEBUG para console
    static void d(std::string message);

    // Linha de separação para console
    static void line();

    // Cria/Reabre o arquivo de log, para armazenar os dados.
    void initLogFile(const char *filePath, bool appendMode);

    // Obter a instância singleton do TXLogger
    static TXLogger *instance();

    // Escreve no arquivo de log
    void write(const char *data);

    // Escreve no arquivo de log
    void write(int data);

    // Escreve no arquivo de log
    void write(float data);

    // Escreve no arquivo de log
    void write(bool data);

    // Escreve no arquivo de log
    void write(int64_t data);

    // Escreve no arquivo de log
    void write(std::string data);

    // Escreve no arquivo de log e quebra a linha no final
    void writeln(int data);

    // Escreve no arquivo de log e quebra a linha no final
    void writeln(std::string data);

    // Escreve no arquivo de log e quebra a linha no final
    void writeln(float data);

    // Escreve no arquivo de log e quebra a linha no final
    void writeln(bool data);

    // Escreve no arquivo de log e quebra a linha no final
    void writeln(int64_t data);

    // Escreve no arquivo de log e quebra a linha no final
    void writeln(const char *data);

    // Limpa o arquivo de log gerado por initLogFile
    void clearLogFile();

    // Fecha o arquivo de log gerado por initLogFile
    void closeLogFile();

};


#endif //TRIX_LOGGER_H
