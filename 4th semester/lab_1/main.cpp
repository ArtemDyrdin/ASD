#include <iostream>
#include <vector>
#include <random>
#include <Windows.h>

#define POINTS 20
#define BLUE 1
#define RED 4

HANDLE m_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void drawPoint(std::pair<int, int> &point, int Color) {
    SetConsoleTextAttribute(m_hStdOut, static_cast<int>(Color));
    SetConsoleCursorPosition(m_hStdOut, {static_cast<short>(point.first * 2 + POINTS), static_cast<short>(point.second)});
    std::cout << '*';
}

void makeSetPoints(std::vector<std::pair<int, int>>& points) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, POINTS);
    for (int i = 0; i < POINTS; ++i) {
        int random_x = distribution(gen);
        int random_y = distribution(gen);
        points.emplace_back(random_x, random_y);
    }
    for (auto& point: points)
        drawPoint(point, BLUE);
}

int orientation(std::pair<int, int>& p, std::pair<int, int>& q, std::pair<int, int>& r) {
    int value = (q.second - p.second) * (r.first - q.first) - (q.first - p.first) * (r.second - q.second);
    if (value == 0)
        return 0;
    else if (value > 0)
        return 1;
    else return 2;
}

std::vector<std::pair<int, int>> getConvexHull(std::vector<std::pair<int, int>>& points) {
    int n = static_cast<int>(points.size());
    if (n < 3) return {};

    std::vector<std::pair<int, int>> hull; // вектор точек оболочки

    // Находим самую левую точку
    int leftmost = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].first < points[leftmost].first)
            leftmost = i;
    }

    int p = leftmost; // текущая точка
    int q; // следующая точка

    // Проходим по всем точкам оболочки
    do {
        // Добавляем текущую точку в результат
        hull.push_back(points[p]);
        drawPoint(points[p], RED);

        // Находим следующую точку в оболочке
        q = (p + 1) % n; // Используем операцию модуля, чтобы перейти к следующей точке
        for (int i = 0; i < n; i++)
            if (orientation(points[p], points[i], points[q]) == 2)
                q = i;
        p = q;

    } while (p != leftmost); // Повторяем, пока не вернемся к начальной точке

    return hull;
}

int main() {
    std::vector<std::pair<int, int>> points;
    makeSetPoints(points);
    getConvexHull(points);
    SetConsoleTextAttribute(m_hStdOut, static_cast<int>(7));
    SetConsoleCursorPosition(m_hStdOut, {static_cast<short>(0), static_cast<short>(POINTS)});
    return 0;
}