/**
* @file   project7.cpp
* @author Намєснік Є.В., гр. 515б
* @date   21 июня 2018
* @brief  Летняя практика
*
* Решение задачи способом волнового алгоритма.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/* проверяем не вышли ли мы за границы лабиринта, есть ли клетка
в массиве посещенных и можно ли через нее пройти*/
void find_path(int n, int row, int col, char **lab, int **visited, int **path, int *plan, int &n_queue) {
	if (!visited[row][col]) {
		//проверяем правую клетку на возможность продвижения
		if ((row + 1) < n && (row + 1) >= 0 && !visited[row + 1][col] &&
			(lab[row + 1][col] == '.' || lab[row + 1][col] == 'X')) {
			path[row + 1][col] = path[row][col] + 1;
			plan[n_queue] = row + 1;
			n_queue++;
			plan[n_queue] = col;
			n_queue++;
		}
		//проверяем левую клетку на возможность продвижения
		if ((row - 1) < n && (row - 1) >= 0 && !visited[row - 1][col] &&
			(lab[row - 1][col] == '.' || lab[row - 1][col] == 'X')) {
			path[row - 1][col] = path[row][col] + 1;
			plan[n_queue] = row - 1;
			n_queue++;
			plan[n_queue] = col;
			n_queue++;
		}
		//проверяем верхнюю клетку на возможность продвижения
		if ((col + 1) < n && (col + 1) >= 0 && !visited[row][col + 1] &&
			(lab[row][col + 1] == '.' || lab[row][col + 1] == 'X')) {
			path[row][col + 1] = path[row][col] + 1;
			plan[n_queue] = row;
			n_queue++;
			plan[n_queue] = col + 1;
			n_queue++;
		}
		//проверяем нижнюю клетку на возможность продвижения
		if ((col - 1) < n && (col - 1) >= 0 && !visited[row][col - 1] &&
			(lab[row][col - 1] == '.' || lab[row][col - 1] == 'X')) {
			path[row][col - 1] = path[row][col] + 1;
			plan[n_queue] = row;
			n_queue++;
			plan[n_queue] = col - 1;
			n_queue++;
		}
		visited[row][col] = 1; /* отмечаем клетку в которой побывали */
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	int n, x_end = 0, y_end = 0, x, y;
	int n_queue = 0;       // количество элементов очереди
	int p_queue = 0;       // текущий элемент очереди
	printf("\n|*****************************************************************************|\n");
	printf("|--------------------***Краткое руководство по символам ввода***--------------|\n");
	printf("|                                                                             |\n");
	printf("|1) В первой строке находится число n (2<=n<=40).                             |\n");
	printf("|2) В каждой из следующих n строк - по n символов.                            |\n");
	printf("|3) Символом точки обозначена свободная клетка.                               |\n");
	printf("|4) 0 - шарик.                                                                |\n");
	printf("|5) @ - исходное положение шарика, который должен двигаться.                  |\n");
	printf("|6) Латинской заглавной Х - конечное положение шарика.                        |\n");
	printf("|                                                                             |\n");
	printf("|                       ***Выходные данные***                                 |\n");
	printf("|1) В первой строке выводится X , если движение возможно, или N - если нет.   |\n");
	printf("|2) Если движение возможно, далее n строк по n символов - как и на вводе,но Х.|\n");
	printf("|3) Все точки на пути заменяются плюсами.                                     |\n");
	printf("|                                                                             |\n");
	printf("|-----------------------Краткое руководство по символам ввода-----------------|\n");

	printf("\n");
Begin:
	printf("Введите исходные данные:\n");
	scanf("%d", &n);
	//проверка на интервал n
	if (n < 2 || n > 40)
	{
		printf("Вы вышли за интервал числа n, прочтите инструкцию и введите заново.\n");
		goto Begin;
	}
	char **lab = (char **)malloc(n * sizeof(char *) + 1);
	int **visited = (int **)malloc(n * sizeof(int *));
	int **path = (int **)malloc(n * sizeof(int *));
	int *plan = (int *)malloc(3 * n * n * sizeof(int));
	//вводим лабиринт и заполняем очередь для поиска пути
	for (int i = 0; i < n; i++) {
		lab[i] = (char *)malloc(n * sizeof(char) + 1);   /* массив для хранения лабиринта */
		visited[i] = (int *)malloc(n * sizeof(int)); /* массив для хранения онформации о посещении*/
		path[i] = (int *)malloc(n * sizeof(int));  /* массив для хранения найденых путей */
		scanf("%s", lab[i]);
		for (int j = 0; j < n; j++) {
			visited[i][j] = 0;
			path[i][j] = -1;

			if (lab[i][j] == '@') { /* находим начало пути и заносим начальную клетку в очередь посещения*/
				plan[n_queue] = i;
				n_queue++;
				plan[n_queue] = j;
				n_queue++;
				path[i][j] = 1;
			}
			else if (lab[i][j] == 'X') { /* находим конечную точку */
				x_end = i;
				y_end = j;
			}
		}
	}
	//
	while (n_queue != p_queue) { /* пока не пройдена вся очередь*/
		x = plan[p_queue];
		p_queue++;
		y = plan[p_queue];
		p_queue++;
		find_path(n, x, y, lab, visited, path, plan, n_queue); /* продолжаем поиск пути*/
	}
	printf("\n");
	printf("Результат: \n");
	if (!visited[x_end][y_end]) {//если конечная точка не посещена, пути нет
		printf("N\n");
	}
	else {//если посещена, восстанавливаем путь
		printf("Y\n");
		x = x_end;
		y = y_end;

		while (path[x][y] != 2) { /* восстановление пути*/
			if ((x - 1) >= 0 && (x - 1) < n && (path[x - 1][y] == path[x][y] - 1)) {
				x = x - 1;
				lab[x][y] = '+';
			}
			else if ((x + 1) >= 0 && (x + 1) < n && (path[x + 1][y] == path[x][y] - 1)) {
				x = x + 1;
				lab[x][y] = '+';
			}
			else if ((y - 1) >= 0 && (y - 1) < n && (path[x][y - 1] == path[x][y] - 1)) {
				y = y - 1;
				lab[x][y] = '+';
			}
			else if ((y + 1) >= 0 && (y + 1) < n && (path[x][y + 1] == path[x][y] - 1)) {
				y = y + 1;
				lab[x][y] = '+';
			}
		}
		//вывод пути
		for (int i = 0; i < n; i++) {
			printf("%s", lab[i]);

			printf("\n");
		}
	}
	getchar();
	getchar();
	return 0;
}
