//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// File: vehicle.h
// Title: Vehicle Class Interface
// Purpose: 
//   Declares the Vehicle class and its supporting functions for vehicle
//   creation, classification, dimension tracking, and binary file I/O.
//   Also includes logic to detect duplicate vehicle entries.
//
// Version History:
//   v1.0  (2025-07-8)  Initial interface for Vehicle data and file operations.
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

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
