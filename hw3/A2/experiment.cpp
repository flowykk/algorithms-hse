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

    std::uniform_int_distribution<> swap_count(5, 20);
    int swaps = swap_count(gen);

    for (int i = 0; i < swaps; ++i) {
        int index1 = std::rand() % N;
        int index2 = std::rand() % N;

        int temp = array[index1];
        array[index1] = array[index2];
        array[index2] = temp;
    }

    return array;
}

// Функция для сортировки вставками
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Перемещаем элементы массива, которые больше key, на одну позицию вперед
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Функция для слияния двух отсортированных массивов
void merge(std::vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Создаем временные вспомогательные массивы
    std::vector<int> leftArray(n1);
    std::vector<int> rightArray(n2);

    // Копируем данные во временные массивы leftArray[] и rightArray[]
    for (int i = 0; i < n1; i++) {
        leftArray[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = arr[middle + 1 + j];
    }

    // Объединяем временные массивы обратно в основной массив arr[]
    int i = 0; // Индекс первого подмассива (leftArray)
    int j = 0; // Индекс второго подмассива (rightArray)
    int k = left; // Индекс объединенного массива (arr)

    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            arr[k] = leftArray[i];
            i++;
        } else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Копируем оставшиеся элементы leftArray[], если они есть
    while (i < n1) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    // Копируем оставшиеся элементы rightArray[], если они есть
    while (j < n2) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

// Рекурсивная функция сортировки слиянием
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        // Находим середину массива
        int middle = left + (right - left) / 2;

        // Рекурсивно сортируем две половины
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        // Объединяем отсортированные половины
        merge(arr, left, middle, right);
    }
}

void mergePlusInsertionSort(std::vector<int>& arr, int minSize, int left, int right) {
    if (arr.size() < minSize) {
        insertionSort(arr);
    }
    else {
        if (left < right) {
            // Находим середину массива
            int middle = left + (right - left) / 2;

            // Рекурсивно сортируем две половины
            mergePlusInsertionSort(arr, minSize, left, middle);
            mergePlusInsertionSort(arr, minSize, middle + 1, right);

            // Объединяем отсортированные половины
            merge(arr, left, middle, right);
        }
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

void experimentMerge() {
    int maxN = 4000;
    std::vector<int> array1case = generateArray1Case(maxN);
    std::vector<int> array2case = generateArray2Case(maxN);
    std::vector<int> array3case = generateArray3Case(maxN);
    print(array2case);

    for (int N = 500; N <= maxN; N += 100) {
        std::vector<int> array1 = cutArray(array1case, maxN, N);
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(array1, 0, array1.size() - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec1case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::vector<int> array2 = cutArray(array1case, maxN, N);
        start = std::chrono::high_resolution_clock::now();
        mergeSort(array2, 0, array2.size() - 1);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec2case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::vector<int> array3 = cutArray(array1case, maxN, N);
        start = std::chrono::high_resolution_clock::now();
        mergeSort(array3, 0, array3.size() - 1);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec3case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::cout << "N: " << N << "; time: " << millisec1case << " " << millisec2case << " " << millisec3case << std::endl;
    }
}

void experimentMergePlusInsertion(int minSize) {
    int maxN = 4000;
    std::vector<int> array1case = generateArray1Case(maxN);
    std::vector<int> array2case = generateArray2Case(maxN);
    std::vector<int> array3case = generateArray3Case(maxN);

    for (int N = 500; N <= maxN; N += 100) {
        std::vector<int> array1 = cutArray(array1case, maxN, N);
        auto start = std::chrono::high_resolution_clock::now();
        mergePlusInsertionSort(array1, minSize, 0, array1.size() - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec1case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::vector<int> array2 = cutArray(array1case, maxN, N);
        start = std::chrono::high_resolution_clock::now();
        mergePlusInsertionSort(array2, minSize, 0, array2.size() - 1);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec2case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::vector<int> array3 = cutArray(array1case, maxN, N);
        start = std::chrono::high_resolution_clock::now();
        mergePlusInsertionSort(array3, minSize, 0, array3.size() - 1);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec3case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::cout << "N: " << N << "; time: " << millisec1case << " " << millisec2case << " " << millisec3case
                  << std::endl;
    }
}

int main() {
    //experimentMerge();
    //experimentMergePlusInsertion();

    std::vector<int> array = generateArray1Case(100);

    int minSize = 20;
    // Вызываем функцию сортировки вставками
    mergePlusInsertionSort(array, minSize, 0, array.size() - 1);

    std::cout << "\nОтсортированный массив: ";
    for (int num : array) {
        std::cout << num << " ";
    }

    return 0;
}
