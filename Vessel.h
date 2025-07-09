#ifndef VESSEL_H
#define VESSEL_H

#include "Sailing.h"
#include <vector>
#include <string>

class Vessel {
public:
    int vesselID; // Unique identifier for the vessel
    std::string vesselName; // Name of the vessel
    float HCLL; // High ceiling lane length
    float LCLL; // Low ceiling lane length

    // Methods for vessel management
    Vessel(); // Default constructor

    ~Vessel(); // Destructor

    void addSailing(const Sailing& sailing); // Method to add a sailing

    void removeSailing(const Sailing& sailing); // Method to remove a sailing

    void viewVesselDetails() const; // Method to view vessel details
};

#endif // VESSEL_H