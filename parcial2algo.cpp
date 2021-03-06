#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

typedef struct {
    int codigoempleado;
    char nom [41],apellido [41],puesto [41], descripcion[41];
    float sueldo;
} templeado;


void continuar()
{
    printf("Presione una tecla para continuar\n\n");
    getch();
}

void crear()
{
    FILE *arch;
    arch=fopen("empleados.dat","wb");
    if (arch==NULL)
        exit(1);
    fclose(arch);
    continuar();
}


void cargar()
{
    FILE *arch;
    arch=fopen("empleados.dat","ab");
    if (arch==NULL)
        exit(1);
    templeado empleado;
    printf("Ingrese el codigo de empleado:");
    scanf("%i",&empleado.codigoempleado);
    fflush(stdin);
    printf("Ingrese el nombre del empleado:");
    gets(empleado.nom);
    printf("Ingrese el apellido del empleado:");
    gets(empleado.apellido);
    printf("Ingrese el puesto del empleado:");
    gets(empleado.puesto);
    printf("Ingrese sueldo:");
    scanf("%f",&empleado.sueldo);
    fwrite(&empleado, sizeof(templeado), 1, arch);
    fclose(arch);
    continuar();
}

void listado()
{
    FILE *arch;
    arch=fopen("empleados.dat","rb");
    if (arch==NULL)
        exit(1);
    templeado empleado;
    fread(&empleado, sizeof(templeado), 1, arch);
    while(!feof(arch))
    {
        printf("%i %s %0.2f\n", empleado.codigoempleado, empleado.nom,empleado.apellido,empleado.puesto, empleado.sueldo);
        fread(&empleado, sizeof(templeado), 1, arch);
    }
    fclose(arch);
    continuar();
}

void consulta()
{
    FILE *arch;
    arch=fopen("empleados.dat","rb");
    if (arch==NULL)
        exit(1);
    printf("Ingrese el codigo de empleado a consultar:");
    int cod;
    scanf("%i", &cod);
    templeado empleado;
    int existe=0;
    fread(&empleado, sizeof(templeado), 1, arch);
    while(!feof(arch))
    {
        if (cod==empleado.codigoempleado)
        {
           printf("%i %s %0.2f\n", empleado.codigoempleado, empleado.nom,empleado.apellido,empleado.puesto, empleado.sueldo);
           existe=1;
           break;
        }
        fread(&empleado, sizeof(templeado), 1, arch);
    }
    if (existe==0)
        printf("No existe un empleado con dicho codigo\n");
    fclose(arch);
    continuar();
}

void modificacion()
{
    FILE *arch;
    arch=fopen("empleados.dat","r+b");
    if (arch==NULL)
        exit(1);
    printf("Ingrese el codigo de empleado a modificar:");
    int cod;
    scanf("%i", &cod);
    templeado empleado;
    int existe=0;
    fread(&empleado, sizeof(templeado), 1, arch);
    while(!feof(arch))
    {
        if (cod==empleado.codigoempleado)
        {
           printf("%i %s %0.2f\n", empleado.codigoempleado, empleado.nom,empleado.apellido,empleado.puesto, empleado.sueldo);
           printf("Ingrese nuevo sueldo:");
           scanf("%f",& empleado.sueldo);
           int pos=ftell(arch)-sizeof(templeado);
           fseek(arch,pos,SEEK_SET);
           fwrite(&empleado, sizeof(templeado), 1, arch);
           printf("Se modifico el sueldo para dicho empleado.\n");
           existe=1;
           break;
        }
        fread(&empleado, sizeof(templeado), 1, arch);
    }
    if (existe==0)
        printf("No existe un empleado con dicho codigo\n");
    fclose(arch);
    continuar();
}

int main()
{
    int opcion;
    do {
        printf("1 - Crear un archivo binario llamado \"empleados.dat\"\n");
        printf("2 - Carga de registros de tipo templeados\n");
        printf("3 - Listado completo de empleados.\n");
        printf("4 - Consulta de un empleado por su codigo.\n");
        printf("5 - Modificacion del sueldo de un empleado. \n");
        printf("6 - Finalizar\n\n");
        printf("Ingrese su opcion:");
        scanf("%i",&opcion);
        switch (opcion) {
            case 1:crear();
                   break;
            case 2:cargar();
                   break;
            case 3:listado();
                   break;
            case 4:consulta();
                   break;
            case 5:modificacion();
                   break;
        }
    } while (opcion!=6);
    return 0;
}
