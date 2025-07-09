#ifndef RESERVATION_H
#define RESERVATION_H

class Reservation {
public:
    // Attributes for reservation details
    int reservationID; // Unique identifier for the reservation
    int sailingID; // ID of the sailing associated with the reservation
    int vehicleID; // ID of the vehicle associated with the reservation
    int phoneNumber; // Phone number of the person making the reservation
    bool isBoarded; // Flag to indicate if the vehicle is boarded

    // Methods for reservation management
    Reservation(); // Default constructor

    ~Reservation(); // Destructor

    void makeReservation(); // Method to make a reservation

    void cancelReservation(); // Method to cancel a reservation

    void viewReservation() const; // Method to view reservation details
};

#endif // RESERVATION_H