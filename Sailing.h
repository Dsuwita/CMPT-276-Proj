#ifndef SAILING_H
#define SAILING_H

#include <vector>
#include "Reservation.h"
struct date {
    int day; // Day of the month
    int month; // Month of the year
    int year; // Year
    int hour; // Hour of the day (24-hour format)

    // Default constructor (empty date)
    date() : day(0), month(0), year(0), hour(0) {}

    // Parameterized constructor
    date(int d, int m, int y, int h) : day(d), month(m), year(y), hour(h) {}

    // destructor
    ~date() {}
};

class Sailing {
public:
    // Attributes for sailing details
    int sailingID; // Unique identifier for the sailing
    std::vector<Reservation> reservations; // List of reservations for the sailing
    date departureDate; // Departure date of the sailing
    float HRL; // High ceiling remaining lane space
    float LRL; // Low ceiling remaining lane space

    // Methods for sailing management
    Sailing(); // Default constructor
    Sailing(int id, int vid, const date& depDate, float hrl, float lrl); // Parameterized constructor
    ~Sailing(); // Destructor
    void viewSailingDetails() const; // Method to view sailing details
    void checkAvailability() const; // Method to check availability of the sailing
};

#endif // SAILING_H
