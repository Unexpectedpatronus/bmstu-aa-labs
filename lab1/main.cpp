#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <fstream>

LARGE_INTEGER getPerformanceCounter() {
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return count;
}

double getTimeDiff(LARGE_INTEGER start, LARGE_INTEGER end, LARGE_INTEGER frequency) {
    return static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
}

void BubbleSort(std::vector<int> &array) {
    for (size_t i = 0; i < array.size() - 1; ++i) {
        for (size_t j = 0; j < array.size() - 1 - i; ++j) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
            }
        }
    }
}

void InsertionSort(std::vector<int> &array) {
    for (size_t step = 1; step < array.size(); ++step) {
        int elem = array[step];
        int j = step - 1;
        while (j >= 0 && array[j] > elem) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = elem;
    }
}

void ShellSort(std::vector<int> &array) {
    int N = array.size();
    for (int gap = N / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < N; i++) {
            int temp = array[i];
            int j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                array[j] = array[j - gap];
            }
            array[j] = temp;
        }
    }
}

std::vector<int> generateRandomArray(int size) {
    std::vector<int> array(size);
    for (int &num: array) {
        num = rand() % 100000; // Генерим от 0 до 999999
    }
    return array;
}

std::vector<int> ASC(const std::vector<int> &array) {
    std::vector<int> sorted = array;
    std::sort(sorted.begin(), sorted.end());
    return sorted;
}

std::vector<int> DESC(const std::vector<int> &array) {
    std::vector<int> sorted = array;
    std::sort(sorted.begin(), sorted.end(), std::greater<>());
    return sorted;
}

void printArray(const std::vector<int> &array) {
    for (int i = 0; i < array.size(); ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

double measureSortingTime(void (*sortFunction)(std::vector<int> &), std::vector<int> array) {
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);

    double totalTime = 0;
    int runs = 5;
    for (int i = 0; i < runs; ++i) {
        std::vector<int> temp = array;
        //printArray(temp);
        LARGE_INTEGER start = getPerformanceCounter();
        sortFunction(temp);
        LARGE_INTEGER end = getPerformanceCounter();
        totalTime += getTimeDiff(start, end, frequency);
    }
    return totalTime / runs;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    std::vector<int> sizes = {100, 150, 200, 250, 300};
    std::ofstream file("sorting_times.csv");
    file << "Size,Case,BubbleSort,InsertionSort,ShellSort\n";

    for (int size: sizes) {
        std::vector<int> randArray = generateRandomArray(size);
        std::vector<int> bestArray = ASC(randArray);
        std::vector<int> worstArray = DESC(randArray);

        double timeBubbleRand = measureSortingTime(BubbleSort, randArray);
        double timeInsertionRand = measureSortingTime(InsertionSort, randArray);
        double timeShellRand = measureSortingTime(ShellSort, randArray);

        double timeBubbleBest = measureSortingTime(BubbleSort, bestArray);
        double timeInsertionBest = measureSortingTime(InsertionSort, bestArray);
        double timeShellBest = measureSortingTime(ShellSort, bestArray);

        double timeBubbleWorst = measureSortingTime(BubbleSort, worstArray);
        double timeInsertionWorst = measureSortingTime(InsertionSort, worstArray);
        double timeShellWorst = measureSortingTime(ShellSort, worstArray);

        file << size << ",Random," << timeBubbleRand << "," << timeInsertionRand << "," << timeShellRand << "\n";
        file << size << ",Best," << timeBubbleBest << "," << timeInsertionBest << "," << timeShellBest << "\n";
        file << size << ",Worst," << timeBubbleWorst << "," << timeInsertionWorst << "," << timeShellWorst << "\n";

        std::cout << "Size " << size << " done.\n";
    }

    file.close();
    std::cout << "Data saved to sorting_times.csv\n";

    return 0;
}
