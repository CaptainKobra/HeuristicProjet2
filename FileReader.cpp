#include "FileReader.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Job.h"

using namespace std;

FileReader::FileReader() {
}

/**
 * @brief Read the file and fill the jobs_list vector
 * 
 * @param file_name path to the file
 * @param jobs_list the list of jobs to fill
 */
void FileReader :: read_file(string & file_name, vector<Job*> & jobs_list) {

    ifstream file(file_name);
    string word;
    int number_of_jobs;
    int number_of_machines;
    file >> word;
    number_of_jobs = stoi(word);
    file >> word;
    number_of_machines = stoi(word);

    //Initialise the jobs_list vector
    jobs_list = vector<Job*>(number_of_jobs);
    for (int i = 0; i < number_of_jobs; i++) {
        jobs_list[i] = new Job(number_of_machines);
    }
    //Fill the time_per_machines vector of each job
    for (int i = 0; i < number_of_jobs; i ++) {
        for (int j = 0; j < number_of_machines; j++) {   
            file >> word;//Skip job number
            file >> word;
            jobs_list[i]->time_per_machines[j] = stoi(word);
        }      
    }
    //Skip the reldue standholder
    file >> word;
    //Read the due dates and weights of each job
    for (int i = 0; i < number_of_jobs; i++) {
        file >> word; //Skip -1 placeholder
        file >> word;
        jobs_list[i]->due_date = stoi(word);
        file >> word; //Skip -1 placeholder
        file >> word;
        jobs_list[i]->weight = stoi(word);
    }
    file.close();
}

/**
 * @brief Write the results in a csv file and add the best value at the end
*/
void FileReader :: write_csv(string & file_name, vector<int> results) {
    ofstream file(file_name, ios::out | ios::app);
    file << results[0] << "," << results[1] << "," << results[2] << endl;
    file.close();
}



