#ifndef PVZ_LAWN_ZEN_GARDEN_H
#define PVZ_LAWN_ZEN_GARDEN_H

#include "PvZ/Enums.h"

inline int *(*ZenGarden_GetStinky)(int **zenGarden);

inline bool (*ZenGarden_IsStinkyHighOnChocolate)(int *zenGarden);

inline void (*ZenGarden_OpenStore)(int *);

inline int (*ZenGarden_GetPottedPlantInWheelbarrow)(int *);

inline void (*ZenGarden_DrawPottedPlant)(int *a1, Sexy::Graphics *g, float x, float y, PottedPlant *thePottedPlant, float theScale, bool theDrawPot);

inline float (*PlantFlowerPotHeightOffset)(SeedType, float);


inline void (*old_ZenGarden_DrawBackdrop)(int *zenGarden, int *graphics);


void ZenGarden_DrawBackdrop(int *zenGarden, int *graphics);

#endif // PVZ_LAWN_ZEN_GARDEN_H
