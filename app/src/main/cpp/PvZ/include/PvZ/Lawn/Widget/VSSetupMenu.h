#ifndef PVZ_LAWN_VS_SETUP_MENU_H
#define PVZ_LAWN_VS_SETUP_MENU_H

class VSSetUpMenu {
    int m;

public:
};

inline void (*VSSetupMenu_GameButtonDown)(int *a, int a2, unsigned int a3, int a4);


inline void (*old_VSSetupMenu_Update)(int *a);

inline void (*old_VSSetupMenu_KeyDown)(int *a, int a2);


void VSSetupMenu_Update(int *a);

void VSSetupMenu_KeyDown(int *a, int a2);

#endif // PVZ_LAWN_VS_SETUP_MENU_H
