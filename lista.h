#ifndef LISTA_H
#define LISTA_H
#define TOTAL_ELEMENTOS 3
#include "nota.h"

typedef int posicion;
typedef Nota tipoElemento;


const posicion POSICION_imprimeError=-1;

class Lista
{
    posicion ult;
    tipoElemento** lista;


public:
    Lista()
    {
        lista=new tipoElemento*[TOTAL_ELEMENTOS];
        ult=-1;
    }
    ~Lista()
    {
        for(int i=0; i<fin(); i++)
        {
            delete lista[i];
        }

        delete [] lista;
    }
    bool inserta(tipoElemento *x, posicion p);
    bool suprime(posicion p);
    bool imprimeLista();

    posicion siguiente(posicion p);
    posicion anterior(posicion p);
    posicion primero();
    posicion ultimo();
    posicion localiza(tipoElemento* x);
    posicion fin();
    tipoElemento* recupera(posicion p);

    bool estaVacia();
    bool estaLlena();

    string imprimeElemento(tipoElemento* x);
    bool mismo(tipoElemento *x,tipoElemento *y);
    void imprimeError(string info);
};

posicion Lista::fin()
{
    return ult+1;
}
posicion Lista::anterior(posicion p)
{
    return p-1;
}

posicion Lista::siguiente(posicion p)
{
    return p+1;
}

bool Lista::estaVacia()
{
    return ult<0;
}

bool Lista::estaLlena()
{
    return fin()>=TOTAL_ELEMENTOS;
}

posicion Lista::ultimo()
{
    if(estaVacia())
    {
        return POSICION_imprimeError;
    }
    else
    {
        return anterior(fin());
    }
}

posicion Lista::primero()
{
    return 0;
}

bool Lista::mismo(tipoElemento *x,tipoElemento *y)
{
    if(x->dameDescripcion()==y->dameDescripcion())
    {
        return true;
    }

    else
    {
        return false;
    }

}

tipoElemento* Lista::recupera(posicion p)
{
    return (lista[p]);
}

void Lista::imprimeError(string imprimeError)
{
    cout<<endl<<imprimeError<<endl;
}

posicion Lista::localiza(tipoElemento *x)
{
    posicion p,q;
    for(p=primero(),q=fin(); p!=q; p=siguiente(p))
    {
        if(mismo(lista[p],x))
        {
            break;
        }
    }
    return p;
}

bool Lista::imprimeLista()
{
    posicion p,q;
    if(estaVacia())
    {
        imprimeError("No hay ningun elemento registrado!");
        return false;
    }
    else
    {
        cout<<"    Registro\t\tDescripcion\t"<<endl;
        for(p=primero(),q=fin(); p!=q; p=siguiente(p))
        {
            cout<<"\t"<<p+1<<"\t\t";
            cout<<imprimeElemento(recupera(p));
            cout <<endl<<endl;
        }

        return true;
    }
}

string Lista::imprimeElemento(tipoElemento* x)
{
    return x->dameDescripcion();
}

bool Lista::inserta(tipoElemento *x, posicion p)
{
    bool insertado=false;
    posicion q;

    if ((p<primero()) || (p>fin()))
    {
        imprimeError("La posicion a insertar no existe");
    }
    else
    {
        if(estaLlena()&&p==fin())
        {

            Nota**aumentarVector=new Nota*[fin()+1];

            for(p=primero(),q=fin(); p!=q; p=siguiente(p))
            {
                aumentarVector[p]=lista[p];
            }

            delete [] lista;
            lista=aumentarVector;
        }

        if(p==fin())
        {
            for(q=ult; q>=p; q--)
            {
                lista[q+1]=lista[q];
            }
            ult++;
        }

        lista[p]=x;
        insertado=true;
    }
    return insertado;
}
bool Lista:: suprime(posicion p)
{
    posicion q,r;
    if ((p<primero()) || (p>fin()))
    {
        imprimeError("La posicion a suprimir no existe");
        return false;
    }
    else
    {
        --ult;
        r=ult;
        for(q=p; q<=r; q++)
        {
            lista[q]=lista[q+1];
        }
        return true;
    }
}

#endif
