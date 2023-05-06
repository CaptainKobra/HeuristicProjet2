#ifndef DEF_SOLUTION
#define DEF_SOLUTION

#include <iostream>
#include <vector>
#include <string>
#include "Job.h"

using namespace std;

class Solution {

    public:
        Solution();
        Solution(vector<Job*> * jobs);
    

        int solution_value;
        int wtc;
        int tardiness;
        vector<int> jobs_indices;
        vector<int> jobs_tardiness;
        vector<Job*> * jobs;
        vector<vector<int>> planning;

        void print_jobs();

        void print_jobs_tardiness();

        void reset_plannig();

        void generate_planning();

        void generate_solution_value();

        void generate_wtc();

        void generate_simplified_RZ_permutation();

        void generate_random_uniform_permutation();

        void print_time_per_machines();

        void print_planning();

        void print_jobs_indices();

        vector<int> RZ_insert(int index, vector<int> jobs_indices,int value_to_insert);

        //The tree types of neighborhood movements
        Solution transpose(int i, Solution & solution);

        Solution insert(int i, int j, Solution & solution);


        Solution exchange(int i, int j, Solution & solution);

        Solution find_best_first_solution(string & neighborhood_type, Solution & best_solution);

        Solution find_best_solution_in_neighborhood(string & neighborhood_type, Solution & best_solution);

        vector<Solution> neighborhood;
};

#endif