#include <iostream>
#include <Windows.h>
using namespace std;


//
//  main.cpp
//  Noteapad
//
//  Created by Musa Dildar Ahmed Cheema on 10/6/20.
//




struct refs {
    char data;
    refs* next;
    refs* back;
    refs* up;
    refs* down;
};

class Cursor {
private:
    refs* cursor;
    int x;
    int y;
public:
    int getx() {
        return x;
    }
    int gety() {
        return y;
    }
    void setx(int y) {
        x = y;
    }
    void sety(int x) {
        y = x;
    }
    refs* getcursor()
    {
        return cursor;
    }
    void setcursor(refs* C) {
        cursor = C;
    }
    void  cursorback() {
        if (cursor->back != NULL) {
            cursor = cursor->back;
        }
    }
    void  cursornext() {
        if (cursor->next != NULL) {
            cursor = cursor->next;
        }
    }
    void  cursorup() {
        if (cursor->up != NULL) {
            cursor = cursor->up;
        }
    }
    void  cursordown() {
        if (cursor->down != NULL) {
            cursor = cursor->down;
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
        refs *temp = dl;
        refs* head = dl;
        refs* lastendl = dl;
        while (temp->data != '\n' && temp->next != NULL) {
            temp = temp->next;
        }
        if (temp->next == NULL) {
            return;
        }
        else {
            while (temp->next != NULL) {
                temp = temp->next;
                temp->up = head;
                head->down = temp;
                lastendl = temp;
            }
        }
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

					case VK_UP: //up
						y--;
                        a.up();
						gotoxy(x, y);
						break;
					case VK_DOWN: //down
						y++;
                        a.down();
						gotoxy(x, y);
						break;
					case VK_RIGHT: //right
						x++;
                        a.right();
						gotoxy(x, y);
						break;
					case VK_LEFT: //left
						x--;
                        a.left();
						gotoxy(x, y);
						break;
					default:
                        system("cls");
                        if ((int(eventBuffer->Event.KeyEvent.uChar.AsciiChar)>63 && int(eventBuffer->Event.KeyEvent.uChar.AsciiChar)<128 )|| int(eventBuffer->Event.KeyEvent.uChar.AsciiChar) == 32) {
                            a.insertinline(eventBuffer->Event.KeyEvent.uChar.AsciiChar);
                            x++;
                            
                        }
                        else if (int(eventBuffer->Event.KeyEvent.uChar.AsciiChar) == 8) {            
                            a.deleteat();
                            x--;
                        }
                        else if (int(eventBuffer->Event.KeyEvent.uChar.AsciiChar) == 13) {
                                a.insertinline('\n');
                                x++;
                        }
                        a.display();
                  
                        gotoxy(x, y);
						break;
					}
				}

			} // end EventsRead loop

		}

	} // end program loop

	return 0;
}