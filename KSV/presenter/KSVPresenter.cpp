#include "KSVPresenter.h"
#include <iostream>

const char *Presenter::version() {
    return "KSV TRIXLOGGER ~ Version 1.0 ~";
}

void Presenter::showHeader() {
    Presenter::showVersion();

    std::cout << std::endl;
    std::cout << " _  ________     __  _____     _      _                             \n"
            "| |/ / ___\\ \\   / / |_   _| __(_)_  _| | ___   __ _  __ _  ___ _ __ \n"
            "| ' /\\___ \\\\ \\ / /    | || '__| \\ \\/ / |/ _ \\ / _` |/ _` |/ _ \\ '__|\n"
            "| . \\ ___) |\\ V /     | || |  | |>  <| | (_) | (_| | (_| |  __/ |   \n"
            "|_|\\_\\____/  \\_/      |_||_|  |_/_/\\_\\_|\\___/ \\__, |\\__, |\\___|_|   \n"
            "                                              |___/ |___/       ";
    std::cout << std::endl;
    std::cout << std::endl;
}

void Presenter::showVersion() {
    std::cout << Presenter::version();
}

void Presenter::showHelp() {
    std::cout << "O KSV Keylogger é um aplicativo para controle remoto de computadores rodando sistema operacional OSX." << std::endl;
    std::cout << std::endl;
    std::cout << "\tksv [command] [-v|--version|-h|--help|-c|--clear|--disableClipboard|--disableKeylogger|--logFile <filePath>|" << std::endl;
    std::cout << "\t               --recordMacro|--deleteMacro|--executeMacro|--macroName]" << std::endl;
    std::cout << std::endl;

    std::cout << "Examples:" << std::endl;
    std::cout << "\tksv --version" << std::endl;
    std::cout << "\tksv --help" << std::endl;
    std::cout << "\tksv --disableClipboard --logFile /somefile.txt" << std::endl;
    std::cout << "\tksv --disableKeylogger --logFile /somefile.txt" << std::endl;
    std::cout << "\tksv --disableKeylogger --disableClipboard --logFile /somefile.txt" << std::endl;
    std::cout << "\tksv --clear --logFile /somefile.txt" << std::endl;
    std::cout << "\tksv --clear --disableClipboard --logFile /somefile.txt" << std::endl;
    // TODO - Macro Runner
    std::cout << "\tksv --recordMacro --macroName Macro_Abrir_Chrome_Pesquisar_LoremIpsum --logFile ~/Desktop/abre_chrome.ksvm" << std::endl;
    std::cout << "\tksv --deleteMacro --macroName Macro_Abrir_Chrome_Pesquisar_LoremIpsum" << std::endl;
    std::cout << "\tksv --executeMacro --macroName Macro_Abrir_Chrome_Pesquisar_LoremIpsum" << std::endl;
    std::cout << "\tksv --executeMacro --logFile ~/Desktop/abre_chrome.ksvm" << std::endl;
    std::cout << "\tksv --deleteMacro --logFile ~/Desktop/abre_chrome.ksvm" << std::endl;
    std::cout << std::endl;

    std::cout << "Commands:" << std::endl;
    std::cout << "\t--clear              Faz com que o KSV limpe o arquivo <--logFile> antes de iniciar os processos do KSV." << std::endl;
    std::cout << "\t--version            Mostra a versão do KSV." << std::endl;
    std::cout << "\t--help               Mostra essa página de ajuda." << std::endl;
    std::cout << "\t--disableClipboard   Inicia o KSV com o módulo do Clipboard desativado." << std::endl;
    std::cout << "\t--disableKeylogger   Inicia o KSV com o módulo do Keylogger desativado.--logFile /somefile.txt" << std::endl;
    std::cout << "\t--logFile <path>     Diz ao KSV aonde o arquivo de log deve ser salvo." << std::endl;
    // TODO - Macro Runner
    std::cout << "\t--recordMacro        Executa o KSV no modo de gravação de macros (em arquivo especificado em --logFile), para ser re-executado posteriormente chamando --executeMacro" << std::endl;
    std::cout << "\t--executeMacro       Executa uma Macro gravada usando --recordMacro (de arquivo .ksvm)" << std::endl;
    std::cout << "\t--macroName          Define o nome da Macro a ser gravada, ou executada. Não pode conter espaços ou caracteres especiais" << std::endl;
    std::cout << "\t--deleteMacro        Deleta uma macro gravada usando --recordMacro, a macro a ser deletada pode ser definida usando --logFile ou --macroName" << std::endl;

    std::cout << std::endl;
}


