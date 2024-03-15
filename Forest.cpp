// Forest.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <queue>

// Files Included
#include "Project.h"
#include "ProjectGenerator.h"
#include <string>
#include <vector>

#include <iomanip> // For setw()


using namespace std;


string projectsLog = "projects_log.txt";

// vector to store completed projects
vector<Project> completedProjects;

// Queue of projects
queue <Project> projectQueue;

// Function to print a horizontal line
void printHorizontalLine() {
    cout << std::string(50, '-') << endl;
}



void queueProject() {
    int newProjects;
    int newProject = rand() % 15; // Generate a random number to decide how many projects to queue
    if (newProject == 0) {
        newProjects = 1; // 1 in 15 chance for one project
    }
    else {
        newProjects = 0; // 14 in 15 chance for no projects
    }

    for (int i = 0; i < newProjects; ++i) {
        projectQueue.push(Project());
    }
}


void completeProject(int& curProjectTime, int& projectCount) {
    // Process projects in the queue until the end of the simulated time
        if (projectQueue.empty() == false) {

            if (curProjectTime >= projectQueue.front().getCompletionTime()) {
                projectCount++;
                curProjectTime = 0; // Reset current project time
                //cout << "Project completion time: " << projectQueue.front().getCompletionTime() << endl; // debug for completion time
                projectQueue.front().changeStatus();

                // Move completed project to the vector of completed projects
                completedProjects.push_back(projectQueue.front()); // add completed project to Vector
                projectQueue.front().writeToFile(projectsLog);
                projectQueue.pop(); // Remove completed project from the queue
            }
            else {

                // Increment current project time
                curProjectTime += workingRate() ;
            }
        }
        
    }

void printSimulationResults(int totalTime, int projectCount) {
    cout << "\nSimulation ended!" << endl;
    cout << totalTime << " days have of work have been simulated" << endl;
    printHorizontalLine();
    cout << std::setw(25) << std::left << "Projects pending:";
    cout << std::setw(5) << std::right << projectQueue.size() << endl;
    cout << std::setw(25) << std::left << "Projects completed:";
    cout << std::setw(5) << std::right << projectCount << endl;
    printHorizontalLine();
}

int getUserYears() {
    int years;
    cout << "Enter the number of years to simulate: ";
    cin >> years;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
    return years;
}

int main()
{
    // Clear the content of projects_log.txt
    clearLogFile(projectsLog);

    cout << "Simulation begins!" << endl;
    cout << "This Program is simulating the Work Rate of a Foresting Company" << endl;
    srand(static_cast<unsigned int>(time(nullptr)));

    int years;
    do {
        years = getUserYears();
        if (years > 0) {
            int totalTime = years * 365;
            int currentTime = 0;
            int currentProjectTime = 0;
            int projectCount = 0;

            while (currentTime < totalTime) {
                completeProject(currentProjectTime, projectCount);
                queueProject();
                currentTime++;
            }

            printSimulationResults(totalTime, projectCount);
            writePendingProjectsToFile(projectsLog, projectQueue);
        }
        else if (years != 0) {
            cout << "Invalid input. Please enter a positive number of years or '0' to exit." << endl;
        }
    } while (years != 0);


    return 0;
    /*
    cout << "Simulation begins!\n";

    srand(time(NULL));

    int totalTime = 1825; // Total simulation time in days
    int currentTime = 0; // Current time in days
    int currentProjectTime = 0; // Days spent om Current Poorject;
    int projectCount = 0;

    // Loop to simulate the passage of time
    while (currentTime < totalTime) {
        // Process projects in the queue
        completeProject(currentProjectTime, projectCount);

        // Add new projects to the queue
        queueProject();

        currentTime++; // Increment current time
    }
    writeUncompletedProjectsToFile(projectsLog, projectQueue);

    // Output simulation results
    std::cout << "\nSimulation ended!\n";
    cout << totalTime << " days have of work have been simulated\n";
    printHorizontalLine();
    cout << std::setw(25) << std::left << "Projects pending:";
    std::cout << std::setw(5) << std::right << projectQueue.size() << std::endl;

    cout << std::setw(25) << std::left << "Projects completed:";
    cout << std::setw(5) << std::right << projectCount << std::endl;
    printHorizontalLine();
 */

    return 0;

}

