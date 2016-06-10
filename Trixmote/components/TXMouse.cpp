#include "TXMouse.h"

/**
 * Converte um tipo de mouse para uma string legível
 */
const char *TXMouse::convertMouseEvent(CGEventType type) {

    switch ((int) type) {
        case 1:
            return "[left-click]";
        case 3:
            return "[right-click]";
        case 6:
            return "[left-drag]";
        case 7:
            return "[right-drag]";
        default:
            return "[unknow]";
    }

}


/**
 * Obtem as cordenadas atuais do mouse.
 */
CGPoint TXMouse::getCursorPosition() {

    // Apenas para o SO ter como referencia, criamos um evento em branco
    CGEventRef mousePositionEvent = CGEventCreate(NULL);

    // As cordenadas na tela de onde esta o mouse
    CGPoint cursor = CGEventGetLocation(mousePositionEvent);

    // Liberamos o evento
    CFRelease(mousePositionEvent);

    // Retorna as cordenadas
    return cursor;
}



