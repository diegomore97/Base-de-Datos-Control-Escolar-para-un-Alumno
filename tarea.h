#ifndef TAREA_H_INCLUDED

#define TAREA_H_INCLUDED
#define TOTAL_TAREAS_ABC 3
#define NOMBRE_ARCHIVO_TAREAS "tareas.txt"
#include <iostream>

using namespace std;

void solicitarMemoriaTarea();
int cuentaTareas;

class Tarea
{
private:

    string asunto;
    string descripcion;
    string materia;
    bool estado;

public:

    Tarea(string materia,string descripcion,string asunto,bool estado)
    {
        if(!fijaAsunto(asunto))
        {
            this->asunto="Hacer ejercicios";
        }
        if(!fijaDescripcion(descripcion))
        {
            this->descripcion="Descripcion por defecto";

        }
        if(!fijaMateria(materia))
        {
            this->materia="Matematicas";
        }
        if(!fijaEstado(estado))
        {
            this->estado=true;
        }

    }

    ~Tarea()
    {

    }

    bool fijaAsunto(string asunto)
    {
        if(asunto.length()>1)
        {
            this->asunto=asunto;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool fijaDescripcion(string descripcion)
    {
        if(descripcion.length()>1)
        {
            this->descripcion=descripcion;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool fijaMateria(string materia)
    {
        if(materia.length()>1)
        {
            this->materia=materia;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool fijaEstado(bool estado)
    {
        this->estado=estado;
        return true;
    }

    string dameAsunto()
    {
        return asunto;
    }

    string dameDescripcion()
    {
        return descripcion;
    }

    string dameMateria()
    {
        return materia;
    }

    bool dameEstado()
    {
        return estado;
    }

};

Tarea** tareas=new Tarea *[TOTAL_TAREAS_ABC];
Tarea** temporal;

void solicitarMemoriaTarea()
{
    int i;
    temporal=new Tarea*[cuentaTareas+1];
    for(i=0; i<cuentaTareas; i++)
    {
        temporal[i]=tareas[i];
    }
    delete[] tareas;
    tareas=temporal;
}

#endif
