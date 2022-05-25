#include <stdio.h>
#include <math.h>
#define PI 3.14159265358979323846
#define EP 0.0001

int fact(int k)
{
    int f = 1, i;
    for (i = 2; i <= k; i++)
        f = f * i;
    return f;
}

double mycos(double x)
{
    double S = 0, S_1;
    int zn = 1, n = 1, sign = 1;

    //если х меньше 0, берем по модулю
    if (x < 0) x = fabs(x);
    //если x > 2Pi перемещаем в интервал [0..2pi]
    x = fmod(x, 2 * PI);
    //остаток от деления x/(2*pi) , убираем период

    //x > pi перемещаем в интервал [0..pi]
    if (x > PI)
    {
        x = 2 * PI - x;
    // чтобы получить угол от 0 до пи, вычитаем из 2пи найденный угол >пи
    }

    //x > (pi/2) перемещаем в интервал [0..pi/2]
    if (x > (PI / 2))
    {
        x = PI - x;
        sign = sign * (-1);
    //т.к от 0 до пи/2 знак + а от пи/2 до пи знак -, то меняем знак
    }

    do
    {
        S_1 = S; //предыдущее значение суммы
        S = S + (zn * pow(x, 2 * n - 2) / fact(2 * n - 2));
        n = n + 1;
        zn = zn * (-1);
    } while (fabs(S - S_1) > EP);
    S = S * sign;
    return S;
}

int test_cos(void)
{
    double g; // для подсчета угла
    for (g = -2 *PI; g  <= 2 * PI; g = g + PI / 10.) // с шагом 1/10 pi идем до 6pi от нуля
    {
        if (fabs(fmod(fabs(g), PI) - PI / 2)>=EP) //точки pi/2 убираем
        {
            printf("mycos(%8.5f) = %9.6f  cos(%8.5f) =%9.6f\n", g, mycos(g, EP),g, cosl(g));
            // печать двух вещ. чисел с заданной точностью
        }
        else
        {
             return 1; // Если угол близится к pi/2 то код ошибки 1
        }

    }
    return 0;


}

int main() {
	return test_cos();
}
