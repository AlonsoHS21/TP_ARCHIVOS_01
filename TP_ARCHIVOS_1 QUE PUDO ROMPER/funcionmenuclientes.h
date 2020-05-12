#ifndef FUNCIONMENUCLIENTES_H_INCLUDED
#define FUNCIONMENUCLIENTES_H_INCLUDED

#include "funcionesextra.h"

const char *PATH_CLIENTES = "ARCHIVOS_CLIENTES.dat";

struct fecha{
 int dia;
 int mes;
 int anos;
};

struct clientes{
int id;
char apellidos[50];
char nombres[50];
char mail[50];
char domicilio[100];
int cp;
fecha nacimiento;
bool estado;
};

int cantidad_clientes()
{
  int bytes,cr;
  FILE *p;
  p = fopen(PATH_CLIENTES,"rb");
  if(p == NULL){
    return 0;
  }
  fseek(p,0,SEEK_END);
  bytes = ftell(p);
  cr = bytes / sizeof(clientes);
  fclose(p);
  return cr;
}

bool guardar_cliente(struct clientes regcliente)
{
    FILE *p;
    p = fopen(PATH_CLIENTES,"ab");
    if(p == NULL){
        return false;
    }
    fwrite(&regcliente,sizeof(struct clientes),1,p);
    fclose(p);
    return true;
}

bool cadena_validacion(char *cadena) // NO VALIDA SI INGRESA PRIMERO UN ESPACIO (32)
{
  if(cadena[0] == '\0' || cadena[0] == '@' || cadena[0] == '.')
  {
      return true;
  }
  return false;
}

bool validacion_mail(char *cadena)
{

    if(cadena[0] == '\0' || cadena[0] == '@' || cadena[0] == '.' )
    {
        return true;
    }
    int x = 0;
    int cont_arroba = 0;
    int longitud = strlen(cadena);
    while(cadena[x] != '\0'){

        if(!(cadena[x] == '.')){
                return true;
        }
        if(cadena[x] == '@'){
            cont_arroba++;
            if(cont_arroba > 0){
                return true;
            }
        }
        x++;
    }
    if(cadena[longitud-1] == '.' || cadena[longitud-1] == ':'){
        return true;
    }
 return false;
}
bool vacio(char *cad)
{
    if(cad[0] == '\0'){
        return true;
    }
    return false;
}

bool cargar_cliente(clientes *regclientes)
{
    //faltan validaciones
    cout << " ================================ " << endl;
    cout << " ID DEL CLIENTE : ";
    regclientes->id = cantidad_clientes() + 1;
    cout << regclientes->id << endl;
    cin.ignore();
    cout << " NOMBRES DEL CLIENTE : ";
    cin.getline(regclientes->nombres,50);
    if(vacio(regclientes->nombres)){
        return false;
    }
    cout << " APELLIDOS DEL CLIENTE :  ";
    cin.ignore();
    cin.getline(regclientes->apellidos,50);
    if(vacio(regclientes->apellidos)){
        return false;
    }
    cout << " MAIL DEL CLIENTE : ";
    cin >> regclientes->mail;
    if(validacion_mail(regclientes->mail)){
        return false;
    }
    cout << " DOMICILIO DEL CLIENTE : ";
    cin.ignore();
    cin.getline(regclientes->domicilio,100);
    if(vacio(regclientes->domicilio)){
        return false;
    }
    cout << " CODIGO POSTAL ";
    cin >> regclientes->cp;
    if(regclientes->cp < 1000 || regclientes->cp > 9999 ){
        return false;
    }
    cout << " FECHA DE NACIMIENTO : " << endl;
    cout << " DIA --> ";
    cin >> regclientes->nacimiento.dia;
    if(regclientes->nacimiento.dia <= 0 || regclientes->nacimiento.dia > 31){
        return false;
    }
    cout << " MES --> ";
    cin >> regclientes->nacimiento.mes;
    if(regclientes->nacimiento.mes <=  0 || regclientes->nacimiento.mes > 12){
        return false;
    }
    cout << " AÑO --> ";
    cin >> regclientes->nacimiento.anos;
    if(regclientes->nacimiento.anos < 1920  || regclientes->nacimiento.anos > 2020 ){
        return false;
    }
    regclientes->estado = 1;
    cout << " ESTADO DEL CLIENTE : " << regclientes->estado << endl;
    getch();
    return true;
}

void mostrar_cliente(clientes reg)
{
    cout << endl;
    cout << " DATOS DEL CLIENTE " << reg.id << endl;
    cout << " ========================= " << endl;
    cout << " NOMBRE DEL CLIENTE    : " << " " << reg.nombres << endl;
    cout << " APELLIDO DEL CLIENTE  : " << " " << reg.apellidos << endl;
    cout << " MAIL DEL CLIENTE      : " << " " << reg.mail << endl;
    cout << " DOMICILIO DEL CLIENTE : " << " " << reg.domicilio << endl;
    cout << " FECHA DE NACIMIENTO   : " << " " <<reg.nacimiento.dia << "/" << reg.nacimiento.mes << "/" << reg.nacimiento.anos << endl;
    cout << " ESTADO DEL CLIENTE    : " << " " <<  reg.estado << endl;
}

int listar_cliente(int id)
{
    clientes reg;
    FILE *p;
    p = fopen(PATH_CLIENTES,"rb");
    if(p == NULL)
    {
        return -1;
    }
    while(fread(&reg,sizeof(clientes),1,p)){
        if(id == reg.id){
            mostrar_cliente(reg);
            getch();
            return 1;
        }
    }
  return -1;
}
int listar_cliente_totales()
{
    clientes reg;
    FILE *p;
    p = fopen(PATH_CLIENTES,"rb");
    if(p == NULL)
    {
        return -1;
    }
    fseek(p,0,SEEK_SET);
    while(fread(&reg,sizeof(clientes),1,p)){
            mostrar_cliente(reg);
    }
  fclose(p);
  return 1;
}


void validar(int num)
{
    cout << endl;
    switch(num)
    {
    case -1:
        {
            system("cls");
            cout << " *********************************** " << endl;
            cout << " NO SE PUDO ABRIR EL ARCHIVO CLIENTE " << endl;
            cout << " *********************************** " << endl;
        }break;
    case -2:
        {
            cout << " **************************** " << endl;
            cout << " NO SE PUDO MOSTAR EL CLIENTE " << endl;
            cout << " **************************** " << endl;
        }break;
    case 1:
        {
            cout << " ********************************** " << endl;
            cout << " SE MOSTRO EL CLIENTE CORRECTAMENTE " << endl;
            cout << " ********************************** " << endl;
        }break;
    }
}

int id_buscar(int id)
{
    clientes reg;
   int i = 0;
   FILE *p;
   p = fopen(PATH_CLIENTES,"rb");
   while(fread(&reg,sizeof(clientes),1,p)){
        if(id == reg.id){
           fclose(p);
           return i;
        }
    i++;
   }
 fclose(p);
 return -1;
}

bool listar_clientexid()
{
    system("cls");
    int id,pos;
    cout << " -------------------------- " << endl;
    cout << " INGRESE LA ID A BUSCAR : ";
    cin >> id;
    cout << " -------------------------- " << endl;
    if(id > 0)
    {
        pos = id_buscar(id);
        if(pos >= 0){
        int num = listar_cliente(id);
        if(num == -1){
                system("cls");
            cout << " *********************************** " << endl;
            cout << " NO SE PUDO ABRIR EL ARCHIVO CLIENTE " << endl;
            cout << " *********************************** " << endl;
            return false;

        }
        if(num == -2){
            system("cls");
            cout << " ****************** " << endl;
            cout << " NO SE PUDO MOSTRAR " << endl;
            cout << " ****************** " << endl;
            return false;
        }
        else{
            system("cls");
            cout << " *********************** " << endl;
            cout << " SE MOSTRO CORRECTAMENTE " << endl;
            cout << " *********************** " << endl;
            return true;
        }
    }
}
 return false;
}

bool modificar_cliente(clientes reg,int pos)
{
   bool sobreescribio;
   FILE *p;
   p = fopen(PATH_CLIENTES,"rb+");
   if(p == NULL){
    return false;
   }
   fseek(p,pos*sizeof(clientes),SEEK_SET);
   sobreescribio = fwrite(&reg,sizeof(clientes),1,p);
   fclose(p);
   cout << sobreescribio;
   getch();
   return sobreescribio;
}
int buscar_id_cliente(int id)
{
    int i = 0;
    FILE *p;
    p = fopen(PATH_CLIENTES,"rb");
    if(p == NULL){
        return -1;
    }
    struct clientes reg;
    while(fread(&reg,sizeof(struct clientes),1,p)){
        if(reg.id == id){
            fclose(p);
            return i;
        }
     i++;
    }
  fclose(p);
  return -1;
}

clientes devuelve_reg(int pos)
{
    clientes reg;
    FILE *p;
    p = fopen(PATH_CLIENTES,"rb"); // error : lo tenia en ab
    fseek(p, pos * sizeof(clientes),SEEK_SET);
    fread(&reg,sizeof(clientes),1,p);
    fclose(p);
    return reg;
}

bool editar_cliente()
{
    system("cls");
    int id_buscado,pos = -1;
    cout << "================================ " << endl;
    cout << " INGRESE LA ID DEL CLIENTE : ";
    cin >> id_buscado;
    cout << "================================ " << endl;
    if(id_buscado > 0){
        pos = id_buscar(id_buscado);
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
    if(pos >= 0){
        clientes reg = devuelve_reg(pos);
                   mostrar_cliente(reg);
                   cout << endl;
                   cout << " ======================================== " << endl;
                   cout << " INGRESE SU NUEVO DOMICILIO ";
                   cin >> reg.domicilio;
                   cout << " ======================================== " << endl;
                   if(reg.domicilio[0] == '\0'){
                    return false;
                   }
                   if(!(modificar_cliente(reg,pos))){
                   return false;
                   }

     }
     return true;
}

bool eliminar_cliente()
{
    clientes reg;
    int id_delete,pos;
    cout << " ========================================= " << endl;
    cout << " INGRESE LA ID DEL CLIENTE A ELIMINAR : ";
    cin >> id_delete;
    cout << " ========================================= " << endl;
   if(id_delete > 0){
       pos = buscar_id_cliente(id_delete);
    }
    else{
        system("cls");
        cout << endl;
        cout << " ============================================ " << endl;
        cout << " LA ID NO PUEDE SER UN NUMERO NEGATIVO O CERO " << endl;
        cout << " ============================================ " << endl;
    }
    if(pos >= 0){
          listar_cliente(id_delete);
          cout << endl;
          reg.estado = 0;
          if(modificar_cliente(reg,pos) >= 0){
            mostrar_cliente(reg);
            getch();
            return true;
      }
    }
    else{
        return false;
    }
return true;
}

void menuclientes()
{
    int opclientes;
    bool salirmenuclientes = false;
    while(!salirmenuclientes)
    {
        system("cls");
        cout << endl;
        cout << " MENU CLIENTES " << endl;
        cout << " ---------------------------- " << endl;
        cout << " 1) NUEVO CLIENTE " << endl;
        cout << " 2) MODIFICAR CLIENTE " << endl;
        cout << " 3) LISTAR CLIENTE POR ID " << endl;
        cout << " 4) LISTAR TODOS LOS CLIENTES " << endl;
        cout << " 5) ELIMINAR CLIENTE " << endl;
        cout << " ---------------------------- " << endl;
        cout << " 0) VOLVER AL MENU PRINCIPAL " << endl;
        cout << " ---------------------------- " << endl;
        cout << " OPCION : ";
        cin >> opclientes;
        switch(opclientes)
        {
        case 1:
            {
                system("cls");
                clientes regclientes;
                if(cargar_cliente(&regclientes)){
                    if(guardar_cliente(regclientes)){
                    system("cls");
                    cout << endl;
                    cout << " ================================= " << endl;
                    cout << " EL CLIENTE SE CARGO CORRECTAMENTE " << endl;
                    cout << " ================================= " << endl;
                    }
                    else{
                        system("cls");
                        cout << " ====================== " << endl;
                        cout << " NO SE CARGO EL CLIENTE " << endl;
                        cout << " ====================== " << endl;
                    }

                }
                else{
                    system("cls");
                    cout << " ====================== " << endl;
                    cout << " NO SE CARGO EL CLIENTE " << endl;
                    cout << " ====================== " << endl;
                }
                getch();
            }break;
        case 2:
            {
                if(editar_cliente()){
                    system("cls");
                    cout << " ---------------------- " << endl;
                    cout << " SE MODIFICO EL CLIENTE " << endl;
                    cout << " ---------------------- " << endl;
                }
                else{
                        system("cls");
                    cout << " ------------------------- " << endl;
                    cout << " NO SE MODIFICO EL CLIENTE " << endl;
                    cout << " ------------------------- " << endl;
                }
            }break;
        case 3:
            {
              if(!(listar_clientexid())){
                   system("cls");
                   cout << endl;
                   cout << " ---------------------------- " << endl;
                   cout << " NO SE PUDO MOSTAR EL CLIENTE " << endl;
                   cout << " ---------------------------- " << endl;
              }
              getch();
            }break;
        case 4:
            {
                system("cls");
                if(cantidad_clientes() > 0){
                        if(listar_cliente_totales() == 1){
                                cout << endl;
                                cout << " | ============================== | " << endl;
                                cout << " | SE LISTARON TODOS LOS CLIENTES |" << endl;
                                cout << " | ============================== | " << endl;
                        }
                }
                else{
                    cout << endl;
                    cout << " | =============================== | " << endl;
                    cout << " |    NO HAY CLIENTES CARGADOS     | " << endl;
                    cout << " | =============================== | " << endl;
                }
                getch();
            }break;
        case 5:
            {
                if(eliminar_cliente()){
                    system("cls");
                    cout << " +-+-+-+-+-+-+-+-+-+ " << endl;
                    cout << " SE ELIMINO EL PLATO " << endl;
                    cout << " +-+-+-+-+-+-+-+-+-+ " << endl;
                }
                else{
                    system("cls");
                    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ " << endl;
                    cout << " NO SE PUDO ELIMINAR EL PLATO " << endl;
                    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ " << endl;
                }

            }break;
        case 0:
            {
              salirmenuclientes = true;
            }break;
        }
    }
}

#endif // FUNCIONMENUCLIENTES_H_INCLUDED
