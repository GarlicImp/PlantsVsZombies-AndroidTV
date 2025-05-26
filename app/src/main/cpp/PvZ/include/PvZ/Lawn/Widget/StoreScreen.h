#ifndef PVZ_LAWN_STORE_SCREEN_H
#define PVZ_LAWN_STORE_SCREEN_H

#include "PvZ/Lawn/Common/ConstEnums.h"
#include "PvZ/Symbols.h"
#include "PvZ/SexyAppFramework/Widget/Widget.h"

class StoreScreen {
public:
//    int SetSelectedSlot(int theIndex) { return reinterpret_cast<int (*)(StoreScreen*, int)>(StoreScreen_SetSelectedSlotAddr)(this, theIndex);};
//
//    void MouseDown(int x, int y, int theClickCount);
};

inline void (*StoreScreen_AdvanceCrazyDaveDialog)(int *);

inline bool (*StoreScreen_CanInteractWithButtons)(int *);

inline StoreItem (*StoreScreen_GetStoreItemType)(int *, int);

inline void (*StoreScreen_GetStoreItemInfo)(int *, int, StoreItem, Sexy::Image **, int *, int *, int *);

inline bool (*StoreScreen_IsItemSoldOut)(int *, StoreItem);

inline bool (*StoreScreen_IsItemUnavailable)(int *, StoreItem);

inline bool (*StoreScreen_IsComingSoon)(int *, StoreItem);

inline bool (*StoreScreen_IsPageShown)(int *, int);

inline void (*StoreScreen_EnableButtons)(int *, bool);

inline bool (*StoreScreen_IsPottedPlant)(int *, StoreItem);


inline void (*old_StoreScreen_AddedToManager)(int *a, int a2);

inline void (*old_StoreScreen_RemovedFromManager)(int *a, int a2);

inline void (*old_StoreScreen_Update)(int a);

inline void (*old_StoreScreen_SetupPage)(int *a);

inline void (*old_StoreScreen_DrawItem)(int *a1, Sexy::Graphics *a2, int a3, StoreItem item);

inline void (*old_StoreScreen_ButtonDepress)(int *, int);

inline void (*old_StoreScreen_PurchaseItem)(int *, StoreItem);

inline void (*old_StoreScreen_Draw)(int *storeScreen, Sexy::Graphics *a2);

inline void (*old_StoreScreen_MouseDown)(int *storeScreen, int x, int y, int theClickCount);

inline void (*old_StoreScreen_MouseUp)(int *storeScreen, int x, int y, int theClickCount);


void StoreScreen_AddedToManager(int *a, int a2);

void StoreScreen_RemovedFromManager(int *a, int a2);

void StoreScreen_Update(int a);

void StoreScreen_SetupPage(int *a);

void StoreScreen_DrawItem(int *a1, Sexy::Graphics *a2, int a3, StoreItem item);

void StoreScreen_ButtonDepress(int *storeScreen, int buttonId);

void StoreScreen_PurchaseItem(int *storeScreen, StoreItem item);

void StoreScreen_Draw(int *storeScreen, Sexy::Graphics *a2);

void StoreScreen_MouseDown(int *storeScreen, int x, int y, int theClickCount);

void StoreScreen_MouseUp(int *storeScreen, int x, int y, int theClickCount);


#endif // PVZ_LAWN_STORE_SCREEN_H
