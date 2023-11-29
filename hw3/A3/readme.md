# Задание A3

## Код программы 
### Полный код программы можно посмотреть в [файле](experiment.cpp) 
Для начала были реализованы две сортировки из условия задачи по отдельности - **quickSort** и **heapSort**.

**quickSort** - сортировка состоящая из двух методов - `quickSort()` и `partition()`, рассмотрим каждый из них по-отдельности.

`quickSort()`:
```cpp
void quickSort(std::vector<int>& array, int low, int high) {
    if (low < high) {
        int pivot_index = partition(array, low, high);

        quickSort(array, low, pivot_index - 1);
        quickSort(array, pivot_index + 1, high);
    }
}
```

`partition()`:
```cpp
int partition(std::vector<int>& array, int low, int high) {
    int pivot = array[low];
    int i = low + 1;
    int j = high;

    while (true) {
        while (i <= j && array[i] <= pivot) {
            i++;
        }

        while (array[j] >= pivot && j >= i) {
            j--;
        }

        if (j < i) {
            break;
        } else {
            std::swap(array[i], array[j]);
        }
    }

    std::swap(array[low], array[j]);

    return j;
}
```

**heapSort** - сортировка состоящая из двух методов - `heapSort()` и `heapify()`, рассмотрим каждый из них по-отдельности.

`heapSort()`:
```cpp
void heapSort(std::vector<int>& array, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}
```

`heapify()`:
```cpp
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
```

Для удобства проведения эксперимента и дальнейшего анализа был написан метод `quickPlusHeapSort()`, который осуществляет гибридную **Quick+Heap** сортировку.
```cpp
void quickPlusHeapSort(std::vector<int>& array, int minSize, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);

        if (pi - low < minSize)
        {
            heapSort(array, pi - low);
        } else {
            quickSort(array, low, pi - 1);
        }

        if (high - pi < minSize)
        {
            heapSort(array, high - pi - 1);
        } else {
            quickSort(array, pi + 1, high);
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
    
    Для того, чтобы сделать из полученного массива "почти" отсортированный массив, позже будет применяться метод `makeAlmostSorted()`, который выбирает рандомным образом от 10 до 30 пар элементов, которые нужно переставить местами.
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

Для измерения времени работы реализации алгоритмов **quickSort** и **quickPlusHeapSort** было написано два отдельных метода:

Метод `experimentQuick()`. Где **maxN** - максимальная длина генерируемых массивов, **array1case**, **array2case** и **array3case** - тестовые данные, которые созданы согласно условию с помощью выше описанных методов. В методе присутсвует цикл, в котором перебираются длины генерируемых массивов (от 500 до 4000 с шагом 100). В цикле же каждый из массивов из входных данных "обрезается" по длине **N** с помощью вышеописанного метода `cutArray()`, и над полученными массивами ведутся вычисления времени работы сортировки ***mergeSort**, а результат в конце метода выводится на экран.
```cpp
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
```

Метод `experimentQuickPlusHeap()`. Написан аналогично предыдущему методу. Отличия - аргумент **minSize** - размер массива, при котором будет использоваться сортировка **insertionSort**, а внутри цикла используется метод `mergePlusInsertionSort()` для гибридной сортировки массива.
```cpp
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
```

## Анализ результатов 
### Excel-файл, в котором я строил все графики и в котором приведены полученные из программы данные можно посмотреть [тут](A2.xlsx).

### Анализ стандартной **heapSort**:

Сначала я запустил алгоритм 4 раза, занёс данные в Excel и усреднил. Получились следующие значения, где в столбцах №1, №2, №3 - значения времени работы сортировки в милисекундах для каждого из видов тестовых данных: 
```
N	№1	№2	№3
500	0	0	0
600	0	0	0
700	0	0,25	0
800	0	0,5	0
900	0	1	0
1000	0	1	0
1100	0	1,75	0,75
1200	0	2	1
1300	0	3	1,25
1400	0	2,5	1,25
1500	0	3,75	1,5
1600	0	3,5	2
1700	0	4,5	2
1800	0	4,5	2,75
1900	0	5,75	3
2000	0	6,25	3,25
2100	0	6,5	3,25
2200	0	7,25	3,75
2300	0	7,75	4
2400	0	8,5	4,25
2500	0	10	5
2600	0	10,25	5,25
2700	0	10,75	5,5
2800	0	12	6,25
2900	0	12,75	6,25
3000	0	15,5	7,5
3100	0	14,5	8,25
3200	0	15,75	9,25
3300	0	16,25	8,5
3400	0	17,25	9,5
3500	0	20,25	9,5
3600	0	19,5	10,5
3700	0	20,5	11
3800	0	21,5	12,75
3900	0	24,75	12,75
4000	0	23,75	12,75
```

### Рассмотрим результат на графиках
#### Тестовые данные №1:
![image](https://github.com/flowykk/algorithms-hse/assets/71427624/bac1647d-80cb-4ad8-8665-c93f09561fb4)

#### Тестовые данные №2:
![image](https://github.com/flowykk/algorithms-hse/assets/71427624/ae1904c3-0ad2-4557-bb24-643907509d3b)

#### Тестовые данные №3:
![image](https://github.com/flowykk/algorithms-hse/assets/71427624/00c76591-7a41-4341-821b-5e76d16c93b3)

Смотря на эти графики и усреднённые значения можно сделать следующий вывод: В случае с наборами данных №2 и №3 QuickSort приходит к худшему случаю, ведь выбирая опорный элемент деление массива в этих ситуациях становится неэффективным. А с тестовыми данными №1, где элементы неупорядочены, опорные элементы лучше распределены, а это в свою очередь приводит к лучшей производительности. 

### Анализ гибридной **quickPlusHeapSort**:

Сначала я запустил алгоритм 4 раза для каждого значения minSize (5, 10, 20, 50), занёс данные в Excel и усреднил. Теперь приведу получившиеся значения и построенные графики:

### *minSize = 5*

#### Усреднённые значения: 
```
N	№1	№2	№3
500	0	0	0
600	0	0	0
700	0	0	0
800	0	0,25	0
900	0	1	0
1000	0	1,25	0
1100	0	1,25	0
1200	0	2	0
1300	0	2	0
1400	0	2	0
1500	0	3	0
1600	0	3,25	0
1700	0	4,25	0
1800	0	4,5	0,5
1900	0	5,5	0
2000	0	6	0,25
2100	0	6	0,75
2200	0	7,25	0,5
2300	0	7,25	1,5
2400	0	8,25	1,25
2500	0	9,5	1,25
2600	0	9,75	1
2700	0	11	1,5
2800	0	11,25	1
2900	0	12,5	1,25
3000	0	13,75	2,5
3100	0	15,25	1,75
3200	0	15	2,25
3300	0	17,25	2,5
3400	0	17	2,25
3500	0	18,75	2,5
3600	0	20	3
3700	0	20,25	2,25
3800	0	22,75	4
3900	0	23	3,25
4000	0	24,25	3
```

#### Тестовые данные №1:
![image](https://github.com/flowykk/algorithms-hse/assets/71427624/afa6758f-e75f-42d6-9f68-b2fec35b72ef)

#### Тестовые данные №2:
![image](https://github.com/flowykk/algorithms-hse/assets/71427624/0e6d8386-8fba-490b-a14c-5dc17d4b9e1f)

#### Тестовые данные №3:
![image](https://github.com/flowykk/algorithms-hse/assets/71427624/642269af-66ee-4d7d-9571-9afc934f481b)

### *minSize = 10*

#### Усреднённые значения: 
```
N	№1	№2	№3
500	0	0	0
600	0	0	0
700	0	0	0
800	0	0,75	0
900	0	1	0
1000	0	1	0
1100	0	1,5	0
1200	0	2,25	0
1300	0	2,75	0
1400	0	2,25	0
1500	0	3,5	0,5
1600	0	4	0
1700	0	4,25	0
1800	0	4,75	0,5
1900	0	6,25	0,5
2000	0	8,75	0,5
2100	0	7,5	0,75
2200	0	7	0,75
2300	0	8,5	1,25
2400	0	8,5	0,75
2500	0	9,25	1,25
2600	0	9,75	0,75
2700	0	11	2
2800	0	11,5	1,25
2900	0	12,25	1,25
3000	0	13,25	2,25
3100	0	15,25	2,25
3200	0	16	2,75
3300	0	18,75	2,75
3400	0,25	19,5	2,5
3500	0	19	2,25
3600	0	20,25	3,75
3700	0	21,25	2
3800	0	21,25	3,25
3900	0	22,25	2,5
4000	0	23,25	3
```

#### Тестовые данные №1:

#### Тестовые данные №2:

#### Тестовые данные №3:

### *minSize = 20*

#### Усреднённые значения: 
```
N	№1	№2	№3
500	0	0	0
600	0	0	0
700	0	0	0
800	0	0,25	0
900	0	1	0
1000	0	1,25	0
1100	0	1,75	0
1200	0	2	0
1300	0	2,5	0
1400	0	2,5	0
1500	0	3,5	0
1600	0	5,25	0,25
1700	0	5	0,25
1800	0	6	0
1900	0	5,25	0
2000	0	5,75	0,75
2100	0	6,5	1
2200	0	8	1,5
2300	0	9	0,75
2400	0	9	1
2500	0	10,75	2,25
2600	0	10,5	1,25
2700	0	11,25	1,75
2800	0	11,5	1,5
2900	0	12,75	1,25
3000	0	13,25	2,25
3100	0	15,5	3,75
3200	0	15,75	1,75
3300	0	20,5	2
3400	0	17,5	1,75
3500	0	19	2,5
3600	0	22	2,5
3700	0	21	2,75
3800	0	24,25	3
3900	0	23,75	3,75
4000	0	23,5	3
```

#### Тестовые данные №1:
![image](https://github.com/flowykk/algorithms-hse/assets/71427624/21e4a384-915d-4398-9324-f0ca9fc1eec1)

#### Тестовые данные №2:
![image](https://github.com/flowykk/algorithms-hse/assets/71427624/4864ffe5-372b-48b8-983c-165faf286fe7)

#### Тестовые данные №3:
![image](https://github.com/flowykk/algorithms-hse/assets/71427624/69f276bd-c0ab-4434-81d5-4c8d2932f400)

### *minSize = 50*

#### Усреднённые значения: 
```
N	№1	№2	№3
500	0	0	0
600	0	0	0
700	0	0,25	0
800	0	0,75	0
900	0	1	0
1000	0	1,25	0
1100	0	1,25	0
1200	0	2	0,25
1300	0	2	0
1400	0	2,75	0
1500	0	3,5	0
1600	0	3,5	0
1700	0	4	0
1800	0	5	0
1900	0	5,75	0,5
2000	0	6,5	0,5
2100	0	6,5	1
2200	0	8	0,5
2300	0	8,75	0,75
2400	0	11,25	1,25
2500	0	9,75	1,25
2600	0	9,75	0,75
2700	0	11	1,75
2800	0	12	1,25
2900	0	12,5	1,5
3000	0	13,5	1,75
3100	0	14,25	2,25
3200	0	15	2
3300	0	16	1,75
3400	0	18,75	1,75
3500	0	22,5	2
3600	0	20,5	3,5
3700	0	21,5	2
3800	0	21,5	3
3900	0	25,25	3,75
4000	0	23,75	4,5
```

#### Тестовые данные №1:

#### Тестовые данные №2:

#### Тестовые данные №3:

## Вывод:
Быстрая сортировка имеет сложность O(n log n) в лучшем случае, а в худшем случае O(n^2). В случае заранее упорядоченных данных (тестовые наборы №2 и №3), QuickSort приходит к худшему случаю. В первом случае элементы случайны, что обеспечивает лучший случай.
