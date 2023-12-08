#include <iostream> // Include the standard I/O library
#include <fstream> // Include the file stream library for file operations
#include <vector> // Include the vector container library
#include <chrono> // Include the chrono library for high-resolution clock
#include <algorithm> // Include the algorithm library for swap function
#include <cassert> // Include the assert library for debugging
#include <random> // Include the random library for generating random numbers

using namespace std; // Use the standard namespace
using namespace std::chrono; // Use the chrono namespace for high-resolution clock

int findMedianIndex(vector<float>& arr, int low, int high) {
    int middle = (low + high) / 2; // Find the middle index
    // Ensure low, middle, and high elements are sorted
    if (arr[low] > arr[middle])
        swap(arr[low], arr[middle]);
    if (arr[low] > arr[high])
        swap(arr[low], arr[high]);
    if (arr[middle] > arr[high])
        swap(arr[middle], arr[high]);

    swap(arr[middle], arr[high - 1]); // Place median at high-1 position
    return high - 1; // Return median index
}

int partition(vector<float>& arr, int low, int high) {
    int medianIndex = findMedianIndex(arr, low, high); // Find the median index
    float pivot = arr[medianIndex]; // Choose the median as the pivot
    swap(arr[medianIndex], arr[high - 1]); // Move pivot to end for partitioning

    int i = low; // Partitioning index
    for (int j = low; j < high - 1; ++j) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            ++i;
        }
    }
    swap(arr[i], arr[high - 1]); // Restore pivot
    return i; // Return pivot's final position
}

void quickSort(vector<float>& arr, int low, int high) {
    if (low >= high) return; // Base case for recursion
    int pivotIndex = partition(arr, low, high); // Partition the array
    quickSort(arr, low, pivotIndex - 1); // Sort the left part
    quickSort(arr, pivotIndex + 1, high); // Sort the right part
}

void quickSort(vector<float>& arr) {
    if (!arr.empty())
        quickSort(arr, 0, arr.size() - 1); // Initiate quicksort if array is not empty
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <inputfile> <outputfile>\n"; // Check command-line arguments
        return 1;
    }

    ifstream inFile(argv[1]); // Open the input file
    if (!inFile) {
        cout << "Error opening input file\n"; // Check if file opened successfully
        return 1;
    }

    vector<float> numbers; // Vector to store numbers from the file
    float temp;
    while (inFile >> temp) {
        numbers.push_back(temp); // Read numbers from the file
    }
    inFile.close(); // Close the input file

    auto start = high_resolution_clock::now(); // Start the timer
    quickSort(numbers); // Perform quicksort on the vector
    auto stop = high_resolution_clock::now(); // Stop the timer
    auto duration = duration_cast<microseconds>(stop - start); // Calculate the duration

    ofstream outFile(argv[2]); // Open the output file
    for (float num : numbers) {
        outFile << num << " "; // Write sorted numbers to the file
    }
    outFile.close(); // Close the output file

    ofstream timeFile("Vaught_Jacob_executionTime.txt", ios::app); // Open the execution time file
    if (!timeFile) {
        cout << "Error opening time file\n"; // Check if file opened successfully
        return 1;
    }
    timeFile << numbers.size() << "\t" << duration.count() << "\n"; // Write size and duration to the file
    timeFile.close(); // Close the time file

    return 0; // End the program
}
