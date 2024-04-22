#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <random>
#include <ctime>

std::mutex mtx; // Mutex for shared resource
std::vector<int> finish_order; // Vector to hold finish order
// Team names: update to be GitHub theme names
std::vector<std::string> team_names = {"Octocat", "Hubot", "Copilot", "Code", "GitHub", "Actions", "Packages", "Security", "Insights", "Issues"};
// Function to calculate sum of array elements
void calculate_sum(std::vector<int>& arr, int start, int end, int& result, int thread_id) {
    for (int i = start; i < end; i++) {
        result += arr[i];
    }
    // Lock mutex and update finish order
    mtx.lock();
    finish_order.push_back(thread_id);
    mtx.unlock();
}

int main() {
    // Initialize random number generator
    std::mt19937 rng(time(0));

    // Initialize array
    std::vector<int> arr;
    for (int i = 1; i <= 1000000; i++) {
        arr.push_back(i);
    }

    int num_threads = std::thread::hardware_concurrency(); // Get number of threads
    std::vector<std::thread> threads(num_threads); // Vector to hold all threads
    std::vector<int> results(num_threads, 0); // Vector to hold results from each thread

    int len = arr.size() / num_threads; // Length of each part

    // Create threads
    for (int i = 0; i < num_threads; i++) {
        threads[i] = std::thread(calculate_sum, std::ref(arr), i*len, (i+1)*len, std::ref(results[i]), i);
    }

    // Handle remainder if array size is not perfectly divisible by number of threads
    for (int i = num_threads*len; i < arr.size(); i++) {
        results[0] += arr[i];
    }

    // Join threads
    for (auto& th : threads) {
        th.join();
    }

    // Calculate total sum
    int total_sum = 0;
    for (const auto& res : results) {
        total_sum += res;
    }

    std::cout << "Sum = " << total_sum << std::endl;

    // Print finish order
    std::cout << "Finish order:\n";
    for (const auto& order : finish_order) {
        std::cout << "Team " << team_names[order % team_names.size()] << "\n";
    }
    std::cout << std::endl;

    return 0;
}

