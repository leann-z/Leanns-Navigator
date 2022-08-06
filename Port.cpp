/* Author name: Leann Alhashishi
 * Class: CMSC202
 * Section number: 13
 * Author Email: lalhash1@umbc.edu
 * Date: April 4, 2022
*/
#include "Port.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Preconditions: None
// Postconditions: Creates a new Port for use in a Route
Port::Port(){
    // create a “New Port” from a “New Location” with north and west of 0
    m_location = "New location";
    m_name = "New Port";
    m_north = 0;
    m_west = 0;
    // sets next pointer to nullptr
    m_next = nullptr;
}


// Preconditions: None
// Postconditions: Creates a new port for use in a Route
Port::Port(string name, string location, double north, double west) {
    // Simply sets all the variables
    m_name = name;
    m_location = location;
    m_north = north;
    m_west = west;
}


// Preconditions: There is an existing port
// Postconditions: Port is deallocated and has no memory leaks!
Port::~Port() {
    // de-constructor

}


// Preconditions: None
// Postconditions: Returns the name of the port
string Port::GetName() {
    return m_name;
}


// Preconditions: None (may return either port or nullptr)
// Postconditions: Returns m_next;
Port* Port::GetNext() {
    return m_next;
}


// Preconditions: None
// Postconditions: Returns the N coordinates of the port
double Port::GetNorth() {
    return m_north;
}


// Preconditions: None
// Postconditions: Returns the W coordinates of the port
double Port::GetWest() {
    return m_west;
}


// Preconditions: None
// Postconditions: Returns the description of where the port is located
string Port::GetLocation() {
    return m_location;
}


// Preconditions: None
// Postconditions: Sets the next port
void Port::SetNext(Port* next) {
        m_next = next;

}


