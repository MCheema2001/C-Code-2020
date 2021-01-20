#include <iostream>
#include <fstream>

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
            //coordinates p;
           /* p.x = 0;
            p.y = 0;*/
            return NULL;
        }
        x<T>* temp = HEAD;
        T re = temp->data;
        HEAD = HEAD->next;
        free(temp);
        return re;
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





struct coordinates {
    int x;
    int y;
};




struct refs {
    int x = 0;
    int y = 0;
    char data;
    refs* next;
    refs* back;
    refs* up;
    refs* down;
};

class Movement {
private:
    refs* cursor;
public:
    refs* getcursor()
    {
        return cursor;
    }
    void setcursor(refs* C) {
        cursor = C;
    }
    void  cursorback() {
        if (cursor != NULL) {

            cursor = cursor->back;

        }
    }
    void  cursornext() {
        if (cursor != NULL) {
            if (cursor->next != NULL) {
                cursor = cursor->next;
            }
        }
    }
    void  cursorup() {
        if (cursor != NULL) {
            if (cursor->up != NULL) {
                cursor = cursor->up;
            }
        }
    }
    void  cursordown() {
        if (cursor != NULL) {
            if (cursor->down != NULL) {
                cursor = cursor->down;
            }
        }
    }
    void deleteatcursor() {
        if (cursor != NULL) {
            if (cursor->back != NULL) {
                cursor->back->next = cursor->next;
                refs* prev = cursor->back;
                free(cursor);
                cursor = prev;
            }
            else {
                cursor->data = '\0';
            }
        }
    }

};

class Maze {
private:
    refs* dl;
    Movement at;
    coordinates end;
    coordinates* array;
    coordinates size;
   // Stack<coordinates>pathat;
    int numberhurdles;
    bool las = false;
    bool lyt = false;
public:
    Maze() {
        string filename;
        cout << "File name to get Co-ordinates of maze from" << endl;
        cin >> filename;
        fstream f;
        f.open(filename, ios::in);
        int in = 0;
        int io = 0;
        int j = 0;
        for (int i = 0; !f.eof(); i++) {
            if (i == 2) {
                f >> in;
                numberhurdles = in;
                array = new coordinates[in];
            }
            else {
                f >> in;
                f >> io;
                if (i == 0) {
                    size.x = in;
                    size.y = io;
                }
                else if (i == 1) {
                    end.x = in;
                    end.y = io;
                }
                else {
                    array[j].x = in;
                    array[j].y = io;
                    j++;
                }
            }
        }
        for (int i = 0; i < size.x; i++) {
            for (int j = 0; j < size.y; j++) {
                insertinline(' ');
            }
        }
        makemaze();
    }
    void insertinline(char a) {

        if (dl == NULL) {
            dl = new refs;
            dl->next = NULL;
            dl->back = NULL;
            dl->up = NULL;
            dl->back = NULL;
            dl->data = a;
            at.setcursor(dl);
        }
        else {
            refs* temp = dl;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            refs* n = new refs;
            n->next = NULL;
            n->back = NULL;
            n->up = NULL;
            n->back = temp;
            n->data = a;
            temp->next = n;
        }
        upanddownlink();
    }
    void display() {
        refs* temp = dl;
        while (temp) {
            cout << temp->data;
            temp = temp->next;
        }
        cout << endl;
        temp = dl;
        while (temp) {
            cout << temp->x;
            temp = temp->next;
        }
        cout << endl;
        temp = dl;
        while (temp) {
            cout << temp->y;
            temp = temp->next;
        }
        cout << endl;
        if (dl) {
            cout << at.getcursor()->data << endl;
        }
    }
    void displayback() {
        refs* temp = dl;
        //        refs* prev = dl;
        while (temp) {
            cout << temp->x << " ";
            temp = temp->next;
        }
        //        while (prev) {
        //            cout << prev->data;
        //            prev = prev->back;
        //        }
        //        cout << endl;
    }

    void deleteat() {
        at.deleteatcursor();
    }
    void left() {
        at.cursorback();
    }
    void right() {
        at.cursornext();
    }
    void up() {
        at.cursorup();
    }
    void down() {
        at.cursordown();
    }
    void makemaze() {
        refs* temp = dl;
        while (temp != NULL) {
            if (temp->x == end.x && temp->y == end.y) {
                temp->data = 'E';
            }
            else {
                for (int i = 0; i < numberhurdles; i++)
                {
                    if (temp->x == array[i].x && temp->y == array[i].y) {
                        temp->data = '1';
                    }
                }
            }
            temp = temp->next;
        }

    }
    refs* getNode(int x, int y) {
        refs* temp = dl;
        while (temp) {
            if (temp->x == x && temp->y == y) {
                return temp;
            }
            temp = temp->next;
        }
        return temp;
    }
    void upanddownlink() {
        refs* temp = dl;
        int start_x = 0;
        int start_y = 0;
        while (temp != NULL) {
            temp->x = start_x;
            temp->y = start_y;
            temp = temp->next;
            if (start_x < 3) {
                start_x++;
            }
            else {
                start_y++;
                start_x = 0;
            }
        }
        temp = dl;
        refs* temp2 = dl;
        while (temp2->y == 0) {
            temp2 = temp2->next;
            if (temp2 == NULL) {
                break;
            }
        }
        while (temp2 != NULL) {
            temp->down = temp2;
            /*  cout << "(" << temp->x << "," << temp->y << ") ";
              cout << "(" << temp2->x << "," << temp2->y << ") ";*/
            cout << endl;
            temp2->up = temp;
            temp2 = temp2->next;
            temp = temp->next;
        }
    }
    void path() {
        int path_x = 0;
        int path_y = 0;
        bool reverse = true;
        refs* temp = dl;
        while (temp->x != end.x || temp->y != end.y) {
            if (getNode(path_x, path_y)->data == ' ') {
                if (getNode(path_x, path_y)->data != ' ' && getNode(path_x + 1, path_y)->data != ' ' && getNode(path_x - 1, path_y)->data != ' ' && getNode(path_x, path_y + 1)->data != ' ') {
                    cout << "No Path Found" << endl;
                }
                if (path_x == 2) {


                    if (getNode(path_x - 1, path_y + 1)->data == ' ') {
                        path_y++;
                        //
                        path_x--;
                        //
                        reverse = true;
                    }
                    else if (getNode(path_x, path_y + 1)->data == ' ') {
                        path_y++;
                    }

                }
                else if (path_x == 0) {
                    reverse = false;
                    if (getNode(path_x, path_y + 1)->data == ' ') {
                        path_y++;
                    }
                }
                else {
                    if (reverse == false) {
                        path_x++;
                    }
                    else {
                        path_x--;
                    }
                }
            }
        }
    }

    refs* getcursor()
    {
        return at.getcursor();
    }
};




int main(int argc, const char* argv[]) {
    Maze A;
    A.display();
    A.path();
    return 0;
}