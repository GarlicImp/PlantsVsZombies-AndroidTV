#ifndef PVZ_LAWN_ALMANAC_DIALOG_H
#define PVZ_LAWN_ALMANAC_DIALOG_H

#include "PvZ/Enums.h"

class AlmanacDialog : public LawnDialog {
public:
    int *mScrollListener;                                                    // 191
    LawnApp *mApp;                                                           // 192
    Sexy::GameButton *mViewPlantButton;                                      // 193
    Sexy::GameButton *mViewZombieButton;                                     // 194
    Sexy::CustomScrollbarWidget *mScrollTextView;                            // 195
    int mOpenPage;                                                           // 196
    SeedType::SeedType mSelectedSeed;                                        // 197
    ZombieType mSelectedZombie;                                  // 198
    Plant *mPlant;                                                           // 199
    Zombie *mZombie;                                                         // 200
    TRect mUnkRect;                                                          // 201 ~ 204
    TRect mDescriptionRect;                                                  // 205 ~ 208
    TRect mCostRect;                                                         // 209 ~ 212
    TRect mWaitTimeRect;                                                     // 213 ~ 216
    int unk2[2];                                                             // 217 ~ 218
    char *mNameString;                                                       // 219
    char *mDescriptionHeaderString;                                          // 220
    char *mDescriptionStringTmp;                                             // 221
    char *mDescriptionString;                                                // 222
    char *mCostString;                                                       // 223
    char *mWaitTimeString;                                                   // 224
    DrawStringJustification::DrawStringJustification mWaitTimeJustification; // 225
    DrawStringJustification::DrawStringJustification mJustification;         // 226
    bool mSetupFinished;                                                     // 227 * 4
    double unk3;                                                             // 228 ~ 229
    int *mHelpBarWidget;                                                     // 230
    int unk4[11];                                                            // 231 ~ 233
}; // 115: 234, 111: 236

inline bool (*AlmanacDialog_KeyDown)(AlmanacDialog *, int);

inline SeedType::SeedType (*AlmanacDialog_SeedHitTest)(AlmanacDialog *, int, int);

inline ZombieType (*AlmanacDialog_ZombieHitTest)(AlmanacDialog *, int, int);

inline void (*AlmanacDialog_SetupPlant)(AlmanacDialog *);

inline void (*AlmanacDialog_SetupZombie)(AlmanacDialog *);

inline void (*AlmanacDialog_GetSeedPosition)(AlmanacDialog *almanacDialog, int seedType, int *x, int *y);


inline void (*old_AlmanacDialog_AlmanacDialog)(AlmanacDialog *almanacDialog, LawnApp *lawnApp);

inline void (*old_AlmanacDialog_SetPage)(AlmanacDialog *almanacDialog, int targetPage);

inline void (*old_AlmanacDialog_MouseDrag)(AlmanacDialog *almanacDialog, int, int);

inline void (*old_AlmanacDialog_RemovedFromManager)(AlmanacDialog *almanacDialog, int *manager);

inline void (*old_AlmanacDialog_Delete2)(AlmanacDialog *almanacDialog);

inline void (*old_AlmanacDialog_DrawPlants)(AlmanacDialog *almanacDialog, Sexy::Graphics *graphics);

inline void (*old_AlmanacDialog_SetupLayoutPlants)(AlmanacDialog *almanacDialog, Sexy::Graphics *graphics);


void AlmanacDialog_AlmanacDialog(AlmanacDialog *almanacDialog, LawnApp *lawnApp);

void AlmanacDialog_SetPage(AlmanacDialog *almanacDialog, int targetPage);

void AlmanacDialog_MouseDown(AlmanacDialog *almanacDialog, int x, int y, int a4);

void AlmanacDialog_MouseDrag(AlmanacDialog *almanacDialog, int x, int y);

void AlmanacDialog_MouseUp(AlmanacDialog *almanacDialog, int x, int y, int a4);

void AlmanacDialog_RemovedFromManager(AlmanacDialog *almanacDialog, int *manager);

void AlmanacDialog_Delete2(AlmanacDialog *almanacDialog);

void AlmanacDialog_ButtonDepress(AlmanacDialog *almanacDialog, int id);

void AlmanacDialog_DrawPlants_Unmodified(AlmanacDialog *almanacDialog, Sexy::Graphics *graphics);

void AlmanacDialog_DrawPlants(AlmanacDialog *almanacDialog, Sexy::Graphics *graphics);

void AlmanacDialog_SetupLayoutPlants(AlmanacDialog *almanacDialog, Sexy::Graphics *graphics);

#endif // PVZ_LAWN_ALMANAC_DIALOG_H
