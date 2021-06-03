all: sortTester benchmark source

sortTester : sortTester.o BucketSort.o
	g++ -std=c++14 -Wall -Werror -pg -pthread -lpthread -O2 -o sortTester sortTester.o BucketSort.o

sortTester.o: sortTester.cpp BucketSort.h
	g++ -std=c++14 -Wall -Werror -O2 -pthread -lpthread -c sortTester.cpp

benchmark : benchmark.o BucketSort.o
	g++ -std=c++14 -Wall -Werror -pthread -lpthread -O2 -o benchmark benchmark.o BucketSort.o

benchmark.o: benchmark.cpp BucketSort.h
	g++ -std=c++14 -Wall -Werror -O2 -pthread -lpthread -c benchmark.cpp

BucketSort.o : BucketSort.h BucketSort.cpp
	g++ -std=c++14 -Wall -Werror -O2 -pthread -lpthread -c BucketSort.cpp

source : Source.o BucketSort.o
	g++ -std=c++14 -Wall -Werror -pthread -lpthread -O2 -o source Source.o BucketSort.o

source.o: Source.cpp BucketSort.h
	g++ -std=c++14 -Wall -Werror -O2 -pthread -lpthread -c Source.cpp

clean:
	rm *.o sortTester benchmark source
