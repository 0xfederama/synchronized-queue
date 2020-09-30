# synchronized-queue

A thread synchonized queue made for C's PThreads.

## Usage 

Place the files `fifoQ.c` and `fifoQ.h` in your project directory.

In order to compile the code and run it, first off you have to compile the library with `gcc fifoQ.c -c -o fifoQ.o`, then create the static library with `ar rvs libfifoq.a fifoQ.o` and compile with your code using `gcc main.c -lpthread -o main -L. -lfifoq`.

Here's what you can do with this library: 
```
	//Create the queue
	Q = initQueue();
	
	//Insert an element in the queue
	void *element;
	push(Q, element);

	//Remove an element from the queue
	void *head = pop(Q);

	//Get the size of the queue
	int size = getSize(Q);

	//Delete and free the space of the queue
	deleteQueue(Q);
```

## License

Under the MIT License, you can do whatever you want with this library, even use it in closed source projects. Despite that, a mention is appreciated :wink:.
