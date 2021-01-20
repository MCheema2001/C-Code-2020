#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;

template <class T>
struct q {
    T data;
    q* next;
    q* nextarray;
};


template <class T>
class q2 {
private:
    q <T>*dl = NULL;
public:
    void enqueue(q <T>* newDataItem) {
        if (dl == NULL) {
            dl = new q <T>;
            dl->nextarray = NULL;
            dl->next = newDataItem;
        }
        else {
            q <T> * temp = dl;
            while (temp->nextarray != NULL) {
                temp = temp->nextarray;
            }
            if (newDataItem->data == ' ')
            {
                temp->nextarray = newDataItem;
                return;
            }
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newDataItem;
        }
    }
    q<T>* dequeue() {
        if (dl == NULL) {
            return NULL;
        }
        if (dl->next == NULL) {
            if (dl->nextarray == NULL) {
                return NULL;
            }
            else {
                dl = dl->nextarray;
            }
        }
        q<T>* fre = dl;
        q<T>* temp = dl->next;
        temp->nextarray = dl->nextarray;
        q<T>* returnit = dl;
        dl = temp;
        free(fre);
        return returnit;
    }
    void stringtoqueue() {
        string str;
        cout << "Enter a String" << endl;
        getline(cin, str);
        getline(cin, str);
        cout << str;
        for (int i = 0; str[i] != '\0'; i++)
        {
            q<T>* r = new q;
            r->next = NULL;
            r->nextarray = NULL;
            r->data = str[i];
            enqueue(r);
        }
    }
};





template <class T>
struct x {
    T data;
    x* next;
};

template <class T>
class Stack {
private:
    x<T>* HEAD=NULL;
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

    int pop() {
        if (HEAD==NULL) {
            return NULL;
        }
        x<T>* temp = HEAD;
        T re = temp->data;
        HEAD = HEAD->next;
        free(temp);
        return re;
    }

    bool isEmpty() {
        if (HEAD==NULL) {
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
    
    bool compiler(string filename) {
        ifstream f;
        f.open(filename);
       
        char temp='a';
         f >> temp;
        cout << temp;
        if (f.is_open()) {
            while (!f.eof())
            {
                f >> temp;
                if (temp == '{' || temp == '}') {
                    push(temp);
                }
            }
        }
        Stack<T> b;
        while (isEmpty() == false && b.isEmpty() == false) {
            T check = pop();
            while (!isEmpty()) {
                T tempcheck = pop();
                if (check == tempcheck) {
                    b.push(tempcheck);
                    if (isEmpty() == true) {
                        return false;
                    }
                }
                else {
                    while (!b.isEmpty()) {
                        push(b.pop());
                    }
                }
            }
        }
        return true;
    }
};

int main()
{
    Stack<char> a;
    a.compiler("test1.txt");
    
    
}

