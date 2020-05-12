#ifndef FUNCIONCONFIGURACION_H_INCLUDED
#define FUNCIONCONFIGURACION_H_INCLUDED

void copia_seguridad(pizzeria *regplatos,clientes *regclientes,Pedidos *regpedidos)
{
  FILE *pplatos,*pcoplatos,*pclientes,*pcoclientes,*ppedidos,*pcopedidos;

  pplatos = fopen(PATH_ARCHIVO,"rb");
  if(pplatos == NULL){
        system("cls");
        system("color 04");
      cout << " NO SE PUDO ABRIR EL ARCHIVOS PLATOS " << endl;
      getch();
       return;
  }
  pclientes = fopen(PATH_CLIENTES,"rb");
  if(pclientes == NULL){
    system("cls");
    system("color 04");
    cout << " NO SE PUDO ABRIR EL ARCHIVO CLIENTES " << endl;
    getch();
    return;
  }
  ppedidos = fopen(PATH_PEDIDOS,"rb");
  if(ppedidos == NULL){
    system("cls");
    system("color 04");
    cout << "NO SE PUDO ABRIR EL ARCHIVO PEDIDOS  " << endl;
    getch();
    return;
  }
  pcoplatos = fopen("platos.bkp","ab");
  if(pcoplatos == NULL){
        system("cls");
        system("color 04");
    cout << " NO SE PUDO ABRIR EL ARCHIVO COPIA PLATOS " << endl;
    getch();
    return;
  }
  pcoclientes = fopen("clientes.bkp","ab");
  if(pcoclientes == NULL){
    system("cls");
    system("color 04");
    cout << " NO SE PUDO ABRIR EL ARCHIVO COPIA CLIENTES " << endl;
    getch();
    return;
  }
  pcopedidos = fopen("pedidos.bkp","ab");
  if(pcopedidos == NULL){
    system("cls");
    system("color 04");
    cout << " NO SE PUDO ABRIR EL ARCHIVO COPIA PEDIDOS " << endl;
    getch();
    return;
  }
  while(fread(&regplatos,sizeof(pizzeria),1,pplatos) == 1){
    fwrite(&regplatos,sizeof(pizzeria),1,pcoplatos);
  }
  while(fread(&regclientes,sizeof(clientes),1,pclientes) == 1){
    fwrite(&regclientes,sizeof(clientes),1,pcoclientes);
  }
  while(fread(&regpedidos,sizeof(Pedidos),1,ppedidos) == 1){
    fwrite(&regpedidos,sizeof(Pedidos),1,pcopedidos);
  }
  fclose(pclientes);
  fclose(pcoclientes);
  fclose(ppedidos);
  fclose(pcopedidos);
  fclose(pplatos);
  fclose(pcoplatos);
  system("cls");
  system("0F");
  cout << " Datos copiados ..." << endl;
  getch();
}


void restaurar_copia_de_seguridad(pizzeria *regplatos,clientes *regclientes,Pedidos *regpedidos)
{
    FILE *pplatos,*pcoplatos,*pclientes,*pcoclientes,*ppedidos,*pcopedidos;
    pcoplatos= fopen("platos.bkp","rb");
    if(pcoplatos == NULL){
        system("cls");
        system("color 04");
    cout << " NO SE PUDO ABRIR EL ARCHIVO COPIA PLATOS " << endl;
    getch();
    return;
  }
  pcoclientes = fopen("clientes.bkp","rb");
  if(pcoclientes == NULL){
    system("cls");
    system("color 04");
    cout << " NO SE PUDO ABRIR EL ARCHIVO COPIA CLIENTES " << endl;
    getch();
    return;
  }
  pcopedidos = fopen("pedidos.bkp","rb");
  if(pcoclientes == NULL){
    system("cls");
    system("color 04");
    cout << " NO SE PUDO ABRIR EL ARCHIVO COPIA CLIENTES " << endl;
    getch();
    return;
  }
  pplatos = fopen(PATH_ARCHIVO,"wb");
  if(pplatos == NULL){
      system("cls");
      system("color 04");
      cout << " NO SE PUDO ABRIR EL ARCHIVOS PLATOS " << endl;
      getch();
      return;
  }
  pclientes = fopen(PATH_CLIENTES,"wb");
  if(pclientes == NULL){
    system("cls");
    system("color 04");
    cout << " NO SE PUDO ABRIR EL ARCHIVO CLIENTES " << endl;
    getch();
    return;
  }
  ppedidos = fopen(PATH_PEDIDOS,"wb");
  if(ppedidos == NULL){
    system("cls");
    system("color 04");
    cout << " NO SE PUDO ABRIR EL ARCHIVO PEDIDOS " << endl;
    getch();
    return;
  }
  while(fread(&regplatos,sizeof(pizzeria),1,pcoplatos) == 1){
    fwrite(&regplatos,sizeof(pizzeria),1,pplatos);
  }
  while(fread(&regclientes,sizeof(clientes),1,pcoclientes) == 1){
    fwrite(&regclientes,sizeof(clientes),1,pclientes); // error &regplatos
  }
  while(fread(&regpedidos,sizeof(Pedidos),1,pcopedidos) == 1){
    fwrite(&regpedidos,sizeof(Pedidos),1,ppedidos);
  }
 fclose(pclientes);
  fclose(pcoclientes);
  fclose(ppedidos);
  fclose(pcopedidos);
  fclose(pplatos);
  fclose(pcoplatos);
  system("cls");
  system("0F");
  cout << " Datos restaurados correctamente " << endl;
  getch();
}

void menuconfiguracion()
{
    system("cls");
    int opconfi;
    bool salirmenuconfi = false;
    while(!salirmenuconfi)
    {
        system("cls");
        system("color E0");
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
            system("cls");
            pizzeria regplatos;
            clientes regclientes;
            Pedidos regpedidos;
            copia_seguridad(&regplatos,&regclientes,&regpedidos);
        }break;
    case 2:
        {
            system("cls");
            pizzeria regplatos;
            clientes regclientes;
            Pedidos regpedidos;
            restaurar_copia_de_seguridad(&regplatos,&regclientes,&regpedidos);
        }break;
    case 0:
        {
          salirmenuconfi = true;
        }break;
    }
 }
}

#endif // FUNCIONCONFIGURACION_H_INCLUDED
