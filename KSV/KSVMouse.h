#ifndef KSV_MOUSE_H
#define KSV_MOUSE_H

#include <CoreGraphics/CoreGraphics.h>

class Mouse {

public:
    static const char *convertMouseEvent(CGEventType type);

    static CGPoint getCursorPosition();

};


#endif //KSV_MOUSE_H
