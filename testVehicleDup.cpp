//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// testSailingOps.cpp — unit test for Sailing file I/O into Vessel
// Version History:
//   v1.0 (2025‑07‑24) — basic test for add/load sailing with fixed array
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include <iostream>
#include <cstdio>      
#include <vector>
#include "Vessel.h"   
#include "Sailing.h"   

int main() {
    // 1) Clean slate: remove both files
    std::remove("vessels.dat");
    std::remove("sailings.dat");

    // 2) Create and save one vessel
    std::vector<Vessel> vessels;
    Vessel v(1, "Endeavour", 12.5f, 6.3f);
    vessels.push_back(v);

    // 3) Add one sailing to that vessel
    Sailing s;
    std::strncpy(s.sailingID, "S001", SAILING_ID_LEN);
    s.sailingID[SAILING_ID_LEN - 1] = '\0';
    s.departureDate = {24, 7, 2025, 14};
    s.HRL = 5;
    s.LRL = 2;

    v.sailings.push_back(s);

    // Save sailing (simulate saveAll)
    SailingRecord rec;
    std::memset(&rec, 0, sizeof(SailingRecord));
    std::strncpy(rec.sailingID, s.sailingID, SAILING_ID_LEN);
    rec.day = s.departureDate.day;
    rec.month = s.departureDate.month;
    rec.year = s.departureDate.year;
    rec.hour = s.departureDate.hour;
    rec.HRL = s.HRL;
    rec.LRL = s.LRL;
    rec.vesselID = v.vesselID;

    std::ofstream out("sailings.dat", std::ios::binary);
    out.write(reinterpret_cast<char*>(&rec), sizeof(SailingRecord));
    out.close();

    // 4) Load back into a new vessel
    std::vector<Vessel> loadedVessel;
    Sailing::loadAll(loadedVessel);  // assumes loadAll(Vessel&)

    Vessel loaded = loadedVessel[0];

    bool pass = true;
    pass &= (loaded.vesselID == 1);
    pass &= (loaded.sailings.size() == 1);
    pass &= (std::strncmp(loaded.sailings[0].sailingID, "S001", SAILING_ID_LEN) == 0);
    pass &= (loaded.sailings[0].departureDate.day == 24);
    pass &= (loaded.sailings[0].departureDate.hour == 14);
    pass &= (loaded.sailings[0].HRL == 5);
    pass &= (loaded.sailings[0].LRL == 2);

    std::cout << (pass ? "Pass\n" : "Fail\n");
    return pass ? 0 : 1;
}
