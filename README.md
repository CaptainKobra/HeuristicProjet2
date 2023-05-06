# PFSP Heuristic Project 1

## How to compile
Just use the makefile by typing make in a terminal opened in the repertory where the makefile is located

## How to run

You can execute the program in the terminal by typing ./PFSD in the terminal after compiling

If you don't add any parameter an help message will be printed

Usage : 

    To apply a local search algorithm -> <file_path> <neighborhood_type> <first_or_best> <RZ_or_random>
    To apply a VND algorithm -> VND <file_path> <VND_type> <RZ_or_random>

    !! You don't have to type the followings commands, it will change the data I used for my statisticals tests and take a long time to run !!
    To generate data for the statisticals tests -> ./PFSP full_ls_test
                                                                        -> /PFSP full_VND_test

# The statistic part
You can simply type in the terminal : Rscript ./Statistics.r
It will print the results
