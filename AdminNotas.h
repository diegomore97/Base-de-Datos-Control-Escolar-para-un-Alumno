#ifndef ADMINNOTAS_H_INCLUDED
#define ADMINNOTAS_H
#include "nota.h"
#include "lista.h"
#include <sstream>

class AdminNotas
{
    Lista *adminLista;

public:

    AdminNotas()
    {
        adminLista=new Lista();
    }

    ~AdminNotas()
    {
        delete adminLista;
    }

    bool agregarNota(string descripcion)
    {

        if(adminLista->inserta(new Nota(descripcion),adminLista->fin()))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int dameCuentaNotas()
    {
        return adminLista->fin();
    }


    bool eliminarNota(int posicion)
    {
        if(adminLista->suprime(posicion))
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    void modificarNota(string descripcion,int posicion)
    {
        adminLista->inserta(new Nota(descripcion),posicion);
    }

    string dameInfo(int posicion)
    {
        return adminLista->imprimeElemento(adminLista->recupera(posicion));
    }

    bool listarNotas()
    {
        int i;

        if(!adminLista->estaVacia())
        {
            cout<<"    Registro\t\tDescripcion\t"<<endl;
            for(i=adminLista->primero(); i<adminLista->fin(); i=adminLista->siguiente(i))
            {
                cout<<"\t"<<i+1<<"\t\t";
                cout<<adminLista->imprimeElemento(adminLista->recupera(i));
                cout<<endl<<endl;
            }
            cout<<endl<<endl;
            return true;
        }
        else
        {
            adminLista->imprimeError("No hay ninguna Nota registrada!");
            return false;
        }
    }

    int buscarNota(string descripcion)
    {
        int coincidencias=0;
        int i;

        for(i=adminLista->primero(); i!=adminLista->fin(); i=adminLista->siguiente(i))
        {

            if(adminLista->imprimeElemento(adminLista->recupera(i)).find(descripcion)!=string::npos)
            {
                cout<<adminLista->imprimeElemento(adminLista->recupera(i));
                cout<<endl<<endl;
                coincidencias++;
            }
        }

        return coincidencias;
    }


    void guardarNotas()
    {
        int i;
        ofstream escritura;
        escritura.open(NOMBRE_ARCHIVO_NOTA,ios::out);
        cout<<"Guardar Registros en un archivo de texto!"<<endl<<endl;

        if(escritura.is_open())
        {
            for(i=adminLista->primero(); i!=adminLista->fin(); i=adminLista->siguiente(i))
            {
                escritura<<adminLista->imprimeElemento(adminLista->recupera(i))<<endl;
            }

            cout<<endl<<endl<<"Se han guardado correctamente los registros!";
        }

        else
        {
            adminLista->imprimeError("No se pudo leer el archivo!\n");
        }

        escritura.close();
    }

    bool notaTieneDatos(int i)
    {
        if(i>=0&&i<dameCuentaNotas())
        {
            return true;
        }

        else
        {
            adminLista->imprimeError("No existe ese registro!\n");
            return false;
        }
    }

    void cargarNotas()
    {
        ifstream lectura;
        string descripcion;
        lectura.open(NOMBRE_ARCHIVO_NOTA,ios::in);

        if(lectura.is_open())
        {
            getline(lectura,descripcion);
            while(!lectura.eof())
            {
                agregarNota(descripcion);
                getline(lectura,descripcion);
            }

            cout<<"Se han cargado "<<adminLista->fin()<<" notas!";
        }

        else
        {
            adminLista->imprimeError("No se pudo leer el archivo!");
        }

        lectura.close();
        pausar();
        system(CLEAR);
    }


};

#endif // ADMINNOTAS_H_INCLUDED
