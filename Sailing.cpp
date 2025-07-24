/*
 * File:        Sailing.cpp
 * Description: Implements the Sailing module. A Sailing belongs to a Vessel and
 *              contains a list of Reservations. Responsible for adding, canceling,
 *              and checking in reservations.
 * Author:      Team 21
 *
 * Version History:
 */


#include "Sailing.h"
#include <iostream>
#include <fstream>

 // Default constructor
Sailing::Sailing()
    : sailingID(0), reservations(), departureDate(), HRL(0.0f), LRL(0.0f) {
}

// Parameterized constructor
Sailing::Sailing(int id, int vid, const date& depDate, float hrl, float lrl)
    : sailingID(id), reservations(), departureDate(depDate), HRL(hrl), LRL(lrl) {
}

// Destructor
Sailing::~Sailing() {}

// View sailing details
void Sailing::viewSailingDetails() const {
    std::cout << "Sailing ID: " << sailingID << "\n";
    std::cout << "Departure Date: " << departureDate.day << "/" << departureDate.month << "/" << departureDate.year
        << " " << departureDate.hour << ":00\n";
    std::cout << "High Ceiling Remaining Lane: " << HRL << "\n";
    std::cout << "Low Ceiling Remaining Lane: " << LRL << "\n";
    std::cout << "Number of Reservations: " << reservations.size() << "\n";
}

// Check availability of the sailing
void Sailing::checkAvailability() const {
    std::cout << "HRL: " << HRL << ", LRL: " << LRL << "\n";
    if (HRL > 0 || LRL > 0) {
        std::cout << "Space available for reservation.\n";
    }
    else {
        std::cout << "No space available.\n";
    }
}

//Make a reservation
void Sailing::makeReservation(const Reservation& res) {
    // Determine lane usage based on vehicle type
    if (res.vehicle.type == Vehicle::VehicleType::OVERSIZE_HIGH) {
        if (HRL < res.vehicle.length) {
            std::cout << "Not enough HRL space for this vehicle.\n";
            return;
        }
        HRL -= res.vehicle.length;
    }
    else {
        if (LRL < res.vehicle.length) {
            std::cout << "Not enough LRL space for this vehicle.\n";
            return;
        }
        LRL -= res.vehicle.length;
    }

    reservations.push_back(res);
    std::cout << "Reservation added successfully.\n";
}

// Cancel the last reservation (restores space)
void Sailing::cancelReservation() {
    if (reservations.empty()) {
        std::cout << "No reservations to cancel.\n";
        return;
    }

    Reservation last = reservations.back();
    reservations.pop_back();

    if (last.vehicle.type == Vehicle::VehicleType::OVERSIZE_HIGH) {
        HRL += last.vehicle.length;
    }
    else {
        LRL += last.vehicle.length;
    }

    std::cout << "Last reservation cancelled.\n";
}


// Get a reservation by ID
void Sailing::getReservation(int reservationID) const {
    for (const auto& res : reservations) {
        if (res.reservationID == reservationID) {
            res.viewReservation();
            return;
        }
    }
    std::cout << "Reservation ID " << reservationID << " not found.\n";
}

// Load sailings from file (placeholder)
void Sailing::load() {
    std::ifstream infile("sailings.txt");
    if (infile.is_open()) {
        infile >> sailingID;
		infile >> departureDate.day >> departureDate.month >> departureDate.year >> departureDate.hour;
        infile >> HRL >> LRL;
        infile.close();
		std::cout << "Sailings loaded successfully.\n";
    }
    else {
        std::cout << "No sailing data found.\n";
    }
}



// Save sailings to file
void Sailing::save() const {
    std::ofstream outfile("sailings.txt");
    if (outfile.is_open()) {
        // Implement file writing logic
        outfile << sailingID << "\n";
		outfile << departureDate.day << " " << departureDate.month << " " << departureDate.year << " " << departureDate.hour << "\n";
        outfile << HRL << "\n" << LRL << "\n";
        outfile.close();
		std::cout << "Sailings saved successfully.\n";
    }
}
