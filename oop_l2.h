#include <iostream>
#include <cmath> // for trunc and round

const int ascii = 48; // для перевода char в числа

using namespace std;

class Money {
    unsigned long long roubles; // рубли
    unsigned char kopek;        // копейки
public:
    class Exeption {}; // исключения
    Money() : roubles(), kopek() {}
    Money(unsigned long long r, unsigned char k) : roubles(r), kopek(k) {} // конструктор
    void Replace(char *r, char *k);
    void Show();
    Money operator+(Money A);
    Money operator-(Money A);
    float operator/(Money A);
    friend Money operator/(Money A, float a);
    friend Money operator*(Money A, float a);
    bool operator>(Money A);
    bool operator<(Money A);
    bool operator==(Money A);
    void Converter(); // перевод лишних копеек в рубли
};

void Money::Show() { 
    cout << " " << roubles << ',';
    if(kopek < 10) cout << "0" << (int)kopek << endl;
    else cout << (int)kopek << endl;
}

void Money::Replace(char *r, char *k) {
    if (r[0] == '-' || k[0] == '-') throw Money::Exeption();
    size_t szr = strlen(r), szk = strlen(k);
    if(szk > 2) throw Money::Exeption();
    unsigned long long ro = 0;
    unsigned short ko = 0;
    for(int i = 0; i < szr; i++) ro += ((int)r[i] - ascii) * pow(10, szr - 1 - i);
    for(int i = 0; i < szk; i++) ko += ((int)k[i] - ascii) * pow(10, szk - 1 - i);
    roubles = ro; kopek = ko;
}

void Money::Converter() {
    if (kopek > 99) {
        roubles += kopek / 100;
        kopek %= 100;
    }
}

Money Money::operator+(Money A) {
    Money temp;
    temp.roubles = A.roubles + roubles;
    temp.kopek = A.kopek + kopek;
    temp.Converter();
    return temp;
}

Money Money::operator-(Money A) { 
    Money temp;
    if (roubles < A.roubles) throw Money::Exeption();
        if (kopek < A.kopek) {
            roubles--;
            kopek += 100;
        }
    temp.roubles = roubles - A.roubles;
    temp.kopek = kopek - A.kopek;
    return temp;
}

float Money::operator/(Money A) { 
    if (A.roubles == 0 && A.kopek == 0) throw Money::Exeption();
    float result = (roubles + (float)kopek / 100) / (A.roubles + (float)A.kopek / 100);
    return result; // получаем, во сколько раз одна сумма отличается от другой
}

Money operator/(Money A, float a) {
    if (a == 0) throw Money::Exeption();
    Money temp;
    float res = (A.roubles + (float)A.kopek / 100 )/ a;
    temp.roubles = trunc(res);
    temp.kopek = round((res - trunc(res)) * 100);
    return temp;
}

Money operator*(Money A, float a) {
    Money temp;
    float res = (A.roubles + (float)A.kopek / 100 )* a;
    temp.roubles = trunc(res);
    temp.kopek = round((res - trunc(res)) * 100);
    temp.Converter();
    return temp;
}

bool Money::operator>(Money A) {
    if (roubles > A.roubles) return 1;
    else if (roubles == A.roubles) {
        if (kopek > A.kopek) return 1;
        else return 0;
    } else return 0;
}

bool Money::operator<(Money A) {
    if (roubles < A.roubles) return 1;
    else if (roubles == A.roubles) {
        if (kopek < A.kopek) return 1;
        else return 0;
    } else return 0;
}

bool Money::operator==(Money A) {
    if (roubles == A.roubles) {
        if (kopek == A.kopek) return 1;
    } else return 0;
}

Money operator"" _kop(const char* str) // из копеек в рубли и копейки
{
    unsigned long long rub = 0;
    unsigned short kop;
    size_t size = strlen(str);
    rub = atol(str);
    kop = rub % (unsigned long long)pow(10, 2);
    rub = rub / pow(10, 2);
    return Money(rub, kop);
}