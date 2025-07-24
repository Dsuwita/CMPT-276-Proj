#include "Sailing.h"
#include <iostream>
#include <fstream>
#include <cstring>

// Default constructor
Sailing::Sailing()
    : sailingID(0), departureDate(), HRL(0.0f), LRL(0.0f), reservationCount(0) {
}

// Parameterized constructor
Sailing::Sailing(int id, const date& depDate, float hrl, float lrl)
    : sailingID(id), departureDate(depDate), HRL(hrl), LRL(lrl), reservationCount(0) {
}

// Destructor
Sailing::~Sailing() {}

void Sailing::viewSailingDetails() const {
    std::cout << "Sailing ID: " << sailingID << "\n";
    std::cout << "Departure Date: " << departureDate.day << "/"
              << departureDate.month << "/" << departureDate.year << " "
              << departureDate.hour << ":00\n";
    std::cout << "High Ceiling Remaining Lane: " << HRL << "\n";
    std::cout << "Low Ceiling Remaining Lane: " << LRL << "\n";
    std::cout << "Number of Reservations: " << reservationCount << "\n";
}

void Sailing::checkAvailability() const {
    std::cout << "HRL: " << HRL << ", LRL: " << LRL << "\n";
    if (HRL > 0 || LRL > 0)
        std::cout << "Space available for reservation.\n";
    else
        std::cout << "No space available.\n";
}

bool Sailing::makeReservation(const Reservation& res) {
    if (reservationCount >= MAX_RESERVATIONS) {
        std::cout << "Reservation limit reached.\n";
        return false;
    }

    if (res.vehicle.type == Vehicle::VehicleType::OVERSIZE_HIGH) {
        if (HRL < res.vehicle.length) {
            std::cout << "Not enough HRL space.\n";
            return false;
        }
        HRL -= res.vehicle.length;
    } else {
        if (LRL < res.vehicle.length) {
            std::cout << "Not enough LRL space.\n";
            return false;
        }
        LRL -= res.vehicle.length;
    }

    reservations[reservationCount++] = res;
    std::cout << "Reservation added.\n";
    return true;
}

bool Sailing::cancelReservation(const char* id) {
    for (int i = 0; i < reservationCount; ++i) {
        if (reservations[i].matchesID(id)) {
            // Restore space
            if (reservations[i].vehicle.type == Vehicle::VehicleType::OVERSIZE_HIGH)
                HRL += reservations[i].vehicle.length;
            else
                LRL += reservations[i].vehicle.length;

            // Overwrite with last and shorten
            reservations[i] = reservations[reservationCount - 1];
            reservationCount--;
            std::cout << "Reservation cancelled.\n";
            return true;
        }
    }
    std::cout << "Reservation ID not found.\n";
    return false;
}

const Reservation* Sailing::getReservation(const char* id) const {
    for (int i = 0; i < reservationCount; ++i) {
        if (reservations[i].matchesID(id)) {
            return &reservations[i];
        }
    }
    return nullptr;
}

// Write entire struct to binary file
void Sailing::writeToFile(std::ofstream& out) const {
    out.write(reinterpret_cast<const char*>(this), sizeof(Sailing));
}

// Read entire struct from binary file
void Sailing::readFromFile(std::ifstream& in) {
    in.read(reinterpret_cast<char*>(this), sizeof(Sailing));
}
