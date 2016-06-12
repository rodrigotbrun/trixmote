#include "TXLogger.h"
#include "TXPresenter.h"
#include "TXConfig.h"
#include <iostream>

using namespace std;

// Cria na memória o ponteiro ( não o objeto )
TXLogger *TXLogger::s_instance = 0;

void TXLogger::line() {
    cout << "---------------------------------------------------------------------" << endl;
}

void TXLogger::i(string message) {
    cout << "[INFO] " << message << endl;
}

void TXLogger::e(string message) {
    cout << "[ERROR] " << message << endl;
}

void TXLogger::w(string message) {
    cout << "[WARNING] " << message << endl;
}

void TXLogger::d(string message) {
    cout << "[DEBUG] " << message << endl;
}

void TXLogger::initLogFile(const char *fp, bool appendMode) {
    filePath = fp;
    file = fopen(fp, "a");
}

void TXLogger::closeLogFile() {
    if (file != NULL)
        fclose(file);
}

TXLogger *TXLogger::instance() {
    if (!s_instance) {
        s_instance = new TXLogger;
    }

    return s_instance;
}

void TXLogger::write(const char *data) {
    fprintf(file, "%s", data);
    fflush(file);

    if (TRIX_LOGGER_WRITES_CONSOLE)
        std::cout << data;
}

void TXLogger::write(std::string data) {
    fprintf(file, "%s", data.c_str());
    fflush(file);

    if (TRIX_LOGGER_WRITES_CONSOLE)
        std::cout << data;
}

void TXLogger::write(int data) {
    fprintf(file, "%i", data);
    fflush(file);

    if (TRIX_LOGGER_WRITES_CONSOLE)
        std::cout << data;
}

void TXLogger::write(float data) {
    fprintf(file, "%f", data);
    fflush(file);

    if (TRIX_LOGGER_WRITES_CONSOLE)
        std::cout << data;
}

void TXLogger::write(bool data) {
    fprintf(file, "%i", data);
    fflush(file);

    if (TRIX_LOGGER_WRITES_CONSOLE)
        std::cout << data;
}

void TXLogger::write(int64_t data) {
    write((int) data);
}

void TXLogger::writeln(int64_t data) {
    writeln((int) data);
}

void TXLogger::writeln(const char *data) {
    if (blockNewLineOnGroups) {
        write(data);
    } else {
        fprintf(file, "%s\n", data);
        fflush(file);

        if (TRIX_LOGGER_WRITES_CONSOLE)
            std::cout << data << std::endl;
    }
}

void TXLogger::writeln(std::string data) {
    if (blockNewLineOnGroups) {
        write(data);
    } else {
        fprintf(file, "%s\n", data.c_str());
        fflush(file);

        if (TRIX_LOGGER_WRITES_CONSOLE)
            std::cout << data << std::endl;
    }
}

void TXLogger::writeln(int data) {
    if (blockNewLineOnGroups) {
        write(data);
    } else {
        fprintf(file, "%i\n", data);
        fflush(file);

        if (TRIX_LOGGER_WRITES_CONSOLE)
            std::cout << data << std::endl;
    }
}

void TXLogger::writeln(bool data) {
    if (blockNewLineOnGroups) {
        write(data);
    } else {
        fprintf(file, "%i\n", data);

        fflush(file);

        if (TRIX_LOGGER_WRITES_CONSOLE)
            std::cout << data << std::endl;
    }
}

void TXLogger::writeln(float data) {
    if (blockNewLineOnGroups) {
        write(data);
    } else {
        fprintf(file, "%f\n", data);
        fflush(file);

        if (TRIX_LOGGER_WRITES_CONSOLE)
            std::cout << data << std::endl;
    }
}

void TXLogger::clearLogFile() {
    fopen(filePath, "w");

    writeln(TXPresenter::version());
}


std::string TXLogger::getTemDir() {
    return tempDir;
}

void TXLogger::setTempDir(std::string td) {
    tempDir = td;
}

void TXLogger::setImagickBinDir(std::string im) {
    imagickBinDir = im;
}

std::string TXLogger::getImagickBinDir() {
    return imagickBinDir;
}



















