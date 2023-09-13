#ifndef MATERIA_H_INCLUDED
#define MATERIA_H_INCLUDED
#define NOMBRE_POR_DEFECTO "Estructuras de Datos"
#define ACRONIMO_POR_DEFECTO "EDA"
#define PROFESOR_POR_DEFECTO "Luis Munoz"
#define DIAS_POR_DEFECTO "LMV"
#define C_0 0
using namespace std;

class Materia{
    static constexpr int HORA_INICIO_DEFECTO=9;
    static constexpr int HORA_FIN_DEFECTO=11;
    string nombre;
    string acronimo;
    string profesor;
    string dias;
    int horaInicio;
    int horaFin;
public:
    Materia(string nombre,string acronimo,string profesor,string dias,int horaInicio,int horaFin)
    {
        /*nombre=NOMBRE_POR_DEFECTO;
        acronimo=ACRONIMO_POR_DEFECTO;
        profesor=PROFESOR_POR_DEFECTO;
        dias=DIAS_POR_DEFECTO;
        horaInicio=HORA_INICIO_DEFECTO;
        horaFin=HORA_FIN_DEFECTO;*/
        fijaNombre(nombre);
        fijaAcronimo(acronimo);
        fijaProfesor(profesor);
        fijaDias(dias);
        fijaHoraInicio(horaInicio);
        fijaHoraFin(horaFin);
    }
    bool fijaNombre(string n)
    {
        if (n.length()>C_0){
            nombre=n;
            return true;
        }
        else{
            return false;
        }
    }
    bool fijaAcronimo(string a)
    {
        if (a.length()>C_0){
            acronimo=a;
            return true;
        }
        else{
            return false;
        }
    }
    bool fijaProfesor(string p)
    {
        if (p.length()>C_0){
            profesor=p;
            return true;
        }
        else{
            return false;
        }
    }
    bool fijaDias(string d)
    {
        if (d.length()>C_0){
            dias=d;
            return true;
        }
        else{
            return false;
        }
    }
    bool fijaHoraInicio(int h)
    {
        if (h>C_0){
            horaInicio=h;
            return true;
        }
        else{
            return false;
        }
    }
    bool fijaHoraFin(int h)
    {
        if (h>C_0){
            horaFin=h;
            return true;
        }
        else{
            return false;
        }
    }
    string dameNombre()
    {
        return nombre;
    }
    string dameAcronimo()
    {
        return acronimo;
    }
    string dameNombreProfesor()
    {
        return profesor;
    }
    string dameDias()
    {
        return dias;
    }
    int dameHoraInicio()
    {
        return horaInicio;
    }
    int dameHoraFin()
    {
        return horaFin;
    }
};

typedef Materia* tipo_elemento;
#define ELEMENTOS_POR_DEFECTO 0
#define MAX_MATERIAS 3
#define ELEMENTO_NO_EXISTE -1

#endif // MATERIA_H_INCLUDED
