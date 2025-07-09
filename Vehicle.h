#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle {
public:
    // Attributes for vehicle details
    std::string licensePlate; // Vehicle's license plate
    float length; // Length of the vehicle in meters
    float height; // Height of the vehicle in meters
    float width; // Width of the vehicle in meters
    bool isSpecial; // Flag to indicate if the vehicle is special 
    enum class VehicleType { 
        REGULAR,
        OVERSIZE_LOW,
        OVERSIZE_HIGH,
    } type;  // Type of the vehicle

    // Methods for vehicle management
    Vehicle(); // Default constructor

    ~Vehicle(); // Destructor

    void start(); // Method to start the vehicle

    void stop(); // Method to stop the vehicle

    void honk() const; // Method to honk the horn
};

#endif // VEHICLE_H