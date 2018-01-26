#ifndef MENUNOTA_H_INCLUDED
#define MENUNOTA_H
#include "AdminNotas.h"

enum {ALTA=1,LISTAR,MOSTRAR,BUSCAR,MODIFICAR,ELIMINAR,GUARDAR,REGRESAR};

class MenuNota
{
    AdminNotas *adminNotas;

public:

    MenuNota()
    {
        adminNotas=new AdminNotas();
    }

    ~MenuNota()
    {
        adminNotas->~AdminNotas();
    }

    void buscarNota()
    {
        cout<<"***BUSCAR NOTA***"<<endl<<endl;
        fflush(stdin);
        string buscaNota;

        cout<<"Ingresa alguna palabra de la nota que estas buscando: ";
        getline(cin,buscaNota);

        cout<<endl<<"Se han encontrado "<<adminNotas->buscarNota(buscaNota)<<" coincidencias.";
    }


    int opcionesMenuNota()
    {
        int opcion;
        fflush(stdin);
        cout<<"1. Agregar nota"<<endl;
        cout<<"2. Listar notas"<<endl;
        cout<<"3. Mostrar detalles de una nota"<<endl;
        cout<<"4. Buscar Nota"<<endl;
        cout<<"5. Modificar una nota"<<endl;
        cout<<"6. Eliminar nota"<<endl;
        cout<<"7. Guardar cambios"<<endl;
        cout<<"8. Regresar al menu anterior"<<endl<<endl;
        cout<<"Opcion: ";
        cin>>opcion;
        if (opcion>=ALTA && opcion<=GUARDAR)
        {
            system(CLEAR);
        }
        return opcion;
    }

    void altaNota()
    {
        cout<<"***DAR DE ALTA UNA NOTA***"<<endl<<endl;
        string descripcion;
        fflush(stdin);
        cout<<"Ingresa la descripcion de la Nota: ";
        getline(cin,descripcion);


        if(adminNotas->agregarNota(descripcion))
        {
            cout<<endl<<endl<<"El registro se dio de alta correctamente!";
        }
    }


    void mostrarDetallesNota()
    {
        int opcion;
        fflush(stdin);
        cout<<"***MOSTRAR DETALLES DE UNA NOTA***"<<endl<<endl;
        if(adminNotas->listarNotas())
        {
            cout<<"Ingresa el numero de nota del que quieras consultar detalles: ";
            cin>>opcion;
            if(adminNotas->notaTieneDatos(--opcion))
            {
                cout<<adminNotas->dameInfo(opcion);
                cout<<endl<<endl;
            }
        }
    }

    void modificarNota()
    {
        fflush(stdin);
        int opcion;
        string descripcion;
        cout<<"***MODIFICAR NOTA***"<<endl<<endl;
        if(adminNotas->listarNotas())
        {
            cout<<"Ingresa el numero de nota que deseas modificar: ";
            cin>>opcion;
            if(adminNotas->notaTieneDatos(--opcion))
            {
                cout<<adminNotas->dameInfo(opcion);
                cout<<endl<<endl;
                cout<<"Ingresa los nuevos datos"<<endl;
                cout<<"-------------------------------------------------------------"<<endl<<endl;
                fflush(stdin);
                cout<<"Ingresa la nueva descripcion de la nota: ";
                getline(cin,descripcion);
                adminNotas->modificarNota(descripcion,opcion);
                cout<<endl<<endl<<"Se ha modificado correctamente el registro!";
            }
        }
    }

    void bajaNota()
    {
        fflush(stdin);
        int i;
        char respuesta;
        int opcion;
        cout<<"***DAR DE BAJA UNA NOTA***"<<endl<<endl;
        if(adminNotas->listarNotas())
        {
            cout<<"Ingresa el numero de registro que deseas eliminar: ";
            cin>>opcion;

            if(adminNotas->notaTieneDatos(--opcion))
            {
                i=opcion;
                fflush(stdin);
                cout<<adminNotas->dameInfo(opcion);
                cout<<endl<<endl;
                cout<<"Deseas dar de baja esta nota (s/n): ";
                cin>>respuesta;
                while(respuesta!='s'&&respuesta!='n')
                {
                    fflush(stdin);
                    cout<<endl<<"Respuesta no valida!"<<endl;
                    cout<<"Deseas dar de baja esta nota: ";
                    cin>>respuesta;

                }
                switch(respuesta)
                {
                case 's':
                    adminNotas->eliminarNota(i);
                    cout<<endl<<endl<<"Registro eliminado!";
                    break;
                case 'n':
                    cout<<endl<<endl<<"Registro conservado!";
                    break;
                default:
                    break;
                }
            }
        }
    }

    void controlNotas()
    {
        adminNotas->cargarNotas();
        int opcion;
        do
        {
            opcion=opcionesMenuNota();
            switch(opcion)
            {
            case ALTA:
                altaNota();
                break;
            case LISTAR:
                adminNotas->listarNotas();
                break;
            case MOSTRAR:
                mostrarDetallesNota();
                break;
            case BUSCAR:
                buscarNota();
                break;

            case MODIFICAR:
                modificarNota();
                break;

            case ELIMINAR:
                bajaNota();
                break;

            case GUARDAR:
                adminNotas->guardarNotas();
                break;

            case REGRESAR:
                delete adminNotas;
                break;

            default:
                cout<<"Opcion no valida!";
                break;
            }

            pausar();
            system(CLEAR);
        }
        while(opcion!=REGRESAR);
    }

};

#endif // MENUNOTA_H_INCLUDE
