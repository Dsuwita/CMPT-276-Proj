//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// testVesselSimple.cpp — simple unit test for Vessel::saveAll and ::loadAll
// Version History:
//   v1.1 (2025‑07‑24) — uses saveAll/loadAll with std::vector
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include <iostream>
#include <vector>
#include <cstdio>     
#include "../Vessel.h"    
#include "../Sailing.h"

int main() {
    bool pass = true;

    // 1) Create vessel
    Vessel v(42, "TestVessel", 20.0f, 10.0f);
    pass &= (v.vesselID == 42);
    pass &= (std::string(v.vesselName) == "TestVessel");
    pass &= (v.HCLL == 20.0f);
    pass &= (v.LCLL == 10.0f);

    // 2) Add a sailing
    date d = {1, 1, 2025, 12};
    Sailing s;
    std::strncpy(s.sailingID, "S12345678", SAILING_ID_LEN);
    s.departureDate = d;
    s.HRL = 5.0f;
    s.LRL = 3.0f;

    v.addSailing(s);
    pass &= (!v.sailings.empty());
    pass &= (std::string(v.sailings[0].sailingID) == "S12345678");

    std::cout << (pass ? "Pass\n" : "Fail\n");
    return pass ? 0 : 1;
}
