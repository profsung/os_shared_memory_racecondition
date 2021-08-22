p: producer.cpp my_defs.h
	g++ producer.cpp -lrt -o p

c: consumer.cpp my_defs.h
	g++ consumer.cpp -lrt -o c

clean:
	rm -f *.o p c *.zip

zip:
	zip shared_mem.zip *.h *.cpp Makefile