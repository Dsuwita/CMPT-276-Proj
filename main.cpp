/*
 * File:        main.cpp
 * Description: Main entry point for the Vessel Management System. Provides a user interface
 *              for managing vessels, sailings, and reservations. Implements a menu-driven
 *              system for creating vessels, sailings, making reservations, and viewing reports.
 * Author:      Team 21
 *
 * Version History:
 *
 */

#include <iostream>
#include <algorithm>
#include <limits>

#include "Sailing.h"
#include "Reservation.h"
#include "Vessel.h"
#include "Vehicle.h"

//Global Variables
std::vector<Vessel> vessels; // List of vessels in the system

// Function prototypes (defined elsewhere)
void startup(){}

// Function to print the menu
void printMenu() {
    std::cout << "\033[2J\033[1;1H"; // Clear screen
    std::cout << "==================== Vessel Management System ====================\n\n";
    std::cout << "Welcome to the Vessel Management System\n";
    std::cout << "1. Create New Vessel\n";
    std::cout << "2. Create New Sailing\n";
    std::cout << "3. Make or Cancel Reservation\n";
    std::cout << "4. Vehicle Check-In\n";
    std::cout << "5. View Sailing Report\n";
    std::cout << "6. View Sailing Vacancy\n";
    std::cout << "7. Check In Vehicle\n";
    std::cout << "0. Exit\n\n\n";
    std::cout << "Please select an option: ";
}

void inputVehicle(Vehicle& vehicle) {
    std::cout << "Enter license plate (max 9 characters): ";
    std::cin >> vehicle.licensePlate;
    std::cout << "Enter vehicle length: ";
    std::cin >> vehicle.length;
    std::cout << "Enter vehicle height: ";
    std::cin >> vehicle.height;
    std::cout << "Enter vehicle width: ";
    std::cin >> vehicle.width;
    std::cout << "Is this a special vehicle? (1 for yes, 0 for no): ";
    std::cin >> vehicle.isSpecial;

    int type;
    std::cout << "Enter vehicle type (0 = REGULAR, 1 = OVERSIZE_LOW, 2 = OVERSIZE_HIGH): ";
    std::cin >> type;
    vehicle.type = static_cast<Vehicle::VehicleType>(type);
}


void createVessel(){
    int id;
    std::string name;
    float hcll, lcll;

    std::cout << "Enter Vessel ID: ";
    std::cin >> id;
    std::cout << "Enter Vessel Name: ";
    std::cin.ignore(); // Clear the newline character from the input buffer
    std::getline(std::cin, name);
    std::cout << "Enter High Ceiling Lane Length (HCLL): ";
    std::cin >> hcll;
    std::cout << "Enter Low Ceiling Lane Length (LCLL): ";
    std::cin >> lcll;

    Vessel newVessel(id, name, hcll, lcll);

    if (std::any_of(vessels.begin(), vessels.end(), [id](const Vessel& v) { return v.vesselID == id; })) {
        std::cout << "Vessel with ID " << id << " already exists.\n";
        std::cout << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get(); // Wait for user to press Enter
        return;
    }

    vessels.push_back(newVessel);
    std::cout << "Vessel created successfully!\n";

    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(); // Wait for user to press Enter
}

void createSailing(){
    int id, vid;
    date depDate;
    float hrl, lrl;

    std::cout << "Enter Sailing ID: ";
    std::cin >> id;
    std::cout << "Enter Vessel ID: ";
    std::cin >> vid;
    std::cout << "Enter Departure Date (day month year hour): ";
    std::cin >> depDate.day >> depDate.month >> depDate.year >> depDate.hour;
    std::cout << "Enter High Ceiling Remaining Lane (HRL): ";
    std::cin >> hrl;
    std::cout << "Enter Low Ceiling Remaining Lane (LRL): ";
    std::cin >> lrl;

    Sailing newSailing(id, vid, depDate, hrl, lrl);

    // Check if the sailing ID already exists
    if (std::any_of(vessels.begin(), vessels.end(), [id](const Vessel& v) {
        return std::any_of(v.sailings.begin(), v.sailings.end(), [id](const Sailing& s) {
            return s.sailingID == id;
        });
    })) {
        std::cout << "Sailing with ID " << id << " already exists.\n";
        std::cout << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get(); // Wait for user to press Enter
        return;
    }
    
    // Find the vessel and add the sailing
    auto it = std::find_if(vessels.begin(), vessels.end(), [vid](const Vessel& v) { return v.vesselID == vid; });
    if (it != vessels.end()) {
        it->addSailing(newSailing);
        std::cout << "Sailing created successfully!\n";
    } else {
        std::cout << "Vessel with ID " << vid << " not found.\n";
    }

    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(); // Wait for user to press Enter
}

void makeReservation() {
    char reservationID[13];
    int phoneNumber, sailingID;
    Vehicle vehicle;

    std::cout << "Enter Reservation ID (max 12 characters): ";
    std::cin >> reservationID;
    reservationID[12] = '\0'; // Ensure null-termination

    std::cout << "Enter Phone Number: ";
    std::cin >> phoneNumber;

    std::cout << "Enter Sailing ID: ";
    std::cin >> sailingID;

    // Use vehicle input method
    std::cout << "Enter Vehicle Details:\n";
    vehicle.input(); // Assumes input() handles all required attributes

    // Set reservation fields
    Reservation newReservation;
    std::strncpy(newReservation.reservationID, reservationID, 12);
    newReservation.reservationID[12] = '\0';
    newReservation.phoneNumber = phoneNumber;
    newReservation.vehicle = vehicle;
    newReservation.isBoarded = false;

    // Search for the sailing and make the reservation
    bool found = false;
    for (auto& vessel : vessels) {
        for (auto& sailing : vessel.sailings) {
            if (sailing.sailingID == sailingID) {
                found = true;
                if (newReservation.checkAvailability(0, sailingID)) {
                    sailing.makeReservation(newReservation);
                    newReservation.save(); // Save to file if binary method is implemented
                } else {
                    std::cout << "Vehicle not available for this sailing.\n";
                }
                break;
            }
        }
        if (found) break;
    }

    if (!found) {
        std::cout << "Sailing with ID " << sailingID << " not found.\n";
    }

    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}


void cancelReservation(){
    int reservationID, sailingID;

    std::cout << "Enter Reservation ID to cancel: ";
    std::cin >> reservationID;
    std::cout << "Enter Sailing ID: ";
    std::cin >> sailingID;

    // Find the sailing and cancel the reservation
    auto it = std::find_if(vessels.begin(), vessels.end(), [sailingID](const Vessel& v) {
        return std::any_of(v.sailings.begin(), v.sailings.end(), [sailingID](const Sailing& s) {
            return s.sailingID == sailingID;
        });
    });

    if (it != vessels.end()) {
        for (auto& sailing : it->sailings) {
            if (sailing.sailingID == sailingID) {
                sailing.cancelReservation(); // Assume this method exists
                std::cout << "Reservation cancelled successfully!\n";
                return;
            }
        }
        std::cout << "Sailing with ID " << sailingID << " not found.\n";
    } else {
        std::cout << "Vessel with ID not found.\n";
    }

    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(); // Wait for user to press Enter
}

void viewSailingReport(){
    int sailingID;
    std::cout << "Enter Sailing ID to view report: ";
    std::cin >> sailingID;

    // Find the sailing and view its details
    auto it = std::find_if(vessels.begin(), vessels.end(), [sailingID](const Vessel& v) {
        return std::any_of(v.sailings.begin(), v.sailings.end(), [sailingID](const Sailing& s) {
            return s.sailingID == sailingID;
        });
    });

    if (it != vessels.end()) {
        for (const auto& sailing : it->sailings) {
            if (sailing.sailingID == sailingID) {
                sailing.viewSailingDetails();
                return;
            }
        }
        std::cout << "Sailing with ID " << sailingID << " not found.\n";
    } else {
        std::cout << "Vessel with ID not found.\n";
    }

    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(); // Wait for user to press Enter
}

void viewSailingVacancy(){
    int sailingID;
    std::cout << "Enter Sailing ID to check vacancy: ";
    std::cin >> sailingID;

    // Find the sailing and check its availability
    auto it = std::find_if(vessels.begin(), vessels.end(), [sailingID](const Vessel& v) {
        return std::any_of(v.sailings.begin(), v.sailings.end(), [sailingID](const Sailing& s) {
            return s.sailingID == sailingID;
        });
    });

    if (it != vessels.end()) {
        for (const auto& sailing : it->sailings) {
            if (sailing.sailingID == sailingID) {
                sailing.checkAvailability();
                return;
            }
        }
        std::cout << "Sailing with ID " << sailingID << " not found.\n";
    } else {
        std::cout << "Vessel with ID not found.\n";
    }

    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(); // Wait for user to press Enter
}

// Function to check in a vehicle
void checkInVehicle() {
    char reservationID[13];
    std::cout << "Enter Reservation ID to check-in: ";
    std::cin >> reservationID;

    for (auto& vessel : vessels) {
        for (auto& sailing : vessel.sailings) {
            for (auto& res : sailing.reservations) {
                if (std::strncmp(res.reservationID, reservationID, 13) == 0) {
                    res.checkInReservation();
                    return;
                }
            }
        }
    }

    std::cout << "Reservation not found.\n";
}


// Function to run the user interface
bool runUserInterface(){
    printMenu();
    
    int choice;
    std::cin >> choice;

    // Handle invalid (non-integer) input
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::cout << "Invalid input. Please enter a number.\n";
        return true; 
    }

    switch (choice) {
        case 1:
            createVessel();
            break;
        case 2:
            createSailing();
            break;
        case 3:
            makeReservation();
            break;
        case 4:
            cancelReservation();
            break;
        case 5:
            viewSailingReport();
            break;
        case 6:
            viewSailingVacancy();
            break;
        case 7:
            checkInVehicle();
            break;
        case 0:
            std::cout << "Exiting the system...\n";
            return false; // Exit the loop      
        default:
            std::cout << "Invalid option. Please select again.\n";
    }

    return true; // Continue running the interface
}


void shutdown(){}

int main() {
    std::cout << "Starting system...\n";
    bool done = false;

    startup();

    while(!done){
        done = !runUserInterface();
    }

    std::cout << "Shutting down system...\n";
    shutdown();
    return 0;
}

//================ CODING CONVENTION ================
// Indentation: 4 spaces
// Braces: K&R style (same line)
// Variable names: camelCase
// Constants: ALL_CAPS
// Functions: camelCase
// Comments: Use // for inline, /* */ for block
// Header guards use ALL_CAPS with underscores
