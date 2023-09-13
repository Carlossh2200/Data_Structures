#ifndef AGENDA_H_INCLUDED
#define AGENDA_H_INCLUDED
#define TAMANIO_ASUNTO 100
#define TAMANIO_TIPO 1
#define TAMANIO_FECHA 10
#define TAMANIO_HORA 5
#define MAX_RECORDATORIOS 5
using namespace std;

class Agenda{
    char asunto[TAMANIO_ASUNTO+1];
    char tipo[TAMANIO_TIPO+1];
    char fecha[TAMANIO_FECHA+1];
    char hora[TAMANIO_HORA+1];










public:
    Agenda(char*asunto,char* tipo,char* fecha,char* hora){
        fijaAsunto(asunto);
        fijaTipo(tipo);
        fijaFecha(fecha);
        fijaHora(hora);
    }
    bool fijaAsunto(char* a){
        if (strlen(a)>0 && strlen(a)<TAMANIO_ASUNTO){
            strcpy(this->asunto,a);
            return true;
        }
        else{
            return false;
        }
    }
    bool fijaTipo(char* t){
        if (strlen(t)>0 && strlen(t)<TAMANIO_TIPO){
            strcpy(this->tipo,t);
            return true;
        }
        else{
            return false;
        }
    }

    bool fijaFecha(char* f){
        if (strlen(f)>0 && strlen(f)<TAMANIO_FECHA){
            strcpy(this->fecha,f);
            return true;
        }
        else{
            return false;
        }
    }

    bool fijaHora(char* h){
        if (strlen(h)>0 && strlen(h)<TAMANIO_FECHA){
            strcpy(this->hora,h);
            return true;
        }
        else{
            return false;
        }
    }
    char* dameAsunto(){
        return asunto;
    }
    char* dameTipo(){
        return tipo;
    }
    char* dameFecha(){
        return fecha;
    }
    char* dameHora(){
        return hora;
    }
};


#endif // AGENDA_H_INCLUDED
