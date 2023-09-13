#ifndef BLOC_NOTAS_H_INCLUDED
#define BLOC_NOTAS_H_INCLUDED
#define TAMANIO_NOTA 70
#define NOTA_POR_DEFECTO "Ir por pan"
class Nota{
    char descripcion[TAMANIO_NOTA+1];
public:
    Nota();
    Nota(char* descripcion);
    bool fijaDescripcion(char* d);
    char* dameDescripcion();
};
    Nota::Nota(){
        strcpy(this->descripcion,NOTA_POR_DEFECTO);
    }

    Nota::Nota(char* descripcion){
        fijaDescripcion(descripcion);
    }
    bool Nota::fijaDescripcion(char* d){
        if (strlen(d)>0 && strlen(d)<TAMANIO_NOTA){
            strcpy(this->descripcion,d);
            return true;
        }
        else{
            return false;
        }
    }
    char* Nota::dameDescripcion(){
        return descripcion;
    }

#endif // BLOC_NOTAS_H_INCLUDED
