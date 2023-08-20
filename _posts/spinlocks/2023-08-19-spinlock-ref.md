---
layout: post
title:  "Spinlock - Basics (pt. 1)"
tags: [c++, concurrent, multithreading, spinlock, synchronization]
date:   2023-08-19 22:57:49 +0000
---

Synchronization is a pretty exciting topic. An important key in the multithreaded and concurrent process.

Today I plan to do a deliberate practice over the spinlocks. Probably it also will be a series of posts over the other synchronization primitives.

Spinlocks are synchronization primitives used to protect shared resources in multithreaded environments. They might seem simple, but mastering them requires a deep understanding of their implementation details.

At the core, a spinlock is a binary flag that indicates whether a resource is currently being accessed by a thread. When a thread wants to access the r  it first checks if the spinlock is available. If it is, the thread sets the spinlock to a "locked" state and proceeds with the critical section of the code. If the spinlock is already locked, the thread "spins" in a loop, continuously checking the lock's status until it becomes available.

Because they avoid overhead from rescheduling and context switching, spinlocks are efficient if threads are likely to be blocked for only short periods (since the thread remains active but is not performing a useful task). For this reason, kernels often use spinlock (https://en.wikipedia.org/wiki/Spinlock).

So, let’s start this study by trying to understand the basics of a spinlock, and how to implement it.

## What is a spinlock?

As I’ve mentioned, a spinlock is a pattern that blocks the code until a certain condition is validated. So, in general, we can describe the spinlock based on three elements:

1. A state which should be evaluated;
2. A lock function that should block the program;
3. An unlock function that should release the resource.

```cpp
class Spinlock {
  private:
    bool locked{false};

  public:
    void lock() {
				locked = true;
        while (locked);
    }

    void unlock() { locked=false; }
};
```

This is the template of this pattern. A state (`locked`), the `lock` function that blocks (i.e. `while(1)`), and the `unlock` function that releases the lock condition.

Now, let’s test our simplest spinlock implementation. Here, I’ve proposed (`work`) a simple function that tries to modify the value of a variable in a multithreading scenario.
 

```cpp
void work(std::int64_t &val) {
    for (int i = 0; i < 100000; i++) {
        val++;
    }
}
```

And then, the `test_work_on_two_threads` to evaluate it in a concurrent environment.

```cpp
void test_work_on_two_threads() {
	std::int64_t val = 0;

	Spinlock sl;

	std::thread t1(work, std::ref(sl), std::ref(val));
	std::thread t2(work, std::ref(sl), std::ref(val));

	t1.join();
	t2.join();

	std::cout << val << std::endl;
}
```

```bash
gbs@gojira:~/fun/blog/cpp/spinlock/build $ ./spinlock
119916
gbs@gojira:~/fun/blog/cpp/spinlock/build $ ./spinlock
177647
gbs@gojira:~/fun/blog/cpp/spinlock/build $ ./spinlock
110945
gbs@gojira:~/fun/blog/cpp/spinlock/build $ ./spinlock
100848
gbs@gojira:~/fun/blog/cpp/spinlock/build $ ./spinlock
127276
gbs@gojira:~/fun/blog/cpp/spinlock/build $ ./spinlock
150574
gbs@gojira:~/fun/blog/cpp/spinlock/build $ ./spinlock
172791
gbs@gojira:~/fun/blog/cpp/spinlock/build $ ./spinlock
109485
gbs@gojira:~/fun/blog/cpp/spinlock/build $ ./spinlock
106638
```

This is the ideal of a basic spinlock, obviously, this code does not run correctly, in special in a concurrent scenario. Each thread tries to modify the read-modify value concurrently. Let’s modify it to get a useful version.

I’ve planned to implement different versions of this spinlock. My objective here is to understand deeply the concept. Therefore, let’s do it in baby steps. 

An initial approach to creating a viable implementation is to use the `std::atomic` (https://en.cppreference.com/w/cpp/atomic/atomic). It will provide us with the possibility of working in multithreading and also some tools to maintain the spinlock.

In special, the `std::atomic` provides us with a state (1) that holds atomically the current status of the spinlock. Also, the very intuitive `exchange` that atomically replaces the value of the atomic object and obtains the value held previously. It means, that when the `locked` comes false the lock condition will become false too.

```cpp
class Spinlock {
  private:
    std::atomic<bool> locked{false};

  public:
    void lock() {
        while (locked.exchange(true));
    }

    void unlock() { locked.store(false); }
};
```

Adding the spinlock to guarantee the concurrent access we have:

```cpp
void work(Spinlock &s, std::int64_t &val) {
    for (int i = 0; i < MAX_ITER; i++) {
        s.lock();
        val++;
        s.unlock();
    }
}
```

Then, running the `test_work_on_two_threads` we got:

```bash
gbs@gojira:~/fun/blog/cpp/spinlock/build $ ./spinlock
200000
gbs@gojira:~/fun/blog/cpp/spinlock/build $ ./spinlock
200000
gbs@gojira:~/fun/blog/cpp/spinlock/build $ ./spinlock
200000
gbs@gojira:~/fun/blog/cpp/spinlock/build $ ./spinlock
200000
gbs@gojira:~/fun/blog/cpp/spinlock/build $ ./spinlock
200000
gbs@gojira:~/fun/blog/cpp/spinlock/build $ ./spinlock
200000
```

And as expected, it works pretty well. Now, let’s create a better test and also add the Google Benchmark (https://github.com/google/benchmark) to evaluate our different implementations of spinlock.

```cpp
static void bm_ref(benchmark::State &s) {
    auto num_threads = s.range(0);

    std::int64_t val = 0;

    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    Spinlock sl;

    for (auto _ : s) {
        for (auto i = 0u; i < num_threads; i++) {
            threads.emplace_back([&] { work(sl, val); });
        }
		
        for (auto &thread : threads)
            thread.join();
        threads.clear();
    }
}

BENCHMARK(bm_ref)
		->DenseRange(1, std::thread::hardware_concurrency(), 1)
		->UseRealTime();

BENCHMARK_MAIN();
```

```bash
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
bm_ref/1/real_time    1050932 ns        17797 ns          632
bm_ref/2/real_time    9894298 ns        40638 ns           69
bm_ref/3/real_time   15041799 ns        53106 ns           47
bm_ref/4/real_time   28551069 ns        80500 ns           24
bm_ref/5/real_time   67210773 ns       103727 ns           11
bm_ref/6/real_time  114636946 ns       135429 ns            7
bm_ref/7/real_time  127173375 ns       124667 ns            6
bm_ref/8/real_time  161605250 ns       137000 ns            5
```
This is the first part of this series. In the next parts, we’ll try to evaluate and improve this spinlock. Let’s try to analyze it deeply and take a look at how spinlock is really implemented.
