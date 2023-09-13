//CuatroCero
//Actividad 9
//Tiempo=02:00
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <locale.h>
#include "Materia.h"
#include "TDA_Lista_Arreglos.h"
#include "Evaluacion.h"
#include "Tarea.h"
#include "Agenda.h"
#include "Bloc_Notas.h"
#include "Administrador_Nota.h"
#include "Administrador_Materia.h"
#include "util.h"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif // _WIN32
using namespace std;

#define NOMBRE_ARCHIVO "Actividad 9.dat"
#define NOMBRE_ARCHIVO_AGENDA "Agenda.dat"
#define DELIMITADOR_CAMPOS '|'
#define DELIMITADOR_REGISTROS '&'
#define PORCENTAJE_TAREAS 7
#define PORCENTAJE_ACTIVIDADES 63
#define PORCENTAJE_EXAMENES 30
#define TOTAL_ASISTENCIAS 34
#define RETARDOS_POR_FALTA 3
#define TOTAL_TAREAS 10
#define TOTAL_ACTIVIDADES 9
#define TOTAL_EXAMENES 3
#define MINIMO_ASISTENCIA 80
#define MINIMA_CALIF 60
#define MINIMO_PORCENTAJE_ASISTENCIA 28.8
#define C_0 0
#define C_1 1
#define C_2 2
#define C_3 3
#define C_100 100
#define C_300 300
#define C_900 900
#define TEXTO_1 "primer"
#define TEXTO_2 "segundo"
#define TEXTO_3 "tercer"
#define MAX_TAREAS_INICIAL 3
#define TAMANIO_ASUNTO 100
#define TAMANIO_TIPO 1
#define TAMANIO_FECHA 10
#define TAMANIO_HORA 5
#define MAX_RECORDATORIOS 5

enum {EVALUACION_CURSO=C_1,GESTION_MATERIAS,CONTROL_TAREAS,CONTROL_AGENDA,CONTROL_NOTA,SALIR};
enum {AGREGAR_MATERIA=C_1,LISTAR_MATERIA,MOSTRAR_DETALLES,MODIFICAR_MATERIA,ELIMINAR_MATERIA,
      GUARDAR,REGRESAR};
enum{MODIF_MATERIA=C_1,MODIF_NOMBRE,MODIF_ACRONIMO,MODIF_NOMBRE_PROFESOR,MODIF_DIAS,
MODIF_HORA_INICIO,MODIF_HORA_FIN,SALIR_MODIFICAR};
enum{AGREGAR_TAREA=C_1,LISTAR_TAREA,MOSTRAR_TAREA,MODIFICAR_TAREA,ELIMINAR_TAREA,GUARDAR_TAREA,
MENU_ANTERIOR};
enum{MODIFICAR_TAREA_COMPLETA=C_1,MODIFICAR_ASUNTO_TAREA,MODIFICAR_DESC_TAREA,
MODIFICAR_MATERIA_TAREA,SALIR_MODIFICAR_TAREA};
enum{AGREGAR_RECORDATORIO=C_1,LISTAR_RECORDATORIOS,MOSTRAR_DETALLE_RECORDATORIO,
MODIFICAR_RECORDATORIO,ELIMINAR_RECORDATORIO,GUARDAR_RECORDATORIOS,SALIR_AGENDA};
enum{AGREGAR_NOTA=C_1,LISTAR_NOTAS,MOSTRAR_DETALLE_NOTA,MODIFICAR_NOTA,ELIMINAR_NOTA,GUARDAR_NOTAS,
SALIR_MENU_NOTAS};

int cuentaRegistros;
int cuentaTareas;
int cuentaRecordatorios;
int registrosLeidos;


//Materia* materias[MAX_MATERIAS];
AdminMateria adminMateria;
Tarea** tareas;
Agenda* recordatorios[MAX_RECORDATORIOS];
AdminNota agenda;
int maxTareas=MAX_TAREAS_INICIAL;
stringstream reporteRegistro;
string reporteRegistroStr;

int menu();
int menuGestionMateria();
void pausar();
bool cargarDatos();
void limpiarPantalla();
void gestionMaterias();
void evaluacionCurso();
void controlTareas();
int menuControlTarea();
void agregarTarea();
void capturaDatosTarea(string* asunto,string* descripcion,string* materia);
void imprimeTarea(int i);
void listarTareas();
void mostrarTarea();
void modificarTarea();
int menuModificarTarea();
void modificarTareaCompleta(int i);
void modificarAsuntoTarea(int i);
void modificarDescripcionTarea(int i);
void modificarMateraTarea(int i);
void eliminarTarea();

void escribirRecordatorio(ofstream& file,Agenda* a);
void escribirRecordatorios();
Agenda* leerRecordatorio(ifstream& file);
int contarRegistrosEscritos(ifstream& file);
void leerRecordatorios();
void imprimirRecordatorio(Agenda* a);
void imprimirRecordatorios();
void borrarAgenda();
void agregarRecordatorio();
void administradorAgenda();
int menuAgenda();
void mostrarRecordatorio(int i);
void mostrarAsunto(int i);
void listarRecordatorios();
void eliminarRecordatorio();
void listarAgenda();


int menuNota();
void administradorNotas();
void agregarNota();
void mostrarDetallesNota();
void mostrarNotaCompleta(const vector<Nota*>& blocNotas,int i);
void listarNotas(const vector<Nota*>& blocNotas);
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
void leerNotas(vector<Nota*>& blocNotas);




















int main()
{
    setlocale(LC_ALL, "");
    bool seguirEjecutandoPrograma=true;
    leerRecordatorios();
    agenda.leerNotas();
    do
    {
        system(CLEAR);
        switch(menu())
        {
        case EVALUACION_CURSO:
            evaluacionCurso();
            break;
        case GESTION_MATERIAS:
            gestionMaterias();
            break;
        case CONTROL_TAREAS:
            controlTareas();
            break;
        case CONTROL_AGENDA:
            administradorAgenda();
            break;
        case CONTROL_NOTA:
            administradorNotas();
            break;
        case SALIR:
            cout << "Haz salido del programa..." << endl;
            seguirEjecutandoPrograma=false;
            break;
        default:
            cout << "Opción no válida..." << endl;
            pausar();
        }
    }while(seguirEjecutandoPrograma);
    agenda.borrarBlocNotas();
    delete[] tareas;
    return 0;
}

int menu()
{
    int opcion;
    cout << "ACTIVIDAD 5" << endl << endl;
    cout << "1. Evaluación del curso" << endl;
    cout << "2. Gestión de Materias" << endl;
    cout << "3. Control de Tareas" << endl;
    cout << "4. Agenda" << endl;
    cout << "5. Bloc de Notas" << endl;
    cout << "6. Salir" << endl;
    cout << "Opción: ";
    cin >> opcion;
    cin.get();
    return opcion;
}

int menuGestionMateria()
{
    int opcion;
    cout << "Gestión de materias" << endl << endl;
    cout << "1. Agregar materia" << endl;
    cout << "2. Listar materias" << endl;
    cout << "3. Mostrar detalles de una materia" << endl;
    cout << "4. Modificar una materia" << endl;
    cout << "5. Eliminar una materia" << endl;
    cout << "6. Guardar cambios" << endl;
    cout << "7. Regresar al menu anterior" << endl;
    cout << "Opción: ";
    cin >> opcion;
    cin.get();
    return opcion;
}

void evaluacionCurso()
{
    MateriaEvaluacion materia;
    //Declaracion de variables (a usar para entrada de datos)
    short cantidadFalta,cantidadRetardo,cantidadTarea,calificacionActividades[TOTAL_ACTIVIDADES],
          calificacionExamenes[TOTAL_EXAMENES];
    //Declaracion de variables (a usar para computos)
    float porcentajeActividad,porcentajeExamen,calificacionFinal,
          asistencias,auxiliarAsistencia,porcentajeAsistencia,auxiliarActividad,
          acumuladorActividad=C_0,auxiliarExamen,acumuladorExamen=C_0,porcentajeTareas;
    string calificacionAprobatoria;
    string textoExamen[TOTAL_EXAMENES];
    textoExamen[C_0]=TEXTO_1;
    textoExamen[C_1]=TEXTO_2;
    textoExamen[C_2]=TEXTO_3;
    //Entrada de datos
    cout << "Dame el nombre de la materia a evaluar: ";
    getline(cin, materia.nombre);
    cout << "Dame el acronimo de la materia: ";
    cin >> materia.acronimo;
    cin.get();
    cout << "Dame los dias de la semana en que se imparte la materia: ";
    cin >> materia.diasSemana;
    cin.get();
    cout << "Dame la hora de inicio de la clase: ";
    cin >> materia.horaInicio;
    cin.get();
    cout << "Dame la hora de fin de la clase: ";
    cin >> materia.HoraFinalizacion;
    cin.get();
    cout << "Presione entrar para continuar..." << endl;
    cin.get();
    cout << "Cuántas faltas tuviste en el curso? ";
    cin >> cantidadFalta;
    cin.get();
    cout << "Cuántos retardos tuviste en el curso? ";
    cin >> cantidadRetardo;
    cin.get();
    cout << "Cuántas tareas realizaste? ";
    cin >> cantidadTarea;
    cin.get();
    for(int i=C_0; i<TOTAL_ACTIVIDADES; i++)
    {
        cout << "Cuánto obtuviste en la actividad #" << i+C_1 << "? ";
        cin >> calificacionActividades[i];
    }
    for(int i=C_0; i<TOTAL_EXAMENES; i++)
    {
        cout << "Cuánto obtuviste en el " << textoExamen[i] << " examen parcial? ";
        cin >> calificacionExamenes[i];
    }
    for(int i=C_0; i<TOTAL_ACTIVIDADES; i++)
    {
        acumuladorActividad+=calificacionActividades[i];
    }
    for(int i=C_0; i<TOTAL_EXAMENES; i++)
    {
        acumuladorExamen+=calificacionExamenes[i];
    }
    //Computo de actividades
    auxiliarActividad=(acumuladorActividad*C_100)/C_900;
    porcentajeActividad=(auxiliarActividad*PORCENTAJE_ACTIVIDADES)/C_100;
    //Computo de examenes parciales
    auxiliarExamen=(acumuladorExamen*C_100)/C_300;
    porcentajeExamen=(auxiliarExamen*PORCENTAJE_EXAMENES)/C_100;
    //Computo de asistencias
    auxiliarAsistencia=cantidadRetardo%C_3;
    asistencias=TOTAL_ASISTENCIAS-auxiliarAsistencia-cantidadFalta;
    porcentajeAsistencia=(asistencias*C_100)/TOTAL_ASISTENCIAS;
    //Computo de tareas
    porcentajeTareas=(cantidadTarea*PORCENTAJE_TAREAS)/TOTAL_TAREAS;
    //Computo de puntos finales
    calificacionFinal=porcentajeTareas+porcentajeActividad+porcentajeExamen;
    calificacionAprobatoria= (calificacionFinal>=MINIMA_CALIF) ? "Calificación aprobatoria" :
                             "Calificación no aprobatoria";
    //Salida de datos
    cout << "Presiona entrar para continuar..." << endl;
    cin.get();
    system(CLEAR);
    cout << "Evaludador de curso v1.0 - " << materia.nombre << " (" << materia.acronimo <<") " <<
         materia.diasSemana << " " << materia.horaInicio << "-" << materia.HoraFinalizacion <<
         endl << endl;
    cout << "Tareas    Actividades    Examenes" << endl;
    cout << " " <<porcentajeTareas << "       " << porcentajeActividad << "          "
         << porcentajeExamen << endl;
    cout << "Total de asistencias=        " << asistencias << endl;
    cout << "Porcentaje de asistencias=   " << porcentajeAsistencia;
    if (asistencias>=MINIMO_PORCENTAJE_ASISTENCIA)
    {
        cout << " Tiene derecho" << endl;
    }
    else
    {
        cout << " NO tiene derecho" << endl;
    }
    cout << "Calificación Final=          " << calificacionFinal << "  " << calificacionAprobatoria;
    if (asistencias>=MINIMO_PORCENTAJE_ASISTENCIA && calificacionFinal>=MINIMA_CALIF)
    {
        cout << endl << "Alumn@ aprobado!" << endl;
    }
    else
    {
        cout << endl << "Alumn@ no aprobado." << endl;
    }
    cout << "Presione entrar para terminar..." << endl;
    cin.get();
}

void gestionMaterias()
{
    bool seguirEjecutandoModulo=true;
    do
    {
        system(CLEAR);
        switch(menuGestionMateria())
        {
        case AGREGAR_MATERIA:
            adminMateria.agregarMateria();
            break;
        case LISTAR_MATERIA:
            adminMateria.listarMateria();
            break;
        case MOSTRAR_DETALLES:
            adminMateria.mostrarDetallesMateria();
            break;
        case MODIFICAR_MATERIA:
            adminMateria.modificarMateria();
            break;
        case ELIMINAR_MATERIA:
            adminMateria.eliminarMateria();
            break;
        case GUARDAR:
            adminMateria.guardarEnArchivo();
            break;
        case REGRESAR:
            seguirEjecutandoModulo=false;
            break;
        default:
            cout << "Opción no válida..." << endl;
        }
    }
    while(seguirEjecutandoModulo);
}

int menuControlTarea(){
    int opcion;
    cout << "1. Agregar tarea" << endl;
    cout << "2. Listar tareas" << endl;
    cout << "3. Mostrar detalles de una tarea" << endl;
    cout << "4. Modificar detalles de una tarea" << endl;
    cout << "5. Eliminar tarea" << endl;
    cout << "6. Guardar cambios" << endl;
    cout << "7. Regresar al menu anterior" << endl;
    cout << "Opcion: ";
    cin >> opcion;
    cin.get();
    return opcion;
}

void controlTareas(){
    tareas=new Tarea*[maxTareas];
    bool seguirEjecutandoModulo=true;
    do{
        system(CLEAR);
        switch(menuControlTarea()){
        case AGREGAR_TAREA:
            agregarTarea();
            break;
        case LISTAR_TAREA:
            listarTareas();
            break;
        case MOSTRAR_TAREA:
            mostrarTarea();
            break;
        case MODIFICAR_TAREA:
            modificarTarea();
            break;
        case ELIMINAR_TAREA:
            eliminarTarea();
            break;
        case GUARDAR_TAREA:
            cout << "En construccion" << endl;
            break;
        case MENU_ANTERIOR:
            seguirEjecutandoModulo=false;
            break;
        default:
            cout << "Opcion no valida..." << endl;
            pausar();
        }
    }while(seguirEjecutandoModulo);
}

void guardarTarea(){
    cout << "En construccion :) " << endl;
    pausar();
}

void capturaDatosTarea(string* asunto,string* descripcion,string* materia){
    cout << "Dame el asunto: ";
    getline(cin, *asunto);
    cout << "Dame la descripcion: ";
    getline(cin, *descripcion);
    cout << "Dame la materia: ";
    getline(cin, *materia);
}

void agregarTarea(){
    string asunto,descripcion,materia;
    Tarea** temp;
    cout << "ALTA DE TAREA" << endl;
    if (cuentaTareas==maxTareas){
        temp=new Tarea*[maxTareas=cuentaTareas+1];
        for(int i=C_0;i<cuentaTareas;i++){
            temp[i]=tareas[i];
        }
        delete[] tareas;
        tareas=temp;
    }
    capturaDatosTarea(&asunto,&descripcion,&materia);
    tareas[cuentaTareas]=new Tarea(asunto,descripcion,materia);
    cuentaTareas++;
}

void listarTareas(){
    if (cuentaTareas>0){
        for(int i=0;i<cuentaTareas;i++){
            imprimeTarea(i);
        }
    }
    else{
        cout << "No hay tareas que listar..." << endl;
    }
    pausar();
}

void imprimeTarea(int i){
    cout << "Registro " << i+C_1 << endl;
    cout << "Asunto: " << tareas[i]->dameAsunto() << endl;
    cout << "Descripcion: " << tareas[i]->dameDescripcion() << endl;
    cout << "Materia: " << tareas[i]->dameMateria() << endl << endl;
}

void mostrarTarea(){
    int opcion;
    if (cuentaTareas>C_0){
        cout << "MOSTRAR TAREA" << endl;
        cout << "Que registro quieres ver? (1 a " << cuentaTareas << ") :";
        cin >> opcion;
        opcion--;
        cin.get();
        imprimeTarea(opcion);
    }
    pausar();
}

void modificarTarea(){
    bool seguirEjecutandoModulo=true;
    int opcion;
    if (cuentaTareas>C_0){
        listarTareas();
        cout << endl << "¿Qué registro quieres modificar? (1 a " << cuentaTareas << ") :";
        cin >> opcion;
        opcion--;
        cin.get();
        do
        {
            switch(menuModificarTarea()){
            case MODIFICAR_TAREA_COMPLETA:
                modificarTareaCompleta(opcion);
                break;
            case MODIFICAR_ASUNTO_TAREA:
                modificarAsuntoTarea(opcion);
                break;
            case MODIFICAR_DESC_TAREA:
                modificarDescripcionTarea(opcion);
                break;
            case MODIFICAR_MATERIA_TAREA:
                modificarMateraTarea(opcion);
                break;
            case SALIR_MODIFICAR_TAREA:
                cout << "Haz salido del menu modificar tarea..." << endl;
                pausar();
                seguirEjecutandoModulo=false;
                break;
            default:
                cout << "Opcion no valida..." << endl;
            }
        }
        while(seguirEjecutandoModulo);
    }
}

int menuModificarTarea(){
    int opcionMenu;
    cout << "MENU PARA MODIFICAR TAREA " << endl;
    cout << "1) Modificar tarea completa" << endl;
    cout << "2) Modificar asunto de la tarea" << endl;
    cout << "3) Modificar descripcion de la tarea" << endl;
    cout << "4) Modificar materia a la que pertenece la tarea" << endl;
    cout << "5) Salir del menu modificar" << endl;
    cout << "Opción: ";
    cin >> opcionMenu;
    cin.get();
    return opcionMenu;
}

void modificarTareaCompleta(int i){
    string nuevoAsunto,nuevaDescripcion,nuevaMateria;
    cout << "Dame el asunto de la tarea: ";
    getline(cin, nuevoAsunto);
    cout << "Dame la nueva descripcion de la tarea: ";
    getline(cin, nuevaDescripcion);
    cout << "Dame la nueva materia a la que pertenece esta materia: ";
    getline(cin,nuevaMateria);
    tareas[i]->fijaAsunto(nuevoAsunto);
    tareas[i]->fijaDescripcion(nuevaDescripcion);
    tareas[i]->fijaMateria(nuevaMateria);
    cout << "¡Registro modificado con exito!" << endl;
    pausar();
}

void modificarAsuntoTarea(int i){
    string nuevoAsunto;
    cout << "Dame el asunto modificado para esta tarea: ";
    getline(cin, nuevoAsunto);
    tareas[i]->fijaAsunto(nuevoAsunto);
    cout << "¡Asunto modificado con éxito!" << endl;
    pausar();
}

void modificarDescripcionTarea(int i){
    string nuevaDescripcion;
    cout << "Dame la nueva descripcion para esta tarea: ";
    getline(cin, nuevaDescripcion);
    tareas[i]->fijaDescripcion(nuevaDescripcion);
    cout << "¡Descripcion modificada con éxito!"<< endl;
    pausar();
}

void modificarMateraTarea(int i){
    string nuevaTarea;
    cout << "Dame la nueva materia para esta tarea: ";
    getline(cin, nuevaTarea);
    tareas[i]->fijaMateria(nuevaTarea);
    cout << "¡Materia modificada con éxito!" << endl;
    pausar();
}

void eliminarTarea(){
    int i;
    if (cuentaTareas>C_0){
    listarTareas();
    cout << "¿Qué registro quieres eliminar (1 a " << cuentaTareas << ") :";
    cin >> i;
    i--;
    cin.get();
    delete tareas[i];
    for(cuentaTareas--;i<cuentaRegistros;i++){
        tareas[i]=tareas[i+C_1];
    }
    cout << "Registro eliminado con éxito." << endl;
    }
    else{
        cout << "No hay tareas que borrar" << endl;
    }
    pausar();
}


void administradorAgenda(){
    bool seguirEjecutandoModulo=true;
    do{
        system(CLEAR);
        switch(menuAgenda()){
        case AGREGAR_RECORDATORIO:
            agregarRecordatorio();
            pausar();
            break;
        case LISTAR_RECORDATORIOS:
            listarAgenda();
            pausar();
            break;
        case MOSTRAR_DETALLE_RECORDATORIO:
            listarRecordatorios();
            pausar();
            break;
        case ELIMINAR_RECORDATORIO:
            eliminarRecordatorio();
            pausar();
            break;
        case GUARDAR_RECORDATORIOS:
            escribirRecordatorios();
            pausar();
            break;
        case SALIR_AGENDA:
            seguirEjecutandoModulo=false;
            break;
        default:
            cout << "Opcion no valida..." << endl;
        }
    }while(seguirEjecutandoModulo);
}


void eliminarRecordatorio(){
    int i;
    if (cuentaRecordatorios>C_0){
        listarRecordatorios();
        cout << "Que registro quieres eliminar (1 a " << cuentaRecordatorios << ") " << endl;
        cin >> i;
        i--;
        recordatorios[i]=nullptr;
        for(cuentaRecordatorios--;i<cuentaRecordatorios;i++){
            recordatorios[i]=recordatorios[i+C_1];
        }
        cout << "Hecho." << endl;
    }
    else{
        cout << "No hay recordatorios que borrar" << endl;
    }
}

void listarAgenda(){
    if (cuentaRecordatorios>C_0){
        for(int i=0;i<cuentaRecordatorios;i++){
            cout << i+C_1 << " ";
            mostrarRecordatorio(i);
        }
    }
    else{
        cout << "no hay recordatorios que listar" << endl;
    }
}

void listarRecordatorios(){
    int opcion;
    if (cuentaRecordatorios>C_0){
        for(int i=0;i<cuentaRecordatorios;i++){
            cout << i+C_1 << " ";
            mostrarAsunto(i);
        }
        cout << "cual recordatorio quieres ver? ";
        cin >> opcion;
        opcion--;
        mostrarRecordatorio(opcion);
    }
    else{
        cout << "no hay recordatorios que listar" << endl;
    }
}

void mostrarAsunto(int i){
    cout << "Asunto: " << recordatorios[i]->dameAsunto() << endl;
}

void mostrarRecordatorio(int i){
    cout << "Asunto: " << recordatorios[i]->dameAsunto() << endl;
    cout << "Tipo:   " << recordatorios[i]->dameTipo() << endl;
    cout << "Fecha:  " << recordatorios[i]->dameFecha() << endl;
    cout << "Hora:   " << recordatorios[i]->dameHora() << endl;
}

int menuAgenda(){
    int opcion;
    cout << "1. Agregar recordatorio" << endl;
    cout << "2. Listar recordatorios" << endl;
    cout << "3. Mostrar detalles de un recordatorio" << endl;
    cout << "4. Modificar un recordatorio" << endl;
    cout << "5. Eliminar recordatorio" << endl;
    cout << "6. Guardar cambios" << endl;
    cout << "7. Regresar al menu anterior" << endl;
    cout << "Opcion: ";
    cin >> opcion;
    cin.get();
    return opcion;
}

void agregarRecordatorio(){
    char asunto[TAMANIO_ASUNTO+1];
    char tipo[TAMANIO_TIPO+1];
    char fecha[TAMANIO_FECHA+1];
    char hora[TAMANIO_HORA+1];
    cout << "AGREGAR RECORDATORIO" << endl;
    if (cuentaRecordatorios<MAX_RECORDATORIOS){
        cout << "Dame el asunto (hasta 100 caracteres): ";
        cin.getline(asunto,TAMANIO_ASUNTO);
        cout << "Dame el tipo: ";
        cin.getline(tipo,TAMANIO_ASUNTO);
        cout << "Dame la fecha: ";
        cin.getline(fecha,TAMANIO_FECHA);
        cout << "Dame la hora: ";
        cin.getline(hora,TAMANIO_HORA);
        recordatorios[cuentaRecordatorios]=new Agenda(asunto,tipo,fecha,hora);
        cuentaRecordatorios++;
    }
    else{
        cout << "No hay espacio para captura..." << endl;
    }

}

void escribirRecordatorio(ofstream& file,Agenda* a){
    int nbytes;
    cout << "Guardando un recordatorio" << endl;
    file.write((char*)a,nbytes=sizeof(Agenda));
    cout << "Se escribieron " << nbytes << " bytes" << endl;
}

void escribirRecordatorios(){
    ofstream file;
    file.open(NOMBRE_ARCHIVO_AGENDA,ios::trunc | ios::binary);
    if (file.is_open()){
        for(int i=0;i<MAX_RECORDATORIOS&&i<cuentaRecordatorios;i++){
            escribirRecordatorio(file,recordatorios[i]);
        }
        file.close();
    }
    else{
        cout << "Hubo error al guardar" << endl;
    }
}

void imprimirRecordatorio(Agenda* a){
    cout << "Asunto: " << a->dameAsunto() << endl;
    cout << "Tipo:   " << a->dameTipo() << endl;
    cout << "Fecha:  " << a->dameFecha() << endl;
    cout << "Hora:   " << a->dameHora() << endl;
}

void imprimirRecordatorios(){
    for(int i=0;i<MAX_RECORDATORIOS&&recordatorios[i];i++){
        imprimirRecordatorio(recordatorios[i]);
    }
}

void borrarAgenda(){
    cout << "Borrando agenda" << endl;
    for(int i=0;i<MAX_RECORDATORIOS&&recordatorios[i];i++){
        delete recordatorios[i];
    }
    pausar();
}

Agenda* leerRecordatorio(ifstream& file){
    Agenda* a=new Agenda((char*)"",(char*)"",(char*)"",(char*)"");
    cout << "leyendo registro " << endl;
    file.read((char*)a,sizeof(Agenda));
    return a;
}

int contarRegistrosEscritos(ifstream& file){
    int registrosEscritos;
    file.seekg(0,ios_base::end);
    registrosEscritos=file.tellg()/sizeof(Agenda);
    file.seekg(0,ios_base::beg);
    cout << "Registros escritos: " << registrosEscritos << endl;
    cuentaRecordatorios=registrosEscritos;
    return registrosEscritos;
}

void leerRecordatorios(){
    ifstream file;
    int i;
    cout << "Leyendo agenda" << endl;
    file.open(NOMBRE_ARCHIVO_AGENDA,ios::binary);
    if (file.is_open()){
        for(i=0,registrosLeidos=contarRegistrosEscritos(file);i<MAX_RECORDATORIOS&&
        i<registrosLeidos;i++){
            recordatorios[i]=leerRecordatorio(file);
        }
        file.close();
    }
    else{
        cout << "hubo un error leyendo agenda :(" << endl;
    }
    pausar();
}

int menuNota(){
    int opcion;
    cout << "BLOC DE NOTAS" << endl;
    cout << "1. Agregar nota" << endl;
    cout << "2. Listar notas" << endl;
    cout << "3. Mostrar detalles de una nota" << endl;
    cout << "4. Modificar una nota" << endl;
    cout << "5. Eliminar nota" << endl;
    cout << "6. Guardar cambios" << endl;
    cout << "7. Regresar al menú anterior" << endl;
    cout << "Opcion: ";
    cin >> opcion;
    cin.get();
    return opcion;
}

void administradorNotas(){
    bool seguirEjecutandoNota=true;
    do{
        system(CLEAR);
        switch(menuNota()){
    case AGREGAR_NOTA:
        agenda.agregarNota();
        break;
    case LISTAR_NOTAS:
        agenda.listarNotas();
        break;
    case MOSTRAR_DETALLE_NOTA:
        agenda.mostrarDetallesNota();
        break;
    case MODIFICAR_NOTA:
        agenda.modificarNota();
        break;
    case ELIMINAR_NOTA:
        agenda.eliminarNota();
        break;
    case GUARDAR_NOTAS:
        agenda.escribirNotas();
        break;
    case SALIR_MENU_NOTAS:
        seguirEjecutandoNota=false;
        break;
    default:
    cout << "Selección no valida..." << endl;
    }
    }while(seguirEjecutandoNota);
}

