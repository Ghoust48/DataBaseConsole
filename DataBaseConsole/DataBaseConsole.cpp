#include "pch.h"
#include <iostream>

#include<iostream>
#include<cstdio>
#include<conio.h>
#include<iomanip>
#include<cstring>
#include<fstream>
#include<cstdlib>

using namespace std;
char buff[80]{};					//буфер char
char txt[] = ".txt";
int p = 0;

struct Bank {
	char surname[30];
	char name[30];
	char patronymic[30];			//Отчество
	char personal_account[15];		//Лицевой счет
	int day;
	int month;
	int year;						//Дата
	char number[25];				//номер карты
	char validity[8];				//Срок действия
	double balance;					// Баланс
	char phone_number[12];			// Номер телефона клиента
	char cvc[5];					// CVC2/CVV2 (код на обороте карты)
};

int check_data(Bank *account, int n, char buf[50]) {
	int a = 0, b = 0, k = 0;
	char day[3], month[3], year[5];
	do {
		strcpy(buf, "");
		cin.getline(buf, 50);
		a = 0;
		b = 0;
		for (int i = 0; i < strlen(buf); i++) {
			if (buf[i] >= '0' && buf[i] <= '9') a++;
			if (buf[i] == '.') b++;
		}
		if (b == 1 || a == 4 || atoi(buf) != 0) {
			day[0] = buf[0]; day[1] = buf[1]; day[2] = '\0';
			month[0] = buf[3]; month[1] = buf[4]; month[2] = '\0';
			year[0] = buf[6]; year[1] = buf[7]; year[2] = buf[8]; year[3] = buf[9]; year[4] = '\0';
			if (atoi(day) >= 1 && atoi(day) <= 31 && atoi(month) >= 1 && atoi(month) <= 12 && atoi(year) >= 1990 && atoi(year) <= 2018) {
				if (atoi(month) == 1 || atoi(month) == 3 || atoi(month) == 5 || atoi(month) == 7 || atoi(month) == 8 || atoi(month) == 10 || atoi(month) == 12) k++;
				if ((atoi(month) == 4 || atoi(month) == 6 || atoi(month) == 9 || atoi(month) == 11) && atoi(day) <= 30) k++;
				if (atoi(month) == 2 && atoi(day) <= 28) k++;
				if (atoi(month) == 2 && atoi(year) % 4 == 0 && atoi(day) <= 29) k++;
			}
		}
		if (b != 2 || a != 8 || atoi(buf) == 0 || k == 0)
			return 0;
	} while (b != 2 || a != 8 || atoi(buf) == 0 || k == 0);
	account[n].day = atoi(day);
	account[n].month = atoi(month);
	account[n].year = atoi(year);
	k = 0;
	return 1;
}

int check_char(Bank *account, int n, char buf[50]) {
	strcpy(buf, "");
	cin.getline(buf, 50);
	for (int i = 0; i < strlen(buf); i++) {
		if (!isalpha(buf[i])) {
			return 0;
		}
	}
	return 1;
}

int check_number_card(Bank *account, int n, char buf[50]) {
	strcpy(buf, "");
	cin.getline(buf, 50);
	for (int i = 0; i < strlen(buf); i++) {
		if (isdigit(buf[i])) {
			if (buf[4] == ' ' && buf[9] == ' ' && buf[14] == ' ') {
				return 1;
			}
		}
	}
	return 0;
}

int check_int(Bank *account, int n, char buf[50]) {
	strcpy(buf, "");
	cin.getline(buf, 50);
	for (int i = 0; i < strlen(buf); i++) {
		if (isdigit(buf[i])) {
			return 1;
		}
	}
	return 0;
}

int check_validity(Bank *account, int n, char buf[50]) {
	strcpy(buf, "");
	cin.getline(buf, 50);
	for (int i = 0; i < strlen(buf); i++) {
		if (isdigit(buf[i])) {
			return 1;
		}
		if (isalpha(buf[i])) {
			return 0;
			//break;
		}
	}
	return 0;
}

Bank input(Bank *account, int i) {
	char buf[50];
	do {
		do {
			cout << "Фамилия: ";
		} while (check_char(account, i, buf) == 0);
		strcpy(account[i].surname, buf);
	} while (strlen(account[i].surname) > 30 || strlen(account[i].surname) == 0);
	/*do {
		do{
			cout << "Имя: ";
		} while (check_char(account, i, buf) == 0);
		strcpy(account[i].name, buf);
	} while (strlen(account[i].name) > 30 || strlen(account[i].name) == 0);
	do {
		do {
			cout << "Отчество: ";
		} while (check_char(account, i, buf) == 0);
		strcpy(account[i].patronymic, buf);
	} while (strlen(account[i].patronymic) > 30 || strlen(account[i].patronymic) == 0);
	do {
		do {
			cout << "Лицевой счёт: ";
		} while (check_int(account, i, buf) == 0);
		strcpy(account[i].personal_account, buf);
	} while (strlen(account[i].personal_account) != 7);
	do {
		cout << "Дата регистрации(dd.mm.yyyy): ";
	}while(check_data(account, i, buf) == 0);
	do {
		do {
			cout << "Номер карты(1234 5678 9101 2131): ";
		} while (check_number_card(account, i, buf) == 0);
		strcpy(account[i].number, buf);
	} while (strlen(account[i].number) != 19);
	do {
		do {
			cout << "Срок действия карты (мм/гг): ";
		} while (check_validity(account, i, buf) == 0);
		strcpy(account[i].validity, buf);
	} while (strlen(account[i].validity) != 5);
	do {
		cout << "Баланс: ";
	} while (check_char(account, i, buf) == 1);
	account[i].balance = atof(buf);
	do {
		do {
			cout << "Номер телефона(331115522): ";
		} while (check_int(account, i, buf) == 0);
		strcpy(account[i].phone_number, buf);
	} while (strlen(account[i].phone_number) != 9);
	do {
		int a = 0;
		do {
			cout << "CVC2/CVV2: ";
			cin.getline(buf, 50);
			while (isdigit(buf[a]))
				a++;
		} while (a != strlen(buf));
		strcpy(account[i].cvc, buf);
	} while (strlen(account[i].cvc) != 3);*/

	return account[i];
}

void Show_one(Bank *account, int i) {

	cout << setw(3) << "|" << setw(21) << account[i].surname << "|" << setw(13) << "|" << setw(17) << "|" << setw(20) << "|" << setw(21) << "|\t" << setw(6) << "\t|" << setw(12) << "|" << setw(7) << "|" << endl;
	cout << setw(2) << i + 1 << "|" << setw(21) << account[i].name << "|"
		<< setw(12) << account[i].personal_account << "|   "
		<< setfill('0') << setw(2) << account[i].day << "." << setfill('0') << setw(2) << account[i].month << "." << setw(4) << account[i].year << "   |" << setfill(' ')
		<< setw(19) << account[i].number << "|"
		<< setw(19) << account[i].validity << "|"
		<< setw(9) << account[i].balance << "|"
		<< setw(11) << account[i].phone_number << "|"
		<< setw(6) << account[i].cvc << "|" << endl;
	cout << setw(3) << "|" << setw(21) << account[i].patronymic << "|" << setw(13) << "|" << setw(17) << "|" << setw(20) << "|" << setw(21) << "|\t" << setw(6) << "\t|" << setw(12) << "|" << setw(7) << "|" << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------\n";
}

ofstream new_DB() {
	strcpy(buff, "");
	do {
		cout << "Введите название файла(макс. 50 символов): ";
		gets_s(buff, 54);
		buff[50] = '\0';
	} while (strlen(buff) == 0);
	strcat(buff, txt);
	ofstream file(buff, ios_base::app);
	if (!file.is_open()) cout << "Ошибка!" << endl;
	return file;
}

void save_DB(Bank *account, int &n) {
	new_DB();
	ofstream fout(buff, ios_base::app);
	for (int i = 0; i < n; i++) {
		fout << account[i].surname << endl;
		fout << account[i].name << endl;
		fout << account[i].patronymic << endl;
		fout << account[i].personal_account << endl;
		fout << account[i].day << endl;
		fout << account[i].month << endl;
		fout << account[i].year << endl;
		fout << account[i].number << endl;
		fout << account[i].validity << endl;
		fout << account[i].balance << endl;
		fout << account[i].phone_number << endl;
		fout << account[i].cvc << endl;
	}
	fout.close();
	cout << endl << "Данные успешно записаны в файл " << buff << endl;
}

void remove_DB() {
	char del[54];
	getchar();
	do {
		cout << "Введите название файла(макс. 50 символов): ";
		gets_s(del, 54);
		buff[50] = '\0';
	} while (strlen(del) == 0);
	strcat(del, txt);
	if (remove(del)) {
		cout << "Ошибка!" << endl;
	}
	else cout << "Файл удалён!" << endl;
}

Bank* load_DB(Bank *account, int &n) {
	new_DB();
	char buf[50];
	ifstream fin(buff);
	if (!fin.is_open()) {
		cout << "Файл не может быть открыт или такой файл не существует!";
	}
	else {
		account = (Bank*)realloc(account, (n + 1) * sizeof(Bank));
		fin.getline(account[n].surname, 30);
		int proverka = 0;
		if (strcmp(account[n].surname, "") != 0) {
			while (strcmp(account[n].surname, "") != 0) {
				account = (Bank*)realloc(account, (n + 2) * sizeof(Bank));
				fin.getline(account[n].name, 30);
				fin.getline(account[n].patronymic, 30);
				fin.getline(account[n].personal_account, 15);
				fin.getline(buf, 50);
				account[n].day = atoi(buf);
				strcpy(buf, "");
				fin.getline(buf, 50);
				account[n].month = atoi(buf);
				strcpy(buf, "");
				fin.getline(buf, 50);
				account[n].year = atoi(buf);
				strcpy(buf, "");
				fin.getline(account[n].number, 25);
				fin.getline(account[n].validity, 8);
				fin.getline(buf, 50);
				account[n].balance = atof(buf);
				fin.getline(account[n].phone_number, 12);
				fin.getline(account[n].cvc, 5);
				n++;
				proverka++;
				fin.getline(account[n].surname, 30);
			}
			if (n != 0) {
				cout << "Файл успешно загружен\n";
			}
			else
				cout << "Библиотека пуста\n";
			fin.close();
		}
		else if (proverka == 0) {
			cout << "Файл " << buff << " пуст!" << endl;
		}
	}
	system("pause");
	return account;
}

void clear(Bank *account, int &n) {
	free(account);
	n = 0;
}

Bank* menu_files(Bank *account, int &n) {

	cout << "1. Сохранить в файл\n2. Удалить файл\n3. Загрузить из файла\n0. Выход\n";
	switch (_getch()) {
	case 49: {
		system("cls");
		save_DB(account, n);
		break;
	}
	case 50: {
		system("cls");
		remove_DB();
		break;
	}
	case 51: {
		system("cls");
		account = load_DB(account, n);
		break;
	}
	case 48:
		system("cls"); break;
	}


	system("cls");
	return account;
}

void menu_sort(Bank *account, int &n) {					//Сортировка
	int i, j, step;

	cout << "\t\t\t\t\t~~~~~Сортировка~~~~~\n";
	cout << "1. По Ф.И.О\n";
	cout << "2. По лицевому счёту\n";
	cout << "3. По дате\n";
	cout << "4. По номеру карты\n";
	cout << "5. По сроку действия\n";
	cout << "6. По балансу\n";
	cout << "7. По номеру телефона\n";
	cout << "8. CVC\n";
	cout << "0. Выход\n";

	switch (_getch()) {
	case 49: {
		system("cls");
		cout << "1. По возрастанию\n2. По убыванию";
		switch (_getch()) {
		case 49: {
			system("cls");
			for (step = n / 2; step > 0; step /= 2)			//Фамилия
				for (i = step; i < n; i++) {
					account[n] = account[i];
					for (j = i; j >= step; j -= step) {
						if (strcmp(account[n].surname, account[j - step].surname) == -1 || (strcmp(account[n].surname, account[j - step].surname) == 0 && strcmp(account[n].name, account[j - step].name) == -1) || (strcmp(account[n].surname, account[j - step].surname) == 0 && strcmp(account[n].name, account[j - step].name) == 0 && strcmp(account[n].patronymic, account[j - step].patronymic) == -1))
							account[j] = account[j - step];
						else
							break;
					}
					account[j] = account[n];
				}
			break;
		}
		case 50: {
			system("cls");
			for (step = n / 2; step > 0; step /= 2)			//Фамилия
				for (i = step; i < n; i++) {
					account[n] = account[i];
					for (j = i; j >= step; j -= step) {
						if (strcmp(account[n].surname, account[j - step].surname) == 1 || (strcmp(account[n].surname, account[j - step].surname) == 0 && strcmp(account[n].name, account[j - step].name) == 1) || (strcmp(account[n].surname, account[j - step].surname) == 0 && strcmp(account[n].name, account[j - step].name) == 0 && strcmp(account[n].patronymic, account[j - step].patronymic) == 1))
							account[j] = account[j - step];
						else
							break;
					}
					account[j] = account[n];
				}
			break;
		}
		}
		break;
	}
	case 50: {
		system("cls");
		cout << "1. По возрастанию\n2. По убыванию";
		switch (_getch()) {
		case 49: {
			system("cls");
			for (step = n / 2; step > 0; step /= 2)			//Лицевой счёт
				for (i = step; i < n; i++) {
					account[n] = account[i];
					for (j = i; j >= step; j -= step) {
						if (strcmp(account[n].personal_account, account[j - step].personal_account) == -1)
							account[j] = account[j - step];
						else
							break;
					}
					account[j] = account[n];
				}
			break;
		}
		case 50: {
			system("cls");
			for (step = n / 2; step > 0; step /= 2)			//Лицевой счёт
				for (i = step; i < n; i++) {
					account[n] = account[i];
					for (j = i; j >= step; j -= step) {
						if (strcmp(account[n].personal_account, account[j - step].personal_account) == 1)
							account[j] = account[j - step];
						else
							break;
					}
					account[j] = account[n];
				}
			break;
		}
		}
		break;
	}
	case 51: {
		system("cls");
		cout << "1. По возрастанию\n2. По убыванию";
		switch (_getch()) {
		case 49: {
			system("cls");
			for (step = n / 2; step > 0; step /= 2)			//Дата
				for (i = step; i < n; i++) {
					account[n] = account[i];
					for (j = i; j >= step; j -= step) {
						if (account[n].year < account[j - step].year || (account[n].year == account[j - step].year && account[n].month < account[j - step].month) || (account[n].year == account[j - step].year && account[n].month == account[j - step].month && account[n].day < account[j - step].day))
							account[j] = account[j - step];
						else
							break;
					}
					account[j] = account[n];
				}
			break;
		}
		case 50: {
			system("cls");
			for (step = n / 2; step > 0; step /= 2)			//Дата
				for (i = step; i < n; i++) {
					account[n] = account[i];
					for (j = i; j >= step; j -= step) {
						if (account[n].year > account[j - step].year || (account[n].year == account[j - step].year && account[n].month > account[j - step].month) || (account[n].year == account[j - step].year && account[n].month == account[j - step].month && account[n].day > account[j - step].day))
							account[j] = account[j - step];
						else
							break;
					}
					account[j] = account[n];
				}
			break;
		}
		}
		break;
	}
	case 52: {
		system("cls");
		cout << "1. По возрастанию\n2. По убыванию";
		switch (_getch()) {
		case 49: {
			system("cls");
			for (step = n / 2; step > 0; step /= 2)			//Номер карты
				for (i = step; i < n; i++) {
					account[n] = account[i];
					for (j = i; j >= step; j -= step) {
						if (strcmp(account[n].number, account[j - step].number) == -1)
							account[j] = account[j - step];
						else
							break;
					}
					account[j] = account[n];
				}
			break;
		}
		case 50: {
			system("cls");
			for (step = n / 2; step > 0; step /= 2)			//Номер карты
				for (i = step; i < n; i++) {
					account[n] = account[i];
					for (j = i; j >= step; j -= step) {
						if (strcmp(account[n].number, account[j - step].number) == 1)
							account[j] = account[j - step];
						else
							break;
					}
					account[j] = account[n];
				}
			break;
		}
		}
		break;
	}
	case 53: {
		system("cls");
		cout << "1. По возрастанию\n2. По убыванию";
		switch (_getch()) {
		case 49: {
			system("cls");
			for (step = n / 2; step > 0; step /= 2)			//Срок действия
				for (i = step; i < n; i++) {
					account[n] = account[i];
					for (j = i; j >= step; j -= step) {
						if (strcmp(account[n].validity, account[j - step].validity) == -1)
							account[j] = account[j - step];
						else
							break;
					}
					account[j] = account[n];
				}
			break;
		}
		case 50: {
			system("cls");
			for (step = n / 2; step > 0; step /= 2)			//Срок действия
				for (i = step; i < n; i++) {
					account[n] = account[i];
					for (j = i; j >= step; j -= step) {
						if (strcmp(account[n].validity, account[j - step].validity) == 1)
							account[j] = account[j - step];
						else
							break;
					}
					account[j] = account[n];
				}
			break;
		}
		}
		break;
	}
	case 54: {
		system("cls");
		cout << "1. По возрастанию\n2. По убыванию";
		switch (_getch()) {
		case 49: {
			system("cls");
			for (step = n / 2; step > 0; step /= 2)			//Баланс
				for (i = step; i < n; i++) {
					account[n] = account[i];
					for (j = i; j >= step; j -= step) {
						if (account[n].balance < account[j - step].balance)
							account[j] = account[j - step];
						else
							break;
					}
					account[j] = account[n];
				}
			break;
		}
		case 50: {
			system("cls");
			for (step = n / 2; step > 0; step /= 2)			//Баланс
				for (i = step; i < n; i++) {
					account[n] = account[i];
					for (j = i; j >= step; j -= step) {
						if (account[n].balance > account[j - step].balance)
							account[j] = account[j - step];
						else
							break;
					}
					account[j] = account[n];
				}
			break;
		}
		}
		break;
	}
	case 55: {
		system("cls");
		cout << "1. По возрастанию\n2. По убыванию";
		switch (_getch()) {
		case 49: {
			system("cls");
			for (step = n / 2; step > 0; step /= 2)			//Номер телефона
				for (i = step; i < n; i++) {
					account[n] = account[i];
					for (j = i; j >= step; j -= step) {
						if (strcmp(account[n].phone_number, account[j - step].phone_number) == -1)
							account[j] = account[j - step];
						else
							break;
					}
					account[j] = account[n];
				}
			break;
		}
		case 50: {
			system("cls");
			for (step = n / 2; step > 0; step /= 2)			//Номер телефона
				for (i = step; i < n; i++) {
					account[n] = account[i];
					for (j = i; j >= step; j -= step) {
						if (strcmp(account[n].phone_number, account[j - step].phone_number) == 1)
							account[j] = account[j - step];
						else
							break;
					}
					account[j] = account[n];
				}
			break;
		}
		}
		break;
	}
	case 56: {
		system("cls");
		cout << "1. По возрастанию\n2. По убыванию";
		switch (_getch()) {
		case 49: {
			system("cls");
			for (step = n / 2; step > 0; step /= 2)			//CVC
				for (i = step; i < n; i++) {
					account[n] = account[i];
					for (j = i; j >= step; j -= step) {
						if (strcmp(account[n].cvc, account[j - step].cvc) == -1)
							account[j] = account[j - step];
						else
							break;
					}
					account[j] = account[n];
				}
			break;
		}
		case 50: {
			system("cls");
			for (step = n / 2; step > 0; step /= 2)			//CVC
				for (i = step; i < n; i++) {
					account[n] = account[i];
					for (j = i; j >= step; j -= step) {
						if (strcmp(account[n].cvc, account[j - step].cvc) == 1)
							account[j] = account[j - step];
						else
							break;
					}
					account[j] = account[n];
				}
			break;
		}
		}
		break;
	}
	case 48: {system("cls");  break; }
	default: system("cls");
	}
}

void menu_output(Bank *account, int &n) {
	cout << "Как вывести?\n";
	cout << "1. В формате <<поле: значение>>\n";
	cout << "2. В табличном формате\n";
	cout << "0. Выход\n";
	switch (_getch()) {
	case 49: {
		system("cls");
		for (int i = 0; i < n; i++) {
			cout << "ФИО: " << account[i].surname << " " << account[i].name << " " << account[i].patronymic << endl;
			cout << "Лицевой счёт: " << account[i].personal_account << endl;
			cout << "Дата регистрации: " << setfill('0') << setw(2) << account[i].day << "." << setfill('0') << setw(2) << account[i].month << "." << setw(4) << account[i].year << setfill(' ') << endl;
			cout << "Номер карты: " << account[i].number << endl;
			cout << "Срок действия карты: " << account[i].validity << endl;
			cout << "Баланс: " << account[i].balance << endl;
			cout << "Номер телефона: " << account[i].phone_number << endl;
			cout << "CVC2/CVV2 (код на обороте карты): " << account[i].cvc << endl;
			cout << "\n------------------------------------------------------\n";
		}
		break;
	}
	case 50: {
		system("cls");
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
		cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		for (int i = 0; i < n; i++) {
			cout << setw(3) << "|" << setw(21) << account[i].surname << "|" << setw(13) << "|" << setw(17) << "|" << setw(20) << "|" << setw(21) << "|\t" << setw(6) << "\t|" << setw(12) << "|" << setw(7) << "|" << endl;
			cout << setw(2) << i + 1 << "|" << setw(21) << account[i].name << "|"
				<< setw(12) << account[i].personal_account << "|   "
				<< setfill('0') << setw(2) << account[i].day << "." << setfill('0') << setw(2) << account[i].month << "." << setw(4) << account[i].year << "   |" << setfill(' ')
				<< setw(19) << account[i].number << "|"
				<< setw(19) << account[i].validity << "|"
				<< setw(9) << account[i].balance << "|"
				<< setw(11) << account[i].phone_number << "|"
				<< setw(6) << account[i].cvc << "|" << endl;
			cout << setw(3) << "|" << setw(21) << account[i].patronymic << "|" << setw(13) << "|" << setw(17) << "|" << setw(20) << "|" << setw(21) << "|\t" << setw(6) << "\t|" << setw(12) << "|" << setw(7) << "|" << endl;
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		}
		break;
	}
	case 48: {
		system("cls"); break;
	}
	default: system("cls");
	}
}

int search(Bank *account, int &n) {
	char buf[50];
	cout << "\t\t\t\t\t\t~~~~~Поиск данных~~~~~\n";
	cout << "1. ФИО\n";
	cout << "2. Лицевой счёт\n";
	cout << "3. Дата\n";
	cout << "4. Номер карты\n";
	cout << "5. Срок действия\n";
	cout << "6. Баланс\n";
	cout << "7. Номер телефона\n";
	cout << "8. CVC\n";
	cout << "0. Выход\n";

	switch (_getch()) {
	case 49: {
		system("cls");
		cout << "1. Фамилия\n";
		cout << "2. Имя\n";
		cout << "3. Отчество\n";
		switch (_getch()) {
		case 49: {
			system("cls");
			cout << "Фамилия: ";
			fflush(stdin);
			gets_s(buf);
			int count = 0;
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
			cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
			cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
			for (int i = 0; i < n; i++) {
				if (strstr(account[i].surname, buf) != 0) {
					Show_one(account, i);
					count++;
				}
			}
			if (count == 0) {
				printf("Cовпадений не найдено\n");
			}
			system("pause");
			break;
		}
		case 50: {
			system("cls");
			strcpy(buf, "");
			cout << "Имя: ";
			fflush(stdin);
			gets_s(buf);
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
			cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
			cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
			int count = 0;
			for (int i = 0; i < n; i++) {
				if (strstr(account[i].name, buf) != 0) {
					Show_one(account, i);
					count++;
				}
			}
			if (count == 0) {
				printf("Cовпадений не найдено\n");
			}
			system("pause");
			break;
		}
		case 51: {
			system("cls");
			strcpy(buf, "");
			cout << "Отчество: ";
			fflush(stdin);
			gets_s(buf);
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
			cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
			cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";

			int count = 0;
			for (int i = 0; i < n; i++) {
				if (strstr(account[i].patronymic, buf) != 0) {
					Show_one(account, i);
					count++;
				}
			}
			if (count == 0) {
				printf("Cовпадений не найдено\n");
			}
			system("pause");
			break;
		}

		case 48: return 0; break;
		default: system("cls"); break;
		}
		break;
	}
	case 50: {
		system("cls");
		strcpy(buf, "");
		cout << "Лицевой счет: ";
		fflush(stdin);
		gets_s(buf);
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
		cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";

		int count = 0;
		for (int i = 0; i < n; i++) {
			if (strstr(account[i].personal_account, buf) != 0) {
				Show_one(account, i);
				count++;
			}
		}
		if (count == 0) {
			printf("Cовпадений не найдено\n");
		}
		system("pause");
		break;
	}
	case 51: {
		cout << "\t\t\t\t\tДата\n";
		cout << "1. День\n";
		cout << "2. Месяц\n";
		cout << "3. Год\n";
		switch (_getch()) {
		case 49: {
			system("cls");
			strcpy(buf, "");
			cout << "День: ";
			fflush(stdin);
			gets_s(buf);
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
			cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
			cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";

			int count = 0;
			for (int i = 0; i < n; i++) {
				if (account[i].day == atoi(buf)) {
					Show_one(account, i);
					count++;
				}
			}
			if (count == 0) {
				printf("Cовпадений не найдено\n");
			}
			system("pause");
			break;
		}
		case 50: {
			system("cls");
			strcpy(buf, "");
			cout << "Месяц: ";
			fflush(stdin);
			gets_s(buf);
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
			cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
			cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";

			int count = 0;
			for (int i = 0; i < n; i++) {
				if (account[i].month == atoi(buf)) {
					Show_one(account, i);
					count++;
				}
			}
			if (count == 0) {
				printf("Cовпадений не найдено\n");
			}
			system("pause");
			break;
		}
		case 51: {
			system("cls");
			strcpy(buf, "");
			cout << "Год: ";
			fflush(stdin);
			gets_s(buf);
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
			cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
			cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";

			int count = 0;
			for (int i = 0; i < n; i++) {
				if (account[i].year == atoi(buf)) {
					Show_one(account, i);
					count++;
				}
			}
			if (count == 0) {
				printf("Cовпадений не найдено\n");
			}
			system("pause");
			break;
		}
		}
		break;
	}
	case 52: {
		system("cls");
		strcpy(buf, "");
		cout << "Номер карты: ";
		fflush(stdin);
		gets_s(buf);
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
		cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";

		int count = 0;
		for (int i = 0; i < n; i++) {
			if (strstr(account[i].number, buf) != 0) {
				Show_one(account, i);
				count++;
			}
		}
		if (count == 0) {
			printf("Cовпадений не найдено\n");
		}
		system("pause");
		break;
	}
	case 53: {
		system("cls");
		strcpy(buf, "");
		cout << "Срок действия: ";
		fflush(stdin);
		gets_s(buf);
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
		cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";

		int count = 0;
		for (int i = 0; i < n; i++) {
			if (strstr(account[i].validity, buf) != 0) {
				Show_one(account, i);
				count++;
			}
		}
		if (count == 0) {
			printf("Cовпадений не найдено\n");
		}
		system("pause");
		break;
	}
	case 54: {
		system("cls");
		strcpy(buf, "");
		cout << "Баланс: ";
		fflush(stdin);
		gets_s(buf);
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
		cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";

		int count = 0;
		for (int i = 0; i < n; i++) {
			if (account[i].day == atof(buf)) {
				Show_one(account, i);
				count++;
			}
		}
		if (count == 0) {
			printf("Cовпадений не найдено\n");
		}
		system("pause");
		break;
	}
	case 55: {
		system("cls");
		strcpy(buf, "");
		cout << "Номер телефона: ";
		fflush(stdin);
		gets_s(buf);
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
		cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";

		int count = 0;
		for (int i = 0; i < n; i++) {
			if (strstr(account[i].phone_number, buf) != 0) {
				Show_one(account, i);
				count++;
			}
		}
		if (count == 0) {
			printf("Cовпадений не найдено\n");
		}
		system("pause");
		break;
	}
	case 56: {
		system("cls");
		strcpy(buf, "");
		cout << "CVC: ";
		fflush(stdin);
		gets_s(buf);
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
		cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";

		int count = 0;
		for (int i = 0; i < n; i++) {
			if (strstr(account[i].cvc, buf) != 0) {
				Show_one(account, i);
				count++;
			}
		}
		if (count == 0) {
			printf("Cовпадений не найдено\n");
		}
		system("pause");
		break;
	}
	case 48: system("cls"); return 0; break;
	default: system("cls"); break;
	}
}

int edit(Bank *account, int &n) {
	if (n != 0) {
		char buf[50];
		int proverka;
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
		cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		for (int i = 0; i < n; i++) {
			cout << setw(3) << "|" << setw(21) << account[i].surname << "|" << setw(13) << "|" << setw(17) << "|" << setw(20) << "|" << setw(21) << "|\t" << setw(6) << "\t|" << setw(12) << "|" << setw(7) << "|" << endl;
			cout << setw(2) << i + 1 << "|" << setw(21) << account[i].name << "|"
				<< setw(12) << account[i].personal_account << "|   "
				<< setfill('0') << setw(2) << account[i].day << "." << setfill('0') << setw(2) << account[i].month << "." << setw(4) << account[i].year << "   |" << setfill(' ')
				<< setw(19) << account[i].number << "|"
				<< setw(19) << account[i].validity << "|"
				<< setw(9) << account[i].balance << "|"
				<< setw(11) << account[i].phone_number << "|"
				<< setw(6) << account[i].cvc << "|" << endl;
			cout << setw(3) << "|" << setw(21) << account[i].patronymic << "|" << setw(13) << "|" << setw(17) << "|" << setw(20) << "|" << setw(21) << "|\t" << setw(6) << "\t|" << setw(12) << "|" << setw(7) << "|" << endl;
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";

		}
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		cout << "\t\t\t\t\t\t~~~~~Редактирование данных~~~~~\n";
		cout << "Введите номер строки: ";
		do {
			strcpy_s(buf, "");
			gets_s(buf);
			proverka = 0;
			for (int i = 0; i < strlen(buf); i++)
			{
				if (buf[i] >= '0' && buf[i] <= '9') proverka++;
			}
			if (proverka != strlen(buf) || atoi(buf) > n || strlen(buf) == 0)
			{
				system("cls");
				cout << "----------------------------------------------------------------------------------------------------------------------------\n";
				cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
				cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
				cout << "----------------------------------------------------------------------------------------------------------------------------\n";
				for (int i = 0; i < n; i++) {
					cout << setw(3) << "|" << setw(21) << account[i].surname << "|" << setw(13) << "|" << setw(17) << "|" << setw(20) << "|" << setw(21) << "|\t" << setw(6) << "\t|" << setw(12) << "|" << setw(7) << "|" << endl;
					cout << setw(2) << i + 1 << "|" << setw(21) << account[i].name << "|"
						<< setw(12) << account[i].personal_account << "|   "
						<< setfill('0') << setw(2) << account[i].day << "." << setfill('0') << setw(2) << account[i].month << "." << setw(4) << account[i].year << "   |" << setfill(' ')
						<< setw(19) << account[i].number << "|"
						<< setw(19) << account[i].validity << "|"
						<< setw(9) << account[i].balance << "|"
						<< setw(11) << account[i].phone_number << "|"
						<< setw(6) << account[i].cvc << "|" << endl;
					cout << setw(3) << "|" << setw(21) << account[i].patronymic << "|" << setw(13) << "|" << setw(17) << "|" << setw(20) << "|" << setw(21) << "|\t" << setw(6) << "\t|" << setw(12) << "|" << setw(7) << "|" << endl;
					cout << "----------------------------------------------------------------------------------------------------------------------------\n";

				}
				cout << "----------------------------------------------------------------------------------------------------------------------------\n";
				cout << "\t\t\t\t\t\t~~~~~Редактирование данных~~~~~\n";
				cout << "Данные введены некорректно!\n";
				cout << "Введите номер строки: ";
			}
		} while (proverka != strlen(buf) || atoi(buf) > n || strlen(buf) == 0);

		if (atoi(buf) != 0) {
			int k = atoi(buf) - 1;
			system("cls");
			do {
				cout << "1. ФИО\n";
				cout << "2. Лицевой счёт\n";
				cout << "3. Дата\n";
				cout << "4. Номер карты\n";
				cout << "5. Срок действия\n";
				cout << "6. Баланс\n";
				cout << "7. Номер телефона\n";
				cout << "8. CVC\n";
				cout << "0. Выход\n";

				switch (_getch()) {
				case 49: {
					system("cls");
					cout << "1. Фамилия\n";
					cout << "2. Имя\n";
					cout << "3. Отчество\n";
					switch (_getch()) {
					case 49: {
						system("cls");
						do {
							do {
								cout << "Фамилия: ";
							} while (check_char(account, k, buf) == 0);
							strcpy(account[k].surname, buf);
						} while (strlen(account[k].surname) > 30 || strlen(account[k].surname) == 0);
						break;
					}
					case 50: {
						system("cls");
						do {
							do {
								cout << "Имя: ";
							} while (check_char(account, k, buf) == 0);
							strcpy(account[k].name, buf);
						} while (strlen(account[k].name) > 30 || strlen(account[k].name) == 0);
						break;
					}
					case 51: {
						system("cls");
						do {
							do {
								cout << "Отчество: ";
							} while (check_char(account, k, buf) == 0);
							strcpy(account[k].patronymic, buf);
						} while (strlen(account[k].patronymic) > 30 || strlen(account[k].patronymic) == 0);
						break;
					}
					case 48: return 0; break;
					default: system("cls"); break;
					}
					break;
				}
				case 50: {
					system("cls");
					do {
						do {
							cout << "Лицевой счёт: ";
						} while (check_int(account, k, buf) == 0);
						strcpy(account[k].personal_account, buf);
					} while (strlen(account[k].personal_account) != 7);
					break;
				}
				case 51: {
					system("cls");
					do {
						cout << "Дата регистрации(dd.mm.yyyy): ";
					} while (check_data(account, k, buf) == 0);
					break;
				}
				case 52: {
					system("cls");
					do {
						do {
							cout << "Номер карты(1234 5678 9101 2131): ";
						} while (check_number_card(account, k, buf) == 0);
						strcpy(account[k].number, buf);
					} while (strlen(account[k].number) != 19);
					break;
				}
				case 53: {
					system("cls");
					do {
						do {
							cout << "Срок действия карты (мм/гг): ";
						} while (check_validity(account, k, buf) == 0);
						strcpy(account[k].validity, buf);
					} while (strlen(account[k].validity) != 5);
					break;
				}
				case 54: {
					system("cls");
					do {
						cout << "Баланс: ";
					} while (check_char(account, k, buf) == 1);
					account[k].balance = atof(buf);
					break;
				}
				case 55: {
					system("cls");
					do {
						do {
							cout << "Номер телефона(331115522): ";
						} while (check_int(account, k, buf) == 0);
						strcpy(account[k].phone_number, buf);
					} while (strlen(account[k].phone_number) != 9);
					break;
				}
				case 56: {
					system("cls");
					do {
						int a = 0;
						do {
							cout << "CVC2/CVV2: ";
							cin.getline(buf, 50);
							while (isdigit(buf[a]))
								a++;
						} while (a != strlen(buf));
						strcpy(account[k].cvc, buf);
					} while (strlen(account[k].cvc) != 3);

					break;
				}
				case 48: system("cls"); return 0; break;
				default: system("cls"); break;
				}
			} while (!0);

		}
	}
	else {
		cout << "Данных нет, добавьте данные\n";
		system("pause");
		system("cls");
	}

}

void filtration(Bank *account, int &n) {
	char a, b;
	char s[5] = "";
	cout << "\t\t\t\t\t~~~~~Фильтрация~~~~~\n";
	cout << "1. По Ф.И.О\n";
	cout << "2. По лицевому счёту\n";
	cout << "3. По дате\n";
	cout << "4. По номеру карты\n";
	cout << "5. По сроку действия\n";
	cout << "6. По балансу\n";
	cout << "7. По номеру телефона\n";
	cout << "8. CVC\n";
	cout << "0. Выход\n";

	switch (_getch()) {
	case 49: {
		system("cls");
		cout << "1. Фамилия\n";
		cout << "2. Имя\n";
		cout << "3. Отчество\n";
		switch (_getch()) {
		case 49: {
			system("cls");
			cout << "\t\t\t\t\t~~~~~Фильтрация по первой букве~~~~~\n";
			cout << "От: "; cin >> a;
			cout << "До: "; cin >> b;
			system("cls");
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
			cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
			cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
			int count = 0;
			while (a <= b) {
				for (int i = 0; i < n; i++) {
					s[0] = account[i].surname[0];
					if (strchr(s, a) != 0) {
						Show_one(account, i);
						count++;
					}
				}
				a++;
			}
			if (count == 0) {
				printf("Cовпадений не найдено\n");
			}
			system("pause");
			break;
		}
		case 50: {
			system("cls");
			strcpy(s, "");
			cout << "\t\t\t\t\t~~~~~Фильтрация по первой букве~~~~~\n";
			cout << "От: "; cin >> a;
			cout << "До: "; cin >> b;
			system("cls");
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
			cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
			cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
			int count = 0;
			while (a <= b) {
				for (int i = 0; i < n; i++) {
					s[0] = account[i].name[0];
					if (strchr(s, a) != 0) {
						Show_one(account, i);
						count++;
					}
				}
				a++;
			}
			if (count == 0) {
				printf("Cовпадений не найдено\n");
			}
			system("pause");
			break;
		}
		case 51: {
			system("cls");
			strcpy(s, "");
			cout << "\t\t\t\t\t~~~~~Фильтрация по первой букве~~~~~\n";
			cout << "От: "; cin >> a;
			cout << "До: "; cin >> b;
			system("cls");
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
			cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
			cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
			int count = 0;
			while (a <= b) {
				for (int i = 0; i < n; i++) {
					s[0] = account[i].patronymic[0];
					if (strchr(s, a) != 0) {
						Show_one(account, i);
						count++;
					}
				}
				a++;
			}
			if (count == 0) {
				printf("Cовпадений не найдено\n");
			}
			system("pause");
			break;
		}
		}
		break;
	}
	case 50: {
		system("cls");
		strcpy(s, "");
		cout << "\t\t\t\t\t~~~~~Фильтрация по первой цифре~~~~~\n";
		cout << "От: "; cin >> a;
		cout << "До: "; cin >> b;
		system("cls");
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
		cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		int count = 0;
		while (a <= b) {
			for (int i = 0; i < n; i++) {
				s[0] = account[i].personal_account[0];
				if (strchr(s, a) != 0) {
					Show_one(account, i);
					count++;
				}
			}
			a++;
		}
		if (count == 0) {
			printf("Cовпадений не найдено\n");
		}
		system("pause");
		break;
	}
	case 51: {
		system("cls");
		cout << "1. День\n";
		cout << "2. Месяц\n";
		cout << "3. Год\n";
		switch (_getch()) {
		case 49: {
			system("cls");
			int x, y;
			cout << "\t\t\t\t\t~~~~~Фильтрация по дню~~~~~\n";
			cout << "От: "; cin >> x;
			cout << "До: "; cin >> y;
			system("cls");
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
			cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
			cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
			int count = 0;
			for (int i = 0; i < n; i++) {
				if (account[i].day >= x && account[i].day <= y) {
					Show_one(account, i);
					count++;
				}

			}
			if (count == 0) {
				printf("Cовпадений не найдено\n");
			}
			system("pause");
			break;
		}
		case 50: {
			system("cls");
			int x, y;
			cout << "\t\t\t\t\t~~~~~Фильтрация по месяцу~~~~~\n";
			cout << "От: "; cin >> x;
			cout << "До: "; cin >> y;
			system("cls");
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
			cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
			cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
			int count = 0;
			for (int i = 0; i < n; i++) {
				if (account[i].month >= x && account[i].month <= y) {
					Show_one(account, i);
					count++;
				}

			}
			if (count == 0) {
				printf("Cовпадений не найдено\n");
			}
			system("pause");
			break;
		}
		case 51: {
			system("cls");
			int x, y;
			cout << "\t\t\t\t\t~~~~~Фильтрация по году~~~~~\n";
			cout << "От: "; cin >> x;
			cout << "До: "; cin >> y;
			system("cls");
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
			cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
			cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
			cout << "----------------------------------------------------------------------------------------------------------------------------\n";
			int count = 0;
			for (int i = 0; i < n; i++) {
				if (account[i].year >= x && account[i].year <= y) {
					Show_one(account, i);
					count++;
				}

			}
			if (count == 0) {
				printf("Cовпадений не найдено\n");
			}
			system("pause");
			break;
		}
		}
		break;
	}
	case 52: {
		system("cls");
		strcpy(s, "");
		cout << "\t\t\t\t\t~~~~~Фильтрация по первой цифре~~~~~\n";
		cout << "От: "; cin >> a;
		cout << "До: "; cin >> b;
		system("cls");
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
		cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		int count = 0;
		while (a <= b) {
			for (int i = 0; i < n; i++) {
				s[0] = account[i].number[0];
				if (strchr(s, a) != 0) {
					Show_one(account, i);
					count++;
				}
			}
			a++;
		}
		if (count == 0) {
			printf("Cовпадений не найдено\n");
		}
		system("pause");
		break;
	}
	case 53: {
		system("cls");
		strcpy(s, "");
		cout << "\t\t\t\t\t~~~~~Фильтрация по первой цифре~~~~~\n";
		cout << "От: "; cin >> a;
		cout << "До: "; cin >> b;
		system("cls");
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
		cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		int count = 0;
		while (a <= b) {
			for (int i = 0; i < n; i++) {
				s[0] = account[i].validity[0];
				if (strchr(s, a) != 0) {
					Show_one(account, i);
					count++;
				}
			}
			a++;
		}
		if (count == 0) {
			printf("Cовпадений не найдено\n");
		}
		system("pause");
		break;
	}
	case 54: {
		system("cls");
		double x, y;
		cout << "\t\t\t\t\t~~~~~Фильтрация по балансу~~~~~\n";
		cout << "От: "; cin >> x;
		cout << "До: "; cin >> y;
		system("cls");
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
		cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		int count = 0;
		for (int i = 0; i < n; i++) {
			if (account[i].balance >= x && account[i].balance <= y) {
				Show_one(account, i);
				count++;
			}

		}
		if (count == 0) {
			printf("Cовпадений не найдено\n");
		}
		system("pause");
		break;
	}
	case 55: {
		system("cls");
		int x, y;
		cout << "\t\t\t\t\t~~~~~Фильтрация по номеру~~~~~\n";
		cout << "От: "; cin >> x;
		cout << "До: "; cin >> y;
		system("cls");
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
		cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		int count = 0;
		for (int i = 0; i < n; i++) {
			if (atoi(account[i].phone_number) >= x && atoi(account[i].phone_number) <= y) {
				Show_one(account, i);
				count++;
			}

		}
		if (count == 0) {
			printf("Cовпадений не найдено\n");
		}
		system("pause");
		break;
	}
	case 56: {
		system("cls");
		int x, y;
		cout << "\t\t\t\t\t~~~~~Фильтрация по CVC~~~~~\n";
		cout << "От: "; cin >> x;
		cout << "До: "; cin >> y;
		system("cls");
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		cout << "  |\t   Ф.И.О   \t|  Лицевой   |      Дата      |       Номер       |   Срок действия   |\tБаланс\t|   Номер   | CVC2 |\n";
		cout << " №|\t           \t|    счет    |   регистрации  |       карты       |       карты       |\t руб. \t|  телефона | CVV2 |\n";
		cout << "----------------------------------------------------------------------------------------------------------------------------\n";
		int count = 0;
		for (int i = 0; i < n; i++) {
			if (atoi(account[i].cvc) >= x && atoi(account[i].cvc) <= y) {
				Show_one(account, i);
				count++;
			}

		}
		if (count == 0) {
			printf("Cовпадений не найдено\n");
		}
		system("pause");
		break;
	}

	}
}

int menu(Bank *account, int &n) {
	do {
		cout << "1. Добавить запись\n2. Редактировать запись\n3. Вывести на экран\n4. Работа с файлами\n5. Поиск\n6. Сортировка\n7. Фильтрация\n8. Очистка памяти\n0. Выход\n";

		switch (_getch()) {
		case 49: { //1

			system("cls");
			n++;
			account = (Bank*)realloc(account, n * sizeof(Bank));
			input(account, n - 1);
			break; }
		case 50: { //2
			system("cls");
			edit(account, n);
			break;
		}
		case 51: { //3
			system("cls");
			menu_output(account, n);
			break;
		}
		case 52: { //4
			system("cls");
			account = menu_files(account, n);
			break;
		}
		case 53: { //5
			system("cls");
			search(account, n);
			break;
		}
		case 54: { //6
			system("cls");
			menu_sort(account, n);
			break;
		}
		case 55: {
			system("cls");
			filtration(account, n);
			break;
		}
		case 56: {
			system("cls");
			clear(account, n);
			break;
		}
		case 48:
			return 0; break;
		default: system("cls");
			break;
		}
		//system("cls");
	} while (!0);
}

int main() {
	setlocale(LC_ALL, "");

	int n = 0;
	Bank *account = NULL;
	account = (Bank*)malloc(n * sizeof(Bank));

	menu(account, n);

	system("pause");
	return 0;
}