#include <iostream>  // input and output operations
#include <vector> // dynamic array that can resize itself automatically
#include <unordered_map> // hash table-based array that stores key-value pair
#include <fstream> // file stream classes: ifstream, ofstream, fstream reading and writing to files
#include <sstream> // string streams for string manipulation and parsing
#include <limits> // information about arithmetic types
#include <algorithm> // common algorithms to operate on containers
#include <stdexcept> // standard exception classes for error handling

using namespace std; // contains all c++ library components

struct Hospital {
    string name;
    string type;
    string location;
    string director;
    int doctors, nurses, cleaners, management, patients;
};

class HospitalGraph {
private:
    unordered_map<string, Hospital> hospitals;  // define hospitals
    unordered_map<string, unordered_map<string, int>> edges;
    const string defaultFile = "database.txt";

    // Helper function to validate non-empty string input
    bool isValidString(const string& input) {
        return !input.empty() && all_of(input.begin(), input.end(), [](char c) { return !isspace(c) || c == ' '; });
    } //for complex things: if I need a user to write the whole string

//bool isValidCommand(const string& input, int minCmd = 1, int maxCmd = 12) {
//    // Check if input is a single character representing a digit
//    if (input.empty() || input.size() > 2) return false; // Reject empty/multi-char input
//    
//    // Check if all characters are digits
//    if (!all_of(input.begin(), input.end(), ::isdigit)) {
//        cout << "Error: Input must be a number.\n";
//        return false;
//    }
//
//    // Convert to integer and check range
//    int cmd = stoi(input);
//    if (cmd < minCmd || cmd > maxCmd) {
//        cout << "Error: Command must be between " << minCmd << " and " << maxCmd << ".\n";
//        return false;
//    }
//    
//    return true;
//}

   
  // Helper function to get valid integer input
  
    // Helper function to clear input buffer
    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

public:
	
	 bool getValidInteger(int& value, const string& prompt) {
        cout << prompt;
        string input;
        getline(cin, input);
        try {
            size_t pos;
            value = stoi(input, &pos);
            if (pos != input.length()) {
                cout << "Error: Invalid input. Please enter a number.\n";
                return false;
            }
            if (value < 0) {
                cout << "Error: Number cannot be negative.\n";
                return false;
            }
            return true;
        } catch (...) {
            cout << "Error: Please enter a valid number.\n";
            return false;
        }
    }
    
    bool loadFromFile() {
        ifstream file(defaultFile); // open the database file to read from it
        if (!file.is_open()) {
            cout << "Error: Could not open file " << defaultFile << " for reading.\n";
            return false; // if the file not open send the error
        }
        string line; // this is the header line and checks whether it's not empty if empty means the file empty/ corrupted
        if (!getline(file, line)) { // Check header
            cout << "Error: File is empty or corrupted.\n";
            file.close(); // then close the file if it finds it empty or corrupted
            return false;
        }
        while (getline(file, line)) { // while the line header line not empty then
            stringstream ss(line); //splits csv fields
            Hospital h;
            string val;
            try {
                getline(ss, h.name, ','); // see if the hospital name isn't empty
                if (!isValidString(h.name)) throw runtime_error("Invalid hospital name."); // if the name is not valid string throw error
                getline(ss, h.type, ','); //// check is hospital type field isn't empty
                getline(ss, h.location, ','); // checke whther location isn't empty
                getline(ss, h.director, ','); // director name isn't empty
                getline(ss, val, ','); // reads string val until it reaches , delimiter
				h.doctors = stoi(val); // converts string val to int
                getline(ss, val, ','); // reads string val until it reaches , delimiter
				h.nurses = stoi(val);// converts string val to int
                getline(ss, val, ',');// reads string val until it reaches , delimiter
				h.cleaners = stoi(val);// converts string val to int
                getline(ss, val, ','); // reads string val until it reaches , delimiter
				h.management = stoi(val);// converts string val to int
                getline(ss, val); // reads string val until it reaches , delimiter
				h.patients = stoi(val);// converts string val to int
                if (h.doctors < 0 || h.nurses < 0 || h.cleaners < 0 || h.management < 0 || h.patients < 0) {
                    throw runtime_error("Negative values not allowed."); // check if numbeers added are not negative numbers
                }
                hospitals[h.name] = h; // then store valid hospital in hospitals map
            } catch (const exception& e) {
                cout << "Error parsing line: " << line << " (" << e.what() << ")\n"; // invalid lines
                continue; // skip them and continue parsing
            }
        }
        file.close(); // then close the file
        return true; // return true
    }

    bool saveToDefaultFile() {
        ofstream file(defaultFile); // open database file for writing while ifstream opens for reading
        if (!file.is_open()) { //
            cout << "Error: Could not open file " << defaultFile << " for writing.\n";
            return false; // if file can't be opened
        }
        file << "Name,Type,Location,Director,Doctors,Nurses,Cleaners,Management,Patients\n";  // write csv's header line
        for (const auto& [_, h] : hospitals) { //
            file << h.name << "," << h.type << "," << h.location << "," << h.director << ","
                 << h.doctors << "," << h.nurses << "," << h.cleaners << ","// wrtite each hospitals data as comma-separated
                 << h.management << "," << h.patients << "\n";
        }
        file.close(); // CLOSE THE FILE
        return true; // then return true
    }

    void addHospital() {
        Hospital h;
        clearInputBuffer(); // clear any residual input
        cout << "Name: "; getline(cin, h.name); // prompts for each field and validates the user input
        if (!isValidString(h.name)) {
            cout << "Error: Hospital name cannot be empty.\n";
            return;
        }
        if (hospitals.count(h.name)) {
            cout << "Error: Hospital with name '" << h.name << "' already exists.\n"; // if hosptials has the same count with h.name entered now
            // then the hosptial with the same name exists
            return;
        }
        cout << "Type: "; getline(cin, h.type);
        if (!isValidString(h.type)) {
            cout << "Error: Type cannot be empty.\n"; // prompts for type and vsalidates it
            return;
        }
        cout << "Location: "; getline(cin, h.location);  // prompts locatrion and validates
        if (!isValidString(h.location)) {
            cout << "Error: Location cannot be empty.\n";
            return;
        }
        cout << "Director: "; getline(cin, h.director);
        if (!isValidString(h.director)) { // validates director and validates
            cout << "Error: Director cannot be empty.\n";
            return;
        }
        if (!getValidInteger(h.doctors, "Doctors: ")) return;
        if (!getValidInteger(h.nurses, "Nurses: ")) return;
        if (!getValidInteger(h.cleaners, "Cleaners: ")) return;
        if (!getValidInteger(h.management, "Management: ")) return;
        if (!getValidInteger(h.patients, "Patients: ")) return;
        hospitals[h.name] = h;
        if (saveToDefaultFile()) {
            cout << "Hospital added successfully.\n"; // saving the hosptial data to the database file
        }
    }

    void connectHospitals() {
        string h1, h2; // both hosptals
        int dist; // define distance betweem these hospitals
        clearInputBuffer(); // clear input buffer
        cout << "Base hospital name: "; getline(cin, h1);
        if (!hospitals.count(h1)) { // prompts user to add h1 and validates if it exists
            cout << "Error: Hospital '" << h1 << "' not found.\n";
            return;
        }
        cout << "Hospital to connect to: "; getline(cin, h2);
        if (!hospitals.count(h2)) { // prompts user to add h2 and validates if it exists too
            cout << "Error: Hospital '" << h2 << "' not found.\n";
            return;
        }
        if (h1 == h2) {
            cout << "Error: Cannot connect a hospital to itself.\n";
            return; // if they are the same then no connection gcan happen h1==h2?????
        }
        if (!getValidInteger(dist, "Distance (km): ")) return;
        edges[h1][h2] = dist; // add the distance to both directions coming or going to one h from another h
        edges[h2][h1] = dist;
        cout << "Hospitals connected successfully.\n";
    }

    void viewAll() {
        if (hospitals.empty()) {
            cout << "No hospitals in the system.\n"; // if no hospitals in system, then you can't view any
            return;
        }
        for (const auto& [_, h] : hospitals)
            displayHospitalWithConnections(h.name); //on each hopsital diplay it with it's connections
    }

    void viewHospital() {
        clearInputBuffer(); // view one hosptial specifially
        string name;
        cout << "Enter hospital name: "; getline(cin, name); // viwe by hospital name
        if (hospitals.count(name)) {
            displayHospitalWithConnections(name); // if exists display it with the conections
        } else {
            cout << "Error: Hospital '" << name << "' not found.\n";
        } // if not found then not found!!!!!!!
    }

    void viewConnections() {
        clearInputBuffer();
        string name;
        cout << "Enter hospital name: "; getline(cin, name); // view connections by hosptiaL NAME: THE CONNECTIONS coming from  this h.name
        if (!hospitals.count(name)) {
            cout << "Error: Hospital '" << name << "' not found.\n";
            return; // check if hospital exists
        }
        if (!edges.count(name)) {
            cout << "No connections found for hospital: " << name << "\n"; // check if it has some connections
            return;
        }
        cout << "\nConnections from " << name << ":\n";
        for (const auto& [other, dist] : edges[name]) {
            cout << " -> " << other << " : " << dist << " km\n";
        }
    }

    void deleteHospital() {
        clearInputBuffer();
        string name;
        cout << "Enter hospital name: "; getline(cin, name); // delete the hosptial by hospital name
        if (!hospitals.count(name)) {
            cout << "Error: Hospital '" << name << "' not found.\n"; // check is that hospital even exists
            return;
        }
        hospitals.erase(name); // h.erase(name) function to delete the hospital
        edges.erase(name); // delete the edges on this hosptial too
        for (auto& [_, e] : edges) e.erase(name); // then save to database file
        if (saveToDefaultFile()) {
            cout << "Hospital deleted successfully.\n"; // success message
        }
    }

    void deleteAll() {
        if (hospitals.empty()) {
            cout << "No hospitals to delete.\n"; // you can delete all
            return;// first check whether that hosptials even are there
        }
        hospitals.clear(); // then hs.clear() to delete all, but h.erase() to delete one
        edges.clear(); // clear the edges too
        if (saveToDefaultFile()) { // then save tha ction in database file
            cout << "All hospitals deleted successfully.\n";
        }
    }

  void updateHospital() {
        clearInputBuffer();
        string name;
        cout << "Enter hospital name: "; getline(cin, name);
        if (!hospitals.count(name)) {
            cout << "Error: Hospital '" << name << "' not found.\n";
            return;
        }
        
        Hospital newData;
        cout << "Enter new data:\n";
        cout << "Name: "; getline(cin, newData.name);
        if (!isValidString(newData.name)) {
            cout << "Error: Hospital name cannot be empty.\n";
            return;
        }
        if (hospitals.count(newData.name) && newData.name != name) {
            cout << "Error: Hospital with name '" << newData.name << "' already exists.\n";
            return;
        }
        
        cout << "Type: "; getline(cin, newData.type);
        if (!isValidString(newData.type)) {
            cout << "Error: Type cannot be empty.\n";
            return;
        }
        cout << "Location: "; getline(cin, newData.location);
        if (!isValidString(newData.location)) {
            cout << "Error: Location cannot be empty.\n";
            return;
        }
        cout << "Director: "; getline(cin, newData.director);
        if (!isValidString(newData.director)) {
            cout << "Error: Director cannot be empty.\n";
            return;
        }
        if (!getValidInteger(newData.doctors, "Doctors: ")) return;
        if (!getValidInteger(newData.nurses, "Nurses: ")) return;
        if (!getValidInteger(newData.cleaners, "Cleaners: ")) return;
        if (!getValidInteger(newData.management, "Management: ")) return;
        if (!getValidInteger(newData.patients, "Patients: ")) return;

        // If name changed, update edges
        if (name != newData.name) {
            if (edges.count(name)) {
                edges[newData.name] = edges[name];
                edges.erase(name);
                for (auto& [_, e] : edges) {
                    if (e.count(name)) {
                        e[newData.name] = e[name];
                        e.erase(name);
                    }
                }
            }
        }
        
        hospitals.erase(name);
        hospitals[newData.name] = newData;
        
        if (saveToDefaultFile()) {
            cout << "Hospital updated successfully.\n";
        }
    }

    void searchHospital() { // search hospital by key
        clearInputBuffer();
        string key;
        cout << "Enter search key: "; getline(cin, key); // enter search key
        if (key.empty()) {
            cout << "Error: Search key cannot be empty.\n"; // key must not be empty, you have to give it
            return;
        }
        bool found = false;
        for (const auto& [_, h] : hospitals) {
            if (h.name.find(key) != string::npos || h.location.find(key) != string::npos || h.director.find(key) != string::npos) {
                displayHospitalWithConnections(h.name);
                found = true;
            }
        } // then find based on the key
        if (!found) {
            cout << "No hospitals found matching '" << key << "'.\n"; // throw error if not found
        }
    }

    void displayHospital(const Hospital& h) {
        cout << "\nName: " << h.name
             << "\nType: " << h.type
             << "\nLocation: " << h.location
             << "\nDirector: " << h.director
             << "\nDoctors: " << h.doctors
             << "\nNurses: " << h.nurses
             << "\nCleaners: " << h.cleaners
             << "\nManagement: " << h.management
             << "\nPatients: " << h.patients << "\n";
    } // display the hopsital details

    void displayHospitalWithConnections(const string& name) {
        if (!hospitals.count(name)) return;
        displayHospital(hospitals[name]);
        if (edges.count(name)) {
            cout << "Connections:\n";
            for (const auto& [other, dist] : edges[name]) {
                cout << " - " << other << " (" << dist << " km)\n";
            }
        } else {
            cout << "No connected hospitals.\n";
        }
    } // display hosptial det and the connections it have

    bool saveToFile() {
        clearInputBuffer();
        string filename; // define file name on which you're going to save the things 
        cout << "Enter filename (e.g., data.csv): "; getline(cin, filename);
        if (filename.empty()) {
            cout << "Error: Filename cannot be empty.\n";
            return false; // check if it' empty since it must not be empty
        }
        ofstream file(filename); // open the file for writing
        if (!file.is_open()) {
            cout << "Error: Could not open file " << filename << " for writing.\n";
            return false;
        }
        file << "Name,Type,Location,Director,Doctors,Nurses,Cleaners,Management,Patients\n"; // add file headers
        for (const auto& [_, h] : hospitals) { // then save data in form of csv, where they'll be separated by (,) simply
            file << h.name << "," << h.type << "," << h.location << "," << h.director << ","
                 << h.doctors << "," << h.nurses << "," << h.cleaners << ","
                 << h.management << "," << h.patients << "\n";
        }
        file.close(); // then close the file
        cout << "Data saved to " << filename << " successfully.\n";
        return true; // give notification that all is done successfully
    }

    void help() {
        cout << "\nAvailable commands:\n"
             << "1. Add a hospital\n"
             << "2. Connect two hospitals\n"
             << "3. View all hospitals\n"
             << "4. View a hospital\n"
             << "5. View connections\n"
             << "6. Delete a hospital\n"
             << "7. Delete all hospitals\n"
             << "8. Update a hospital\n"
             << "9. Search hospitals\n"
             << "10. Save to file\n"
             << "11. Show help\n"
             << "12. Exit\n"
             << "Enter a number (1-12): ";
    }
}; // help for user who don''t know the commands to use or options to choose from

int main() { ///// ONE AND ONLY ONE MAIN FUNCTION
    HospitalGraph hg; // define graph
    if (!hg.loadFromFile()) {
        cout << "Starting with an empty database.\n"; // starts with empty database
    }

    cout << "=============================================================\n";
    cout << "         WELCOME TO THE HOSPITAL MANAGEMENT SYSTEM          \n"; // welcome message
    cout << "=============================================================\n";
    hg.help(); // help to display commands which are possible

    while (true) {
        int choice;
        if (!hg.getValidInteger(choice, "")) {
            continue;
        }
        switch (choice) { // display choice or commands one may choose from
            case 1: hg.addHospital(); break;
            case 2: hg.connectHospitals(); break;
            case 3: hg.viewAll(); break;
            case 4: hg.viewHospital(); break;
            case 5: hg.viewConnections(); break;
            case 6: hg.deleteHospital(); break;
            case 7: hg.deleteAll(); break;
            case 8: hg.updateHospital(); break;
            case 9: hg.searchHospital(); break;
            case 10: hg.saveToFile(); break;
            case 11: hg.help(); break;
            case 12: cout << "We will be happy tp see you back. Byeee\n"; return 0;
            default: cout << "Error: Invalid choice. Enter a number between 1 and 12.\n"; break; // if u add one which is not between 1-12 then default error
        }
    }

    return 0;
}