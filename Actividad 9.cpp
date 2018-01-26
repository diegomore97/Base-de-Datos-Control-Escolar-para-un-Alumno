//CeroCuatro Actividad 9 Tiempo=01:30

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "calculo.h"
#include "materia.h"
#include "tarea.h"
#include "recordatorio.h"
#include "menuNota.h"


#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif // _WIN32


using namespace std;

enum {EVALUACION=1,GESTION_DE_MATERIAS,CONTROL_TAREAS,AGENDA,NOTA,SALIR};



void liberarMemoria();

int opcionesMenuPrincipal();

int opcionesMenuMateria();
bool materiaTieneDatos(int i);
void pedirDatosMateria(int i);
void mostrarMateria(int i);
void altaMateria();
void bajaMateria();
void listarMaterias();
void modificarMateria();
void mostrarDetallesMateria();
void controlMaterias();
void guardarRegistrosMaterias();
void cargarMaterias();
void buscarMateria();


void altaTarea();
void bajaTarea();
void listarTareas();
void modificarTarea();
void mostrarDetallesTarea();
void buscarTarea();
void pedirDatosTarea(int i);
void mostrarTarea(int i);
void guardarRegistrosTareas();
void cargarTareas();
bool tareaTieneDatos(int i);
void controlTareas();
int opcionMenuTarea();

void pedirDatosRecordatorio(int i);
void altaRecordatorio();
void mostrarRecordatorio(int i);
void modificarRecordatorio();
void listarRecordatorios();
bool recordatorioTieneDatos(int i);
void bajaRecordatorio();
void buscarRecordatorio();
void mostrarDetallesRecordatorio();
void guardarRegistrosRecordatorios();
void cargarRecordatorios();
int opcionMenuRecordatorio();
void controlRecordatorios();


void inicializar();
MenuNota *menuNota;

using namespace std;

int main()
{
    bool continuar=true;

    do
    {
        switch(opcionesMenuPrincipal())
        {
        case EVALUACION:
            evaluadorCurso();
            break;
        case GESTION_DE_MATERIAS:
            controlMaterias();
            break;
        case CONTROL_TAREAS:
            controlTareas();
            break;
        case AGENDA:
            controlRecordatorios();
            break;
        case NOTA:
            inicializar();
            menuNota->controlNotas();
            break;
        case SALIR:
            continuar=false;
            break;
        default:
            cout<<"Opcion invalida"<<endl;
        }
    }
    while(continuar);
    liberarMemoria();
    return 0;
}

void pedirDatosMateria(int i)
{
    string nombre,acronimo,dias;
    int horaInicio,horaFin;
    fflush(stdin);
    materias[i]=new Materia (nombre,acronimo,dias,horaInicio,horaFin,false);
    cout<<"Nombre de materia: ";
    getline(cin,nombre);
    fflush(stdin);
    while(!materias[i]->fijaNombre(nombre))
    {
        fflush(stdin);
        cout<<endl<<"Nombre no valido!"<<endl;
        cout<<"Nombre de materia: ";
        getline(cin,nombre);
    }
    cout<<"Acronimo: ";
    getline(cin,acronimo);
    fflush(stdin);
    while(!materias[i]->fijaAcronimo(acronimo))
    {
        fflush(stdin);
        cout<<endl<<"Acronimo no valido!"<<endl;
        cout<<"Acronimo: ";
        getline(cin,acronimo);
    }
    cout<<"Dias de la semana: ";
    getline(cin,dias);
    fflush(stdin);
    while(!materias[i]->fijaDias(dias))
    {
        fflush(stdin);
        cout<<endl<<"Dias no validos!"<<endl;
        cout<<"Dias de la semana: ";
        getline(cin,dias);
    }
    cout<<"Hora de inicio: ";
    cin>>horaInicio;
    fflush(stdin);
    cout<<"Hora Final: ";
    cin>>horaFin;
    while(!materias[i]->fijaHorario(horaInicio,horaFin))
    {
        fflush(stdin);
        cout<<endl<<"Horas no validas!"<<endl;
        cout<<"Hora Inicial: ";
        cin>>horaInicio;
        cout<<"Hora Final: ";
        cin>>horaFin;
    }


    materias[i]=new Materia (nombre,acronimo,dias,horaInicio,horaFin,false);

    cout<<endl<<endl<<"Registro completado!";
}

int opcionesMenuPrincipal()
{
    int opcion;
    system(CLEAR);
    cout<<"1. Evaluacion del Curso"<<endl;
    cout<<"2. Gestion de Materias "<<endl;
    cout<<"3. Control de Tareas"<<endl;
    cout<<"4. Agenda"<<endl;
    cout<<"5. Block de Notas"<<endl;
    cout<<"6. Salir "<<endl<<endl;
    cout <<"Opcion: ";
    cin>>opcion;
    if(opcion<=NOTA&&opcion>=EVALUACION)
    {
        system(CLEAR);
    }
    return opcion;
}


void liberarMemoria()
{
    for(int i=0; i<cuentaMaterias; i++)
    {

        delete materias[i];
    }

    for(int i=0; i<cuentaTareas; i++)
    {

        delete tareas[i];
    }

    for(int i=0; i<cuentaRecordatorios; i++)
    {
        delete recordatorios[i];
    }

    delete [] tareas;
    delete [] materias;
    delete [] recordatorios;
    menuNota->~MenuNota();

}

void mostrarMateria(int i)
{
    cout<<"Nombre: "<<materias[i]->dameNombre()<<endl;
    cout<<"Acronimo: "<<materias[i]->dameAcronimo()<<endl;
    cout<<"Dias: "<<materias[i]->dameDias()<<endl;
    cout<<"Horario: "<<materias[i]->dameHoraInicio()<<" a "<<materias[i]->dameHoraFin()<<endl;
}

bool materiaTieneDatos(int i)
{
    bool materiaTieneDatos;
    if(0<=i&&i<cuentaMaterias)
    {
        materiaTieneDatos=true;

    }
    else
    {
        cout<<"No existe ese registro"<<endl;
    }
    return materiaTieneDatos;
}

void altaMateria()
{
    if(cuentaMaterias<TOTAL_MATERIAS)
    {
        pedirDatosMateria(cuentaMaterias);
        cuentaMaterias++;
    }

    else
    {
        solicitarMemoriaMateria();
        pedirDatosMateria(cuentaMaterias);
        cuentaMaterias++;
    }

    cout<<endl<<endl<<"El registro se dio de alta correctamente!";
}

void bajaMateria()
{
    int i;
    char opcion;
    cout<<"***Baja de materia***"<<endl<<endl;
    listarMaterias();
    cout<<"Indica el numero de registro a eliminar: ";
    cin>>i;
    i--;
    cout<<endl;
    if (materiaTieneDatos(i))
    {
        mostrarMateria(i);
        cout << endl << "Deseas eliminar el registro (s/n)?";
        cin.ignore();
        cin >> opcion;
        if (opcion=='S' || opcion=='s')
        {
            for(cuentaMaterias--; i<cuentaMaterias; i++)
            {
                materias[i]=materias[i+1];
            }
            cout << "Registro eliminado!" << endl;
        }
        else
        {
            cout << "Registro conservado!" << endl;
        }
    }

}

void listarMaterias()
{
    int i;
    int registro=0;
    cout<<endl<<endl;
    cout<<"Registro\tMateria\t\tAcronimo"<<endl;
    for(i=0; i<cuentaMaterias; i++)
    {
        if(!materias[i]->dameEstado())
        {
            registro++;
            cout<<registro <<"\t\t";
            cout<<materias[i]->dameNombre()<<"\t";
            cout<<materias[i]->dameAcronimo()<<endl;
        }
    }

    cout<<endl<<endl;
}

void mostrarDetallesMateria()
{
    int i;
    cout<<"***Mostrar detalles***"<<endl<<endl;
    listarMaterias();
    cout<<"Indica el numero de registro a consultar: ";
    cin>>i;
    i--;
    cout<<endl;
    if (materiaTieneDatos(i))
    {
        mostrarMateria(i);
    }
}

void modificarMateria()
{
    int i;
    int datoModificar;
    string nombre,acronimo,dias;
    int horaInicio,horaFin;

    cout<<"***Cambio de datos***"<<endl<<endl;
    listarMaterias();
    cout<<"Ingresa el numero de registro que deseas modificar: ";
    cin>>i;
    i--;
    cout<<endl<<endl;
    if (materiaTieneDatos(i))
    {
        cout<<"1. Modificar todos los datos del registro"<<endl;
        cout<<"2. Nombre"<<endl;
        cout<<"3. Acronimo"<<endl;
        cout<<"4. Dias"<<endl;
        cout<<"5. Modificar Horario"<<endl<<endl;
        cout<<"Ingresa el Dato que deseas modificar: ";
        cin>>datoModificar;

        while(datoModificar!=1&&datoModificar!=2&&datoModificar!=3&&datoModificar!=4&&
                datoModificar!=5)
        {
            cout<<"opcion no valida!"<<endl<<endl;
            cout<<"1. Modificar todos los datos del registro"<<endl;
            cout<<"2. Nombre"<<endl;
            cout<<"3. Acronimo"<<endl;
            cout<<"4. Dias"<<endl;
            cout<<"5. Modificar Horario"<<endl<<endl;
            cout<<"Ingresa el Dato que deseas modificar: ";
            cin>>datoModificar;
        }
        cout<<endl;
        switch(datoModificar)
        {
        default:
            break;

        case 1:
            pedirDatosMateria(i);
            break;

        case 2:
            fflush(stdin);
            cout<<"Ingresa el Nombre: ";
            getline(cin,nombre);

            while(!materias[i]->fijaNombre(nombre))
            {
                fflush(stdin);
                cout<<endl<<"Nombre no valido!"<<endl;
                cout<<"Nombre de materia: ";
                getline(cin,nombre);
            }
            break;

        case 3:
            fflush(stdin);
            cout<<"Ingresa el Acronimo: ";
            getline(cin,acronimo);
            while(!materias[i]->fijaAcronimo(acronimo))
            {
                fflush(stdin);
                cout<<endl<<"Acronimo no valido!"<<endl;
                cout<<"Acronimo: ";
                getline(cin,acronimo);
            }
            break;

        case 4:
            fflush(stdin);
            cout<<"Ingresa los dias: ";
            getline(cin,dias);
            while(!materias[i]->fijaDias(dias))
            {
                fflush(stdin);
                cout<<endl<<"Dias no validos!"<<endl;
                cout<<"Dias de la semana: ";
                getline(cin,dias);
            }
            break;

        case 5:
            fflush(stdin);
            cout<<"Ingresa la hora de incio: ";
            cin>>horaInicio;
            cout<<"Ingresa la hora en la que finaliza la clase: ";
            cin>>horaFin;
            while(!materias[i]->fijaHorario(horaInicio,horaFin))
            {
                fflush(stdin);
                cout<<endl<<"Horas no validas!"<<endl;
                cout<<"Hora Inicial: ";
                cin>>horaInicio;
                cout<<"Hora Final: ";
                cin>>horaFin;
            }
            break;
        }

        cout<<"Registro Modificado Correctamente!";
    }
}

void buscarMateria()
{
    string buscarNombre;
    int i,encontrados;

    cout<<"***Busqueda***"<<endl<<endl;
    cout<<"Ingresa el nombre de la materia que deseas buscar: ";
    fflush(stdin);
    getline(cin,buscarNombre);
    encontrados=0;
    cout<<endl;
    for(i=0; i<cuentaMaterias; i++)
    {
        if (materias[i]->dameNombre().find(buscarNombre)!=string::npos)
        {
            mostrarMateria(i);
            cout<<endl<<endl;
            encontrados++;
        }
    }
    if (encontrados)
    {
        cout<<"Se encontro "<<encontrados<<" registro(s) con la palabra buscada"<<endl;
    }
    else
    {
        cout<<"No se encontro algun registro con la palabra buscada"<<endl;
    }

}

int opcionesMenuMateria()
{
    int opcion;

    system(CLEAR);
    cout<<"***REGISTRO DE MATERIAS***"<<endl<<endl;
    cout << "1. Agregar materia" << endl;
    cout << "2. Listar materias" << endl;
    cout << "3. Mostrar detalles de una materia" << endl;
    cout << "4. Buscar Materia"<<endl;
    cout << "5. Modificar una materia" << endl;
    cout << "6. Eliminar materia" << endl;
    cout << "7. Guardar cambios" << endl;
    cout << "8. Regresar al menu principal" << endl;
    cout << "Opcion: ";
    cin >> opcion;

    if (opcion>=ALTA && opcion<=GUARDAR)
    {
        system(CLEAR);
    }

    return opcion;
}

void controlMaterias()
{
    cargarMaterias();
    int opcion;

    do
    {
        opcion=opcionesMenuMateria();

        switch(opcion)
        {
        case ALTA:
            altaMateria();
            break;
        case LISTAR:
            listarMaterias();
            break;
        case MOSTRAR:
            mostrarDetallesMateria();
            break;
        case BUSCAR:
            buscarMateria();
            break;
        case MODIFICAR:
            modificarMateria();
            break;
        case ELIMINAR:
            bajaMateria();
            break;
        case GUARDAR:
            guardarRegistrosMaterias();
            break;
        case REGRESAR:
            cuentaMaterias=0;
            break;
        default:
            cout<<"Opcion no valida"<<endl;
        }

        pausar();
        system(CLEAR);
    }

    while(opcion!=REGRESAR);
}

void guardarRegistrosMaterias()
{
    ofstream escritura;
    int i;
    escritura.open(NOMBRE_ARCHIVO_MATERIAS,ios::out);

    if(escritura.is_open())
    {
        for(i=0; i<cuentaMaterias; i++)
        {
            if(!materias[i]->dameEstado())
            {
                escritura<<materias[i]->dameNombre()<<endl;
                escritura<<materias[i]->dameAcronimo()<<endl;
                escritura<<materias[i]->dameDias()<<endl;
                escritura<<materias[i]->dameHoraInicio()<<endl;
                escritura<<materias[i]->dameHoraFin()<<endl;
            }
        }

        cout<<"Se ha guardado correctamente!"<<endl;


    }
    else
    {
        cout<<"No se pudo leer el Archivo!";
    }

    escritura.close();
}

void cargarMaterias()
{
    int i=0;
    ifstream lectura;
    string nombre;
    string acronimo;
    string dias;
    string horaInicio,horaFin;
    lectura.open(NOMBRE_ARCHIVO_MATERIAS,ios::in);
    if(lectura.is_open())
    {
        getline(lectura,nombre);
        while(!lectura.eof())
        {
            getline(lectura,acronimo);
            getline(lectura,dias);
            getline(lectura,horaInicio);
            getline(lectura,horaFin);
            materias[i]=new Materia(nombre,acronimo,dias,atoi(horaInicio.c_str()),
                                    atoi(horaFin.c_str()),false);
            i++;
            cuentaMaterias++;
            getline(lectura,nombre);
        }

        if(cuentaMaterias==0)
        {
            cout<<"No hay ninguna materia registrada"<<endl<<endl;
        }

        else if(cuentaMaterias==1)
        {
            cout<<"Hay una sola materia registrada"<<endl<<endl;
        }

        else if(cuentaMaterias>1)
        {

            cout<<"Hay un total de "<<i<<" materias registradas"<<endl<<endl;
        }
    }
    else
    {
        cout<<"No se pudo leer el archivo!"<<endl<<endl;
    }
    lectura.close();
    pausar();
}

void pedirDatosTarea(int i)
{
    string asunto,descripcion,materia;
    fflush(stdin);
    tareas[i]=new Tarea(materia,descripcion,asunto,false);
    cout<<"Ingresa el asunto de la tarea: ";
    getline(cin,asunto);
    fflush(stdin);
    while(!tareas[i]->fijaAsunto(asunto))
    {
        fflush(stdin);
        cout<<endl<<"Asunto no valido!"<<endl;
        cout<<"Ingresa el asunto de la tarea: ";
        getline(cin,asunto);
    }
    cout<<"Ingresa la descripcion de la tarea: ";
    getline(cin,descripcion);
    fflush(stdin);
    while(!tareas[i]->fijaDescripcion(descripcion))
    {
        fflush(stdin);
        cout<<endl<<"Descripcion no valida!"<<endl;
        cout<<"Ingresa la descripcion de la tarea: ";
        getline(cin,descripcion);
    }
    cout<<"De que materia es la tarea?: ";
    getline(cin,materia);
    fflush(stdin);
    while(!tareas[i]->fijaMateria(materia))
    {
        fflush(stdin);
        cout<<endl<<"Materia no valida!"<<endl;
        cout<<"De que materia es la tarea?: ";
        getline(cin,materia);
    }

    tareas[i]=new Tarea(materia,descripcion,asunto,false);

}

void mostrarTarea(int i)
{
    cout<<"Asunto: "<<tareas[i]->dameAsunto()<<endl;
    cout<<"Descripcion: "<<tareas[i]->dameDescripcion()<<endl;
    cout<<"Materia: "<<tareas[i]->dameMateria()<<endl;
    cout<<endl<<endl;
}

void altaTarea()
{
    if(cuentaTareas<TOTAL_TAREAS_ABC)
    {
        pedirDatosTarea(cuentaTareas);
        cuentaTareas++;
    }

    else
    {
        solicitarMemoriaTarea();
        pedirDatosTarea(cuentaTareas);
        cuentaTareas++;
    }

    cout<<endl<<endl<<"El registro se dio de alta correctamente!";
}

void bajaTarea()
{
    int i;
    char respuesta;
    fflush(stdin);

    cout<<"***Eliminar Tarea***"<<endl<<endl;
    if(cuentaTareas>0)
    {
        listarTareas();
        cout<<"Ingresa el numero de registro que deseas eliminar: ";
        cin>>i;
        i--;
        cout<<endl<<endl;

        if(tareaTieneDatos(i))
        {
            mostrarTarea(i);
            fflush(stdin);
            cout<<"Deseas eliminar esta tarea (s/n): ";
            cin>>respuesta;
            if(respuesta=='S')
            {
                respuesta='s';
            }
            else if(respuesta=='N')
            {
                respuesta='n';
            }
            while(respuesta!='s'&&respuesta!='n')
            {
                cout<<"Opcion no valida!"<<endl<<endl;
                cout<<"Deseas eliminar esta tarea: (S/N)";
                cin>>respuesta;
                if(respuesta=='S')
                {
                    respuesta='s';
                }
                else if(respuesta=='N')
                {
                    respuesta='n';
                }
            }

            switch(respuesta)
            {
            default:
                break;

            case 's':
                for(cuentaTareas--; i<cuentaTareas; i++)
                {
                    tareas[i]=tareas[i+1];
                }
                cout<<"Registro Eliminado!";
                break;

            case 'n':
                cout<<"Registro conservado!";
                break;
            }
        }

    }

    else
    {
        cout<<"No hay ninguna Tarea Registrada";
    }
}

bool tareaTieneDatos(int i)
{
    bool tareaTieneDatos;
    if(0<=i&&i<cuentaTareas)
    {
        tareaTieneDatos=true;
    }
    else
    {
        cout<<"No existe ese registro"<<endl;
    }
    return tareaTieneDatos;
}

void modificarTarea()
{
    int i;
    int datoModificar;
    string materia,descripcion,asunto;
    fflush(stdin);

    cout<<"***Modificar Tarea***"<<endl<<endl;

    if(cuentaTareas>0)
    {
        listarTareas();
        cout<<"Ingresa el numero de registro que deseas modificar: ";
        cin>>i;
        i--;
        cout<<endl<<endl;

        if(tareaTieneDatos(i))
        {
            fflush(stdin);
            cout<<"1. Modificar todos los datos del registro"<<endl;
            cout<<"2. Materia"<<endl;
            cout<<"3. Asunto"<<endl;
            cout<<"4. Descripcion"<<endl<<endl;
            cout<<"Ingresa el Dato que deseas modificar: ";
            cin>>datoModificar;

            while(datoModificar!=1&&datoModificar!=2&&datoModificar!=3&&datoModificar!=4)
            {
                fflush(stdin);
                cout<<"Opcion no valida!"<<endl<<endl;
                cout<<"1. Modificar todos los datos del registro"<<endl;
                cout<<"2. Materia"<<endl;
                cout<<"3. Asunto"<<endl;
                cout<<"4. Descripcion"<<endl<<endl;
                cout<<"Ingresa el Dato que deseas modificar: ";
                cin>>datoModificar;
            }
            cout<<endl;
            switch(datoModificar)
            {
            default:
                break;

            case 1:
                pedirDatosTarea(i);
                break;

            case 2:
                fflush(stdin);
                cout<<"Ingresa la Materia: ";
                getline(cin,materia);
                while(!tareas[i]->fijaMateria(materia))
                {
                    fflush(stdin);
                    cout<<endl<<"Materia no valida!"<<endl;
                    cout<<"De que materia es la tarea?: ";
                    getline(cin,materia);
                }
                break;

            case 3:
                fflush(stdin);
                cout<<"Ingresa el asunto: ";
                getline(cin,asunto);
                while(!tareas[i]->fijaAsunto(asunto))
                {
                    fflush(stdin);
                    cout<<endl<<"Asunto no valido!"<<endl;
                    cout<<"Ingresa el asunto de la tarea: ";
                    getline(cin,asunto);
                }
                break;

            case 4:
                fflush(stdin);
                cout<<"Ingresa la Descripcion: ";
                getline(cin,descripcion);
                while(!tareas[i]->fijaDescripcion(descripcion))
                {
                    fflush(stdin);
                    cout<<endl<<"Descripcion no valida!"<<endl;
                    cout<<"Ingresa la descripcion de la tarea: ";
                    getline(cin,descripcion);
                }
                break;
            }

            cout<<"Registro Modificado Correctamente!";
        }

    }
    else
    {
        cout<<"No hay ninguna Tarea Registrada";
    }
}

void listarTareas()
{
    int i;
    int registro=0;
    cout<<endl<<endl;

    cout<<"Registro\tMateria\t\tAsunto"<<endl;
    for(i=0; i<cuentaTareas; i++)
    {
        if(!tareas[i]->dameEstado())
        {
            registro++;
            cout<<registro <<"\t\t";
            cout<<tareas[i]->dameMateria()<<"\t";
            cout<<tareas[i]->dameAsunto()<<endl;
        }
    }

    cout<<endl<<endl;
}

void mostrarDetallesTarea()
{
    int i;
    fflush(stdin);

    cout<<"***Mostrar Detalles de una Tarea***"<<endl<<endl;
    listarTareas();
    cout<<"Ingresa el numero de registro del que deseas consultar detalles: ";
    cin>>i;
    i--;
    cout<<endl<<endl;

    if(tareaTieneDatos(i))
    {
        mostrarTarea(i);
    }

}

void buscarTarea()
{
    string buscarNombre;
    int i,encontrados;

    cout<<"***Buscar tarea***"<<endl<<endl;
    cout<<"Ingresa el nombre del que deseas saber la tarea: ";
    fflush(stdin);
    getline(cin,buscarNombre);
    encontrados=0;
    cout<<endl;

    for(i=0; i<cuentaTareas; i++)
    {
        if (tareas[i]->dameMateria().find(buscarNombre)!=string::npos)
        {
            mostrarTarea(i);
            cout<<endl<<endl;
            encontrados++;
        }
    }
    if (encontrados)
    {
        cout<<"Se encontro "<<encontrados<<" registro(s) con la palabra buscada"<<endl;
    }
    else
    {
        cout<<"No se encontro algun registro con la palabra buscada"<<endl;
    }

}

int opcionMenuTarea()
{
    int opcion;
    fflush(stdin);

    system(CLEAR);
    cout<<"***REGISTRO DE TAREAS***"<<endl<<endl;
    cout << "1. Agregar tarea" << endl;
    cout << "2. Listar tareas" << endl;
    cout << "3. Mostrar detalles de una tarea" << endl;
    cout << "4. Buscar Tarea"<<endl;
    cout << "5. Modificar una tarea" << endl;
    cout << "6. Eliminar una tarea" << endl;
    cout << "7. Guardar cambios" << endl;
    cout << "8. Regresar al menu principal" << endl;
    cout << "Opcion: ";
    cin >> opcion;

    if (opcion>=ALTA && opcion<=GUARDAR)
    {
        system(CLEAR);
    }

    return opcion;
}
void controlTareas()
{
    cargarTareas();
    int opcion;

    do
    {
        opcion=opcionMenuTarea();

        switch(opcion)
        {
        case ALTA:
            altaTarea();
            break;
        case LISTAR:
            listarTareas();
            break;
        case MOSTRAR:
            mostrarDetallesTarea();
            break;
        case BUSCAR:
            buscarTarea();
            break;
        case MODIFICAR:
            modificarTarea();
            break;
        case ELIMINAR:
            bajaTarea();
            break;
        case GUARDAR:
            guardarRegistrosTareas();
            break;
        case REGRESAR:
            cuentaTareas=0;
            break;
        default:
            cout<<"Opcion no valida"<<endl;
        }

        pausar();
        system(CLEAR);
    }

    while(opcion!=REGRESAR);

}

void cargarTareas()
{
    int i=0;
    ifstream lectura;
    string materia;
    string descripcion;
    string asunto;
    bool libre=false;

    lectura.open(NOMBRE_ARCHIVO_TAREAS,ios::in);
    if(lectura.is_open())
    {
        getline(lectura,materia);
        while(!lectura.eof())
        {
            getline(lectura,descripcion);
            getline(lectura,asunto);
            tareas[i]=new Tarea (materia,descripcion,asunto,libre);
            i++;
            cuentaTareas++;
            getline(lectura,materia);
        }

        if(cuentaTareas==0)
        {
            cout<<"No hay ninguna tarea registrada"<<endl<<endl;
        }

        else if(cuentaTareas==1)
        {
            cout<<"Hay una sola tarea registrada"<<endl<<endl;
        }

        else if(cuentaTareas>1)
        {

            cout<<"Hay un total de "<<i<<" tareas registradas"<<endl<<endl;
        }
    }
    else
    {
        cout<<"No se pudo leer el archivo!"<<endl<<endl;
    }
    lectura.close();
    pausar();
}

void guardarRegistrosTareas()
{
    ofstream escritura;
    int i;
    escritura.open(NOMBRE_ARCHIVO_TAREAS,ios::out);

    if(escritura.is_open())
    {
        for(i=0; i<cuentaTareas; i++)
        {
            if(!tareas[i]->dameEstado())
            {
                escritura<<tareas[i]->dameMateria()<<endl;
                escritura<<tareas[i]->dameDescripcion()<<endl;
                escritura<<tareas[i]->dameAsunto()<<endl;
            }
        }

        cout<<"Se ha guardado correctamente!"<<endl;
    }
    else
    {
        cout<<"No se pudo leer el Archivo!";
    }

    escritura.close();
}

void pedirDatosRecordatorio(int i)
{
    string asunto,hora,fecha;
    char tipoRecordatorio;

    recordatorios[i]=new Recordatorio(asunto,tipoRecordatorio,fecha,hora,false);
    fflush(stdin);
    cout<<"Ingresa el asunto del recordatorio: ";
    getline(cin,asunto);
    fflush(stdin);
    while(!recordatorios[i]->fijaAsunto(asunto))
    {
        fflush(stdin);
        cout<<endl<<"Asunto no valido!"<<endl;
        cout<<"Ingresa el asunto del recordatorio: ";
        getline(cin,asunto);
    }
    cout<<"Ingresa el tipo de recordatorio (Letra): ";
    cin>>tipoRecordatorio;
    fflush(stdin);
    cout<<"Ingresa la fecha: ";
    getline(cin,fecha);
    fflush(stdin);
    while(!recordatorios[i]->fijaFecha(fecha))
    {
        fflush(stdin);
        cout<<endl<<"Fecha no valida!"<<endl;
        cout<<"Ingresa la fecha: ";
        getline(cin,fecha);
    }
    cout<<"Ingresa la hora del recordatorio: ";
    getline(cin,hora);
    while(!recordatorios[i]->fijaHora(hora))
    {
        fflush(stdin);
        cout<<endl<<"Hora no valida!"<<endl;
        cout<<"Ingresa la hora del recordatorio: ";
        getline(cin,hora);
    }

    recordatorios[i]=new Recordatorio(asunto,tipoRecordatorio,fecha,hora,false);
}

void altaRecordatorio()
{
    cout<<"***Dar de alta un recordatorio***"<<endl<<endl;

    if(cuentaRecordatorios<TOTAL_RECORDATORIOS)
    {
        pedirDatosRecordatorio(cuentaRecordatorios);
        cuentaRecordatorios++;
    }
    else
    {
        solicitarMemoriaRecordatorio();
        pedirDatosRecordatorio(cuentaRecordatorios);
        cuentaRecordatorios++;
    }

    cout<<endl<<endl<<"El registro se dio de alta correctamente!";
}

void mostrarRecordatorio(int i)
{
    cout<<"Asunto: "<<recordatorios[i]->dameAsunto()<<endl;
    cout<<"Tipo de recordatorio: "<<recordatorios[i]->dameTipoRecordatorio()<<endl;
    cout<<"Fecha: "<<recordatorios[i]->dameFecha()<<endl;
    cout<<"Hora: "<<recordatorios[i]->dameHora()<<endl<<endl;
}

void modificarRecordatorio()
{
    int i;
    int datoModificar;
    char tipoRecordatorio;
    string asunto,hora,fecha;

    cout<<"***Modificar Recordatorio***"<<endl<<endl;
    listarRecordatorios();
    fflush(stdin);
    cout<<"Ingresa el numero de registro que deseas modificar: ";
    cin>>i;
    fflush(stdin);
    i--;
    if(recordatorioTieneDatos(i))
    {
        mostrarRecordatorio(i);
        cout<<"1. Modificar todos los datos del registro"<<endl;
        cout<<"2. Asunto"<<endl;
        cout<<"3. Tipo de Recordatorio"<<endl;
        cout<<"4. Fecha"<<endl;
        cout<<"5. Hora"<<endl<<endl;
        cout<<"Ingresa el Dato que deseas modificar: ";
        cin>>datoModificar;

        while(datoModificar!=1&&datoModificar!=2&&datoModificar!=3&&datoModificar!=4&&
                datoModificar!=5)
        {
            fflush(stdin);
            cout<<"opcion no valida!"<<endl<<endl;
            cout<<"1. Modificar todos los datos del registro"<<endl;
            cout<<"2. Asunto"<<endl;
            cout<<"3. Tipo de Recordatorio"<<endl;
            cout<<"4. Fecha"<<endl;
            cout<<"5. Hora"<<endl<<endl;
            cout<<"Ingresa el Dato que deseas modificar: ";
            cin>>datoModificar;
        }
        cout<<endl;
        switch(datoModificar)
        {
        default:
            break;

        case 1:
            pedirDatosRecordatorio(i);
            break;

        case 2:
            fflush(stdin);
            cout<<"Ingresa el Asunto: ";
            getline(cin,asunto);
            while(!recordatorios[i]->fijaAsunto(asunto))
            {
                fflush(stdin);
                cout<<endl<<"Asunto no valido!"<<endl;
                cout<<"Ingresa el asunto del recordatorio: ";
                getline(cin,asunto);
            }
            break;

        case 3:
            fflush(stdin);
            cout<<"Ingresa el tipo de recordatorio: ";
            cin>>tipoRecordatorio;
            recordatorios[i]->fijaTipoRecordatorio(tipoRecordatorio);
            break;

        case 4:
            fflush(stdin);
            cout<<"Ingresa la fecha: ";
            getline(cin,fecha);
            while(!recordatorios[i]->fijaFecha(fecha))
            {
                fflush(stdin);
                cout<<endl<<"Fecha no valida!"<<endl;
                cout<<"Ingresa la fecha: ";
                getline(cin,fecha);
            }
            break;

        case 5:
            fflush(stdin);
            cout<<"Ingresa la hora: ";
            getline(cin,hora);
            while(!recordatorios[i]->fijaHora(hora))
            {
                fflush(stdin);
                cout<<endl<<"Hora no valida!"<<endl;
                cout<<"Ingresa la hora del recordatorio: ";
                getline(cin,hora);
            }
            break;
        }

        cout<<endl<<endl<<"Registro modificado correctamente!"<<endl;
    }
}

void listarRecordatorios()
{

    int i;
    int registro=0;
    cout<<endl<<"Listado Actual de registros."<<endl;
    cout<<"Registro\tFecha\t\tAsunto"<<endl;
    for(i=0; i<cuentaRecordatorios; i++)
    {
        if(!recordatorios[i]->dameEstado())
        {
            registro++;
            cout<<registro <<"\t\t";
            cout<<recordatorios[i]->dameFecha()<<"\t";
            cout<<recordatorios[i]->dameAsunto()<<endl;
        }
    }

    cout<<endl<<endl;

}

bool recordatorioTieneDatos(int i)
{
    bool tieneDatos;

    if(i>=0&&i<cuentaRecordatorios)
    {
        tieneDatos=true;
    }
    else
    {
        cout<<endl<<"No existe ese registro"<<endl;
        tieneDatos=false;
    }
    return tieneDatos;
}

void bajaRecordatorio()
{
    int i;
    char respuesta;
    fflush(stdin);

    cout<<"***Baja recordatorio***"<<endl<<endl;
    listarRecordatorios();
    cout<<"Ingresa el registro que quieras dar de baja: ";
    cin>>i;
    i--;
    cout<<endl;
    if(recordatorioTieneDatos(i))
    {
        fflush(stdin);
        mostrarRecordatorio(i);
        cout<<"Deseas dar de baja este recordatorio (s/n): ";
        cin>>respuesta;
        while(respuesta!='s'&&respuesta!='n')
        {
            fflush(stdin);
            cout<<endl<<endl<<"Respuesta no valida!"<<endl;
            cout<<"Deseas dar de baja este recordatorio (s/n): ";
            cin>>respuesta;
        }

        switch(respuesta)
        {
        default:
            break;

        case 's':
            for(cuentaRecordatorios--; i<cuentaRecordatorios; i++)
            {
                recordatorios[i]=recordatorios[i+1];
            }
            cout<<endl<<"Recordatorio Eliminado!";
            break;
        case 'n':
            cout<<endl<<"Recordatorio Conservado!";
            break;
        }

    }

}

void mostrarDetallesRecordatorio()
{
    int i;
    fflush(stdin);
    cout<<"***Mostrar Detalles Recordatorio***"<<endl<<endl;
    listarRecordatorios();
    cout<<"Ingresa el numero de registro del recordatorio que deseas saber detalles: ";
    cin>>i;
    i--;
    if(recordatorioTieneDatos(i))
    {
        mostrarRecordatorio(i);
    }
}

void buscarRecordatorio()
{
    int i;
    int coincidencias=0;
    string buscarAsunto;
    fflush(stdin);
    cout<<"***Buscar recordatorio***"<<endl<<endl;
    cout<<"Ingresa el asunto del recordatorio: ";
    getline(cin,buscarAsunto);

    for(i=0; i<cuentaRecordatorios; i++)
    {
        if(recordatorios[i]->dameAsunto().find(buscarAsunto)!=string::npos)
        {
            mostrarRecordatorio(i);
            coincidencias++;
        }
    }

    cout<<endl<<endl<<"Se encontraron "<<coincidencias<<" coinidencias."<<endl<<endl;
}

void guardarRegistrosRecordatorios()
{
    cout<<"***Guardar Registros en un archivo de texto***"<<endl<<endl;
    int i;
    ofstream escritura;
    escritura.open(NOMBRE_ARCHIVO_RECORDATORIO,ios::out);

    if(cuentaRecordatorios>0)
    {
        if(escritura.is_open())
        {

            for(i=0; i<cuentaRecordatorios; i++)
            {
                escritura<<recordatorios[i]->dameAsunto()<<endl;
                escritura<<recordatorios[i]->dameTipoRecordatorio()<<endl;
                escritura<<recordatorios[i]->dameFecha()<<endl;
                escritura<<recordatorios[i]->dameHora()<<endl;
            }
            cout<<endl<<"Se han guardado los registros correctamente!"<<endl;
        }
        else
        {
            cout<<endl<<endl<<"No se pudo abrir el archivo!"<<endl;
        }
    }
    else
    {
        cout<<endl<<"No hay nada que guardar!"<<endl;
    }

    escritura.close();
}

void cargarRecordatorios()
{
    ifstream lectura;
    int i=0;
    string asunto,hora,fecha,tipoRecordatorio;

    lectura.open(NOMBRE_ARCHIVO_RECORDATORIO,ios::in);
    if(lectura.is_open())
    {
        getline(lectura,asunto);
        while(!lectura.eof())
        {
            getline(lectura,tipoRecordatorio);
            getline(lectura,fecha);
            getline(lectura,hora);
            recordatorios[i]=new Recordatorio(asunto,tipoRecordatorio[0],fecha,hora,false);
            cuentaRecordatorios++;
            i=cuentaRecordatorios;
            getline(lectura,asunto);
        }

        cout<<"Se ha cargado "<<cuentaRecordatorios<<" recordatorios!";
    }
    else
    {
        cout<<"No se pudo leer el archivo!";
    }

    lectura.close();
    pausar();
}

int opcionMenuRecordatorio()
{

    int opcion;
    fflush(stdin);

    system(CLEAR);
    cout<<"***Agenda***"<<endl<<endl;
    cout << "1. Agregar recordatorio" << endl;
    cout << "2. Listar recordatorios" << endl;
    cout << "3. Mostrar detalles de un recordatorio" << endl;
    cout << "4. Buscar recordatorio"<<endl;
    cout << "5. Modificar un recordatorio" << endl;
    cout << "6. Eliminar un recordatorio" << endl;
    cout << "7. Guardar cambios" << endl;
    cout << "8. Regresar al menu principal" << endl;
    cout << "Opcion: ";
    cin >> opcion;

    if (opcion>=ALTA && opcion<=GUARDAR)
    {
        system(CLEAR);
    }

    return opcion;
}

void controlRecordatorios()
{

    cargarRecordatorios();
    int opcion;

    do
    {
        opcion=opcionMenuRecordatorio();

        switch(opcion)
        {
        case ALTA:
            altaRecordatorio();
            break;
        case LISTAR:
            listarRecordatorios();
            break;
        case MOSTRAR:
            mostrarDetallesRecordatorio();
            break;
        case BUSCAR:
            buscarRecordatorio();
            break;
        case MODIFICAR:
            modificarRecordatorio();
            break;
        case ELIMINAR:
            bajaRecordatorio();
            break;
        case GUARDAR:
            guardarRegistrosRecordatorios();
            break;
        case REGRESAR:
            cuentaRecordatorios=0;
            break;
        default:
            cout<<"Opcion no valida"<<endl;
        }

        pausar();
        system(CLEAR);
    }

    while(opcion!=REGRESAR);
}


void inicializar()
{
    menuNota=new MenuNota();
}
