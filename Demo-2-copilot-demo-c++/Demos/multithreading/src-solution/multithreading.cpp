#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

// Global variable for storing the sum
long long sum = 0;

// Mutex for synchronizing access to the sum
std::mutex mtx_sum;

// Vector for storing the results
std::vector<std::pair<int, std::chrono::duration<double>>> results;

// Mutex for synchronizing access to the results
std::mutex mtx_results;

// Function for calculating the sum of elements in a part of the array
void calculate_sum(std::vector<int>& arr, int start, int end, int thread_id) {
    auto start_time = std::chrono::high_resolution_clock::now();

    long long partial_sum = 0;
    for (int i = start; i < end; ++i) {
        partial_sum += arr[i];
    }

    // Lock the mutex before updating the global sum
    mtx_sum.lock();
    sum += partial_sum;
    mtx_sum.unlock();

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    // Lock the mutex before updating the results
    mtx_results.lock();
    results.push_back({thread_id, elapsed});
    mtx_results.unlock();
}

int main() {
    // Size of the array
    int size = 1000000;

    std::vector<std::string> teamNames = {"Ferrari", "RedBull", "Mercedes",
     "McLaren", "Aston Martin", "Alpine", "Alpha Tauri", "Alfa Romeo", "Haas", "Williams"};

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(teamNames.begin(), teamNames.end(), g);
    // Initialize the array with random numbers
    srand(time(0));
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand();
    }

    // Number of threads
    int num_threads = 10;

    // Calculate the size of the parts
    int part_size = arr.size() / num_threads;

    // Vector for storing the threads
    std::vector<std::thread> threads;

    // Create and start the threads
    for (int i = 0; i < num_threads; ++i) {
        int start = i * part_size;
        int end = (i == num_threads - 1) ? arr.size() : (i + 1) * part_size;
        threads.push_back(std::thread(calculate_sum, std::ref(arr), start, end, i));
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    // Sort the results
     std::sort(results.begin(), results.end(), [](const std::pair<int, std::chrono::duration<double>>& a, const std::pair<int, std::chrono::duration<double>>& b) {
    return a.second < b.second;
    });

    // Print the results
    for (int i = 0; i < results.size(); ++i) {
    std::cout << teamNames[results[i].first] << " finished " << (i + 1) << " with time " << results[i].second.count() << " seconds.\n";
    }

    // Print the sum
    std::cout << "Sum: " << sum << std::endl;

    return 0;
}