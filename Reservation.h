//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// File: reservation.h
// Title: Reservation Class Interface
// Purpose:
//   Declares the Reservation class and its key operations, including
//   reservation creation, lookup, and file persistence.
//   Integrates with Vehicle and Sailing modules to manage booking logic.
//
// Version History:
//   v1.0  (2025-07-8)  Initial creation of Reservation class interface.
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#ifndef RESERVATION_H
#define RESERVATION_H

#include "Vehicle.h"
#include <fstream>
#include <cstring>
#include <vector>

class Vessel;

static const int RES_ID_LEN = 13;
static const int PLATE_SIZE = 10;
static const int PHONE_SIZE = 15; 

class Reservation {
public:
    char reservationID[RES_ID_LEN];   
    Vehicle vehicle;            
    char phoneNumber[PHONE_SIZE];
    bool isBoarded;             

    // Default constructor
    Reservation();

    // Parameterized constructor
    Reservation(const char* id, const Vehicle& veh, const char* phone);

    // Destructor
    ~Reservation();

    // View details
    void viewReservation() const;
    void checkInReservation();
    bool isAlreadyCheckedIn() const;

    // Utility
    bool matchesID(const char* id) const;
    static void saveAll(const std::vector<Vessel>& vessels);
    static void loadAll(std::vector<Vessel>& vessels);


};

#endif // RESERVATION_H
