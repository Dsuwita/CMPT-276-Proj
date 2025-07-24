/*
 * File:        Reservation.cpp
 * Description: Implements the Reservation module. A Reservation stores user contact info,
 *              a linked Vehicle object, and reservation metadata. Managed by the Sailing class.
 * Author:      Team 21
 *
 * Version History:
 */

#include "Reservation.h"
#include <iostream>
#include <fstream>
#include <cstring>

// Default constructor
Reservation::Reservation() {
    std::memset(reservationID, 0, sizeof(reservationID));
    std::memset(phoneNumber, 0, sizeof(phoneNumber));
    isBoarded = false;
}

// Parameterized constructor
Reservation::Reservation(const char* id, const Vehicle& veh, const char* phone)
    : vehicle(veh), isBoarded(false) {
    std::strncpy(reservationID, id, sizeof(reservationID) - 1);
    reservationID[sizeof(reservationID) - 1] = '\0';
    std::strncpy(phoneNumber, phone, sizeof(phoneNumber) - 1);
    phoneNumber[sizeof(phoneNumber) - 1] = '\0';
}

// Destructor
Reservation::~Reservation() {}

// View reservation details
void Reservation::viewReservation() const {
    std::cout << "Reservation ID: " << reservationID << "\n";
    std::cout << "Phone Number: " << phoneNumber << "\n";
    std::cout << "Boarded: " << (isBoarded ? "Yes" : "No") << "\n";
    vehicle.viewVehicle(); 
}

// Check in reservation
void Reservation::checkInReservation() {
    if (!isBoarded) {
        isBoarded = true;
        std::cout << "Checked in successfully.\n";
    } else {
        std::cout << "Already checked in.\n";
    }
}

// Check if already checked in
bool Reservation::isAlreadyCheckedIn() const {
    return isBoarded;
}

// Binary file write
void Reservation::writeToFile(std::ofstream& out) const {
    out.write(reinterpret_cast<const char*>(this), sizeof(Reservation));
}

// Binary file read
void Reservation::readFromFile(std::ifstream& in) {
    in.read(reinterpret_cast<char*>(this), sizeof(Reservation));
}

// Match reservation ID (utility method)
bool Reservation::matchesID(const char* id) const {
    return std::strncmp(reservationID, id, sizeof(reservationID)) == 0;
}
