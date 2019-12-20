#include "PriorityQueue.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

void addFiles(std::string filename, PriorityQueue &p_queue);
void addPatient(PriorityQueue &p_queue);
void showNext(PriorityQueue &p_queue);
void admitNext(PriorityQueue &p_queue, int &t_count);
void proccessQueue(PriorityQueue &p_queue);
int main(int argc, char *argv[]) {
    
    // keeps track of total time treating patients
    int t_count = 0;

    int q_size = std::stoi(argv[1]);
    PriorityQueue p_queue(q_size);

    bool quit_flag = false;
    while(!quit_flag) {
        int choice;
        std::cout << "======Main Menu======" << std::endl;
        std::cout << "1. Get Patient Information from File" << std::endl;
        std::cout << "2. Add Patient to Priority Queue" << std::endl;
        std::cout << "3. Show Next Patient" << std::endl;
        std::cout << "4. Admit Next Patient" << std::endl;
        std::cout << "5. Process Entire Queue" << std::endl;
        std::cout << "6. Quit" << std::endl;

        std::cin >> choice;

        if(choice == 1) {
            addFiles(argv[2], p_queue);
        }
        else if(choice == 2) {
            addPatient(p_queue);
        }
        else if(choice == 3) {
            showNext(p_queue);
        }
        else if(choice == 4) {
            admitNext(p_queue, t_count);
        }
        else if(choice == 5) {
            proccessQueue(p_queue);
        }
        else if(choice == 6) {
            std::cout << "Goodbye!" << std::endl;
            quit_flag = true;
        }
        std::cin.ignore();
    }
    return 0;
}

void addFiles(std::string filename, PriorityQueue &p_queue) {
    std::ifstream file;
    file.open(filename);
    if(file.is_open()) {
        std::string line;
        while(getline(file, line)) {
            if(!p_queue.isFull()) {
                std::stringstream ss(line);
                std::string inner_line;

                int item = 0;
                std::string name;
                int injurySeverity;
                int treatmentTime;
                while(getline(ss, inner_line,' ')) {
                    if(item == 0) {
                        name = inner_line;
                    }
                    else if(item == 1) {
                        injurySeverity = stoi(inner_line);
                    }
                    else if(item == 2) {
                        treatmentTime = stoi(inner_line);
                    }
                    item++;
                }
                p_queue.enqueue(name,injurySeverity,treatmentTime);
            }
            else {
                std::cout << "Priority Queue full. Send Patient to another hospital." << std::endl;
                file.close();
                return ;
            }
        }
    }
    file.close();
}

void addPatient(PriorityQueue &p_queue) {
    if(p_queue.isFull()) {
        std::cout << "Priority Queue full. Send Patient to another hospital." << std::endl;
        return ;
    }
    else {
        std::string name;
        int injurySeverity;
        int treatmentTime;

        std::cout << "Enter Patient Name:" << std::endl;
        std::cin >> name;
        std::cout << "Enter Injury Severity:" << std::endl;
        std::cin >> injurySeverity;
        std::cout << "Enter Treatment Time:" << std::endl;
        std::cin >> treatmentTime;

        p_queue.enqueue(name,injurySeverity,treatmentTime);
    }
}

void showNext(PriorityQueue &p_queue) {
    if(p_queue.isEmpty()) {
        std::cout << "Queue empty." << std::endl;
        return ;
    }
    else {
        std::cout << "Patient Name: " << p_queue.peekName() << std::endl;
        std::cout << "Injury Severity: " << p_queue.peekInjurySeverity() << std::endl;
        std::cout << "Treatment Time: " << p_queue.peekTreatmentTime() << std::endl;
    }
}

void admitNext(PriorityQueue &p_queue, int &t_count) {
    if(p_queue.isEmpty()) {
        std::cout << "Queue empty." << std::endl;
        return ;
    }
    else {
        t_count += p_queue.peekTreatmentTime();
        std::cout << "Patient Name: " << p_queue.peekName() << " - Total Time Treating Patients: " << t_count << std::endl;
        p_queue.dequeue();
    }
}

void proccessQueue(PriorityQueue &p_queue) {
    if(p_queue.isEmpty()) {
        std::cout << "Queue empty." << std::endl;
        return ;
    }
    else {
        while(!p_queue.isEmpty()) {
            std::cout << "Name: " << p_queue.peekName() << " - Total Wait Time: " << p_queue.peekTreatmentTime() << std::endl;
            p_queue.dequeue();
        }
    }
}