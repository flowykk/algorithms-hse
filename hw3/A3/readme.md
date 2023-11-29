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
![1](https://github.com/flowykk/algorithms-hse/assets/71427624/11d36f4a-a222-4ee0-a204-53f9c1e2a0b2)


#### Тестовые данные №2:
![2](https://github.com/flowykk/algorithms-hse/assets/71427624/89bd4def-3df3-4539-8d55-929ad70c3083)


#### Тестовые данные №3:
![3](https://github.com/flowykk/algorithms-hse/assets/71427624/6c6cbcc8-4f6d-43a1-962c-4dcc1f8834ef)

Смотря на эти графики и усреднённые значения можно сделать следующий вывод: В случае с наборами данных №2 и №3 QuickSort приходит к худшему случаю, ведь выбирая опорный элемент деление массива в этих ситуациях становится неэффективным. А с тестовыми данными №1, где элементы неупорядочены, опорные элементы лучше распределены, а это в свою очередь приводит к лучшей производительности. 

### Анализ гибридной **quickPlusHeapSort**:

Сначала я запустил алгоритм 4 раза для каждого значения minSize (5, 10, 20, 50), занёс данные в Excel и усреднил. Теперь приведу получившиеся значения и построенные графики:

### *minSize = 5*

#### Усреднённые значения: 
```

```

#### Тестовые данные №1:

#### Тестовые данные №2:

#### Тестовые данные №3:

### *minSize = 10*

#### Усреднённые значения: 
```

```

#### Тестовые данные №1:

#### Тестовые данные №2:

#### Тестовые данные №3:

### *minSize = 20*

#### Усреднённые значения: 
```

```

#### Тестовые данные №1:

#### Тестовые данные №2:

#### Тестовые данные №3:


### *minSize = 50*

#### Усреднённые значения: 
```

```

#### Тестовые данные №1:

#### Тестовые данные №2:

#### Тестовые данные №3:

## Вывод:
Быстрая сортировка имеет сложность O(n log n) в лучшем случае, а в худшем случае O(n^2). В случае заранее упорядоченных данных (тестовые наборы №2 и №3), QuickSort приходит к худшему случаю. В первом случае элементы случайны, что обеспечивает лучший случай.
