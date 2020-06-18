/*
 * Controller.h
 *
 *  Created on: 16 jun. 2020
 *      Author: Juan
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

int controller_loadFromText(char* path , LinkedList* pArrayListEmployee);
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee);
int controller_addEmployee(LinkedList* pArrayListEmployee);
int controller_editEmployee(LinkedList* pArrayListEmployee);
int controller_removeEmployee(LinkedList* pArrayListEmployee);
int controller_ListEmployee(LinkedList* pArrayListEmployee);
int controller_sortEmployee(LinkedList* pArrayListEmployee);
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee);
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee);

int controller_imprimirLista(LinkedList* listaEmpleados);
int controller_borrarSueldosAltos(LinkedList* listaEmpleados);
int controller_listaSuledos(LinkedList* listaEmpleados,LinkedList* listaEmpleadosDos);
int controller_listaHoras(LinkedList* listaEmpleados,LinkedList* listaEmpleadosDos);

#endif /* CONTROLLER_H_ */
