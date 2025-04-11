#ifndef PVZ_LAWN_HELP_TEXT_SCREEN_H
#define PVZ_LAWN_HELP_TEXT_SCREEN_H

#include "PvZ/Enums.h"

inline void (*HelpTextScreen_KeyDown)(Sexy::Widget *, int);


inline void (*old_HelpTextScreen_Update)(Sexy::Widget *helpTextScreen);

inline void (*old_HelpTextScreen_Draw)(Sexy::Widget *helpTextScreen, Sexy::Graphics *graphics);

inline void (*old_HelpTextScreen_HelpTextScreen)(Sexy::Widget *helpTextScreen, int *lawnApp, int pageIndex);

inline void (*old_HelpTextScreen_AddedToManager)(Sexy::Widget *helpTextScreen, int *manager);

inline void (*old_HelpTextScreen_MouseDown)(Sexy::Widget *helpTextScreen, int x, int y, int theClickCount);

inline void (*old_HelpTextScreen_RemovedFromManager)(Sexy::Widget *helpTextScreen, int *widgetManager);

inline void (*old_HelpTextScreen_Delete2)(Sexy::Widget *helpTextScreen);

inline void (*old_HelpTextScreen_ButtonDepress)(Sexy::Widget *helpTextScreen, int);


void HelpTextScreen_Update(Sexy::Widget *helpTextScreen);

void HelpTextScreen_Draw(Sexy::Widget *helpTextScreen, Sexy::Graphics *graphics);

void HelpTextScreen_HelpTextScreen(Sexy::Widget *helpTextScreen, int *lawnApp, int pageIndex);

void HelpTextScreen_AddedToManager(Sexy::Widget *helpTextScreen, int *manager);

void HelpTextScreen_MouseDown(Sexy::Widget *helpTextScreen, int x, int y, int theClickCount);

void HelpTextScreen_RemovedFromManager(Sexy::Widget *helpTextScreen, int *widgetManager);

void HelpTextScreen_Delete2(Sexy::Widget *helpTextScreen);

void HelpTextScreen_ButtonDepress(Sexy::Widget *helpTextScreen, int id);

#endif // PVZ_LAWN_HELP_TEXT_SCREEN_H
