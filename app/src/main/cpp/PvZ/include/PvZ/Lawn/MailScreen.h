#ifndef PVZ_LAWN_MAIL_SCREEN_H
#define PVZ_LAWN_MAIL_SCREEN_H

#include "PvZ/Enums.h"

class MailScreen : public LawnDialog {
public:
    int unk[3];   // 191 ~ 193
    int mPage;    // 194
    int unk2[12]; // 195 ~ 206
    // 115: 207, 111: 209
public:
    void MouseDown(int x, int y, int theClickCount);
    void MouseUp(int x, int y);
    void MouseDrag(int x, int y);
};

inline void (*MailScreen_KeyDown)(MailScreen *mailScreen, int keyCode, int, int);


inline void (*old_MailScreen_MailScreen)(MailScreen *mailScreen, LawnApp *lawnApp);

inline void (*old_MailScreen_AddedToManager)(MailScreen *mailScreen, int *widgetManager);

inline void (*old_MailScreen_RemovedFromManager)(MailScreen *mailScreen, int *widgetManager);

inline void (*old_MailScreen_Delete2)(MailScreen *mailScreen);

inline void (*old_MailScreen_ButtonPress)(MailScreen *mailScreen, int id);

inline void (*old_MailScreen_ButtonDepress)(MailScreen *mailScreen, int id);

inline void (*old_MailScreen_MouseDown)(MailScreen *mailScreen, int x, int y, int theClickCount);

inline void (*old_MailScreen_MouseDrag)(MailScreen *mailScreen, int x, int y);

inline void (*old_MailScreen_MouseUp)(MailScreen *mailScreen, int x, int y);


void MailScreen_MailScreen(MailScreen *mailScreen, LawnApp *lawnApp);

void MailScreen_AddedToManager(MailScreen *mailScreen, int *widgetManager);

void MailScreen_RemovedFromManager(MailScreen *mailScreen, int *widgetManager);

void MailScreen_Delete2(MailScreen *mailScreen);

void MailScreen_ButtonPress(MailScreen *mailScreen, int id);

void MailScreen_ButtonDepress(MailScreen *mailScreen, int id);

#endif // PVZ_LAWN_MAIL_SCREEN_H
