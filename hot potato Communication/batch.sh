#!/bin/bash
#SBATCH -n 16                 # requested MPI tasks
#SBATCH -p normal            # requested queue
#SBATCH -t 1                 # maximum runtime in minutes

ibrun ./ring.exe
