#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct game {
	char Name[100];
	char Publisher[100];
	char Genre[100];
	char Platforms[100];
	int Year;
	float Rating;
};

typedef struct game Game;

Game* add_el(Game* ptrarr, int* size);
Game loading();
void print_el(Game game);
int save(FILE* file, char* adress, Game* ptrarr, int size);
Game file_loading(FILE* file);
Game* load(FILE* file, char* adress, int* size);
int compare(const void* a, const void* b);
Game* find(Game* ptrarr, int size, int* size_n, char* str, int choice);

int main() {
	system("chcp 1251");
	int size = 0;
	Game* database = (Game*)malloc(size * sizeof(Game));

	FILE* file = NULL;
	char* adress = (char*)malloc(40 * sizeof(char));
	adress = "data.txt";

	int choice;

	do {
		printf("\n===========================================================\n");
		printf("%30.30s\n", "[����]");
		printf("(1) �������� ���� � ���� ������\n");
		printf("(2) ����� ���� �� ���� ������\n");
		printf("(3) ����� ���� �� ��������\n");
		printf("(4) ������� ���� ������ � �������\n");
		printf("(5) ������������� �� �������� ����\n");
		printf("(6) ������ � ���� ���� ��������� ����\n");
		printf("(7) ��������� �� ����� ��� ������\n");
		printf("(8) �������� ���� ������\n");
		printf("===========================================================\n");
		printf("�������� ����� �� ����: ");
		scanf(" %d", &choice);

		switch (choice)
		{
		case 1:;
			Game temp = loading();
			database = add_el(database, &size);
			database[size - 1] = temp;
			break;
		case 2:
			printf("\n===========================================================\n");
			printf("������� �������� ������: ");
			char str_h[100];
			scanf(" %s", str_h);
			int size_h = 0;
			Game* data0 = find(database, size, &size_h, &str_h, 0);
			if (data0 == NULL) {
				printf("������ �� �������");
			}
			else {
				printf("%5c| %20.20s | %20.20s | %20.20s | %20.20s | %11.11s | %7.7s |\n", ' ', "��������", "��������", "����", "���������", "���� ������", "�������");
				for (int i = 0; i < size_h; i++) {
					print_el(data0[i]);
				}
				printf("===========================================================\n");
				printf("����� ���������� ������� Enter");
				getchar();
				getchar();
			}
			break;
		case 3:
			printf("\n===========================================================\n");
			printf("������� �������� ������: ");
			char str_g[100];
			scanf(" %s", str_g);
			int size_g = 0;
			Game* data1 = find(database, size, &size_g, &str_g, 1);
			if (data1 == NULL) {
				printf("������ �� �������");
			}
			else {
				printf("%5c| %20.20s | %20.20s | %20.20s | %20.20s | %11.11s | %7.7s |\n", ' ', "��������", "��������", "����", "���������", "���� ������", "�������");
				for (int i = 0; i < size_g; i++) {
					print_el(data1[i]);
				}
				printf("===========================================================\n");
				printf("����� ���������� ������� Enter");
				getchar();
				getchar();
			}
			break;
		case 4:
			printf("\n===========================================================\n");
			printf("%30.30s\n", "[���� ������]");
			printf("%5c| %20.20s | %20.20s | %20.20s | %20.20s | %11.11s | %7.7s |\n", ' ', "��������", "��������", "����", "���������", "���� ������", "�������");
			for (int i = 0; i < size; i++) {
				print_el(database[i]);
			}
			printf("===========================================================\n");
			printf("����� ���������� ������� Enter");
			getchar();
			getchar();
			break;
		case 5:
			printf("\n===========================================================\n");
			qsort(database, size, sizeof(Game), compare);
			printf("���������� ���������\n");
			printf("===========================================================\n");
			break;
		case 6:;
			int result_save = save(file, adress, database, size);
			printf("\n===========================================================\n");
			if (result_save == 1) printf("������ ������� ��������� � ����\n");
			if (result_save == 0) printf("������ �� ��������� � ����\n");
			printf("===========================================================\n");
			break;
		case 7:
			free(database);
			int size_n = 0;
			printf("\n===========================================================\n");
			database = load(file, adress, &size_n);
			size = size_n;
			printf("===========================================================\n");
			break;
		default:
			break;
		}

	} while (choice < 8);

	return 0;
}

Game* add_el(Game* ptrarr, int* size) {
	int size_n = (*size) + 1;
	Game* temp = (Game*)realloc(ptrarr, size_n * sizeof(Game));
	ptrarr = temp;
	(*size)++;
	return ptrarr;
}

Game loading() {
	Game temp = { "", "", "", "", 1, 1. };
	printf("\n===========================================================\n");
	printf("%30.30s\n", "[�������� ����]");
	printf("%5c������� �������� ����: ", ' ');
	scanf(" %s", temp.Name);
	printf("%5c������� ��������: ", ' ');
	scanf(" %s", temp.Publisher);
	printf("%5c������� ����: ", ' ');
	scanf(" %s", temp.Genre);
	printf("%5c������� ���������: ", ' ');
	scanf(" %s", temp.Platforms);
	printf("%5c������� ��� ������: ", ' ');
	scanf(" %d", &temp.Year);
	printf("%5c������� �������: ", ' ');
	scanf(" %f", &temp.Rating);
	printf("===========================================================\n");
	printf("����� ������ ������� ��������� � ���� ������\n");
	printf("����� ���������� ������� Enter");
	getchar();
	getchar();
	return temp;
}

void print_el(Game game) {
	printf("%5c| %20.20s | %20.20s | %20.20s | %20.20s | %11d | %7.1f |\n", ' ', game.Name, game.Publisher, game.Genre, game.Platforms, game.Year, game.Rating);
}

int save(FILE* file, char* adress, Game* ptrarr, int size) {
	file = fopen(adress, "w");
	if (file == NULL) return 0;
	for (int i = 0; i < size; i++) {
		if (file)
		{
			if (i != 0) fprintf(file, "\n");
			fprintf(file, "%s\n", ptrarr[i].Name);
			fprintf(file, "%s\n", ptrarr[i].Publisher);
			fprintf(file, "%s\n", ptrarr[i].Genre);
			fprintf(file, "%s\n", ptrarr[i].Platforms);
			fprintf(file, "%d\n", ptrarr[i].Year);
			fprintf(file, "%f\0", ptrarr[i].Rating);
		}
	}
	fclose(file);
	return 1;
}


Game file_loading(FILE* file) {

	Game temp;
	fgets(temp.Name, 100, file);
	fgets(temp.Publisher, 100, file);
	fgets(temp.Genre, 100, file);
	fgets(temp.Platforms, 100, file);
	fscanf(file, "%d\n", &temp.Year);
	fscanf(file, "%f\n", &temp.Rating);

	strtok(temp.Name, "\n");
	strtok(temp.Publisher, "\n");
	strtok(temp.Genre, "\n");
	strtok(temp.Platforms, "\n");

	return temp;
}

Game* load(FILE* file, char* adress, int* size) {
	file = fopen(adress, "r");
	if (file == NULL) printf("������ �� ��������� �� �����\n");

	int lines = 0;
	int previous = '\n';
	int ch;
	while ((ch = fgetc(file)) != EOF) {
		if (previous == '\n') lines++;
		previous = ch;
	}
	*size = lines / 6;
	fclose(file);

	file = fopen(adress, "r");
	int i = 0;
	Game* database = (Game*)malloc(*size * sizeof(Game));
	while (feof(file) == 0) {
		Game temp = file_loading(file);
		database[i] = temp;
		i++;
	}
	fclose(file);
	printf("������ ������� ��������� �� �����\n");
	return database;
}

int compare(const void* a, const void* b)
{
	Game* data1 = a;
	Game* data2 = b;
	return strcmp(data1->Name, data2->Name);
}

Game* find(Game* ptrarr, int size, int* size_n, char* str, int choice) {
	int count = 0;
	int year;
	if (choice == 0) {
		year = atoi(str);
	}
	for (int i = 0; i < size; i++) {
		if (choice == 0) {
			if (year == ptrarr[i].Year) {
				count++;
			}
		}
		if (choice == 1) {
			if (!strcmp(str, ptrarr[i].Publisher)) count++;
		}
	}
	if (count == 0) return NULL;
	*size_n = count;
	Game* temp = (Game*)malloc(*size_n * sizeof(Game));
	int j = 0;
	for (int i = 0; i < size; i++) {
		if (choice == 0) {
			if (year == ptrarr[i].Year) {
				temp[j] = ptrarr[i];
				j++;
			};
		}
		if (choice == 1) {
			if (!strcmp(str, ptrarr[i].Publisher)) {
				temp[j] = ptrarr[i];
				j++;
			}
		}
	}
	return temp;
}