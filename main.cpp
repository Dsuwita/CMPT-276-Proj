/*
 * File:        main.cpp
 * Description: Main entry point for the Vessel Management System. Provides a user interface
 *              for managing vessels, sailings, and reservations. Implements a menu-driven
 *              system for creating vessels, sailings, making reservations, and viewing reports.
 * Author:      Team 21
 *
 * Version History:
 * *  v1.0 (2025-07-24) — initial implementation
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

// Function to initialize the system
void startup() {
    Vessel::loadAll(vessels);
    Sailing::loadAll(vessels);
    Reservation::loadAll(vessels);
}

// Function to print the menu
void printMenu() {
    std::cout << "\033[2J\033[1;1H"; // Clear screen
    std::cout << "==================== Vessel Management System ====================\n\n";
    std::cout << "Welcome to the Vessel Management System\n";
    std::cout << "1. Create New Vessel\n";
    std::cout << "2. Create New Sailing\n";
    std::cout << "3. Make Reservation\n";
    std::cout << "4. Cancel Reservation\n";
    std::cout << "5. View Sailing Report\n";
    std::cout << "6. Check In Vehicle\n";
    std::cout << "7. View All Vessels\n";
    std::cout << "0. Exit\n";
}

// Function to input vehicle details

void inputVehicle(Vehicle& vehicle) {
    std::cout << "Enter license plate (max 9 characters): ";
    std::cin >> vehicle.licensePlate;
    std::cout << "Enter vehicle length: ";
    std::cin >> vehicle.length;
    std::cout << "Enter vehicle height: ";
    std::cin >> vehicle.height;
    std::cout << "Is this a special vehicle? (1 for yes, 0 for no): ";
    std::cin >> vehicle.isSpecial;

    int type;
    std::cout << "Enter vehicle type (0 = REGULAR, 1 = OVERSIZE_LOW, 2 = OVERSIZE_HIGH): ";
    std::cin >> type;
    vehicle.type = static_cast<Vehicle::VehicleType>(type);
}

// Function to create a new vessel

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

// Function to create a new sailing

void createSailing() {
    char sailingID[10];
    int vesselID;
    date depDate;
    float hrl, lrl;

    std::cout << "Enter Sailing ID (max 9 characters): ";
    std::cin >> sailingID;
    sailingID[9] = '\0';

    std::cout << "Enter Vessel ID: ";
    std::cin >> vesselID;

    std::cout << "Enter Departure Date (day month year hour): ";
    std::cin >> depDate.day >> depDate.month >> depDate.year >> depDate.hour;

    std::cout << "Enter High Ceiling Remaining Lane (HRL): ";
    std::cin >> hrl;
    std::cout << "Enter Low Ceiling Remaining Lane (LRL): ";
    std::cin >> lrl;

    Sailing newSailing(sailingID, depDate, hrl, lrl);

    for (const auto& vessel : vessels) {
        for (const auto& sailing : vessel.sailings) {
            if (std::strncmp(sailing.sailingID, sailingID, 10) == 0) {
                std::cout << "Sailing with ID " << sailingID << " already exists.\n";
                std::cout << "Press Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                return;
            }
        }
    }

    auto it = std::find_if(vessels.begin(), vessels.end(), [vesselID](const Vessel& v) {
        return v.vesselID == vesselID;
    });

    if (it != vessels.end()) {
        it->addSailing(newSailing);
        std::cout << "Sailing created successfully!\n";
    } else {
        std::cout << "Vessel with ID " << vesselID << " not found.\n";
    }

    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// Function to make a reservation

void makeReservation() {
    char reservationID[13];
    char sailingID[10];
    char phoneNumber[10];
    Vehicle vehicle;

    std::cout << "Enter Phone Number: ";
    std::cin >> phoneNumber;
    phoneNumber[10] = '\0'; 

    std::cout << "Enter Sailing ID (max 9 characters): ";
    std::cin >> sailingID;
    sailingID[9] = '\0';

    std::cout << "Enter Vehicle Details:\n";
    inputVehicle(vehicle);

    Reservation newReservation;
    std::strncpy(newReservation.reservationID, reservationID, 12);
    newReservation.reservationID[12] = '\0';
    std::strncpy(newReservation.phoneNumber, phoneNumber, 14);
    newReservation.phoneNumber[10] = '\0';
    newReservation.vehicle = vehicle;
    newReservation.isBoarded = false;

    bool found = false;
    for (auto& vessel : vessels) {
        for (auto& sailing : vessel.sailings) {
            if (std::strncmp(sailing.sailingID, sailingID, 10) == 0) {
                std::string generatedID = sailing.generateReservationID();
                std::strncpy(reservationID, generatedID.c_str(), 12);
                reservationID[12] = '\0';
                sailing.makeReservation(newReservation);
                std::cout << "Reservation created successfully!\n";
                found = true;
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

// Function to cancel a reservation

void cancelReservation() {
    char reservationID[13];
    char sailingID[10];

    std::cout << "Enter Reservation ID (12 chars): ";
    std::cin >> reservationID;
    reservationID[12] = '\0';

    std::cout << "Enter Sailing ID (9 chars max): ";
    std::cin >> sailingID;
    sailingID[9] = '\0';

    for (auto& vessel : vessels) {
        for (auto& sailing : vessel.sailings) {
            if (std::strncmp(sailing.sailingID, sailingID, 10) == 0) {
                sailing.cancelReservation(reservationID);
                std::cout << "Reservation cancelled successfully!\n";
                std::cout << "Press Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                return;
            }
        }
    }

    std::cout << "Sailing with ID " << sailingID << " not found.\n";
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// Function to view sailing report
void viewSailingReport() {
    char sailingID[10];
    std::cout << "Enter Sailing ID to view report (9 chars max): ";
    std::cin >> sailingID;
    sailingID[9] = '\0';

    for (const auto& vessel : vessels) {
        for (const auto& sailing : vessel.sailings) {
            if (std::strncmp(sailing.sailingID, sailingID, 10) == 0) {
                sailing.viewSailingDetails();
                std::cout << "Press Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                return;
            }
        }
    }

    std::cout << "Sailing with ID " << sailingID << " not found.\n";
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// Function to check in a vehicle
void checkInVehicle() {
    char reservationID[13];
    std::cout << "Enter Reservation ID (12 chars max): ";
    std::cin >> reservationID;
    reservationID[12] = '\0';

    for (auto& vessel : vessels) {
        for (auto& sailing : vessel.sailings) {
            for (auto& res : sailing.reservations) {
                if (std::strncmp(res.reservationID, reservationID, 13) == 0) {
                    res.checkInReservation();
                    std::cout << "Press Enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                    return;
                }
            }
        }
    }

    std::cout << "Reservation not found.\n";
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
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
            checkInVehicle();
            break;
        case 7:
            for(const auto& vessel : vessels) {
                vessel.viewVesselDetails();
            }
            std::cout << "Press Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        case 0:
            std::cout << "Exiting the system...\n";
            return false; // Exit the loop      
        default:
            std::cout << "Invalid option. Please select again.\n";
    }

    return true; // Continue running the interface
}

// Function to shut down the system
void shutdown() {
    Vessel::saveAll(vessels);
    Sailing::saveAll(vessels);
    Reservation::saveAll(vessels);
}

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
