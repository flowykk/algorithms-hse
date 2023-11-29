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
### Excel-файл, в котором я строил все графики и в котором приведены полученные из программы данные можно посмотреть [тут](A2.xlsx).

### Анализ стандартной **mergeSort**:

Сначала я запустил алгоритм 4 раза, занёс данные в Excel и усреднил. Получились следующие значения, где в столбцах №1, №2, №3 - значения времени работы сортировки в милисекундах для каждого из видов тестовых данных: 
```
N	№1	№2	№3
500	0	0	0
600	0	0	0
700	0	0	0
800	0	0	0
900	0,25	0,25	0
1000	0,25	0,25	0
1100	0	0	0
1200	1	0,75	0,5
1300	1	1	1
1400	1	1	1
1500	1,25	1	1
1600	1,5	1,25	1
1700	1	1	1,25
1800	1,25	1	1,5
1900	1,5	1	1
2000	1,75	1,25	1,25
2100	1,5	1,25	1,5
2200	2	1,5	1,75
2300	2	2	2
2400	2	2,25	2,25
2500	2,25	2	2
2600	2	2	2
2700	2	2	2
2800	2,25	2	2
2900	2	2	2
3000	2	2	2,25
3100	3	2,5	2,5
3200	3	2,5	2
3300	3	2,5	2,25
3400	3	2	2,25
3500	3	3	2,75
3600	3	3	3
3700	3	3	3,25
3800	3	3	3
3900	3	3	3
4000	3,5	3,25	3![image](https://github.com/flowykk/algorithms-hse/assets/71427624/178a7ec1-98bb-45e1-9500-7761fd5c8a45)

```

#### Рассмотрим результат на графиках
Тестовые данные №1:
![1](https://github.com/flowykk/algorithms-hse/assets/71427624/55f0d7c2-71c5-434c-80ff-00bb65b80094)

Тестовые данные №2:
![2](https://github.com/flowykk/algorithms-hse/assets/71427624/48800290-9608-43a6-aaa3-a3f37b332a8f)

Тестовые данные №3:
![3](https://github.com/flowykk/algorithms-hse/assets/71427624/60068208-97bf-4b6d-8da7-c6499b085430)

### Анализ гибридной **mergePlusInsertionSort**:

Сначала я запустил алгоритм 4 раза для каждого значения minSize (5, 10, 15, 20), занёс данные в Excel и усреднил. Теперь приведу получившиеся значения и построенные графики:

### *minSize = 5*

#### Усреднённые значения: 
```
N	№1	№2	№3
500	0	0	0
600	0	0	0
700	0	0	0
800	0,33	0	0
900	0,33	0	0
1000	0,33	0,33	0,33
1100	0,67	0,67	0,67
1200	1	0,67	1
1300	1	1	1
1400	1	1	1
1500	1	1	1
1600	1	1	1
1700	1	1	1
1800	1	1	1
1900	1,33	1	1
2000	1,33	1,67	1
2100	1,67	1	1
2200	2	1,33	1
2300	2	2	1,33
2400	2	2	2
2500	2	2	2
2600	2	2	2
2700	2	2	2
2800	2,33	2	2
2900	2,33	2	2
3000	2	2	2
3100	3	2	2
3200	3	2	2,33
3300	3	2,33	2,67
3400	3	2,67	2,67
3500	3	3	3
3600	3	3	3
3700	3,33	3	3
3800	4	3	3
3900	3	3	3,33
4000	3,67	3,33	3
```

#### Тестовые данные №1:
![1](https://github.com/flowykk/algorithms-hse/assets/71427624/dbe5df10-972c-48f0-a451-ad453c2e65fa)

#### Тестовые данные №2:
![2](https://github.com/flowykk/algorithms-hse/assets/71427624/e3530496-1cab-42c3-8d40-d3222d30e982)

#### Тестовые данные №3:
![3](https://github.com/flowykk/algorithms-hse/assets/71427624/43f418de-6fa3-4eab-a5a4-a1e0503a5356)

### *minSize = 10*

#### Усреднённые значения: 
```
500	0	0	0
600	0	0	0
700	0	0	0
800	0	0	0
900	1	0,67	0,33
1000	0,33	0,33	0,33
1100	1	0	0
1200	1	0,33	0,67
1300	1	1	1
1400	1	1	1
1500	1	1	1
1600	1	1	1
1700	1,67	1,33	1
1800	1,33	1	1
1900	1	1	1,33
2000	1,67	1,67	1
2100	2,33	1,33	1,33
2200	2	1,67	1,67
2300	2	1,67	2
2400	2,33	2	2
2500	2	2	2
2600	2	2	2
2700	2,67	2	2,33
2800	2,33	2	2,33
2900	2,33	2,33	2,67
3000	3	2,67	2,33
3100	3	2,67	2,33
3200	3	3	2,33
3300	3	2	2,33
3400	3,33	2,67	3
3500	3	3	3,33
3600	3,33	3	3
3700	3,33	3	3
3800	3	3,33	3
3900	3	3	3
4000	3,33	3,33	3
```

#### Тестовые данные №1:
![1](https://github.com/flowykk/algorithms-hse/assets/71427624/7aeac3d5-bf3b-4410-911d-28c746d0ede2)

#### Тестовые данные №2:
![2](https://github.com/flowykk/algorithms-hse/assets/71427624/3835636c-1e4d-4164-b081-65b64c755850)

#### Тестовые данные №3:
![3](https://github.com/flowykk/algorithms-hse/assets/71427624/aa3510df-dd03-46af-9eb0-829799ab5720)

### *minSize = 15*

#### Усреднённые значения: 
```
N	№1	№2	№3
500	0	0	0
600	0	0	0
700	0	0	0
800	0	0	0
900	0	0	0
1000	0	0	0
1100	0	0,33	0
1200	1	0,33	0,33
1300	1	1	1
1400	1	1	1
1500	1	1	1
1600	1,33	1	1
1700	1	1	1
1800	1	1	1
1900	1	1	1,33
2000	2	1,33	1
2100	1,67	2	2
2200	2	1,67	1
2300	2	1,67	1,67
2400	2	2	2
2500	2	2	2,67
2600	2,67	3,33	3
2700	2,67	2,67	3
2800	3	3,33	2,67
2900	3	2,33	2,33
3000	3	2,67	2,67
3100	3	2,33	2,67
3200	2,67	2,67	2,67
3300	3	3	2,67
3400	3	2,67	2,33
3500	3	3,33	4
3600	3,33	3,33	3
3700	3	3	3
3800	3	3	3
3900	3	3	3
4000	3	3	3
```

#### Тестовые данные №1:
![1](https://github.com/flowykk/algorithms-hse/assets/71427624/c53b44cb-e3cb-44bb-a663-29d14c10c0b9)

#### Тестовые данные №2:
![2](https://github.com/flowykk/algorithms-hse/assets/71427624/2750f4ef-2ddc-4d8f-9be8-d116eeed4167)

#### Тестовые данные №3:
![3](https://github.com/flowykk/algorithms-hse/assets/71427624/13d3cb30-be08-48eb-afc8-ff1d22bd9ed0)


### *minSize = 20*

#### Усреднённые значения: 
```
N	№1	№2	№3
500	0	0	0
600	0	0	0
700	0	0	0
800	0	0	0
900	0,33	0	0
1000	0,33	0,33	0
1100	0,33	0,33	0,33
1200	1	0,33	0,67
1300	1	1	1
1400	1	1	1
1500	1	1	1
1600	1	1	1
1700	1	1	1,33
1800	1	1	1
1900	1	1,67	1,33
2000	1,33	1,33	1,33
2100	1,33	1,33	1,33
2200	2	1,33	1,67
2300	2	1,67	2
2400	2	2	2
2500	2	2	2
2600	2	2	2
2700	2	2	2,33
2800	2,33	2	2,33
2900	2	2	2,33
3000	3	2,33	2,33
3100	2,33	2,33	2,33
3200	3,67	3	4,67
3300	3,67	2,67	2,67
3400	3	2,67	2,67
3500	3	3	3
3600	3	3	3
3700	3	3	3
3800	3,33	3	3
3900	3,33	3,67	3
4000	3,67	3	3,33
```

#### Тестовые данные №1:
![1](https://github.com/flowykk/algorithms-hse/assets/71427624/9713bd33-7d5c-4403-9539-227418d57f08)

#### Тестовые данные №2:
![2](https://github.com/flowykk/algorithms-hse/assets/71427624/e628b164-b437-49ac-bb62-4800ad5fd8e5)

#### Тестовые данные №3:
![3](https://github.com/flowykk/algorithms-hse/assets/71427624/4bac2fed-c0c6-4637-9bb6-26427f3f7c7b)

## Вывод:
