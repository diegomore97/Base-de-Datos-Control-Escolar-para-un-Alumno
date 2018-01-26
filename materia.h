#ifndef MATERIA_H_INCLUDED
#define MATERIA_H_INCLUDED
#include <iostream>
#define TOTAL_MATERIAS 3
#define NOMBRE_ARCHIVO_MATERIAS "materias.txt"

using namespace std;

void solicitarMemoriaMateria();
int cuentaMaterias;


class Materia
{
    string nombre;
    string acronimo;
    string dias;
    int horaInicio,horaFin;
    bool estado;

public:

    Materia(string nombre,string acronimo,string dias,int horaInicio,int horaFin,bool estado)
    {
        if(!fijaNombre(nombre))
        {
            this->nombre="Matematicas (Materia por defecto)";
        }
        if(!fijaAcronimo(acronimo))
        {
            this->acronimo="Mat";
        }
        if(!fijaDias(dias))
        {
            this->dias="L-M";
        }
        if(!fijaHorario(horaInicio,horaFin))
        {
            this->horaInicio=12;
            this->horaFin=1;
        }
        if(!fijaEstado(estado))
        {
            this->estado=true;
        }
    }

    ~Materia()
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
        if(dias.length()>0)
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
        if(horaInicio>0&&horaInicio<=24&&horaFin>0&&horaFin<=24)
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
    bool fijaEstado (bool estado)
    {
        this->estado=estado;
        return true;
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
    bool dameEstado()
    {
        return estado;
    }
};

Materia** materias=new Materia *[TOTAL_MATERIAS];
Materia** temp;

void solicitarMemoriaMateria()
{
    int i;
    temp=new Materia*[cuentaMaterias+1];
    for(i=0; i<cuentaMaterias; i++)
    {
        temp[i]=materias[i];
    }
    delete[] materias;
    materias=temp;
}

#endif

