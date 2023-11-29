#include <iostream>
#include <vector>
#include <random>

std::vector<int> generateArray1Case(int N) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3000);

    std::vector<int> array;

    for (int i = 0; i < N; ++i) {
        int el = dis(gen);
        array.push_back(el);
    }

    return array;
}

std::vector<int> generateArray2Case(int N) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3000);

    std::vector<int> array;

    for (int i = 0; i < N; ++i) {
        int el = dis(gen);
        array.push_back(el);
    }

    std::sort(array.rbegin(), array.rend());

    return array;
}

std::vector<int> generateArray3Case(int N) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3000);

    std::vector<int> array;

    for (int i = 0; i < N; ++i) {
        int el = dis(gen);
        array.push_back(el);
    }

    std::sort(array.begin(), array.end());

    return array;
}

void makeAlmostSorted(std::vector<int>& array) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(10, 30);
    int swaps = dis(gen);

    for (int i = 0; i < swaps; ++i) {
        int index1 = std::rand() % array.size();
        int index2 = std::rand() % array.size();

        int temp = array[index1];
        array[index1] = array[index2];
        array[index2] = temp;
    }
}

// Функция для разделения массива на две части относительно опорного элемента
int partition(std::vector<int>& array, int low, int high) {
    int pivot = array[low];
    int i = low + 1;
    int j = high;

    while (true) {
        // Находим элемент слева, который больше или равен опорному
        while (i <= j && array[i] <= pivot) {
            i++;
        }

        // Находим элемент справа, который меньше или равен опорному
        while (array[j] >= pivot && j >= i) {
            j--;
        }

        // Если i и j не пересеклись, меняем элементы местами
        if (j < i) {
            break;
        } else {
            std::swap(array[i], array[j]);
        }
    }

    // Помещаем опорный элемент на правильное место
    std::swap(array[low], array[j]);

    return j;
}

// Рекурсивная функция для сортировки массива с использованием быстрой сортировки
void quickSort(std::vector<int>& array, int low, int high) {
    if (low < high) {
        // Находим индекс опорного элемента после разделения массива
        int pivot_index = partition(array, low, high);

        // Рекурсивно сортируем две части массива
        quickSort(array, low, pivot_index - 1);
        quickSort(array, pivot_index + 1, high);
    }
}

void heapify(std::vector<int>& array, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && array[left] > array[largest]) {
        largest = left;
    }

    if (right < n && array[right] > array[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(array[i], array[largest]);

        heapify(array, n, largest);
    }
}

void heapSort(std::vector<int>& array, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

void quickPlusHeapSort(std::vector<int>& array, int minSize, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);

        if (pi - low < minSize)
            heapSort(array, pi - low);
        else
            quickSort(array, low, pi - 1);

        if (high - pi < minSize)
            heapSort(array, high - pi - 1);
        else
            quickSort(array, pi + 1, high);
    }
}

std::vector<int> cutArray(std::vector<int> array, int maxN, int N) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, maxN - N);
    int start = dis(gen);

    std::vector<int> result;

    for (int i = start; i < start + N; ++i) {
        result.push_back(array[i]);
    }

    return result;
}

void print(const std::vector<int>& array) {
    std::cout << "array: " << std::endl;
    for (int num : array) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void experimentQuick(int maxN, const std::vector<int>& array1case, const std::vector<int>& array2case, const std::vector<int>& array3case) {
    for (int N = 500; N <= maxN; N += 100) {
        std::vector<int> array1 = cutArray(array1case, maxN, N);
        auto start = std::chrono::high_resolution_clock::now();
        quickSort(array1, 0, array1.size() - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec1case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::vector<int> array2 = cutArray(array2case, maxN, N);
        start = std::chrono::high_resolution_clock::now();
        quickSort(array2, 0, array2.size() - 1);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec2case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::vector<int> array3 = cutArray(array3case, maxN, N);
        start = std::chrono::high_resolution_clock::now();
        quickSort(array3, 0, array3.size() - 1);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec3case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::cout << millisec1case << " " << millisec2case << " " << millisec3case << std::endl;
    }
}

void experimentQuickPlusHeap(int minSize, int maxN, const std::vector<int>& array1case, const std::vector<int>& array2case, const std::vector<int>& array3case) {
    for (int N = 500; N <= maxN; N += 100) {
        std::vector<int> array1 = cutArray(array1case, maxN, N);
        auto start = std::chrono::high_resolution_clock::now();
        quickPlusHeapSort(array1, minSize, 0, array1.size() - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec1case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::vector<int> array2 = cutArray(array2case, maxN, N);
        start = std::chrono::high_resolution_clock::now();
        quickPlusHeapSort(array2, minSize, 0, array2.size() - 1);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec2case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::vector<int> array3 = cutArray(array3case, maxN, N);
        makeAlmostSorted(array3);
        start = std::chrono::high_resolution_clock::now();
        quickPlusHeapSort(array3, minSize, 0, array3.size() - 1);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec3case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::cout << millisec1case << " " << millisec2case << " " << millisec3case << std::endl;
    }
}

int main() {
    int maxN = 4000;
    std::vector<int> array1case = generateArray1Case(maxN);
    std::vector<int> array2case = generateArray2Case(maxN);
    std::vector<int> array3case = generateArray3Case(maxN);

    //experimentQuick(maxN, array1case, array2case, array3case);

    int minSize = 50;
    experimentQuickPlusHeap(minSize, maxN, array1case, array2case, array3case);

    return 0;
}
