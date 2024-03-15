// ProjectGenerator.cpp
#include "ProjectGenerator.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <queue>

using namespace std;


void clearLogFile(const std::string& filename) {
    std::ofstream file(filename, std::ofstream::out | std::ofstream::trunc);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to clear the file." << std::endl;
    }
    else {
        std::cout << "Cleared the content of " << filename << std::endl;
    }
}

TreeComposition createRandomComposition() {
    TreeComposition composition;
    composition.pinePercentage = rand() % 51;
    composition.sprucePercentage = rand() % (101 - composition.pinePercentage);
    composition.birchPercentage = 100 - composition.pinePercentage - composition.sprucePercentage;
    return composition;
}
int workingRate() {
    return rand() % 15 + 1;
}

int generateRandomSize() {
    //return rand() % 10 + 1; // Tamaño entre 1-30;
    //return rand() % 46 + 5; // size between 5-50 // MÁS PEQUEÑITO CABE MEJOR
    //return rand() % 96 + 5; // size between 5-100
     //return rand() % 81 + 20; // size between 20-100
     return rand() % 131 + 20; // size between 20-150
    //return rand() % 201 + 50; // size between 50-250
}

int generateSequentialID() {
    static int nextID = 1; // Static variable to keep track of the next ID
    return nextID++;
}


// ACTUAL PROJECT CLASS :D

// Function definitions for Project class
// Parameterized constructor
Project::Project(int _size, int _id, TreeComposition _composition) : size(_size), id(_id), composition(_composition) {
    completion = calculateProcessingTime(_size, _composition.pinePercentage, _composition.sprucePercentage, _composition.birchPercentage);
}

// Default Constructor
Project::Project() {
    size = generateRandomSize();
    id = generateSequentialID();
    composition = createRandomComposition();
    completion = calculateProcessingTime(size, composition.pinePercentage, composition.sprucePercentage, composition.birchPercentage);
    status = "PENDING";
}

// WRITE TO FILE PROJECT
void Project::changeStatus() {
    status = "COMPLETED";
}

// WRITE THE COMPLETED PROJECTS TO FILE


void Project::writeToFile(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::app); // Open the file in append mode
    if (!outFile.is_open()) {
        std::cerr << "Error: Failed to open the file." << std::endl;
        return;
    }

    outFile << "Project ID: " << id << std::endl;
    outFile << "Size: " << size << " hectares" << std::endl;
    outFile << "Tree Composition: Pine: " << composition.pinePercentage
        << "%, Birch: " << composition.birchPercentage
        << "%, Spruce: " << composition.sprucePercentage << "%" << std::endl;
    outFile << "Completion Time: " << completion << " days" << std::endl;
    outFile << "Status: " << status << std::endl; // Include the project status
    // Add more project information as needed

    outFile << std::endl; // Add a newline to separate projects

    outFile.close();
}

// Write uncompleted projects to file

// Write uncompleted projects to file
void writePendingProjectsToFile(const std::string& filename, std::queue<Project>& projectQueue) {
    std::ofstream outFile(filename, std::ios::app); // Open the file in append mode
    if (!outFile.is_open()) {
        std::cerr << "Error: Failed to open the file." << std::endl;
        return;
    }

    // Iterate through the queue and write pending projects to the file
    while (!projectQueue.empty()) {
        Project project = projectQueue.front();
        outFile << "Project ID: " << project.getId() << std::endl;
        outFile << "Size: " << project.getSize() << " hectares" << std::endl;
        TreeComposition composition = project.getComposition();
        outFile << "Tree Composition: Pine: " << composition.pinePercentage
            << "%, Birch: " << composition.birchPercentage
            << "%, Spruce: " << composition.sprucePercentage << "%" << std::endl;
        outFile << "Completion Time: " << project.getCompletionTime() << " days" << std::endl;
        outFile << "Status: " << project.getStatus() << std::endl; // Include the project status
        outFile << std::endl; // Add a newline to separate projects
        projectQueue.pop(); // Remove the project from the queue after writing its information
    }

    outFile.close();
}


// GETTER DEL STATUS
string Project::getStatus() const {
    return status;
}

// GETTER DEL ID
int Project::getId() const {
    return id;
}

// Getter for completion time
int Project::getCompletionTime() const {
    return completion;
}

// Function to calculate time it takes to complete project
int Project::calculateProcessingTime(int area, int pinePercentage, int sprucePercentage, int birchPercentage) {
    double processingTimePine = (pinePercentage * area)/100 / 1.0;
    double processingTimeSpruce = (sprucePercentage * area)/100 / 3;
    double processingTimeBirch = (birchPercentage * area)/100 / 0.3;

    int totalProcessingTime = static_cast<int>(processingTimePine + processingTimeSpruce + processingTimeBirch);

    return totalProcessingTime;
}

// Definition of getSize() function
int Project::getSize() const {
    return size;
}

// Definition of getComposition() function
TreeComposition Project::getComposition() const {
    return composition;
}


TreeComposition Project::calculateTreesPlanted(int projectSize, const TreeComposition& composition) {
    TreeComposition treesPlanted;

    // Calculate the number of trees per hectare for each type of tree
    int treesPerHectarePine = rand() % 1501 + 1000;  // Random number between 1000 and 2500
    int treesPerHectareSpruce = rand() % 1501 + 1000;  // Random number between 1000 and 2500
    int treesPerHectareBirch = rand() % 1501 + 1000;  // Random number between 1000 and 2500

    // Calculate the total number of trees planted for each type based on project size and composition
    treesPlanted.pinePercentage = static_cast<int>(projectSize * (composition.pinePercentage / 100.0) * treesPerHectarePine);
    treesPlanted.sprucePercentage = static_cast<int>(projectSize * (composition.sprucePercentage / 100.0) * treesPerHectareSpruce);
    treesPlanted.birchPercentage = static_cast<int>(projectSize * (composition.birchPercentage / 100.0) * treesPerHectareBirch);

    return treesPlanted;
}



// Overload the << operator to print project details
std::ostream& operator<<(std::ostream& os, const Project& project) {
    os << "Project ID: " << project.id << ", Size: " << project.size << " hectares, Completion Time: " << project.completion << " days";
    return os;
}

// Overload the < operator to compare completion time to the days gone by
bool Project::operator<(int date) const {
    return completion < date;
}

// Overload the >> operator to read data into a Project object from a stream
std::istream& operator>>(std::istream& is, Project& project) {
    // Read data into project's member variables
    is >> project.id >> project.size >> project.composition.pinePercentage
        >> project.composition.birchPercentage >> project.composition.sprucePercentage;
    return is;
}



void generateSampleProjects(const std::string& filename, int numProjects) {
    srand(static_cast<unsigned int>(time(nullptr)));
    std::ofstream outputFile(filename);
    if (!outputFile) {
        std::cerr << "Error: Failed to open the file." << std::endl;
        return;
    }
    for (int i = 0; i < numProjects; ++i) {
        Project project;
        outputFile << project; // Assuming the << operator is overloaded for Project
    }
    outputFile.close();
    std::cout << "Sample projects have been written to " << filename << std::endl;
}




