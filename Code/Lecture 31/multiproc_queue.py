import multiprocessing as mp
import time
import os


def f(q, n):
    time.sleep(2)
    print(f"{os.getpid()} mette in coda il numero {n}")
    q.put(n)


def main():
    procs = []
    q = mp.Queue()
    for i in range(10):
        p = mp.Process(target=f, args=(q, i))
        p.start()
        procs.append(p)
    for i in range(10):
        n = q.get()
        print(f"ricevuto {n}")
    for p in procs:
        p.join()


if __name__ == '__main__':
    main()
