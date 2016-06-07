#include "KSVLogger.h"
#include "KSVPresenter.h"
#include "KSVConfig.h"
#include <iostream>

using namespace std;

// Cria na memória o ponteiro ( não o objeto )
Logger *Logger::s_instance = 0;

void Logger::line() {
    cout << "---------------------------------------------------------------------" << endl;
}

void Logger::i(string message) {
    cout << "[INFO] " << message << endl;
}

void Logger::e(string message) {
    cout << "[ERROR] " << message << endl;
}

void Logger::w(string message) {
    cout << "[WARNING] " << message << endl;
}

void Logger::d(string message) {
    cout << "[DEBUG] " << message << endl;
}

void Logger::initLogFile(const char *fp, bool appendMode) {
    filePath = fp;
    file = fopen(fp, "a");
}

void Logger::closeLogFile() {
    if (file != NULL)
        fclose(file);
}

Logger *Logger::instance() {
    if (!s_instance) {
        s_instance = new Logger;
    }

    return s_instance;
}

void Logger::write(const char *data) {
    fprintf(file, "%s", data);
    fflush(file);

    if (KSV_LOGGER_WRITES_CONSOLE)
        std::cout << data;
}

void Logger::write(std::string data) {
    fprintf(file, "%s", data.c_str());
    fflush(file);

    if (KSV_LOGGER_WRITES_CONSOLE)
        std::cout << data;
}

void Logger::write(int data) {
    fprintf(file, "%i", data);
    fflush(file);

    if (KSV_LOGGER_WRITES_CONSOLE)
        std::cout << data;
}

void Logger::write(float data) {
    fprintf(file, "%f", data);
    fflush(file);

    if (KSV_LOGGER_WRITES_CONSOLE)
        std::cout << data;
}

void Logger::writeln(const char *data) {
    fprintf(file, "%s\n", data);
    fflush(file);

    if (KSV_LOGGER_WRITES_CONSOLE)
        std::cout << data << std::endl;
}

void Logger::writeln(std::string data) {
    fprintf(file, "%s\n", data.c_str());
    fflush(file);

    if (KSV_LOGGER_WRITES_CONSOLE)
        std::cout << data << std::endl;
}

void Logger::writeln(int data) {
    fprintf(file, "%i\n", data);
    fflush(file);

    if (KSV_LOGGER_WRITES_CONSOLE)
        std::cout << data << std::endl;
}

void Logger::writeln(float data) {
    fprintf(file, "%f\n", data);
    fflush(file);

    if (KSV_LOGGER_WRITES_CONSOLE)
        std::cout << data << std::endl;
}

void Logger::clearLogFile() {
    fopen(filePath, "w");

    writeln(Presenter::version());
}













