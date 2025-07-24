//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// testFileOps.cpp — unit test for Vessel file I/O
// Version History:
//   v1.1 (2025‑07‑24) — adjusted to use VesselRecord for binary ops
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include <iostream>
#include <fstream>
#include <cstdio>      // for std::remove
#include "Vessel.h"    // your Vessel interface

int main() {
    // 1) Clean slate: remove any existing data file
    std::remove("vessels.dat");

    // 2) Create two vessels and save to file
    std::vector<Vessel> vessels;
    Vessel v1(1, "Alpha", 10.5f, 5.2f);
    Vessel v2(2, "Beta",  8.3f, 4.1f);
    vessels.push_back(v1);
    vessels.push_back(v2);
    Vessel::saveAll(vessels);

    // 3) Load them back into new objects
    Vessel u1(1, "", 0, 0);
    Vessel u2(2, "", 0, 0);
    std::vector<Vessel> newVessels;
    Vessel::loadAll(newVessels);

    bool pass = true;
    if (newVessels.size() != 2) {
        std::cout << "Failed to load vessels: expected 2, got " << newVessels.size() << "\n";
        pass = false;
    } else {
        if (newVessels[0].vesselID != v1.vesselID || std::strcmp(newVessels[0].vesselName, v1.vesselName) != 0) {
            std::cout << "First vessel mismatch\n";
            pass = false;
        }
        if (newVessels[1].vesselID != v2.vesselID || std::strcmp(newVessels[1].vesselName, v2.vesselName) != 0) {
            std::cout << "Second vessel mismatch\n";
            pass = false;
        }
    }

    // 4) Test EOF by attempting to read 3 VesselRecords
    std::ifstream in("vessels.dat", std::ios::binary);
    VesselRecord record;
    in.read(reinterpret_cast<char*>(&record), sizeof(record)); // first
    in.read(reinterpret_cast<char*>(&record), sizeof(record)); // second
    in.read(reinterpret_cast<char*>(&record), sizeof(record)); // should fail
    pass &= (in.gcount() < static_cast<std::streamsize>(sizeof(record)));

    std::cout << (pass ? "Pass\n" : "Fail\n");
    return pass ? 0 : 1;
}
