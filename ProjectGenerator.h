// ProjectGeneratot.h
#ifndef PROJECT_GENERATOR_H
#define PROJECT_GENERATOR_H

#include <string>
#include <queue>
using namespace std;


struct TreeComposition {
    int pinePercentage;
    int birchPercentage;
    int sprucePercentage;

    // Overload the += operator to add compositions
    TreeComposition& operator+=(const TreeComposition& other) {
        pinePercentage += other.pinePercentage;
        birchPercentage += other.birchPercentage;
        sprucePercentage += other.sprucePercentage;
        return *this;
    }
    
};

class Project {
private:
    int size; // size of the project in hectares
    int id; // identifier for project
    int completion; // time it takes to complete the project
    TreeComposition composition;
    string status; // Status of the project (PENDING or COMPLETED)

public:
    // Constructor declarations
    Project(int _size, int _id, TreeComposition _composition);
    Project(); // Declaration for the default constructor

    // Getter for completion time
    int getCompletionTime() const;
    int getSize()const;
    TreeComposition getComposition()const;
    string getStatus() const; // Getter for project status
    int getId() const; // Getter for project ID

    TreeComposition calculateTreesPlanted(int projectSize, const TreeComposition& composition);
    void changeStatus(); // Function to change project status


    // Function to write project information to a file
    void writeToFile(const std::string& filename) const;

    // Overload the <<, >>, and < operators
    friend std::ostream& operator<<(std::ostream& os, const Project& project);
    friend std::istream& operator>>(std::istream& is, Project& project);
    bool operator<(int date) const;


private:
    // Function to calculate time it takes to complete project
    int calculateProcessingTime(int area, int pinePercentage, int sprucePercentage, int birchPercentage);
};

// Write uncompleted projects to file
void writePendingProjectsToFile(const std::string& filename, std::queue<Project>& projectQueue);

// Function declarations
int workingRate();

void clearLogFile(const std::string& filename);

TreeComposition createRandomComposition();
int generateRandomSize();
int generateSequentialID();

void generateSampleProjects(const std::string& filename, int numProjects);



#endif // PROJECT_GENERATOR_H
