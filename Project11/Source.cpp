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

