#!/bin/bash
#SBATCH -n 16                 # requested MPI tasks
#SBATCH -p normal          # requested queue
#SBATCH -t 1000
ibrun ./new.exe 128
