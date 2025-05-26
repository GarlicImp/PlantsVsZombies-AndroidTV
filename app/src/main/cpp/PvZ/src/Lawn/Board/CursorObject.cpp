//
// Created by 28636 on 2025/5/26.
//

#include "PvZ/Lawn/Board/CursorObject.h"

bool CursorObject_BeginDraw(CursorObject *cursorObject, Sexy::Graphics *graphics) {
    return old_CursorObject_BeginDraw(cursorObject, graphics);
}

void CursorObject_EndDraw(CursorObject *cursorObject, Sexy::Graphics *graphics) {
    return old_CursorObject_EndDraw(cursorObject, graphics);
}