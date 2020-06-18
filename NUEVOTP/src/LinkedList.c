#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "utn.h"
#include "Controller.h"
#include "Employee.h"
#include "parser.h"

static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= NULL;

    this = (LinkedList*) malloc(sizeof(LinkedList));
    if(this != NULL)
    {
    	this->pFirstNode = NULL;
    	this->size = 0;
    }

    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	returnAux=this->size;
    }

    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* pNodo = NULL;
	int indice=0;

	if(this != NULL && nodeIndex < ll_len(this) && nodeIndex >=0)
	{
		pNodo=this->pFirstNode;
		if(nodeIndex == 0) // si es el primero queda con la direccion del primer nodo.
		{
			 return pNodo;
		}
		else
		{
			do
			{
			 pNodo=pNodo->pNextNode; // direccion de memoria del
			indice ++;
			}while(indice != nodeIndex);
		}
	}

	 return pNodo;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
		int returnAux = -1;
	    Node* pNode;
	    Node* pNodeAux;

	    if(this != NULL && nodeIndex <= ll_len(this) && nodeIndex >=0)
	    {
	    	 pNode = (Node*) malloc(sizeof(Node));
	    	 if(pNode!=NULL)
	    	  {
	    	  	pNode->pElement = pElement;
	    	   	this->size=(ll_len(this))+1;
	    	  }

	    	if(nodeIndex == 0) //primer nodo
	    	{
	    		pNode->pNextNode=this->pFirstNode;
	    		this->pFirstNode=pNode;
	    		returnAux=0;
	    	}
	    	else if(nodeIndex == this->size) //final
	    	{
	    		pNode->pNextNode=NULL;
	    		returnAux=0;
	    	}
	    	else  //en el medio
	    	{
	    		pNode->pNextNode=getNode(this,(nodeIndex));//la direccion de memoria donde estaba
	    		pNodeAux=getNode(this,(nodeIndex-1));
	    		pNodeAux->pNextNode=pNode;
	    		returnAux=0;
	    	}

	    }
	    else
	    {
	    	returnAux=-1;
	    }

	    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	if(addNode(this,this->size,pElement)==0)// agrego un elemento a la lista
    	{
    		returnAux=0;
    	}
    }
    else
    {
    	returnAux=-1;
    }

    return returnAux;
}

/** \brief Permite obtener un puntero a un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */

void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* pNode;

     if(this != NULL && index >= 0 && index <= ll_len(this))
     {
    	 pNode=getNode(this,index); // leo un nodo en un indice determinado
    	 if(pNode !=NULL)
    	 {
    		 returnAux=pNode->pElement; // obtengo su pElement.
    	 }
     }
     else
     {
    	 returnAux=NULL;
     }

  return returnAux;

}

/** \brief Modifica un elemento de la lista
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* pNode;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {

    	pNode=getNode(this, index); // leo un nodo en una posicion determinada
    	if(pNode!=NULL)
    	{
    		pNode->pElement=pElement; // le asigno un elemento nuevo a la posicion de pElement en el nodo.
    		returnAux=0;
    	}
    }

    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* pNode;
    Node* pNodeAux;

    if(this != NULL && index >= 0 && index <= ll_len(this))
    {
    	pNode=getNode(this,index);
    	if(pNode!=NULL)
    	{
    		if(index==0)  // si es el primero
    		{
    			pNode=getNode(this,index);
    			if(pNode!=NULL)
    			{
    				this->pFirstNode=getNode(this,index+1); // direccion de memoria del primer nodo = a la direccion de memoria del proximo nodo USADO.
    				this->size=(ll_len(this)-1); // reduzco el size de la lista
    				free(pNode);
    				returnAux=0;
    			}
    		}
    		else
    		{

    			pNodeAux=getNode(this,index-1);// obtuve direccion del nodo anterior
    			if(pNodeAux!=NULL)
    			{
    				pNodeAux->pNextNode=getNode(this,index+1); // le doy al nodo anterior la direccion de memoria del siguiente (salteando el que quiero eliminar)
    				this->size=(ll_len(this)-1);// reduzco el size de la lista
    				free(pNode);
    				returnAux=0;
    			}
    		}

    	}

    }
    else
    {
    	returnAux=-1;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int i;
    int len = ll_len(this);

    if(this != NULL)
    {
    	returnAux=0;
    	for(i=len;ll_len(this) != 0;i--)
    	{
    		ll_remove(this,i);
    	}
    }
    else
    {
    	returnAux=-1;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	this=NULL; // apunto el puntero de la lista a null asi pierdo todos los datos y elementos.
    	free(this);
    	returnAux=0; // informo que borrre todo con exito.
    }
    else
    {
    	returnAux=-1;
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    Node* pNode;
    int i;

    if(this != NULL)
    {
    	for(i=0;i<(ll_len(this));i++) // recorro la lista
    	{
    		pNode=getNode(this,i); // obtengo direccion de memoria de un nodo
    		if(pNode!=NULL)
    		{
    			if(pNode->pElement==pElement) // leo ese nodo, en la posicion elemento y lo comparo con el elemento que me mandaron,.
    			{
    				return i;  // retorno la posicion si lo encontre.
    				break; // rompo por si esta repetido en otra posicion.
    			}
    		}
    	}
    }
    else
	{
    	returnAux = -1;
	}

    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	if(this->size == 0) // miro el tamaño de la lista si es 0 informo que esta vacia
    	{
    		returnAux=1;
    	}
    	else if(this->size > 0) // si la lista es mas grande informo informo que contiene algo.
    	{
    		returnAux=0;
    	}
    }
    else
    {
    	returnAux=-1;
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    Node* pNode;
    Node* pNodeAux;

    if(this != NULL && index >= 0 && index <= ll_len(this))
    {
    	if(ll_add(this,pElement)==0) // añado un elemento a la lista y asi tengo un nodo
    	{
    		pNode=getNode(this,index); // obtengo direccion del nodo que cree.
    	}

    	if(pNode!=NULL)
    	{
    		pNode->pElement=pElement; // leo el elemento.
    		if(index==0 && index==ll_len(this)) // miro si es el primero de una lista con 1 nodo.
    		{
    			pNode->pNextNode=NULL;

    		}
    		else  // si es un nodo intermedio o el ultimo.
    		{
    			pNodeAux=getNode(this,index-1);
    			if(pNodeAux!=NULL)
    			{
    				pNodeAux->pNextNode=pNode; // le doy al nodo la direccion de memoria del siguiente (salteando el que quiero eliminar)
    				pNode->pNextNode=getNode(this,index+1); // doy la direccion de memoria del sigiuente nodo a mi nodo.
    			}
    		}
    	}
    	returnAux=0;
    }
    else
    {
    	returnAux=-1;
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    Node* pNode;
    Node* pNodeAux;

    if(this != NULL && index >= 0 && index <= ll_len(this)) // verificacion
    {
    	pNode=getNode(this,index); // obtengo direccion del nodo
    	if(pNode!=NULL)
    	{
    		pNodeAux=pNode->pElement; // leo el puntero al elemento del nodo.
    		if(ll_remove(this,index) == 0) // remuevo de la lista en la posicion que piden.
    		{
    		    return pNodeAux; // retorno el puntero al elemento que obtuve anteriormente
    		}
    	}

    }
    else
    {
    	returnAux=NULL;
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    Node* pNode=NULL;
    int i;

    if(this != NULL)
    {
    	if(pElement == NULL) // si pasa un elemento NULL aviso que no lo contiene (ayuda de error linea 51)
    	{
    		returnAux=0;
    	}

    	for(i=0;i<ll_len(this);i++) // recorro lista
    	{
    		pNode=getNode(this,i); // obtengo puntero a nodo
    		if(pNode != NULL)
    		{
    			if(pNode->pElement == pElement) // verifico si ese nodo contiene el elemento
    			{
    				returnAux=1; // si lo tiene rompo y aviso que lo contiene
    				break;
    			}
    			else
    			{
    				returnAux=0; // si nunca lo encontro devuelve 0
    			}
    		}
    	}
    }
    else
    {
    	returnAux=-1; // si la lista da a null
    }

    return returnAux;

}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;

    Node* pNode;
    Node* pNode2;
    int j;
    int i;
    int flag=0;

    if(this != NULL && this2 != NULL)
    {
    	returnAux=0; // si ya paso la primer verificacion digo que no se contienen hasta demostrar lo contrario.

    	for(i=0;i<ll_len(this2);i++) // itero la lista 2.
    	{
    		pNode2=getNode(this2,i); // leo la direccion de un nodo de la lista 2.
    		for(j=0;j<ll_len(this);j++) // itero la lista1
    		{
    			pNode=getNode(this,j);//leo la direccion de un nodo de la lista 1
    			if(pNode2 != NULL && pNode != NULL)
    			{
    				flag=0;
    				if(pNode2->pElement==pNode->pElement) // comparo un elemento de la lista dos, con los elementos de la lista 1
    				{
    				   flag=1;
    				   returnAux=1; // SI PUDE ENCONTRAR EL ELEMENTO DEVUELVO 1.
    				   break; // ROMPO LA ITERACION
    				}
    				if(i == ll_len(this) && flag==0) // si llego al final de la lista 1 y no pudo encontrar el elemento te digo 0 y que NO esta contenida.
    				{
    					returnAux=0;
    					return returnAux;
    				}
    			}

    		}
    	}
    }
    else
    {
    	returnAux=-1;
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    Node* pNode;
    int i;
    int j;

    if(this !=NULL && from >= 0 && from <= ll_len (this) && to >= 0 && to <= ll_len(this))
    {
    	cloneArray = ll_newLinkedList();
    	if(cloneArray != NULL)
    	{
    		for(i=0;i<ll_len(this);i++)
    		{
    			for(j=from;j<to;j++)
    			{
    				pNode=getNode(this,j);
    				if(pNode!=NULL)
    				{
    					ll_add(cloneArray,pNode->pElement);
    				}
    			}
    		}
    	}
    }
    else
    {
    	cloneArray = NULL;
    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    Node* pNode;
    int i;

    if(this != NULL)
    {
    	cloneArray = ll_newLinkedList();
    	if(cloneArray != NULL)
    	{
    		for(i=0;i<ll_len(this);i++)
    		{
    			pNode=getNode(this,i);
    			if(pNode != NULL)
    			{
    				pNode=getNode(this,i);
    				ll_add(cloneArray,pNode->pElement);
    			}
    		}
    	}
    }
    else
    {
    	cloneArray=NULL;
    }
    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    int RuturnFuncion;
    Node* pNode1;
    Node* pNode2;
    void* auxElemento;
    int j;
    int FlagSwap;
    int len = ll_len(this)-1; // le doy a una variable el tamaño de la lista (-1)

    if(this != NULL && pFunc != NULL && (order == 1 || order == 0))  // verifico != NULL y que el orden sea 1 o 0
    {
    	do
    	{
    		FlagSwap=0;  //pongo bandera en 0

    			for(j=0;j<len;j++) // con este for comparo elementos.
    			{
    				pNode1=getNode(this,j); // leo el puntero a un nodo
    				pNode2=getNode(this,j+1); // leo puntero al otro nodo
    				RuturnFuncion = pFunc(pNode1->pElement, pNode2->pElement); // llamo a la funcion criterio que me va a devolver una variable del tipo int (-1/0/1)
    				if(order == 1)
    				{
    					if(RuturnFuncion == 1)
    					{
    						FlagSwap=1;
    						auxElemento=pNode1->pElement;  // hago al swap
    						pNode1->pElement=pNode2->pElement;
    						pNode2->pElement=auxElemento;
    					}
    				}
    				if(order == 0)
    				{
    					if(RuturnFuncion == -1)
    					{
    						FlagSwap=1;
    						auxElemento=pNode2->pElement;  // hago al swap
    						pNode2->pElement=pNode1->pElement;
    						pNode1->pElement=auxElemento;
    					}
    				}
    			}
    		len --;
    	}while(FlagSwap);
    returnAux=0;
    }
    else
    {
    	returnAux =-1;
    }

    return returnAux;
}

/** \brief manda elementos a una funcion criterio.
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                        (0) Si ok
 */

int ll_map (LinkedList* this, int (*pFunc)(void*))  // usa funcion criterio2
{
	int returnAux=-1;
	int i;
	Node* pNode;

	if(this != NULL && *pFunc != NULL)  //
	{
		returnAux=0;
			for(i=0;i<ll_len(this);i++)
			{
				pNode=getNode(this,i); // leo un nodo
				pFunc(pNode->pElement); // LLAMA A UNA FUNCION QUE IMPRIME
			}
	}

	return returnAux;
}

/** \brief elimina un elemento de la lista segun critero de una funcion
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio (1 saco de la lista, 0 dejo en la lista)
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL o puntero a la funcion es NULL
                        (0) Si ok
 */
int ll_reduce (LinkedList* this, int (*pFunc)(void*)) // usa funcion criterio SUELDO
{
	int returnAux = -1;
	Node* pNode;
	int i;
	int AuxFuncion;

	if(this != NULL && pFunc != NULL) // verifico que no sean NULL
	{
		for(i=0;i<ll_len(this);i++) // itero la lista
		{
			pNode=getNode(this,i); // un elemento
			AuxFuncion = pFunc(pNode->pElement); // mando un elemento a la funcion para que determine que hacer
			if(AuxFuncion==1)  // si la funcion de verdadero, remuevo ese elemento de la lista.
			{
				ll_remove(this,i);
				i--;
			}
		}
		returnAux=0;
	}

	return returnAux;
}

/** \brief Crea una lista clon con elementos que la funcion criterio determina
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL o puntero a la funcion es NULL
                        (0) Si ok
 */
// filter (algo tipo clone) solo con los elementos que la funcion criterio diga.

LinkedList* ll_filter (LinkedList* this, int (*pFunc)(void*))
{
	LinkedList* returnAux = NULL;

	LinkedList* cloneArray = NULL;
	Node* pNode;
	int auxFuncion;
	int i;

	if(this != NULL && pFunc != NULL) // verifico que no sean NULL.
	{
		cloneArray = ll_newLinkedList();  // creo una lista (clon).
		if(cloneArray != NULL)
		{
		  for(i=0;i<ll_len(this);i++) // itero la lista principal.
		  {
		    pNode=getNode(this,i);  // leo un nodo.
		    auxFuncion = pFunc(pNode->pElement); // mando un elemento para verificar el criterio.
		    if(pNode != NULL && auxFuncion == 0)  // si da 0, lo añado a la lista.
		    {
		    	ll_add(cloneArray,pNode->pElement); // agrego a mi lista clon
		    }
		  }
		  returnAux=cloneArray; // retorna puntero a la lista clon.
		}

	}

	return returnAux;
}
