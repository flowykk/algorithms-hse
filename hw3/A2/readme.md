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

2. Метод `generateArray2Case()` для генерации массива, где сгенерированные числа упорядочены по невозрастанию в обратном порядке.
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

3. Метод `generateArray3Case()` для генерации массива, который "почти" отсортирован. Для этого в массиве выбирается 
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

    

## Анализ результатов 

