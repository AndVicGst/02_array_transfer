/*
Добавить в уже существующий класс Array конструктор
переноса, оператор присваивания переноса.
*/
#include <iostream>

using namespace std;

class Array {
private:
    int* mas;  // динамический массив
    int size_mas; //размер массива

    void clearMemory() { //очищаем память
        if (size_mas > 0) {
            delete[] mas;
            size_mas = 0;
        }
    }

    void copyArray(int* Arr, int size) { //копируем массив в созданный обьект Array
        clearMemory();                   //очищаем память, если нужно
        this->mas = new int[size];       //выделяем память
        this->size_mas = size;           //размер нашего массива
        for (int i = 0; i < size; i++)   //копируем данные из имеющегося массива в созданный обьект класса Array 
            this->mas[i] = Arr[i];
    }

public:
    Array(int* Arr, int size) {  //конструктор получает имеющийся массив (созданный уже)
        this->size_mas = 0;
        copyArray(Arr, size);
    }
    Array() : Array(nullptr, 0) {} //конструктор без параметров

    Array(const Array& arr) { copyArray(arr.mas, arr.size_mas); } // конструктор копирования

    Array& operator=(Array& arr) {       //оператор копирования
        if (&arr == this) return *this;  // если попробуем присвоить массив в самого себя, просто вернем массив без присваивания
        copyArray(arr.mas, arr.size_mas);
        return *this;
    }

    Array(Array&& arr) noexcept { //конструктор переноса
        mas = arr.mas;
        size_mas = arr.size_mas;
        arr.size_mas = 0; // обнуляем переданный размер массива, иначе ошибка деструктора - два обьекта указывают на одну и ту же память 
    }

    Array& operator=(Array&& arr) noexcept { //оператор переноса
        if (&arr == this) return *this; // если попробуем присвоить массив в самого себя, просто вернем массив без присваивания
        clearMemory(); //особождаем память
        mas = arr.mas;
        size_mas = arr.size_mas;
        arr.size_mas = 0; // обнуляем переданный размер массива, иначе ошибка деструктора - два обьекта указывают на одну и ту же память 
        return *this;
    }

    ~Array() { clearMemory(); } //деструктор вызывает функцию удаления массива и очистки памяти

    void printArr(string tmp) {   //выводим на экран массив, tmp - передаем название создаваемого обьекта, для вывода его на экран
        cout << "Обьект " << tmp << ":" << endl;
        if (size_mas > 0) {
            for (int i = 0; i < size_mas; i++)
                cout << mas[i] << " ";
            cout << endl << endl;
        }
        else {
            cout << "Массив пустой" << endl << endl;
        }
    }
};

int main()
{
    setlocale(LC_ALL, "RUS");
    cout << "------------Класс Array------------" << endl;
    cout << "--конструктор и оператор переноса--" << endl << endl;

    srand(time(NULL));
    int* A = new int[10];          //рандомный массив
    for (int i = 0; i < 10; i++)
        A[i] = rand() % 10;

    Array arr1(A, 10);          //создаем обьект через конструктор с 2 параметрами - передаем в него наш массив А и его размер 10
    arr1.printArr("arr1");

    Array arr2;                 //создаем обьект через конструктор без параметров (пустой массив)
    arr2.printArr("arr2");

    Array arr3 {arr1};          //создаем обьект через конструктор копирования
    arr3.printArr("arr3");

    Array arr4(arr3);           //создаем обьект через конструктор переноса
    arr4.printArr("arr4");

    Array arr5;                 //создаем обьект через оператор переноса
    arr5 = arr4;               
    arr5.printArr("arr5");

    arr1 = arr1;                //если обьект самого в себя скопировать, срабатывает проверка в конструкторе и обьект не изменяется  
    arr1.printArr("arr1 = arr1");

    system("pause");
    return 0;
}
