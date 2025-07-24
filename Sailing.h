//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// File: sailing.h
// Title: Sailing Class Interface
// Purpose:
//   Declares the Sailing class and related data structures, including
//   sail date/time, destination, and capacity tracking.
//   Intended for use with vessel assignments and reservation linkage.
//
// Version History:
//   v1.0  (2025-07-8)  Initial interface definition for Sailing module.
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#ifndef SAILING_H
#define SAILING_H

#include "Reservation.h"
#include <vector>

class Vessel;

const int MAX_RESERVATIONS = 100;
const int SAILING_ID_LEN = 10; // 9 chars + null terminator

struct date {
    int day;
    int month;
    int year;
    int hour;

    date() : day(0), month(0), year(0), hour(0) {}
    date(int d, int m, int y, int h) : day(d), month(m), year(y), hour(h) {}
};

struct SailingRecord {
    char sailingID[SAILING_ID_LEN];
    int vesselID;
    int day, month, year, hour;
    float HRL;
    float LRL;
};

class Sailing {
public:
    char sailingID[SAILING_ID_LEN];
    date departureDate;
    int vesselID;  // ID of the vessel this sailing belongs to
    float HRL;  // High-ceiling remaining lane length
    float LRL;  // Low-ceiling remaining lane length

    Reservation reservations[MAX_RESERVATIONS];
    int reservationCount = 0;  // how many reservations are stored

    // Constructors
    Sailing();
    Sailing(char* sailingID, const date& depDate, float hrl, float lrl);
    ~Sailing();

    // Methods
    void viewSailingDetails() const;
    void checkAvailability() const;
    bool makeReservation(const Reservation& res);
    bool cancelReservation(const char* reservationID);
    char* generateReservationID(); //  sailingID "-" reservationCount
    const Reservation* getReservation(const char* reservationID) const;
    bool operator==(const Sailing& other) const;

    static void saveAll(const std::vector<Vessel>& vessels);
    static void loadAll(std::vector<Vessel>& vessels);
};

#endif // SAILING_H
