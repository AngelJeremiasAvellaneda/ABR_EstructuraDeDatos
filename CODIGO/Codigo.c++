#include <iostream>
using namespace std;

//Estructura Nodo
struct Nodo
{
    int valor;
    Nodo* izquierdo;
    Nodo* derecho;
};

//Insertar un nodo
Nodo* insertar(Nodo* raiz,int valor)
{
    if(raiz==NULL)
    {
        Nodo* nuevo=new Nodo;
        nuevo->valor=valor;
        nuevo->izquierdo=NULL;
        nuevo->derecho=NULL;
        return nuevo;
    }
    if(valor<raiz->valor)
    {
        raiz->izquierdo=insertar(raiz->izquierdo,valor);
    }
    else if(valor>raiz->valor)
    {
        raiz->derecho=insertar(raiz->derecho,valor);
    }
    else
    {
        cout<<"Error, valor duplicado: "<<valor<<" no se insertará."<<endl;
    }
    return raiz;
}

//Recorrer por inorden
void inorden(Nodo* raiz)
{
    if(raiz!=NULL)
    {
        inorden(raiz->izquierdo);
        cout<<raiz->valor<<" ";
        inorden(raiz->derecho);
    }
}


//Buscar un nodo
bool buscar(Nodo* raiz,int valor)
{
    if(raiz==NULL)return false;
    if(raiz->valor==valor)return true;
    if(valor<raiz->valor)
    {
        return buscar(raiz->izquierdo,valor);
    }
    else
    {
        return buscar(raiz->derecho,valor);
    }
}

//Nodo con valor máximo
Nodo* encontrarMax(Nodo* raiz)
{
    while(raiz&&raiz->derecho!=NULL)
    {
        raiz=raiz->derecho;
    }
    return raiz;
}

//Eliminar un nodo
Nodo* eliminar(Nodo* raiz,int valor)
{
    if(raiz==NULL)return NULL;

    if(valor<raiz->valor)
    {
        raiz->izquierdo=eliminar(raiz->izquierdo,valor);
    }
    else if(valor>raiz->valor)
    {
        raiz->derecho=eliminar(raiz->derecho,valor);
    }
    else
    {
        if(raiz->izquierdo==NULL)
        {
            Nodo* temp=raiz->derecho;
            delete raiz;
            return temp;
        }
        else if(raiz->derecho==NULL)
        {
            Nodo* temp=raiz->izquierdo;
            delete raiz;
            return temp;
        }
        else
        {
            Nodo* temp=encontrarMax(raiz->izquierdo);
            raiz->valor=temp->valor;
            raiz->izquierdo=eliminar(raiz->izquierdo,temp->valor);
        }
    }
    return raiz;
}

//Actualizar valor de un nodo
Nodo* actualizar(Nodo* raiz,int viejo,int nuevo)
{
    if(!buscar(raiz,viejo))
    {
        cout<<"El valor "<<viejo<<" no existe."<<endl;
        return raiz;
    }
    raiz=eliminar(raiz,viejo);
    raiz=insertar(raiz,nuevo);
    cout<<"Valor actualizado de "<<viejo<<" a "<<nuevo<<"."<<endl;
    return raiz;
}

//Hallar segundo nodo con mayor valor
void segundoMayor(Nodo* raiz)
{
    if(raiz==NULL||(raiz->izquierdo==NULL&&raiz->derecho==NULL))
    {
        cout<<"Error. No hay suficientes nodos."<<endl;
        return;
    }

    Nodo* padre=NULL;
    Nodo* actual=raiz;

    while(actual->derecho!=NULL)
    {
        padre=actual;
        actual=actual->derecho;
    }

    if(actual->izquierdo!=NULL)
    {
        actual=actual->izquierdo;
        while(actual->derecho!=NULL)
        {
            actual=actual->derecho;
        }
        cout<<">>Segundo mayor valor: "<<actual->valor<<endl;
    }
    else
    {
        cout<<">>Segundo mayor valor: "<<padre->valor<<endl;
    }
}

int main()
{
	setlocale(LC_CTYPE,"Spanish");
    Nodo* raiz=NULL;
    //Insertar nodos de ejemplo
    raiz=insertar(raiz,100);
    raiz=insertar(raiz,200);
    raiz=insertar(raiz,300);
    raiz=insertar(raiz,600);
    raiz=insertar(raiz,800);

    cout<<"\nÁrbol actual (inorden): ";
    inorden(raiz);
    cout<<endl;

    segundoMayor(raiz);
    raiz=actualizar(raiz,200,750);
    cout<<"\nÁrbol tras actualizar (inorden): ";
    inorden(raiz);
    cout<<endl;
    segundoMayor(raiz);
    return 0;
}