#ifndef PVZ_LAWN_VS_RESULTS_MENU_H
#define PVZ_LAWN_VS_RESULTS_MENU_H

#include "PvZ/Enums.h"

class VSResultsMenu {
    int m;

public:
};

inline void (*old_VSResultsMenu_Update)(int *a);

inline void (*old_VSResultsMenu_OnExit)(int *a);

inline void (*old_VSResultsMenu_DrawInfoBox)(int *a, Sexy::Graphics *a2, int a3);


void VSResultsMenu_Update(int *a);

void VSResultsMenu_OnExit(int *a);

void VSResultsMenu_ButtonDepress(int *vsResultsScreen, int buttonId);

void VSResultsMenu_DrawInfoBox(int *a, Sexy::Graphics *a2, int a3);

#endif // PVZ_LAWN_VS_RESULTS_MENU_H
