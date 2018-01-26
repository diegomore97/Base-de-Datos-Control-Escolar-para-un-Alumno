#ifndef NOTA_H_INCLUDED
#define NOTA_H_INCLUDED
#include <iostream>
#define TOTAL_NOTAS 3
#define NOMBRE_ARCHIVO_NOTA "notas.txt"
using namespace std;

class Nota
{
private:
    string descripcion;

public:

    Nota(string descripcion)
    {
        if(!fijaDescripcion(descripcion))
        {
            this->descripcion="descripcion";
        }
    }

    ~Nota()
    {

    }

    string dameDescripcion()
    {
        return descripcion;
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
};

#endif // NOTA_H_INCLUDED
