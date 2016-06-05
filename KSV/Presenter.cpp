#include "Presenter.h"
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


