import multiprocessing as mp
import time
import os


def f(n):
    time.sleep(2)
    print(f"{os.getpid()} ha ricevuto il valore numero {n}")


def main():
    p = mp.Pool(processes=4)
    p.map(f, range(10))


if __name__ == '__main__':
    main()
