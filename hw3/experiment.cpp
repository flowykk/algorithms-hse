#include <iostream>
#include <random>

class Point {
public:
    double x;
    double y;

    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
};

int countM(const std::vector<Point>& points) {
    int M = 0;
    for (auto point : points) {
        if (point.x * point.x + point.y * point.y <= 1) {
            M++;
        }
    }
    return M;
}

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

void experiment() {
    for (int N = 100; N <= 5000; N += 100) {
        std::vector<Point> points = generatePoints(N);
        int M = countM(points);

        double pi = (4.0 * M) / N;
        std::cout << N << " " << pi << "\n";
    }
}

int main() {
    experiment();

    return 0;
}
