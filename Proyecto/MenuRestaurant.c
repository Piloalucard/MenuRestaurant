//Proyecto Michell
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <setjmp.h>
#include <string.h>

struct comida{
	char nombre[32];
	int id;
	float precio;
};

int tam = 100;
int cuenta = 0;
char nombre[64] = "NOMBRE GENERICO";
struct comida cmd[tam];    

void clear()
{
	printf("\n");
	system("pause");
	system("cls");
}


void inicializar()
{
	for(int i = 0; i < tam; i++)
	{
		cmd[i].id = -1;
		cmd[i].precio = -1;
		cmd[i].nombre[0] = "NULL";
	}
}

float obtenerIngresos()
{
	float ingresos = 0;
	for(int i = 0; i < tam; i++)
	{
		if(cmd[i].id != -1)
		{
			ingresos += cmd[i].precio;
		}
	}
	return ingresos;
}

int obtPos(int id)
{
	for(int i = 0; i < tam; i++)
	{
		if(cmd[i].id == id)
		{
			return i;
		}
	}
	return -1;
}

bool estaLlleno()
{
	for(int i = 0; i < tam; i++)
	{
		if(cmd[i].id == -1)
		{
			return false;
		}
	}
	return true;
}

const char* agregar()
{
	int id;
	float precio;
	char nombre[32];
	printf("Ingrese el nombre de la comida: ");
	scanf("%s", nombre);
	printf("Ingrese el precio de la comida: ");
	scanf("%f", &precio);
	printf("Ingrese el id de la comida: ");
	scanf("%d", &id);
	int pos;
	if(pos=obtPos(id) != -1)
	{
		return "El id ya existe";
	}


	for(int i = 0; i < tam; i++)
	{
		if(cmd[i].id == -1)
		{
			cmd[i].id = id;
			cmd[i].precio = precio;
			strcpy(cmd[i].nombre, nombre);
			return "Comida agregada";
		}
	}

	return "No se pudo agregar la comida";
}

const char* eliminar()
{
	int id;
	printf("Ingrese el id de la comida a eliminar: ");
	scanf("%d", &id);
	int pos;
	if(pos=obtPos(id) != -1)
	{
		cmd[pos].id = -1;
		cmd[pos].precio = -1;
		cmd[pos].nombre[0] = "NULL";
		return "Comida eliminada";
	}
	return "No se pudo eliminar la comida";
}

const char* modificar()
{
	int id;
	printf("Ingrese el id de la comida a modificar: ");
	scanf("%d", &id);
	int pos;
	if(pos=obtPos(id) != -1)
	{
		float precio;
		char nombre[32];
		printf("Ingrese el nuevo nombre de la comida: ");
		scanf("%s", nombre);
		printf("Ingrese el nuevo precio de la comida: ");
		scanf("%f", &precio);
		cmd[pos].precio = precio;
		strcpy(cmd[pos].nombre, nombre);
		return "Comida modificada";
	}
	return "No se pudo modificar la comida";
}

void mostrar()
{
	for(int i = 0; i < tam; i++)
	{
		if(cmd[i].id != -1)
		{
			printf("Nombre: %s\n", cmd[i].nombre);
			printf("Precio: %f\n", cmd[i].precio);
			printf("Id: %d\n", cmd[i].id);
			printf("----------------------------------------------\n");
		}
	}
}

void pedirComida()
{
	int id;
	printf("Ingrese el id de la comida a pedir: ");
	scanf("%d", &id);
	int pos;
	if(pos=obtPos(id) != -1)
	{
		printf("Disfrute su comida\n");
		cuenta += cmd[pos].precio;
	}
	else
	{
		printf("No se pudo pedir la comida\n");
	}
}

void pagar()
{
	float pago=0;
	printf("Su cuenta es de: %f\n", cuenta);
	printf("Cuanto desea pagar: ");
	scanf("%f", &pago);
	if(pago >= cuenta)
	{
		printf("Su cambio es de: %f\n", pago-cuenta);
		cuenta = 0;
	}
	else if(pago <= 0)
	{
		printf("No se pudo pagar la cuenta\n");
	}
	else
	{
		cuenta -= pago;
		printf("Su cuenta ahora es de: %f\n", cuenta);
	}
}

void menuOrdenar()
{
	clear();
	char op = '0';
	while (op != '4')
	{
		printf("1. Ver menu\n");
		printf("2. Pedir comida\n");
		printf("3. Pagar\n");
		printf("4. Salir\n Elige una opcion: ");
		scanf("%c", &op);
		switch (op)
		{
			case '1':
				mostrar();
				clear();
				break;
			case '2':
				pedirComida();
				clear();
				break;
			case '3':
				pagar();
				clear();
				break;
			case '4':
				break;
			default:	
				printf("Opcion invalida\n");
				clear();
				break;
		
		}

		if(op == '4' && cuenta > 0)
		{
			printf("No se puede ir con saldo en la cuenta.\n");
			op = '0';
		}
	}
	
}

void menuAdmin()
{
	clear();
	int pass=7654,pin=0;
	printf(" Ingresa el pin de administrador: ");
	scanf("%i",&pin);
	if(pass != pin)
	{
		printf("PIN incorrecto");
		return;
	}
	char op = '0';
	while(op != '5')
	{
		printf(" !Bienvenido al restaurant %s!\n",nombre);
		printf(" Que desea hacer?\n");
		printf(" 1-Agregar Comida\n");
		printf(" 2-Eliminar Comida\n");
		printf(" 3-Modificar Comida\n");
		printf(" 4-Ver ingresos totales\n");
		printf(" 5-Salir \n Elige tu opcion: ");
		scanf("%c",&op);
		switch(op)
		{
			case '1':
				printf("%s",agregar());
				clear();
				break;
			case '2':
				printf("%s",eliminar());
				clear();
				break;
			case '3':
				printf("%s",modificar());
				clear();
				break;
			case '4':
				printf("Los ingresos totales son: %f",obtenerIngresos());
				clear();
				break;
				
			case '5':
				printf("Adios!");
				clear();
				break;
				
			default:
				printf("Esa no es una opcion valida");
				clear();
				break;
		}
		
	}
	
}

void mainMenu()
{
	char op = '0';
	while(op != '3')
	{

		printf(" !Bienvenido al restaurant %s!\n",nombre);
		printf(" Que apartado desea ver\n");
		printf(" 1-Ordenar de comer\n");
		printf(" 2-Administrador\n");
		printf(" 3-Salir \n Elige tu opcion: ");
		scanf("%c",&op);
		switch(op)
		{
			case '1':
				menuOrdenar();
				clear();
				break;
			case '2':
				menuAdmin();
				clear();
				break;
			case '3':
				printf("Adios!");
				clear();
				break;
				
			default:
				printf("Esa no es una opcion valida");
				clear();
				break;
		}
		
	}
}


int main()
{
	bool HadError=true;
    {
        mainMenu();
        {
            HadError=false;
            goto ExitJmp;
        }

    }
	ExitJmp:
    if(HadError)
    {
        printf("Hubo un error dentro la ejecucion del codigo en mainMenu, Pendejo.\n");
    }
    return 0;
}

