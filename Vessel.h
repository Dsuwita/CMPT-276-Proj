//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// File: vessel.h
// Title: Vessel Class Interface
// Purpose: 
//   Declares the Vessel class and its associated functions, including
//   file-based save/load methods, sailing management, and vessel capacity info.
//   Supports binary file persistence using fixed-length records.
//
// Version History:
//   v1.0  (2025-07-24)  Initial creation and interface design for Vessel module.
//                       Includes save/load operations and sailing container.
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#ifndef VESSEL_H
#define VESSEL_H

#include "Sailing.h"
#include <vector>
#include <cstring>
#include <string>
#include <fstream>

static const int NAME_SIZE = 100;

struct VesselRecord {
    int vesselID;
    char vesselName[NAME_SIZE];
    float HCLL;  // High Ceiling Remaining Lane Length
    float LCLL;  // Low Ceiling Remaining Lane Length
};

class Vessel {
public:
    int vesselID;
    char vesselName[32]; 
    float HCLL;
    float LCLL;

    std::vector<Sailing> sailings; 

    Vessel();  
    Vessel(int id, const std::string& name, float hcll, float lcll);
    ~Vessel();

    void addSailing(const Sailing& sailing);
    void removeSailing(const Sailing& sailing);
    void viewVesselDetails() const;

    static void loadAll(std::vector<Vessel>& vessels);
    static void saveAll(const std::vector<Vessel>& vessels);

    static void closeFile(); 
};

#endif // VESSEL_H
