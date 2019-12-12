# HoshenKopelman3Dpbc
Implementation of Hoshen Kopelman Clustering Algorithm for 3 dimensional lattices with periodic boundary conditions. 

Adapted from Tobin Fricke's implementation of the Hoshen-Kopelman algorithm for cluster labeling.
Copyright (c) September 9, 2000, by Tobin Fricke <tobin@splorg.org>
Distributed under the terms of the GNU Public License.
Modified 2002-03-09 Tobin Fricke
Modified substantially 2004-04-21 by Tobin Fricke

*http://www.ocf.berkeley.edu/~fricke/projects/hoshenkopelman/hoshenkopelman.html__*


## INSTRUCTIONS TO EXECUTE :

1. Set variables in parameters.h header file, especially system sizes, number of configurations, and source file location.
2. Compile and execute the required data_format program to get lattice site occupancies in required format. Outputs are stored in F_DATA_DIR directory. Commands to compile and execute the program are mentioned in the topmost docstring of the C code.
3. Compile the hk3d_pbc.c C program. Do not execute it explicitly. It will be executed indirectly via the python script.
4. Run execute.py Python3 script. Number and size of clusters for different configs can be obtained from CLUSTER_STATS_DIR directory. The exact lattice with cluster labels for each configuration can be obtained from CLUSTER_LATTICE_DIR.


## DIRECTORY STRUCTURE :

* ___parameters.h___ header file contains all global parameters definitions.

* ___execute.py___ Python3 script executes HK algorithm and generates all required information about clusters.

* ___hk3d_pbc.c___ C program file contains implementation of HK algorithm for 3D lattices with pbc. This programs needs to be compiled separately with compilation instructions at the top of the file; however, it is executed automatically via execute.py script, and does not need to be executed separately.

* ___data_format.c___ and likewise named files are used to change the values of lattice occupancies to required format.

* ___INFILE file___ contains the raw(unformatted) input spin values for all configurations.

* ___F_DATA_DIR___ directory contains formatted data obtained by executing data_format.c which requires INFILE for initial data. Files are separate for different configurations.

* ___OUT_DIR___ directory contains temporary cluster information required to compute clusters and their sizes.

* ___CLUSTER_STATS_DIR___ directory contains a file for each configuration mentioning total number of clusters and size of each cluster sorted in decreasing order.

* ___CLUSTER_LATTICE_DIR___ directory has a file for each configuration containing lattice occupation sites replaced with their corresponding cluster numbers.
