# Задание А1

## Код программы 
### Полный код программы можно посмотреть в [файле](experiment.cpp) 
Для начала были реализованы алгоритмы сортировок, каждый из которых реализован в следующих классах: 
- `DefaultQuickSort`
- `DefaultMergeSort`
- `StringQuickSort`

Ниже приведен код для каждого из этих классов:
`DefaultQuickSort`:
```cpp
class DefaultQuickSort {
    public:
    static int partition(vector<string>& arr, int low, int high, size_t &opers) {
        string pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (arr[j] <= pivot) {
                ++i;
                swap(arr[i], arr[j]);
            }
            opers += std::min(arr[i].size(), pivot.size());
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    static void quicksort(vector<string>& arr, int low, int high, size_t &opers) {
        if (low < high) {
            int pi = partition(arr, low, high, opers);
            quicksort(arr, low, pi - 1, opers);
            quicksort(arr, pi + 1, high, opers);
        }
    }
};
```

`DefaultMergeSort`:
```cpp
class DefaultMergeSort {
public:
    static void merge(vector<string>& arr, int left, int mid, int right, size_t &opers) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<string> L(n1);
        vector<string> R(n2);

        for (int i = 0; i < n1; ++i)
            L[i] = arr[left + i];
        for (int i = 0; i < n2; ++i)
            R[i] = arr[mid + 1 + i];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                ++i;
            } else {
                arr[k] = R[j];
                ++j;
            }
            ++k;
            opers += std::min(arr[i].size(), arr[j].size());

        }

        while (i < n1) {
            arr[k] = L[i];
            ++i;
            ++k;
        }

        while (j < n2) {
            arr[k] = R[j];
            ++j;
            ++k;
        }
    }

    static void mergeSort(vector<string>& arr, int left, int right, size_t &opers) {
        if (left >= right)
            return;

        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, opers);
        mergeSort(arr, mid + 1, right, opers);
        merge(arr, left, mid, right, opers);
    }
};
```

`StringQuickSort`:
```cpp
class StringQuickSort {
public:
    static vector<string> stringQuickSort(vector<string> &r, size_t l, size_t &opers) {
        if (r.size() <= 1) return r;
        vector<string> rExcl;
        vector<string> tmp;
        for (size_t i = 0; i < r.size(); i++) {
            if (r[i].size() == l) {
                rExcl.push_back(r[i]);
            } else {
                tmp.push_back(r[i]);
            }
        }

        r = tmp;
        srand(time(nullptr));
        int random = rand() % r.size();
        swap(r[random], r[r.size() - 1]);
        string pivot = r[r.size() - 1];

        auto R_less = vector<string>();
        auto R_equal = vector<string>();
        auto R_great = vector<string>();

        for (size_t i = 0; i < r.size(); i++) {
            if (r[i][l] < pivot[l]) {
                R_less.push_back(r[i]);
                opers++;
            } else if (r[i][l] > pivot[l]) {
                opers += 2;
                R_equal.push_back(r[i]);
            } else {
                opers += 2;
                R_great.push_back(r[i]);
            }
        }
        R_less = stringQuickSort(R_less, l, opers);
        R_equal = stringQuickSort(R_equal, l, opers);
        R_great = stringQuickSort(R_great, l + 1, opers);

        vector<string> result;
        copy(rExcl.begin(), rExcl.end(), back_inserter(result));
        copy(R_less.begin(), R_less.end(), back_inserter(result));
        copy(R_great.begin(), R_great.end(), back_inserter(result));
        copy(R_equal.begin(), R_equal.end(), back_inserter(result));

        return result;
    }
};
```

Для создания тестовых векторов было написано 3 метода: для генерации массивов максимальной длины (3000), которые заполняются случайными значениями в диапазоне от 0 до 3000 согласно условию.

1. Метод `generateArray1Case()` для генерации массива, где сгенерированные строки неупорядочены.
    ```cpp
    vector<string> generateArray1Case(int n) {
        vector<string> array;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> len(10, 200);

        for (int i = 0; i < n; ++i) {
            array.push_back(generateRandomString(len(gen)));
        }

        return array;
    }
    ```

2. Метод `generateArray2Case()` для генерации массива, где сгенерированные строки отсортированы в обратном порядке при помощи встроенной сортировки `std::sort()`.
    ```cpp
    vector<string> generateArray2Case(int n) {
        vector<string> array = generateArray1Case(n);
        sort(array.begin(), array.end());
        reverse(array.begin(), array.end());

        return array;
    }
    ```

3. Метод `generateArray3Case()` для генерации массива, который "почти" отсортирован засчет перестановки некоторых строк массива местами.
    ```cpp
    vector<string> generateArray3Case(int n) {
        vector<string> array = generateArray1Case(n);
        sort(array.begin(), array.end());

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 2);

        int swaps = dis(gen);
        for (int i = 0; i < swaps; ++i) {
            uniform_int_distribution<> dis_n(0, n - 1);
            int idx1 = dis_n(gen);
            int idx2 = dis_n(gen);
            swap(array[idx1], array[idx2]);
        }

        return array;
    }
    ```

Для выбора подмассивов нужной длины **N** из массива максимальной длины **3000** написан метод `cutArray()`, который выбирает рандомно начало нужного массива.
```cpp
vector<string> cutArray(vector<string> array, int maxN, int N) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, maxN - N);
    int start = dis(gen);

    vector<string> result;

    for (int i = start; i < start + N; ++i) {
        result.push_back(array[i]);
    }

    return result;
}
```

## Анализ DefaultQuickSort

Для измерения времени работы реализации алгоритма обычной `quickSort` был написан метод experimentQuickSort():

Метод `experimentMerge()`. Где **maxN** - максимальная длина генерируемых массивов, **array1case**, **array2case** и **array3case** - тестовые данные, которые созданы согласно условию с помощью выше описанных методов. В методе присутсвует цикл, в котором перебираются длины генерируемых массивов (от 100 до 3000 с шагом 100). В цикле же каждый из массивов из входных данных "обрезается" по длине **N** с помощью вышеописанного метода `cutArray()`, и над полученными массивами ведутся вычисления времени работы сортировки **quickSort**, а результат в конце метода выводится на экран.

```cpp
void experimentQuickSort(StringGenerator generator, int maxN, const vector<string>& array1case, const vector<string>& array2case, const vector<string>& array3case) {
    for (int N = 100; N <= maxN; N += 100) {
        size_t opers1 = 0;
        std::vector<string> array1 = generator.cutArray(array1case, maxN, N);
        auto start = std::chrono::high_resolution_clock::now();
        DefaultQuickSort::quicksort(array1, 0, N - 1, opers1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec1case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        size_t opers2 = 0;
        std::vector<string> array2 = generator.cutArray(array2case, maxN, N);
        start = std::chrono::high_resolution_clock::now();
        DefaultQuickSort::quicksort(array2, 0, N - 1, opers2);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec2case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        size_t opers3 = 0;
        std::vector<string> array3 = generator.cutArray(array3case, maxN, N);
        start = std::chrono::high_resolution_clock::now();
        DefaultQuickSort::quicksort(array3, 0, N - 1, opers3);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec3case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::cout << "N = " << N << " (" << millisec1case << ", " << opers1 << "), ("<< millisec2case << ", " << opers2 << "), (" << millisec3case << ", " << opers3 << ")" << std::endl;
        //std::cout << N << " " << millisec1case << " " << millisec2case << " " << millisec3case << std::endl;
    }
}
```

### Вывод:
В случае с наборами данных №2 и №3 QuickSort приходит к худшему случаю, ведь выбирая опорный элемент деление массива в этих ситуациях становится неэффективным. А с тестовыми данными №1, где элементы неупорядочены, опорные элементы лучше распределены, а это в свою очередь приводит к лучшей производительности, поэтому алгоритм выполняется в среднем за пару милисекунд.
По тем же причинам в случаях наоборов данных №2 и №3 производится заметно больше сравнений, чем в случае с набором №1.

## Анализ DefaultQuickSort

Метод `experimentStringQuickSort()`:

```cpp
void experimentStringQuickSort(StringGenerator generator, int maxN, const vector<string>& array1case, const vector<string>& array2case, const vector<string>& array3case) {
    for (int N = 100; N <= maxN; N += 100) {
        size_t opers1 = 0;
        std::vector<string> array1 = generator.cutArray(array1case, maxN, N);
        auto start = std::chrono::high_resolution_clock::now();
        auto res1 = StringQuickSort::stringQuickSort(array1, 0, opers1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec1case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        size_t opers2 = 0;
        std::vector<string> array2 = generator.cutArray(array2case, maxN, N);
        start = std::chrono::high_resolution_clock::now();
        auto res2 = StringQuickSort::stringQuickSort(array2, 0, opers2);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec2case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        size_t opers3 = 0;
        std::vector<string> array3 = generator.cutArray(array3case, maxN, N);
        start = std::chrono::high_resolution_clock::now();
        auto res3 = StringQuickSort::stringQuickSort(array3, 0, opers3);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec3case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::cout << "N = " << N << " (" << millisec1case << ", " << opers1 << "), ("<< millisec2case << ", " << opers2 << "), (" << millisec3case << ", " << opers3 << ")" << std::endl;
        //std::cout << N << " " << millisec1case << " " << millisec2case << " " << millisec3case << std::endl;
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

Здесь же, как и было сказано в условии, засчёт вызова **insertionSort** при небольших рамзерах массивов, гибридная сортировка выполняется заметно быстрее, чем стандартная сортировка **mergeSort** даже при `minSize = 5`, ведь в таком случае происходит меньше операций слияния, меньше затрат на рекурсию. Тоже самое будет происходить и при остальных значениях `minSize`, только там разница во времени со стандартной сортировкой слиянием будет видна ещё лучше, особенно при `minSize = 50`.

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
