# Задание А1

## Тестовые данные и результаты работы программ

- Данные с видом генерации №1 в [файле](Data/data-case1.md)
- Данные с видом генерации №2 в [файле](Data/data-case2.md)
- Данные с видом генерации №3 в [файле](Data/data-case3.md)

- Примерный результат работы experimentQuickSort в [файле](Data/result-quickSort.md)
- Примерный результат работы experimentStringQuickSort в [файле](Data/result-stringQuickSort.md)
- Примерный результат работы experimentMergeSort в [файле](Data/result-mergeSort.md)

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

### Графики

<div align="center">
  <img src="https://github.com/flowykk/algorithms-hse/assets/71427624/690d6af5-ef59-4126-95de-caca38d5492f" width="500"> 
  <img src="https://github.com/flowykk/algorithms-hse/assets/71427624/290f0815-2884-4c39-aee7-9c2cbb5cdee1" width="500"> 
</div>

### Вывод

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

### Графики

<div align="center">
  <img src="https://github.com/flowykk/algorithms-hse/assets/71427624/449fb256-d3a6-464f-a96c-7e042bb936c6" width="500"> 
  <img src="https://github.com/flowykk/algorithms-hse/assets/71427624/5483c051-4170-45ff-8338-22b9c6a06c17" width="500"> 
</div>

### Вывод

Одно из главных отличий алгоритма `stringQuickSort` от обычного `quickSort` заключается в том, что он основан на тернарном алгоритме, в котором разбиение выполняется по текущему символу сравниваемых строк. Это дает прирост в скорости алгоритма, а также уменьшает количество посимвольных сравнений строк засчет того, что в этом пропадает необходимость.

## Анализ DefaultMergeSort

Метод `experimentMergeSort()`:


```cpp
void experimentMergeSort(StringGenerator generator, int maxN, const vector<string>& array1case, const vector<string>& array2case, const vector<string>& array3case) {
    for (int N = 100; N <= maxN; N += 100) {
        size_t opers1 = 0;
        std::vector<string> array1 = generator.cutArray(array1case, maxN, N);
        auto start = std::chrono::high_resolution_clock::now();
        DefaultMergeSort::mergeSort(array1, 0, N - 1, opers1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec1case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        size_t opers2 = 0;
        std::vector<string> array2 = generator.cutArray(array2case, maxN, N);
        start = std::chrono::high_resolution_clock::now();
        DefaultMergeSort::mergeSort(array2, 0, N - 1, opers2);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec2case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        size_t opers3 = 0;
        std::vector<string> array3 = generator.cutArray(array3case, maxN, N);
        start = std::chrono::high_resolution_clock::now();
        DefaultMergeSort::mergeSort(array3, 0, N - 1, opers3);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec3case = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::cout << "N = " << N << " (" << millisec1case << ", " << opers1 << "), ("<< millisec2case << ", " << opers2 << "), (" << millisec3case << ", " << opers3 << ")" << std::endl;
        //std::cout << N << " " << millisec1case << " " << millisec2case << " " << millisec3case << std::endl;
    }
}
```

### Графики

<div align="center">
  <img src="https://github.com/flowykk/algorithms-hse/assets/71427624/1d52bd5a-4d16-4877-a458-d59b24625465" width="500"> 
  <img src="https://github.com/flowykk/algorithms-hse/assets/71427624/a069a894-d0d4-47f2-8a61-2468e9ec1d63" width="500"> 
</div>

### Вывод:

Смотря на графики можно понять, что на неупорядоченном наборе данных сортировка слиянием работает чуть медленнее, чем в остальных случаях. Это происходит, потому что на неупорядоченном массиве `mergeSort` часто разделяет и сливает элементы, даже если они близки по значению, также затрачиывается больше памяти и ресурсов на рекурсию. Это вызывает дополнительные операции. В упорядоченных массивах (особенно в обратном порядке), меньше слияний, так как большинство элементов уже находятся в нужной позиции. В "почти" отсортированном массиве также меньше перестановок, что ускоряет сортировку.
По тем же причинам количество посимволньных сравнений во время работы такой сортировки для тестового набора №1 выше, чем для наборов №2 и №3.
