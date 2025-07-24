/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * File:        Vehicle.cpp
 * Description: Implements the Vehicle module. A Vehicle contains license plate,
 *              dimensions, and type. Used as part of a Reservation and not stored independently.
 * Author:      Team 21
 *
 * Version History:
 * *  v1.0 (2025-07-24) — initial implementation
 * @@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 */

#include "Vehicle.h"

Vehicle::Vehicle()
  : licensePlate(), length(0), height(0),
    isSpecial(false), type(VehicleType::REGULAR) {}

Vehicle::~Vehicle() {}

