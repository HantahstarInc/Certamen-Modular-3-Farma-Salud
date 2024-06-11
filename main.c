#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10000

struct FarmaSalud{
    struct RaizCatalogos *AbbCatalogos;
    struct NodoFarmacias *headFarmacias;
    struct NodoProveedores *headProveedores;
};


struct NodoFarmacias{
    struct Farmacias *DatosFarmacias;
    struct NodoFarmacias *sig,*ant;
};
struct Farmacias{
    char *ubicacion;
    int capacidadInventario;
    int venta;
    long presupuesto;
    struct NodoBoleta *boletasFarmacias;
    struct NodoInventario *headInventario;
};
struct NodoBoleta{
    struct Boleta *boletas;
    struct NodoBoleta *sig,*ant;
};
struct Boleta{
    char *rut;
    char *fecha;
    unsigned long montoVenta;
    int tamanio;
    struct TipoMed **medicamentosVenta;
};
struct NodoInventario{
    struct TipoMed *DatosMed;
    struct NodoInventario *sig,*ant;
};
struct TipoMed{
    int stock;
    int demanda;
    int altademanda; //1 si 0 no
    struct Producto *Datosprod;
    struct Medicamento **medicamentos;
};
struct Medicamento{
    int lote;
    char *fechacaducidad;
    struct Proveedor *DatosProveedor;
};
struct NodoProveedores{
    struct Proveedor *DatosProveedor;
    struct NodoProveedores *sig,*ant;
};
struct Proveedor{
    char *nombre;
    char *ubicacion;
    unsigned long cuota;
    struct RaizCatalogos *Mercancia;
};
struct RaizCatalogos{
    struct Producto *DatosProductos;
    struct RaizCatalogos *izq,*der;
};

struct Producto{
    char *nombre;
    char *codigo;
    int receta; //si es 1 necesita receta, si es 0 no necesita
    char *categoria;
    char *descripcion;
    unsigned long precio;
};

void mostrarProductosEnBoleta(struct TipoMed ** medicamentos,int tamanio)
{
    int i;
    for(i = 0 ; i < tamanio ; i++)
    {
        if(medicamentos[i] != NULL)
        {
            printf("%i %s  \n",medicamentos[i] ->stock,medicamentos[i] ->Datosprod ->nombre);

        }
    }
}

void mostrarNodoBoleta(struct NodoBoleta *headBoleta)
{
    struct NodoBoleta *rec;


    if(headBoleta != NULL)
    {
        rec = headBoleta;
        while (rec != NULL)
        {
            printf("\n=============================================\n");
            printf("Rut del comprador : %s\n",rec ->boletas ->rut);
            printf("Fecha de la compra : %s\n",rec ->boletas ->fecha);

            if(rec ->boletas->tamanio >0)
            {
                mostrarProductosEnBoleta(rec ->boletas->medicamentosVenta,rec ->boletas->tamanio);
            }
            printf("Total gastado : %lu\n",rec ->boletas ->montoVenta);
            printf("=============================================\n\n");
            rec = rec -> sig;
        }
    }
}

void mostrarNodoFarmacias(struct NodoFarmacias *headFarmacia)
{
    struct NodoFarmacias *rec;
    if(headFarmacia != NULL) {
        rec = headFarmacia;
        while (rec != NULL) {
            printf("\n=============================================\n");
            printf("Ubicacion Farmacia :  %s\n", rec->DatosFarmacias->ubicacion);
            printf("Capacidad del inventario: %d \n", rec->DatosFarmacias->capacidadInventario);
            printf("presupuesto de la farmacia: $%li pesos\n", rec->DatosFarmacias->presupuesto);
            printf("=============================================\n\n");
            rec = rec->sig;
        }
    }
    else
    {
        puts("\nAun no hay sucursales");
    }
}

void mostrarFarmacia(struct Farmacias *farmacia)
{
    printf("\n=============================================\n");
    printf("Ubicacion Farmacia :  %s\n", farmacia->ubicacion);
    printf("Capacidad del inventario: %d\n", farmacia->capacidadInventario);
    printf("presupuesto de la farmacia: %li\n", farmacia->presupuesto);
    printf("=============================================\n\n");
}

void mostrarNodoInventario(struct NodoInventario * headInventario)
{
    struct NodoInventario*rec = headInventario;
    if(headInventario != NULL)
    {
        while(rec != NULL)
        {
            printf("\n=============================================\n");
            printf("Nombre del producto : %s\n",rec ->DatosMed->Datosprod->nombre);
            printf("Cantidad de productos disponibles : %d\n",rec ->DatosMed ->stock);
            printf("Cuanto se ha comprado : %d\n",rec -> DatosMed ->demanda);
            printf("=============================================\n\n");
            rec = rec ->sig;
        }
    }
    else{
        puts("No hay medicamentos en esta farmacia");
    }
}

void mostrarNodoProveedores(struct NodoProveedores *headProveedores)
{
    struct NodoProveedores *rec = headProveedores;


    if(headProveedores != NULL){
        do{
            printf("\n=============================================\n");
            printf("Nombre del proveedor : %s\n",rec ->DatosProveedor -> nombre);
            printf("Ubicacion del Proveedor : %s\n",rec -> DatosProveedor -> ubicacion);
            printf("Cuota del Proveedor : %lu\n",rec -> DatosProveedor -> cuota);

            printf("=============================================\n\n");
            rec = rec -> sig;
        }while(rec != headProveedores);
    }
    else{
        puts("No hay Proveedores aun");
    }
}

void mostrarProveedor(struct Proveedor *proveedor)
{
    printf("\n=============================================\n");
    printf("Nombre del proveedor : %s\n",proveedor->nombre);
    printf("Ubicacion del Proveedor : %s\n",proveedor->ubicacion);
    printf("Cuota del Proveedor : $%lu\n",proveedor->cuota);
    printf("=============================================\n\n");
}

void mostrarNodoCatalogo(struct RaizCatalogos *arbol)
{
    if(arbol) {
        printf("\n=============================================\n");
        printf("Nombre del producto : %s\n", arbol->DatosProductos->nombre);
        printf("Codigo del producto : %s\n", arbol->DatosProductos->codigo);
        printf("Necesita receta : ");
        if(arbol->DatosProductos->receta == 1)
            printf("SI\n");
        else
            printf("NO\n");
        printf("Categoria Producto : %s\n", arbol->DatosProductos->categoria);
        printf("Descripcion producto : %s\n", arbol->DatosProductos->descripcion);
        printf("Precio producto : $%lu\n", arbol->DatosProductos->precio);
        printf("\n=============================================\n");
        mostrarNodoCatalogo(arbol->izq);
        mostrarNodoCatalogo(arbol->der);
    }
}

/*Janet*/
//retorna el producto que buscas por su codigo en el caso de que exista, si no existe el producto retorna NULL

struct RaizCatalogos *buscarProductoEnCatalogo(struct RaizCatalogos *arbol, char *codigoProducto){
    if(arbol == NULL || arbol->DatosProductos == NULL){
        return NULL;
    }


    if(strcmp(arbol->DatosProductos->codigo, codigoProducto) == 0){
        return arbol;
    }
    else{
        if (arbol->DatosProductos->codigo != NULL && strcmp(codigoProducto,arbol->DatosProductos->codigo)<0)
        {
            return buscarProductoEnCatalogo(arbol->izq, codigoProducto);
        }
        else if (arbol->DatosProductos->codigo != NULL && strcmp(codigoProducto,arbol->DatosProductos->codigo)>0)
            return buscarProductoEnCatalogo(arbol->der, codigoProducto);
    }
}

struct Producto *crearProductoNuevo(char *nombre,char *codigoNuevo, int recetaNueva, char *categoriaNueva, char *descripcionNueva, unsigned long precioNuevo){
    struct Producto *nuevo = (struct Producto *)malloc(sizeof(struct Producto));


    if(!nuevo){
        return NULL;
    }
    nuevo->nombre = (char*) malloc((strlen(nombre) + 1)*sizeof(char));
    nuevo->codigo = (char*) malloc((strlen(codigoNuevo) + 1)*sizeof(char));
    nuevo->categoria = (char*) malloc((strlen(categoriaNueva) + 1)*sizeof(char));
    nuevo->descripcion = (char*) malloc((strlen(descripcionNueva) + 1)*sizeof(char));


    strcpy(nuevo->nombre,(nombre));
    strcpy(nuevo->codigo,(codigoNuevo));
    nuevo->receta = recetaNueva;
    strcpy(nuevo->categoria, (categoriaNueva));
    strcpy(nuevo->descripcion,(descripcionNueva));
    nuevo->precio = precioNuevo;


    return nuevo;
}

//retorna 1 si el producto se agregó al catálogo, retorna 0 en caso contrario
int agregarProductoAlCatalogo(struct RaizCatalogos **arbol,char *nombreNuevo, char *codigoNuevo, int recetaNueva, char *categoriaNueva, char *descripcionNueva, unsigned long precioNuevo){
    struct Producto *productoNuevo = crearProductoNuevo(nombreNuevo,codigoNuevo, recetaNueva, categoriaNueva, descripcionNueva, precioNuevo);
    if(!productoNuevo){
        return 0;
    }
    if(*arbol == NULL)
    {
        (*arbol) = (struct RaizCatalogos *)malloc(sizeof(struct RaizCatalogos));
        (*arbol)->DatosProductos = productoNuevo;
        (*arbol)->der = (*arbol)->izq = NULL;
        return 1;
    }

    if(buscarProductoEnCatalogo(*arbol, productoNuevo->codigo) == NULL)
    {
        if (strcmp(productoNuevo->codigo,(*arbol)->DatosProductos->codigo)<0){
            return agregarProductoAlCatalogo(&((*arbol)->izq),nombreNuevo, codigoNuevo, recetaNueva, categoriaNueva, descripcionNueva, precioNuevo);
        }
        else{
            return agregarProductoAlCatalogo(&((*arbol)->der),nombreNuevo, codigoNuevo, recetaNueva, categoriaNueva, descripcionNueva, precioNuevo);
        }
    }
    return 0;
}


//función eliminar
struct RaizCatalogos *getPadre(struct RaizCatalogos *arbol, struct RaizCatalogos *hijo){
    struct RaizCatalogos *nodoAntecesor = NULL;
    if(arbol){
        struct RaizCatalogos *nodoActual = arbol;
        while(nodoActual != hijo){
            if(strcmp(hijo->DatosProductos->codigo, nodoActual->DatosProductos->codigo) < 0){
                nodoAntecesor = nodoActual;
                nodoActual = nodoActual->izq;
            }else{
                nodoAntecesor = nodoActual;
                nodoActual = nodoActual->der;
            }
        }
    }
    return nodoAntecesor;
}

struct RaizCatalogos *hijoNoNull(struct RaizCatalogos *nodoAEliminar){
    if(nodoAEliminar->izq != NULL)
        return nodoAEliminar->izq;
    else
        return nodoAEliminar->der;
}

int eliminarProductoDelCatalogo(struct RaizCatalogos **arbol, char *codigoProducto){
    if(!arbol){
        return -2;
    }
    struct RaizCatalogos *productoAEliminar = buscarProductoEnCatalogo(*arbol, codigoProducto);
    if(productoAEliminar==NULL){
        return -1;
    }
    struct RaizCatalogos *padre = NULL, *nodo = NULL;
    struct Producto *aux = NULL;
    if(productoAEliminar!=NULL)
        padre = getPadre(*arbol, productoAEliminar);


    while(productoAEliminar){
        //caso 1: eliminar un nodo hoja
        if(!productoAEliminar->der && !productoAEliminar->izq){
            if(padre){
                if(padre->der == productoAEliminar)
                    padre->der = NULL;
                else
                    padre->izq = NULL;
            }else{
                *arbol = NULL;
            }
            //productoAEliminar->DatosProductos = NULL;


            productoAEliminar = NULL;
            free(productoAEliminar);
            return 1;


            //caso 2: se elimina un nodo que contenga dos hijos
        }else if(productoAEliminar->der && productoAEliminar->izq){
            padre = productoAEliminar;
            if(productoAEliminar->der)
            {
                nodo = productoAEliminar->der;
                while(nodo->izq){
                    padre = nodo;
                    nodo = nodo->izq;
                }
            }else
            {
                nodo = productoAEliminar->izq;
                while(nodo->der){
                    padre = nodo;
                    nodo = nodo->der;
                }
            }
            //Intercambio
            aux = productoAEliminar->DatosProductos;
            productoAEliminar->DatosProductos = nodo->DatosProductos;
            nodo->DatosProductos = aux;
            productoAEliminar = nodo;


            //caso 3: se elimina nodo que contenga un solo hijo
        }else if(!productoAEliminar->der || !productoAEliminar->izq){
            if(padre){
                if(strcmp(productoAEliminar->DatosProductos->codigo, padre->DatosProductos->codigo) < 0){
                    padre->izq = hijoNoNull(productoAEliminar);
                }
                else {
                    padre->der = hijoNoNull(productoAEliminar);
                }
            }
            else{
                *arbol = hijoNoNull(productoAEliminar);
            }
            free(productoAEliminar);
            productoAEliminar = NULL;
            return 1;
        }
    }
    return 0;
}

struct TipoMed *crearTipoMed(char *codigo,struct RaizCatalogos *abb){


    struct TipoMed * tiponuevo;
    struct RaizCatalogos *Datos = buscarProductoEnCatalogo(abb,codigo);
    if(Datos == NULL)return NULL;


    tiponuevo = (struct TipoMed*) malloc(sizeof(struct TipoMed));
    if(tiponuevo==NULL) return NULL;


    tiponuevo->medicamentos=NULL;
    tiponuevo->Datosprod = Datos->DatosProductos;
    tiponuevo->stock = 0;
    tiponuevo->demanda = 0;
    tiponuevo->altademanda = 0;


    return tiponuevo;
}

struct NodoInventario *buscartipomed(struct NodoInventario *headinventario,char *codigobuscado)
{
    struct NodoInventario *rec;
    if(headinventario != NULL)
    {
        rec = headinventario;
        while(rec!=NULL)
        {
            if(strcmp(rec->DatosMed->Datosprod->codigo,codigobuscado)==0){
                return rec;
            }
            rec = rec -> sig;
        }
    }
    return NULL;
}
//agregarTipoMedALista
int agregarTipoMedalista(struct NodoInventario **headinventario, struct TipoMed *tiponuevo)
{
    //struct NodoInventario *nuevonodo =
    struct NodoInventario *rec;


    if(*headinventario == NULL)
    {
        (*headinventario) = (struct NodoInventario*) malloc(sizeof(struct NodoInventario));
        (*headinventario) -> DatosMed = tiponuevo;
        (*headinventario) -> ant = NULL;
        (*headinventario) -> sig = NULL;
        return 1;
    }
    else
    {
        if (buscartipomed(*headinventario,tiponuevo->Datosprod->codigo) == NULL) {
            rec =  *headinventario;
            while (rec->sig != NULL){
                rec = rec->sig;
            }
            rec->sig = (struct NodoInventario *) malloc(sizeof(struct NodoInventario));
            rec->sig->DatosMed = tiponuevo;
            rec->sig->sig = NULL;
            rec->sig->ant = rec;
            //free(rec);
            return 1;
        }
    }
    return 0;
}
//eliminarTipoMed

int eliminarTipomed(struct NodoInventario **headinventario, char *codigoProducto)
{
    struct NodoInventario *current;

    if ((*headinventario) == NULL) {
        return -2;
    }
    current = (*headinventario);

    if (strcmp(current->DatosMed->Datosprod->codigo, codigoProducto) == 0) {
        *headinventario = current->sig;
        if (*headinventario != NULL) {
            (*headinventario)->ant = NULL;
        }
    }
    while (current != NULL) {
        if(current->DatosMed->Datosprod->codigo != NULL && (strcmp(current->DatosMed->Datosprod->codigo,codigoProducto)==0))
        {
            if (current->ant != NULL) {
                current->ant->sig = current->sig;
            }
            if (current->sig != NULL) {
                current->sig->ant = current->ant;
            }
            return 1;
        }
        current = current->sig;
    }
    return -1;
}
//Funciones farmacias
struct Farmacias *crearFarmacia(char *ubicacion,int capacidad,long presupuesto){


    struct Farmacias * farmaciaNueva;
    farmaciaNueva = (struct Farmacias*) malloc(sizeof(struct Farmacias));
    if(farmaciaNueva == NULL)return NULL;
    farmaciaNueva->ubicacion = (char*) malloc((strlen(ubicacion) + 1)*sizeof(char));


    strcpy(farmaciaNueva -> ubicacion,ubicacion);
    farmaciaNueva -> capacidadInventario = capacidad ;
    farmaciaNueva -> venta = 0 ;
    farmaciaNueva -> presupuesto = presupuesto;
    farmaciaNueva -> headInventario = NULL;
    return farmaciaNueva;
}

struct NodoFarmacias * buscarFarmacia(struct NodoFarmacias *headFarmacias,char *ubicacionBuscada)
{
    struct NodoFarmacias * current;
    if(headFarmacias != NULL)
    {
        current  = headFarmacias;
        while(current!=NULL)
        {
            if(current->DatosFarmacias->ubicacion != NULL && strcmp(current->DatosFarmacias->ubicacion,ubicacionBuscada)==0){
                return current;
            }
            current = current -> sig;
        }
    }
    return NULL;
}

int agregarFarmaciaALista(struct NodoFarmacias **headFarmacias, struct Farmacias *farmaciaNueva)
{
    struct NodoFarmacias *rec;


    if(*headFarmacias == NULL)
    {
        (*headFarmacias) = (struct NodoFarmacias*) malloc(sizeof(struct NodoFarmacias));
        (*headFarmacias) -> DatosFarmacias = farmaciaNueva;
        (*headFarmacias) -> ant = NULL;
        (*headFarmacias) -> sig = NULL;
        return 1;
    }
    else
    {
        if (buscarFarmacia(*headFarmacias,farmaciaNueva -> ubicacion) == NULL)
        {
            rec = *headFarmacias;
            while(rec -> sig != NULL)
                rec = rec -> sig;
            rec -> sig = (struct NodoFarmacias*) malloc(sizeof(struct NodoFarmacias));
            rec -> sig -> DatosFarmacias = farmaciaNueva;
            rec -> sig -> sig = NULL;
            rec -> sig -> ant = rec;
            return 1;
        }
    }


    return 0;
}

int eliminarFarmacia(struct NodoFarmacias **headFarmacias, char *ubicacion) {
    struct NodoFarmacias *current;
    if (*headFarmacias == NULL) {
        return 0;
    }

    if (strcmp((*headFarmacias)->DatosFarmacias->ubicacion, ubicacion) == 0) {
        *headFarmacias = (*headFarmacias)->sig;
        if (*headFarmacias != NULL) {
            (*headFarmacias)->ant = NULL;
        }
        return 1;
    }

    current = *headFarmacias;
    while (current != NULL) {
        if (current->DatosFarmacias->ubicacion != NULL && strcmp(current->DatosFarmacias->ubicacion, ubicacion) == 0) {
            if (current->ant != NULL) {
                current->ant->sig = current->sig;
            }
            if (current->sig != NULL) {
                current->sig->ant = current->ant;
            }
            return 1;
        }
        current = current->sig;
    }
    return -1;
}

//Funciones Proveedor

struct Proveedor * crearProveedor(char *nombreProveedor, char* ubicacion , unsigned long cuota)
{
    struct Proveedor *ProveedorNuevo;


    ProveedorNuevo = (struct Proveedor *)malloc(sizeof(struct Proveedor));
    if(ProveedorNuevo == NULL)return NULL;


    ProveedorNuevo->nombre = (char*) malloc((strlen(nombreProveedor) + 1)*sizeof(char));
    ProveedorNuevo ->ubicacion = (char*) malloc((strlen(ubicacion) + 1)*sizeof(char));


    strcpy(ProveedorNuevo -> nombre,(nombreProveedor));
    strcpy(ProveedorNuevo -> ubicacion,(ubicacion));
    ProveedorNuevo -> cuota = cuota;


    return ProveedorNuevo;
}

struct NodoProveedores * buscarProveedores(struct NodoProveedores *headProveedores,char *nombre)
{
    struct NodoProveedores * rec;
    if(headProveedores != NULL)
    {
        rec = headProveedores;
        do{
            if(rec ->DatosProveedor -> nombre != NULL && strcmp(rec ->DatosProveedor -> nombre ,nombre) == 0)
            {
                return rec;
            }
            rec = rec ->sig;
        }while(rec != headProveedores);
    }
    return NULL;
}

int agregarProveedor(struct NodoProveedores **headProveedores,struct Proveedor *ProveedorNuevo)
{
    struct NodoProveedores *rec = *headProveedores;
    struct NodoProveedores *nuevo;


    nuevo=(struct NodoProveedores *)malloc(sizeof(struct NodoProveedores));
    nuevo -> DatosProveedor = ProveedorNuevo;


    if(*headProveedores == NULL)
    {
        (*headProveedores) = nuevo;
        (*headProveedores) -> sig = *headProveedores;
        (*headProveedores) -> ant = *headProveedores;
        return  1;
    }
    else
    {
        if(buscarProveedores(*headProveedores,ProveedorNuevo->nombre)== NULL)
        {
            do{
                rec = rec -> sig;
            }while(rec ->sig != (*headProveedores));


            rec -> sig = nuevo;
            nuevo -> sig = *headProveedores;
            (*headProveedores) -> ant = nuevo;
            nuevo -> ant = rec;
            return 1;
        }
    }
    return 0;
}

int eliminarProveedor(struct NodoProveedores **headProveedores,char *nombre)
{
    struct NodoProveedores *temp,*rec = (*headProveedores);


    if(*headProveedores !=NULL)
    {
        if(strcmp(rec->DatosProveedor->nombre,nombre)==0)
        {
            (*headProveedores) -> sig -> ant = (*headProveedores) -> ant;
            (*headProveedores) -> ant -> sig = (*headProveedores) -> sig;


            temp = (*headProveedores) -> sig;
            free(*headProveedores);
            (*headProveedores) = temp;
            return 1;
        }
        else
        {
            do{
                if(strcmp(rec -> DatosProveedor -> nombre ,nombre)== 0)
                {
                    rec->sig->ant=rec->ant;
                    rec->ant->sig=rec->sig;


                    /*ahora borramos*/
                    temp=rec->sig;
                    free(rec);
                    rec=temp;
                    return 1;
                }


                rec=rec->sig;


            }while(rec!=*headProveedores);
        }


    }
    return 0;
}

int agregarProductoCatalogoProveedor(char *codigoNuevoProducto, struct RaizCatalogos **raizProveedor, struct RaizCatalogos *ptrCatalogo){
    if(*raizProveedor == NULL){
        *raizProveedor = (struct RaizCatalogos *)malloc(sizeof(struct RaizCatalogos));
        (*raizProveedor)->DatosProductos = ptrCatalogo->DatosProductos;
        (*raizProveedor)->der = (*raizProveedor)->izq = NULL;
        return 1;
    }
    if(buscarProductoEnCatalogo((*raizProveedor),codigoNuevoProducto) == NULL)
    {
        if (strcmp(codigoNuevoProducto,(*raizProveedor)->DatosProductos->codigo)<0){
            return agregarProductoCatalogoProveedor( codigoNuevoProducto, &((*raizProveedor)->izq), ptrCatalogo);
        }
        else if ((strcmp(codigoNuevoProducto,(*raizProveedor)->DatosProductos->codigo)>0)) {
            return agregarProductoCatalogoProveedor( codigoNuevoProducto, &((*raizProveedor)->der), ptrCatalogo);
        }
    }

    return 0;
}

/*-----------------------------------------------------*/
// FERNANDO - Funciones para registrar ventas y actualizar el stock en cada farmacia.//
struct Producto *buscarMedicamentoPorCodigo(struct NodoInventario *headInventario,char *codigo)
{
    struct NodoInventario *rec = headInventario;
    int i;
    while(rec!=NULL)
    {
        if(rec->DatosMed->Datosprod->codigo != NULL && strcmp(rec->DatosMed->Datosprod->codigo,codigo) == 0)
        {
            return rec -> DatosMed -> Datosprod;
        }
        rec = rec->sig;
    }
    return NULL;
}

struct Boleta * crearBoleta(char *rut,char *fecha,unsigned long montoVenta,struct TipoMed **MedicamentosVenta,int tamanio)
{
    struct Boleta *boletaNueva = (struct Boleta*)malloc(sizeof(struct Boleta));


    boletaNueva ->rut = (char*) malloc((strlen(rut) + 1)*sizeof(char));
    boletaNueva ->fecha = (char*) malloc((strlen(fecha) + 1)*sizeof(char));

    strcpy(boletaNueva->rut,(rut));
    strcpy(boletaNueva->fecha,(fecha));
    boletaNueva->montoVenta = montoVenta;
    boletaNueva->medicamentosVenta = MedicamentosVenta;
    boletaNueva ->tamanio = tamanio;
    return boletaNueva;
}

struct NodoBoleta * buscarBoleta(struct NodoBoleta * headBoletas,char *rut)
{
    struct NodoBoleta * current;
    if(headBoletas != NULL)
    {
        current = headBoletas;
        while(current != NULL)
        {
            if(current -> boletas -> rut != NULL && strcmp(current -> boletas -> rut , rut) == 0)
            {
                return current;
            }
            current = current -> sig;
        }
    }
    return NULL;
}

int agregarBoletasALista(struct NodoBoleta ** headBoletas,struct Boleta * boletaNueva)
{
    struct NodoBoleta *rec;


    if(*headBoletas == NULL)
    {
        (*headBoletas) = (struct NodoBoleta*)malloc(sizeof(struct NodoBoleta));
        (*headBoletas) ->boletas = boletaNueva;
        (*headBoletas)-> ant = NULL;
        (*headBoletas)-> sig = NULL;
        return 1;
    }
    else
    {
        if(buscarBoleta(*headBoletas,boletaNueva ->rut)==NULL)
        {
            rec = *headBoletas;
            while(rec ->sig != NULL)
            {
                rec = rec -> sig;
            }
            rec -> sig = (struct NodoBoleta*)malloc(sizeof(struct NodoBoleta));
            rec -> sig -> boletas = boletaNueva;
            rec -> sig -> sig = NULL;
            rec -> sig -> ant = rec;
            return 1;
        }
    }
    return 0;
}


int eliminarBoleta(struct NodoBoleta ** headBoletas,char *rut)
{
    struct NodoBoleta *current;
    if (*headBoletas == NULL){
        return 0;
    }

    if (strcmp((*headBoletas)->boletas->rut ,rut) == 0)
    {
        *headBoletas = (*headBoletas)->sig;
        (*headBoletas) -> ant = NULL;
        return 1;
    }
    current = *headBoletas;
    while (current!= NULL)
    {
        if (strcmp(current->boletas->rut,rut)==0)
        {
            if (current->ant != NULL) {
                current->ant->sig = current->sig;
            }
            if (current->sig != NULL) {
                current->sig->ant = current->ant;
            }
            return 1;
        }
        current = current->sig;
    }
    return 0;
}

/*------------------------------------------------------------------------------*/
/*-----------------------------------------------------*/
//MATI

//return 1 fecha1 es mayor a fecha 2 return -1 fecha 1 es menor que fecha 2 return 0 son iguales
int estaCaducado(char *fecha1,char *fecha2) {
    char fecha1cpy[11];
    char fecha2cpy[11];
    if (fecha1 != NULL && fecha2 != NULL) {
        strcpy(fecha1cpy, fecha1);
        strcpy(fecha2cpy, fecha2);
    }
    int dia1, mes1, anio1;
    int dia2, mes2, anio2;

    dia1 = atoi(strtok(fecha1cpy, "/"));
    mes1 = atoi(strtok(NULL, "/"));
    anio1 = atoi(strtok(NULL, "/"));

    dia2 = atoi(strtok(fecha2cpy, "/"));
    mes2 = atoi(strtok(NULL, "/"));
    anio2 = atoi(strtok(NULL, "/"));

    if (anio1 > anio2) {
        return 1;
    } else if (anio1 < anio2) {
        return -1;
    }
    if (mes1 > mes2) {
        return 1;
    } else if (mes1 < mes2) {
        return -1;
    }
    if (dia1 > dia2) {
        return 1;
    } else if (dia1 < dia2) {
        return -1;
    }
    return 0;
}

int verificarStockParaCompras(struct Medicamento **medicamentos,char*fecha,int tamanio)
{
    if(tamanio == 0)
    {
        return 0;
    }
    int cont = 0 , i;
    for(i = 0 ; i < tamanio ; i++)
    {
        if(medicamentos[i] != NULL && estaCaducado(fecha,medicamentos[i]->fechacaducidad)<0)
        {
            cont++;
        }
    }
    return cont;
}

void alerta(struct Farmacias *farma){
    struct NodoInventario *rec = farma->headInventario;
    if (rec!=NULL){
        while (rec!=NULL){
            if ((rec->DatosMed->stock)<=10){
                printf("!El producto %s (codigo : %s) se está agotando¡\n",rec->DatosMed->Datosprod->nombre,rec->DatosMed->Datosprod->codigo);
            }
            rec = rec->sig;
        }
    }
}

int compactarDespuesDeVenta(struct Medicamento **medicamento, int *plibre,char *fecha)
{
    int i, j;
    for(i=0; i<(*plibre); i++)
    {
        if (estaCaducado(fecha,medicamento[i]->fechacaducidad)<0)
        {
            medicamento[i]=NULL;
            for(j=i; j<(*plibre)-1; j++)
                medicamento[j]=medicamento[j+1];


            medicamento[(*plibre)-1]=NULL;
            (*plibre)--;

            return 1;
        }
    }
    return 0;
}

void eliminarYCompactar(struct Medicamento **medicamento,char *fecha,int *plibre,int maximoDeVeces)
{
    int i,verificar;
    for(i=0;maximoDeVeces>i;i++){
        verificar = compactarDespuesDeVenta((medicamento),(plibre),fecha);
    }
}

int estaEnBoleta(struct TipoMed ** medicamentos ,char *codigo,int tamanio)
{
    int i;
    if(tamanio == 0)return 0;
    for(i = 0 ; i < tamanio ; i++)
    {
        if(medicamentos[i] != NULL && strcmp(medicamentos[i]->Datosprod ->codigo,codigo)==0)
        {
            return 1;
        }
    }
    return 0;
}

void mostrarProductosParaLaVenta(struct NodoInventario *headInventario, char *fecha) {
    struct NodoInventario *rec = headInventario;
    int verificar;


    while (rec != NULL) {
        verificar = verificarStockParaCompras(rec->DatosMed->medicamentos, fecha, rec->DatosMed->stock);
        if (verificar != 0 && rec->DatosMed->Datosprod != NULL) {
            printf("\n=============================================\n");
            printf("Nombre del producto : %s\n", rec->DatosMed->Datosprod->nombre);
            printf("codigo del producto : %s\n", rec->DatosMed->Datosprod->codigo);
            printf("Categoria del producto : %s\n", rec->DatosMed->Datosprod->categoria);
            printf("Descripcion del producto : %s\n", rec->DatosMed->Datosprod->descripcion);
            printf("Productos disponibles : %d\n", verificar);
            printf("=============================================\n\n");
        }
        rec = rec->sig;
    }
}

int verificarProductosEnfecha(struct NodoInventario * headInventario,char *fecha){
    struct NodoInventario * rec;
    int cont = 0,aux;
    if(headInventario != NULL)
    {
        rec = headInventario;
        while(rec != NULL)
        {
            aux = verificarStockParaCompras(rec ->DatosMed->medicamentos,fecha,rec ->DatosMed->stock);
            if(aux > 0)
            {
                cont++;
            }
            rec = rec ->sig;
        }
    }
    return cont;
}

void menuVentaYRegistro(struct Farmacias **Farmacia) {


    struct NodoInventario *aux;
    struct Producto *productoaAgregar;
    struct TipoMed **MedicamentosVenta = NULL;
    struct Boleta *boletaVenta;
    int cantProductosVenta, i = 0, cantidadDelMismoProducto, verificar, seAgrego;
    unsigned long montoVenta = 0;
    char codigo[MAX];
    char rut[MAX];
    char fecha[MAX];
    int opcion,opcionCancelar;
    int verificacionArreglo;
    int verificarCantProductosEnFecha;
    int cont = 1;

    do {
        puts("=============================================");
        printf("\n   Menu realizar venta en sucursal %s \n", (*Farmacia)->ubicacion);
        puts("=============================================\n");
        puts("(1) Realizar la compra de un/los medicamento/s");
        puts("(2) Volver");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        verificacionArreglo = 1;
        switch (opcion) {
            case 1:
                printf("\n\nIngrese la fecha de la venta (formato DD/MM/AAAA): \n");
                scanf(" %[^\n]", fecha);
                if ((strlen(fecha)!=10||(fecha[2]!='/'&&fecha[5]!='/'))){
                    printf("Formato no permitido, intente de nuevo.\n\n");
                    break;
                }

                verificarCantProductosEnFecha = verificarProductosEnfecha((*Farmacia)->headInventario,fecha);

                if(verificarCantProductosEnFecha == 0){
                    printf("No hay productos en la fecha ingresada\n");
                    break;
                }

                printf("Ingrese el rut del cliente (9 digitos): \n");
                scanf(" %[^\n]", rut);


                printf("Ingrese la cantidad de productos *diferentes* a ingresar: \n");
                scanf("%d", &cantProductosVenta);

                if (cantProductosVenta <= 0) {
                    puts("La cantidad de productos debe ser mayor a cero.");
                    break;

                }else if(verificarCantProductosEnFecha < cantProductosVenta){
                    printf("La cantidad de productos ingresados en fecha %s es mayor a la cantidad de productos disponibles",fecha);
                    break;
                }
                else
                {
                    MedicamentosVenta = (struct TipoMed **)malloc(cantProductosVenta * sizeof(struct TipoMed *));
                    if (MedicamentosVenta == NULL) {
                        puts("Error al asignar memoria.");
                        free(MedicamentosVenta);
                        verificacionArreglo = 0;
                        break;
                    }

                    mostrarProductosParaLaVenta((*Farmacia)->headInventario, fecha);

                    while ( i < cantProductosVenta)
                    {
                        printf("Ingrese el codigo de Producto(%i): ",cont);
                        scanf(" %[^\n]", codigo);
                        if (strlen(codigo)>10||strlen(codigo)<10)
                        {
                            printf("Formato no permitido, intente de nuevo, \n");
                            printf("(1) para digitar otro codigo valido o de otro producto\n");
                            printf("(2) para cancelar la compra\n");
                            printf("Seleccione una opcion: ");
                            scanf( "%d", &opcionCancelar);
                            if(opcionCancelar==1)
                                continue;
                            else
                            {
                                opcion = 2;
                                verificacionArreglo = 0;
                                break;
                            }
                        }

                        productoaAgregar = buscarMedicamentoPorCodigo((*Farmacia)->headInventario, codigo);


                        if (productoaAgregar == NULL) {
                            puts("El producto no esta disponible en esta sucursal. Por favor ingrese un codigo distinto.\n");
                            printf("(1) para elegir otro producto\n");
                            printf("(2) para cancelar la compra\n");
                            printf("Seleccione una opcion: ");
                            scanf( "%d", &opcionCancelar);
                            if(opcionCancelar==1)
                                continue;
                            else
                            {
                                opcion = 2;
                                verificacionArreglo = 0;
                                break;
                            }
                        }


                        if (estaEnBoleta(MedicamentosVenta, codigo, i) == 1) {
                            puts("El producto ya se agrego a su compra anteriormente. Por favor ingrese un codigo distinto.\n");
                            printf("(1) para elegir otro producto \n");
                            printf("(2) para cancelar la compra\n");
                            printf("Seleccione una opcion: ");
                            scanf( "%d", &opcionCancelar);
                            if(opcionCancelar==1)
                                continue;
                            else
                            {
                                opcion = 2;
                                verificacionArreglo = 0;
                                break;
                            }
                        }

                        aux = buscartipomed((*Farmacia)->headInventario, productoaAgregar->codigo);

                        if (verificarStockParaCompras(aux->DatosMed->medicamentos, fecha, aux->DatosMed->stock) == 0) {
                            printf("No hay stock Disponible de este producto, Por favor ingrese un codigo distinto.\n");
                            printf("(1) para elegir otro producto \n");
                            printf("(2) para cancelar la compra\n");
                            printf("Seleccione una opcion: ");
                            scanf( "%d", &opcionCancelar);
                            if(opcionCancelar==1){
                                continue;
                            }
                            else
                            {
                                opcion = 2;
                                verificacionArreglo = 0;
                                break;
                            }
                        }
                        if (productoaAgregar->receta == 1) {
                            puts("Este producto requiere de una receta medica. Ingrese 1 si posee receta, en caso contrario 0: ");
                            scanf("%d", &verificar);
                            if (verificar!=0 && verificar!=1){
                                printf("Valor ingresado no permitido, intente de nuevo.\n\n");
                                break;
                            }
                            if (verificar == 0) {
                                puts("No posee una receta medica. Por favor seleccione otro producto. Por favor ingrese un codigo distinto.\n");
                                printf("(1) para elegir otro producto \n");
                                printf("(2) para cancelar la compra\n");
                                printf("Seleccione una opcion: ");
                                scanf( "%d", &opcionCancelar);
                                if(opcionCancelar==1)
                                    continue;
                                else
                                {
                                    opcion = 2;
                                    verificacionArreglo = 0;
                                    break;
                                }
                            }
                        }


                        puts("Ingrese la cantidad de productos que desea agregar: ");
                        scanf("%d", &cantidadDelMismoProducto);


                        if (verificarStockParaCompras(aux->DatosMed->medicamentos, fecha, aux->DatosMed->stock) < cantidadDelMismoProducto) {
                            puts("No hay stock suficiente para completar su pedido. Por favor ingrese un codigo distinto.");
                            printf("(1) para elegir otro producto \n");
                            printf("(2) para cancelar la compra\n");
                            printf("Seleccione una opcion: ");
                            scanf( "%d", &opcionCancelar);
                            if(opcionCancelar==1){
                                continue;
                            }
                            else
                            {
                                opcion = 2;
                                verificacionArreglo = 0;
                                break;
                            }


                        }


                        montoVenta += productoaAgregar->precio * cantidadDelMismoProducto;


                        MedicamentosVenta[i] = (struct TipoMed *)malloc(sizeof(struct TipoMed));
                        if (MedicamentosVenta[i] == NULL) {
                            puts("Error al asignar memoria para el producto.");
                            for (int j = 0; j <= i; j++) {
                                if (MedicamentosVenta[j] != NULL) {
                                    if (MedicamentosVenta[j]->Datosprod != NULL) {
                                        free(MedicamentosVenta[j]->Datosprod);
                                    }
                                    free(MedicamentosVenta[j]);
                                }
                            }
                            free(MedicamentosVenta);
                            verificacionArreglo = 0;
                            break;
                        }

                        MedicamentosVenta[i]->Datosprod = (struct Producto *)malloc(sizeof(struct Producto));
                        if (MedicamentosVenta[i]->Datosprod == NULL) {
                            puts("Error al asignar memoria para el producto.");
                            for (int j = 0; j <= i; j++) {
                                if (MedicamentosVenta[j] != NULL) {
                                    free(MedicamentosVenta[j]);
                                }
                            }
                            free(MedicamentosVenta);
                            verificacionArreglo = 0;
                            break;
                        }


                        *(MedicamentosVenta[i]->Datosprod) = *productoaAgregar;
                        (MedicamentosVenta[i])->stock= cantidadDelMismoProducto;

                        eliminarYCompactar((((aux)->DatosMed->medicamentos)),fecha,&(aux ->DatosMed ->stock),cantidadDelMismoProducto);
                        aux->DatosMed->demanda+=(cantidadDelMismoProducto);


                        i++;
                        cont++;

                    }


                    if (verificacionArreglo == 1)
                    {
                        boletaVenta = crearBoleta(rut, fecha, montoVenta, MedicamentosVenta,cantProductosVenta);
                        seAgrego = agregarBoletasALista(&((*Farmacia)->boletasFarmacias), boletaVenta);
                        if (seAgrego == 1) {
                            printf("Se Agrego la boleta de %s correctamente\n", boletaVenta->rut);
                        } else {
                            puts("No se pudo agregar la boleta al sistema");
                            free(boletaVenta);
                        }
                        (*Farmacia)->presupuesto += montoVenta;

                        opcion = 2;
                    }
                }
                break;
            case 2:
                printf("Saliendo...\n");
                break;

            default:
                printf("\nOpcion no valida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 2);
}

void menuCatalogo(struct FarmaSalud **farma){
    int opcion;
    char nombre[MAX];
    char codigo[MAX];
    int receta;
    char categoria[MAX];
    char descripcion[MAX];
    unsigned long precio;
    int verificar;
    struct RaizCatalogos *aux;
    struct NodoFarmacias *recFarmacias;
    struct NodoProveedores *recProveedores;
    int eliminado;
    int verificado;
    do{
        printf("\n=============================================\n");
        puts("          Menu Catalogos:");
        printf("=============================================\n\n");
        puts("(1) Agregar Catalogo");
        puts("(2) Buscar Catalogo");
        puts("(3) Eliminar Catalogo");
        puts("(4) Mostrar Catalogo");
        puts("(5) Volver");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        verificado = 0;
        switch (opcion){
            case 1:
                printf("Ingrese el nombre del producto: ");
                scanf(" %[^\n]", nombre);


                printf("Ingrese el codigo de este producto, formato 10 digitos: ");
                scanf(" %[^\n]",codigo);
                if (strlen(codigo)>10||strlen(codigo)<10){
                    printf("Formato no permitido, intente de nuevo.\n\n");
                    break;
                }


                printf("Ingrese si este producto necesita receta, 1 para si y 0 para no: ");
                scanf("%i",&receta);
                if (receta!=0 && receta!=1){
                    printf("Valor ingresado no permitido, intente de nuevo.\n\n");
                    break;
                }
                printf("Ingrese la categoria del producto : ");
                scanf(" %[^\n]",categoria);


                printf("Ingrese la descripcion del producto : ");
                scanf(" %[^\n]",descripcion);


                printf("Ingrese el precio base que tendra el producto : ");
                scanf("%lu",&precio);
                verificar = agregarProductoAlCatalogo(&(*farma)->AbbCatalogos,nombre,codigo,receta,categoria,descripcion,precio);
                if (verificar == 1){
                    puts("Producto nuevo añadido con exito al catalogo\n");
                }
                else{
                    puts("\nNo se pudo agregar el catalogo\n");
                }
                break;
            case 2:
                printf("Ingresa el codigo del producto que deseas buscar: ");
                scanf(" %[^\n]", codigo);
                if (strlen(codigo)>10||strlen(codigo)<10){
                    printf("Formato no permitido, intente de nuevo.\n\n");
                    break;
                }
                puts("");
                aux = buscarProductoEnCatalogo((*farma)->AbbCatalogos,codigo);
                if (aux!=NULL){
                    printf("\nEl producto %s (codigo : %s) se encuentra en el catalogo",aux->DatosProductos->nombre,codigo);
                }
                else{
                    puts("El producto no se encuentra en el catalogo");
                }
                break;
            case 3:
                printf("Ingresa el codigo del producto que deseas eliminar: ");
                scanf(" %[^\n]", codigo);
                if (strlen(codigo)>10||strlen(codigo)<10)
                {
                    printf("Formato no permitido, intente de nuevo.\n\n");
                    break;
                }

                puts("");
                verificar = eliminarProductoDelCatalogo(&(*farma)->AbbCatalogos,codigo);
                if (verificar==1){
                    printf("El producto con el codigo : %s se ha eliminado con exito\n",codigo);
                    if ((*farma)->headProveedores!=NULL){
                        recProveedores = (*farma)->headProveedores;
                        do{
                            eliminado = eliminarProductoDelCatalogo(&(recProveedores->DatosProveedor->Mercancia),codigo);
                            if (eliminado==1){
                                verificado = 1;
                            }
                            recProveedores = recProveedores ->sig;
                        }while(recProveedores!=((*farma)->headProveedores));
                    }
                    if (verificado==1){
                        puts("\nEl producto ya no se vera en el catalogo de ningun proveedor asociado");
                        puts("dado que la empresa Farmasalud ya no vende este producto\n");
                    }
                    verificado = 0;
                    if ((*farma)->headFarmacias!=NULL){
                        recFarmacias=(*farma)->headFarmacias;
                        while (recFarmacias!=NULL){
                            eliminado = eliminarTipomed(&(recFarmacias -> DatosFarmacias->headInventario),codigo);
                            if (eliminado==1){
                                verificado = 1;
                            }
                            recFarmacias = recFarmacias ->sig;
                        }
                    }
                    if (verificado==1){
                        puts("El producto ya no se encuentra en el inventario de ninguna sucursal\n");
                    }
                }
                else if(verificar==-1){
                    printf("El producto con el codigo : %s no se encuentra en el sistema\n",codigo);
                }
                else{
                    puts("No se pudo eliminar el producto\n");
                }
                break;
            case 4:
                if ((*farma)->AbbCatalogos==NULL){
                    puts("No hay ningun producto en el catalogo aun");
                }
                else{
                    mostrarNodoCatalogo((*farma) -> AbbCatalogos);
                }

                break;
            case 5:
                puts("\nVolviendo al menu principal...\n");
                break;
            default:
                puts("\nOpcion no valida. Intente nuevamente.");
                break;
        }
    }while (opcion != 5);
}
void menuInventario(struct NodoFarmacias **farmacias,struct FarmaSalud *farma){
    int opcion;
    char codigo[MAX];
    struct TipoMed *tipomednuevo;
    struct NodoInventario *aux;
    int verificar;
    do {
        printf("\n=============================================\n");
        puts("          Menu Inventario:");
        printf("=============================================\n\n");
        printf("Sucursal %s \n",(*farmacias)->DatosFarmacias->ubicacion);
        puts("(1) Agregar tipo medicamento");
        puts("(2) Buscar tipo medicamento");
        puts("(3) Eliminar tipo medicamento");
        puts("(4) Mostrar tipo/s medicamento/s");
        puts("(5) Volver");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                printf("\nIngrese codigo del medicamento: ");
                scanf(" %[^\n]", codigo);
                if (strlen(codigo)>10||strlen(codigo)<10){
                    printf("Formato no permitido, intente de nuevo.\n\n");
                    break;
                }
                tipomednuevo = crearTipoMed(codigo,farma->AbbCatalogos);
                if (tipomednuevo==NULL){
                    printf("Codigo no existe en el catalogo\n");
                    break;
                }
                verificar = agregarTipoMedalista(&(*farmacias)->DatosFarmacias->headInventario,tipomednuevo);
                if (verificar==1){
                    printf("\nTipo de medicamento %s agregado exitosamente.\n",tipomednuevo->Datosprod->nombre);
                }
                else{
                    printf("\nNo se pudo agregar %s en el sistema\n",codigo);
                    free(tipomednuevo);
                }
                break;
            case 2:
                printf("Ingrese codigo del medicamento a buscar: ");
                scanf(" %[^\n]", codigo);
                if (strlen(codigo)>10||strlen(codigo)<10){
                    printf("Formato no permitido, intente de nuevo.\n\n");
                    break;
                }
                aux = buscartipomed((*farmacias)->DatosFarmacias->headInventario,codigo);
                if(aux!=NULL){
                    printf("\nEl tipo de medicamento %s se encontro exitosamente\n",aux->DatosMed->Datosprod->nombre);
                }
                else{
                    printf("\nNo se logro encontrar el tipo de mecicamento %s\n",codigo);
                }
                break;
            case 3:
                printf("Ingrese el codigo del medicamento a eliminar: ");
                scanf(" %[^\n]",codigo);
                if (strlen(codigo)>10||strlen(codigo)<10){
                    printf("Formato no permitido, intente de nuevo.\n\n");
                    break;
                }


                verificar = eliminarTipomed(&(*farmacias)->DatosFarmacias->headInventario, codigo);
                if(verificar==1){
                    printf("\nTipo de medicamento/producto eliminado exitosamente.\n");
                    //mostrartipo
                }
                else if(verificar==-2){
                    printf("Actualmente la surcusal %s no tiene ningun tipo de producto\n",(*farmacias)->DatosFarmacias->ubicacion);
                }
                else if(verificar==-1){
                    printf("\nEl tipo de medicamento/producto no existe en %s \n",(*farmacias)->DatosFarmacias->ubicacion);
                }
                else{
                    puts("\nNO se pudo eliminar medicamento");
                }
                break;
            case 4:
                mostrarNodoInventario((*farmacias)->DatosFarmacias->headInventario);
                break;
            case 5:
                printf("\nVolviendo al menu principal...\n");
                break;
            default:
                puts("\nOpcion no valida. Intente nuevamente.");
                break;
        }
    } while(opcion != 5);
}

void menuBoletas(struct NodoBoleta **headBoleta,char *ubicacionSucursal)
{
    int opcion;
    int verificar;
    char rut[MAX];
    do{
        printf("\n=============================================\n");
        printf("          Menu Boletas de sucursal : %s\n",ubicacionSucursal);
        printf("=============================================\n\n");
        printf("(1) Eliminar boleta de la sucursal %s\n",ubicacionSucursal);
        printf("(2) Mostrar boletas de la sucurusal %s\n",ubicacionSucursal);
        puts("(3) Volver");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        switch(opcion)
        {
            case 1:
                printf("Ingrese el rut para eliminar la boleta: ");
                scanf("%[^\n]",rut);
                verificar = eliminarBoleta((headBoleta),rut);
                if(verificar == 1)
                {
                    printf("Boleta eliminada exitosamente");
                }
                break;
            case 2:
                if((*headBoleta) != NULL)
                {
                    mostrarNodoBoleta((*headBoleta));
                }
                else
                {
                    puts("No hay boletas disponibles");
                }

                break;
            case 3:
                printf("\nVolviendo al menu Farmacia...\n");
                break;
            default:
                printf("\nOpcion no valida. Intente nuevamente.");
                break;
        }
    }while(opcion != 3);


}

void menuFarmacias(struct FarmaSalud **farma) {
    int opcion;
    char ubicacion[MAX];
    int capacidad;
    long presupuesto;
    struct Farmacias *farmaciaNueva;
    struct NodoFarmacias * aux;
    int verificacion;
    do {
        printf("\n=============================================\n");
        puts("          Menu Farmacias:");
        printf("=============================================\n\n");
        puts("(1) Agregar Farmacia");
        puts("(2) Buscar Farmacia");
        puts("(3) Eliminar Farmacia");
        puts("(4) Elegir Sucursal para Menu Boletas");
        puts("(5) Mostrar Farmacia/s");
        puts("(6) Volver");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                printf("\nIngrese ubicacion de la farmacia: ");
                scanf(" %[^\n]", ubicacion);
                printf("Ingrese el valor de la capacidad total de la bodega : ");
                scanf("%d", &capacidad);


                printf("Ingrese presupuesto de la farmacia: ");
                scanf("%li", &presupuesto);


                farmaciaNueva = crearFarmacia( ubicacion, capacidad, presupuesto);
                verificacion = agregarFarmaciaALista(&(*farma)->headFarmacias,farmaciaNueva);


                if (verificacion == 1) {
                    printf("\nFarmacia de direccion %s agregada con exito\n", ubicacion);
                } else {
                    printf("\nLa farmacia de direccion %s ya existe\n", ubicacion);
                    free(farmaciaNueva);
                }
                break;
            case 2:
                printf("\nIngrese ubicacion de la farmacia a buscar: ");
                scanf(" %[^\n]", ubicacion);


                aux = buscarFarmacia((*farma)->headFarmacias, ubicacion);
                if (aux != NULL) {
                    printf("\nLa farmacia de ubicacion %s se encuentra en el sistema\n",aux -> DatosFarmacias -> ubicacion);
                    mostrarFarmacia(aux->DatosFarmacias);
                } else {
                    printf("\nLa farmacia de ubicacion %s no se encuentra en el sistema\n",ubicacion);
                }
                break;
            case 3:
                printf("\nIngrese ubicacion de la farmacia a eliminar: ");
                scanf(" %[^\n]", ubicacion);


                verificacion = eliminarFarmacia(&(*farma)->headFarmacias, ubicacion);
                if (verificacion==1){
                    puts("\nFarmacia eliminada exitosamente.\n");
                }
                else if(verificacion==-1){
                    puts("Sucursal no se encuentra en el sistema para eliminar\n");
                }
                else if(verificacion==-2){
                    puts("No hay ninguna sucursal de FarmaSalud por el momento");
                }
                else{
                    printf("\nLa farmacia no se pudo eliminar.\n");
                }
                break;
            case 4:
                if ((*farma)->headFarmacias==NULL){
                    printf("Aun no hay sucursales en el sistema, agregue una antes\n\n");
                }
                else {
                    printf("Elija una sucursal que haya hecho alguna venta : \n\n");
                    mostrarNodoFarmacias((*farma)->headFarmacias);
                    printf("\nIngrese ubicacion de la farmacia : ");
                    scanf(" %[^\n]", ubicacion);


                    aux = buscarFarmacia((*farma)->headFarmacias, ubicacion);


                    if(aux != NULL){
                        if(aux ->DatosFarmacias->boletasFarmacias != NULL)
                        {
                            menuBoletas(&(aux ->DatosFarmacias ->boletasFarmacias),aux ->DatosFarmacias ->ubicacion);
                        }
                        else{
                            printf("\nLa farmacia de ubicacion %s no ha realizado ninguna venta\n",ubicacion);
                        }
                    }
                    else{
                        printf("\nLa farmacia de ubicacion %s no se encuentra en el sistema\n",ubicacion);
                    }
                }
                break;


            case 5:
                if ((*farma)->headFarmacias==NULL){
                    puts("Actualmente no hay ninguna sucursal para mostrar");
                }
                else{
                    mostrarNodoFarmacias((*farma)->headFarmacias);
                }
                break;
            case 6:
                printf("\nVolviendo al menu principal...\n");
                break;
            default:


                printf("\nOpcion no valida. Intente nuevamente.");
                break;
        }
    } while(opcion != 6);
}
//menuElegirFarmacia
void menuelegirFarmacia(struct FarmaSalud **farma) {
    int opcion;
    char ubicacionelegida[MAX];
    struct NodoFarmacias *elegido = NULL;
    do {
        puts("");
        puts("=============================================");
        puts("\n         Sucursales de FarmaSalud");
        puts("=============================================\n");
        puts("Menu para elegir a cual sucursal darle nuevo/s tipo/s de producto");
        puts("(1) Elegir una sucursal");
        puts("(2) Volver");
        scanf("%i", &opcion);


        switch (opcion) {
            case 1:
                puts("\nOpciones");

                mostrarNodoFarmacias((*farma)->headFarmacias);
                printf("\nIngrese la ubicación de la farmacia a la cual le quiera añadir inventario :\n");
                scanf(" %[^\n]", ubicacionelegida);
                elegido = buscarFarmacia((*farma)->headFarmacias, ubicacionelegida);
                if (elegido == NULL) {
                    printf("\nLa direccion que ingreso no tiene sucursal \n");
                }else{
                    menuInventario(&elegido,(*farma));
                }
                break;
            case 2:
                printf("Saliendo...\n");
                break;
            default:
                printf("\nOpcion no valida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 2);
}
//mostrarProveedoresQueSirven
void mostrarProveedoresQuesirven(struct NodoProveedores *headProveedores,char *codigo){
    struct NodoProveedores * rec;
    if(headProveedores != NULL)
    {
        rec = headProveedores;
        do{
            if(buscarProductoEnCatalogo(rec->DatosProveedor->Mercancia,codigo)!=NULL){
                mostrarProveedor(rec->DatosProveedor);
            }
            rec = rec ->sig;
        }while(rec != headProveedores);
    }
}
//buscarProveedorQueSirve
int buscarProveedorQuesirve(struct NodoProveedores *headProveedores,char *nombre, char *codigo){
    struct NodoProveedores * rec = headProveedores;
    if(headProveedores != NULL)
    {
        do{
            if(buscarProductoEnCatalogo(rec->DatosProveedor->Mercancia,codigo)!=NULL)
            {
                if(strcmp(rec->DatosProveedor->nombre,nombre)==0){
                    return 1;
                }
            }
            rec = rec ->sig;
        }while(rec != headProveedores);
        return 0;
    }
    return 0;
}
//sumatoriaDeStockFarmacia
unsigned long sumatoriaDeStockFarmacia(struct NodoFarmacias *sucursal){
    unsigned long suma = 0;
    struct NodoInventario *rec;
    rec = sucursal->DatosFarmacias->headInventario;
    while(rec!=NULL){
        suma = rec->DatosMed->stock;
        rec = rec->sig;
    }
    return suma;
}

void altaDemanda(struct NodoFarmacias *sucursal,struct NodoInventario **tipomed){
    long suma = 0,cont = 0;
    struct NodoInventario *rec;
    if (sucursal->DatosFarmacias->headInventario!=NULL){


        rec = sucursal->DatosFarmacias->headInventario;
        while (rec!=NULL){
            suma += rec->DatosMed->demanda;
            cont++;
            rec = rec->sig;
        }
    }
    if (suma==0||cont==0){
        (*tipomed)->DatosMed->altademanda = 0;
    }
    else{
        long promedio = (suma/cont);
        if (((*tipomed)->DatosMed->demanda)>promedio){
            (*tipomed)->DatosMed->altademanda = 1;
        }
        else{
            (*tipomed)->DatosMed->altademanda = 0;
        }
    }
}

void agregarMedicamentos(struct NodoProveedores **prove,struct NodoInventario **tipomed,long cantidad,char *fecha,int lote){
    long i;
    long maximorecorrer = (long)(((*tipomed)->DatosMed->stock)+cantidad);
    struct Proveedor *proveedormedicamento= (*prove)->DatosProveedor;


    struct Medicamento **aux = (struct Medicamento **)realloc((*tipomed)->DatosMed->medicamentos, maximorecorrer * sizeof(struct Medicamento *));
    if (aux == NULL) {
        printf("Error al reasignar memoria\n");
    }
    (*tipomed)->DatosMed->medicamentos=aux;
    for (i = (long)((*tipomed)->DatosMed->stock); i < maximorecorrer; i++) {
        (*tipomed)->DatosMed->medicamentos[i] = (struct Medicamento *)malloc(sizeof(struct Medicamento));
        if ((*tipomed)->DatosMed->medicamentos[i] == NULL) {
            printf( "Error al asignar memoria para medicamento\n");
        }
        (*tipomed)->DatosMed ->medicamentos[i] ->fechacaducidad = (char*) malloc(strlen(fecha) + 1);
        strcpy((*tipomed)->DatosMed->medicamentos[i]->fechacaducidad,(fecha));
        (*tipomed)->DatosMed->medicamentos[i]->lote = lote;
        (*tipomed)->DatosMed->medicamentos[i]->DatosProveedor = proveedormedicamento;




    }
    (*tipomed)->DatosMed->stock+=(int)cantidad;
    /*
    //Esto es para asegurar que se esta guardando de buena manera
    for (i=0;i<maximorecorrer;i++){
        puts("\n=============================================");
        printf("Fecha caducidad  : %s \n",((*tipomed))->DatosMed->medicamentos[i]->fechacaducidad);
        printf("Numero de lote  : %i \n",((*tipomed))->DatosMed->medicamentos[i]->lote);
        printf("Nombre del proveedor : %s \n",((*tipomed))->DatosMed->medicamentos[i]->DatosProveedor->nombre);
        puts("\n=============================================");
    }
    */

}

void menuConfirmarOrden(struct NodoProveedores **prove,struct NodoFarmacias **sucursal,struct NodoInventario **tipomed,long cantidad,unsigned long precio){
    int opcion;
    int lote;
    char fechacaducidad[MAX];
    long presupuestopost = ((*sucursal)->DatosFarmacias->presupuesto)-precio;
    do{
        puts("\n=============================================");
        printf("Orden para sucursal %s de %li %s para el proveedor %s\n",(*sucursal)->DatosFarmacias->ubicacion,cantidad,(*tipomed)->DatosMed->Datosprod->nombre,(*prove)->DatosProveedor->nombre);
        printf("Precio total para la orden : $%li pesos\n",precio);
        printf("       ¿Realizar la compra?\n");
        printf("Tenga en cuenta que el presupuesto de la farmacia quedara en $%li pesos \n",presupuestopost);
        puts("=============================================");
        printf("(1) Si\n");
        printf("(2) No\n");
        puts("Seleccione una opcion: ");
        scanf("%i",&opcion);
        switch(opcion){
            case 1:

                printf("Antes de terminar la orden, Asignele los datos basicos a los productos\n");
                printf("Ingrese el numero del lote : ");
                scanf("%i",&lote);
                printf("Ingrese la fecha de caducidad del lote (formato DD/MM/AAAA) : ");
                scanf(" %[^\n]",fechacaducidad);
                if (strlen(fechacaducidad)!=10||(fechacaducidad[2]!='/'&&fechacaducidad[5]!='/')){
                    printf("Formato no permitido, intente de nuevo.\n\n");
                    break;
                }
                agregarMedicamentos(&(*prove),&(*tipomed),cantidad,fechacaducidad,lote);
                (*sucursal)->DatosFarmacias->presupuesto -= precio;
                printf("Orden hecha con exito!\n");
                opcion = 2;
                break;
            case 2:
                printf("Orden cancelada\n\n");
                printf("Saliendo...\n");
                break;
            default:
                printf("\nOpcion no valida. Intente nuevamente.\n");
                break;
        }
    }while(opcion!=2);
}
//menuRealizarOrden
void menuRealizarOrden(struct NodoProveedores **prove,struct NodoFarmacias **sucursal,struct NodoInventario **tipodemedicamento){
    int opcion;
    long cantidad;
    unsigned long sumatoria = sumatoriaDeStockFarmacia((*sucursal));
    unsigned long restante;
    unsigned long preciobase = ((*tipodemedicamento)->DatosMed->Datosprod->precio);
    unsigned long precioacobrar; //esto existe para que haya ganancia
    altaDemanda((*sucursal),&(*tipodemedicamento));
    do{
        puts("=============================================");
        printf("   Menu realizar orden de %s en surcusal %s \n",(*tipodemedicamento)->DatosMed->Datosprod->nombre,(*sucursal)->DatosFarmacias->ubicacion);
        puts("=============================================\n");
        if ((*tipodemedicamento)->DatosMed->altademanda==1){
            printf("¡Tenga en cuenta que actualmente este medicamento en esta sucursal tiene alta demanda de venta!\n");
        }
        //mensaje de alta demanda;
        printf("(1) Elegir la cantidad\n");
        printf("(2) Volver\n");
        puts("Seleccione una opcion: ");
        scanf("%i",&opcion);
        switch(opcion){
            case 1:
                printf("Elija la cantidad de %s que quiera ordenarle a %s : ",(*tipodemedicamento)->DatosMed->Datosprod->nombre,(*prove)->DatosProveedor->nombre);
                scanf("%li",&cantidad);
                if (cantidad<=0){
                    printf("La orden no se puede efectuar, dado que la cantidad tiene que ser mayor a cero");
                }
                else{
                    precioacobrar = (unsigned long)(((preciobase)*0.4)*cantidad)+(*prove)->DatosProveedor->cuota; //esto es para que la farmacia tenga ganancia por si acaso profe xd
                    if ((cantidad+sumatoria)>((*sucursal)->DatosFarmacias->capacidadInventario)){
                        restante = ((*sucursal)->DatosFarmacias->capacidadInventario) - (sumatoria);
                        printf("La orden no se puede efectuar, dado que la capacidad del inventario no lo aguanta");
                        printf("\nCapacidad total disponible para medicamentos unitarios de cualquier tipo : %li",restante);
                        printf("\nHaga una orden menor\n\n");
                    }
                    else if((cantidad+sumatoria)==((*sucursal)->DatosFarmacias->capacidadInventario)){
                        printf("Con esta orden la capacidad total del inventario se llenara");
                        menuConfirmarOrden(&(*prove),&(*sucursal),&(*tipodemedicamento),cantidad,precioacobrar);
                        opcion = 2;
                    }
                    else{
                        menuConfirmarOrden(&(*prove),&(*sucursal),&(*tipodemedicamento),cantidad,precioacobrar);
                        opcion = 2;
                    }
                }
                break;
            case 2:
                printf("Saliendo...\n");
                break;
            default:
                printf("\nOpcion no valida. Intente nuevamente.\n");
                break;
        }




    }while(opcion!=2);


}

void menuOrden(struct FarmaSalud **farma,struct NodoFarmacias **sucursal){
    int opcion;
    char codigo[MAX];
    char nombre[MAX];
    int verificar;
    struct NodoProveedores *elegido = NULL;
    struct NodoInventario *aux;
    do{
        puts("");
        puts("=============================================");
        printf("   Menu pedir orden en surcusal %s \n",(*sucursal)->DatosFarmacias->ubicacion);
        puts("=============================================\n");
        puts("(1) Elegir el producto para hacerle orden");
        puts("(2) Volver");
        puts("Seleccione una opcion: ");
        if ((*sucursal)->DatosFarmacias->boletasFarmacias!=NULL){
            alerta((*sucursal)->DatosFarmacias);
        }

        scanf("%i",&opcion);
        switch (opcion) {
            case 1:
                printf("\nIngrese el codigo del producto que quiere ordenar :");
                scanf(" %[^\n]", codigo);
                if (strlen(codigo)>10||strlen(codigo)<10){
                    printf("Formato no permitido, intente de nuevo.\n\n");
                    break;
                }
                aux = buscartipomed((*sucursal)->DatosFarmacias->headInventario,codigo);
                if (aux==NULL){
                    printf("\nLa orden no se puede hacer dado que ese producto no se encuentra en");
                    printf("\nesta sucursal. Elija otra sucursal o integre el producto en esta farmacia\n");
                }
                else{
                    if ((*farma)->headProveedores==NULL){
                        printf("\nNo hay proveedores que distribuyan ese medicamento\n");
                    }
                    else{
                        printf("\nEstas son los proveedores que te sirven en ese caso");
                        mostrarProveedoresQuesirven((*farma)->headProveedores,codigo);
                        puts("\nElija uno de estos proveedores por nombre");
                        printf("\n tenga en cuenta su cuota, le van a cobrar : ");
                        scanf(" %[^\n]", nombre);
                        verificar = buscarProveedorQuesirve((*farma)->headProveedores,nombre,codigo);
                        if (verificar==1){
                            printf("Ha elegido el proveedor %s\n",nombre);
                            elegido = buscarProveedores((*farma)->headProveedores,nombre);
                            menuRealizarOrden(&elegido,&(*sucursal),&aux);
                            opcion = 2;
                        }
                        else{
                            printf("\nEl Proveedor elegido no esta en la lista de los que proveen el producto elegido\n");
                        }
                    }
                }
                break;
            case 2:
                printf("Saliendo...\n");
                break;
            default:
                printf("\nOpcion no valida. Intente nuevamente.\n");
                break;
        }
    }while(opcion!=2);
}
//
void menuOrdenFarmacia(struct FarmaSalud **farma) {
    int opcion;
    char ubicacionelegida[MAX];
    struct NodoFarmacias *elegido = NULL;
    do {
        puts("");
        puts("=============================================");
        puts("        Sucursales de FarmaSalud");
        puts("=============================================\n");
        puts("Menu para elegir a cual sucursal hacerle ordenes de producto");
        puts("(1) Elegir una sucursal");
        puts("(2) Volver");
        puts("Seleccione una opcion: ");
        scanf("%i", &opcion);
        switch (opcion) {
            case 1:
                puts("\nOpciones");
                mostrarNodoFarmacias((*farma)->headFarmacias);
                printf("\nIngrese la ubicación de la farmacia que quiere crear una orden :\n");
                scanf(" %[^\n]", ubicacionelegida);
                elegido = buscarFarmacia((*farma)->headFarmacias, ubicacionelegida);
                if (elegido == NULL) {
                    printf("\nLa direccion que ingreso no tiene sucursal \n");
                }else if(elegido!=NULL){
                    if (elegido->DatosFarmacias->headInventario==NULL){
                        printf("Esta sucursal no tiene ningun tipo de producto en su bodega\n");
                        printf("Elija otra sucursal o gestione el inventario de la que eligio\n\n");
                    }
                    else{
                        menuOrden(&(*farma),&elegido);
                    }
                }


                break;
            case 2:
                printf("Saliendo...\n");
                break;
            default:
                printf("\nOpcion no valida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 2);
}
//funcion menu para darle catalogo a los proveedores
void menuCatalogoProveedores(struct NodoProveedores **headProvedores,struct FarmaSalud **farma){
    int opcion;
    char codigo[MAX];
    struct RaizCatalogos *ptr;
    int verificar;
    do{
        puts("=============================================");
        printf("Catalogo de Productos que distribuye el Proveedor %s\n",(*headProvedores)->DatosProveedor->nombre);
        puts("=============================================\n");
        puts("(1) Agregar Producto");
        puts("(2) Buscar Producto");
        puts("(3) Eliminar Producto");
        puts("(4) Mostrar Productos");
        puts("(5) Volver");
        puts("Seleccione una opcion: ");
        scanf("%i",&opcion);
        switch ((opcion)){
            case 1:
                printf("Ingrese el codigo del producto a agregar:");
                scanf(" %[^\n]",codigo);
                if (strlen(codigo)>10||strlen(codigo)<10){
                    printf("Formato no permitido, intente de nuevo.\n\n");
                    break;
                }


                ptr = buscarProductoEnCatalogo((*farma)->AbbCatalogos,codigo);
                if (ptr==NULL){
                    printf("El producto no se encuentra en el catalogo de la farmacia\n");
                }
                else{
                    printf("El producto se encuentra en el catalogo de la farmacia\n");
                    verificar = agregarProductoCatalogoProveedor(codigo,&(*headProvedores)->DatosProveedor->Mercancia,ptr);
                    if (verificar==1){
                        printf("\nEl producto %s fue agregado con exito al catalogo de los proveedores\n",ptr->DatosProductos->nombre);
                    }
                    else{
                        printf("El producto no se pudo agregar al catalogo del proveedor\n");
                        free(ptr);
                    }
                }
                break;
            case 2:
                printf("Ingrese el codigo del producto que desea \n");
                printf("buscar en el catalogo de los proveedores :");
                scanf(" %[^\n]", codigo);
                if (strlen(codigo)>10||strlen(codigo)<10){
                    printf("Formato no permitido, intente de nuevo.\n\n");
                    break;
                }
                ptr = buscarProductoEnCatalogo((*headProvedores) ->DatosProveedor -> Mercancia,codigo);
                if (ptr!=NULL){
                    printf("\nEl producto %s se encuentra en el catalogo del proveedor\n",ptr->DatosProductos->nombre);
                }
                else{
                    printf("\nEl producto no se encuenta en el catalogo del proveedor\n");
                }


                break;
            case 3:
                printf("Ingrese el codigo del producto que \n");
                printf("desea borrar del catalogo de los proveedores : ");
                scanf(" %[^\n]", codigo);
                if (strlen(codigo)>10||strlen(codigo)<10){
                    printf("Formato no permitido, intente de nuevo.\n\n");
                    break;
                }
                verificar = eliminarProductoDelCatalogo(&((*headProvedores)->DatosProveedor->Mercancia),codigo);
                if (verificar==1){
                    printf("El producto fue exitosamente eliminado del catalogo del proveedor\n");
                }
                else if (verificar==-1){
                    printf("El producto no se encuentra en el catalogo del proveedor\n");
                }
                else if (verificar==-2){
                    printf("No hay productos en el catalogo del proveedor\n");
                }
                else{
                    printf("No se pudo eliminar el producto del catalogo\n");
                }
                break;
            case 4:
                if((*headProvedores)->DatosProveedor->Mercancia==NULL){
                    printf("Actualmente el proveedor %s no comparte ningun producto con FarmaSalud\n",(*headProvedores)->DatosProveedor->nombre);
                }
                else{
                    mostrarNodoCatalogo((*headProvedores)->DatosProveedor->Mercancia);
                }

                break;
            case 5:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
                break;
        }
    }while(opcion!=5);
}
//funcion menu para saber a cual proveedor darle catalogo
void menuElegirProveedores(struct FarmaSalud **farma) {
    int opcion;
    char nombre[MAX];
    struct NodoProveedores *elegido = NULL;
    do {
        printf("\n\n=============================================\n");
        puts("               Proveedores de FarmaSalud");
        printf("=============================================\n\n");
        puts("(1) Elegir un proveedor");
        puts("(2) Volver");
        puts("Seleccione una opcion: ");
        scanf("%i", &opcion);
        switch (opcion){
            case 1:
                puts("\nElija un proveedor de la lista");
                mostrarNodoProveedores((*farma)->headProveedores);
                printf("Ingrese el nombre del proveedor al cual le quiera añadir productos a su catalogo :\n");
                scanf(" %[^\n]", nombre);
                elegido = buscarProveedores((*farma)->headProveedores, nombre);
                if (elegido == NULL) {
                    printf("El proveedor elegido no esta en el sistema\n");
                } else {
                    menuCatalogoProveedores(&elegido,&(*farma));
                }
                break;
            case 2:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 2);
}
//funcion para menu de proovedores
void menuProveedores(struct FarmaSalud **farma) {
    int opcion;
    char nombre[MAX], ubicacion[MAX];
    unsigned long cuota;
    int verificacion;
    struct Proveedor * proveedorNuevo;
    struct NodoProveedores * aux;
    do {
        printf("\n=============================================\n");
        puts("                   Menu Proveedores:");
        printf("=============================================\n\n");
        puts("(1) Agregar Proveedor");
        puts("(2) Buscar Proveedor");
        puts("(3) Eliminar Proveedor");
        puts("(4) Darle catalogo a Proveedor");
        puts("(5) Mostrar Proveedor/es");
        puts("(6) Volver");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                printf("Ingrese nombre del proveedor :");
                scanf(" %[^\n]", nombre);


                printf("Ingrese ubicacion del proveedor :");
                scanf(" %[^\n]", ubicacion);


                printf("Ingrese cuota del proveedor :");
                scanf("%lu", &cuota);


                proveedorNuevo = crearProveedor(nombre,ubicacion,cuota);
                verificacion = agregarProveedor(&(*farma) -> headProveedores,proveedorNuevo);


                if (verificacion == 1) {
                    printf("Proveedor de nombre %s se agrego con exito\n",proveedorNuevo ->nombre);
                } else {
                    printf("El proveedor %s no se pudo agregar\n",nombre);
                    free(proveedorNuevo);
                }


                break;
            case 2:
                printf("Ingrese nombre del proveedor a buscar: ");
                scanf(" %[^\n]", nombre);
                aux = buscarProveedores((*farma)-> headProveedores , nombre);
                if (aux != NULL)
                {
                    printf("El Proveedor de nombre %s se encuentra en sistema\n",aux->DatosProveedor->nombre);
                }
                else {
                    printf("El Proveedor de nombre %s no se encuentra en sistema\n",nombre);
                }
                break;
            case 3:
                printf("Ingrese nombre del proveedor a eliminar: ");
                scanf(" %[^\n]", nombre);

                verificacion = eliminarProveedor(&(*farma)->headProveedores, nombre);
                if (verificacion==1){
                    printf("\nProveedor de nombre %s eliminado exitosamente.\n",nombre);
                }
                else{
                    printf("\nEl proovedor de nombre %s no se pudo eliminar\n",nombre);
                }
                break;
            case 4:
                if ((*farma)->AbbCatalogos==NULL){
                    printf("Farmasalud aun no tiene un catalogo de sus productos. Agregue aunque sea uno\n");
                }
                else if((*farma)->headProveedores==NULL){
                    printf("No hay proveedores asociados para darles un catalogo de productos. Agregue alguno primero\n");
                }
                else{
                    menuElegirProveedores(&(*farma));
                }
                break;
            case 5:
                if ((*farma)->headProveedores==NULL){
                    puts("Actualmente no se tienen proveedores asociados.\n");
                }
                else{
                    mostrarNodoProveedores((*farma)->headProveedores);
                }

                break;
            case 6:
                printf("Volviendo al menu principal...\n");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
                break;
        }
    } while(opcion != 6);
}
//funcion del menu venta para poder elegir el cual sucursal hacer la venta
void menuVenta(struct FarmaSalud **Farma)
{
    int opcion;
    char ubicacion[MAX];
    struct NodoFarmacias *nodoFarmaciaActual;
    do{
        puts("=============================================");
        printf("\nMenu Venta:\n");
        puts("=============================================");
        printf("(1) Elegir una sucursal para hacer venta\n");
        printf("(2) Volver\n");
        printf("Seleccione una opcion: ");
        scanf("%d",&opcion);
        switch(opcion){
            case 1:
                mostrarNodoFarmacias((*Farma)->headFarmacias);
                printf("\nIngrese ubicacion de la farmacia: \n");
                scanf(" %[^\n]", ubicacion);

                nodoFarmaciaActual = buscarFarmacia((*Farma)->headFarmacias,ubicacion);
                if(nodoFarmaciaActual == NULL)
                {
                    puts("Esta farmacia no esta registrada en el sistema");
                }
                else if(nodoFarmaciaActual ->DatosFarmacias->headInventario == NULL){
                    puts("Esta Farmacia NO tiene productos disponibles");
                }
                else{
                    menuVentaYRegistro(&(nodoFarmaciaActual->DatosFarmacias));
                }
                break;
            case 2:
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
                break;
        }
    }while(opcion != 2);
}
//funcion de menu principal para llegar a los otros menus
void mostrarMenu()
{
    puts("=============================================");
    puts("          Bienvenido a Farmasalud");
    puts("=============================================\n");
    puts("Menu Principal :\n");
    puts("(1) Gestionar Farmacias");
    puts("(2) Gestionar Catalogo");
    puts("(3) Gestionar Proveedores");
    puts("(4) Gestionar Inventario de una Farmacia");
    puts("(5) Hacer Orden de medicamento en una Farmacia");
    puts("(6) Hacer venta y registro");
    puts("(7) Salir");
    printf("Seleccione una opcion: ");
}

//main
int main() {
    struct FarmaSalud *farma = NULL;
    farma = (struct FarmaSalud *) malloc(sizeof(struct FarmaSalud));
    farma->AbbCatalogos = NULL;
    farma->headProveedores = NULL;
    farma->headFarmacias = NULL;
    int opcion;


    do {
        mostrarMenu();
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                menuFarmacias(&farma);
                break;
            case 2:
                menuCatalogo(&farma);
                break;
            case 3:
                menuProveedores(&farma);
                break;
            case 4:
                if (farma->headFarmacias == NULL) {
                    printf("\nNo hay farmacias disponibles. Agregue una farmacia primero.\n\n");

                } else if (farma->AbbCatalogos == NULL) {
                    printf("\nNo hay productos en el catalogo. Agregue alguno primero\n\n");
                } else {
                    menuelegirFarmacia(&farma);
                }
                break;
            case 5:
                if (farma->headFarmacias == NULL) {
                    printf("\nNo hay farmacias disponibles. Agregue una farmacia primero.\n\n");
                } else if (farma->AbbCatalogos == NULL) {
                    printf("\nNo hay productos en el catalogo. Agregue alguno primero\n\n");
                } else if(farma->headProveedores==NULL){
                    printf("\nNo hay proveedores asociados a FarmaSalud. Agregue alguno primero\n\n");
                }
                else {
                    menuOrdenFarmacia(&farma);
                }
                break;
            case 6:
                if (farma->headFarmacias == NULL) {
                    printf("\nNo hay farmacias disponibles. Agregue una farmacia primero.\n\n");
                } else if (farma->AbbCatalogos == NULL) {
                    printf("\nNo hay productos en el catalogo. Agregue alguno primero\n\n");
                }
                else {
                    menuVenta(&farma);
                }
            case 7:
                printf("Saliendo...\n");
                break;


            default:
                printf("Opcion no valida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 7);
    return 0;
}






