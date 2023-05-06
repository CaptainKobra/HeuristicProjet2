#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Job.h"
#include "Solution.h"
#include "FileReader.h"
#include <chrono>
#include <tuple>

using namespace std;

vector<int> VND_algorithm(string  type, string path, string  RZ_or_random);
vector<int> local_search_algorithm(string path, string neighborhood_type, string first_or_best, string RZ_or_random);
void algorithm_for_full_ls_test(string & csv_path, vector<string> & paths_list, FileReader & fr, 
                                                  string neighborhood_type, string first_or_best, 
                                                  string RZ_or_random, int * best_known_values);

void VND_full_test( string csv_path, vector<string> paths_list, string type, 
                              FileReader fr, string RZ_or_random ,int * best_known_values);

int best_known_50_values[10] = {53112,57403,61981,59625,45295,49014,45340,49659,52175,89492};
int best_known_100_values[10] = {584718,457130,669194,759003,652146,685307,536860,527615,749219,624426};

/**
 * @brief Main function of the program taking in argmuents the name of the file to read
 * and the maximum iteration number 
 *  If the number of iteration is not given it is set by default to 30
 * It also take as arguments the type of neighborhood to use, the type of search 
 * and the type of first solution to generate
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[]) {

     string file_path;
     string neighborhood_type;
     string VND_type;
     string first_or_best;
     string RZ_or_random;
     bool full_test = false;
     bool full_VND = false;
     bool local_search = false;
     bool VND = false;

     string csv_50_path = "./PFSP_instances/50/results50.csv";
     string csv_100_path = "./PFSP_instances/100/results100.csv";
     string csv_50_VND_path = "./PFSP_instances/50/results50_VND.csv";
     string csv_100_VND_path = "./PFSP_instances/100/results100_VND.csv";

     if (argc != 5 && argc != 2 && argc != 3) {
          cout << "Usage for local search: " << argv[0] << " <file_path> <neighborhood_type> <first_or_best> <RZ_or_random>" << endl;
          cout << "Usage for VND: " << argv[0] << "VND <file_path> <VND_type> <RZ_or_random>" << endl;
          return 1;
     } else if (argc == 5) {
          string arg = argv[1];
          if (arg == "VND") {
               VND = true;
               file_path = argv[2];
               VND_type = argv[3];
               RZ_or_random = argv[4];
          } else {
          local_search = true;
          file_path = argv[1];
          neighborhood_type = argv[2];
          first_or_best = argv[3];
          RZ_or_random = argv[4];
          }
     } else if (argc == 2) {
          string arg = argv[1];
          if (arg == "full_ls_test") {
               full_test = true;
          } else if (arg == "full_VND_test") {
               full_VND = true;
          }
     }
          
     if (full_test) {
          //Apply the algorithms on all the files in the repertory 50
          ifstream file("./PFSP_instances/50/paths50.txt");
          string file_path;
          FileReader fr;
          //reset the csv files
          ofstream csv_50_file(csv_50_path);
          csv_50_file << "score,time,best" << endl;
          csv_50_file.close();
          ofstream csv_100_file(csv_100_path);
          csv_100_file << "score,time,best" << endl;
          csv_100_file.close();
          vector<string> paths_list;

          while (file >> file_path) {
               paths_list.push_back(file_path);
          }
          algorithm_for_full_ls_test(csv_50_path, paths_list, fr, "transpose", "first", "RZ",best_known_50_values);
          algorithm_for_full_ls_test(csv_50_path, paths_list, fr, "transpose", "first", "random",best_known_50_values);
          algorithm_for_full_ls_test(csv_50_path, paths_list, fr, "transpose", "best", "RZ",best_known_50_values);
          algorithm_for_full_ls_test(csv_50_path, paths_list, fr, "transpose", "best", "random",best_known_50_values);
          algorithm_for_full_ls_test(csv_50_path, paths_list, fr, "exchange", "first", "RZ",best_known_50_values);
          algorithm_for_full_ls_test(csv_50_path, paths_list, fr, "exchange", "first", "random",best_known_50_values);
          algorithm_for_full_ls_test(csv_50_path, paths_list, fr, "exchange", "best", "RZ",best_known_50_values);
          algorithm_for_full_ls_test(csv_50_path, paths_list, fr, "exchange", "best", "random",best_known_50_values);
          algorithm_for_full_ls_test(csv_50_path, paths_list, fr, "insert", "first", "RZ",best_known_50_values);
          algorithm_for_full_ls_test(csv_50_path, paths_list, fr, "insert", "first", "random",best_known_50_values);
          algorithm_for_full_ls_test(csv_50_path, paths_list, fr, "insert", "best", "RZ",best_known_50_values);
          algorithm_for_full_ls_test(csv_50_path, paths_list, fr, "insert", "best", "random",best_known_50_values);
          paths_list.clear();
          file.close();
          //Apply the algorithms on all the files in the repertory 100
          ifstream file2("./PFSP_instances/100/paths100.txt");
          while (file2 >> file_path) {
               paths_list.push_back(file_path);
          }
          algorithm_for_full_ls_test(csv_100_path, paths_list, fr, "transpose", "first", "RZ",best_known_100_values);
          algorithm_for_full_ls_test(csv_100_path, paths_list, fr, "transpose", "first", "random",best_known_100_values);
          algorithm_for_full_ls_test(csv_100_path, paths_list, fr, "transpose", "best", "RZ",best_known_100_values);
          algorithm_for_full_ls_test(csv_100_path, paths_list, fr, "transpose", "best", "random",best_known_100_values);
          algorithm_for_full_ls_test(csv_100_path, paths_list, fr, "exchange", "first", "RZ",best_known_100_values);
          algorithm_for_full_ls_test(csv_100_path, paths_list, fr, "exchange", "first", "random",best_known_100_values);
          algorithm_for_full_ls_test(csv_100_path, paths_list, fr, "exchange", "best", "RZ",best_known_100_values);
          algorithm_for_full_ls_test(csv_100_path, paths_list, fr, "exchange", "best", "random",best_known_100_values);
          algorithm_for_full_ls_test(csv_100_path, paths_list, fr, "insert", "first", "RZ",best_known_100_values);
          algorithm_for_full_ls_test(csv_100_path, paths_list, fr, "insert", "first", "random",best_known_100_values);
          algorithm_for_full_ls_test(csv_100_path, paths_list, fr, "insert", "best", "RZ",best_known_100_values);
          algorithm_for_full_ls_test(csv_100_path, paths_list, fr, "insert", "best", "random",best_known_100_values);

     } else if (local_search) {
          vector<int> results = local_search_algorithm(file_path, neighborhood_type, first_or_best, RZ_or_random);
          cout << "score: " << results[0] << endl;
          cout << "time: " << results[1] << endl;
     } else if (VND) {
          vector<int> results = VND_algorithm(VND_type, file_path, RZ_or_random);
          cout << "score: " << results[0] << endl;
          cout << "time: " << results[1] << endl;
     } else if (full_VND) {
          //Apply the algorithms on all the files in the repertory 50
          ifstream file("./PFSP_instances/50/paths50.txt");
          string file_path;
          FileReader fr;
          //reset the csv files
          ofstream csv_50_file(csv_50_VND_path);
          csv_50_file << "score,time,best" << endl;
          csv_50_file.close();
          ofstream csv_100_file(csv_100_VND_path);
          csv_100_file << "score,time,best" << endl;
          csv_100_file.close();
          vector<string> paths_list;

          while (file >> file_path) {
               paths_list.push_back(file_path);
          }
          VND_full_test(csv_50_VND_path, paths_list, "tei", fr, "RZ",best_known_50_values);
          VND_full_test(csv_50_VND_path, paths_list, "tei", fr, "random",best_known_50_values);
          VND_full_test(csv_50_VND_path, paths_list, "tie", fr, "RZ",best_known_50_values);
          VND_full_test(csv_50_VND_path, paths_list, "tie", fr, "random",best_known_50_values);

          paths_list.clear();
          file.close();
          //Apply the algorithms on all the files in the repertory 100
          ifstream file2("./PFSP_instances/100/paths100.txt");
          while (file2 >> file_path) {
               paths_list.push_back(file_path);
          }
          VND_full_test(csv_100_VND_path, paths_list, "tei", fr, "RZ",best_known_100_values);
          VND_full_test(csv_100_VND_path, paths_list, "tei", fr, "random",best_known_100_values);
          VND_full_test(csv_100_VND_path, paths_list, "tie", fr, "RZ",best_known_100_values);
          VND_full_test(csv_100_VND_path, paths_list, "tie", fr, "random",best_known_100_values);
          file.close();
     }    
     return 0;
}

/**
 * @brief      Test 5 times a VND algorithm for all the files in the repertory
 * @param      csv_path      The csv path
 * @param      paths_list    The paths list
 * @param      type          The type
 * @param      fr            The file reader
 * @param      RZ_or_random  The rz or random
 * @param      best_known_values  The best known values
*/
void VND_full_test( string csv_path, vector<string> paths_list, string type, FileReader fr, string RZ_or_random ,int * best_known_values) {
     for (unsigned int i = 0; i < paths_list.size(); i++) {
          string path = paths_list[i];
          int best_known_value = *(best_known_values + i);
          vector<int> results = VND_algorithm(type , path, RZ_or_random);
          results.push_back(best_known_value);
          fr.write_csv(csv_path, results);
     }
}

/**
 * @brief      Test 5 times a local search algorithm for all the files in the repertory
 * @param      csv_path           The csv path
 * @param      paths_list         The paths list
 * @param      fr                 The file reader
 * @param      neighborhood_type  The neighborhood type
 * @param      first_or_best      The first or best
 * @param      RZ_or_random       The rz or random
 * @param      best_known_values  The best known values
 * 
*/
void algorithm_for_full_ls_test(string & csv_path, vector<string> & paths_list, FileReader & fr,
                                                  string neighborhood_type, string first_or_best, 
                                                  string RZ_or_random, int * best_known_values) {
     for (unsigned int i = 0; i < paths_list.size(); i++) {
          string path = paths_list[i];
          int best_known_value = *(best_known_values + i);

          for (size_t j = 0; j < 5; j++) {
               vector<int> results = local_search_algorithm(path, neighborhood_type, first_or_best, RZ_or_random);
               results.push_back(best_known_value);
               fr.write_csv(csv_path, results);
          }  
     }
}

/**
 * @brief      Perform a local search algorithm for a given file and neighborhood type and pivoting rule
 * @param      path               The path to the file
 * @param      neighborhood_type  The neighborhood type
 * @param      first_or_best      The first or best
 * @param      RZ_or_random       rz or random permutation
 * @return     The score and the time
*/
vector<int> local_search_algorithm(string path, string neighborhood_type, string first_or_best, string RZ_or_random) {

     FileReader fr;
     vector<Job*> jobs_list;
     vector<Job*> * jobs = &jobs_list;
     fr.read_file(path, jobs_list);
     Solution s1 = Solution(jobs);
     
     auto start = chrono::high_resolution_clock::now();

     if (RZ_or_random == "RZ") {
          s1.generate_simplified_RZ_permutation();
     } else if (RZ_or_random == "random") {
          s1.generate_random_uniform_permutation();
     }
     
     s1.generate_solution_value();
     int solution_value = s1.solution_value + 1;

     while (solution_value != s1.solution_value) {
          solution_value = s1.solution_value;
          if (first_or_best == "first") {
               s1 = s1.find_best_first_solution(neighborhood_type, s1);
          } else if (first_or_best == "best") {
               s1 = s1.find_best_solution_in_neighborhood(neighborhood_type, s1);
          } else {
               cout << "Wrong argument for first_or_best, must be first or best" << endl;
               break;
          }
     }
     auto stop = chrono::high_resolution_clock::now();
     auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
     int time_microseconds = duration.count();
     vector<int> results = {solution_value, time_microseconds};

     return  results;
}

/**
 * @brief      Perform a VND algorithm for a given file and neighborhood ordering
 * @param      type               The type of neighborhood ordering
 * @param      path               The path to the file
 * @param      RZ_or_random       rz or random starting permutation
 * @return     The score and the time
*/
vector<int> VND_algorithm(string  type, string path, string  RZ_or_random) {

     FileReader fr;
     vector<Job*> jobs_list;
     vector<Job*> * jobs = &jobs_list;
     fr.read_file(path, jobs_list);
     Solution s1 = Solution(jobs);
     string transpose = "transpose";
     string exchange = "exchange";
     string insert = "insert";
     vector<string> combo = {"","",""};

     if (type == "tei") {
          combo = {transpose, exchange, insert};
     } else if (type == "tie") {
          combo = {transpose, insert, exchange};
     } else {
          cout << "Wrong argument for type, must be tei or tie for VND" << endl;
     }

     auto start = chrono::high_resolution_clock::now();

     if (RZ_or_random == "RZ") {
          s1.generate_simplified_RZ_permutation();
     } else if (RZ_or_random == "random") {
          s1.generate_random_uniform_permutation();
     }
     s1.generate_solution_value();
     int initial_solution_value;
     do {
          initial_solution_value = s1.solution_value ;
          s1 = s1.find_best_first_solution(combo[0], s1);
          if (s1.solution_value == initial_solution_value) {
               s1 = s1.find_best_first_solution(combo[1], s1);
               if (s1.solution_value == initial_solution_value) {
                    s1 = s1.find_best_first_solution(combo[2],s1);
               }
          }
     } while (initial_solution_value != s1.solution_value);

     auto stop = chrono::high_resolution_clock::now();
     auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
     int time_microseconds = duration.count();
     int solution_value = s1.solution_value;
     vector<int> results = {solution_value,time_microseconds};
     return results;
}




  
