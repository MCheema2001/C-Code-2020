#include <iostream>
#include <string>
using namespace std;


struct refs {
    string en;
    string md;
    string fn;
    string on;
    refs* next;
};


class Queue{
private:
    refs* dl;
public:
    void enqueue(refs* newDataItem) {
        if (dl == NULL) {
            dl = newDataItem;  
        }
        else {
            refs* temp = dl;
            while (temp->next != NULL) {
                temp = temp->next;
           }
            temp->next = newDataItem;
        }
    }
    refs* dequeue() {
        if (dl->next != NULL) {
            refs* temp = dl;
            dl = dl->next;
            refs* returnit = dl;
            cout << returnit->en;
            free(temp);
            return returnit;
        }
        return NULL;
    }
    void clear() {
        if (dl == NULL) {
            return;
        }
        while (dl->next!=NULL) {
            refs* temp = dl;
            dl = dl->next;
            refs* returnit = dl;
            free(temp);
        }
        dl = NULL;
    }
    bool isEmpty() {
        if (dl == NULL) {
            return true;
        }
        else {
            return false;
        }
    }
    ~Queue() {
        free(dl);
    }
    int getlength() {
        refs* temp = dl;
        int k = 0;
        while (temp != NULL) {
            temp = temp->next;
            k++;
        }
        return k;
    }
};

struct q {
    char data;
    q* next;
    q* nextarray;
};



class q2 {
private:
    q* dl=NULL;
public:
    void enqueue(q* newDataItem) {
        if (dl == NULL) {
            dl = new q;
            dl->nextarray = NULL;
            dl->next = newDataItem;
        }
        else {
            q* temp = dl;
            while (temp->nextarray!=NULL) {
               temp =  temp->nextarray;
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
    q* dequeue() {
        if (dl==NULL) {
            return NULL;
        }
        if (dl->next == NULL) {
            if (dl->nextarray == NULL) {
                return NULL;
            }
            else {
               dl= dl->nextarray;
            }
        }
        q* fre = dl;
        q* temp = dl->next;
        temp->nextarray = dl->nextarray;
        q* returnit = dl;
        dl = temp;
        free(fre);
        return returnit;
    }
    void stringtoqueue() {
       string str;
        cout << "Enter a String" << endl;
        getline(cin,str);
        getline(cin, str);
        cout << str;
        for (int i = 0; str[i]!='\0'; i++)
        {
            q *r=new q;
            r->next = NULL;
            r->nextarray = NULL;
            r->data = str[i];
            enqueue(r);
        }
    }
};


int main()
{
    Queue b;
    char l;
    cout << "Enter an Option" << endl;
    cout << "1)Question 1 and 3" << endl;
    cout << "2)Question 2" << endl;
    cin >> l;
    switch (l) {
    case '1': {
        while (true) {
            char l;
            cout << "Enter the Option." << endl;
            cout << "1) Insert" << endl;
            cout << "2) Remove" << endl;
            cout << "3) isEmpty" << endl;
            cout << "4) clear" << endl;
            cout << "5) get lenght" << endl;
            cout << "6) Exit" << endl;
            cin >> l;
            system("cls");
            switch (l) {
            case '1': {
                refs* a = new refs;
                string en;
                string md;
                string fn;
                string on;
                cout << "Enter Car Engine Number" << endl;
                cin >> en;
                cout << "Enter Car Engine Manufacture Date" << endl;
                cin >> md;
                cout << "Enter Car FN" << endl;
                cin >> fn;
                cout << "Enter Car Owner Name" << endl;
                cin >> on;
                a->next = NULL;
                b.enqueue(a);
                break;
            }
            case'2': {
                b.dequeue();
                break;
            }
            case '3': {
                cout << b.isEmpty() << endl;
                break;
            }
            case '4': {
                b.clear();
                break;
            }
            case '5': {
                cout << b.getlength() << endl;
                break;
            }
            case '6': {
                exit(0);
            }
            default: {
                cout << "Enter Correct" << endl;
            }
            }
        }
    }
    case'2': {
        q2 a;
        a.stringtoqueue();
        cout << endl << endl << a.dequeue()->data;
    }
    }
    
}

