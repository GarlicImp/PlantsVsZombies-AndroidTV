#ifndef PVZ_LAWN_ZEN_GARDEN_H
#define PVZ_LAWN_ZEN_GARDEN_H

#include "PvZ/Lawn/Common/ConstEnums.h"
#include "PvZ/SexyAppFramework/Graphics/Graphics.h"

class LawnApp;
class Board;
class PottedPlant;
class SpecialGridPlacement {
public:
    int mPixelX;
    int mPixelY;
    int mGridX;
    int mGridY;
};

class ZenGarden {
public:
    LawnApp *mApp;          //+0x0
    Board *mBoard;          //+0x4
    GardenType mGardenType; //+0x8

    SpecialGridPlacement *GetSpecialGridPlacements(int &theCount);
    int GridToPixelX(int theGridX, int theGridY);
    int GridToPixelY(int theGridX, int theGridY);
};

inline int *(*ZenGarden_GetStinky)(ZenGarden **zenGarden);

inline bool (*ZenGarden_IsStinkyHighOnChocolate)(ZenGarden *zenGarden);

inline void (*ZenGarden_OpenStore)(ZenGarden *);

inline int (*ZenGarden_GetPottedPlantInWheelbarrow)(ZenGarden *);

inline void (*ZenGarden_DrawPottedPlant)(ZenGarden *a1, Sexy::Graphics *g, float x, float y, PottedPlant *thePottedPlant, float theScale, bool theDrawPot);


inline void (*old_ZenGarden_DrawBackdrop)(ZenGarden *zenGarden, int *graphics);


void ZenGarden_DrawBackdrop(ZenGarden *zenGarden, int *graphics);

#endif // PVZ_LAWN_ZEN_GARDEN_H
