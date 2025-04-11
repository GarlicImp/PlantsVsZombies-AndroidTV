#ifndef PVZ_LAWN_AWARD_SCREEN_H
#define PVZ_LAWN_AWARD_SCREEN_H

inline void (*AwardScreen_StartButtonPressed)(int *);

inline void (*old_AwardScreen_MouseDown)(int *awardScreen, int x, int y, int theClickCount);

inline void (*old_AwardScreen_MouseUp)(int *awardScreen, int x, int y, int theClickCount);

void AwardScreen_MouseDown(int *awardScreen, int x, int y, int theClickCount);

void AwardScreen_MouseUp(int *awardScreen, int x, int y, int theClickCount);

#endif // PVZ_LAWN_AWARD_SCREEN_H
