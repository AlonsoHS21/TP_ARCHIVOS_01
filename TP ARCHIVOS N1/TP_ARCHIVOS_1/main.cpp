#include <iostream>
#include <cstdlib>
#include <conio.h>

using namespace std;
#include "funcionmenuplatos.h"
#include <fstream>


int main()
{
    int opmenu;
    bool salirmenu = false;
    while(!salirmenu)
    {
        system("cls");
        cout << endl;
        cout << " MENU PRINCIPAL " << endl;
        cout << " ------------------------- " << endl;
        cout << " 1) PLATOS " << endl;
        cout << " ------------------------- " << endl;
        cout << " 0) SALIR DEL PROGRAMA " << endl;
        cout << " ------------------------- " << endl;
        cout << " OPCION : ";
        cin >>opmenu;
        switch(opmenu)
        {
        case 1:
            {
                menuplatos();
            }break;
        case 0:
            {
                salirmenu = true;
            }break;
        }
    }
    return 0;
}
