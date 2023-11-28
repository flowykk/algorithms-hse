# Задание А1

## Код программы 
### Полный код программы можно посмотреть в [файле](experiment.cpp) 
Для удобства работы с точками и их координатами я сделал класс `Point`, в котором есть конструктор и два публичных поля - координаты `x` и `y`.
```cpp
class Point {
public:
    double x;
    double y;

    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
};
```

Далее идёт метод `generatePoints()`, который принимает целое число **N** и возвращает вектор из **N** точек со случайно сгенерированными координатами `x` и `y`.
```cpp
std::vector<Point> generatePoints(int N) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    std::vector<Point> points;

    for (int i = 0; i < N; ++i) {
        double x = dis(gen);
        double y = dis(gen);

        Point point = Point(x, y);
        points.push_back(point);
    }

    return points;
}
```
Для подсчёта числа **M**(числа точек, которые находятся внутри круга радиусом 1 и центром в начале координат) используется метод `countM()`, который принимает вектор из точек и возвращает целое число **M**. 
```cpp
int countM(const std::vector<Point>& points) {
    int M = 0;
    for (auto point : points) {
        if (point.x * point.x + point.y * point.y <= 1) {
            M++;
        }
    }
    return M;
}
```
Для проведения самого эксперимента применяется метод `experiment()`, в котором написан цикл для перебора нужного количества сгенированных точек(от 100 до 5000 с шагом 100). На каждой итерации цикла генерируется массив из точек при помощи метода `generatePoints()` длины **N**, подсчитывается число **M** с помощью метода `countM()` и наконец-то считается результат - приблизительное значение числа **pi** формулой `pi = 4M / N`.
```cpp
void experiment() {
    for (int N = 100; N <= 5000; N += 100) {
        std::vector<Point> points = generatePoints(N);
        int M = countM(points);

        double pi = (4.0 * M) / N;
        std::cout << N << " " << pi << "\n";
    }
}
```


