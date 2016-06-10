#ifndef TRIX_INPUTLISTENER_H
#define TRIX_INPUTLISTENER_H

#include <fstream>
#include <CoreGraphics/CoreGraphics.h>
#include "TXLogger.h"

/**
 * Classe TXInputListener, observa e registra eventos de INPUT em Teclado e TXMouse.
 */
class TXInputListener {

public:

    TXInputListener() {
    }

    virtual ~TXInputListener() {
        // TODO - Liberar memória aqui.
    }

    // Thread Main Function*
    void operator()();

    // Registra a callback para eventos de teclado
    void initializeKeyboardTracker();

    // Registra a callback para eventos de mouse
    void initializeMouseTracker();

    // Callback para eventos de teclado
    static CGEventRef CGKeyboardInputEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon);

    // Callback para eventos de mouse
    static CGEventRef CGMouseClickEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon);

    // Analísa grupo de teclas modificadoras
    static void CGKeyboardModifierInputEventCallback(CGEventType type, CGEventRef event, const char *parsedKey, int keyCode, TXLogger *logger);
};

#endif //TRIX_INPUTLISTENER_H
