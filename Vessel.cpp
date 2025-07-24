/*
 * File:        Vessel.cpp
 * Description: Implements the Vessel module. A Vessel contains identifying information
 *              and a list of Sailings. Responsible for managing its own sailings and
 *              persisting vessel data to file.
 * Author:      Team 21
 *
 * Version History:'
 * *  v1.0 (2025-07-24) — initial implementation
 */

#include "Vessel.h"        
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <unistd.h>         // for ftruncate()
#include <fcntl.h>          // for open()

static std::fstream vesselFile;
static bool      vesselFileOpen = false;

static void ensureVesselFileOpen() {
    if (!vesselFileOpen) {
        vesselFile.open("vessels.dat",
                  std::ios::in | std::ios::out | std::ios::binary);
        if (!vesselFile) {
            vesselFile.clear();
            vesselFile.open("vessels.dat",
                      std::ios::out | std::ios::binary);
            vesselFile.close();
            vesselFile.open("vessels.dat",
                      std::ios::in | std::ios::out | std::ios::binary);
        }
        vesselFileOpen = true;
    }
}


Vessel::Vessel()
  : vesselID(0), vesselName(), HCLL(0.0f), LCLL(0.0f) {
    std::vector<Sailing> sailings; 
  }

Vessel::Vessel(int id, const std::string& name,
               float hcll, float lcll)
  : vesselID(id), HCLL(hcll), LCLL(lcll) {
    std::strncpy(vesselName, name.c_str(), sizeof(vesselName));
    vesselName[sizeof(vesselName) - 1] = '\0';
    std::vector<Sailing> sailings; 
}



Vessel::~Vessel() {

}


void Vessel::addSailing(const Sailing& s) {
    sailings.push_back(s);
}

void Vessel::removeSailing(const Sailing& s) {
    sailings.erase(
      std::remove(sailings.begin(), sailings.end(), s),
      sailings.end()
    );
}

void Vessel::viewVesselDetails() const {
    std::cout << "Vessel ID: "   << vesselID
              << ", Name: "      << vesselName
              << ", HCLL: "      << HCLL
              << ", LCLL: "      << LCLL
              << "\nSailings:\n";
    for (const auto& s : sailings) {
        s.viewSailingDetails(); 
    }
}

void Vessel::loadAll(std::vector<Vessel>& vessels) {
    ensureVesselFileOpen();
    vessels.clear();
    VesselRecord rec;
    vesselFile.seekg(0, std::ios::beg);

    while (vesselFile.read(reinterpret_cast<char*>(&rec), sizeof(rec))) {
        Vessel v;
        v.vesselID = rec.vesselID;
        std::strncpy(v.vesselName, rec.vesselName, sizeof(v.vesselName));
        v.vesselName[sizeof(v.vesselName) - 1] = '\0';
        v.HCLL = rec.HCLL;
        v.LCLL = rec.LCLL;
        vessels.push_back(v);
    }
}

void Vessel::saveAll(const std::vector<Vessel>& vessels) {
    ensureVesselFileOpen();
    vesselFile.close();
    vesselFile.open("vessels.dat", std::ios::out | std::ios::binary | std::ios::trunc); // Clear file
    for (const auto& v : vessels) {
        VesselRecord rec;
        rec.vesselID = v.vesselID;
        std::strncpy(rec.vesselName, v.vesselName, NAME_SIZE);
        rec.HCLL = v.HCLL;
        rec.LCLL = v.LCLL;
        vesselFile.write(reinterpret_cast<const char*>(&rec), sizeof(rec));
    }
}


void Vessel::closeFile() {
    if (vesselFileOpen) {
        vesselFile.close();
        vesselFileOpen = false;
    }
}
