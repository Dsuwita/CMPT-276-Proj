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
    std::cout << "0. Exit\n\n\n";
    std::cout << "Please select an option: ";
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

void makeReservation(){
    int reservationID, phoneNumber, vehicleID, sailingID;
    Vehicle vehicle; // Assume Vehicle has a method to input details
    Reservation newReservation;

    std::cout << "Enter Reservation ID: ";
    std::cin >> reservationID;
    std::cout << "Enter Phone Number: ";
    std::cin >> phoneNumber;
    std::cout << "Enter Vehicle ID: ";
    std::cin >> vehicleID;
    std::cout << "Enter Sailing ID: ";
    std::cin >> sailingID;

    // Set the reservation details
    newReservation.reservationID = reservationID;
    newReservation.phoneNumber = phoneNumber;
    newReservation.vehicle = vehicle; // Assume vehicle details are set

    // Find the sailing and add the reservation
    auto it = std::find_if(vessels.begin(), vessels.end(), [sailingID](const Vessel& v) {
        return std::any_of(v.sailings.begin(), v.sailings.end(), [sailingID](const Sailing& s) {
            return s.sailingID == sailingID;
        });
    });

    if (it != vessels.end()) {
        for (auto& sailing : it->sailings) {
            if (sailing.sailingID == sailingID) {
                if (newReservation.checkAvailability(vehicleID, sailingID)) {
                    sailing.makeReservation(newReservation);
                    std::cout << "Reservation made successfully!\n";
                } else {
                    std::cout << "Vehicle not available for this sailing.\n";
                }
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
            for(int i = 0; i < vessels.size(); ++i) {
                std::cout << "Vessel ID: " << vessels[i].vesselID << ", Name: " << vessels[i].vesselName << "\n";
            }
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
