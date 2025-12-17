/*
* Copyright (C) 2023-2025  PvZ TV Touch Team
*
* This file is part of PlantsVsZombies-AndroidTV.
*
* PlantsVsZombies-AndroidTV is free software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or (at your
* option) any later version.
*
* PlantsVsZombies-AndroidTV is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
* Public License for more details.
*
* You should have received a copy of the GNU General Public License along with
* PlantsVsZombies-AndroidTV.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef PVZ_SEXYAPPFRAMEWORK_MISC_MTRAND_H
#define PVZ_SEXYAPPFRAMEWORK_MISC_MTRAND_H

#include <string>

namespace Sexy {

constexpr int MTRAND_N = 624;

class MTRand {
    unsigned long mt[MTRAND_N]; /* the array for the state vector  */
    int mti;

public:
    MTRand(const std::string &theSerialData);
    MTRand(unsigned long seed);
    MTRand();

    void SRand(const std::string &theSerialData);
    void SRand(unsigned long seed);
    unsigned long NextNoAssert();
    unsigned long Next();
    unsigned long NextNoAssert(unsigned long range);
    unsigned long Next(unsigned long range);
    float NextNoAssert(float range);
    float Next(float range);

    std::string Serialize();

    static void SetRandAllowed(bool allowed);
};

struct MTAutoDisallowRand {
    MTAutoDisallowRand() {
        MTRand::SetRandAllowed(false);
    }
    ~MTAutoDisallowRand() {
        MTRand::SetRandAllowed(true);
    }
};

} // namespace Sexy

#endif // PVZ_SEXYAPPFRAMEWORK_MISC_MTRAND_H
