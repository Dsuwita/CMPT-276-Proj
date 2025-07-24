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

// Default constructor
Reservation::Reservation()
    : reservationID(0), vehicle(), phoneNumber(0), isBoarded(false) {}

// Destructor
Reservation::~Reservation() {}

// View reservation details
void Reservation::viewReservation() const {
    std::cout << "Reservation ID: " << reservationID << "\n";
    std::cout << "Phone Number: " << phoneNumber << "\n";
    std::cout << "Boarded: " << (isBoarded ? "Yes" : "No") << "\n";
    // You may want to print vehicle details here
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

// Check availability (placeholder)
bool Reservation::checkAvailability(int vehicleID, int sailingID) const {
    // Implement logic to check if vehicle is available for the sailing
    std::cout << "Checking availability for vehicle " << vehicleID << " on sailing " << sailingID << "\n";
    return true; // Placeholder
}

// Load reservations from file (placeholder)
void Reservation::load() {
    std::ifstream infile("reservations.txt");
    if (infile.is_open()) {
        // Implement file reading logic
        infile.close();
    }
}

// Save reservation to file (placeholder)
void Reservation::save() const {
    std::ofstream outfile("reservations.txt", std::ios::app);
    if (outfile.is_open()) {
        // Implement file writing logic
        outfile.close();
    }
}