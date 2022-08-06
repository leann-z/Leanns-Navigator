/* Author name: Leann Alhashishi
 * Class: CMSC202
 * Section number: 13
 * Author Email: lalhash1@umbc.edu
 * Date: April 4, 2022
*/
#include "Navigator.h"
#include <iostream>
using namespace std;

int main (int argc, char* argv[]) {
  if (argc < 2)
    {
      cout << "You are missing a data file." << endl;
      cout << "Expected usage ./proj3 proj3_data.txt" << endl;
      cout << "File 1 should be a file with ports" << endl;
    }
  else
    {
      cout << endl << "***Navigator***" << endl << endl;
      Navigator S = Navigator(argv[1]);
      S.Start();
    }
  return 0;
}