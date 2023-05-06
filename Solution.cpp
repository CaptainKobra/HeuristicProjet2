#include "Solution.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

/**
 * @brief Construct a new Solution:: Solution object
*/
Solution :: Solution() {
    jobs = NULL;
    planning = vector<vector<int>>(jobs_indices.size(), vector<int>((*jobs)[0]->time_per_machines.size(),0));
}

/**
 * @brief Construct a new Solution by taking a pointer to a vector of jobs as a parameter
 * 
 * @param jobs pointer to a vector of jobs
 * @return Solution 
 */
Solution :: Solution(vector<Job*> * jobs) {
    this->jobs = jobs;
    this->jobs_indices = vector<int>(jobs->size(),0);
    this->jobs_tardiness = vector<int>(jobs->size(),0);
    for (unsigned int i = 0; i < jobs_indices.size(); i++) {
        jobs_indices[i] = i;
    }
    planning = vector<vector<int>>(jobs_indices.size(), vector<int>((*jobs)[0]->time_per_machines.size(),0));
}

/**
 * @brief Generate the solution value by generating 
 * the planning and then calculating the solution value
 */
void Solution :: generate_solution_value() {
    generate_planning();
    solution_value = 0;
    for (unsigned int i = 0; i < jobs_indices.size(); i++) {
        solution_value += jobs_tardiness[i] * (*jobs)[jobs_indices[i]]->weight;
    }
}

/**
 * @brief 
 * 
 */
void Solution :: generate_wtc() {
    generate_planning();
    wtc = 0;
    int number_of_machines = (*jobs)[0]->time_per_machines.size();
    for (unsigned int i = 0; i < planning.size(); i++) {
        wtc += planning[i][number_of_machines] * (*jobs)[jobs_indices[i]]->weight;
    }
}

/**
 * @brief  Create a solution step by step by adding jobs indices in the list
 * one by one at the best position possible
 * 
 */
void Solution :: generate_simplified_RZ_permutation() {
    unsigned int number_of_jobs = jobs->size();
    jobs_indices = vector<int>(1,0);
    for (unsigned int i = 1; i < number_of_jobs; i++) {
        int best_position = 0;
        vector<int> actual_jobs_indices = jobs_indices;
        jobs_indices = RZ_insert(0,actual_jobs_indices,i);
        generate_wtc();
        int best_value = wtc;

        for (unsigned int j = 1; j <= jobs_indices.size(); j++) {
            jobs_indices = RZ_insert(j, actual_jobs_indices, i);
            generate_wtc();
            if (wtc < best_value) {
                best_value = wtc;
                best_position = j;
            } else if(wtc == best_value)  {
                if (rand() % 2 == 0) {
                    best_value = wtc;
                    best_position = j;
                }
            }
            jobs_indices = actual_jobs_indices;
        }
        jobs_indices = RZ_insert(best_position, actual_jobs_indices, i);
    }
}

/**
 * @brief insert a job at a given index in the jobs_indices vector
 * 
 */
vector<int> Solution :: RZ_insert(int index, vector<int> jobs_indices,int value_to_insert) {
    jobs_indices.insert(jobs_indices.begin() + index, value_to_insert);
    return jobs_indices;
}

/**
 * @brief Generate a random uniform permutation of the jobs indices
 * 
 */
void Solution :: generate_random_uniform_permutation() {
    random_device rd;
    mt19937 g(rd());
    shuffle(jobs_indices.begin(), jobs_indices.end(), g);
}

/**
 * @brief Reset the planning matrix and the jobs tardiness vector
 */
void Solution :: reset_plannig() {
    planning = vector<vector<int>>(jobs_indices.size(), vector<int>((*jobs)[0]->time_per_machines.size(),0));
    jobs_tardiness = vector<int>(jobs_indices.size(),0);
}

/**
 * @brief Generate the planning matrix
 */
void Solution :: generate_planning() {
    reset_plannig();
    int number_of_jobs = jobs_indices.size();
    int number_of_machines = (*jobs)[0]->time_per_machines.size();
    //Fill the first column of the planning matrix
    for (int j = 0; j < number_of_machines; j++) {
        planning[0][j] = (*jobs)[jobs_indices[0]]->time_per_machines[j] + planning[0][j - 1];
    }
    jobs_tardiness[0] = max(0,planning[0][number_of_machines - 1] - (*jobs)[jobs_indices[0]]->due_date);
    
    //Fill the rest of the planning matrix
    for (int i = 1; i < number_of_jobs; i++) {
        for (int j = 0; j < number_of_machines; j++) {   
            if (planning[i -1][j] > jobs_tardiness[i]) {
                planning[i][j] = planning[i - 1][j] + (*jobs)[jobs_indices[i]]->time_per_machines[j];
            } else {
                planning[i][j] = jobs_tardiness[i] + (*jobs)[jobs_indices[i]]->time_per_machines[j];
            }
            jobs_tardiness[i] = planning[i][j];
        }
        jobs_tardiness[i] = max(0,planning[i][number_of_machines - 1] - (*jobs)[jobs_indices[i]]->due_date);
    }
}


/**
 * @brief Createt a new solution by transposing two jobs int the jobs_indices vector
 * 
 * @param i Index of the first job to transpose with his right neighbor
 * @param solution  Solution to transpose
 * @return Solution 
 */
Solution Solution :: transpose(int i, Solution & solution) {
    Solution s = Solution(solution);
    s.jobs_indices = solution.jobs_indices;
    swap(s.jobs_indices[i],s.jobs_indices[i+1]);
    return s;
}


/**
 * @brief Createt a new solution by inserting a job at a given index
 * 
 * @param i Index of the job to insert
 * @param j Index of the position where to insert the job
 * @param solution Solution to insert the job in
 * @return Solution 
 */
Solution Solution :: insert(int i, int j, Solution & solution) {
    Solution s = Solution(solution);
    if (i != j) {
        s.jobs_indices.insert(s.jobs_indices.begin() + j, s.jobs_indices[i]);
        if (i < j) {
            s.jobs_indices.erase(s.jobs_indices.begin() + i);
        } else if (i > j) {
            s.jobs_indices.erase(s.jobs_indices.begin() + i + 1);
        } 
    }
    return s;
}

/**
 * @brief Createt a new solution by exchanging two jobs in the jobs_indices vector
 * 
 * @param i Index of the first job to exchange
 * @param j Index of the second job to exchange
 * @param solution Solution to exchange the jobs in
 * @return Solution 
 */
Solution Solution :: exchange(int i, int j, Solution & solution) {
    Solution s = Solution(solution);
    s.jobs_indices = solution.jobs_indices;
    int buffer = s.jobs_indices[i];
    s.jobs_indices[i] = s.jobs_indices[j];
    s.jobs_indices[j] = buffer;
    return s;
}


/**
 * @brief Find the best first solution by using a neighborhood
 * 
 * @param neighborhood_type  Define the neighborhood type to use : transpose, insert or exchange
 * @param best_solution Actual best solution
 * @return Best first solution 
 */
Solution Solution :: find_best_first_solution(string & neighborhood_type, Solution & best_solution) {
    unsigned int number_of_jobs = jobs_indices.size();
    if (neighborhood_type == "transpose") {
        for (unsigned int i = 0; i < number_of_jobs - 1; i++) {
            Solution s = transpose(i,best_solution);
            s.generate_solution_value();
            if (s.solution_value < best_solution.solution_value) {
                best_solution = s;
                break;
            }
        }
    } else if (neighborhood_type == "insert") {
        for (unsigned int i = 0; i < number_of_jobs; i++) {
            for (unsigned int j = 0; j < number_of_jobs; j++) {
                Solution s = insert(i,j,best_solution);
                s.generate_solution_value();
                if (s.solution_value < best_solution.solution_value) {
                    best_solution = s;
                    break;
                }
            }
        }
    } else if (neighborhood_type == "exchange") {
        for (unsigned int i = 0; i < number_of_jobs; i++) {
            for (unsigned int j = 0; j < number_of_jobs - i; j++) {
                Solution s = exchange(i,j,best_solution);
                s.generate_solution_value();
                if (s.solution_value < solution_value) {
                    best_solution = s;
                    break;
                }
            }
        }
    } else {
        cout << "Error: neighborhood type not found" << endl;
    }
    return best_solution;
}


/**
 * @brief Find the best solution in the neighborhood of the current solution
 * 
 * @param neighborhood_type Define the neighborhood to explore: transpose, insert or exchange
 * @param best_solution Actual best solution
 * @return Best Solution int the neighborhood
 */
Solution Solution :: find_best_solution_in_neighborhood(string & neighborhood_type, Solution & best_solution) {
    unsigned int number_of_jobs = jobs_indices.size();
    if (neighborhood_type == "transpose") {
        for (unsigned int i = 0; i < number_of_jobs - 1; i++) {
            Solution s = transpose(i, best_solution);
            s.generate_solution_value();
            if (s.solution_value < best_solution.solution_value) {
                best_solution = s;
            }
        }
    } else if (neighborhood_type == "insert") {
        for (unsigned int i = 0; i < number_of_jobs; i++) {
            for (unsigned int j = 0; j < number_of_jobs; j++) {
                Solution s = insert(i,j,best_solution);
                s.generate_solution_value();
                if (s.solution_value < best_solution.solution_value) {
                    best_solution = s;
                }
            }
        }
    } else if (neighborhood_type == "exchange") {
        for (unsigned int i = 0; i < number_of_jobs; i++) {
            for (unsigned int j = 0; j < number_of_jobs - i; j++) {
                Solution s = exchange(i,j,best_solution);
                s.generate_solution_value();
                if (s.solution_value < best_solution.solution_value) {
                    best_solution = s;
                }
            }
        }
    } else {
        cout << "Error: neighborhood type not found" << endl;
    }
    return best_solution;
}

