#ifndef CALCULO_H_INCLUDED
#define CALCULO_H_INCLUDED
#include <iostream>

#define VALOR_TAREAS 7
#define VALOR_ACTIVIDADES 63
#define VALOR_EXAMENES 30
#define TOTAL_TAREAS 10
#define PORCENTAJE_ASISTENCIA_MINIMA_AL_CURSO 80
#define PORCENTAJE_CAL_MAXIMA 100
#define PORCENTAJE_CAL_MINIMA 60
#define TOTAL_ACTIVIDADES 9
#define TOTAL_EXAMENES 3
#define TOTAL_ASISTENCIA 34
#define TOTAL_RETARDOS 3
#define CIEN 100



#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

using namespace std;

void ingresarDatosMateria();
void evaluadorCurso();
void pausar();
void imprimirTitulo();

class Registro
{
    string nombre;
    string acronimo;
    string dias;
    int horaInicio;
    int horaFin;
public:
    Registro(string nombre, string acronimo,string dias,int horaInicio,int horaFin)
    {
        if(!fijaNombre(nombre))
        {
            this->nombre="Matematicas";
        }

        if(!fijaAcronimo(acronimo))
        {
            this->acronimo="mat";
        }

        if(!fijaDias(dias))
        {
            this->dias="L-M";
        }

        if(!fijaHorario(horaInicio,horaFin))
        {
            this->horaInicio=1;
            this->horaFin=3;
        }
    }

    ~Registro()
    {

    }

    bool fijaNombre(string nombre)
    {
        if(nombre.length()>1)
        {
            this->nombre=nombre;
            return true;
        }
        else
        {
            return false;
        }

    }
    bool fijaAcronimo(string acronimo)
    {
        if(acronimo.length()>1)
        {
            this->acronimo=acronimo;
            return true;
        }
        else
        {
            return false;
        }

    }
    bool fijaDias(string dias)
    {
        if(dias.length()>1)
        {
            this->dias=dias;
            return true;
        }
        else
        {
            return false;
        }

    }
    bool fijaHorario(int horaInicio,int horaFin)
    {
        if(horaInicio>0&&horaFin>0)
        {
            this->horaInicio=horaInicio;
            this->horaFin=horaFin;
            return true;
        }
        else
        {
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

Registro *materia;

void ingresarDatosMateria()
{
    string nombre,acronimo,dias;
    int horaInicio,horaFin;
    fflush(stdin);
    cout<<"Nombre de materia: ";
    getline(cin,nombre);
    fflush(stdin);
    cout<<"Acronimo: ";
    getline(cin,acronimo);
    fflush(stdin);
    cout<<"Dias de la semana: ";
    getline(cin,dias);
    fflush(stdin);
    cout<<"Hora de inicio: ";
    cin>>horaInicio;
    fflush(stdin);
    cout<<"Hora Final: ";
    cin>>horaFin;

    materia=new Registro(nombre,acronimo,dias,horaInicio,horaFin);
    pausar();
    system(CLEAR);
}

void evaluadorCurso()
{
    float sumatoriaActividad=0,sumatoriaExamen=0,calificacionFinal;
    float porcentajeAsistencia,porcentajeExamen,porcentajeTarea,porcentajeActividad;
    int i,faltaRetardo,tarea,falta,retardo,totalAsistencia;
    int actividades[TOTAL_ACTIVIDADES];
    int examenes[TOTAL_EXAMENES];
    bool aprobado,derecho;

    fflush(stdin);
    cout<<"Cuantas faltas acumulaste?: ";
    cin>>falta;
    fflush(stdin);
    cout<<"Cuantos retardos acumulaste?: ";
    cin>>retardo;
    fflush(stdin);
    cout<<"Cuantas tareas hiciste?: ";
    cin>>tarea;

    for(i=0; i<TOTAL_ACTIVIDADES; i++)
    {
        cout<<"Cuanto obtuviste en la actividad "<<i+1<<" ?: ";
        cin>>actividades[i];
        sumatoriaActividad+=actividades[i];
    }
    cout<<endl;
    for (i=0; i<TOTAL_EXAMENES; i++)
    {
        cout<<"Cuanto obtuviste en el "<<i+1<<" examen parcial?: ";
        cin>>examenes[i];
        sumatoriaExamen+=examenes[i];
    }
    cout<<endl;
    faltaRetardo=retardo/TOTAL_RETARDOS;
    totalAsistencia=TOTAL_ASISTENCIA-falta-faltaRetardo;
    porcentajeAsistencia=(totalAsistencia*CIEN)/TOTAL_ASISTENCIA;

    porcentajeTarea=(tarea*CIEN)/TOTAL_TAREAS;
    porcentajeTarea=(porcentajeTarea*VALOR_TAREAS)/CIEN;

    porcentajeActividad=sumatoriaActividad/TOTAL_ACTIVIDADES;
    porcentajeActividad=(porcentajeActividad*VALOR_ACTIVIDADES)/CIEN;

    porcentajeExamen=sumatoriaExamen/TOTAL_EXAMENES;
    porcentajeExamen=(porcentajeExamen*VALOR_EXAMENES)/CIEN;

    calificacionFinal=porcentajeActividad+porcentajeExamen+porcentajeTarea;

    if(calificacionFinal>=PORCENTAJE_CAL_MINIMA&&calificacionFinal<=PORCENTAJE_CAL_MAXIMA)
    {
        aprobado=true;
    }
    else
    {
        aprobado=false;
    }
    if(porcentajeAsistencia>=PORCENTAJE_ASISTENCIA_MINIMA_AL_CURSO)
    {
        derecho=true;
    }
    else
    {
        derecho=false;
    }


    cout<<"Tareas";
    cout<<"\tActividades " ;
    cout<<"\tExamenes \n";
    cout<<porcentajeTarea<<"\t\t"<<porcentajeActividad<<"\t"<<porcentajeExamen;
    cout<<"\nTotal de asistencias =     " <<totalAsistencia;
    cout<<"\nPorcentaje de asistencias= " <<porcentajeAsistencia;
    derecho? cout<<"\t\tTiene derecho":cout<<"\t\tNo tiene derecho";
    cout<<"\nCalificacion final=        " <<calificacionFinal;
    aprobado? cout<<"\t\tCalificacion aprobatoria"<<endl:cout<<"\t\tCalificacion no aprobatoria";
    cout<<endl;
    aprobado? cout<<"\nAlumno aprobado"<<endl: cout<<"\nAlumno no aprobado"<<endl;

    pausar();
}

void pausar()
{
    fflush(stdin);
    cout<<endl<<endl<<"Presiona enter para continuar...";
    cin.ignore();
    fflush(stdin);
}

void imprimirTitulo()
{
    cout<<"Evaluador de materias v1.0 - ";
    cout<<materia->dameNombre()<<"  ("<<materia->dameAcronimo()<<")  "<<materia->dameDias()<<"  "
        <<materia->dameHoraInicio()<<" a "<<materia->dameHoraFin()<<endl;
}

#endif // CALCULO_H_INCLUDED
