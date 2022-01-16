import concurrent.futures
import threading
import time


def factorial(x):
    if x == 0 or x == 1:
        return 1
    result = 1
    for i in range(x, 1, -1):
        result *= i
    time.sleep(0.25)
    print(f"Factorial of {x:-5} is {result}")


def do_queue(start, end):
    for i in range(start, end):
        factorial(i**2)


def do_threading(start, end):
    my_threads = []

    for i in range(start, end):
        t = threading.Thread(target=factorial, args=(i**2,))
        t.start()
        my_threads.append(t)

    for t in my_threads:
        t.join()


def do_concurrent(start, end):
    with concurrent.futures.ThreadPoolExecutor() as ex:
        results = [ex.submit(factorial, i**2) for i in range(start, end)]
        for i in concurrent.futures.as_completed(results):
            print(i.result())


def compare(func):
    start = time.perf_counter()
    x = 5
    func(x, x+5)
    duration = time.perf_counter() - start

    print(f"Used time: {duration:.5} seconds\n")


# Run functions here
print("Do queue")
compare(do_queue)

print("Do threading")
compare(do_threading)

print("Do concurrent")
compare(do_concurrent)