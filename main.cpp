#include <iostream>

#include "Sailing.h"
#include "Reservation.h"
#include "Vessel.h"
#include "Vehicle.h"

// Function prototypes (defined elsewhere)
void startup(){}
void runUserInterface(){}
void shutdown(){}

int main() {
    std::cout << "Starting system...\n";
    startup();

    runUserInterface();

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
