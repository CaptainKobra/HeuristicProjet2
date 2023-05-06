#include "Job.h"

Job :: Job() {
    time_per_machines = vector<int>(0);
}

Job :: Job(vector<int> time_per_machines) {
    this->time_per_machines = time_per_machines;
}

Job :: Job(int number_of_machines) {
    this->time_per_machines = vector<int>(number_of_machines,0);
}