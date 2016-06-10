#ifndef TRIX_MOUSE_H
#define TRIX_MOUSE_H

#include <CoreGraphics/CoreGraphics.h>

class TXMouse {

public:
    static const char *convertMouseEvent(CGEventType type);

    static CGPoint getCursorPosition();

};


#endif //TRIX_MOUSE_H
