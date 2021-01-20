#include <iostream>
#include <windows.h>
#include <cmath>

using namespace std;
template <class T>
struct x {
    T data;
    x* next;
};

template <class T>
class Stack {
private:
    x<T>* HEAD = NULL;
public:
    void push(T data) {
        if (HEAD == NULL) {
            HEAD = new x<T>;
            HEAD->next = NULL;
            HEAD->data = data;
        }
        else {
            x<T>* temp = HEAD;
            x<T>* newnode = new x<T>;
            newnode->data = data;
            newnode->next = HEAD;
            HEAD = newnode;
        }
    }

    T pop() {
        if (HEAD == NULL) {
            T p = NULL;
            return p;
        }
        x<T>* temp = HEAD;
        T re = temp->data;
        HEAD = HEAD->next;
        free(temp);
        return re;
    }

    void Print() {
        x<T>* temp = HEAD;
        while (temp != NULL) {
            cout << temp->data<< " ";
            temp = temp->next;
        }
    }

    bool isEmpty() {
        if (HEAD == NULL) {
            return true;
        }
        return false;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
        HEAD = NULL;
    }
};

template <class T>
class TowerofHanaoi {
private:
    Stack <T> a;
    Stack <T> b;
    Stack <T> c;
public:
    void diskmovement(Stack<T> &a, Stack<T> &b) {
        if (b.isEmpty()) {
            b.push(a.pop());
        }
        else if (a.isEmpty()) {
            a.push(b.pop());
        }
        else {
            T temp_a = a.pop();
            T temp_b = b.pop();
            if (temp_b > temp_a) {
                b.push(temp_b);
                b.push(temp_a);
            }
            else {
                a.push(temp_a);
                a.push(temp_b);
            }
        }
    }
    void Intialize(int n) {
        for (int i = n; i >= 1; i--) {
            a.push(i);
        }
    }
    void ShowSource() {
        while (c.isEmpty() != true) {
            cout << c.pop() << endl;
        }
    }
    void FromStarttoEnd(int numberofdisk) {
        Intialize(numberofdisk);
        int numberofmoves = pow(2, numberofdisk) - 1;
        cout << numberofmoves << endl;
        int i = 1;

        if (numberofdisk % 2 == 0) {
            while (i <= numberofmoves) {
                if (i % 3 == 1) {
                    diskmovement(a, b);
                }
                else if (i % 3 == 2) {
                    diskmovement(a, c);
                }
                else {
                    diskmovement(b, c);
                }
                i++;
                system("cls");
                a.Print();
                cout << " -----Start" << endl;
                b.Print();
                cout << " -----Aux" << endl;
                c.Print();
                cout << " -----End" << endl;
                Sleep(450);
            }
            
        }
        else {
            while (i <= numberofmoves) {
                if (i % 3 == 1) {
                    diskmovement(a, c);
                }
                else if (i % 3 == 2) {
                    diskmovement(a, b);
                }
                else {
                    diskmovement(b, c);
                }
                i++;
                system("cls");

                a.Print();
                cout << " -----Start" << endl;
                b.Print();
                cout << " -----Aux" << endl;
                c.Print();
                cout << " -----End" << endl;
                Sleep(450);
            }
            
        }
        ShowSource();
    }
    
};


int main() {
    TowerofHanaoi<int> a;
    a.FromStarttoEnd(10);
}