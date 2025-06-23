#include <iostream>
#include <string>
using namespace std;

//Estructura Vendedor
struct Vendedor 
{
    int id;
    string nombre;
    string apellido;
    int productosVendidos;
    Vendedor* izquierdo;
    Vendedor* derecho;
};

//Nodo Nuevo Vendedor
Vendedor* crearVendedor(int id, string nombre, string apellido, int productos) 
{
    Vendedor* nuevo=new Vendedor;
    nuevo->id=id;
    nuevo->nombre=nombre;
    nuevo->apellido=apellido;
    nuevo->productosVendidos=productos;
    nuevo->izquierdo=NULL;
    nuevo->derecho=NULL;
    return nuevo;
}

//Insertar nodos
Vendedor* insertar(Vendedor* raiz, int id, string nombre, string apellido, int productos) 
{
    if(raiz==NULL) 
	{
        return crearVendedor(id, nombre, apellido, productos);
    }
    if(productos<raiz->productosVendidos) 
	{
        raiz->izquierdo=insertar(raiz->izquierdo, id, nombre, apellido, productos);
    } 
	else if (productos>raiz->productosVendidos) 
	{
        raiz->derecho=insertar(raiz->derecho, id, nombre, apellido, productos);
    } 
	else
	{
        cout << "Vendedor con " <<productos<< " productos ya existe. No se permiten duplicados.\n";
    }
    return raiz;
}

//Mostrar vendedores en orden (de menor a mayor por productos)
void mostrarInorden(Vendedor* raiz) 
{
    if(raiz!=NULL) 
	{
        mostrarInorden(raiz->izquierdo);
        cout<<raiz->id<<" - "<<raiz->nombre<<" "<<raiz->apellido<<" - Productos: "<< raiz->productosVendidos<<endl;
        mostrarInorden(raiz->derecho);
    }
}

//Buscar Vendedores
bool buscarID(Vendedor* raiz, int id) 
{
    if(raiz==NULL) 
	{
		return false;
	}
    if(raiz->id==id)
	{
		return true;
	} 
    return buscarID(raiz->izquierdo, id) || buscarID(raiz->derecho, id);
}

//Nodo con más productos vendidos
Vendedor* encontrarMax(Vendedor* raiz) 
{
    while(raiz && raiz->derecho!= NULL) 
	{
        raiz=raiz->derecho;
    }
    return raiz;
}

Vendedor* eliminarPorID(Vendedor* raiz, int id) 
{
    if(raiz==NULL)
    {
        return NULL;
    }

    // Recorremos ambos lados porque no sabemos dónde estará el ID
    if(raiz->id==id)
    {
        // Caso 1: sin hijos
        if(raiz->izquierdo==NULL && raiz->derecho==NULL)
        {
            delete raiz;
            return NULL;
        }

        // Caso 2: un solo hijo
        if(raiz->izquierdo==NULL)
        {
            Vendedor* temp=raiz->derecho;
            delete raiz;
            return temp;
        }
        else if(raiz->derecho==NULL)
        {
            Vendedor* temp=raiz->izquierdo;
            delete raiz;
            return temp;
        }

        // Caso 3: dos hijos, buscamos el mayor del subárbol izquierdo
        Vendedor* temp=encontrarMax(raiz->izquierdo);
        raiz->id=temp->id;
        raiz->nombre=temp->nombre;
        raiz->apellido=temp->apellido;
        raiz->productosVendidos=temp->productosVendidos;
        raiz->izquierdo=eliminarPorID(raiz->izquierdo, temp->id);
    }
    else
    {
        // Recorremos ambos lados porque el ID puede estar en cualquier lado
        raiz->izquierdo=eliminarPorID(raiz->izquierdo, id);
        raiz->derecho=eliminarPorID(raiz->derecho, id);
    }

    return raiz;
}

//Menu
int main()
{
	setlocale(LC_CTYPE, "Spanish");
	Vendedor* raiz = NULL;
	Vendedor temp;
	int op, productos;
	do
	{
		cout<<"\tMENU DE OPCIONES \n";
		cout<<"\t1. Insertar vendedor\n";
        cout<<"\t2. Mostrar vendedores\n";
        cout<<"\t3. Buscar vendedor por ID\n";
        cout<<"\t4. Eliminar vendedor\n";
        cout<<"\t5. Mostrar segundo mejor vendedor\n";
        cout<<"\t6. Salir\n";
        cout<<"\t-------------------------------------------------\n";
		
		do //Validar menu de opciones
		{
			cout<<"Elegir opcion: ";
			cin>>op;
			if(op<1 || op>6)
			{
				cout<<"Opcion incorrecta.\n";
			}
		}
		while(op<1 || op>6);
		cout<<"\n";
		
		switch (op)
		{
			case 1: 
			{
				cout<<"******Insertar vendedor******\n";
			    cout<<"ID: ";
			    cin>>temp.id;
			    cout<<"Nombre: ";
			    cin>>temp.nombre;
			    cout<<"Apellido: ";
			    cin>>temp.apellido;
			    
			    //Validar que productos no sea negativo
				do
				{
					cout<<"Productos vendidos: ";
					cin>>temp.productosVendidos;
					if(temp.productosVendidos<0)
					{
						cout<<"Error. La cantidad de productos vendidos no puede ser negativa.\n";
					}
				}
				while(temp.productosVendidos<0);
			
			    if(!buscarID(raiz, temp.id)) 
				{
			        raiz=insertar(raiz, temp.id, temp.nombre, temp.apellido, temp.productosVendidos);
			    } 
				else 
				{
			        cout<<"Error. Ya existe un vendedor con ese ID.\n";
			    }
			    cout<<"\n";
			}
			break;
			case 2:
				cout<<"******Vendedores Registrados******\n";
				mostrarInorden(raiz);
				cout<<"\n";
			break;
			case 3:
				cout<<"******Buscar Vendedores******\n";
	            cout<<"Ingrese ID de vendedor a buscar: ";
	            cin>>temp.id;
	            if(buscarID(raiz, temp.id))
	            {
	            	cout<<"Vendedor encontrado.\n";
				}
	            else
	            {
	            	cout<<"El vendedor no se encuentra registrado.\n";
				}
				cout<<"\n";
			break;
			case 4:
				cout<<"******Eliminar un Registro******\n";
            	cout<<"ID del vendedor a eliminar: ";
			    cin>>temp.id;
			    if(buscarID(raiz, temp.id))
			    {
			        raiz=eliminarPorID(raiz, temp.id);
			        cout<<"Vendedor eliminado correctamente.\n";
			    }
			    else
			    {
			        cout<<"No se encontró un vendedor con ese ID.\n";
			    }
			    cout<<"\n******Registro Actualizado******\n";
				mostrarInorden(raiz);
				cout<<"\n";
			break;
			case 5:
				cout<<"******Segundo Mejor Vendedor******\n";
				if(raiz==NULL || (raiz->izquierdo==NULL && raiz->derecho==NULL)) 
				{
                cout<<"No hay suficientes vendedores para determinar el segundo mejor.\n";
	            } 
				else 
				{
	                Vendedor* padre=NULL;
	                Vendedor* actual=raiz;
	                while(actual->derecho!=NULL) 
					{
	                    padre=actual;
	                    actual=actual->derecho;
	                }
	                if(actual->izquierdo!=NULL) 
					{
	                    actual=actual->izquierdo;
	                    while (actual->derecho!=NULL) 
						{
	                        actual=actual->derecho;
	                    }
	                    cout<<">> Segundo mejor vendedor: "<<actual->nombre<<" "<<actual->apellido<<" - Productos: "<<actual->productosVendidos<<endl;
	                } 
					else if(padre!=NULL) 
					{
	                    cout<<">> Segundo mejor vendedor: "<<padre->nombre<<" "<<padre->apellido<<" - Productos: "<< padre->productosVendidos<<endl;
	                }    
	            }
	            cout<<"\n";
	        break;
			case 6:
				cout<<"Hasta pronto...\n";
				cout<<"\n";
			break;
		}
	system("pause");
	system("cls");	
	}
	while(op!=6);	
	return 0;
}


