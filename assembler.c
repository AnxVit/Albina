#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 200

char* read_file(int c, char file[]);
char* change_string(char string_s[]);
void write_file(char string[], char file[]);

int main(int argc, char** argv[]) {
	char string[N], ch_string[N];			  //переменные считанной строки и измененной

	strcpy(string, read_file(argc, argv[1])); //копируем результат из функции считывания

	strcpy(ch_string, change_string(string)); //копируем результат из функции изменения

	write_file(ch_string, argv[2]);			  //записываем результат в файл

	return 0;

}

char* read_file(int c, char file[]) {
	char string[N];
	if (c != 3) { //проверка на количество аргументов командной строки
		printf("The wrong number of files was enterned or another unknown error occured\n");
		exit(1);
	}

	FILE* f = fopen(file, "r");
	if (!f) //проверка на открытие файла
	{
		printf("File with name %s could not be open for read\n", file);
		exit(2);
	}

	fgets(string, N, f); //считываем из файла строку

	fclose(f);

	return string;
}
char* change_string(char string_s[]) {
	char new_string[N] = "";
	int i, j, flag = 0;
	int len = strlen(string_s);
	for (i = 0; i < len; i++) {
		if ('A' <= string_s[i] && string_s[i] <= 'Z') { //ищем загланую букву
			if (flag) {//если ввод уже был, ставим пробел
				strcat(new_string, " ");
			}
			else { //иначе ставим флаг
				flag = 1;
			}
			for (j = i + 1; j < len; j++) {//ищем количество строчных букв после заглавной буквы
				if ('a' >= string_s[j] || string_s[j] >= 'z') {
					break;
				}
			}
			strncat(new_string, &string_s[i], j - i); //присоединяем к строке слово
		}
	}

	return new_string;
}
void write_file(char string[], char file[]) {
	FILE* f = fopen(file, "w");
	if (!f) // проверка на открытие файла
	{
		printf("File with name %s could not be open for write\n", file);
		exit(3);
	}
	fputs(string, f); //вписываем строку в файл

	fclose(f);
}