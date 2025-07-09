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
    std::vector<Sailing> sailings; // List of sailings associated with the vessel

    // Methods for vessel management
    Vessel(); // Default constructor

    Vessel(int id, const std::string& name, float hcll, float lcll); // Parameterized constructor

    ~Vessel(); // Destructor

    void addSailing(const Sailing& sailing); // Method to add a sailing

    void removeSailing(const Sailing& sailing); // Method to remove a sailing

    void viewVesselDetails() const; // Method to view vessel details

    void load(); // Method to load vessels from a file

    void save() const; // Method to save vessels to a file
};

#endif // VESSEL_H