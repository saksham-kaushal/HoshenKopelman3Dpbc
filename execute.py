import subprocess
import os
import numpy as np
import json


'''
Parse parameters from parameters header file.
'''

PARAMETER_FILE = './parameters.h'
parameters=dict()
with open(PARAMETER_FILE,'r') as param_file:
	for line in param_file:
		tokens=line.replace('"','').split()
		#print(tokens)
		if len(tokens)==3 and tokens[0]=='#define':
			parameters[tokens[1]]=tokens[2]



'''
Execute command "cat cluster_data_filename | hk3d_pbc" for each cluster_data file.
'''

files_list=os.listdir(parameters['F_DATA_DIR'])
for filename in files_list:
	cat_ps = subprocess.Popen(('cat',parameters['F_DATA_DIR']+filename), stdout=subprocess.PIPE)
	hk_ps = subprocess.Popen(('./hk3d_pbc'), stdin=cat_ps.stdout, stdout=open(parameters['OUT_DIR']+'cluster_'+filename,'w'))



'''
Combine oppositely oriented clusters to form complete lattice with non-sequential cluster numbers.
Get a total count of clusters in the lattice for each configuration.
Get size of each cluster and save these statistics.
'''

for i in range(int(parameters['CONFIGS'])):
	cd1_count = np.loadtxt(parameters['OUT_DIR']+'cluster_data_'+str(i)+'_1.txt',dtype=int,max_rows=1)
	cd1_lattice = np.genfromtxt(parameters['OUT_DIR']+'cluster_data_'+str(i)+'_1.txt',dtype=int,skip_header=1)
	cd2_count = np.loadtxt(parameters['OUT_DIR']+'cluster_data_'+str(i)+'_2.txt',dtype=int,max_rows=1)
	cd2_lattice = np.genfromtxt(parameters['OUT_DIR']+'cluster_data_'+str(i)+'_2.txt',dtype=int,skip_header=1)
	#Start cluster number in second file in continuation with first file.
	cd2_lattice[cd2_lattice!=0] += cd1_count

	total_count = cd1_count+cd2_count
	lattice = np.add(cd1_lattice,cd2_lattice)

	value,counts = np.unique(lattice,return_counts=True)
	stats_dict = dict(zip(value,counts))
	sorted_stats_dict = {k: v for k, v in sorted(stats_dict.items(), key=lambda item: item[1])}
	cluster_lattice_fname = parameters['CLUSTER_LATTICE_DIR']+'cluster_'+str(i)+'.txt'
	np.savetxt(cluster_lattice_fname,lattice,fmt='%5i')

	cluster_stats_fname = parameters['CLUSTER_STATS_DIR']+'cluster_stats_'+str(i)+'.txt'
	with open(cluster_stats_fname,'w') as stats_file:
		stats_file.write('Number of clusters = %d\n' %(total_count))
		for entry in sorted_stats_dict:
			stats_file.write(str(entry)+' : '+str(sorted_stats_dict[entry])+'\n')


