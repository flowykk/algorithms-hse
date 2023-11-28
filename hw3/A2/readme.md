# Задание А2

## Код программы 
### Полный код программы можно посмотреть в [файле](experiment.cpp) 
Для начала были реализованы две сортировки из условия задачи по отдельности - **mergeSort** и **insertionSort**.

**mergeSort** - сортировка состоящая из двух методов - `mergeSort()` и `merge()`, рассмотрим каждый из них по-отдельности.

`mergeSort()`:
```cpp
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
```

`merge()`:
```cpp
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
```

`insertionSort`:
```cpp
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
```

Для удобства проведения эксперимента и дальнейшего анализа был написан метод `mergePlusInsertionSort()`, который осуществляет гибридную **Merge+Insertion** сортировку.
```cpp
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
```

Для создания тестовых векторов я написал 3 метода: для генерации массивов максимальной длины(4000), которые заполняются случайными значениями в диапазоне от 0 до 3000 согласно условию.

1. Метод `generateArray1Case()` для генерации массива, где сгенерированные числа неупорядочены.
    ```cpp
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
    ```

2. Метод `generateArray2Case()` для генерации массива, где сгенерированные числа упорядочены по невозрастанию в обратном порядке при помощи встроенной сортировки `std::sort()`.
    ```cpp
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
    ```

3. Метод `generateArray3Case()` для генерации массива, который отсортирован в порядке неубывания при помощи встроенной сортировки `std::sort()`.
    ```cpp
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
    ```
    
    Для того, чтобы сделать массив из полученного массива "почти" отсортированны, позже будет применяться метод `makeAlmostSorted()`, который выбирает рандомным образом от 10 до 30 пар элементов, которые нужно переставить местами.
    ```cpp
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
    ```

Для выбора подмассивов нужной длины **N** из массива максимальной длины **4000** написан метод `cutArray()`, который выбирает рандомно начало нужного массива.
```cpp
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
```

Для измерения времени работы реализации алгоритмов **mergeSort** и **mergePlusInsertionSort** было написано два отдельных метода:

метод `experimentMerge()`. Где **maxN** - максимальная длина генерируемых массивов, **array1case**, **array2case** и **array3case** - тестовые данные, которые созданы согласно условию с помощью выше описанных методов. В методе присутсвует цикл, в котором перебираются длины генерируемых массивов (от 500 до 4000 с шагом 100). В цикле же каждый из массивов из входных данных "обрезается" по длине **N** с помощью вышеописанного метода `cutArray()`, и над полученными массивами ведутся вычисления времени работы сортировки ***mergeSort**, а результат в конце метода выводится на экран.
```cpp
void experimentMerge(int maxN, std::vector<int> array1case, std::vector<int> array2case, std::vector<int> array3case) {
    for (int N = 500; N <= maxN; N += 100) {
        std::vector<int> array1 = cutArray(array1case, maxN, N);
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(array1, 0, array1.size() - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec1case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::vector<int> array2 = cutArray(array2case, maxN, N);
        start = std::chrono::high_resolution_clock::now();
        mergeSort(array2, 0, array2.size() - 1);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec2case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::vector<int> array3 = cutArray(array3case, maxN, N);
        start = std::chrono::high_resolution_clock::now();
        mergeSort(array3, 0, array3.size() - 1);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec3case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::cout << "N: " << N << "; time: " << millisec1case << " " << millisec2case << " " << millisec3case << std::endl;
    }
}
```

метод `experimentMergePlusInsertion()`. Написан аналогично предыдущему методу. Отличия - аргумент **minSize** - размер массива, при котором будет использоваться сортировка **insertionSort**, а внутри цикла используется метод `mergePlusInsertionSort()` для гибридной сортировки массива.
```cpp
void experimentMergePlusInsertion(int minSize, int maxN, std::vector<int> array1case, std::vector<int> array2case, std::vector<int> array3case) {
    for (int N = 500; N <= maxN; N += 100) {
        std::vector<int> array1 = cutArray(array1case, maxN, N);
        auto start = std::chrono::high_resolution_clock::now();
        mergePlusInsertionSort(array1, minSize, 0, array1.size() - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec1case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::vector<int> array2 = cutArray(array2case, maxN, N);
        start = std::chrono::high_resolution_clock::now();
        mergePlusInsertionSort(array2, minSize, 0, array2.size() - 1);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec2case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::vector<int> array3 = cutArray(array3case, maxN, N);
        makeAlmostSorted(array3);
        start = std::chrono::high_resolution_clock::now();
        mergePlusInsertionSort(array3, minSize, 0, array3.size() - 1);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec3case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::cout << "N: " << N << "; time: " << millisec1case << " " << millisec2case << " " << millisec3case << std::endl;
    }
}
```

## Анализ результатов 

