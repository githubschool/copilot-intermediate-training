# Getting Started - C++ Multithreading Demo - Visual Studio Code

Welcome to GitHub Copilot! What will be the best way to see the power of Copilot? Let's build a simple C++ multithreading demo that demonstrates how to create and manage threads in C++ using Visual Studio Code with Copilot's help.

Although you can use any supported editor for Copilot like Visual Studio Code, Visual Studio IDE, NeoVim, and IntelliJ, we will use Visual Studio Code for this demo.

## Pre-requisites

- [VSCode](https://code.visualstudio.com/download)
- [Install g++ compiler](https://code.visualstudio.com/docs/cpp/config-mingw)
- [C/C++ Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
- [Copilot Extension for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=GitHub.copilot)
- [Copilot Chat Extension for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=GitHub.copilot-chat)

## Steps

Welcome! In this starting Copilot demo for **Getting started - C++ Multithreading - Visual Studio Code**, we will create a multithreading example very quickly and iterate over this application with a few additional prompts.

![Let's Begin!](/Demos/multithreading/images/jetpack.png)

### Step 1: Open Visual Studio Code and open GitHub Copilot Chat

Open Visual Studio Code and navigate to primary location of your GitHub Copilot chat, by default it is on the right but you may have moved it somewhere else. Make sure that your GitHub Copilot is enabled and turned on. 
![Let's Setup!](/Demos/multithreading/images/Where.png)

Your Visual Studio Code should look like this. We are now ready to write some code through GitHub Copilot.
![Ready!](/Demos/multithreading/images/Chat.png)

### Step 2: Ask GitHub Copilot Chat for assistance

In the GitHub Copilot Chat text box, provide the following prompt to get help from GitHub Copilot Chat.

```txt
Can you create a program in C++ that calculate the sum of elements in an array using multiple threads
```

Copilot Chat will provide the code for you to text in the chat.

You have 2 options of getting the code into your project.

#### Option 1

By clicking on the code that was generated and hovering over the top right corner, you can press the copy button to add it to your clipboard for easy pasting. Simply create the type of file you need to work with in your project and paste the generated code there.  

![Copy](/Demos/multithreading/images/copy.png)

For this example, if we chose Option 1 we would need to create 3 files, calculator.html, calculator.js, and calculator.css. We would then paste the 3 respective generated pieces of code from GitHub Copilot Chat into each of the files.

#### Option 2

If you select Option 2, click into the code that was generated and hover over the top right corner once more. This time press the middle button labaled `Insert at cursor`. This pastes the generated code into whatever file was open in your project at your mouse's location.

![Insert](/Demos/multithreading/images/insert.png)

<details><summary>Cheat Sheet</summary>
<p>

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <cstdlib> // Include this for rand() and srand()
#include <ctime> // Include this for time()

// Global variable for storing the sum
long long sum = 0;

// Mutex for synchronizing access to the sum
std::mutex mtx;

// Function for calculating the sum of elements in a part of the array
void calculate_sum(std::vector<int>& arr, int start, int end) {
    long long partial_sum = 0;
    for (int i = start; i < end; ++i) {
        partial_sum += arr[i];
    }

    // Lock the mutex before updating the global sum
    mtx.lock();
    sum += partial_sum;
    mtx.unlock();
}

int main() {
    // Size of the array
    int size = 1000000;

     // Initialize the array with random numbers
    srand(time(0)); // Seed the random number generator with the current time
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand(); // Generate a random number
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
        threads.push_back(std::thread(calculate_sum, std::ref(arr), start, end));
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    // Print the sum
    std::cout << "Sum: " << sum << std::endl;

    return 0;
}
```

</p>
</details> 

### Step 3: Run the program

Now that you have the code in your project, we can ask GitHub Copilot Chat to run the program for us. Simply type 

```txt
How can I compile and run this program ?
```

and GitHub Copilot Chat will provide the output of the program.

<details><summary>Cheat Sheet</summary>
<p>

```bash
g++ -std=c++11 -pthread multithread.cpp -o multithread
./multithread
```

</p>
</details>

If you get any compiling errors, we can ask GitHub Copilot Chat for help. Simply type 

```txt
Can you help me with the compiling errors? <paste errors>
```

 and GitHub Copilot will provide the necessary information to fix the errors.

### Step 4: Further Iterations

Now that you have a working version of the program. Feel free to iterate on it with any prompt that you would like. We have added a few below to provide some inspiration as to what is possible with Copilot.

In case the array provided is small

```txt
can you modify it so that the array is a very large number ?
```

Add your own flavor

```txt
Can you add a "racing" theme to it, so that we calculate which thread finished first second ... etc ?
```

```txt
When printing the results, can you assign a random team name to each thread?
```
