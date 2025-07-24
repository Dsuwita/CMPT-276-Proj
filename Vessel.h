#ifndef VESSEL_H
#define VESSEL_H

#include "Sailing.h"
#include <vector>
#include <cstring>
#include <string>
#include <fstream>

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
