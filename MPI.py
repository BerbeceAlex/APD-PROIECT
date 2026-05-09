from mpi4py import MPI
import numpy as np
import time
from numba import njit


@njit(fastmath=True)
def compute_local_dist(points, start_i, end_i):
    n = len(points)
    s_control = 0.0
    for i in range(start_i, end_i):
        for j in range(i + 1, n):
            d = ((points[i,0]-points[j,0])**2 + 
                 (points[i,1]-points[j,1])**2 + 
                 (points[i,2]-points[j,2])**2)**0.5
            s_control += d
    return s_control

def main():
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()
    
    n_points = 100000
    points = None

    if rank == 0:
        # Generăm sau citim datele
       
        points = np.random.rand(n_points, 3).astype(np.float64)
        print(f"[{rank}] Start calcul pentru {n_points} puncte cu {size} procese...")

    # Trimitem toate punctele la toți (Bcast)
    points = comm.bcast(points, root=0)
    
    # Împărțim sarcina
    rows_per_proc = n_points // size
    start_i = rank * rows_per_proc
    end_i = (rank + 1) * rows_per_proc if rank != size - 1 else n_points

    # Sincronizam inainte de cronometrare
    comm.Barrier()
    t_start = time.time()

  
    local_sum = compute_local_dist(points, start_i, end_i)

    # Adunam rezultatele
    total_sum = comm.reduce(local_sum, op=MPI.SUM, root=0)
    
    comm.Barrier()
    t_end = time.time()

    if rank == 0:
        print("\n" + "="*40)
        print(f"Timp de calcul: {t_end - t_start:.4f} secunde")
        print(f"Suma control: {int(total_sum)}")
        print("="*40)

if __name__ == "__main__":
    main()