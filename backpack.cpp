#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Структура для описания предмета
struct Item {
    int weight;
    int value;
};

// Функция для вычисления максимальной стоимости, которую можно получить, заполнив рюкзак
int knapsack(int W, vector<Item> &items) {
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
    cout << "Выбранные предметы: ";
    for (int i = n; i > 0 && res > 0; i--) {
        if (res == dp[i - 1][w])
            continue;
        else {
            // Этот предмет включен
            cout << "(вес: " << items[i - 1].weight << ", стоимость: " << items[i - 1].value << ") ";
            // Так как этот предмет включен, его стоимость вычитается
            res = res - items[i - 1].value;
            w = w - items[i - 1].weight;
        }
    }
    cout << endl;

    return dp[n][W];
}

int main() {
    int W = 13; // Вместимость рюкзака

    // Список предметов: {вес, стоимость}
    vector<Item> items = {
            {3, 1},
            {4, 6},
            {5, 4},
            {8, 7},
            {9, 6}
    };

    // Вычисление и вывод максимальной стоимости, которую можно получить
    int max_value = knapsack(W, items);
    cout << "Максимальная стоимость, которую можно получить: " << max_value << endl;

    return 0;
}
