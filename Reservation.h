#ifndef RESERVATION_H
#define RESERVATION_H

#include "Vehicle.h"
#include <fstream>
#include <cstring>

class Reservation {
public:
    char reservationID[13];     // e.g. "R00000000001" — 12 chars + null
    Vehicle vehicle;            // embedded, must also be binary-safe
    char phoneNumber[15];       // store as char array to preserve formatting (e.g. "6041234567")
    bool isBoarded;             // boarding status

    // Default constructor
    Reservation();

    // Parameterized constructor
    Reservation(const char* id, const Vehicle& veh, const char* phone);

    // View details
    void viewReservation() const;
    void checkInReservation();
    bool isAlreadyCheckedIn() const;

    // Binary I/O
    void writeToFile(std::ofstream& out) const;
    void readFromFile(std::ifstream& in);

    // Utility
    bool matchesID(const char* id) const;

};

#endif // RESERVATION_H
