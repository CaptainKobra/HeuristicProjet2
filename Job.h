#ifndef DEF_JOB
#define DEF_JOB

#include <vector>
#include <iostream>

using namespace std;

class Job {
    public:
        int weight;
        int due_date;
        vector<int> time_per_machines;
        Job();
        Job(int number_of_machines);
        Job(vector<int> time_per_machines);
};

#endif