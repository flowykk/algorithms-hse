#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int damerau_levenshtein(const std::string& str1, const std::string& str2) {
    size_t N = str1.length();
    size_t M = str2.length();

    std::vector<std::vector<int>> dp(N + 1, std::vector<int>(M + 1, 0));

    for (int i = 0; i <= N; ++i) dp[i][0] = i;
    for (int j = 0; j <= M; ++j) dp[0][j] = j;

    for (size_t i = 1; i <= N; ++i) {
        for (size_t j = 1; j <= M; ++j) {
            int cost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;

            dp[i][j] = std::min(
                    {dp[i - 1][j] + 1,        // удаление
                     dp[i][j - 1] + 1,           // вставка
                     dp[i - 1][j - 1] + cost     // замена
                     });

            // перестановка соседних символов
            if (i > 1 && j > 1 && str1[i - 1] == str2[j - 2] && str1[i - 2] == str2[j - 1]) {
                dp[i][j] = std::min(dp[i][j], dp[i - 2][j - 2] + cost);
            }
        }
    }

    return dp[N][M];
}

int main() {
    // 2 - удаление, перестановка
    std::cout << "BKASO  ->  KAOS  ->  " << damerau_levenshtein("BKASO", "KAOS") << std::endl;

    // 1 - перестановка
    std::cout << "OS     ->  SO    ->  "<< damerau_levenshtein("OS", "SO") << std::endl;

    // 3 - вставка, удаление, перестановка
    std::cout << "BC     ->  ACBO  ->  "<< damerau_levenshtein("BC", "ACBO") << std::endl;

    // 4 - замена, перестановка
    std::cout << "ABC    ->  AGB   ->  "<< damerau_levenshtein("ABC", "AGB") << std::endl;
    return 0;
}
