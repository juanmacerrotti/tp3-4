#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "utn.h"
#include "Controller.h"

static int esNumerica(char* cadena, int limite);
static int isValidNombre(char* cadena,int longitud);



/**
 * \brief crea espacio en memoria para un empelado
 * \return Retorna NULL si no encontro el espacio o el puntero a ese espacio si pudo encontrarlo.
 */
Employee* employee_new(void)
{
	Employee* auxiliarEmpleado = NULL;

	auxiliarEmpleado = (Employee*) malloc(sizeof(Employee)); //creo un espacio de memoria del tamaño de un empleado.

	return auxiliarEmpleado;
}

/**
 * \brief crea un empleado en memoria
 * \param idStr id del empleado
 * \param nombre del empleado
 * \param horas que trabaja
 * \param sueldo del empleado
 * \return Retorna NULL si no pudo crear el empleado, o la direccion de memoria en caso que pueda cargar el empleado.
 */
Employee* employee_newParametrosTxt(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr)
{
    Employee* punteroEmpleado = NULL;
	punteroEmpleado = employee_new();
	int flag = 0;
	if(punteroEmpleado != NULL)
	{
		if(employee_setIdStr(punteroEmpleado,idStr) == 0 &&
				employee_setNombre(punteroEmpleado,nombreStr) == 0 &&
				employee_setHorasTrabajadasStr(punteroEmpleado,horasTrabajadasStr) == 0 &&
				employee_setSueldoStr(punteroEmpleado,sueldoStr)== 0)
		{
			flag = 1;
		}

		if(flag == 0)
		{
			employee_delete(punteroEmpleado);
			punteroEmpleado=NULL;
		}
	}
	return punteroEmpleado;

}

Employee* employee_newParametros(int id,char* nombreStr,int horasTrabajadas,int sueldo)
{
	int flagOk=0;
	Employee* punteroEmpleados = NULL;
	punteroEmpleados = employee_new();

	if(punteroEmpleados != NULL)
	{
		if(employee_setNombre(punteroEmpleados,nombreStr) == 0)
		{
			if(employee_setHorasTrabajadas(punteroEmpleados, horasTrabajadas) == 0)
			{
				if(employee_setId(punteroEmpleados,id) == 0)
				{
					if(employee_setSueldo(punteroEmpleados,sueldo) == 0)
					{
						flagOk=1;
					}
				}
			}
		}
		if(flagOk==0)
		{
			employee_delete (punteroEmpleados);
			punteroEmpleados=NULL;
		}
	}
	return punteroEmpleados;
}

void employee_delete(Employee* this)
{
	if(this != NULL)
	{
	  free(this);
	}
}
int employee_imprimir(Employee* this)
{
	int retorno = -1;
    char auxiliarId[2048];
	char auxiliarNombre[2048];
	char auxiliarHsTrabajadas[2048];
	char auxiliarSueldo[2048];

	if(this != NULL)
	{
		employee_getHorasTrabajadasStr(this,auxiliarHsTrabajadas);
		employee_getIdStr(this,auxiliarId);
		employee_getNombre(this,auxiliarNombre);
		employee_getSueldoStr(this,auxiliarSueldo);
		printf("ID: %s | Nombre: %s | Sueldo: %s | Hs.Trabajadas: %s\n",auxiliarId,auxiliarNombre,auxiliarSueldo,auxiliarHsTrabajadas);
		retorno = 0;
	}


	return retorno;
}

// SET Y GET

int employee_setId(Employee* this,int id)
{
	int retorno = -1;
    if(this != NULL && id >= 0)
		{
			retorno = 0;
			this->id = id;
		}
		return retorno;
}


int employee_setIdStr(Employee* this,char* id)
{
	int retorno = -1;
	if(this != NULL && id != NULL)
	{
		if(esNumerica(id,10))
		{
			retorno = 0;
			this->id = atoi(id);
		}
	}
return retorno;
}

int employee_getId(Employee* this,int* id)
{
	int retorno = -1;
	if(this != NULL && id != NULL)
	{
		retorno = 0;
		*id = this->id;
	}
	return retorno;
}

int employee_getIdStr(Employee* this,char* id)
{
	int retorno = -1;
    if(this != NULL && id != NULL)
	{
		retorno = 0;
		sprintf(id,"%d",this->id);
	}
		return retorno;
}

int employee_setNombre(Employee* this,char* nombre)
{
	int retorno = -1;
    if(this != NULL && nombre != NULL)
		{
		 if(isValidNombre(nombre,128))
			{
			  retorno = 0;
			  strncpy(this->nombre,nombre,128);
			}
		}
		return retorno;
}

int employee_getNombre(Employee* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		retorno = 0;
		strncpy(nombre,this->nombre,128);
	}
	return retorno;
}

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
   int retorno = -1;
   if(this != NULL && horasTrabajadas >= 0)
   		{
   			retorno = 0;
   			this->horasTrabajadas = horasTrabajadas;
   		}
   		return retorno;
}

int employee_setHorasTrabajadasStr(Employee* this,char* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas != NULL)
	{
		if(esNumerica(horasTrabajadas,10))
	        {
	         	retorno = 0;
	   			this->horasTrabajadas = atoi(horasTrabajadas);
	   		}
	}
	   return retorno;
}

int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas >= 0)
	{
	      retorno = 0;
		  *horasTrabajadas = this->horasTrabajadas;
	}
	return retorno;
}

int employee_getHorasTrabajadasStr(Employee* this,char* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas != NULL)
	{
	  retorno = 0;
	  sprintf(horasTrabajadas,"%d",this->horasTrabajadas);
	}
		   return retorno;
}

int employee_setSueldo(Employee* this,int sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo >= 0)
	   {
	   	 retorno = 0;
	   	 this->sueldo = sueldo;
	   }
	return retorno;
}

int employee_setSueldoStr(Employee* this,char* sueldo)
{
    int retorno = -1;
	if(this != NULL && sueldo != NULL)
	{
		if(esNumerica(sueldo,10))
	        {
	         	retorno = 0;
	   			this->sueldo = atoi(sueldo);
	   		}
	}
	   return retorno;
}

int employee_getSueldo(Employee* this,int* sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo >= 0)
		{
		  retorno = 0;
	     *sueldo = this->sueldo;
		}
		return retorno;
}

int employee_getSueldoStr(Employee* this,char* sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo != NULL)
		{
		  retorno = 0;
		  sprintf(sueldo,"%d",this->sueldo);
		}
		return retorno;
}

/***********************************/
//Statics para validad

static int esNumerica(char* cadena, int limite)
{
	int retorno = -1;
	int i;
	if(cadena != NULL && limite > 0)
	{
		retorno = 1;
		for(i=0;i<limite && cadena[i] != '\0';i++)
		{
			if(i==0 && (cadena[i] == '+' || cadena[i] == '-'))
			{
				continue;
			}
			if(cadena[i] < '0'||cadena[i] > '9')
			{
				retorno = 0;
				break;
			}

		}

	}
	return retorno;
}
static int isValidNombre(char* cadena,int longitud)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			if(cadena[i] != '-' && cadena[i] != ' ' && (cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief compara dos sueldo de empleados.
 * \param item1 puntero a void (direccion de memoria de un empleado)
 * \param item2 puntero a void (direccion de memoria de un empleado)
 * \return Retorna 1 (si suledo 1 es mayor o igual que el 2) retorno 0 (si sueldo dos es mas grande que sueldo 1) retorno -1 (error)
 */
int Employee_funcionCriterio (void* item1, void* item2)
{
	int retorno = 0;

	Employee* empleado1;
	Employee* empleado2;

	int sueldo1;
	int sueldo2;

	empleado1= (Employee*)item1;  //guardo mi puntero a void en una variable del tipo empleado* para acceder a sus campos.
	empleado2=(Employee*)item2;

	if(item1 != NULL && item2 != NULL)
	{
		if(employee_getSueldo(empleado1,&sueldo1)==0 &&  // leo sueldo del puntero a empleado.
			employee_getSueldo(empleado2,&sueldo2) == 0) // leo sueldo del puntero a empleado.
			{
				if(sueldo1>sueldo2)
				{
					retorno=1; //sueldo1 es mayor
				}
				if(sueldo1<sueldo2)
				{
					retorno=-1; //sueldo2 es mayor
				}
				if(sueldo1==sueldo2) // sueldos iguales.
				{
					retorno=0;
				}
			}
	}

	return retorno;
}

/**
 * \brief imprime empleado.
 * \param item puntero a void (direccion de memoria de un empleado)
 * \return -1 si el item es NULL o 0 en caso de imprimir.
 */

int employee_funcionCriterio2 (void* item)
{
	int retorno=-1;
	char auxiliarNombre[2048];
	int auxiliarHsTrabajadas;
	int auxiliarId;
	int auxiliarSueldo;
	Employee* empleado;

	if(item != NULL)
	{
		empleado=item; // le asigno a un empleado esa direccion para poder acceder a sus campos con el get.
		employee_getHorasTrabajadas(empleado,&auxiliarHsTrabajadas);
		employee_getId(empleado,&auxiliarId);
		employee_getNombre(empleado,auxiliarNombre);
		employee_getSueldo(empleado,&auxiliarSueldo);
		printf("ID: %d | Nombre: %s | Sueldo: %d | Horas Trabajadas: %d \n",auxiliarId,auxiliarNombre,auxiliarSueldo,auxiliarHsTrabajadas);
		retorno = 0;
	}

	return retorno;
}

/**
 * \brief determina si un empleado cobra mas de 25000-
 * \param item puntero a void (direccion de memoria de un empleado)
 * \return 0 si cobra mas de 25000 0 1 si cobra menos de 25000
 */
int employee_funcionCriterioSueldo (void* item)
{
	int returnAux=-1;
	Employee* empleado;
	int sueldo;


	if(item!=NULL)
	{
		empleado= (Employee*)item;
		employee_getSueldo(empleado,&sueldo);
		if(sueldo <= 25000) //si el sueldo es menor (o igual) que 25000 lo dejo en la lista.
		{
			returnAux=0;
		}
		else // sino lo saco
		{
			returnAux=1;
		}
	}

	return returnAux;
}
/**
 * \brief determina si un empleado trabaja menos de 150 hs
 * \param item puntero a void (direccion de memoria de un empleado)
 * \return 0 si trabaja menos de 150hs o 1 si trabaja mas de 150 hs.
 */
int employee_funcionCriterioHoras (void* item)
{
	int returnAux=-1;
	Employee* empleado;
	int horas;


	if(item!=NULL) // veoq ue el item sea distinto de null
	{
		empleado= (Employee*)item; // casteo ese elemento en un empleado.
		employee_getHorasTrabajadas(empleado,&horas);  // leo las horas que trabaja
		if(horas <= 150) //si las horas trabadas son menos 150, lo dejo
		{
			returnAux=0;
		}
		else // sino lo saco
		{
			returnAux=1;
		}
	}

	return returnAux;
}
