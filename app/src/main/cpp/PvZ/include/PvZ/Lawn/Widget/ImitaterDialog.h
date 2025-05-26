#ifndef PVZ_LAWN_IMITATER_DIALOG_H
#define PVZ_LAWN_IMITATER_DIALOG_H

#include "PvZ/Enums.h"

inline SeedType (*ImitaterDialog_SeedHitTest)(LawnDialog *, int, int);


inline void (*old_ImitaterDialog_ImitaterDialog)(LawnDialog *instance, int a2);

inline void (*old_ImitaterDialog_ShowToolTip)(LawnDialog *instance);

inline bool (*old_ImitaterDialog_KeyDown)(LawnDialog *a, int a2);

inline void (*old_ImitaterDialog_MouseDown)(LawnDialog *a, int x, int y, int theCount);


void ImitaterDialog_ImitaterDialog(LawnDialog *instance, int playerIndex);

void ImitaterDialog_ShowToolTip(LawnDialog *instance);

bool ImitaterDialog_KeyDown(LawnDialog *a, int a2);

void ImitaterDialog_MouseDown(LawnDialog *a, int x, int y, int theCount);

#endif // PVZ_LAWN_IMITATER_DIALOG_H
