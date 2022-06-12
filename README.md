# Randomization

### NOTE:
### This was part of a group project in which I and one collaborator each developed our own randomization algorithms with the goal of maximizing randomness and efficiency (and without using built-in randomness).
### I excluded the collaborator's algorithm, but everything else is almost exactly the same.
### The purpose of main.cpp was to test each of our algorithms, which I decided to do with different sizes of Collections and different starting sortedness states. This main.cpp does so with only my own algorithm.

### Metric, Results, and Analysis
* For our metric, I decided to use a combination of two different measurements: runtime complexity (measured in milliseconds) and 'well-randomness,' which we define as the items being as evenly distributed as possible (in terms of their indexes after randomization) after many runs of the randomization algorithm.
* To measure the runtime, I used the chrono class to set timers. Specifically, I started a timer right before each run of an algorithm, and ended it right after. I compiled these results after every run of both algorithms, putting them into a matrix with the first axis representing the test 'case' (e.g. small sorted deck) and the second axis representing the iteration of the test for that case. At the end, I took the minimums, maximums, and averages of all the runtimes for each case, which represent the best-case, worst-case, and average-case runtimes respectively.
* To measure the 'well-randomness,' I kept a matrix with the first axis representing the test 'case' and the second axis representing the old (before randomizing) index of each item. I kept a history of each item's old (before randomizing) and new (after randomizing) indexes as a vector field in the Collection class. After each randomization algorithm run, the values in this vector field (which represent the new positions for each old index) were added to the existing elements in the corresponding vector (representing the test 'case') in the matrix (that is to say, I added the new values element-wise to the existing values, *not* to the end of the vector). I then displayed the resulting vectors to show the user the distributions of how each item's position was randomized.
* Analyzing the results, it was clear that the runtime of gdlevineRandomize was faster than that of the collaborator's algorithm in all cases. Regarding the distributions of items' positions, for gdlevineRandomize, the numbers were fairly similar, indicating that the items' new positions were fairly evenly distributed. This was true in all cases.

### References
* I spent a few hours learning all about std::chrono, which I ended up using to implement my gdlevineRandomize method. The code I used to get the current time in nanoseconds is based on the following:
https://stackoverflow.com/questions/27677964

* https://www.geeksforgeeks.org/stdmt19937-class-in-cpp/  
* https://www.cplusplus.com/reference/chrono/
