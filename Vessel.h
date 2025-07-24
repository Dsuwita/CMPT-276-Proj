#ifndef VESSEL_H
#define VESSEL_H

#include "Sailing.h"
#include <vector>
#include <cstring>

class Vessel {
public:
    int vesselID;                 // Unique identifier
    char vesselName[32];          // Fixed-length name
    float HCLL;                   // High ceiling lane length
    float LCLL;                   // Low ceiling lane length

    std::vector<Sailing> sailings; // This is kept in memory; NOT written directly to binary

    // Constructors
    Vessel();  // Default
    Vessel(int id, const std::string& name, float hcll, float lcll);

    // Destructor
    ~Vessel();

    // Methods
    void addSailing(const Sailing& sailing);
    void removeSailing(const Sailing& sailing);
    void viewVesselDetails() const;

    void load(std::ifstream& file);      // Load from binary file
    void save(std::ofstream& file) const; // Save to binary file
};

#endif // VESSEL_H
