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

int main()
{
	setlocale(LC_ALL, "rus");
	int n, x_end = 0, y_end = 0, x, y;
	int n_queue = 0;       // ���������� ��������� �������
	int p_queue = 0;       // ������� ������� �������
	printf("\n|*****************************************************************************|\n");
	printf("|--------------------***������� ����������� �� �������� �����***--------------|\n");
	printf("|                                                                             |\n");
	printf("|1) � ������ ������ ��������� ����� n (2<=n<=40).                             |\n");
	printf("|2) � ������ �� ��������� n ����� - �� n ��������.                            |\n");
	printf("|3) �������� ����� ���������� ��������� ������.                               |\n");
	printf("|4) 0 - �����.                                                                |\n");
	printf("|5) @ - �������� ��������� ������, ������� ������ ���������.                  |\n");
	printf("|6) ��������� ��������� � - �������� ��������� ������.                        |\n");
	printf("|                                                                             |\n");
	printf("|                       ***�������� ������***                                 |\n");
	printf("|1) � ������ ������ ��������� X , ���� �������� ��������, ��� N - ���� ���.   |\n");
	printf("|2) ���� �������� ��������, ����� n ����� �� n �������� - ��� � �� �����,�� �.|\n");
	printf("|3) ��� ����� �� ���� ���������� �������.                                     |\n");
	printf("|                                                                             |\n");
	printf("|-----------------------������� ����������� �� �������� �����-----------------|\n");

	printf("\n");
Begin:
	printf("������� �������� ������:\n");
	scanf("%d", &n);
	//�������� �� �������� n
	if (n < 2 || n > 40)
	{
		printf("�� ����� �� �������� ����� n, �������� ���������� � ������� ������.\n");
		goto Begin;
	}
	char **lab = (char **)malloc(n * sizeof(char *) + 1);
	int **visited = (int **)malloc(n * sizeof(int *));
	int **path = (int **)malloc(n * sizeof(int *));
	int *plan = (int *)malloc(3 * n * n * sizeof(int));
	//������ �������� � ��������� ������� ��� ������ ����
	for (int i = 0; i < n; i++) {
		lab[i] = (char *)malloc(n * sizeof(char) + 1);   /* ������ ��� �������� ��������� */
		visited[i] = (int *)malloc(n * sizeof(int)); /* ������ ��� �������� ���������� � ���������*/
		path[i] = (int *)malloc(n * sizeof(int));  /* ������ ��� �������� �������� ����� */
		scanf("%s", lab[i]);
		for (int j = 0; j < n; j++) {
			visited[i][j] = 0;
			path[i][j] = -1;

			if (lab[i][j] == '@') { /* ������� ������ ���� � ������� ��������� ������ � ������� ���������*/
				plan[n_queue] = i;
				n_queue++;
				plan[n_queue] = j;
				n_queue++;
				path[i][j] = 1;
			}
			else if (lab[i][j] == 'X') { /* ������� �������� ����� */
				x_end = i;
				y_end = j;
			}
		}
	}
	//
	while (n_queue != p_queue) { /* ���� �� �������� ��� �������*/
		x = plan[p_queue];
		p_queue++;
		y = plan[p_queue];
		p_queue++;
		find_path(n, x, y, lab, visited, path, plan, n_queue); /* ���������� ����� ����*/
	}
	printf("\n");
	printf("���������: \n");
	if (!visited[x_end][y_end]) {//���� �������� ����� �� ��������, ���� ���
		printf("N\n");
	}
	else {//���� ��������, ��������������� ����
		printf("Y\n");
		x = x_end;
		y = y_end;

		while (path[x][y] != 2) { /* �������������� ����*/
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
		//����� ����
		for (int i = 0; i < n; i++) {
			printf("%s", lab[i]);

			printf("\n");
		}
	}
	getchar();
	getchar();
	return 0;
}
