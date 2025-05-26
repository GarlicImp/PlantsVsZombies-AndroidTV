//
// Created by 28636 on 2025/5/26.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_BUTTONLISTENER_H
#define PLANTSVSZOMBIES_ANDROIDTV_BUTTONLISTENER_H


namespace Sexy {

struct ButtonListenerVTable {
    void *Delete;
    void *Delete2;
    void *ButtonPress;
    void *ButtonPress2;
    void *ButtonDepress;
    void *ButtonDownTick;
    void *ButtonMouseEnter;
    void *ButtonMouseLeave;
    void *ButtonMouseMove;
};

class ButtonListener {
public:
    ButtonListenerVTable *vTable;
};

}


#endif // PLANTSVSZOMBIES_ANDROIDTV_BUTTONLISTENER_H
