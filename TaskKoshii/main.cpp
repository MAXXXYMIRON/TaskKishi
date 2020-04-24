#include<iostream>
#include<vector>
#include<cmath>

float f(float x, float y)
{
	return ((2 * x * x) + 5) * sin(y);
}


float Eyler(float yk, float xk, float h)
{
	return yk + h * f(xk, yk);
}

float EylerModificate(float yk, float xk, float h)
{
	return yk + h * f(xk + (h / 2), yk + ((h / 2) * f(xk, yk)));
}

float Runge_Cutt(float yk, float xk, float h)
{
	float a = h * f(xk, yk),
		b = h * f(xk + (h / 2), yk + (a / 2)),
		c = h * f(xk + (h / 2), yk + (b / 2)),
		d = h * f(xk + h, yk + c);

	return yk + (a + (2 * b) + (2 * c) + d) / 6.;
}

float Adams_1(float yk, float xk, float yk_1, float xk_1, float h)
{
	return yk + ((h / 2) * (3 * f(xk, yk)
		- f(xk_1, yk_1)));
}

float Adams_2(float yk, float xk, float yk_1, float xk_1, float yk_2, float xk_2,
	float h)
{
	return yk + (h / 12) * (23 * f(xk, yk)
		- 16 * f(xk_1, yk_1)
		+ 5 * f(xk_2, yk_2));
}

float Adams_3(float yk, float xk, float yk_1, float xk_1, float yk_2, float xk_2,
	float yk_3, float xk_3, float h)
{
	return yk + (h / 24) * (55 * f(xk, yk)
		- 59 * f(xk_1, yk_1)
		+ 37 * f(xk_2, yk_2)
		- 9 * f(xk_3, yk_3));
}

void Out(std::vector<float> array)
{
	for (int i = 0; i < array.size(); i++)
	{
		std::cout << array[i] << "    ";
	}
	std::cout << std::endl;
}



int main()
{
	setlocale(0, "");

	float h = 0.1,
		y0 = 1,
		e = 0.001,
		x = 0;


	//Метод Эйлера
	std::cout << "Метод Эйлера" << "\n";
	
	std::vector<float> y;
	y.push_back(y0);
	while (x < 1)
	{
		y.push_back(Eyler(y[y.size() - 1], x, h));
		x += h;
	}
	Out(y);
	std::cout << std::endl;

	//Модифицированный метод Эйлера
	std::cout << "Модифицированный метод Эйлера" << "\n";

	x = 0;
	for (int i = 1; i < y.size(); i++)
	{
		y[i] = EylerModificate(y[i - 1], x, h);
		x += h;
	}
	Out(y);
	std::cout << std::endl;


	//Метод Рунге-Кутта
	std::cout << "Метод Рунге-Кутта" << "\n";

	x = 0;
	for (int i = 1; i < y.size(); i++)
	{
		y[i] = Runge_Cutt(y[i - 1], x, h);
		x += h;
	}
	Out(y);
	std::cout << std::endl;



	//Метод Aдамса первого порядка
	std::cout << "Метод Aдамса первого порядка" << "\n";

	x = 0;
	y[1] = Runge_Cutt(y[0], x, h);
	for (int i = 2; i < y.size(); i++)
	{
		x += h;
		y[i] = Adams_1(y[i - 1], x,
			y[i - 2], x - h,
			h);
	}
	Out(y);
	std::cout << std::endl;


	//Метод Aдамса второго порядка
	std::cout << "Метод Aдамса второго порядка" << "\n";

	x = 0;
	y[1] = Runge_Cutt(y[0], x, h);
	x += h;
	y[2] = Runge_Cutt(y[1], x, h);
	for (int i = 3; i < y.size(); i++)
	{
		x += h;
		y[i] = Adams_2(y[i - 1], x,
			y[i - 2], x - h,
			y[i - 3], x - (2 * h),
			h);
	}
	Out(y);
	std::cout << std::endl;


	//Метод Aдамса третьего порядка
	std::cout << "Метод Aдамса третьего порядка" << "\n";

	x = 0;
	y[1] = Runge_Cutt(y[0], x, h);
	x += h;
	y[2] = Runge_Cutt(y[1], x, h);
	x += h;
	y[3] = Runge_Cutt(y[2], x, h);
	for (int i = 4; i < y.size(); i++)
	{
		x += h;
		y[i] = Adams_3(y[i - 1], x,
			y[i - 2], x - h,
			y[i - 3], x - (2 * h),
			y[i - 4], x - (3 * h),
			h);
	}
	Out(y);
	std::cout << std::endl;



	system("pause");
	return 0;
}