#ifndef SAILING_H
#define SAILING_H

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
    int vesselID; // ID of the vessel associated with the sailing
    date departureDate; // Departure date of the sailing
    float HRL; // High ceiling remaining lane space
    float LRL; // Low ceiling remaining lane space

    // Methods for sailing management
    Sailing(); // Default constructor
    ~Sailing(); // Destructor
    void viewSailingDetails() const; // Method to view sailing details
};

#endif // SAILING_H