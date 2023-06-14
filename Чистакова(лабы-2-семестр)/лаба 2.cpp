#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <locale>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

//тип данных для информации о машине
struct Characteristic {
    char fio[25];
    char registration[25];
    int registrationNumber;
};


//тип данных для машины
struct Car {
    char model[25];
    char brand[25];
    int year;
    bool hasInsurance;
    Characteristic characteristic;
};

//тип данных для имени файла
typedef char TName[25];
//тип данных для файловой переменной
typedef FILE TFile;
//переменная для машины
Car car;
//переменная для имени файла
TName NameFile;
//файловая переменная
TFile *f;
//флаг выбора файла для работы
int flag = 0;

//** вывод меню ************************************************************
void menu(void) {
    system("cls");
    cout << "******** М Е Н Ю ********\n\n"
         << "[1]-Создание/открытие типизированного файла\n"
         << "[2]-Добавление в файл записей\n"
         << "[3]-Удаление из файла записей\n"
         << "[4]-Просмотр всего файла\n"
         << "[5]-Обновление записи с заданным номером\n"
         << "[6]-Выполнение задания. Проверить наличие страховки и владельца.\n"
         << "[ ESC ]-Выход\n";
}

//** ввод машины *****************************************************
void InputCar(Car &car) {
    cin.clear(); //очистить поток и затем выставить позиционирование в 0
    while (!isspace(cin.get())) //Избавиться от результатов неверного ввода
        continue;
    cout << "Добавление машины:\n";
    cout << "Наименование модели ->";
    cin.getline(car.model, 25);

    cout << "Год выпуска->";
    cin >> car.year;

    cin.clear(); //очистить поток и затем выставить позиционирование в 0
    while (!isspace(cin.get())) //Избавиться от результатов неверного ввода
        continue;
    cout << "Марка машины->";
    cin.getline(car.brand, 25);

    cout << "Наличие страховки (true/false)->";
    cin >> car.hasInsurance;

    cout << "\n Технические характеристики:\n";
    
    cout << "\t Номер удостоверения->";
    cin.clear();
    while (!isspace(cin.get()))
        continue;
    cin >> car.characteristic.registrationNumber;
	cin.clear();
    while (!isspace(cin.get()))
        continue;
    cout << "\t Регистрация прописка->";
    cin.getline(car.characteristic.registration, 25);
    cin.clear();
    cout << "\t Ф.И.О->";
    gets(car.characteristic.fio);
    cout << "Конец ввода";

}

//** вывод машины на экран ************************************************
void OutputCar(Car &car) {
    cout << "Наименование модели машины: " << car.model << "\n"
         << "Наименование марки машины: " << car.brand << "\n"
         << "Наличие страховки у машины: " << (car.hasInsurance?"true":"false") << "\n"
         << "Год выпуска машины: " << car.year << " г.\n"
         << "Технические характеристики машины:\n"
         << "\tФ.И.О.: " << car.characteristic.fio << "\n"
         << "\tНомер удостоверения:" << car.characteristic.registrationNumber << "\n"
         << "\tРегистрация/прописка: " << car.characteristic.registration << "\n";
}

//** создание/открытие файла базы данных ********************************

void CreateOpenFile(TName &nameFile, int &flag) {
    char ch;
    flag = 0;
    cout << "Введите имя файла для работы-->";
    //scanf("%s",&NameFile);
    gets(nameFile);
    f = fopen(nameFile, "r");
    if (f == NULL)
        do {
            system("cls");
            cout << "ФАЙЛА с именем "
                 << nameFile
                 << " НЕТ.\n\n"
                 << "Создать файл с именем "
                 << nameFile;
            cout << "Нажмите [ Y ] / [ N ]\n";
            ch = getch();
            if (ch == 'Y' || ch == 'y') {
                f = fopen(nameFile, "w");
                cout << "Файл с именем " << nameFile << " создан.\n"
                     << "\n\nДля продолжения нажмите любую клавашу\n";
                getch();
                flag = 1;
            }
            if (ch == 'N' || ch == 'n') {
                cout << "Файл не создан.\n"
                     << "\n\nДля продолжения нажмите любую клавашу\n";
                getch();
            }
        } while (!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));
    else {
        flag = 1;
        cout << "Файл успешно открыт\n"
             << "\nДля продолжения нажмите любую клавашу\n";
        getch();
    }
    fclose(f);
}

//** добавление записи (машин) в файл (в базу данных) **********
void RecordCar(TName NameFile, Car &car, int flag) {
    if (flag) {
        f = fopen(NameFile, "a");
        InputCar(car);
        fwrite(&car, sizeof(car), 1, f);
        fclose(f);
    } else {
        cout << "\nВыберите файл для работы.\n"
             << "Нажмите [ 1 ] в разделе М Е Н Ю.";
        getch();
    }
}

//** вывод файла (базы данных) на экран *****************
void FileOutput() {
    int i = 0;
    if (flag) {
        f = fopen(NameFile, "r+");

        cout << "********  Вывод файла на экран  ********\n"
             << "****************************************\n";
        while (fread(&car, sizeof(Car), 1, f)) {
            //printf("%d",ftell(f));
            cout << "Номер записи = " << i + 1 << "\n\n";
            OutputCar(car);
            cout << "****************************************" << "\n";
            i++;
            if (i % 3 == 0)  //вывод по несколько записей (машин)
            {
                getch();
                system("cls");
                cout << "********  Вывод файла на экран  ********\n"
                     << "****************************************\n";
            }
        }
        getch();
        fclose(f);
    } else {
        cout << "\nВыберите файл для работы.\n"
             << "Нажмите [ 1 ] в разделе М Е Н Ю.";
        getch();
    }

}

//** размер файла *****************************
long filesize(TFile *f) {
    long curpos, length;
    curpos = ftell(f);        //запоминаем текущее положение
    fseek(f, 0L, SEEK_END);    //перемещаем на конец файла
    length = ftell(f);        //запоминаем положение в конце файла
    fseek(f, curpos, SEEK_SET);    //перемещаем на старое положение
    return length;
}

//** обновление записи с заданным номером ******
void UpdateCar(TName NameFile, Car &car, int flag) {
    long i = 0;
    if (flag) {
        f = fopen(NameFile, "r+");
        cout << "********  Обновление записи с заданным номером  ********\n\n"
             << "********************************************************\n\n"
             << "Введите номер записи для обновления "
             << "из "
             << (filesize(f) / sizeof(car))
             << " --> ";
        cin >> i;
        //long q;
        fpos_t q;
        //перемещаемся на запись с номером i
        fseek(f, (i - 1) * sizeof(car), SEEK_CUR);
        //запоминаем текущее положение
        fgetpos(f, &q);

        fread(&car, sizeof(car), 1, f);
        OutputCar(car);
        cout << "****************************************\n";

        char ch;
        cout << "Обновить данные?\nНажмите [ Y ] / [ N ]\n";
        do {
            //clrscr();
            ch = getch();
            if (ch == 'Y' || ch == 'y') {
                //вводим новые значения
                InputCar(car);
                //переходим на старое место
                fsetpos(f, &q);
                //записываем новые значения
                fwrite(&car, sizeof(car), 1, f);
                cout << "Данные обновлены.\n";
            }
            if (ch == 'N' || ch == 'n') {
                cout << "Данные не обновленны.\n";
            }
        } while (!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));
        cout << "\nДля продолжения нажмите любую клавашу\n";
        getch();
        fclose(f);
    } else {
        cout << "\nВыберите файл для работы.\n"
             << "Нажмите [ 1 ] в разделе М Е Н Ю.";
        getch();
    }
}

//** удаление машины из базы **********************************
void DeleteCar(TName NameFile, Car &car, int flag) {
    long i = 0, k = 0;
    TFile *g;
    if (flag) {
        f = fopen(NameFile, "r+");

        cout << "********  Удаление записи с заданным номером  ********\n\n"
             << "********************************************************\n\n"
             << "Введите номер записи для удаления "
             << "из "
             << (filesize(f) / sizeof(car))
             << " --> ";
        cin >> i;

        //перемещаемся на запись с номером i
        fseek(f, (i - 1) * sizeof(car), SEEK_CUR);
        fread(&car, sizeof(car), 1, f);
        OutputCar(car);
        cout << "****************************************\n";

        char ch;
        cout << "Удалить данные?\n"
             << "Нажмите [ Y ] / [ N ]\n";
        do {
            //clrscr();
            ch = getch();
            if (ch == 'Y' || ch == 'y') {
                fseek(f, 0L, SEEK_SET);
                cout << "****" << ftell(f);
                g = fopen("Temp", "w");
                while (fread(&car, sizeof(car), 1, f)) {
                    if (k != (i - 1)) fwrite(&car, sizeof(car), 1, g);
                    k++;
                }
                cout << "Данные обновлены.\n";
                fclose(g);
                fclose(f);
                remove(NameFile);    //удаляем старый файл
                rename("Temp", NameFile);//переименовываем временный файл
            }
            if (ch == 'N' || ch == 'n') {
                cout << "Данные не обновленны.\n";
            }
        } while (!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));
        cout << "\nДля продолжения нажмите любую клавашу\n";
        getch();
        //fclose(f);
    } else {
        cout << "\nВыберите файл для работы.\n"
             << "Нажмите [ 1 ] в разделе М Е Н Ю.";
        getch();
    }
}

//******************** моя функция *****************
void FindYear() {
    if (flag) {
        f = fopen(NameFile, "r");
        cout << "********  Поиск в каком году было выпущено больше всего автомобилей  ********\n"
             << "********************************************************\n";
        vector<int> vector;
        while (fread(&car, sizeof(car), 1, f)) {
            vector.push_back(car.year);
        }
        
        int frequentYear = -1;
        int numberOfEnterence = -1;
        for (int i = 0; i < vector.size(); i++) {
            int numberOfInclusion = 0;
            //cout<<vector[i]<<" ";
            for (int j = 0; j < vector.size(); j++) {
                if (vector[i] == vector[j]) {
                    numberOfInclusion++;
                }
            }
            if (numberOfInclusion > numberOfEnterence) {
                frequentYear = vector[i];
                numberOfEnterence=numberOfInclusion;
            }
        }
        cout<<endl;
        cout << "********************************************************\n";
        cout << "******** Самый часто встречаемый год - " << frequentYear << "   ********\n"
             << "******** Он встречается - " << numberOfEnterence << "   раз           ********\n"
             << "********************************************************\n";

        getch();
        fclose(f);
    } else {
        cout << "\nВыберите файл для работы.\n"
             << "Нажмите [ 1 ] в разделе М Е Н Ю.";
        getch();
    }
}



//Начало программы

int main() {
    setlocale(0, "");
    char ch;
    system("cls");
    do {
        menu();
        ch = getch();
        switch (ch) {
            case '1':
                system("cls");
                CreateOpenFile(NameFile, flag); //создание и открытие файла базы данных
                break;
            case '2':
                system("cls");
                RecordCar(NameFile, car, flag); //запись данных в файл
                //getch();
                break;
            case '3':
                system("cls"); // Удаление машины из базы данных
                cout << "Удаление машины из базы данных\n";
                DeleteCar(NameFile, car, flag);
                getch();
                break;
            case '4':
                system("cls");    // вывод файла на экран
                FileOutput();
                break;
            case '5':
                system("cls");        //Обновление записи с заданным номером
                //printf("Обновление записи с заданным номером\n");
                UpdateCar(NameFile, car, flag);
                //getch();
                break;
            case '6':
                system("cls");
                cout << "Выполнение задания в соответствии с вариантом:\n"
                     << "Поиск необходимой  в базе данных\n";
                FindYear();
                getch();
                break;
            case '8':
                exit(1);
        }
    } while (ch != 27);
    return 0;
}
