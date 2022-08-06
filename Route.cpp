/* Author name: Leann Alhashishi
 * Class: CMSC202
 * Section number: 13
 * Author Email: lalhash1@umbc.edu
 * Date: April 4, 2022
*/
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>

#include "Route.h"
using namespace std;

// Preconditions: None
// Postconditions: Creates a new Route where m_head and m_tail point to nullptr and size = 0
Route::Route() {
m_head = nullptr;
m_tail = nullptr;
m_size = 0;
}


// Preconditions: None
// Postconditions: Sets name of route
void Route::SetName(string name) {
    m_name = name;
}


// Preconditions: There is an existing Route strand with at least one port
// Postconditions: Route is deallocated (including all dynamically allocated ports)
//                 to have no memory leaks!
Route::~Route() {
    // create temp and next ports to use in while loop
    Port* temp = m_head;
    Port* next = nullptr;

while (temp != NULL) {
    // set next equal to temp
    next = temp->GetNext();
    delete temp;
    // makes temp equal to next after deleting the previous pointer
    temp = next;

    }
}


// Preconditions: Takes in a Port
//                Requires a Route
// Postconditions: Adds the new port to the end of a route
void Route::InsertEnd(string name, string location, double north, double west) {
    // prepares a new port
    Port* newPort = new Port(name, location, north, west);


    // if route is empty, newPort will be a head node
    if (m_head == nullptr) {
        m_head = newPort;
        m_tail = newPort;
        m_size++;
        return;
    }


    // insert the node at the end
    m_tail->SetNext(newPort);
    m_tail = newPort;
    m_size++;

}


// Preconditions: Index must be less than the size of the route
//       Cannot make route less than two ports. If the route has
//       two or fewer ports, fails.
// Postconditions: Name may be updated. Size is reduced. Route has one less port.
void Route::RemovePort(int port) {
    // creates temp variable
    Port* temp1 = m_head;
    Port* prev = nullptr;

    // special case 1: first port
    if (port == 0) {
        m_head = temp1->GetNext();
        delete temp1;
        m_size--;
        return;
    }


    // traverses through list and removes node
    int i;
    for (i = 0; i < port; i++) {
        prev = temp1;
        temp1 = temp1->GetNext();
    }
    prev->SetNext(temp1->GetNext());
    delete temp1;

    // special case
    if (prev->GetNext() == nullptr) {
        m_tail = prev;
    }
    m_size--;
}


// Preconditions: Requires a Route
// Postconditions: Returns m_name;
string Route::GetName() {
   return m_name;
}


// Preconditions: Requires a Route with at least two ports
// Postconditions: Returns m_name;
string Route::UpdateName() {
    if (m_head == nullptr) {
        // return empty string if the head is pointing to null
        return "";
    } else {
        m_name = m_head->GetName() + " to " + m_tail->GetName(); // updates name to head and tail
        return m_name;

    }
}


// Preconditions: Requires a Route
// Postconditions: Returns m_size;
int Route::GetSize() {
return m_size;

}


// Preconditions: Reverses the Route
// Postconditions: Route is reversed in place; nothing returned
void Route::ReverseRoute() {
    // create temp variable and last variable to adjust list
    Port* temp = m_head;
    Port* last = nullptr;
    Port* current = nullptr;

    // adjusts the links of the ports to reverse route
    while (temp != nullptr) {
        current = temp->GetNext();
        temp->SetNext(last);
        last = temp;
        temp = current;

    }
    // sets the head to the last port
    m_tail = m_head;
    m_head = last;


}


// Preconditions: Requires a Route
// Post-conditions: Returns the port from specific item
Port* Route::GetData(int index) {
Port* temp = m_head;
// index of node
int count = 0;

while (temp != NULL) {
    // if the data matches
    if (count == index) {
        return (temp);

    }
    count++;
    // temp now points to next
    temp = temp->GetNext();

}
// if temp equals null, return nullptr
return nullptr;
}


// Preconditions: Requires a Route
// Postconditions: Displays all of the ports in a route
void Route::DisplayRoute() {

        // creates temp variable to use in for loop
        Port *temp = m_head;
        for (int i = 0; i < m_size; i++) {

            // print statement that matches the document's formatting of the routes

            cout << i + 1 << ". " << temp->GetName() << ", " << temp->GetLocation() <<
            " (N" << temp->GetNorth() << " W" << temp->GetWest() << ")" << endl;
            temp = temp->GetNext();
        }


}


