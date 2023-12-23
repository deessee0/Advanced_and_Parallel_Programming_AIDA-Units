import multiprocessing as mp
import time
import os


def f(a, n):
    time.sleep(2)
    print(f"{os.getpid()} mette nell'array il numero {n} in posizione {n}")
    a[n] = n


def main():
    procs = []
    a = mp.Array('i', [0] * 10)
    for i in range(10):
        p = mp.Process(target=f, args=(a, i))
        p.start()
        procs.append(p)
    for p in procs:
        p.join()
    for i in range(10):
        print(f"a[{i}] = {a[i]}")


if __name__ == '__main__':
    main()
