#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Структура для описания предмета
struct Item {
    int weight;
    int value;
};

struct FloatItem {
    int value;
    double weight;
};

// Функция для нахождения НОД
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Функция для нахождения НОК
int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

// Функция для нахождения НОК для массива чисел
int findLCM(const std::vector<int>& denominators) {
    int result = denominators[0];
    for (size_t i = 1; i < denominators.size(); ++i) {
        result = lcm(result, denominators[i]);
    }
    return result;
}

// Функция для преобразования вещественных чисел в дроби и нахождения знаменателей
std::vector<int> findDenominators(const std::vector<double>& numbers) {
    std::vector<int> denominators;
    for (double num : numbers) {
        double intpart, fracpart;
        fracpart = modf(num, &intpart);
        int denominator = 1;

        while (fracpart != 0) {
            num *= 10;
            fracpart = modf(num, &intpart);
            denominator *= 10;
        }

        denominators.push_back(denominator);
    }
    return denominators;
}

// Основная функция для получения целых чисел из вещественных
std::vector<int> getIntegerMultiples(const std::vector<double>& numbers) {
    std::vector<int> denominators = findDenominators(numbers);
    int commonDenominator = findLCM(denominators);

    std::vector<int> integerNumbers;
    for (double num : numbers) {
        integerNumbers.push_back(static_cast<int>(num * commonDenominator));
    }
    return integerNumbers;
}

// Функция для вычисления максимальной стоимости, которую можно получить, заполнив рюкзак
std::pair<int, int> knapsack(int W, vector<Item> &items) {
    int n = items.size();
    // Создание таблицы для динамического программирования
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Заполнение таблицы
    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Восстановление выбранных предметов
    int res = dp[n][W];
    int w = W;
    int sumWeights = 0;
    cout << "Выбранные предметы: " << endl;
    for (int i = n; i > 0 && res > 0; i--) {
        if (res == dp[i - 1][w])
            continue;
        else {
            // Этот предмет включен
            cout << "Предмет: №" << i << ", цена: " << items[i - 1].value << ", вес: " << items[i - 1].weight << endl;
            sumWeights += items[i - 1].weight;
            // Так как этот предмет включен, его стоимость вычитается
            res = res - items[i - 1].value;
            w = w - items[i - 1].weight;
        }
    }

    return {dp[n][W], sumWeights};
}

vector<Item> proceed(const vector<FloatItem>& floatItems) {
    vector<double> weights;
    for (int i = 0; i < floatItems.size(); i++) {
        weights.push_back(floatItems[i].weight);
    }

    vector<int> intWeights = getIntegerMultiples(weights);

    vector<Item> items;
    for (int i = 0; i < floatItems.size(); i++) {
        Item item = {intWeights[i], floatItems[i].value};
        items.push_back(item);
    }

    return items;
}

int main() {
    int W = 10; // Вместимость рюкзака

    // Список предметов: {вес, стоимость}
    vector<FloatItem> floatItems = {
            {40, 2},
            {50, 3.14},
            {100, 1.98},
            {95, 5},
            {30, 3}
    };

    cout << "Измененные значения: " << endl;
    vector<Item> items = proceed(floatItems);
    for (int i = 0; i < items.size(); i++) {
        cout << "Предмет: №" << i + 1 << ", цена: " << items[i].value << ", вес: " << items[i].weight << endl;
    }

    int denom = static_cast<int>(items[0].weight / floatItems[0].weight);
    W *= denom;
    cout << "Общий множитель весов: " << denom << endl;
    cout << "Обновленная вместимость рюкзака: " << W << endl;

        // Вычисление и вывод максимальной стоимости, которую можно получить
    cout << endl;
    std::pair<int, int> knapsackResult = knapsack(W, items);
    int maxValue = knapsackResult.first;
    int sumWeights = knapsackResult.second;
    cout << "\nПолученный суммарный вес (с учетом общего множителя): " << sumWeights << endl;
    cout << "Полученная максимальная прибыль (с учетом общего множителя): " << maxValue << endl;

    cout << "\nПолученный суммарный вес (без учета общего множителя): " << static_cast<double>(sumWeights) / denom << endl;
    cout << "Полученная максимальная прибыль (без учета общего множителя): " << static_cast<double>(maxValue) / denom << endl;

    return 0;
}
