//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// testFileOps.cpp — unit test for Vessel file I/O
// Version History:
//   v1.0 (2025‑07‑24) — initial test of add/load & EOF behavior
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include <iostream>
#include <cstdio>      // for std::remove
#include "Vessel.h"    // your Vessel interface

int main() {
    // 1) Clean slate: remove any existing data file
    std::remove("vessels.dat");

    // 2) Create two vessels and save to file
    Vessel v1(1, "Alpha", 10.5f, 5.2f);
    Vessel v2(2, "Beta",  8.3f, 4.1f);
    v1.save();
    v2.save();

    // 3) Load them back into new objects
    Vessel u1(1, "", 0, 0);
    Vessel u2(2, "", 0, 0);
    u1.load();
    u2.load();

    bool pass = true;
    pass &= (u1.vesselID   == 1);
    pass &= (u1.vesselName == "Alpha");
    pass &= (u1.HCLL       == 10.5f);
    pass &= (u1.LCLL       ==  5.2f);

    pass &= (u2.vesselID   == 2);
    pass &= (u2.vesselName == "Beta");
    pass &= (u2.HCLL       ==  8.3f);
    pass &= (u2.LCLL       ==  4.1f);

    // 4) Test EOF: try reading a 3rd record directly
    std::ifstream in("vessels.dat", std::ios::binary);
    char buffer[sizeof(Vessel)];
    in.read(buffer, sizeof(buffer)); // first
    in.read(buffer, sizeof(buffer)); // second
    in.read(buffer, sizeof(buffer)); // should fail / hit EOF
    pass &= (in.gcount() < static_cast<std::streamsize>(sizeof(buffer)));

    std::cout << (pass ? "Pass\n" : "Fail\n");
    return pass ? 0 : 1;
}
