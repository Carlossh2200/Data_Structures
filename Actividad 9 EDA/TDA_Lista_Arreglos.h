#ifndef TDA_LISTA_ARREGLOS_H_INCLUDED
#define TDA_LISTA_ARREGLOS_H_INCLUDED
#include "Materia.h"

typedef int posicion;

struct ListaMateria{
    tipo_elemento elementos[MAX_MATERIAS];
    int ultimo;
public:
    ListaMateria();
    posicion primero();
    posicion fin();
    posicion siguiente(posicion p);
    posicion anterior(posicion p);
    posicion localiza(tipo_elemento x);
    bool inserta(tipo_elemento x, posicion p);
    bool suprime(posicion p);
    bool estaLlena();
    bool estaVacia();
    bool mismo(tipo_elemento x,tipo_elemento y);
    int dameCuenta();
    tipo_elemento recupera(posicion p);
};

ListaMateria::ListaMateria(){
    ultimo=-1;
}

posicion ListaMateria::fin(){
    return ultimo+1;
}

posicion ListaMateria::primero(){
    return 0;
}

posicion ListaMateria::siguiente(posicion p){
    if (p>=0 && p<=ultimo){
        return p+1;
    }
    else{
        return p;
    }
}

posicion ListaMateria::localiza(tipo_elemento x){
    posicion p,q;
    for(p=primero(),q=fin();p!=q;p=siguiente(p)){
        if (mismo(x,elementos[p])){
            break;
        }
    }
    return p;
}

bool ListaMateria::inserta(tipo_elemento x,posicion p){
    if (p>=0 && p<=ultimo+1 && p<MAX_MATERIAS && !estaLlena()){
        for(int i=++ultimo;i>p;i--){
            elementos[i]=elementos[i-1];
        }
        elementos[p]=x;
        return true;
    }
    else{
        return false;
    }
}

bool ListaMateria::suprime(posicion p){
    int i;
    if (p>=0&&p<=ultimo){
        for(i=p;i<ultimo;i++){
            elementos[i]=elementos[i+1];
        }
        ultimo--;
        return true;
    }
    else{
        return false;
    }
}

bool ListaMateria::estaLlena(){
    return ultimo==MAX_MATERIAS-1;
}

bool ListaMateria::estaVacia(){
    return ultimo==-1;
}

int ListaMateria::dameCuenta(){
    return ultimo+1;
}

tipo_elemento ListaMateria::recupera(posicion p){
    tipo_elemento elementoErroneo=ELEMENTOS_POR_DEFECTO;
    if (p>=0&&p<=ultimo){
        return elementos[p];
    }
    else{
        return elementoErroneo;
    }
}



#endif // TDA_LISTA_ARREGLOS_H_INCLUDED
