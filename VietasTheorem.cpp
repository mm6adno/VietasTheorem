#include <iostream>	//для std::cin, std::cout
#include <ctime>	//для time()
#include <conio.h>	//для _getch()

enum withA
{
	e_withoutA = 0,
	e_withA,
	e_rand
};

//глобальные переменные
withA G_WithoutA{ e_rand };	// e_withoutA - a = 1, e_withA - a != 1, e_rand - случайно
int G_minX{ -20 };					//минимальное значение корней
int G_maxX{ 20 };						//максимальное значение корней
int G_minA{ 1 };						//минимальное значение A
int G_maxA{ 5 };						//максимальное значение A
bool autoDeleting{ true };	//автоделение (если непонятно - смотрите строку 79)


//ГПСЧ
int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

//теорема Виета 
void VietasTheorem()
{
	system("cls");
	bool testing{ true };

	while (testing)
	{
		int X1, X2;															//корни уравнения
		while (true)														//цикл, необходимый для того, чтобы сумма корней уравнения не была равна нулю
		{
			X1 = getRandomNumber(G_minX, G_maxX);	//первый корень уравнения
			while (X1 == 0)												//цикл, не пропускающий нулевые значения корня
			{
				X1 = getRandomNumber(G_minX, G_maxX);
			}
			X2 = getRandomNumber(G_minX, G_maxX);	//второй корень уравнения
			while (X2 == 0)												//цикл, не пропускающий нулевые значения корня
			{
				X2 = getRandomNumber(G_minX, G_maxX);
			}
			if (!((X1 + X2) == 0))
				break;
		}

		int A;																	//собственно A
		switch (G_WithoutA)											//цикл, определяющий диапазон A в соответствии с настройками(по умолчанию диапазон 1-5)
		{
		case e_withoutA: A = 1;
			break;
		case e_withA: A = getRandomNumber(G_minA, G_maxA);
			while (A == 0 || A == 1)							//цикл, не пропускающий нулевые и единичные значения A
			{
				A = getRandomNumber(G_minA, G_maxA);
			}
			break;
		case e_rand: A = getRandomNumber(G_minA, G_maxA);
			while (A == 0)												//цикл, не пропускающий нулевые значения A
			{
				A = getRandomNumber(G_minA, G_maxA);
			}
			break;
		}
		int B = -(X1 + X2) * A;									//собственно B
		int C = (X1 * X2) * A;									//собственно C


		std::string Bcheck{ "" };
		if (B > 0)
			Bcheck = '+';
		std::string Ccheck{ "" };
		if (C > 0)
			Ccheck = '+';
		std::string Acheck{ "" };
		if ((A == 1) || (A == -1))
			Acheck = "\b";
		
		std::cout << A << Acheck << "x^2" << Bcheck << B << "x" << Ccheck << C << " = 0\n";
		if (autoDeleting)
		{
			std::cout << "X1 + X2 = " << -B / A << '\n';
			std::cout << "X1 * X2 = " << C / A << '\n';
		}
		else
		{
			std::cout << "X1 + X2 = " << -B << " / " << A << '\n';
			std::cout << "X1 * X2 = " << C << " / " << A << '\n';
		}
		std::cout << "Введите X1 и X2: ";

		int X1in, X2in;
		std::cin >> X1in >> X2in;

		if ((X1in == X1) && (X2in == X2))
			std::cout << "Вы правы!\n";
		else if ((X2in == X1) && (X1in == X2))
			std::cout << "Правильно!\n";
		else if ((X1in == 0) && (X2in == 0))
		{
			testing = false;
			return;
		}
		else if (((X1in == 0) && (X2in == 1)) || ((X1in == 1) && (X2in == 0)))
		{
			std::cout << "Корни: " << X1 << " " << X2 << '\n';
		}
		else
			std::cout << "Вы ошиблись.\n";
	}


}

//настройки
void settings()
{
	
	while (true)
	{
		system("cls");

		std::string str_autoDeleting;
		if (autoDeleting)
			str_autoDeleting = "включен";
		else
			str_autoDeleting = "выключён";

		double chance = (1.0 / -(G_minA - G_maxA - 1)) * 100;


		std::cout	<< "Настройки:\n"
					<< " --w чтобы включить режим [a = 1] (x^2 + bx + c = 0)\n"
					<< " --a чтобы включить режим [a != 1] (ax^2 + bx + c = 0)\n"
					<< " --r чтобы было случайно(" << chance <<"% [a = 1], "<< 100 - chance << "% [a != 1])\n"
					<< " --d чтобы изменить диапазоны генерации корней и a"
					<< " (текущий диапазон корней - от " << G_minX << " до " << G_maxX << ", и диапазон A - от " << G_minA << " до " << G_maxA << ")\n"
					<< " --l чтобы переключить \"автоделение\" (" << str_autoDeleting << ")\n"
					<< " --q назад в меню\n"
					<< "Ввод осуществляется с английской раскладкой и без капса\n"
					<< "Сейчас включен ";
		switch (G_WithoutA)
		{
		case e_withoutA: std::cout << "режим [a = 1]\n";
			break;
		case e_withA: std::cout << "режим [a != 1]\n";
			break;
		case e_rand: std::cout << "случайный режим\n";
			break;
		}

		switch (_getch())
		{
		case 'w': G_WithoutA = e_withoutA; //строго без а
			break;
		case 'a': G_WithoutA = e_withA; //строго с a
			break;
		case 'r': G_WithoutA = e_rand; //случайно
			break;
		case 'q': return;
			break;
		case 'l':
			autoDeleting = !autoDeleting;
			break;
		case 'd': bool changeRange{ true };
			short whatPrint{ 0 }; // 1 - изменен диапазон Х, 2 - изменен диапазон А, 3 - значения сброшены
			while (changeRange)
			{
				system("cls");
				std::cout << "Какой диапазон изменить -\n"
					<< " --x диапазон корней\n"
					<< " --a диапазон A\n"
					<< " --d сбросить значения диапазонов\n"
					<< " --q назад\n";
				switch (whatPrint)
				{
				case 0:
					break;
				case 1:
					std::cout << "Диапазон корней изменён\n";
					break;
				case 2:
					std::cout << "Диапазон A изменён\n";
					break;
				case 3:
					std::cout << "Диапазоны установлены по умолчанию\n";
					break;
				}

				switch (_getch())
				{
				case 'x': 
				{
					bool checkError{ false };
						while (true)
						{
							system("cls");

							if (checkError)		// вывод ошибки пользователю
								std::cout << "Вы ввели неверный диапазон\n";

							std::cout << "Введите минимальное значение диапазона X: ";
							std::cin >> G_minX;
							std::cout << "Введите максимальное значение диапазона X: ";
							std::cin >> G_maxX;
							if (G_minX > G_maxX) // отброс неверного диапазона
								checkError = true;
							else break;
						}
						whatPrint = 1; 
				}
					break;
				case 'a': 
				{
					bool checkError{ false };
						while (true)
						{
							system("cls");

							if (checkError)		// вывод ошибки пользователю
								std::cout << "Вы ввели неверный диапазон\n";

							std::cout << "Введите минимальное значение диапазона A: ";
							std::cin >> G_minA;
							std::cout << "Введите максимальное значение диапазона A: ";
							std::cin >> G_maxA;
							if (G_minA > G_maxA) // отброс неверного диапазона
								checkError = true;
							else break;

						}
						whatPrint = 2; 
				}
					break;
				case'd':
					G_minX = -20;
					G_maxX = 20;
					G_minA = 1;
					G_maxA = 5;
					whatPrint = 3;
					break;
				case 'q': changeRange = false;
					break;
				}
			}

			break;
		}
	}

	
}

void showDeveloper()
{
	while (true)
	{
		system("cls");
		std::cout	<< "VietasTheorem v2020.12.23 //created by mm6adno\n"
					<< " --q назад";
		if (_getch() == 'q')
			return;
	}

}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(static_cast<int>(time(0)));
	rand();

	while(true)
	{
		system("cls");
		bool wAgain{ true };
		
		std::cout	<< "Меню:\n"
					<< " --p чтобы начать\n"
					<< " --s чтобы настроить\n"
					<< " --q чтобы выйти\n"
					<< "Чтобы выйти обратно в меню во время тестирования - напишите x1 = 0 и x2 = 0\n"
					<< "Если вы не можете решить уравнение и хотите узнать ответ - напишите x1 = 0 и x2 = 1\n"
					<< "Ввод осуществляется с английской раскладкой и без капса\n";
		
		while (wAgain)
		{
			
			switch (_getch())
			{
			case 'p': 
				VietasTheorem();
				wAgain = false;
				break;
			case 's': settings();
				wAgain = false;
				break;
			case 'c': showDeveloper();
				wAgain = false;
				break;
			case 'q': return 0;
				break;
			}
		}
	}
	
	
}
