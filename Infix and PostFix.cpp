#include <iostream>
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
            return NULL;
        }
        x<T>* temp = HEAD;
        T re = temp->data;
        HEAD = HEAD->next;
        free(temp);
        return re;
    }

    T Print() {
        if (HEAD == NULL) {
            return NULL;
        }
        T re = HEAD->data;
        return re;
    }

    bool empty() {
        if (HEAD == NULL) {
            return true;
        }
        return false;
    }

    void clear() {
        while (!empty()) {
            pop();
        }
        HEAD = NULL;
    }
};


class ToolsforinfixandPostfix {
public:
    bool OperatorCheck(char c){
        if (c == '+' || c == '-' || c == '*' || c == '^' || c== '/'){
            return true;
        }
        else{
            return false;
        }
    }
    int OrderofPriority(char c){
        if (c == '^'){
            return 3;
        }
        else if (c == '*' || c == '/'){
            return 2;
        }
        else if (c == '+' || c == '-'){
            return 1;
        }
        else{
            return -1;
        }
    }
};

class Converstion {
private:
    ToolsforinfixandPostfix a;
    Stack <char> s;
public:

    void start() {
        string stringentered;
        cout << "Enter a String" << endl;
        cin >> stringentered;
        cout << "Infix : " << stringentered << " PostFix : " << infixtopostfix(stringentered) << " PreFix : " << infixtoprefix(stringentered) << endl;
        cout << Evaluation(infixtopostfix(stringentered)) << endl;
    }

    string reverse(string infix) {
        string temp;
        for (int i = infix.length() -1 ; i >=0 ; i--)
        {
            if (infix[i] == '(') {
                temp += ')';
           }
            else if (infix[i] == ')') {
                temp += '(';
            }
            else {
                temp += infix[i];
            }
        }
        return temp;
    }

    string infixtoprefix(string infix) {
         
        return reverse(infixtopostfix(reverse(infix)));
    }


    string infixtopostfix(string infix)
    {
        string postfix;
        for (int i = 0; i < infix.length(); i++)
        {
            if ((infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z'))
            {
                postfix += infix[i];
            }
            else if (infix[i] == '(')
            {
                s.push(infix[i]);
            }
            else if (infix[i] == ')')
            {
                while ((s.Print() != '(') && (!s.empty()))
                {
                    char temp = s.pop();
                    postfix += temp;
                }
            }
            else if (a.OperatorCheck(infix[i]))
            {
                if (s.empty())
                {
                    s.push(infix[i]);
                }
                else
                {
                    if (a.OrderofPriority(infix[i] > a.OrderofPriority(s.Print())))
                    {
                        s.push(infix[i]);
                    }
                    else if (a.OrderofPriority(infix[i] == a.OrderofPriority(s.Print())) && (infix[i] == '^'))
                    {
                        s.push(infix[i]);
                    }
                    else
                    {
                        while ( (a.OrderofPriority(infix[i]) <= a.OrderofPriority(s.Print())) && (!s.empty()))
                        {
                            char temp = s.pop();
                            postfix += temp;
                           
                        }
                        s.push(infix[i]);
                    }
                }

            }

        }
        while (!s.empty())
        {
            char temp;
            temp = s.pop();
                if (temp!=')' && temp!='(') {
                    postfix += temp;
                }
          
        }

        return postfix;
    }


    string Evaluation(string e) {
        Stack <string> k;
        for (int i = 0; i < e.length(); i++)
        {
            if (a.OperatorCheck(e[i])) {
                string t1 = k.pop();
                string t2 = k.pop();
                if (e[i]=='+') {
                    k.push(t1 +"+"+ t2);
                }
                if (e[i] == '-') {
                    k.push(t1 + "-" + t2);
                }
                if (e[i] == '*') {
                    k.push(t1 + "*" + t2);
                }
                if (e[i] == '/') {
                    k.push(t1 + "/" + t2);
                }
                if (e[i] == '^') {
                    k.push(t1 + "^" + t2);
                }
            }
            else {
                k.push(""+e[i]);
            }
        }
        return k.pop();
    }
   
};

int main()
{
    Converstion a;
    a.start();
}
