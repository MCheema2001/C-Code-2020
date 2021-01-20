#include <iostream>
#include <Windows.h>
#include <fstream>

using namespace std;

//
//  main.cpp
//  Noteapad
//
//  Created by Musa Dildar Ahmed Cheema on 10/6/20.
//

struct refs {
    int x=0;
    int y=0;
    char data;
    refs* next;
    refs* back;
    refs* up;
    refs* down;
};

class Cursor {
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

class Link {
private:
    refs* dl;
    Cursor at;
    bool las = false;
    bool lyt = false;
public:
    Link() {

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
        else if (getcursor()->x == 1 && getcursor()->y == 0 && las==false && lyt==true) {
            refs* insert = new refs;
            insert->up = NULL;
            insert->back = NULL;
            insert->down = NULL;
            insert->data = a;
            insert->next = dl;
            dl = insert;
            at.setcursor(dl);
            las = true;
        }
        else {
            refs* temp = at.getcursor();
            refs* insert = new refs;
            if (temp->next == NULL) {
                insert->next = NULL;
            }
            else {
                insert->next = temp->next;
            }
            insert->up = NULL;
            insert->back = temp;
            insert->down = NULL;
            insert->data = a;
            temp->next = insert;
            at.setcursor(insert);
            las = false;
            lyt = true;
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
        refs* prev = dl;
        while (temp) {
            prev = temp;
            temp = temp->next;
        }
        while (prev) {
            cout << prev->data;
            prev = prev->back;
        }
        cout << endl;
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

    void upanddownlink() {
        refs* temp = dl;
        refs* head = dl;
        refs* lastendl = dl;

        int x = 0;
        int y = 0;
        while (temp != NULL) {

            if (temp->data == '\n') {
                y++;
                temp->y = y;
                x = 0;

            }
            else {
                x++;
                temp->x = x;
                temp->y = y;

            }
            if (temp != NULL) {
                temp = temp->next;
            }
        }
        temp = dl;
        while (temp->next != NULL) {
            temp->up = NULL;
            temp->down = NULL;
            temp = temp->next;
        }
        temp = dl;
    nextline:
        while (temp->data != '\n' && temp->next != NULL) {
            temp = temp->next;
        }
        lastendl = temp;
        if (temp->next == NULL) {
            return;
        }
        else {
            while (temp->next != NULL) {
                temp = temp->next;
                temp->up = head;
                if (head->next->data != '\n') {
                    head->down = temp;
                    head = head->next;
                }
                else {
                    if (temp->data == '\n') {
                        
                        head = lastendl->next;
                        lastendl = temp;
                    }
                }
            }
        }

    }

    void writetofile(string filename) {
        fstream f;
        f.open(filename+".txt", ios::out);
        refs* temp = dl;
        while (temp) {
            f << temp->data;
            temp = temp->next;
        }
    }
    void openfile(string filename){
    
        fstream fa;
        fa.open(filename);

        if (fa.is_open()) {
            char xa = '1';

            while (!fa.eof()) {
                fa.get(xa);
                cout << xa;
                insertinline(xa);
            }
        }
    }
    refs* getcursor()
    {
        return at.getcursor();
    }
};

void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
int main(int argc, char* argv[]) {
    Link a;
    system("cls");
    HANDLE  rhnd = GetStdHandle(STD_INPUT_HANDLE);  // handle to read console

    DWORD Events = 0;     // Event count
    DWORD EventsRead = 0; // Events read from console

    bool Running = true;

    int x = 0, y = 0;
    gotoxy(x, y);
    int line = 0;
    //programs main loop
    char menu;
    selectoption:
    cout << "Enter a Number in Menu to Select a Option." << endl;
    cout << "1) New" << endl;
    cout << "2) Load a File" << endl;
    cout << "3) Safe Mode Open New (File is Auto Saved and Progress is Saved no Matter Your Computer Accidently Shuts File can be Found as Safe.txt)" << endl;
    cin >> menu;
    switch (menu) {
    case '1':{
        system("cls");
        while (Running) {

            // gets the systems current "event" count
            GetNumberOfConsoleInputEvents(rhnd, &Events);

            if (Events != 0) { // if something happened we will handle the events we want

                // create event buffer the size of how many Events
                INPUT_RECORD eventBuffer[200];

                // fills the event buffer with the events and saves count in EventsRead
                ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead);

                // loop through the event buffer using the saved count
                for (DWORD i = 0; i < EventsRead; ++i) {

                    // check if event[i] is a key event && if so is a press not a release
                    if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown) {


                        // check if the key press was an arrow key
                        switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode) {

                        case VK_UP: //u
                            if (a.getcursor()->up != NULL) {
                                a.up();
                                gotoxy(a.getcursor()->x, a.getcursor()->y);
                            }
                            break;
                        case VK_DOWN: //down
                            if (a.getcursor()->down != NULL) {
                                a.down();
                                gotoxy(a.getcursor()->x, a.getcursor()->y);
                            }
                            break;
                        case VK_RIGHT: //right
                            if (a.getcursor()->next != NULL) {
                                a.right();
                                gotoxy(a.getcursor()->x, a.getcursor()->y);
                            }
                            break;
                        case VK_LEFT: //left
                            if (a.getcursor()->back != NULL) {
                                a.left();
                                gotoxy(a.getcursor()->x, a.getcursor()->y);
                            }
                            break;
                        case VK_ESCAPE:
                        {
                            system("cls");
                            string filename;
                            cout << "Enter Filename in which you want to save File" << endl;
                            cin >> filename;
                            a.writetofile(filename);
                            exit(0);
                            break;
                        }
                        default:
                            system("cls");
                            if ((int(eventBuffer->Event.KeyEvent.uChar.AsciiChar) > 63 && int(eventBuffer->Event.KeyEvent.uChar.AsciiChar) < 128) || int(eventBuffer->Event.KeyEvent.uChar.AsciiChar) == 32) {
                                a.insertinline(eventBuffer->Event.KeyEvent.uChar.AsciiChar);

                            }
                            else if (int(eventBuffer->Event.KeyEvent.uChar.AsciiChar) == 8) {
                                a.deleteat();

                            }
                            else if (int(eventBuffer->Event.KeyEvent.uChar.AsciiChar) == 13) {

                                a.insertinline('\n');
                            }
                            if (a.getcursor() != NULL) {
                                a.display();
                                gotoxy(a.getcursor()->x, a.getcursor()->y);
                            }
                            break;
                        }
                    }

                } // end EventsRead loop

            }

        } // end program loop
        break;
    }
    case '2': {
        string load;
        cout << "Enter Filename to Load." << endl;
        cin >> load;
        system("cls");
        a.openfile(load+".txt");
        while (Running) {

            // gets the systems current "event" count
            GetNumberOfConsoleInputEvents(rhnd, &Events);

            if (Events != 0) { // if something happened we will handle the events we want

                // create event buffer the size of how many Events
                INPUT_RECORD eventBuffer[200];

                // fills the event buffer with the events and saves count in EventsRead
                ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead);

                // loop through the event buffer using the saved count
                for (DWORD i = 0; i < EventsRead; ++i) {

                    // check if event[i] is a key event && if so is a press not a release
                    if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown) {


                        // check if the key press was an arrow key
                        switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode) {

                        case VK_UP: //u
                            if (a.getcursor()->up != NULL) {
                                a.up();
                                gotoxy(a.getcursor()->x, a.getcursor()->y);
                            }
                            break;
                        case VK_DOWN: //down
                            if (a.getcursor()->down != NULL) {
                                a.down();
                                gotoxy(a.getcursor()->x, a.getcursor()->y);
                            }
                            break;
                        case VK_RIGHT: //right
                            if (a.getcursor()->next != NULL) {
                                a.right();
                                gotoxy(a.getcursor()->x, a.getcursor()->y);
                            }
                            break;
                        case VK_LEFT: //left
                            if (a.getcursor()->back != NULL) {
                                a.left();
                                gotoxy(a.getcursor()->x, a.getcursor()->y);
                            }
                            break;
                        case VK_ESCAPE:
                        {
                            system("cls");
                            string filename;
                            cout << "Enter Filename in which you want to save File" << endl;
                            cin >> filename;
                            a.writetofile(filename);
                            exit(0);
                            break;
                        }
                        default:
                            system("cls");
                            if ((int(eventBuffer->Event.KeyEvent.uChar.AsciiChar) > 63 && int(eventBuffer->Event.KeyEvent.uChar.AsciiChar) < 128) || int(eventBuffer->Event.KeyEvent.uChar.AsciiChar) == 32) {
                                a.insertinline(eventBuffer->Event.KeyEvent.uChar.AsciiChar);

                            }
                            else if (int(eventBuffer->Event.KeyEvent.uChar.AsciiChar) == 8) {
                                a.deleteat();

                            }
                            else if (int(eventBuffer->Event.KeyEvent.uChar.AsciiChar) == 13) {

                                a.insertinline('\n');
                            }
                            if (a.getcursor() != NULL) {
                                a.display();
                                gotoxy(a.getcursor()->x, a.getcursor()->y);
                            }
                            break;
                        }
                    }

                } // end EventsRead loop

            }

        } // end program loop
        break;
    }
    case '3': {
        system("cls");
        while (Running) {

            // gets the systems current "event" count
            GetNumberOfConsoleInputEvents(rhnd, &Events);

            if (Events != 0) { // if something happened we will handle the events we want

                // create event buffer the size of how many Events
                INPUT_RECORD eventBuffer[200];

                // fills the event buffer with the events and saves count in EventsRead
                ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead);

                // loop through the event buffer using the saved count
                for (DWORD i = 0; i < EventsRead; ++i) {

                    // check if event[i] is a key event && if so is a press not a release
                    if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown) {


                        // check if the key press was an arrow key
                        switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode) {

                        case VK_UP: //u
                            if (a.getcursor()->up != NULL) {
                                a.up();
                                gotoxy(a.getcursor()->x, a.getcursor()->y);
                            }
                            break;
                        case VK_DOWN: //down
                            if (a.getcursor()->down != NULL) {
                                a.down();
                                gotoxy(a.getcursor()->x, a.getcursor()->y);
                            }
                            break;
                        case VK_RIGHT: //right
                            if (a.getcursor()->next != NULL) {
                                a.right();
                                gotoxy(a.getcursor()->x, a.getcursor()->y);
                            }
                            break;
                        case VK_LEFT: //left
                            if (a.getcursor()->back != NULL) {
                                a.left();
                                gotoxy(a.getcursor()->x, a.getcursor()->y);
                            }
                            break;
                        case VK_ESCAPE:
                        {
                            system("cls");
                            string filename;
                            cout << "Enter Filename in which you want to save File" << endl;
                            cin >> filename;
                            a.writetofile(filename);
                            exit(0);
                            break;
                        }
                        default:
                            system("cls");
                            if ((int(eventBuffer->Event.KeyEvent.uChar.AsciiChar) > 63 && int(eventBuffer->Event.KeyEvent.uChar.AsciiChar) < 128) || int(eventBuffer->Event.KeyEvent.uChar.AsciiChar) == 32) {
                                a.insertinline(eventBuffer->Event.KeyEvent.uChar.AsciiChar);

                            }
                            else if (int(eventBuffer->Event.KeyEvent.uChar.AsciiChar) == 8) {
                                a.deleteat();

                            }
                            else if (int(eventBuffer->Event.KeyEvent.uChar.AsciiChar) == 13) {

                                a.insertinline('\n');
                            }
                            if (a.getcursor() != NULL) {
                                a.display();
                                a.writetofile("Safe");
                                gotoxy(a.getcursor()->x, a.getcursor()->y);
                            }
                            break;
                        }
                    }

                } // end EventsRead loop

            }

        } // end program loop
        break;
    }
    default: {
        cout << "Enter a Valid Option." << endl;
        goto selectoption;
    }
    }
    

    return 0;
}