#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <string>
#include <vector>
#include <map>

using namespace std;

struct Hospital {
    string id;
    string name;
    string location;
    int numPatients;
};

struct Edge {
    string toHospital;
    double distance;
};

class HospitalManagement {
private:
    map<string, Hospital> hospitals; 
    map<string, vector<Edge>> adjList; 

    void saveHospitalsToCSV();
    void saveEdgesToCSV();
    void loadHospitalsFromCSV();
    void loadEdgesFromCSV();

public:
    HospitalManagement();
    void viewHospitals();
    void addHospital();
    void updateHospital();
    void deleteHospital();
    void linkHospitals();
    void viewGraph();
};

#endif