#ifndef SAILING_H
#define SAILING_H

#include "Reservation.h"

const int MAX_RESERVATIONS = 100;

struct date {
    int day;
    int month;
    int year;
    int hour;

    date() : day(0), month(0), year(0), hour(0) {}
    date(int d, int m, int y, int h) : day(d), month(m), year(y), hour(h) {}
};

class Sailing {
public:
    int sailingID;
    date departureDate;
    int vesselID;  // ID of the vessel this sailing belongs to
    float HRL;  // High-ceiling remaining lane length
    float LRL;  // Low-ceiling remaining lane length

    Reservation reservations[MAX_RESERVATIONS];
    int reservationCount;  // how many reservations are stored

    // Constructors
    Sailing();
    Sailing(int id, const date& depDate, float hrl, float lrl);

    // Methods
    void viewSailingDetails() const;
    void checkAvailability() const;
    bool makeReservation(const Reservation& res);
    bool cancelReservation(const char* reservationID);
    char* generateReservationID() const;    
    const Reservation* getReservation(const char* reservationID) const;

    void writeToFile(std::ofstream& out) const;
    void readFromFile(std::ifstream& in);
};

#endif // SAILING_H
