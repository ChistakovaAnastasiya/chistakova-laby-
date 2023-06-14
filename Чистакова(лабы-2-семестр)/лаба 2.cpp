#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <locale>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

//��� ������ ��� ���������� � ������
struct Characteristic {
    char fio[25];
    char registration[25];
    int registrationNumber;
};


//��� ������ ��� ������
struct Car {
    char model[25];
    char brand[25];
    int year;
    bool hasInsurance;
    Characteristic characteristic;
};

//��� ������ ��� ����� �����
typedef char TName[25];
//��� ������ ��� �������� ����������
typedef FILE TFile;
//���������� ��� ������
Car car;
//���������� ��� ����� �����
TName NameFile;
//�������� ����������
TFile *f;
//���� ������ ����� ��� ������
int flag = 0;

//** ����� ���� ************************************************************
void menu(void) {
    system("cls");
    cout << "******** � � � � ********\n\n"
         << "[1]-��������/�������� ��������������� �����\n"
         << "[2]-���������� � ���� �������\n"
         << "[3]-�������� �� ����� �������\n"
         << "[4]-�������� ����� �����\n"
         << "[5]-���������� ������ � �������� �������\n"
         << "[6]-���������� �������. ��������� ������� ��������� � ���������.\n"
         << "[ ESC ]-�����\n";
}

//** ���� ������ *****************************************************
void InputCar(Car &car) {
    cin.clear(); //�������� ����� � ����� ��������� ���������������� � 0
    while (!isspace(cin.get())) //���������� �� ����������� ��������� �����
        continue;
    cout << "���������� ������:\n";
    cout << "������������ ������ ->";
    cin.getline(car.model, 25);

    cout << "��� �������->";
    cin >> car.year;

    cin.clear(); //�������� ����� � ����� ��������� ���������������� � 0
    while (!isspace(cin.get())) //���������� �� ����������� ��������� �����
        continue;
    cout << "����� ������->";
    cin.getline(car.brand, 25);

    cout << "������� ��������� (true/false)->";
    cin >> car.hasInsurance;

    cout << "\n ����������� ��������������:\n";
    
    cout << "\t ����� �������������->";
    cin.clear();
    while (!isspace(cin.get()))
        continue;
    cin >> car.characteristic.registrationNumber;
	cin.clear();
    while (!isspace(cin.get()))
        continue;
    cout << "\t ����������� ��������->";
    cin.getline(car.characteristic.registration, 25);
    cin.clear();
    cout << "\t �.�.�->";
    gets(car.characteristic.fio);
    cout << "����� �����";

}

//** ����� ������ �� ����� ************************************************
void OutputCar(Car &car) {
    cout << "������������ ������ ������: " << car.model << "\n"
         << "������������ ����� ������: " << car.brand << "\n"
         << "������� ��������� � ������: " << (car.hasInsurance?"true":"false") << "\n"
         << "��� ������� ������: " << car.year << " �.\n"
         << "����������� �������������� ������:\n"
         << "\t�.�.�.: " << car.characteristic.fio << "\n"
         << "\t����� �������������:" << car.characteristic.registrationNumber << "\n"
         << "\t�����������/��������: " << car.characteristic.registration << "\n";
}

//** ��������/�������� ����� ���� ������ ********************************

void CreateOpenFile(TName &nameFile, int &flag) {
    char ch;
    flag = 0;
    cout << "������� ��� ����� ��� ������-->";
    //scanf("%s",&NameFile);
    gets(nameFile);
    f = fopen(nameFile, "r");
    if (f == NULL)
        do {
            system("cls");
            cout << "����� � ������ "
                 << nameFile
                 << " ���.\n\n"
                 << "������� ���� � ������ "
                 << nameFile;
            cout << "������� [ Y ] / [ N ]\n";
            ch = getch();
            if (ch == 'Y' || ch == 'y') {
                f = fopen(nameFile, "w");
                cout << "���� � ������ " << nameFile << " ������.\n"
                     << "\n\n��� ����������� ������� ����� �������\n";
                getch();
                flag = 1;
            }
            if (ch == 'N' || ch == 'n') {
                cout << "���� �� ������.\n"
                     << "\n\n��� ����������� ������� ����� �������\n";
                getch();
            }
        } while (!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));
    else {
        flag = 1;
        cout << "���� ������� ������\n"
             << "\n��� ����������� ������� ����� �������\n";
        getch();
    }
    fclose(f);
}

//** ���������� ������ (�����) � ���� (� ���� ������) **********
void RecordCar(TName NameFile, Car &car, int flag) {
    if (flag) {
        f = fopen(NameFile, "a");
        InputCar(car);
        fwrite(&car, sizeof(car), 1, f);
        fclose(f);
    } else {
        cout << "\n�������� ���� ��� ������.\n"
             << "������� [ 1 ] � ������� � � � �.";
        getch();
    }
}

//** ����� ����� (���� ������) �� ����� *****************
void FileOutput() {
    int i = 0;
    if (flag) {
        f = fopen(NameFile, "r+");

        cout << "********  ����� ����� �� �����  ********\n"
             << "****************************************\n";
        while (fread(&car, sizeof(Car), 1, f)) {
            //printf("%d",ftell(f));
            cout << "����� ������ = " << i + 1 << "\n\n";
            OutputCar(car);
            cout << "****************************************" << "\n";
            i++;
            if (i % 3 == 0)  //����� �� ��������� ������� (�����)
            {
                getch();
                system("cls");
                cout << "********  ����� ����� �� �����  ********\n"
                     << "****************************************\n";
            }
        }
        getch();
        fclose(f);
    } else {
        cout << "\n�������� ���� ��� ������.\n"
             << "������� [ 1 ] � ������� � � � �.";
        getch();
    }

}

//** ������ ����� *****************************
long filesize(TFile *f) {
    long curpos, length;
    curpos = ftell(f);        //���������� ������� ���������
    fseek(f, 0L, SEEK_END);    //���������� �� ����� �����
    length = ftell(f);        //���������� ��������� � ����� �����
    fseek(f, curpos, SEEK_SET);    //���������� �� ������ ���������
    return length;
}

//** ���������� ������ � �������� ������� ******
void UpdateCar(TName NameFile, Car &car, int flag) {
    long i = 0;
    if (flag) {
        f = fopen(NameFile, "r+");
        cout << "********  ���������� ������ � �������� �������  ********\n\n"
             << "********************************************************\n\n"
             << "������� ����� ������ ��� ���������� "
             << "�� "
             << (filesize(f) / sizeof(car))
             << " --> ";
        cin >> i;
        //long q;
        fpos_t q;
        //������������ �� ������ � ������� i
        fseek(f, (i - 1) * sizeof(car), SEEK_CUR);
        //���������� ������� ���������
        fgetpos(f, &q);

        fread(&car, sizeof(car), 1, f);
        OutputCar(car);
        cout << "****************************************\n";

        char ch;
        cout << "�������� ������?\n������� [ Y ] / [ N ]\n";
        do {
            //clrscr();
            ch = getch();
            if (ch == 'Y' || ch == 'y') {
                //������ ����� ��������
                InputCar(car);
                //��������� �� ������ �����
                fsetpos(f, &q);
                //���������� ����� ��������
                fwrite(&car, sizeof(car), 1, f);
                cout << "������ ���������.\n";
            }
            if (ch == 'N' || ch == 'n') {
                cout << "������ �� ����������.\n";
            }
        } while (!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));
        cout << "\n��� ����������� ������� ����� �������\n";
        getch();
        fclose(f);
    } else {
        cout << "\n�������� ���� ��� ������.\n"
             << "������� [ 1 ] � ������� � � � �.";
        getch();
    }
}

//** �������� ������ �� ���� **********************************
void DeleteCar(TName NameFile, Car &car, int flag) {
    long i = 0, k = 0;
    TFile *g;
    if (flag) {
        f = fopen(NameFile, "r+");

        cout << "********  �������� ������ � �������� �������  ********\n\n"
             << "********************************************************\n\n"
             << "������� ����� ������ ��� �������� "
             << "�� "
             << (filesize(f) / sizeof(car))
             << " --> ";
        cin >> i;

        //������������ �� ������ � ������� i
        fseek(f, (i - 1) * sizeof(car), SEEK_CUR);
        fread(&car, sizeof(car), 1, f);
        OutputCar(car);
        cout << "****************************************\n";

        char ch;
        cout << "������� ������?\n"
             << "������� [ Y ] / [ N ]\n";
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
                cout << "������ ���������.\n";
                fclose(g);
                fclose(f);
                remove(NameFile);    //������� ������ ����
                rename("Temp", NameFile);//��������������� ��������� ����
            }
            if (ch == 'N' || ch == 'n') {
                cout << "������ �� ����������.\n";
            }
        } while (!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));
        cout << "\n��� ����������� ������� ����� �������\n";
        getch();
        //fclose(f);
    } else {
        cout << "\n�������� ���� ��� ������.\n"
             << "������� [ 1 ] � ������� � � � �.";
        getch();
    }
}

//******************** ��� ������� *****************
void FindYear() {
    if (flag) {
        f = fopen(NameFile, "r");
        cout << "********  ����� � ����� ���� ���� �������� ������ ����� �����������  ********\n"
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
        cout << "******** ����� ����� ����������� ��� - " << frequentYear << "   ********\n"
             << "******** �� ����������� - " << numberOfEnterence << "   ���           ********\n"
             << "********************************************************\n";

        getch();
        fclose(f);
    } else {
        cout << "\n�������� ���� ��� ������.\n"
             << "������� [ 1 ] � ������� � � � �.";
        getch();
    }
}



//������ ���������

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
                CreateOpenFile(NameFile, flag); //�������� � �������� ����� ���� ������
                break;
            case '2':
                system("cls");
                RecordCar(NameFile, car, flag); //������ ������ � ����
                //getch();
                break;
            case '3':
                system("cls"); // �������� ������ �� ���� ������
                cout << "�������� ������ �� ���� ������\n";
                DeleteCar(NameFile, car, flag);
                getch();
                break;
            case '4':
                system("cls");    // ����� ����� �� �����
                FileOutput();
                break;
            case '5':
                system("cls");        //���������� ������ � �������� �������
                //printf("���������� ������ � �������� �������\n");
                UpdateCar(NameFile, car, flag);
                //getch();
                break;
            case '6':
                system("cls");
                cout << "���������� ������� � ������������ � ���������:\n"
                     << "����� �����������  � ���� ������\n";
                FindYear();
                getch();
                break;
            case '8':
                exit(1);
        }
    } while (ch != 27);
    return 0;
}
