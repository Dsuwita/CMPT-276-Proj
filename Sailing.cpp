/*
 * File:        Reservation.cpp
 * Description: Implements the Reservation module. A Reservation stores user contact info,
 *              a linked Vehicle object, and reservation metadata. Managed by the Sailing class.
 * Author:      Team 21
 *
 * Version History:
 */

#include "Sailing.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

#include "Vessel.h"

// Default constructor
Sailing::Sailing()
    : sailingID(), departureDate(), HRL(0.0f), LRL(0.0f), reservationCount(0) {
}

// Parameterized constructor
Sailing::Sailing(char* id, const date& depDate, float hrl, float lrl)
    : departureDate(depDate), HRL(hrl), LRL(lrl), reservationCount(0) {
    strncpy(sailingID, id, sizeof(sailingID) - 1);
    sailingID[sizeof(sailingID) - 1] = '\0';
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

bool Sailing::operator==(const Sailing& other) const {
    return std::strncmp(this->sailingID, other.sailingID, 9) == 0;  // or 10 if null-terminated
}

char* Sailing::generateReservationID(){
    static char result[13]; // 9-char sailingID + 3-char count = 12 + '\0'
    std::snprintf(result, sizeof(result), "%s%03d", sailingID, reservationCount + 1);
    result[12] = '\0'; 
    reservationCount++; 
    return result;
}

struct SailingRecord {
    char sailingID[SAILING_ID_LEN];
    int vesselID;
    int day, month, year, hour;
    float HRL;
    float LRL;
};

void Sailing::saveAll(const std::vector<Vessel>& vessels) {
    std::ofstream out("sailings.dat", std::ios::binary | std::ios::trunc);
    if (!out) return;

    for (const auto& v : vessels) {
        for (const auto& s : v.sailings) {
            SailingRecord rec{};
            std::strncpy(rec.sailingID, s.sailingID, SAILING_ID_LEN);
            rec.vesselID = v.vesselID;
            rec.day = s.departureDate.day;
            rec.month = s.departureDate.month;
            rec.year = s.departureDate.year;
            rec.hour = s.departureDate.hour;
            rec.HRL = s.HRL;
            rec.LRL = s.LRL;
            out.write(reinterpret_cast<const char*>(&rec), sizeof(rec));
        }
    }
}

void Sailing::loadAll(std::vector<Vessel>& vessels) {
    std::ifstream in("sailings.dat", std::ios::binary);
    if (!in) return;

    SailingRecord rec;
    while (in.read(reinterpret_cast<char*>(&rec), sizeof(rec))) {
        Sailing s;
        std::strncpy(s.sailingID, rec.sailingID, SAILING_ID_LEN);
        s.sailingID[SAILING_ID_LEN - 1] = '\0';
        s.departureDate = date(rec.day, rec.month, rec.year, rec.hour);
        s.HRL = rec.HRL;
        s.LRL = rec.LRL;
        s.vesselID = rec.vesselID;

        // Find vessel by ID and add sailing
        auto it = std::find_if(vessels.begin(), vessels.end(), [rec](const Vessel& v) {
            return v.vesselID == rec.vesselID;
        });

        if (it != vessels.end()) {
            it->addSailing(s);
        }
    }
}
