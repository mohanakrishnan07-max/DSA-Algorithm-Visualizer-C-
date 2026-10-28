#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

struct Step
{
    vector<int> values;
    int first;
    int second;
    string message;
};

class Visualizer
{
private:
    vector<Step> steps;
    int current;
    string algorithm;

    void record(const vector<int> &a, int i, int j, const string &message)
    {
        steps.push_back({a, i, j, message});
    }

    void bubbleSort(vector<int> a)
    {
        int n = (int)a.size();
        record(a, -1, -1, "Starting Bubble Sort.");
        for (int i = 0; i < n - 1; ++i)
        {
            bool swapped = false;
            for (int j = 0; j < n - i - 1; ++j)
            {
                record(a, j, j + 1, "Compare " + to_string(a[j]) + " and " + to_string(a[j + 1]) + ".");
                if (a[j] > a[j + 1])
                {
                    swap(a[j], a[j + 1]);
                    swapped = true;
                    record(a, j, j + 1, "They are out of order. Swap them.");
                }
                else
                {
                    record(a, j, j + 1, "They are already in order. No swap.");
                }
            }
            if (!swapped)
                break;
        }
        record(a, -1, -1, "Bubble Sort finished.");
    }

    void selectionSort(vector<int> a)
    {
        int n = (int)a.size();
        record(a, -1, -1, "Starting Selection Sort.");
        for (int i = 0; i < n - 1; ++i)
        {
            int minIndex = i;
            record(a, i, minIndex, "Assume index " + to_string(i) + " has the minimum value.");
            for (int j = i + 1; j < n; ++j)
            {
                record(a, minIndex, j, "Compare current minimum " + to_string(a[minIndex]) + " with " + to_string(a[j]) + ".");
                if (a[j] < a[minIndex])
                {
                    minIndex = j;
                    record(a, i, minIndex, "Found a smaller value. Update minimum index.");
                }
            }
            if (minIndex != i)
            {
                swap(a[i], a[minIndex]);
                record(a, i, minIndex, "Swap the minimum value into position " + to_string(i) + ".");
            }
            else
            {
                record(a, i, minIndex, "Minimum is already in the correct position.");
            }
        }
        record(a, -1, -1, "Selection Sort finished.");
    }

    void insertionSort(vector<int> a)
    {
        int n = (int)a.size();
        record(a, -1, -1, "Starting Insertion Sort.");
        for (int i = 1; i < n; ++i)
        {
            int key = a[i];
            int j = i - 1;
            record(a, i, j, "Take " + to_string(key) + " as the key. Check the sorted part on its left.");
            while (j >= 0 && a[j] > key)
            {
                a[j + 1] = a[j];
                record(a, j, j + 1, "Shift " + to_string(a[j]) + " one position to the right.");
                --j;
            }
            a[j + 1] = key;
            record(a, j + 1, i, "Insert key " + to_string(key) + " at index " + to_string(j + 1) + ".");
        }
        record(a, -1, -1, "Insertion Sort finished.");
    }

    void linearSearch(const vector<int> &a, int target)
    {
        record(a, -1, -1, "Starting Linear Search for " + to_string(target) + ".");
        for (int i = 0; i < (int)a.size(); ++i)
        {
            record(a, i, -1, "Check index " + to_string(i) + ": value is " + to_string(a[i]) + ".");
            if (a[i] == target)
            {
                record(a, i, -1, "Target found at index " + to_string(i) + ".");
                return;
            }
        }
        record(a, -1, -1, "Target was not found.");
    }

    void binarySearch(vector<int> a, int target)
    {
        for (int i = 0; i < (int)a.size(); ++i)
            for (int j = i + 1; j < (int)a.size(); ++j)
                if (a[i] > a[j])
                    swap(a[i], a[j]);
        record(a, -1, -1, "Binary Search uses a sorted array. The values are shown sorted.");

        int left = 0, right = (int)a.size() - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            record(a, left, right, "Search range: [" + to_string(left) + ", " + to_string(right) + "]. Middle index = " + to_string(mid) + ".");
            record(a, mid, -1, "Compare middle value " + to_string(a[mid]) + " with target " + to_string(target) + ".");
            if (a[mid] == target)
            {
                record(a, mid, -1, "Target found at sorted index " + to_string(mid) + ".");
                return;
            }
            else if (a[mid] < target)
            {
                left = mid + 1;
                record(a, left, right, "Target is larger. Move left boundary to mid + 1.");
            }
            else
            {
                right = mid - 1;
                record(a, left, right, "Target is smaller. Move right boundary to mid - 1.");
            }
        }
        record(a, -1, -1, "Target was not found.");
    }

    void showStep() const
    {
        if (steps.empty())
            return;
        const Step &s = steps[current];
        cout << "\n==================================================\n";
        cout << algorithm << " | Step " << current + 1 << " of " << steps.size() << "\n";
        cout << s.message << "\n\nArray: ";
        for (int i = 0; i < (int)s.values.size(); ++i)
        {
            bool highlighted = (i == s.first || i == s.second);
            if (highlighted)
                cout << "[" << s.values[i] << "] ";
            else
                cout << s.values[i] << " ";
        }
        cout << "\n(Values in [brackets] are highlighted.)\n";
        cout << "==================================================\n";
    }

public:
    Visualizer() : current(0) {}

    void run(const vector<int> &input, int choice, int target = 0)
    {
        steps.clear();
        current = 0;
        switch (choice)
        {
        case 1:
            algorithm = "Bubble Sort";
            bubbleSort(input);
            break;
        case 2:
            algorithm = "Selection Sort";
            selectionSort(input);
            break;
        case 3:
            algorithm = "Insertion Sort";
            insertionSort(input);
            break;
        case 4:
            algorithm = "Linear Search";
            linearSearch(input, target);
            break;
        case 5:
            algorithm = "Binary Search";
            binarySearch(input, target);
            break;
        default:
            return;
        }

        while (true)
        {
            showStep();
            cout << "\nControls: [N]ext  [P]revious  [R]estart  [M]enu\nChoose: ";
            char command;
            cin >> command;
            command = (char)tolower(command);
            if (command == 'n')
            {
                if (current + 1 < (int)steps.size())
                    ++current;
                else
                    cout << "You are at the last step.\n";
            }
            else if (command == 'p')
            {
                if (current > 0)
                    --current;
                else
                    cout << "You are at the first step.\n";
            }
            else if (command == 'r')
            {
                current = 0;
            }
            else if (command == 'm')
            {
                return;
            }
            else
            {
                cout << "Invalid command. Please choose N, P, R, or M.\n";
            }
        }
    }
};

int main()
{
    cout << "==============================================\n";
    cout << "       DSA ALGORITHM VISUALIZER (C++)\n";
    cout << "==============================================\n";

    while (true)
    {
        int n;
        cout << "\nEnter number of array elements (1 to 20): ";
        if (!(cin >> n))
            return 0;
        if (n < 1 || n > 20)
        {
            cout << "Please enter a size from 1 to 20.\n";
            continue;
        }

        vector<int> values(n);
        cout << "Enter " << n << " integers separated by spaces: ";
        for (int i = 0; i < n; ++i)
            cin >> values[i];

        cout << "\nChoose an algorithm:\n";
        cout << "1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n";
        cout << "4. Linear Search\n5. Binary Search (input will be sorted first)\n6. Exit\n";
        cout << "Choice: ";
        int choice;
        cin >> choice;
        if (choice == 6)
        {
            cout << "Thank you for using the visualizer!\n";
            break;
        }
        if (choice < 1 || choice > 5)
        {
            cout << "Invalid choice. Try again.\n";
            continue;
        }

        int target = 0;
        if (choice == 4 || choice == 5)
        {
            cout << "Enter target value to search: ";
            cin >> target;
        }

        Visualizer visualizer;
        visualizer.run(values, choice, target);
    }
    return 0;
}
