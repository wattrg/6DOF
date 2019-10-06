# 6DOF
Purpose: Source code for PHYS3990 boomerang capstone project
Author: Robert Watt
Date: 6/9/2019

## Dependancies
The only external dependancy required for full functionality is Python (3.7 works, earlier versions may work).

## Compilation
To compile on Linux, 
  1. clone the repo using "git clone https://github.com/wattrg/6DOF.git".
  2. In "Exec", execute "make.sh". An executable named "sixDOF.ex" should be produced.
To compile on Windows or Mac, consult your C++ compiler's documentation. All the files required for compilation are otulined in "make.sh" described above.

  
## Execution
Within "Exec" there is a folder for each test case, currently 6DOF, Boomerang, and Projectile. Within each folder is a lua configuration file and a bash script. The bash script calls the executable with the lua script as an input. The lua script must be the first argument in calling the executable.

Upon execution, a "trajectory.csv" file will be created in the folder of execution. A python script will then plot the data in this csv file, and save the results in "../../../Final_Report/img/(6DOF or boomerang or projectile) depending on which case is being run. Make sure these folders exist (Note that Final_Report is a folder on the same level as the repo, and is external to the repo).

## Trouble shooting
