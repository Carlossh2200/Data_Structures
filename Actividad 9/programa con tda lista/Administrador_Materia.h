#ifndef ADMINISTRADOR_MATERIA_H_INCLUDED
#define ADMINISTRADOR_MATERIA_H_INCLUDED
#include "util.h"
#include "Materia.h"
#include "TDA_Lista_Arreglos.h"
#define C_0 0
#define C_1 1
#define NOMBRE_ARCHIVO_MATERIA "Actividad 9.txt"
#define DELIMITADOR_CAMPOS '|'
#define DELIMITADOR_REGISTROS '&'

ListaMateria listaMaterias;
ofstream archivoMat;
class AdminMateria{
public:
    void gestionMaterias();
    void agregarMateria();
    void capturaDatosMateria(string* nombre,string* acronimo,string* profesor,string* dias,int*
                             horaInicio,int* horaFin);
    void imprimeMateria(int i);
    void listarMateria();
    void mostrarDetallesMateria();
    void modificarMateria();
    void eliminarMateria();
    void modificarMateriaCompleta(int opcion);
    void purgarLista(ListaMateria& listaMaterias);
    void guardarEnArchivo();
};











void AdminMateria::capturaDatosMateria(string* nombre,string* acronimo,string* profesor,string* dias,int*
                         horaInicio,int* horaFin)
{
    cout << "Dame el nombre de la materia: ";
    getline(cin, *nombre);
    cout << "Dame el acronimo de la materia: ";
    getline(cin, *acronimo);
    cout << "Dame el nombre del profesor: ";
    getline(cin, *profesor);
    cout << "Dame los dias en que se imparte la materia: ";
    getline(cin, *dias);
    cout << "Dame la hora de inicio de clase: ";
    cin >> *horaInicio;
    cin.get();
    cout << "Dame la hora de fin de clase: ";
    cin >> *horaFin;
    cin.get();
}

void AdminMateria::agregarMateria()
{
    string nombre,acronimo,profesor,dias;
    int horaInicio,horaFin;
    if (!listaMaterias.estaLlena()){
        capturaDatosMateria(&nombre,&acronimo,&profesor,&dias,&horaInicio,&horaFin);
        Materia* materia=new Materia(nombre,acronimo,profesor,dias,horaInicio,horaFin);
        listaMaterias.inserta(materia,listaMaterias.fin());
    }
    else{
        cout << "No hay mas espacio para capturar materias" << endl;
    }
}

void AdminMateria::listarMateria(){
    posicion p,q;
    tipo_elemento materias;
    int i;
    if (!listaMaterias.estaVacia()){
        for(i=1,p=listaMaterias.primero(),q=listaMaterias.fin();p!=q;p=listaMaterias.siguiente(p),
        i++){
        materias=listaMaterias.recupera(p);
        cout << i << " ";
        cout << "Nombre de la materia: " << materias->dameNombre() << endl;
        cout << " Acrónimo:             " << materias->dameAcronimo() << endl;
        cout << " Profesor:             " << materias->dameNombreProfesor() << endl;
    }
    }
    else{
        cout << "no hay elementos que mostrar..." << endl;
    }
    pausar();
}

void AdminMateria::imprimeMateria(posicion p){
    tipo_elemento materias=listaMaterias.recupera(p);
    cout << "Nombre de la materia: " << materias->dameNombre() << endl;
    cout << "Acrónimo:             " << materias->dameAcronimo() << endl;
    cout << "Profesor:             " << materias->dameNombreProfesor() << endl;
    cout << "Dias:                 " << materias->dameDias() <<endl;
    cout << "Hora Inicio:          " << materias->dameHoraInicio() << endl;
    cout << "Hora Fin:          " << materias->dameHoraFin() << endl;
}

void AdminMateria::mostrarDetallesMateria(){
    int i;
    posicion p;
    i=listaMaterias.dameCuenta();
    if (!listaMaterias.estaVacia()){
        listarMateria();
        cout << "Indica el registro a mostrar 1 a (" << i <<") :";
        cin >> p;
        cin.ignore();
        p--;
        imprimeMateria(p);
    }
    else{
        cout << "No hay registros que mostrar..." << endl;
    }
    pausar();
}

void AdminMateria::modificarMateria(){
    int opcion;
    if (!listaMaterias.estaVacia()){
        listarMateria();
        cout << "Dime el número de registro que quieres modificar (1 a " <<
        listaMaterias.dameCuenta() << ") :";
        cin >> opcion;
        opcion--;
        cin.get();
        modificarMateriaCompleta(opcion);
    }
    else{
        cout << "No hay materias para modificar..." << endl;
    }
    pausar();
}

void AdminMateria::modificarMateriaCompleta(int opcion){
    posicion p;
    p=opcion;
    string nombre,acronimo,profesor,dias;
    int horaInicio,horaFin;
    capturaDatosMateria(&nombre,&acronimo,&profesor,&dias,&horaInicio,&horaFin);
    listaMaterias.suprime(p);
    Materia* materia=new Materia(nombre,acronimo,profesor,dias,horaInicio,horaFin);
    listaMaterias.inserta(materia,p);

}

void AdminMateria::eliminarMateria(){
    int elementoARemover,i;
    posicion p,q;
    cout << "Baja de materia\n";
    if (!listaMaterias.estaVacia()){
        listarMateria();
        cout << "Dime cual ingreso deseas remover (1 a " <<listaMaterias.dameCuenta() << "): ";
        cin >> elementoARemover;
        cin.ignore();
        for(i=1,p=listaMaterias.primero(),q=listaMaterias.fin();i<elementoARemover && p!=q;i++,
        p=listaMaterias.siguiente(p)){}
            if (p!=q&&elementoARemover>0){
                listaMaterias.suprime(p);
                cout << "Registro dado de baja" << endl;
            }
            else{
                cout << elementoARemover << " esta fuera del rango solicitado" << endl;
            }
    }
    else{
        cout << "No hay ingresos" << endl;
    }
    pausar();
    pausar();
}

bool ListaMateria::mismo(tipo_elemento x,tipo_elemento y){
    return x->dameNombre()==y->dameNombre();
}

void AdminMateria::purgarLista(ListaMateria& listaMaterias){
    posicion p,q;
    p=listaMaterias.primero();
    while(p!=listaMaterias.fin()){
        q=listaMaterias.siguiente(p);
        while(q!=listaMaterias.fin()){
            if (listaMaterias.mismo(listaMaterias.recupera(p),listaMaterias.recupera(q))){
                listaMaterias.suprime(q);
            }
            else{
                q=listaMaterias.siguiente(p);
            }
        }
        p=listaMaterias.siguiente(p);
    }
}

void AdminMateria::guardarEnArchivo(){
    archivoMat.open(NOMBRE_ARCHIVO_MATERIA);
    tipo_elemento materias;
    if (archivoMat.is_open()){
        if (!listaMaterias.estaVacia()){
            archivoMat << listaMaterias.dameCuenta() << DELIMITADOR_REGISTROS;
            for(int i=C_0;i<listaMaterias.dameCuenta();i++){
            materias=listaMaterias.recupera(i);
            archivoMat
            << i+C_1 << DELIMITADOR_CAMPOS
            << materias->dameNombre() << DELIMITADOR_CAMPOS
            << materias->dameAcronimo() << DELIMITADOR_CAMPOS
            << materias->dameNombreProfesor() << DELIMITADOR_CAMPOS
            << materias->dameDias() << DELIMITADOR_CAMPOS
            << materias->dameHoraInicio() << DELIMITADOR_CAMPOS
            << materias->dameHoraFin() << DELIMITADOR_REGISTROS;
        }
    }
    archivoMat.close();
    }
    else{
        cout << "No hay registros que listar..." << endl;
    }
    cout << "Archivo guardado con éxito!" << endl;
    pausar();
}

#endif // ADMINISTRADOR_MATERIA_H_INCLUDED
