#ifndef RECORDATORIO_H_INCLUDED
#define RECORDATORIO_H_INCLUDED
#include <iostream>
#define TOTAL_RECORDATORIOS 3
#define NOMBRE_ARCHIVO_RECORDATORIO "recordatorios.txt"
using namespace std;

void solicitarMemoriaRecordatorio();
int cuentaRecordatorios;

class Recordatorio
{
private:
    string asunto;
    char tipoRecordatorio;
    string fecha;
    string hora;
    bool estado;

public:
    Recordatorio(string asunto,char tipoRecordatorio,string fecha,string hora,bool estado)
    {

        if(!fijaAsunto(asunto))
        {
            this->asunto="Recordatorio";
        }
        if(!fijaTipoRecordatorio(tipoRecordatorio))
        {
            this->tipoRecordatorio='a';
        }
        if(!fijaFecha(fecha))
        {
            this->fecha="4 de Noviembre del 2017";
        }
        if(!fijaHora(hora))
        {
            this->hora="5:30";
        }
        if(!fijaEstado(estado))
        {
            this->estado=true;
        }
    }

    ~Recordatorio()
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

    bool fijaTipoRecordatorio(char tipoRecordatorio)
    {
        this->tipoRecordatorio=tipoRecordatorio;
        return true;
    }

    bool fijaFecha(string fecha)
    {
        if(fecha.length()>1)
        {
            this->fecha=fecha;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool fijaHora(string hora)
    {
        if(hora.length()>1)
        {
            this->hora=hora;
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

    string dameFecha()
    {
        return fecha;
    }

    string dameHora()
    {
        return hora;
    }

    char dameTipoRecordatorio ()
    {
        return tipoRecordatorio;
    }

    bool dameEstado()
    {
        return estado;
    }

};

Recordatorio** recordatorios=new Recordatorio*[TOTAL_RECORDATORIOS];
Recordatorio** auxiliar;

void solicitarMemoriaRecordatorio()
{
    int i;
    auxiliar=new Recordatorio*[cuentaRecordatorios+1];
    for(i=0; i<cuentaRecordatorios; i++)
    {
        auxiliar[i]=recordatorios[i];
    }

    delete [] recordatorios;
    recordatorios=auxiliar;
}

#endif // RECORDATORIO_H_INCLUDED
