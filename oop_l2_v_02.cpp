#include <iostream>
#include <cmath> // for trunc and round
#include <cstring>
#include <map>
#include <cstdlib> // for exit
#include "oop_l2.h"

using namespace std;

int WhatIsIt(char c);

int main() {
    char str[40],   // вся введенная команда
        number[20], // число для умножения или деления, имеет значение для проверки на пустоту
        r[65],      // массив для считывания рублей
        k[17];      // массив для считывания копеек
    number[0] = 'E';
    char name1, name2, // имена объектов при вводе
        op;            // оператор
    float res,         // переменная для результата деления
        num;           // число, на которое умножаем или на которое делим объект
    size_t sz;
    Money X, Y, R;
    map<char, Money> dict = {{'X', X}, {'Y', Y}};

    //использование пользовательского литерала
    cout << "Convert 325465779876 kopecks to rubles using a custom literal:";
    R = 325465779876_kop;
    R.Show();

    cout << "\n\t############################\n"
            "\t    Calсulator of money\n"
            "\t############################\n\n"
            "type 'h' for help\n";

    while(1) {
        stop:
        cout << "> ";
        cin.getline(str, 40);
        sz = strlen(str);
        if (sz == 1) {
            switch (str[0]) {
            case 'h':
                cout << "n - create two new objects or replace old objects\n"
                        "object consists of two numbers: the first one is roubles, the second one is kopek\n"
                        "s - show all existing ojects\n"
                        "q - quit the program\n"
                        "'name_of_a_first_object' 'operation' 'name_of_a_second_object'/'a_number'\n"
                        "All numbers must have a positive value\n";
                break;
            case 'n':
                cout << " X = "; 
                cin.getline(r, 65, ' '); cin.getline(k, 17);
                try {X.Replace(r, k);} 
                catch (Money::Exeption) {
                    cerr << "ERROR: money cannot have a negative value or kopek cannot be over 99\n";
                    break;
                }
                dict.at('X') = X;
                r[65] = {0}; k[17] = {0};
                cout << " Y = "; cin.getline(r, 65, ' '); cin.getline(k, 17);
                try {Y.Replace(r, k);} 
                catch (Money::Exeption){
                    cerr << "ERROR: money cannot have a negative value or kopek cannot be over 99\n";
                    break;
                }
                dict.at('Y') = Y;
                break;
            case 's':
                cout << " X =";
                X.Show();
                cout << " Y =";
                Y.Show();
                break;
            case 'q':
                exit(0);
            default:
                cerr << "ERROR: wrong command\n";
                break;
            }

            ////////////// обработка выражений

        }else{
            int i = 0;
            if (WhatIsIt(str[i]) == 3) {
                name1 = str[i]; // запоминаем имя первого объекта
                i++;
                if (isspace(str[i])) i++;
                if (WhatIsIt(str[i]) == 1) op = str[i];
                else { cerr << "ERROR: operator is skipped\n"; break;}
                i++;
                if (isspace(str[i])) i++;
                if (WhatIsIt(str[i]) == 3) name2 = str[i];
                else if (WhatIsIt(str[i]) == 2) {
                    int k = sz - i;
                    for (int j = 0; j < k; j++) {number[j] = str[i]; i++;}
                    num = atof(number);
                }
                else {
                    cerr << "ERROR: What did you enter? (MONEY CANNOT HAVE A NEGATIVE VALUE)\n";
                    goto stop;
                }

                //////////////////// теперь точно обработка выражений

                switch (op) {
                case '+':
                    if (number[0] != 'E') {
                        cerr << "ERROR: add a number to money is impossible\n";
                        break;
                    }
                    R = dict.at(name1) + dict.at(name2);
                    R.Show();
                    break;
                case '-':
                    if (number[0] != 'E') {
                        cerr << "ERROR: it is impossible to subtract a number from money\n";
                        break;
                    }
                    try {R = dict.at(name1) - dict.at(name2);}
                    catch (Money::Exeption) {
                        cerr << "ERROR: money cannot have a negative value\n";
                        break;
                    }
                    R.Show();
                    break;
                case '*':
                    if (number[0] != 'E') {
                        R = dict.at(name1) * num;
                        R.Show();
                        break;
                    } else {
                        cerr << "ERROR: impossible to multiply money by money\n";
                        break;
                    }
                case '/':
                    if (number[0] != 'E') {
                        R = dict.at(name1) / num;
                        R.Show();
                        break;
                    } else {
                        try{
                            num = dict.at(name1) / dict.at(name2);
                            cout << num << endl;
                        }
                        catch(Money::Exeption){
                            cerr << "ERROR: division by zero\n";
                            break;
                        }
                        break;
                    }
                case '>':
                    if (number[0] != 'E') {
                        cerr << "ERROR: impossible to compare money with number\n";
                        break;
                    } else {
                        if (dict.at(name1) > dict.at(name2)) cout << "Right\n";
                        else cout << "Wrong\n";
                        break;
                    }
                case '<':
                    if (number[0] != 'E') {
                        cerr << "ERROR: impossible to compare money with number\n";
                        break;
                    } else {
                        if (dict.at(name1) < dict.at(name2)) cout << "Right\n";
                        else cout << "Wrong\n";
                        break;
                    }
                case '=':
                    if (number[0] != 'E') {
                        cerr << "ERROR: impossible to compare money with number\n";
                        break;
                    } else {
                        if (dict.at(name1) == dict.at(name2)) cout << "Right\n";
                        else cout << "Wrong\n";
                        break;
                    }
                }
                memset(number, 0, 65);
                number[0] = 'E';
                num = 0;
            } else cerr << "ERROR: What did you enter?\n";
        }
    }
}

int WhatIsIt(char c) {
    if (c == '+' || c == '*' || c == '/' || c == '-' || c == '>' || c == '<' || c == '=') return 1;
    else if (c >= '0' && c <= '9') return 2;
    else if (c == 'X' || c == 'Y') return 3;
    else if (c == 'n' || c == 'h' || c == 'q' || c == 's') return 4;
    else return 5;
}
