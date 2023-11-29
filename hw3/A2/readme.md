# Задание А2

## Код программы 
### Полный код программы можно посмотреть в [файле](experiment.cpp) 
Для начала были реализованы две сортировки из условия задачи по отдельности - **mergeSort** и **insertionSort**.

**mergeSort** - сортировка состоящая из двух методов - `mergeSort()` и `merge()`, ниже приведён каждый из них по-отдельности.

`mergeSort()`:
```cpp
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}
```

`merge()`:
```cpp
void merge(std::vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<int> leftArray(n1);
    std::vector<int> rightArray(n2);

    for (int i = 0; i < n1; i++) {
        leftArray[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = arr[middle + 1 + j];
    }

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

    while (i < n1) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}
```

`insertionSort()` - здесь этот метод выполняет сортировку нужной части массива от `left` до `right`:
```cpp
void insertionSort(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key) {
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
    if (right - left <= minSize) {
        insertionSort(arr, left, right);
    } else {
        if (left < right) {
            int middle = left + (right - left) / 2;

            mergePlusInsertionSort(arr, minSize, left, middle);
            mergePlusInsertionSort(arr, minSize, middle + 1, right);

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

Для измерения времени работы реализации алгоритмов **mergeSort** и **mergePlusInsertionSort** было написано два отдельных метода:

Метод `experimentMerge()`. Где **maxN** - максимальная длина генерируемых массивов, **array1case**, **array2case** и **array3case** - тестовые данные, которые созданы согласно условию с помощью выше описанных методов. В методе присутсвует цикл, в котором перебираются длины генерируемых массивов (от 500 до 4000 с шагом 100). В цикле же каждый из массивов из входных данных "обрезается" по длине **N** с помощью вышеописанного метода `cutArray()`, и над полученными массивами ведутся вычисления времени работы сортировки **mergeSort**, а результат в конце метода выводится на экран.
```cpp
void experimentMerge(int maxN, const std::vector<int>& array1case, const std::vector<int>& array2case, const std::vector<int>& array3case) {
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

        std::cout << N << " " << millisec1case << " " << millisec2case << " " << millisec3case << std::endl;
    }
}
```

Метод `experimentMergePlusInsertion()`. Написан аналогично предыдущему методу. Отличия - аргумент **minSize** - размер массива, при котором будет использоваться сортировка **insertionSort**, а внутри цикла используется метод `mergePlusInsertionSort()` для гибридной сортировки массива.
```cpp
void experimentMergePlusInsertion(int minSize, int maxN, const std::vector<int>& array1case, const std::vector<int>& array2case, const std::vector<int>& array3case) {
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

        std::cout << millisec1case << " " << millisec2case << " " << millisec3case << std::endl;
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
4000	3,5	3,25	3
```

### Рассмотрим результат на графиках
#### Тестовые данные №1:
![1](https://github.com/flowykk/algorithms-hse/assets/71427624/b2d7c219-6821-45ab-87f5-065d80c1a85d)


#### Тестовые данные №2:
![2](https://github.com/flowykk/algorithms-hse/assets/71427624/a12d6ad1-91b0-46bb-bf7c-54b894718d6f)


#### Тестовые данные №3:
![3](https://github.com/flowykk/algorithms-hse/assets/71427624/270be363-00fb-4bae-af03-55dec728d7c5)

Смотря на графики можно понять, что на неупорядоченном наборе данных сортировка слиянием работает чуть медленнее, чем в остальных случаях. Это происходит, потому что на неупорядоченном массиве **MergeSort** часто разделяет и сливает элементы, даже если они близки по значению, также затрачиывается больше памяти и ресурсов на рекурсию. Это вызывает дополнительные операции. В упорядоченных массивах (особенно в обратном порядке), меньше слияний, так как большинство элементов уже находятся в нужной позиции. В "почти" отсортированном массиве также меньше перестановок, что ускоряет сортировку.

### Анализ гибридной **mergePlusInsertionSort**:

Сначала я запустил алгоритм 4 раза для каждого значения minSize (5, 10, 20, 50), занёс данные в Excel и усреднил. Теперь приведу получившиеся значения и построенные графики:

### *minSize = 5*

#### Усреднённые значения: 
```
N	№1	№2	№3
500	0	0	0
600	0	0	0
700	0	0	0
800	0	0	0
900	0	0	0
1000	0	0	0
1100	0	0	0
1200	0	0	0
1300	0	0	0
1400	0	0	0
1500	0	0	0
1600	0	0	0
1700	0,25	0	0
1800	0,5	0	0
1900	0,25	0	0
2000	0	0	0
2100	0	0	0,25
2200	0,25	0	0
2300	0,75	0,25	0,5
2400	1	0,5	0
2500	1	0	1
2600	1	0,5	1
2700	1	1	1
2800	1	1	1
2900	1	1	1
3000	1	1	1
3100	1	1	1
3200	1	1	1
3300	1	1	1
3400	1	1	1
3500	1,25	1	1,25
3600	1	1	1
3700	1,25	1,25	1,25
3800	1,5	1	1
3900	1,75	1	1
4000	1,75	1,25	1,25
```

#### Тестовые данные №1:
![1](https://github.com/flowykk/algorithms-hse/assets/71427624/af3efe1f-8e01-4583-82bc-80605007a9e0)

#### Тестовые данные №2:
![2](https://github.com/flowykk/algorithms-hse/assets/71427624/b54235ed-3576-4a08-a712-bcdb1030a5f0)

#### Тестовые данные №3:
![3](https://github.com/flowykk/algorithms-hse/assets/71427624/7d8eb659-302a-4f21-bb87-2a49ce03b56b)

Здесь же, как и было сказано в условии, засчёт вызова **insertionSort** при небольших рамзерах массивов, гибридная сортировка выполняет заметно быстрее, чем стандартная сортировка **mergeSort** даже при `minSize = 5`, ведь в таком случае происходит меньше операций слияния, меньше затрат на рекурсию. Тоже самое будет происходить и при остальных значениях `minSize`, только там разница во времени со стандартной сортировкой слиянием будет видна ещё лучше, особенно при `minSize = 50`.

### *minSize = 10*

#### Усреднённые значения: 
```
N	№1	№2	№3
500	0	0	0
600	0	0	0
700	0	0	0
800	0	0	0
900	0	0	0
1000	0	0	0
1100	0	0	0
1200	0	0	0
1300	0	0	0
1400	0	0	0
1500	0	0	0
1600	0	0	0
1700	0	0	0
1800	0	0	0
1900	0	0	0
2000	0	0	0
2100	0	0	0
2200	0,25	0,25	0
2300	0,25	0	0
2400	0	0	0
2500	0	0	0
2600	0	0	0
2700	0,25	0	0,5
2800	0	0	0,25
2900	1	0	0,5
3000	1	1	1
3100	1	1	1
3200	1	1	1
3300	1	1	1
3400	1	1	1
3500	1	1	1
3600	1	1	1
3700	1	1	1
3800	1	1	1
3900	1	1	1
4000	1	1	1
```

#### Тестовые данные №1:
![1](https://github.com/flowykk/algorithms-hse/assets/71427624/690d6705-36a2-4c7a-897e-c21669738dcb)

#### Тестовые данные №2:
![2](https://github.com/flowykk/algorithms-hse/assets/71427624/13ded4fd-d204-40fd-ac1d-4561279ca0f6)

#### Тестовые данные №3:
![3](https://github.com/flowykk/algorithms-hse/assets/71427624/81c5bd2b-bfd1-4acd-b0c1-0dae548d1818)

### *minSize = 20*

#### Усреднённые значения: 
```
N	№1	№2	№3
500	0	0	0
600	0	0	0
700	0	0	0
800	0	0	0
900	0	0	0
1000	0	0	0
1100	0	0	0
1200	0	0	0
1300	0	0	0
1400	0	0	0
1500	0	0	0
1600	0	0	0
1700	0	0	0
1800	0	0	0
1900	0	0	0
2000	0	0	0
2100	0	0	0
2200	0	0	0
2300	0	0	0
2400	0	0	0
2500	0	0	0
2600	0	0	0
2700	0	0	0
2800	0,25	0	0
2900	0	0,5	0,5
3000	0,25	0	0,5
3100	0,5	0,25	0,25
3200	1	0,5	0,25
3300	1	0,25	0,75
3400	1	0,5	0,75
3500	1	0,5	1
3600	1	1	1
3700	1	1	1
3800	1	1	1
3900	1	1	1
4000	1	1	1
```

#### Тестовые данные №1:
![1](https://github.com/flowykk/algorithms-hse/assets/71427624/15a86fa7-2da7-4043-8fbd-2b4fd27e5318)

#### Тестовые данные №2:
![2](https://github.com/flowykk/algorithms-hse/assets/71427624/41063f08-53e2-43d8-90ca-c4d3b0e35286)

#### Тестовые данные №3:
![3](https://github.com/flowykk/algorithms-hse/assets/71427624/161d2f6b-ef26-4a97-a814-5d7b31bff758)


### *minSize = 50*

#### Усреднённые значения: 
```
N	№1	№2	№3
500	0	0	0
600	0	0	0
700	0	0	0
800	0	0	0
900	0	0	0
1000	0	0	0
1100	0	0	0
1200	0	0	0
1300	0	0	0
1400	0	0	0
1500	0	0	0
1600	0	0	0
1700	0	0	0
1800	0	0	0
1900	0	0	0
2000	0	0	0
2100	0	0	0
2200	0	0	0
2300	0	0	0
2400	0	0	0
2500	0	0	0
2600	0	0	0
2700	0	0	0
2800	0	0	0
2900	0	0	0
3000	0	0	0
3100	0	0	0
3200	0	0	0
3300	0	0	0
3400	0,25	0,25	0
3500	0,25	0	0
3600	0	0,25	0
3700	0,25	0	0
3800	0,5	0,5	0,5
3900	0,5	0	0
4000	0,5	0,25	0,25
```

#### Тестовые данные №1:
![1](https://github.com/flowykk/algorithms-hse/assets/71427624/5a9350f6-5755-4576-a180-86e2cf83f275)

#### Тестовые данные №2:
![2](https://github.com/flowykk/algorithms-hse/assets/71427624/b804ecd3-81ee-41a6-bbb6-6271cda921ac)

#### Тестовые данные №3:
![3](https://github.com/flowykk/algorithms-hse/assets/71427624/8b688dad-c855-4ba1-b4d0-358373f11801)

## Вывод:
В конечном итоге можно сделать вывод о том, что гибридная сортировка работает быстрее стандартной, ведь при небольших объёмах данных мы избегаем лишних затрат дополнительной память, лишние операции слияния, выполняемые при помощи `merge()`. Также стоит учитывать, что разница во времени работы между алгоритмами **mergeSort** и **mergePlusInsertionSort** происходит и за счет лучшей оценки константы у **insertionSort**.
