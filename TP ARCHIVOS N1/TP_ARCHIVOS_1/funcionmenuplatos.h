#ifndef FUNCIONMENUPLATOS_H_INCLUDED
#define FUNCIONMENUPLATOS_H_INCLUDED

#include <fstream>

const char *PATH_ARCHIVO = "ARCHIVO_PLATOS.dat";

struct pizzeria{
 int id;
 char nombre[50];
 float costo_preparacion;
 float valor_venta;
 int tiempo_preparacion;
 int id_restaurante;
 int comision_restaurante;
 int id_categoria;
 bool estado;
};

int buscar_id(int *id)
{
    int i = 0;
    FILE *p;
    p = fopen(PATH_ARCHIVO,"rb");
    if(p == NULL){
        return -1;
    }
    struct pizzeria reg;
    while(fread(&reg,sizeof(struct pizzeria),1,p)){
        if(reg.id == *id){
            fclose(p);
            return i;
        }
     i++;
    }
  fclose(p);
  return -1;
}
int buscar_id_restaurante(int *id)
{
    int i = 0;
    FILE *p;
    p = fopen(PATH_ARCHIVO,"rb");
    if(p == NULL){
        return -1;
    }
    struct pizzeria reg;
    while(fread(&reg,sizeof(struct pizzeria),1,p)){
        if(reg.id_restaurante == *id){
            fclose(p);
            return i;
        }
     i++;
    }
  fclose(p);
  return -1;
}

bool guardar_plato(struct pizzeria reg)
{
    FILE *p;
    p = fopen(PATH_ARCHIVO,"ab");
    if(p == NULL){
        return false;
    }
    fwrite(&reg,sizeof(struct pizzeria),1,p);
    fclose(p);
    return true;
}

bool cargar_plato(struct pizzeria *reg)
{
    int pos;
    cout << " ------------------------ " << endl;
    cout << " INGRESE EL ID : ";
    cin >> reg->id;
    pos = buscar_id(&(reg->id));
    if(reg->id < 0 || pos >= 0){
        return false;
    }
    cout << " NOMBRE : ";
    cin.ignore();
    cin.getline(reg->nombre,50);
    cout << " COSTO DE PREPARACION : ";
    cin >> reg->costo_preparacion;
    if(reg->costo_preparacion < 0 ){
        return false;
    }
    cout << " VALOR DE VENTA : ";
    cin >> reg->valor_venta;
    if(reg->valor_venta < 0 || reg->valor_venta < reg->costo_preparacion){
        return false;
    }
    cout << " TIEMPO DE PREPARACION : ";
    cin >> reg->tiempo_preparacion;
    if(reg->tiempo_preparacion < 0 ){
        return false;
    }
    cout << " ID RESTAURANTE : ";
    cin >> reg->id_restaurante;
    if(reg->id_restaurante < 0){
        return false;
    }
    cout << " COMISION RESTAURANTE : ";
    cin >> reg->comision_restaurante;
    if(reg->comision_restaurante < 0 || reg->comision_restaurante > 100){
        return false;
    }
    cout << " ID CATEGORIA : ";
    cin >> reg->id_categoria;
    if(reg->id_categoria < 0){
        return false;
    }
    reg->estado = 1;
    cout << " ESTADO DEL PLATO : " << reg->estado << endl;
    return true;
}
void mostrar_platos(pizzeria reg)
{
    cout << " =================================== " << endl;
    cout << endl;
    cout << "  ID DEL PLATO : " << "          " <<  reg.id << endl;
    cout << "  NOMBRE DEL PLATO : " << "      " << reg.nombre << endl;
    cout << "  COSTO DE PREPARACION : " << "  $" <<  reg.costo_preparacion << endl;
    cout << "  VALOR DE VENTA : " << "        $" << reg.valor_venta << endl;
    cout << "  TIEMPO DE PREPARACION : " <<" " << reg.tiempo_preparacion << "  MINUTOS " << endl;
    cout << "  ID RESTAURANTE : " << "        " <<reg.id_restaurante << endl;
    cout << "  COMISION RESTAURANTE : " << "  " <<  reg.comision_restaurante << "%"<< endl;
    cout << "  ID CATEGORIA : " << "          " <<reg.id_categoria << endl;
    cout << "  ESTADO DEL PLATO : " << "      " << reg.estado << endl;
    cout << endl;
}
pizzeria listar_plato_id(int pos)
{
    pizzeria reg;
    FILE *p;
    p = fopen(PATH_ARCHIVO,"rb");
    fseek(p, pos * sizeof(pizzeria),SEEK_SET);
    fread(&reg,sizeof(pizzeria),1,p);
    fclose(p);
    return reg;
    // ME MUESTRA EL REGISTRO PLATOS AUNQUE LA ID NO EXISTA SIEMPRE MUESTRA EL REGISTRO 1
}
int cantidad_platos()
{
  int bytes,cr;
  FILE *p;
  p = fopen(PATH_ARCHIVO,"rb");
  if(p == NULL){
    return 0;
  }
  fseek(p,0,SEEK_END);
  bytes = ftell(p);
  cr = bytes / sizeof(pizzeria);
  fclose(p);
  return cr;
}
void listar_platos()
{
    pizzeria reg;
    int cant = cantidad_platos(),i;
    for(i = 0;i<cant; i++)
    {
        reg = listar_plato_id(i);
        mostrar_platos(reg);
        cout << endl;
    }
}
bool sobreescribir_plato(pizzeria reg,int pos)
{
bool escribio;
  FILE * p;
  p = fopen(PATH_ARCHIVO,"rb+");
  if(p == NULL){
    return false;
  }
  fseek(p,pos * sizeof(pizzeria),SEEK_SET);
  escribio = fwrite(&reg,sizeof(pizzeria),1,p);
  fclose(p);
  return escribio;
}
bool editar_plato()
{
    int id_buscado,pos;
    cout << " INGRESE EL ID A EDITAR : ";
    cin >> id_buscado;
    pos = buscar_id(&id_buscado);
    if(pos >= 0){
        pizzeria reg = listar_plato_id(pos);
        cout << endl;
        mostrar_platos(reg);
        cout << " =================================== " << endl;
        cout << " NUEVO VALOR DE VENTA : ";
        cin >> reg.valor_venta;
        cout << " =================================== " << endl;
        if(reg.valor_venta < reg.costo_preparacion || reg.valor_venta < 0){
            return false;
        }
        cout << " NUEVO TIEMPO DE PREPARACION : ";
        cout << " =================================== " << endl;
        cin >> reg.tiempo_preparacion;
        if(reg.tiempo_preparacion < 0){
            return false;
        }
        if(!(sobreescribir_plato(reg,pos))){
             return false;
        }
    }
    else{
        cout << endl;
        cout << " | ========================= | " << endl;
        cout << " | EL ID INGRESADO NO EXISTE | " << endl;
        cout << " | ========================= | " << endl;
        cout << endl;
        getch();
        return false;
    }
    return true;
}
void menuplatos()
{
    int opplatos;
    bool salirmenuplatos = false;
    while(!salirmenuplatos)
    {
        system("cls");
        cout << endl;
        cout << " MENU PLATOS " << endl;
        cout << " --------------------- " << endl;
        cout << " 1) NUEVO PLATO " << endl;
        cout << " 2) MODIFICAR PLATO " << endl;
        cout << " 3) MOSTRAR PLATO POR ID " << endl;
        cout << " 4) PLATOS POR RESTAURANTE " << endl;
        cout << " 5) LISTAR TODOS LOS PLATOS " << endl;
        cout << " --------------------- " << endl;
        cout << " 0) VOLVER AL MENU PRINCIPAL " << endl;
        cout << " --------------------- " << endl;
        cout << " OPCION : ";
        cin >> opplatos;
        switch(opplatos)
        {
        case 1:
            {
                system("cls");
                pizzeria regplatos;
                if(cargar_plato(&regplatos)){
                        if(guardar_plato(regplatos)){
                         system("cls");
                         cout << endl;
                         cout << " | =============================== |" << endl;
                         cout << " | SE CARGO EL PLATO CORRECTAMENTE |" << endl;
                         cout << " | =============================== |" << endl;
                         cout << endl;
                         system("pause");
                        }
                }
                else
                {
                    system("cls");
                    cout << endl;
                    cout << " | =========================== |" << endl;
                    cout << " | NO SE PUDO CARGAR EL PLATO  |" << endl;
                    cout << " | =========================== |" << endl;
                    cout << endl;
                    system("pause");
                }
            }break;
        case 2:
            {
                system("cls");
                if(editar_plato()){
                    cout << endl;
                    cout << "|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-| " << endl;
                    cout << "|-   SE EDITO EL PLATO CORRECTAMENTE   -|" << endl;
                    cout << "|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-| " << endl;
                }
                else{
                    system("cls");
                    cout << endl;
                    cout << " |-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-| " << endl;
                    cout << " |-   NO SE PUDO EDITAR EL PLATO CORRECTAMENTE    -| " << endl;
                    cout << " |-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-| " << endl;
                }
                getch();
            }break;
        case 3:
            {
                system("cls");
                int id,pos;
                cout << " [ ------------------------------------- ]" << endl;
                cout << " [  INGRESE LA ID DEL PLATO A BUSCAR : ";
                cin >> id;
                cout << " [ ------------------------------------- ]" << endl;
                pos = buscar_id(&id);
                if( pos < 0 ){
                system("cls");
                cout << endl;
                cout << " | .............................. | " << endl;
                cout << " | NO SE ENCONTRO LA ID DEL PLATO | " << endl;
                cout << " |............................... | " << endl;
                }
                else{
                     cout << endl;
                     mostrar_platos(listar_plato_id(pos));
                }
                getch();
            }break;
        case 4:
            {
                system("cls");
                int id_restaurante,pos;
                cout << " +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ " << endl;
                cout << " +- INGRESE LA ID DEL RESTAURANTE A BUSCAR : ";
                cin >> id_restaurante;
                cout << " +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ " << endl;
                pos = buscar_id(&id_restaurante);
                if(pos < 0){
                    cout << endl;
                    cout << " ************************************ " << endl;
                    cout << " NO SE ENCONTRO LA ID DEL RESTAURANTE " << endl;
                    cout << " ************************************ " << endl;
                }
                else{
                    mostrar_platos(listar_plato_id(pos));
                }
                getch();
            }break;
        case 5:
            {
                system("cls");
                listar_platos();
                getch();
            }break;
        case 0:
            {
                salirmenuplatos = true;
            }break;
        }

    }
}

#endif // FUNCIONMENUPLATOS_H_INCLUDED
