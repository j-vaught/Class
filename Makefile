all: Vaught_Jacob_QuickSort InputFileGenerator

Vaught_Jacob_QuickSort: Vaught_Jacob_QuickSort.cpp
	g++ -o Vaught_Jacob_QuickSort Vaught_Jacob_QuickSort.cpp

QuickSortTest: QuickSortTest.cpp
	g++ -o InputFileGenerator InputFileGenerator.cpp

clean:
	rm -f Vaught_Jacob_QuickSort InputFileGenerator