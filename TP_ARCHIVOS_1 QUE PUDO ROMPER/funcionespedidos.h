#ifndef FUNCIONESPEDIDOS_H_INCLUDED
#define FUNCIONESPEDIDOS_H_INCLUDED
#include "funcionmenuclientes.h"

const char*PATH_PEDIDOS = "ARCHIVO_PEDIDOS.dat";

struct Pedidos{
 int id;
 int id_cliente;
 int id_plato;
 int cantidad;
 float precio_unitario;
 fecha fecha_pedido;
 float valoracion;
 int estado;
};

int buscar_id_pedido(int id)
{
    int i = 0;
    FILE *p;
    p = fopen(PATH_PEDIDOS,"rb");
    if(p == NULL ){
        return -1;
    }
    struct Pedidos regpedidos;
    while(fread(&regpedidos,sizeof(Pedidos),1,p)){
        if(regpedidos.id == id){
            fclose(p);
            return i;
        }
     i++;
    }
fclose(p);
return -1;
}

int cantidad_pedidos()
{
  int bytes,cr;
  FILE *p;
  p = fopen(PATH_PEDIDOS,"rb");
  if(p == NULL){
    return 0;
  }
  fseek(p,0,SEEK_END);
  bytes = ftell(p);
  cr = bytes / sizeof(Pedidos);
  fclose(p);
  return cr;
}
bool guardar_pedido(struct Pedidos reg)
{
    FILE *p;
    p = fopen(PATH_PEDIDOS,"ab");
    if(p == NULL){
       return false;
    }
    fwrite(&reg,sizeof(Pedidos),1,p);
    fclose(p);
    return true;
}
int buscar_valor_venta(float preciouni)
{
    FILE *p;
    p = fopen(PATH_ARCHIVO,"rb");
    if( p == NULL){
        return -1;
    }
    pizzeria reg;
    while(fread(&reg,sizeof(pizzeria),1,p)){
         if(preciouni == reg.valor_venta){
            fclose(p);
            return 1;
          }
    }
 fclose(p);
 return -1;
}

bool cargar_pedido(Pedidos *reg)
{
    int id_cliente,id_plato;
    float precio_unitario;
    reg->id = cantidad_pedidos() + 1;
    cout << " INGRESE LA ID DEL PEDIDO   : " << reg->id << endl;
    cout << " INGRESE LA ID DEL CLIENTE  : ";
    cin >> id_cliente;
    if(buscar_id_cliente(id_cliente) == -1){
        return false;
    }
    reg->id_cliente = id_cliente;
    cout << " INGRESE LA ID DEL PLATO    : ";
    cin >> id_plato;
    if(buscar_id(&id_plato) == -1){
        return false;
    }
    reg->id_plato = id_plato;
    cout << " INGRESE LA CANTIDAD        : ";
    cin >> reg->cantidad;
    if(reg->cantidad < 0){
        return false;
    }
    cout << " INGRESE EL PRECIO UNITARIO : ";
    cin >> precio_unitario;
    if(buscar_valor_venta(precio_unitario) == -1){
        return false;
    }
    reg->precio_unitario = precio_unitario;
    cout << " FECHA DE PEDIDO " << endl;
    cout << " DIA : ";
    cin >> reg->fecha_pedido.dia;
    if(reg->fecha_pedido.dia <= 0 || reg->fecha_pedido.dia > 31 ){
        return false;
    }
    cout << " MES : ";
    cin >> reg->fecha_pedido.mes;
    if(reg->fecha_pedido.mes <= 0 || reg->fecha_pedido.mes > 12 ){
        return false;
    }
    cout << " AÑO : ";
    cin >> reg->fecha_pedido.anos;
    if(reg->fecha_pedido.anos < 2020 ){
        return false;
    }
    cout << " VALORACION : ";
    cin >> reg->valoracion;
    if(reg->valoracion < 0 || reg->valoracion > 10 ){
        return false;
    }
    reg->estado = 1;
    cout << " ESTADO DEL PEDIDO : " << reg->estado << endl;
    getch();
 return true;
}

void mostrar_pedido(Pedidos reg)
{
    cout << " ------------------------------------/ " << endl;
    cout << " ID DEL PEDIDO     : " << " " << reg.id << endl;
    cout << " ID CLIENTE        : " << " " << reg.id_cliente << endl;
    cout << " ID DEL PLATO      : " << " " << reg.id_plato << endl;
    cout << " CANTIDAD          : " << " " << reg.cantidad << endl;
    cout << " PRECIO UNITARIO   : " << " " << reg.precio_unitario << "$" << endl;
    cout << " FECHA DE PEDIDO   : " << " " << reg.fecha_pedido.dia << "/" << reg.fecha_pedido.mes << "/" << reg.fecha_pedido.anos << endl;
    cout << " VALORACION        : " << " " << reg.valoracion << endl;
    cout << " ESTADO DEL PEDIDO : " << " " << reg.estado << endl;
    cout << " ----------------------------------/ " << endl;
}

Pedidos listar_pedido_por_id(int pos)
{
   Pedidos reg;
   FILE *p;
   p = fopen(PATH_PEDIDOS,"rb");
   fseek(p,pos * sizeof(Pedidos),SEEK_SET);
   fread(&reg,sizeof(Pedidos),1,p);
   fclose(p);
   return reg;
}

bool sobreescribir_pedido(Pedidos reg,int pos)
{
    bool sobreescribio = false;
    FILE *p;
    p = fopen(PATH_PEDIDOS,"rb+");
    if(p == NULL){
        return sobreescribio;
    }
    fseek(p, pos * sizeof(Pedidos),SEEK_SET);
    sobreescribio = fwrite(&reg,sizeof(Pedidos),1,p);
    fclose(p);
    return sobreescribio;
}

bool modificar_pedido()
{
    int id_buscado,pos = -1;
    cout << " INGRESE LA ID DEL PEDIDO ";
    cin >> id_buscado;
    if(id_buscado > 0){
        pos = buscar_id_pedido(id_buscado);
    }
    else{
    system("cls");
    cout << endl;
    cout << " | ========================= | " << endl;
    cout << " | EL ID INGRESADO NO EXISTE | " << endl;
    cout << " | ========================= | " << endl;
    cout << endl;
    getch();
    return false;
    }
    if(pos >= 0){
        Pedidos reg = listar_pedido_por_id(pos);
        cout << endl;
        mostrar_pedido(reg);
        cout << " ================================================== " << endl;
        cout << " INDIQUE EL NUEVO ESTADO DEL PLATO ( 1-2-3) : " ;
        cin >> reg.estado;
        if(reg.estado < 0 || reg.estado > 3){
            return false;
        }
        cout << " ================================================== " << endl;
        if(!(sobreescribir_pedido(reg,pos))){
                return false;
    }
   }
   return true;
}

bool listar_por_id()
{
    int id,pos = -1;
    cout << " ======================================= " << endl;
    cout << " INGRESE LA ID DEL PEDIDO A LISTAR : ";
    cin >> id;
    cout << " ======================================= " << endl;
    if(id > 0){
        pos = buscar_id_pedido(id);
    }
    else{
        return false;
    }
    if(pos >= 0 ){
            system("cls");
            Pedidos aux = listar_pedido_por_id(pos);
            mostrar_pedido(aux);
    }
    else{
        system("cls");
        cout <<" =========================== " << endl;
        cout << " NO EXISTE EL ID DEL PEDIDO " << endl;
        cout <<" =========================== " << endl;
        getch();
        return false;
    }
    return true;
}

void listar_todos_los_pedidos(Pedidos reg)
{
   FILE *p;
   p = fopen(PATH_PEDIDOS,"rb");
   if(p == NULL ){
    return;
   }
   fseek(p,0,SEEK_SET);
   while(fread(&reg,sizeof(Pedidos),1,p)){
        mostrar_pedido(reg);
   }
 return;
}

void menupedidos()
{
    int oppedidos;
    bool salirmenupedidos = false;
    while(!salirmenupedidos)
    {
    system("cls");
    cout << endl;
    cout << " MENU PEDIDOS " << endl;
    cout << " ----------------------------- " << endl;
    cout << " 1) NUEVO PEDIDO " << endl;
    cout << " 2) MODIFICAR PEDIDO " << endl;
    cout << " 3) LISTAR PEDIDO POR ID " << endl;
    cout << " 4) LISTAR TODOS LOS PEDIDOS " << endl;
    cout << " ------------------------------ " << endl;
    cout << " 0) VOLVER AL MENU PRINCIPAL " << endl;
    cout << " ------------------------------ " << endl;
    cout << " OPCION : ";
    cin >> oppedidos;
    cout << " ------------------------------ " << endl;
    switch(oppedidos)
    {
    case 1:
        {
            Pedidos regpedidos;
            system("cls");
            if(cargar_pedido(&regpedidos)){
                if(guardar_pedido(regpedidos)){
                    system("cls");
                    cout << " ================================ " << endl;
                    cout << " SE CARGO EL PEDIDO CORRECTAMENTE " << endl;
                    cout << " ================================ " << endl;
                }
            }
            else{
                system("cls");
                cout << " =================================== " << endl;
                cout << "       NO SE CARGO EL PEDIDO         " << endl;
                cout << " =================================== " << endl;
            }
            getch();
        }break;
    case 2:
        {
            system("cls");
            if(modificar_pedido()){
                system("cls");
                cout << " =================================== " << endl;
                cout << " SE MODIFICO EL PEDIDO CORRECTAMENTE " << endl;
                cout << " =================================== " << endl;
            }
            else{
                cout << " =================================== " << endl;
                cout << "    NO SE PUDO MODIFICO EL PEDIDO    " << endl;
                cout << " =================================== " << endl;
            }
           getch();
        }break;
    case 3:
        {
          system("cls");
          if(listar_por_id()){
            cout << endl;
            cout << " ********************** " << endl;
            cout << " SE LISTO CORRECTAMENTE " << endl;
            cout << " ********************** " << endl;
          getch();
        }break;
    case 4:
        {
            Pedidos reg;
            system("cls");
            if(cantidad_pedidos()!= 0){
                    system("cls");
               listar_todos_los_pedidos(reg);
            }
            else{
                system("cls");
                cout << " NO HAY NINGUN PEDIDO " << endl;
            }
            getch();
        }break;
    case 0:
        {
            salirmenupedidos = true;
        }break;

    }

    }

}
}


#endif // FUNCIONESPEDIDOS_H_INCLUDED
