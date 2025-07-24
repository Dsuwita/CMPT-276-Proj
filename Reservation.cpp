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
#include <vector>

#include "Vessel.h"

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

// Match reservation ID (utility method)
bool Reservation::matchesID(const char* id) const {
    return std::strncmp(reservationID, id, sizeof(reservationID)) == 0;
}



struct ReservationRecord {
    char reservationID[RES_ID_LEN];
    char phoneNumber[PHONE_SIZE];
    char sailingID[SAILING_ID_LEN];
    char licensePlate[PLATE_SIZE];
    float length;
    float height;
    bool isSpecial;
    int type;
    bool isBoarded;
};

void Reservation::saveAll(const std::vector<Vessel>& vessels) {
    std::ofstream out("reservations.dat", std::ios::binary | std::ios::trunc);
    if (!out) return;

    for (const auto& vessel : vessels) {
        for (const auto& sailing : vessel.sailings) {
            for (const auto& r : sailing.reservations) {
                ReservationRecord rec{};
                std::strncpy(rec.reservationID, r.reservationID, RES_ID_LEN);
                std::strncpy(rec.sailingID, sailing.sailingID, SAILING_ID_LEN);

                std::strncpy(rec.licensePlate, r.vehicle.licensePlate, PLATE_SIZE);
                rec.length = r.vehicle.length;
                rec.height = r.vehicle.height;
                rec.isSpecial = r.vehicle.isSpecial;
                rec.type = static_cast<int>(r.vehicle.type);

                std::strncpy(rec.phoneNumber, r.phoneNumber, PHONE_SIZE);
                rec.isBoarded = r.isBoarded;

                out.write(reinterpret_cast<const char*>(&rec), sizeof(rec));
            }
        }
    }
}

void Reservation::loadAll(std::vector<Vessel>& vessels) {
    std::ifstream in("reservations.dat", std::ios::binary);
    if (!in) return;

    ReservationRecord rec;
    while (in.read(reinterpret_cast<char*>(&rec), sizeof(rec))) {
        Reservation res;
        std::strncpy(res.reservationID, rec.reservationID, RES_ID_LEN);
        std::strncpy(res.phoneNumber, rec.phoneNumber, PHONE_SIZE);
        res.isBoarded = rec.isBoarded;

        Vehicle veh;
        std::strncpy(veh.licensePlate, rec.licensePlate, PLATE_SIZE);
        veh.length = rec.length;
        veh.height = rec.height;
        veh.isSpecial = rec.isSpecial;
        veh.type = static_cast<Vehicle::VehicleType>(rec.type);

        res.vehicle = veh;

        for (auto& vessel : vessels) {
            for (auto& sailing : vessel.sailings) {
                if (std::strncmp(sailing.sailingID, rec.sailingID, SAILING_ID_LEN) == 0) {
                    sailing.reservations[sailing.reservationCount++] = res;
                    break;
                }
            }
        }
    }
}