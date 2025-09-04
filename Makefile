all:
	gcc -g -o prog main.c serial.c mutex.c rw_lock.c linked_list.c -pthread

clean:
	rm prog
