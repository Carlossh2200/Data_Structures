#ifndef ADMINISTRADOR_NOTA_H_INCLUDED
#define ADMINISTRADOR_NOTA_H_INCLUDED
#include "util.h"
#include "Bloc_Notas.h"
#define MAX_NOTAS 5
#define C_1 1
#define C_0 0
#define NOMBRE_ARCHIVO_NOTA "BlocNotas.dat"
vector<Nota*> blocNotas;
int notasLeidas;
int cuentaNotas;
class AdminNota{
public:
    void agregarNota();
    void mostrarDetallesNota();
    void mostrarNotaCompleta(const vector<Nota*>& blocNotas,int i);
    void listarNotas();
    void mostrarNota(const vector<Nota*>& blocNotas,int i);
    void modificarNota();
    void eliminarNota();
    void escribirNota(ofstream& file,Nota* n);
    void escribirNotas();
    void imprimirNota(Nota* n);
    void imprimirNotas();
    void borrarBlocNotas();
    Nota* leerNota(ifstream& file);
    int contarNotasEscritas(ifstream& file);
    void leerNotas();














};

void AdminNota::agregarNota(){
    char descripcion[TAMANIO_NOTA+1];
    if (cuentaNotas<MAX_NOTAS){
        cout << "Dame la descripcion de la nota (hasta 70 caracteres): ";
        cin.getline(descripcion,TAMANIO_NOTA);
        blocNotas.push_back(new Nota(descripcion));
        cuentaNotas++;
    }
    else{
        cout << "No hay más espacio para captura..." << endl;
    }
    pausar();
}

void AdminNota::mostrarNota(const vector<Nota*>& blocNotas,int i){
    printf("%d %.10s\n",i+C_1,blocNotas[i]->dameDescripcion());
}

void AdminNota::listarNotas(){
    using iter = vector<Nota*>::const_iterator;
    for(iter i =blocNotas.begin();i!=blocNotas.end();i++){
        cout << (*i)->dameDescripcion() << endl;
    }
    pausar();
}

void AdminNota::mostrarNotaCompleta(const vector<Nota*>& blocNotas,int i){
    cout << blocNotas[i]->dameDescripcion() << endl;
    pausar();
}

void AdminNota::mostrarDetallesNota(){
    int opcion;
    listarNotas();
    if (cuentaNotas>0){
        cout << endl << "Que nota quieres mostrar a detalle? (1 a " << cuentaNotas << "): ";
        cin >> opcion;
        opcion--;
        mostrarNotaCompleta(blocNotas,opcion);
    }
    else{
        cout << "No hay notas que mostrar..." << endl;
        pausar();
    }
}

void AdminNota::modificarNota(){
    char nuevaDescripcion[TAMANIO_NOTA+C_1];
    int opcion;
    if (cuentaNotas>C_0){
        listarNotas();
        cout << endl << "Qué nota quieres modificar? (1 a " << cuentaNotas << "): ";
        cin >> opcion;
        opcion--;
        cout << "Dame la nueva descripcion para esa nota: ";
        cin.getline(nuevaDescripcion,TAMANIO_NOTA);
        blocNotas[opcion]->fijaDescripcion(nuevaDescripcion);
        cout << "Nota modificada con exito!" << endl;
    }
    else{
        cout << "No hay notas que modificar..." << endl;
    }
    pausar();
}

void AdminNota::eliminarNota(){
    int notaAEliminar;
    if (cuentaNotas>C_0){
        listarNotas();
        cout << "Qué nota quieres eliminar> (1 a " << cuentaNotas << "): ";
        cin >> notaAEliminar;
        notaAEliminar--;
        delete blocNotas[notaAEliminar];
        blocNotas.erase(blocNotas.begin()+notaAEliminar);
        cuentaNotas--;
    }
    else{
        cout << "No hay notas para borrar..." << endl;
    }
    pausar();
}

void AdminNota::escribirNota(ofstream& file,Nota* n){
    cout << "Guardando una nota" << endl;
    file.write((char*)n,sizeof(Nota));
}

void AdminNota::escribirNotas(){
    ofstream file;
    file.open(NOMBRE_ARCHIVO_NOTA,ios::trunc | ios::binary);
    if (file.is_open()){
        for(int i=0;i<MAX_NOTAS&&i<cuentaNotas;i++){
            escribirNota(file,blocNotas[i]);
        }
        file.close();
    }
    else{
        cout << "Error al guardar notas" << endl;
    }
    pausar();
}

void AdminNota::borrarBlocNotas(){
    cout << "Borrando todas las notas del Bloc de Notas" << endl;
    while(!blocNotas.empty()){
        delete blocNotas[0];
        blocNotas.erase(blocNotas.begin());
    }
}

Nota* AdminNota::leerNota(ifstream& file){
    Nota* n=new Nota((char*)"");
    cout << "leyendo nota" << endl;
    file.read((char*)n,sizeof(Nota));
    return n;
}

int AdminNota::contarNotasEscritas(ifstream& file){
    int notasEscritas;
    file.seekg(0,ios_base::end);
    notasEscritas=file.tellg()/sizeof(Nota);
    file.seekg(0,ios_base::beg);
    cout << "Notas escritas: " << notasEscritas << endl;
    cuentaNotas=notasEscritas;
    return notasEscritas;
}

void AdminNota::leerNotas(){
    ifstream file;
    int i;
    cout << "Leyendo Bloc de Notas" << endl;
    file.open(NOMBRE_ARCHIVO_NOTA,ios::binary);
    if (file.is_open()){
        for(i=0,notasLeidas=contarNotasEscritas(file);i<MAX_NOTAS&&i<notasLeidas;i++){
            blocNotas.push_back(leerNota(file));
        }
        file.close();
    }
    else{
        cout << "Hubo un error leyendo Bloc de Notas o no hay datos guardados..." << endl;
    }
    pausar();
}

#endif // ADMINISTRADOR_NOTA_H_INCLUDED
