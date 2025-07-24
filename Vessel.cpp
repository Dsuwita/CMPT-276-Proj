/*
 * File:        Vessel.cpp
 * Description: Implements the Vessel module. A Vessel contains identifying information
 *              and a list of Sailings. Responsible for managing its own sailings and
 *              persisting vessel data to file.
 * Author:      Team 21
 *
 * Version History:
 */

#include "Vessel.h"        
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <unistd.h>         // for ftruncate()
#include <fcntl.h>          // for open()

static constexpr int NAME_SIZE = 100;
struct VesselRecord {
    int   vesselID;
    char  vesselName[NAME_SIZE];
    float HCLL;
    float LCLL;
};

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
  : vesselID(0), vesselName(), HCLL(0.0f), LCLL(0.0f) {}

Vessel::Vessel(int id, const std::string& name,
               float hcll, float lcll)
  : vesselID(id), vesselName(name),
    HCLL(hcll), LCLL(lcll) {}


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

void Vessel::load() {
    ensureVesselFileOpen();
    VesselRecord rec;
    vesselFile.seekg(0, std::ios::beg);
    while (vesselFile.read(reinterpret_cast<char*>(&rec), sizeof(rec))) {
        if (rec.vesselID == vesselID) {
            vesselName = std::string(rec.vesselName);
            HCLL = rec.HCLL;
            LCLL = rec.LCLL;
            return;
        }
    }
}

void Vessel::save() const {
    ensureVesselFileOpen();
    VesselRecord rec{};
    rec.vesselID = vesselID;
    std::strncpy(rec.vesselName, vesselName.c_str(), NAME_SIZE);
    rec.HCLL = HCLL;
    rec.LCLL = LCLL;

    vesselFile.seekg(0, std::ios::beg);
    std::streampos pos;
    bool found = false;
    while (vesselFile.read(reinterpret_cast<char*>(&rec), sizeof(rec))) {
        if (rec.vesselID == vesselID) {
            found = true;
            pos = vesselFile.tellg() - std::streamoff(sizeof(rec));
            break;
        }
    }

    if (found) {
        vesselFile.seekp(pos);
    } else {
        vesselFile.clear();
        vesselFile.seekp(0, std::ios::end);
    }
    vesselFile.write(reinterpret_cast<const char*>(&rec), sizeof(rec));
}

void Vessel::closeFile() {
    if (vesselFileOpen) {
        vesselFile.close();
        vesselFileOpen = false;
    }
}
