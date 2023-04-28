#include <omp.h>
#include <iostream>
#include <cmath>

using namespace std;
int f(int val)
{
    for (int i = 0; i < 10 ^ 6; i++)
    {
        val += -sin(val);
    }

    return val;
}

int main()
{
    int a[100], b[100];
    // Инициализация массива b
    for (int i = 0; i < 100; i++)
        b[i] = i;

#pragma omp parallel for
    for (int i = 0; i < 100; i++)
    {
        a[i] = f(b[i]);
        b[i] = 2 * a[i];
    }
    int result = 0;

#pragma omp parallel for reduction(+ \
                                   : result)
    for (int i = 0; i < 100; i++)
        result += (a[i] + b[i]);
    cout << "Result = " << result << endl;

    return 0;
}