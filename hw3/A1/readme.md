# Задание А1

## Код программы 
Для удобства работы с точками и их координатами я сделал класс Point, в котором есть конструктор и два публичных поля - координаты x и y.
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

Далее идёт метод generatePoints, который принимает целое число N и возвращает вектор из N точек со случайно сгенерированными координатами x и y.
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


