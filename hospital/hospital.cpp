#include "hospital.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

HospitalManagement::HospitalManagement() {
    loadHospitalsFromCSV();
    loadEdgesFromCSV();
}

// Save hospitals to CSV
void HospitalManagement::saveHospitalsToCSV() {
    ofstream file("hospitals.csv");
    if (!file.is_open()) {
        cout << "Error creating hospitals.csv\n";
        return;
    }
    file << "ID,Name,Location,NumberOfPatients\n";
    for (const auto& pair : hospitals) {
        const Hospital& h = pair.second;
        file << h.id << "," << h.name << "," << h.location << "," << h.numPatients << "\n";
    }
    file.close();
}

// Save edges to CSV
void HospitalManagement::saveEdgesToCSV() {
    ofstream file("hospital_connections.csv");
    if (!file.is_open()) {
        cout << "Error creating hospital_connections.csv\n";
        return;
    }
    file << "FromHospital,ToHospital,Distance\n";
    for (const auto& pair : adjList) {
        for (const Edge& e : pair.second) {
            file << pair.first << "," << e.toHospital << "," << e.distance << "\n";
        }
    }
    file.close();
}

// Load hospitals from CSV
void HospitalManagement::loadHospitalsFromCSV() {
    ifstream file("hospitals.csv");
    if (!file.is_open()) return; // File doesn't exist, will be created on save
    
    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, location;
        int patients;
        string temp;
        
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, location, ',');
        getline(ss, temp);
        patients = stoi(temp);
        
        Hospital h = {id, name, location, patients};
        hospitals[id] = h;
    }
    file.close();
}

// Load edges from CSV
void HospitalManagement::loadEdgesFromCSV() {
    ifstream file("hospital_connections.csv");
    if (!file.is_open()) return; // File doesn't exist, will be created on save
    
    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string from, to;
        double distance;
        string temp;
        
        getline(ss, from, ',');
        getline(ss, to, ',');
        getline(ss, temp);
        distance = stod(temp);
        
        adjList[from].push_back({to, distance});
    }
    file.close();
}

// View all hospitals
void HospitalManagement::viewHospitals() {
    if (hospitals.empty()) {
        cout << "No hospitals registered.\n";
        return;
    }
    cout << "\nRegistered Hospitals:\n";
    cout << "ID\tName\tLocation\tPatients\n";
    cout << "------------------------------------\n";
    for (const auto& pair : hospitals) {
        const Hospital& h = pair.second;
        cout << h.id << "\t" << h.name << "\t" << h.location << "\t" << h.numPatients << "\n";
    }
}

// Add a hospital
void HospitalManagement::addHospital() {
    Hospital h;
    cout << "Enter Hospital ID (e.g., H1): ";
    cin >> h.id;
    
    if (hospitals.find(h.id) != hospitals.end()) {
        cout << "Hospital ID already exists!\n";
        return;
    }
    
    cin.ignore();
    cout << "Enter Hospital Name: ";
    getline(cin, h.name);
    cout << "Enter Hospital Location: ";
    getline(cin, h.location);
    cout << "Enter Number of Patients: ";
    cin >> h.numPatients;
    
    hospitals[h.id] = h;
    saveHospitalsToCSV();
    cout << "Hospital added successfully!\n";
}

void HospitalManagement::updateHospital() {
    string id;
    cout << "Enter Hospital ID to update: ";
    cin >> id;
    
    if (hospitals.find(id) == hospitals.end()) {
        cout << "Hospital not found!\n";
        return;
    }
    
    Hospital& h = hospitals[id];
    cin.ignore();
    cout << "Enter new Hospital Name (current: " << h.name << "): ";
    getline(cin, h.name);
    cout << "Enter new Location (current: " << h.location << "): ";
    getline(cin, h.location);
    cout << "Enter new Number of Patients (current: " << h.numPatients << "): ";
    cin >> h.numPatients;
    
    saveHospitalsToCSV();
    cout << "Hospital updated successfully!\n";
}

void HospitalManagement::deleteHospital() {
    string id;
    cout << "Enter Hospital ID to delete: ";
    cin >> id;
    
    if (hospitals.find(id) == hospitals.end()) {
        cout << "Hospital not found!\n";
        return;
    }
    
    hospitals.erase(id);
    adjList.erase(id);
    for (auto& pair : adjList) {
        vector<Edge>& edges = pair.second;
        edges.erase(
            remove_if(edges.begin(), edges.end(),
                [&id](const Edge& e) { return e.toHospital == id; }),
            edges.end()
        );
    }
    
    saveHospitalsToCSV();
    saveEdgesToCSV();
    cout << "Hospital deleted successfully!\n";
}

void HospitalManagement::linkHospitals() {
    string from, to;
    double distance;
    
    cout << "Enter source Hospital ID: ";
    cin >> from;
    cout << "Enter destination Hospital ID: ";
    cin >> to;
    
    if (hospitals.find(from) == hospitals.end() || hospitals.find(to) == hospitals.end()) {
        cout << "One or both hospitals not found!\n";
        return;
    }
    
    cout << "Enter distance between them (in km): ";
    cin >> distance;
    
    adjList[from].push_back({to, distance});
    saveEdgesToCSV();
    cout << "Hospitals linked successfully!\n";
}

void HospitalManagement::viewGraph() {
    if (adjList.empty()) {
        cout << "No hospital connections exist.\n";
        return;
    }
    
    cout << "\nHospital Connections (Graph):\n";
    cout << "From\tTo\tDistance (km)\n";
    cout << "------------------------------------\n";
    for (const auto& pair : adjList) {
        for (const Edge& e : pair.second) {
            cout << pair.first << "\t" << e.toHospital << "\t" << e.distance << "\n";
        }
    }
}