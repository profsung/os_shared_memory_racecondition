#include <sys/mman.h> // shm_open() mmap() munmap()
#include <sys/stat.h> // mode constants
#include <fcntl.h> // O_* constants
#include <unistd.h> // ftruncate() close()
#include <stdlib.h> // exit()
#include <stdio.h> // printf/scanf

#include "my_defs.h"

int main() {
	int fd;
	for ( ; ;) {
		fd = shm_open(NAME, O_RDWR, 0666);
		if (fd >= 0) break;
		printf("waiting for producer to create a shared memory ...\n");
		sleep(1);
	}

	int* p_data = (int *)
	   mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	printf("Consumer successfully opened shared memory.\n");

	for (int i = 0; i < 20000; i++) {
		p_data[0] = 9999;
		int ms = (rand() % 2000) * 1000;
		usleep(ms);
		printf("[%d] consumer: %d\n", i, p_data[0]);
	}

	munmap(p_data, SIZE);
	close(fd);
	shm_unlink(NAME); // shared memory is deleted
}