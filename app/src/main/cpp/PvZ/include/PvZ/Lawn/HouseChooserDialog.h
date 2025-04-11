#ifndef PVZ_LAWN_HOUSE_CHOOSER_DIALOG_H
#define PVZ_LAWN_HOUSE_CHOOSER_DIALOG_H

#include "PvZ/Enums.h"

class HouseChooserDialog : public LawnDialog {
public:
    HouseType::HouseType mSelectedHouseType; // 191
    int unk[2];                              // 192 ~ 193
}; // 115: 194, 111: 196

inline void (*HouseChooserDialog_GameButtonDown)(HouseChooserDialog *, int code, int a3, bool a4);


inline void (*old_HouseChooserDialog_MouseDown)(HouseChooserDialog *a, int x, int y, int theCount);

inline void (*old_HouseChooserDialog_KeyDown)(HouseChooserDialog *a, int x);


bool HouseChooserDialog_IsHouseAvaliable(HouseType::HouseType houseType);

void HouseChooserDialog_MouseDown(HouseChooserDialog *a, int x, int y, int theCount);

void HouseChooserDialog_KeyDown(HouseChooserDialog *a, int keyCode);

#endif // PVZ_LAWN_HOUSE_CHOOSER_DIALOG_H
