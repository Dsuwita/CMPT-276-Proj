/*
 * File:        Vehicle.cpp
 * Description: Implements the Vehicle module. A Vehicle contains license plate,
 *              dimensions, and type. Used as part of a Reservation and not stored independently.
 * Author:      Team 21
 *
 * Version History:
 */

#include "Vehicle.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <unistd.h>   // for ftruncate()
#include <fcntl.h>    // for open()

static constexpr int PLATE_SIZE = 20;
struct VehicleRecord {
    char  licensePlate[PLATE_SIZE];
    float length;
    float height;
    float width;
    bool  isSpecial;
    int   type;  // 枚举存为 int
};

static std::fstream vehicleFile;
static bool      vehicleFileOpen = false;
static std::vector<Vehicle> allVehicles;

static void ensureVehicleFileOpen() {
    if (!vehicleFileOpen) {
        vehicleFile.open("vehicles.dat",
                  std::ios::in | std::ios::out | std::ios::binary);
        if (!vehicleFile) {
            vehicleFile.clear();
            vehicleFile.open("vehicles.dat",
                      std::ios::out | std::ios::binary);
            vehicleFile.close();
            vehicleFile.open("vehicles.dat",
                      std::ios::in | std::ios::out | std::ios::binary);
        }
        vehicleFileOpen = true;
    }
}

Vehicle::Vehicle()
  : licensePlate(), length(0), height(0), width(0),
    isSpecial(false), type(VehicleType::REGULAR) {}

Vehicle::~Vehicle() {}

void Vehicle::start() {
    std::cout << "Vehicle " << licensePlate << " started.\n";
}

void Vehicle::stop() {
    std::cout << "Vehicle " << licensePlate << " stopped.\n";
}

void Vehicle::honk() const {
    std::cout << licensePlate << " says: Beep!\n";
}

bool Vehicle::isDuplicateVehicle(const std::string& plate) const {
    loadVehicles();  
    return std::any_of(
      allVehicles.begin(), allVehicles.end(),
      [&](const Vehicle& v){ return v.licensePlate == plate; }
    );
}

void Vehicle::saveVehicles() const {
    ensureVehicleFileOpen();
    VehicleRecord rec{};
    std::strncpy(rec.licensePlate, licensePlate.c_str(), PLATE_SIZE);
    rec.length    = length;
    rec.height    = height;
    rec.width     = width;
    rec.isSpecial = isSpecial;
    rec.type      = static_cast<int>(type);

    vehicleFile.clear();
    vehicleFile.seekp(0, std::ios::end);
    vehicleFile.write(reinterpret_cast<const char*>(&rec), sizeof(rec));
}

void Vehicle::loadVehicles() {
    ensureVehicleFileOpen();
    allVehicles.clear();
    vehicleFile.seekg(0, std::ios::beg);
    VehicleRecord rec;
    while (vehicleFile.read(reinterpret_cast<char*>(&rec), sizeof(rec))) {
        Vehicle v;
        v.licensePlate = std::string(rec.licensePlate);
        v.length       = rec.length;
        v.height       = rec.height;
        v.width        = rec.width;
        v.isSpecial    = rec.isSpecial;
        v.type         = static_cast<VehicleType>(rec.type);
        allVehicles.push_back(v);
    }
}

static void closeVehicleFile() {
    if (vehicleFileOpen) {
        vehicleFile.close();
        vehicleFileOpen = false;
    }
}
