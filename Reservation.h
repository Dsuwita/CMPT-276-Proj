#ifndef RESERVATION_H
#define RESERVATION_H

#include "Vehicle.h"

class Reservation {
public:
    // Attributes for reservation details
    int reservationID; // Unique identifier for the reservation
    Vehicle vehicle; // Vehicle associated with the reservation
    int phoneNumber; // Phone number of the person making the reservation
    bool isBoarded=false; // Flag to indicate if the vehicle is boarded

    // Methods for reservation management
    Reservation(); // Default constructor

    ~Reservation(); // Destructor

    void viewReservation() const; // Method to view reservation details

    void checkInReservation(); // Method to check in a reservation

    bool isAlreadyCheckedIn() const; // Method to check if vehicle has already boarded

    bool checkAvailability(int vehicleID, int sailingID) const; // Method to check if vehicle is available for a sailing

    void load(); // Method to load reservations from a file 

    void save() const; // Method to save reservations to a file
};

#endif // RESERVATION_H
