#include "hospital.h"
#include <iostream>

using namespace std;

void displayMenu() {
    cout << "\nHospital Management System\n";
    cout << "1. View Registered Hospitals\n";
    cout << "2. Add a Hospital\n";
    cout << "3. Update Hospital Details\n";
    cout << "4. Delete a Hospital\n";
    cout << "5. Link Hospitals (Add Distance)\n";
    cout << "6. View Hospital Graph\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    HospitalManagement system;
    int choice;
    
    while (true) {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                system.viewHospitals();
                break;
            case 2:
                system.addHospital();
                break;
            case 3:
                system.updateHospital();
                break;
            case 4:
                system.deleteHospital();
                break;
            case 5:
                system.linkHospitals();
                break;
            case 6:
                system.viewGraph();
                break;
            case 7:
                cout << "Exiting system.\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
    
    return 0;
}