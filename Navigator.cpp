/* Author name: Leann Alhashishi
 * Class: CMSC202
 * Section number: 13
 * Author Email: lalhash1@umbc.edu
 * Date: April 4, 2022
*/
#include "Navigator.h"
#include <sstream>
using namespace std;

// Preconditions:  Provided with a filename of ports to load
// Postconditions: m_filename is populated with fileName
Navigator::Navigator(string fileName) {
m_fileName = fileName;
}


// Preconditions: There is an existing Navigator
// Postconditions: All ports and routes are cleared
Navigator::~Navigator() {
//delete m_ports;
    for (int i = 0; i < m_ports.size(); i++) {
        delete m_ports.at(i);
    }
//delete m_routes;
    for (int i = 0; i < m_routes.size(); i++) {
        delete m_routes.at(i);
    }
}


// Preconditions: m_fileName is populated
// Postconditions: All ports are loaded and the main menu runs
void Navigator::Start() {

    // calls readfile function to load ports
    ReadFile();

    // calls mainmenu function to run the main menu
    MainMenu();



}


// Preconditions: At least one port is in m_ports
// Postconditions: Displays all ports. Uses overloaded << provided in Port.h
void Navigator::DisplayPorts() {

    for(int i = 0; i < m_ports.size(); i++) {
        // prints out the ports with the same format as the document
        cout << i + 1 << ". " << *m_ports.at(i) << endl;
    }

}


// Preconditions: Valid file name of ports
// Postconditions: Dynamically allocates each port and enters it into m_ports
void Navigator::ReadFile() {
    // declares a delimiter
    char delimiter = ',';
    ifstream inputStream;
    // opens the file here
    inputStream.open(m_fileName);
    string portInfo = "";
    // seen in main menu
    cout << "Opened File" << endl;

    // declares variables to use for getline
    // north and west are temporarily strings so getline works
    string name;
    string location;
    string north;
    string west;

    if (inputStream.is_open()) {

        while (getline(inputStream, portInfo)){

            stringstream s(portInfo);
            getline(s, name, delimiter);
            getline(s, location, delimiter);
            getline(s, north, delimiter);
            getline(s, west, delimiter);
            // changes north and west strings to doubles
            Port* star = new Port(name, location, stod(north), stod(west));

            // populates info into m_ports
            m_ports.push_back(star);
        }
        cout << "Ports loaded: " << m_ports.size() << endl;
}
}


// Preconditions: Populated m_routes
// Postconditions: Inserts a new route into m_routes
void Navigator::InsertNewRoute() {
  DisplayPorts();
  int choice = 0;
  // creates a new route to use in while loop
  Route* r = new Route();

  while (choice != -1) {
      // if choice is -1, end loop
      cout << "Enter the number of the port to add to your Route: (-1 to end)" << endl;
      cin >> choice;
      if (choice != -1) {
          // what happens when the user inputs numbers
          Port* p = m_ports.at(choice - 1);
          r->InsertEnd(p->GetName(), p->GetLocation(), p->GetNorth(), p->GetWest());
      }
  }
  // makes sure to update the names
  r->UpdateName();
  // success message prints
  cout << "Done Building a New Route named " << r->GetName() << endl;
    m_routes.push_back(r);
}


// Preconditions: Populated m_ports
// Postconditions: Exits when someone chooses 5
void Navigator::MainMenu() {
    int choice = 0;




    while (choice != 5) {

        cout << "What would you like to do?:" << endl;
        cout << "1. Create New Route" << endl;
        cout << "2. Display Route" << endl;
        cout << "3. Remove Port From Route" << endl;
        cout << "4. Reverse Route" << endl;
        cout << "5. Exit" << endl;
        // read in and return user's choice
        cin >> choice;
        cin.ignore(256, '\n');
        // while user choice isn't 5 but is also b/w 1 and 5, the game runs
        if (choice == 1) InsertNewRoute(); // choice == 1: create new route

        else if (choice == 2) DisplayRoute(); // choice == 2: displays route

        else if (choice == 3) RemovePortFromRoute(); // choice == 3: remove port from route

        else if (choice == 4) ReverseRoute(); // choice == 4: reverses route


        else if (choice != 5) cout << "ERROR - choice must be between 1 and 5. Try Again." << endl;

    }




}


// Preconditions: Populated m_routes
// Postconditions: Returns the index of the selected route minus 1
int Navigator::ChooseRoute() {
    int choice = 0;
    cout << "Which route would you like to use?" << endl;
   for (int i = 0; i < m_routes.size(); i++) {
       // prints the current routes the user has
       cout << i + 1 << ". " << m_routes[i]->GetName() << endl;

   }
   // reads in then returns choice
   cin >> choice;
   return choice;

}


// Preconditions: Routes has more than one port
// Postconditions: Displays all ports in a route and the total miles of the route
void Navigator::DisplayRoute() {
    if (m_routes.size() == 0) {
        // if m_routes nothing inside it, display the following message:
        cout << "There are no routes to display." << endl;
    } else {
        int choice = ChooseRoute();
        // vector is looked through here
        m_routes.at(choice - 1)->DisplayRoute();
        // print statement that matches document format
        cout << "The total miles of this route is " << RouteDistance(m_routes.at(choice - 1)) << " miles" << endl;
    }


}


// Preconditions: Routes has more than one port
// Postconditions: Displays updated route with removed port and new name
void Navigator::RemovePortFromRoute() {
int choice = ChooseRoute();
// users port of choice
int portNum;
m_routes.at(choice - 1)->DisplayRoute();
cout << "Which port would you like to remove? " << endl;
cin >> portNum;

// calls the functions removeport, updatename, and displayroute for m_routes
m_routes.at(choice - 1)->RemovePort(portNum - 1);
m_routes.at(choice - 1)->UpdateName();
m_routes.at(choice - 1)->DisplayRoute();
cout << "Route named " << m_routes.at(choice - 1)->GetName() << " updated" << endl;


}


// Preconditions: Populated route with more than one port
// Postconditions: Returns the total miles between all ports in a route
double Navigator::RouteDistance(Route* r) {
    double total = 0;

    for (int i = 0; i < r->GetSize() - 1; i++) {
        // creates 2 new ports, p1 and p2 to be used for miles
        Port* p1 = r->GetData(i);
        Port* p2 = r->GetData(i+1);
        // here, uses double total to calculate distance with calcdistance function
        total += CalcDistance(p1->GetNorth(), p1->GetWest(), p2->GetNorth(), p2->GetWest());
    }
    return total;
}

void Navigator::ReverseRoute() {
    // if there are no routes to reverse
    if (m_routes.size() == 0) {
        cout << "No routes to reverse" << endl;
    } else {
        // will adjust vector to reverse route and update name
        int choice = ChooseRoute();
        m_routes.at(choice - 1)->ReverseRoute();
        m_routes.at(choice - 1)->UpdateName();
        cout << "Done reversing route " << choice - 1 << endl;
    }

}



