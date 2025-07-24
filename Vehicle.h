#ifndef VEHICLE_H
#define VEHICLE_H

#include <cstring>
#include <fstream>

class Vehicle {
public:
    // Constants
    static const int LICENSE_PLATE_LEN = 10;

    // Fixed-length attributes for binary file compatibility
    char licensePlate[LICENSE_PLATE_LEN]; // Fixed-length license plate
    float length;    // in meters
    float height;    // in meters
    bool isSpecial;  // special vehicle flag

    enum class VehicleType {
        REGULAR,
        OVERSIZE_LOW,
        OVERSIZE_HIGH,
    } type;  // Type of the vehicle

    // Methods
    Vehicle();              // Default constructor
    ~Vehicle();             // Destructor
};

#endif // VEHICLE_H
