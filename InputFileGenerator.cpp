#include <iostream> // Include the standard I/O library
#include <fstream> // Include the file stream library for file operations
#include <vector> // Include the vector container library
#include <string> // Include the string library
#include <chrono> // Include the chrono library for time-related operations
#include <numeric> // Include the numeric library for numeric operations
#include <random> // Include the random library for generating random numbers
#include <sstream> // Include the stringstream library

using namespace std; // Use the standard namespace

void generateRandomNumbers(vector<float>& arr, int count) {
    random_device rd; // Initializes a random number generator
    mt19937 gen(rd()); // Initializes a Mersenne Twister random number generator
    uniform_real_distribution<> dis(-100, 100); // Defines a distribution range for real numbers

    arr.clear(); // Clears the input vector
    for (int i = 0; i < count; ++i) {
        arr.push_back(dis(gen)); // Generates a random number and adds it to the vector
    }
}

void createTestFile(const string& filename, const vector<float>& numbers) {
    ofstream outFile(filename); // Opens a file for writing
    for (float num : numbers) {
        outFile << num << " "; // Writes each number to the file
    }
    outFile.close(); // Closes the file
}

void runQuickSortTest(int size, int fileCount) {
    vector<float> numbers; // Vector to store random numbers

    for (int i = 0; i < fileCount; ++i) {
        string inputFilename = "test_input_" + to_string(size) + ".txt"; // Creates input filename
        string outputFilename = "test_output_" + to_string(size) + ".txt"; // Creates output filename

        generateRandomNumbers(numbers, size); // Generates random numbers
        createTestFile(inputFilename, numbers); // Creates a test file with generated numbers

        string command = "./Vaught_Jacob_QuickSort " + inputFilename + " " + outputFilename; // Constructs command for sorting
        system(command.c_str()); // Executes the sorting command
    }
}

void calculateAverageExecutionTime(int size, const string& timeFile, const string& avgTimeFile) {
    ifstream inFile(timeFile); // Opens a file for reading
    ofstream outFile(avgTimeFile, ios::app); // Opens a file for appending
    string line;
    long long total = 0;
    int count = 0;

    while (getline(inFile, line)) {
        stringstream ss(line); // Reads each line into a stringstream
        int fileSize;
        long long time;
        ss >> fileSize >> time; // Extracts fileSize and time from the line
        if (fileSize == size) {
            total += time; // Accumulates time
            count++; // Increments count
        }
    }

    long long average = (count > 0) ? total / count : 0; // Calculates average time
    outFile << size << "\t" << average << "\n"; // Writes average time to file
    outFile.close(); // Closes the output file
    inFile.close(); // Closes the input file
}

int main() {
    int sizes[] = {10, 100, 1000}; // Array of different sizes to test
    int fileCount = 25; // Number of files to generate for each size

    for (int size : sizes) {
        runQuickSortTest(size, fileCount); // Runs the quick sort test for each size
        calculateAverageExecutionTime(size, "Vaught_Jacob_executionTime.txt", "Vaught_Jacob_averageExecutionTime.txt"); // Calculates average execution time for each size
    }

    return 0; // Ends the program
}
