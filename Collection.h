#ifndef RANDOMIZATION_COLLECTION_H
#define RANDOMIZATION_COLLECTION_H

/* NOTE: Some of these 'include' statements ('algorithm' and 'random,' I believe) were added by a collaborator for their
 * own different randomization algorithm. I left them all here on the off-chance I used them anywhere in my version.
 */
#include <chrono>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>

using namespace std;

/*
 * Collection Class Contains:
 * Field for Vector of Items
 * Method to Randomize This Collection
 * Method to Sort This Collection
 * Method to Find an Item in This Collection
 * Overloaded << Operator
 */
template <typename Item>
class Collection
{
public:
    // Constructor
    Collection() = default;

    // Getters
    vector<Item> getItems() const
    {
        return items;
    }

    vector<int> getItemsNewPosByOldIndex() const
    {
        return itemsNewPosByOldIndex;
    }

    // Setters
    void setItems(vector<Item> newItems)
    {
        items = newItems;
    }

    void setItemsNewPosByOldIndex(vector<int> newItemsNewPosByOldIndex)
    {
        itemsNewPosByOldIndex = newItemsNewPosByOldIndex;
    }

    /* Gregory Levine's Method to Randomize This Collection
     * Description:
     * This method gets the current time with extreme precision (to the nanosecond),
     * doing so once for each Item in the Collection. It then uses that number of nanoseconds (mod the size of the Collection)
     * as an index for where to place that Item in the randomized version of the Collection. This works because the numbers
     * of nanoseconds that pass between the computations of each current time are massive enough,
     * and thus the precision afforded by measuring in nanoseconds is extreme enough, that the remainder of the number
     * (acquired by modding by the size of the Collection) will be extremely unpredictable.
     * I tested this by printing the numbers of nanoseconds and remainders right after each calculation,
     * and the numbers not only had seemingly no pattern within each run of the method, but there also seemed to be no
     * relationship between what the numbers were after one run and what those same numbers were after a separate run.
     * IMPORTANT NOTE:
     * On certain systems/applications, system_clock precision to the nanosecond isn't properly supported (for example,
     * when running this exact same method on an online compiler (https://www.onlinegdb.com/online_c++_compiler),
     * nanoseconds were supported and were random, but in CLion on my Windows 10 PC, running with nanoseconds results in
     * each number repeating many times before the system 'refreshes' and gets the newest number.
     * So, I added a backup method that uses steady_clock nanoseconds and concatenates with the other time unit values
     * into a long string, substrings of which are converted to ints and used (mod the side of the Collection) as the indexes.
     */
    void gdlevineRandomize()
    {
        // Start timing the program in nanoseconds, to add to the current time in microseconds.
        auto startNano = chrono::steady_clock::now();
        // Keep a vector of randomly-ordered indexes of items in the items vector.
        vector<int> indexes;
        // Keep a vector of whether each randomly-generated index has already been generated before.
        vector<bool> generated(items.size(), false);
        // Generate a random index using the current time in nanoseconds mod the size of the items vector.
        for(int i = 0; i < items.size(); i++)
        {
            // Get the current time.
            auto currentTime = chrono::system_clock::now().time_since_epoch();
            // Get the current number of days since epoch.
            typedef chrono::duration<int, ratio_multiply<chrono::hours::period, ratio<8>>::type> Days;
            Days days = chrono::duration_cast<Days>(currentTime);
            currentTime -= days;
            // Get the current number of hours (mod 24) since epoch.
            auto hours = chrono::duration_cast<chrono::hours>(currentTime);
            currentTime -= hours;
            // Get the current number of minutes (mod 60) since epoch.
            auto minutes = chrono::duration_cast<chrono::minutes>(currentTime);
            currentTime -= minutes;
            // Get the current number of seconds (mod 60) since epoch.
            auto seconds = chrono::duration_cast<chrono::seconds>(currentTime);
            currentTime -= seconds;
            // Get the current number of milliseconds (mod 1,000) since epoch.
            auto milliseconds = chrono::duration_cast<chrono::milliseconds>(currentTime);
            currentTime -= milliseconds;
            // Get the current number of microseconds (mod 1,000,000) since epoch.
            auto microseconds = chrono::duration_cast<chrono::microseconds>(currentTime);
            // If your system supports it, Get the current number of nanoseconds (mod 1,000,000,000) since epoch.
            currentTime -= microseconds;
            auto nanoseconds = chrono::duration_cast<chrono::nanoseconds>(currentTime);
            long index = 0;
            // If your system does support nanoseconds from system_clock, use that number.
            if(nanoseconds.count() != 0)
            {
                // Mod the current number of nanoseconds (mod 1,000,000,000) since epoch by the size of the items vector.
                index = nanoseconds.count() % items.size();
            }
            // If your system doesn't support nanoseconds from system_clock, use relative nanoseconds from steady_clock.
            else
            {
                // Get the current time in nanoseconds since starting the timer.
                nanoseconds = chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - startNano);
                // Concatenate the numbers of time units to form a long string of int values.
                string daysHrsMinsSecsMlsMcsNs = to_string(days.count()) + to_string(hours.count())
                           + to_string(minutes.count()) + to_string(seconds.count()) + to_string(milliseconds.count())
                           + to_string(microseconds.count()) + to_string(nanoseconds.count());
                // Use int index to get an 8-digit substring of the above string.
                int leftStart = daysHrsMinsSecsMlsMcsNs.size() - (i % daysHrsMinsSecsMlsMcsNs.size()) - 8;
                if(leftStart < 0)
                {
                    leftStart = 0;
                }
                int leftLen = daysHrsMinsSecsMlsMcsNs.size() - (i % daysHrsMinsSecsMlsMcsNs.size()) - leftStart;
                int rightStart = daysHrsMinsSecsMlsMcsNs.size() - (8 - leftLen);
                int rightLen = 8 - leftLen;
                string substring = daysHrsMinsSecsMlsMcsNs.substr(rightStart, rightLen)
                        + daysHrsMinsSecsMlsMcsNs.substr(leftStart, leftLen);
                // Convert the string to an int and mod by the size of the items vector.
                index = stoi(substring) % items.size();
            }
            // Make sure the generated index hasn't already been generated before.
            while(generated[index])
            {
                // Increment the index until its value hasn't already been generated before.
                index = (index + 1) % items.size();
            }
            // Add the randomly-generated index to the vector of randomly-ordered indexes.
            indexes.push_back(index);
            // Mark that this randomly-generated index has now been generated at least once.
            generated[index] = true;
        }

        // Make a shallow copy of the items vector in its pre-randomized state.
        vector<Item> itemsBefore(items);
        // Randomize the items vector by using the vector of randomly-generated indexes.
        for(int i = 0; i < indexes.size(); i++)
        {
            // Move each item in the items vector to its corresponding new random index.
            items[i] = itemsBefore[indexes[i]];
        }
        // Keep a history of where each item used to be, and is now, in the items vector.
        itemsNewPosByOldIndex = indexes;
    }

    // Method to Sort This Collection (uses quicksort for efficiency)
    void sort()
    {
        // Choose a pivot index.
        int pivotIndex = items.size() / 2;
        // Swap the pivot Item and the last Item in the vector of items.
        Item pivotItem = items[pivotIndex];
        items[pivotIndex] = items[items.size() - 1];
        items[items.size() - 1] = pivotItem;

        sort(0, items.size() - 1, pivotIndex);
    }

    // Helper Method to Sort a Vector of Items (uses quicksort for efficiency)
    void sort(int startIndex, int endIndex, int pivotIndex)
    {
        // Find the index of the first Item greater than the pivot item in the vector of items.
        int leftGreaterIndex = startIndex;
        while(leftGreaterIndex < endIndex && items[leftGreaterIndex] <= items[endIndex])
        {
            leftGreaterIndex++;
        }
        // Find the index of the last Item less than the pivot item in the vector of items.
        int rightLessIndex = endIndex - 1;
        while(rightLessIndex >= startIndex && items[rightLessIndex] >= items[endIndex])
        {
            rightLessIndex--;
        }
        // If the former index is less than the latter index, swap the items at those two indexes and repeat the sort.
        if(leftGreaterIndex < rightLessIndex)
        {
            Item temp = items[leftGreaterIndex];
            items[leftGreaterIndex] = items[rightLessIndex];
            items[rightLessIndex] = temp;
            sort(startIndex, endIndex, pivotIndex);
        }
        // Otherwise, swap the pivot item and item at the former index, and sort the items before and after it.
        else
        {
            Item temp = items[leftGreaterIndex];
            items[leftGreaterIndex] = items[endIndex];
            items[endIndex] = temp;

            Item pivotItem;
            if(startIndex < leftGreaterIndex - 1)
            {
                // Choose a pivot index.
                int pivotIndexLeft = startIndex + (leftGreaterIndex - startIndex) / 2;
                // Swap the pivot Item and the last Item in the sub-vectors of items.
                pivotItem = items[pivotIndexLeft];
                items[pivotIndexLeft] = items[leftGreaterIndex - 1];
                items[leftGreaterIndex - 1] = pivotItem;

                sort(startIndex, leftGreaterIndex - 1, pivotIndexLeft);
            }
            if(leftGreaterIndex + 1 < endIndex)
            {
                // Choose a pivot index.
                int pivotIndexRight = leftGreaterIndex + 1 + (endIndex - (leftGreaterIndex + 1)) / 2;
                // Swap the pivot Item and the last Item in the sub-vectors of items.
                pivotItem = items[pivotIndexRight];
                items[pivotIndexRight] = items[endIndex];
                items[endIndex] = pivotItem;

                sort(leftGreaterIndex + 1, endIndex, pivotIndexRight);
            }
        }
    }

    // Method to Find an Item in This Collection By Index
    Item findItem(int index) const
    {
        if(index < 0)
        {
            index = 0;
        }
        else if(index >= items.size())
        {
            index = items.size() - 1;
        }
        return items[index];
    }

    // Method to Find the Index of an Item in This Collection
    int findIndex(Item itemToFind) const
    {
        for(int i = 0; i < items.size(); i++)
        {
            if(items[i] == itemToFind)
            {
                return i;
            }
        }
        return -1;
    }

    // Overloaded Operator
    friend ostream& operator << (ostream& outs, const Collection& Collection)
    {
        outs << Collection.items[0];
        for(int i = 1; i < Collection.items.size(); i++)
        {
            outs << ", " << Collection.items[i];
        }
        return outs;
    }

private:
    // Fields
    vector<Item> items;
    vector<int> itemsNewPosByOldIndex;
};

#endif //RANDOMIZATION_COLLECTION_H
