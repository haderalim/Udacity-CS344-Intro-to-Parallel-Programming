

. If you use CPU to run a program which square elements of an array, it needs only one thread of execution. In this program, the size of array = 64. So, it will take 64 times per iteration. But, by running on a GPU, we are going to launch 64 threads and they are running in parallel at the same time.

. Here the relation between CPU and GPU is in charge. It runs the main program and it sends direction to the GPU to tell it what to do.
