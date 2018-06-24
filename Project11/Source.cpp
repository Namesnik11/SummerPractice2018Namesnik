/**
* @file   project7.cpp
* @author ������ �.�., ��. 515�
* @date   21 ���� 2018
* @brief  ������ ��������
*
* ������� ������ �������� ��������� ���������.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/* ��������� �� ����� �� �� �� ������� ���������, ���� �� ������
� ������� ���������� � ����� �� ����� ��� ������*/
void find_path(int n, int row, int col, char **lab, int **visited, int **path, int *plan, int &n_queue) {
	if (!visited[row][col]) {
		//��������� ������ ������ �� ����������� �����������
		if ((row + 1) < n && (row + 1) >= 0 && !visited[row + 1][col] &&
			(lab[row + 1][col] == '.' || lab[row + 1][col] == 'X')) {
			path[row + 1][col] = path[row][col] + 1;
			plan[n_queue] = row + 1;
			n_queue++;
			plan[n_queue] = col;
			n_queue++;
		}
		//��������� ����� ������ �� ����������� �����������
		if ((row - 1) < n && (row - 1) >= 0 && !visited[row - 1][col] &&
			(lab[row - 1][col] == '.' || lab[row - 1][col] == 'X')) {
			path[row - 1][col] = path[row][col] + 1;
			plan[n_queue] = row - 1;
			n_queue++;
			plan[n_queue] = col;
			n_queue++;
		}
		//��������� ������� ������ �� ����������� �����������
		if ((col + 1) < n && (col + 1) >= 0 && !visited[row][col + 1] &&
			(lab[row][col + 1] == '.' || lab[row][col + 1] == 'X')) {
			path[row][col + 1] = path[row][col] + 1;
			plan[n_queue] = row;
			n_queue++;
			plan[n_queue] = col + 1;
			n_queue++;
		}
		//��������� ������ ������ �� ����������� �����������
		if ((col - 1) < n && (col - 1) >= 0 && !visited[row][col - 1] &&
			(lab[row][col - 1] == '.' || lab[row][col - 1] == 'X')) {
			path[row][col - 1] = path[row][col] + 1;
			plan[n_queue] = row;
			n_queue++;
			plan[n_queue] = col - 1;
			n_queue++;
		}
		visited[row][col] = 1; /* �������� ������ � ������� �������� */
	}
}

