---
layout: post
title:  "Memory allocation - A mental model (pt. 1)"
tags: [c, memory, heap, allocation]
date:   2023-08-10 22:57:49 +0000
---

A few days ago, I engaged in a discussion with a friend about memory management concepts. We delved into topics like static vs. dynamic memory allocations, stack vs. heap, etc.

This conversation got me thinking - despite having tackled various coding challenges involving data structures and simple allocators, I realized I had never embarked on the journey of building a memory allocation system from scratch. And so, here I am, at the inception of a series dedicated to understanding and crafting memory management systems.

What follows is the initial iteration, a mere draft, of this memory allocation system. The primary goal is to grasp fundamental concepts related to memory allocation. In the sessions to come, I anticipate refactoring and optimizing the code as my insights deepen. Today's plan is to survive day zero.

This is only a deliberated practice over memory allocation. I do not have any interest in a functional implementation. For a more detailed implementation, such as a version of malloc/free. I will recommend the use of better approaches and tools like the UNIX syscalls `sbrk` and `mmap`. 

## The heap allocation

First things first. Let’s start creating our heap structure and its capacity. Here I choose to use a standard C-like array to emulate our heap.

```c
#define HEAP_CAP 640000
uintptr_t heap[HEAP_CAP] = {0};
size_t heap_size = 0;
```

To make it easy to test let’s create an initial function to validate our implementation. The test is simple, alloc 10 bytes at the heap.

```c
void test_alloc(void) {
    uintptr_t *root = heap_alloc(10);

    assert(heap_size == 10);
    assert(allocated.size == 1);
    assert(root == allocated.chunks[0].start);

    printf("test_alloc: passed\n");
}
```

`heap_alloc` should mimic the `malloc` function. So, the API could be defined as `void * heap_alloc(size_t size)`. The contract is simple, find an available chunk of memory on the heap. Then return the pointer to this memory location.

Reading the `man` of `malloc` [1] we could note that this operation always returns a unique pointer. I’ve never noted that before, and it is very important for a specific case. Allocation of zero byte chunk.

> malloc()
       The malloc() function allocates size bytes and returns a pointer
       to the allocated memory. The memory is not initialized. If size 
       is 0, then malloc() returns a unique pointer value that can later
       be successfully passed to free().  (See "Nonportable behavior"
       for portability issues.)
> 

As I already said before, we will take a shortcut in this implementation. We will handle this edge case by returning a NULL pointer, just at this moment.

When I was figuring out how to create the memory allocation, I thought of using a simple data structure to handle both allocated and freed chunks of heap memory. It was funny because a lot of ideas (basically because of performance) are to apply a data structure that is dynamically allocated, such as hash maps and etc. And damn, we couldn’t use it, because we are creating the memory allocation. It will be cheating.

So, for the initial approach, I propose the use of a simple array. These are the data structures for managing the metadata of our heap allocator.

```c
#define HEAP_CAP 640000
#define HEAP_CHUNK_CAP 1024

typedef struct {
    void *start;
    size_t size;
} chunk_t;

typedef struct {
    size_t size;
    chunk_t chunks[HEAP_CHUNK_CAP];
} chunk_list_t;

uintptr_t heap[HEAP_CAP] = {0};
size_t heap_size = 0;

chunk_list_t allocated = {0};
chunk_list_t freed = {
    .size = 1,
    .chunks = {[0] = {.start = heap, .size = sizeof(heap)}},
};
```

`chunk_t` is the data structure to hold the metadata information of an “allocated” or “freed” chunk of memory. As will see in the `malloc` API, the pointer to the beginning (`start`) and the size of the chunk (`size`) are important. 

Also, I defined (`chunk_list_t`) an array of `chunk_t`s, it represents the `allocated` and `freed` chunks of memory of our heap. Here, `size` has the meaning of `capability` saying how many chunks I have in my list.

May not be clear at first glance. But our heap starts fully freed. So, `freed` should be initialized with a heap-sized block. Thus, `allocated` doesn’t contains any block. 

Finally, the naive approach to allocating memory in the heap is simple. Find a place that fits the memory, remove this chunk from the `freed`, and insert it into the `allocated`. In general, the available size is bigger than the required size. So we need to re-insert the amount of spare free space into the `freed` again. Lets that a look at the implementation of the heap allocation function.

```c
void *heap_alloc(size_t size) {
    if (size <= 0) {
        return NULL;
    }

    if (size > HEAP_CAP - heap_size) {
        return NULL;
    }

    for (size_t i = 0; i < freed.size; i++) {
        const chunk_t chunk = freed.chunks[i];
        if (chunk.size >= size) {
            chunk_list_remove(&freed, i);

            chunk_list_insert(&allocated, chunk.start, size);

            const size_t spare = chunk.size - size;
            if (spare > 0) {
                chunk_list_insert(&freed, (uintptr_t *)chunk.start + size,
                                  spare);
            }

            heap_size += size;
            return chunk.start;
        }
    }
    return NULL;
}
```

It seems good, but before we test it, we need to produce the two auxiliary functions. `chunk_list_remove` and `chunck_list_inser` are both methods that manipulate the `chunk_list_t`.

Since the objective here is just to learn interesting concepts about memory allocation. I choose a linear search on the arrays. One time that the arrays are sorted, you could use a binary sort or other kind of algorithm.

```c
void chunk_list_remove(chunk_list_t *list, const size_t index) {
    if (list->size <= 0) {
        return;
    }

    for (size_t i = index; i < list->size - 1; i++) {
        list->chunks[i] = list->chunks[i + 1];
    }
    list->size--;
}
```

As I've mentioned before, is particularly interesting to maintain the arrays sorted. It will help us in some moment and will possibility some improvements. If it is not clear now, don't worry, on my first try I thought the same.

In order to maintain the array sorted I choose a kind of insertion sort starting from the and, always guaranteeing that the array is sorted before and after the insertion.

```c
void chunk_list_insert(chunk_list_t *list, void *start, const size_t size) {
    if (list->size >= HEAP_CHUNK_CAP) {
        return;
    }

    chunk_t chunk = {.size = size, .start = start};
    list->chunks[list->size++] = chunk;

    for (size_t i = list->size - 1; i > 0; i--) {
        if (list->chunks[i - 1].start < list->chunks[i].start) {
            break;
        }

        const chunk_t tmp = list->chunks[i];
        list->chunks[i] = list->chunks[i - 1];
        list->chunks[i - 1] = tmp;
    }
}
```

To help in the visualization of the memory allocated and freed. I've created an auxiliary function to print the lists.

```c
void chunk_list_dump(const chunk_list_t *list) {
    printf("Chunks (%zu)\n", list->size);
    for (size_t i = 0; i < list->size; i++) {
        printf("start: %p: size: %zu\n", list->chunks[i].start,
               list->chunks[i].size);
    }
}
```

Then, running the test we got it passed.

```bash
gbs@gojira:~/fun/blog/cpp/memory-allocation $ rm heap; make; ./heap
cc -Wall -Wextra -Werror -std=c11 -pedantic -ggdb -o heap heap.c
Chunks (1)
start: 0x100794008: size: 10
test_alloc: passed
```

Another good test to validate our allocation is to confirm that the allocations are being inserted correctly. So I've proposed the following test.

```c
void test_find(void) {
    for (size_t i = 0; i < 10; i++) {
        const uintptr_t *p = heap_alloc(i);
        if (i % 2) {
            int ka = chunk_list_find(&allocated, p);
            int kf = chunk_list_find(&freed, p);

            assert(ka == (int)(i - 1));
            assert(kf == -1);
            assert(allocated.chunks[ka].start == p);
        }
    }

    chunk_list_dump(&allocated);
    printf("test_find: passed\n");
}
```

Let's create another auxiliary function. It should be responsible to find the requested node inside the list. As I've said before, here we could adopt a different algorithm, for simplicity, I choose the linear search.

```c
int chunk_list_find(const chunk_list_t *list, const uintptr_t *ptr) {
    for (size_t i = 0; i < list->size; i++) {
        if (list->chunks[i].start == ptr) {
            return i;
        }
    }

    return -1;
}
```

```bash
gbs@gojira:~/fun/blog/cpp/memory-allocation $ rm heap; make; ./heap
cc -Wall -Wextra -Werror -std=c11 -pedantic -ggdb -o heap heap.c
Chunks (9)
start: 0x104f7c008: size: 1
start: 0x104f7c010: size: 2
start: 0x104f7c020: size: 3
start: 0x104f7c038: size: 4
start: 0x104f7c058: size: 5
start: 0x104f7c080: size: 6
start: 0x104f7c0b0: size: 7
start: 0x104f7c0e8: size: 8
start: 0x104f7c128: size: 9
```

## The heap free

Now, let's code think about the free. Taking a look at the `free` API we could get a good intuition of how it works.

> free()
       The free() function frees the memory space pointed to by ptr,
       which must have been returned by a previous call to malloc() or
       related functions.  Otherwise, or if ptr has already been freed,
       undefined behavior occurs.  If ptr is NULL, no operation is
       performed.
> 

So, let's create a simple test to validate the `heap_free` function. It will allocate and free chunks of memory.

```c
void test_free(void) {
    for (size_t i = 0; i < 10; i++) {
        uintptr_t *p = heap_alloc(i);
        if (i % 2) {
	          int ka = chunk_list_find(&alloced, p);
	          assert(allocated.chunks[ka].start == p);

            heap_free(p);

	          int kf = chunk_list_find(&freed, p);
	          assert(freed.chunks[kf].start == p);

        }
    }
	
	  chunk_list_dump(&alloced);
	  chunk_list_dump(&freed);	
		printf("test_free: passed\n");
}
```

Since we already have created the `chunk_list_insert`, `chunk_list_remove`, and `chunk_list_find` is clear how to create the free function. It should receive a pointer for the chunk, find the chunk and move it from the `allocated` to the `freed` list.

```c
void heap_free(void *ptr) {
		if (ptr == NULL) {
				return;
		}

    const int index = chunk_list_find(&allocated, ptr);

    if (index < 0) {
        return;
    }

    chunk_list_insert(&freed, allocated.chunks[index].start,
                      allocated.chunks[index].size);

    chunk_list_remove(&allocated, (size_t)index);
}
```

```bash
gbs@gojira:~/fun/blog/cpp/memory-allocation $ rm heap; make; ./heap
cc -Wall -Wextra -Werror -std=c11 -pedantic -ggdb -o heap heap.c
Chunks (4)
start: 0x1021e4010: size: 2
start: 0x1021e4038: size: 4
start: 0x1021e4080: size: 6
start: 0x1021e40e8: size: 8
Chunks (6)
start: 0x1021e4008: size: 1
start: 0x1021e4020: size: 3
start: 0x1021e4058: size: 5
start: 0x1021e40b0: size: 7
start: 0x1021e4128: size: 9
start: 0x1021e4170: size: 5119955
```

We also could check how the reallocation of the freed chunks are being performed.

 

```c
void test_reallocation(void) {
    for (size_t i = 0; i < 10; i++) {
        uintptr_t *p = heap_alloc(i);
        if (i % 2) {
            heap_free(p);
        }
    }

    chunk_list_dump(&allocated);
    chunk_list_dump(&freed);

    heap_alloc(1337);

    chunk_list_dump(&allocated);
    chunk_list_dump(&freed);

    for (size_t i = 1; i < 10; i += 2) {
        heap_alloc(i);
    }

    chunk_list_dump(&allocated);
    chunk_list_dump(&freed);
}
```

```bash
gbs@gojira:~/fun/blog/cpp/memory-allocation $ rm heap; make; ./heap
cc -Wall -Wextra -Werror -std=c11 -pedantic -ggdb -o heap heap.c
Chunks (4)
start: 0x102888010: size: 2
start: 0x102888038: size: 4
start: 0x102888080: size: 6
start: 0x1028880e8: size: 8
Chunks (6)
start: 0x102888008: size: 1
start: 0x102888020: size: 3
start: 0x102888058: size: 5
start: 0x1028880b0: size: 7
start: 0x102888128: size: 9
start: 0x102888170: size: 5119955
Chunks (5)
start: 0x102888010: size: 2
start: 0x102888038: size: 4
start: 0x102888080: size: 6
start: 0x1028880e8: size: 8
start: 0x102888170: size: 1337
Chunks (6)
start: 0x102888008: size: 1
start: 0x102888020: size: 3
start: 0x102888058: size: 5
start: 0x1028880b0: size: 7
start: 0x102888128: size: 9
start: 0x10288ab38: size: 5118618
Chunks (10)
start: 0x102888008: size: 1
start: 0x102888010: size: 2
start: 0x102888020: size: 3
start: 0x102888038: size: 4
start: 0x102888058: size: 5
start: 0x102888080: size: 6
start: 0x1028880b0: size: 7
start: 0x1028880e8: size: 8
start: 0x102888128: size: 9
start: 0x102888170: size: 1337
Chunks (1)
start: 0x10288ab38: size: 5118618
```

Everything is going well. The allocation of the freed elements occurs in the correct place (following our algorithm). 

## The heap merge

Now we start to realize that memory fragmentation occurs in the heap and also in the metadata structures. 

In the last test, we noted that the reallocations were performed in the “correct” chunks. But it is, actually, a problem. It seems like memory fragmentation. We create free chunks with very specific sizes.

Trying to figure out how to handle the fragmentation I've created a `chunk_list_merge`. This helper function will merge the consecutive blocks of freed memory.

```c
void test_merge(void) {

    for (size_t i = 0; i < 10; i++) {
        uintptr_t *p = heap_alloc(i);
        heap_free(p);
    }

    chunk_list_dump(&allocated);
    chunk_list_dump(&freed);

    chunk_list_t merged = {0};
    chunk_list_merge(&freed, &merged);

    chunk_list_dump(&allocated);
    chunk_list_dump(&merged);
}
```

```c
void chunk_list_merge(const chunk_list_t *list, chunk_list_t *merged) {
    merged->size = 0;

    for (size_t i = 0; i < list->size; i++) {
        const chunk_t chunk = list->chunks[i];

        if (merged->size > 0) {
            chunk_t *top = &merged->chunks[merged->size - 1];

            if ((uintptr_t *)top->start + top->size == chunk.start) {
                top->size += chunk.size;
            } else {
                chunk_list_insert(merged, chunk.start, chunk.size);
            }
        } else {
            chunk_list_insert(merged, chunk.start, chunk.size);
        }
    }
}
```

It doesn't solve the entire problem. A better approach is to use another structure to handle the metadata. These spare blocks cause high fragmentation.

We do not discuss the “paradise of un-aligned data” This implementation works well in the scenario but is no longer than a proof of concept.

But ok, let’s run the test and check if the merge is correctly performed.

```bash
gbs@gojira:~/fun/blog/cpp/memory-allocation $ rm heap; make; ./heap
cc -Wall -Wextra -Werror -std=c11 -pedantic -ggdb -o heap heap.c
Chunks (0)
Chunks (10)
start: 0x1045f0008: size: 1
start: 0x1045f0010: size: 2
start: 0x1045f0020: size: 3
start: 0x1045f0038: size: 4
start: 0x1045f0058: size: 5
start: 0x1045f0080: size: 6
start: 0x1045f00b0: size: 7
start: 0x1045f00e8: size: 8
start: 0x1045f0128: size: 9
start: 0x1045f0170: size: 5119955
Chunks (0)
Chunks (1)
start: 0x1045f0008: size: 5120000
```

Yes, it works. We allocate and then free 10 different blocks. Then run the `chunk_list_merge` and the outcome is only one block of heap size.

Ok, let’s try to figure out when is the best moment to perform the merge. Since this operation is quite expensive I see some options. For example, we could run it when the system runs out of memory. But, for simplicity, I chose to execute it in any allocation. So every time that we plan to allocate memory, I guarantee that it is allocated in a good fit.

So, let’s create a test and modify the `heap_allocate`. 

The test is simple. Allocate and free the memory and then try to allocate a new chunk.

```c
void test_merge(void) {
    for (int i = 0; i < 100; ++i) {
        void *p = heap_alloc(i);
        heap_free(p);
    }

    chunk_list_dump(&alloced);
    chunk_list_dump(&freed);

    assert(alloced.size == 0);
    assert(freed.size == 2);

    heap_alloc(10);

    assert(alloced.size == 1);
    assert(alloced.chunks[0].size == 10);
    assert(freed.size == 1);

    chunk_list_dump(&alloced);
    chunk_list_dump(&freed);
}
```

To perform the merge during the allocation is pretty simple. Before the allocation, we’ll try to merge the `freed` list. Also, we can declare an auxiliary chunk list to assist during the operation.

```c
chunk_list_t tmp_list = {0};

void *heap_alloc(size_t size) {
    if (size <= 0) {
        return NULL;
    }

    if (size > HEAP_CAP - heap_size) {
        return NULL;
    }

    chunk_list_merge(&freed, &tmp_list);
    freed = tmp_list;

    for (size_t i = 0; i < freed.size; i++) {
        const chunk_t chunk = freed.chunks[i];
        if (chunk.size >= size) {
            chunk_list_remove(&freed, i);

            chunk_list_insert(&allocated, chunk.start, size);

            const size_t spare = chunk.size - size;
            if (spare > 0) {
                chunk_list_insert(&freed, (uintptr_t *)chunk.start + size,
                                  spare);
            }

            heap_size += size;
            return chunk.start;
        }
    }
    return NULL;
}
```

Running the test we got the excepted outcome. Remember that the merge is performed only during the allocation.

```bash
gbs@gojira:~/fun/blog/cpp/memory-allocation $ rm heap; make; ./heap
rm: heap: No such file or directory
cc -Wall -Wextra -Werror -std=c11 -pedantic -ggdb -o heap heap.c
Chunks (0)
Chunks (2)
start: 0x10299c008: size: 99
start: 0x10299c320: size: 5119901
Chunks (1)
start: 0x10299c008: size: 10
Chunks (1)
start: 0x10299c058: size: 5119990
```

We also can improve the allocation test. In this case, try to see if the new elements will be allocated in the position.

```c
void test_alloc(void) {
    for (size_t i = 0; i < 10; i++) {
        uintptr_t *p = heap_alloc(i);
        if (i % 2) {
            heap_free(p);
        }
    }

    chunk_list_dump(&alloced);
    chunk_list_dump(&freed);

    heap_alloc(1337);

    chunk_list_dump(&alloced);
    chunk_list_dump(&freed);

    for (size_t i = 0; i < 10; i += 2) {
        heap_alloc(i);
    }

    chunk_list_dump(&alloced);
    chunk_list_dump(&freed);
}
```

```bash
gbs@gojira:~/fun/blog/cpp/memory-allocaiton $ rm heap; make; ./heap
cc -Wall -Wextra -Werror -std=c11 -pedantic -ggdb -o heap heap.c
Chunks (4)
start: 0x102f68008: size: 2
start: 0x102f68018: size: 4
start: 0x102f68038: size: 6
start: 0x102f68068: size: 8
Chunks (2)
start: 0x102f680a8: size: 9
start: 0x102f680f0: size: 5119971
Chunks (5)
start: 0x102f68008: size: 2
start: 0x102f68018: size: 4
start: 0x102f68038: size: 6
start: 0x102f68068: size: 8
start: 0x102f680a8: size: 1337
Chunks (1)
start: 0x102f6aa70: size: 5118643
Chunks (10)
start: 0x102f68008: size: 2
start: 0x102f68018: size: 4
start: 0x102f68038: size: 6
start: 0x102f68068: size: 8
start: 0x102f680a8: size: 1337
start: 0x102f6aa70: size: 1
start: 0x102f6aa78: size: 3
start: 0x102f6aa90: size: 5
start: 0x102f6aab8: size: 7
start: 0x102f6aaf0: size: 9
Chunks (1)
start: 0x102f6ab38: size: 5118618
```

Therefore, we could check another behavior, fragmentation. In this test I plan to fragment the memory, freeing the even elements. In this case, we would like to see memory fragmentation.

```c
void test_fragment(void) {
    void *ptrs[10] = {0};

    for (size_t i = 0; i < 10; i++) {
        ptrs[i] = heap_alloc(i);
    }

    for (size_t i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            heap_free(ptrs[i]);
        }
    }

    heap_alloc(10);

    chunk_list_dump(&allocated);
    chunk_list_dump(&freed);
}
```

```bash
gbs@gojira:~/fun/blog/cpp/memory-allocation $ rm heap; make; ./heap
cc -Wall -Wextra -Werror -std=c11 -pedantic -ggdb -o heap heap.c
Chunks (6)
start: 0x10433c008: size: 1
start: 0x10433c020: size: 3
start: 0x10433c058: size: 5
start: 0x10433c0b0: size: 7
start: 0x10433c128: size: 9
start: 0x10433c170: size: 10
Chunks (5)
start: 0x10433c010: size: 2
start: 0x10433c038: size: 4
start: 0x10433c080: size: 6
start: 0x10433c0e8: size: 8
start: 0x10433c1c0: size: 5119945
```

And yes, as expected it was not able to merge non-continuous memory.

## Takeaways

After this deliberate practice, I could understand some interesting topics. And I’ve some takeaways.

- My first implementation tries to use arrays of “chunks” as the metadata data struct. Basically because of the facility. It has performed ok, but a know that there are better data structures for this proposal.
- Sorted metadata structure. This seems to be a key role in memory management. Now I understand better why the heap data structure is so good for a sort of application.
- Because of my poor choices, I’ve implemented a lot of not efficient algorithms. Basically, all of them are linear complexity - O(n). In certain moments, like the “find” a binary search could bring a better result.
- Besides the syscalls there are a couple of reasons why the malloc is slow.
