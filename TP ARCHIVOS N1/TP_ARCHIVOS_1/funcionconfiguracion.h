#ifndef FUNCIONCONFIGURACION_H_INCLUDED
#define FUNCIONCONFIGURACION_H_INCLUDED

void menuconfiguracion()
{
    system("cls");
    int opconfi;
    bool salirmenuconfi = false;
    while(!salirmenuconfi)
    {
    cout << endl;
    cout << " MENU CONFIGURACION " << endl;
    cout <<" -------------------------------- " << endl;
    cout << " 1) REALIZAR COPIA DE SEGURIDAD " << endl;
    cout << " 2) RESTAURAR COPIA DE SEGURIDAD " << endl;
    cout << " ------------------------------- " << endl;
    cout << " 0) VOLVER AL MENU PRINCIPAL " << endl;
    cout << " ------------------------------- " << endl;
    cout << " OPCION ";
    cin >> opconfi;
    switch(opconfi)
    {
    case 1:
        {

        }break;
    case 2:
        {

        }break;
    case 0:
        {
          salirmenuconfi = true;
        }break;
    }
 }
}

#endif // FUNCIONCONFIGURACION_H_INCLUDED
