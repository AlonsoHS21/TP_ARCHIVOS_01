#include <iostream>
#include <cstdlib>
#include <conio.h>

using namespace std;
#include "funcionmenuplatos.h"
#include <fstream>
#include <clocale>


int main()
{
    setlocale(LC_ALL,"spanish");
    int opmenu;
    bool salirmenu = false;
    while(!salirmenu)
    {
        system("cls");
        cout << endl;
        cout << " MENU PRINCIPAL " << endl;
        cout << " ------------------------- " << endl;
        cout << " 1) PLATOS " << endl;
        cout << " 2) CLIENTES " << endl;
        cout << " 3) PEDIDOS " << endl;
        cout << " 4) REPORTES " << endl;
        cout << " 5) CONFIGURACION " << endl;
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
