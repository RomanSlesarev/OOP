#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include "allClasses.h"



int main()
{
	typedef List <RhombContour> RhombContourList;
	typedef List <RhombShaded> RhombShadedList;
	typedef List <CombRhomb> CombRhombList;

	RhombContourList *RhC = new RhombContourList();
	RhombShadedList *RhS = new RhombShadedList();
	CombRhombList *RhComb = new CombRhombList();

	RhombContour *bufRhC = new RhombContour;
	RhombShaded *bufRhS = new RhombShaded;
	CombRhomb *bufRhComb = new CombRhomb;

	setlocale(LC_ALL, "Russian");
	char c[15];
	char button1;
	char button2;
	int num;
	do
	{
		system("cls");
		clearScreen();
		printf("\n\n\t***MENU***\n\n");
		printf("\t1: Считать ромб из файла\n");
		printf("\t2: Сохранить ромб в файл\n");
		printf("\t3: Нарисовать контур фигуры\n");
		printf("\t4: Нарисовать закрашенную фигуру\n");
		printf("\t5: Нарисовать две вложенные фигуры\n");
		printf("\t6: Выход\n\t");
		printf("\n        **********");
		button1 = _getch();
		if (button1 == '1')
		{
			do
			{
				system("cls");
				printf("\n\n\t***MENU***\n");
				printf("\tВыберите тип считываемого ромба: \n");
				printf("\t1: Контур\n");
				printf("\t2: Закрашенный\n");
				printf("\t3: Комбиринованный\n");
				printf("\t4: Назад\n");
				printf("\n        **********");
				button2 = _getch();
				system("cls");
				if (button2 == '1')
				{
					printf("Введите имя файла:\n");
					scanf("%s", &c);
					bufRhC->readData(c);
					RhC->addEl(*bufRhC);
				}
				if (button2 == '2')
				{
					printf("Введите имя файла:\n");
					scanf("%s", &c);
					bufRhS->readData(c);
					RhS->addEl(*bufRhS);
				}
				if (button2 == '3')
				{
					printf("Введите имя файла:\n");
					scanf("%s", &c);
					bufRhComb->readData(c);
					RhComb->addEl(*bufRhComb);
				}
			} while (button2 != '4');
		}
		if (button1 == '2')
		{
			do
			{
				system("cls");
				printf("\n\n\t***MENU***\n");
				printf("\tВыберите тип сохраняемого ромба: \n");
				printf("\t1: Контур\n");
				printf("\t2: Закрашенный\n");
				printf("\t3: Комбиринованный\n");
				printf("\t4: Назад\n");
				printf("\n        **********");
				button2 = _getch();
				system("cls");
				if (button2 == '1')
				{
					printf("Введите ключ сохраняемого ромба: \n");
					scanf("%d", &num);
					if (num < RhC->get_quantity())
					{
						printf("Введите имя файла:\n");
						scanf("%s", &c);
						RhC->findEl(bufRhC, num);
						bufRhC->saveData(c);
					}
					else printf("Ромб с таким ключом не существует.");
					_getch();
				}
				if (button2 == '2')
				{
					printf("Введите ключ сохраняемого ромба: \n");
					scanf("%d", &num);
					if (num < RhS->get_quantity())
					{
						printf("Введите имя файла:\n");
						scanf("%s", &c);
						RhS->findEl(bufRhS, num);
						bufRhS->saveData(c);
					}
					else printf("Ромб с таким ключом не существует.");
				}
				if (button2 == '3')
				{
					printf("Введите ключ сохраняемого ромба: \n");
					scanf("%d", &num);
					printf("Введите имя файла:\n");
					scanf("%s", &c);
					RhComb->findEl(bufRhComb, num);
					bufRhComb->saveData(c);
				}
			} while (button2 != '4');
		}
		if (button1 == '3')
		{
			system("cls");
			printf("Введите ключ ромба: \n");
			scanf("%d", &num);
			RhC->findEl(bufRhC, num);
			if (bufRhC->checkRhomb())
				bufRhC->draw();
			else printf("Данная фигура не является ромбом.");
			_getch();
		}
		if (button1 == '4')
		{
			system("cls");
			printf("Введите ключ ромба: \n");
			scanf("%d", &num);
			RhS->findEl(bufRhS, num);
			if (bufRhS->checkRhomb())
				bufRhS->draw();
			else printf("Данная фигура не является ромбом.");
			_getch();
		}
		if (button1 == '5')
		{
			system("cls");
			printf("Введите ключ ромба: \n");
			scanf("%d", &num);
			RhComb->findEl(bufRhComb, num);
			if (bufRhComb->checkRhomb() && bufRhComb->get_smallRhomb().checkRhomb())
			{
				if (bufRhComb->insideRhomb())
				{
					bufRhComb->draw();
					_getch();
				}
				else printf("Ромбы не вложены.");
			}
			else printf("Одна из фигур не является ромбом.");
			_getch();
		}
	} while (button1 != '6');
}
