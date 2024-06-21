#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include "avlbst.h"

bool scheduleExams(AVLTree<int, int>& examtimeslotavl, 
                   const std::vector<std::vector<int>>& studentExams, 
                   const std::vector<int>& examNumbers, 
                   int totalTimeslots, 
                   size_t currentExamIndex, 
                   std::map<int, std::set<int>>& timeslotExamsMap) {

    // Base case: All exams are scheduled
    if (currentExamIndex >= examNumbers.size()) {
        return true; 
    }

    int currentExam = examNumbers[currentExamIndex];

    // Iterate through timeslots to assign
    for (int timeslot = 1; timeslot <= totalTimeslots; timeslot++) {

        bool validAssignment = true;
        std::set<int>& examsInThisTimeslot = timeslotExamsMap[timeslot]; 

        // Iterate through students for conflict checking 
        for (std::size_t student = 0; student < studentExams.size(); student++) {
            
            bool taking = false;
            
            // Iterating if the exam is in student's exam list
            for (std::size_t examIndex = 0; examIndex < studentExams[student].size(); examIndex++) {
                if (studentExams[student][examIndex] == currentExam) {
                    taking = true;
                    break; 
                }
            }

            // checking for timeslot conflict
            if (taking) {
                for (std::size_t examIndex = 0; examIndex < studentExams[student].size(); examIndex++) {
                    int exam = studentExams[student][examIndex];

                    // Check if the student has another exam in the same timeslot
                    if (examsInThisTimeslot.find(exam) != examsInThisTimeslot.end()) {
                        validAssignment = false; // Conflict found, break out of the loop
                        break;
                    }
                }
            }
        }

        // assign the current exam to this timeslot if no conflict and assignment is valid
        if (validAssignment) {
            examtimeslotavl.insert(std::make_pair(currentExam, timeslot));
            timeslotExamsMap[timeslot].insert(currentExam);

            // Recursive call
            if (scheduleExams(examtimeslotavl, studentExams, examNumbers, totalTimeslots, currentExamIndex + 1, timeslotExamsMap)) {
                return true; 
            }

            // Backtrack if cant schedule
            examtimeslotavl.remove(currentExam);
            timeslotExamsMap[timeslot].erase(currentExam);
        }
    }

    return false;
}



int main(int argc, char* argv[]) {

    // Checking if input is wrong or if file is of wrong format
    if (argc != 2) {
        std::cerr << "Wrong Input!\n";
        return 1;
    }

    std::ifstream ifile(argv[1]);
    if (!ifile) {
        std::cerr << "File " << argv[1] << " cannot be opened.\n";
        return 1;
    }

    int totalexams, totalstudents, totaltimeslots;
    ifile >> totalexams >> totalstudents >> totaltimeslots;
    std::string line;
    std::getline(ifile, line); // To go to next line

    std::vector<std::vector<int>> studentExams(totalstudents);
    std::set<int> uniqueExams;
    // iterating through students to get the exams and storing the unique exams in a set
    for (int i = 0; i < totalstudents; i++) {
        std::getline(ifile, line);
        std::istringstream ss(line);
        std::string studentName;
        ss >> studentName; 

        int exam;
        while (ss >> exam) {
            studentExams[i].push_back(exam);
            uniqueExams.insert(exam); 
        }
    }

    // Converting to vector as iteration can be easier then
    std::vector<int> examnumbers(uniqueExams.begin(), uniqueExams.end());

    // AVL tree for storing the timeslot assignments
    AVLTree<int, int> examtimeslotavl;
    std::map<int, std::set<int>> timeslotexamsmap;  // Map keeps track of exams scheduled in timeslots
    
    // Calling schedule exams and checking if they are scheduled
    if (scheduleExams(examtimeslotavl, studentExams, examnumbers, totaltimeslots, 0, timeslotexamsmap)) {
        for (BinarySearchTree<int, int>::iterator i = examtimeslotavl.begin(); i != examtimeslotavl.end(); ++i) {
            std::cout << i->first << " " << i->second << std::endl;
        }
    } else {
        std::cout << "No valid solution." << std::endl;
    }

    return 0;
}



