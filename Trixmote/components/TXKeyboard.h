#ifndef TRIX_KEYBOARD_H
#define TRIX_KEYBOARD_H

class TXKeyboard {

public:

    /**
     * Converte para o caractere correspondente na tabela ASCII
     */
    static const char *convertKeyCode(int key);

    static bool isMDFKey(int keyCode);

    static int MDFKeyIndex(int keyCode);
};


#endif //TRIX_KEYBOARD_H
