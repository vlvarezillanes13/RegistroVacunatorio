#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//estructura para dosis

struct dosis {
    int fechaDia;
    int fechaMes;
    int fechaAnno;
    char tipo[20];

};

//estrutura de una persona

struct personas {
    char rut[20];
    char nombre[20];
    char apellido[20];
    char sexo[1];
    int edad;
    struct dosis *primera;
    struct dosis *segunda;
    struct dosis *tercera;
    struct personas *enlace;
};

//Tipos de Vacuna

char s[] = "Sinovac";
char p[] = "Pfizer";
char a[] = "AstraZeneca";
char c[] = "Cansino";
char j[] = "Janssen";
char g[] = "Generium";
char m[] = "Moderna";
char sp[] = "SinoPharm";

//Tipos de Sexo
char F[] = "F";
char M[] = "M";

//Función para validar que el rut no este repetido

int validarRepetido(struct personas *ptr, struct personas *persona) {
    if (ptr == NULL) {
        return 0;
    } else {
        while (ptr != NULL) {
            if (strcmp(ptr->rut, persona->rut) == 0) {
                return 1;
            } else {
                ptr = ptr->enlace;
            }
        }
        return 0;
    }
}

//Funcion para ingreso de la persona

struct personas * ingresar_persona(struct personas *ptr) {

    //Puntero de inicio de los registros
    struct personas *inicio, *persona, *validarRut;
    struct dosis * dosi;
    validarRut = ptr;

    //Crea espacio de memoria para una persona
    persona = (struct personas *) malloc(sizeof ( struct personas));
    persona->enlace = NULL;
    persona->segunda = NULL;
    persona->tercera = NULL;
    //---------------------------------------------------------------------------
    printf("Ingrese rut de la persona: ");
    scanf("%s", persona->rut);
    while (strlen(persona->rut) < 9 || strlen(persona->rut) > 10 || validarRepetido(validarRut, persona) == 1) {
        printf("Rut ingresado incorrecto!!\n");
        if (validarRepetido(validarRut, persona) == 1) {
            printf("Rut repetido!!\n");
        }
        printf("Ingrese nuevamente rut: ");
        scanf("%s", persona->rut);
    }
    //---------------------------------------------------------------------------
    printf("Ingrese nombre de la persona: ");
    scanf("%s", persona->nombre);
    while (strlen(persona->nombre) < 1) {
        printf("Nombre incorrecto!!\n");
        printf("Ingrese nuevamente nombre de la persona: ");
        scanf("%s", persona->nombre);
    }
    //---------------------------------------------------------------------------
    printf("Ingrese apellido de la persona: ");
    scanf("%s", persona->apellido);
    while (strlen(persona->apellido) < 1) {
        printf("Apellido incorrecto!!\n");
        printf("Ingrese nuevamente apellido de la persona: ");
        scanf("%s", persona->apellido);
    }
    //---------------------------------------------------------------------------
    printf("Ingrese sexo de la persona: ");
    scanf("%s", persona->sexo);
    *persona->sexo = toupper(*persona->sexo);
    while (strcmp(persona->sexo, F) != 0 && strcmp(persona->sexo, M) != 0) {
        printf("Sexo incorrecto!!\n");
        printf("Ingrese nuevamente sexo de la persona: ");
        scanf("%s", persona->sexo);
        *persona->sexo = toupper(*persona->sexo);
    }
    //---------------------------------------------------------------------------
    printf("Ingrese edad de la persona: ");
    scanf("%d", &persona->edad);
    while (persona->edad < 0 || persona->edad > 100) {
        printf("Edad incorrecto!!\n");
        printf("Ingrese nuevamente edad de la persona: ");
        scanf("%d", &persona->edad);
    }
    //---------------------------------------------------------------------------
    dosi = (struct dosis *) malloc(sizeof ( struct dosis));
    printf("Ingrese fecha año de la vacunacion: ");
    scanf("%d", &dosi->fechaAnno);
    //Toma como inicio vacunación desde 2019 hasta 2021
    while (dosi->fechaAnno < 2018 || dosi->fechaAnno > 2021) {
        printf("Año incorrecto!!\n");
        printf("Ingrese nuevamente año de la vacunacion: ");
        scanf("%d", &dosi->fechaAnno);
    }

    printf("Ingrese fecha N° del mes de la vacunacion: ");
    scanf("%d", &dosi->fechaMes);
    //Toma como inicio vacunación desde 01 hasta 12
    while (dosi->fechaMes < 1 || dosi->fechaMes > 12) {
        printf("Mes incorrecto!!\n");
        printf("Ingrese nuevamente mes de la vacunacion: ");
        scanf("%d", &dosi->fechaMes);
    }

    printf("Ingrese fecha N° del día de la vacunacion: ");
    scanf("%d", &dosi->fechaDia);
    //Toma como inicio vacunación desde 01 hasta 30 por mes
    while (dosi->fechaDia < 1 || dosi->fechaDia > 30) {
        printf("Día incorrecto!!\n");
        printf("Ingrese nuevamente día de la vacunacion: ");
        scanf("%d", &dosi->fechaDia);
    }
    //---------------------------------------------------------------------------
    printf("Ingrese tipo de la vacuna (Sinovac, Pfizer, AstraZeneca, Cansino, Janssen, Generium, Moderna, SinoPharm): ");
    scanf("%s", dosi->tipo);

    while (strcmp(dosi->tipo, s) != 0 && strcmp(dosi->tipo, p) != 0 && strcmp(dosi->tipo, a) != 0 && strcmp(dosi->tipo, c) != 0 && strcmp(dosi->tipo, j) != 0 && strcmp(dosi->tipo, g) != 0 && strcmp(dosi->tipo, m) != 0 && strcmp(dosi->tipo, sp) != 0) {
        printf("Tipo incorrecto!!\n");
        printf("Ingrese nuevamente tipo de la vacuna(Sinovac, Pfizer, AstraZeneca, Cansino, Janssen, Generium, Moderna, SinoPharm): ");
        scanf("%s", dosi->tipo);
    }

    persona->primera = dosi;
    //---------------------------------------------------------------------------
    if (ptr == NULL) {
        ptr = persona;
        inicio = ptr;
    } else {
        inicio = ptr;
        while (ptr->enlace != NULL) {
            ptr = ptr->enlace;
        }
        ptr->enlace = persona;
    }

    return inicio;
}

//Función para actualizar datos de una persona

void actualizar_persona(struct personas *ptr) {
    char rut_act[10];
    struct dosis *dosi;

    printf("Ingrese rut a actualizar: ");
    scanf("%s", rut_act);
    while (strlen(rut_act) < 9 || strlen(rut_act) > 10) {
        printf("Rut incorrecto\n");
        printf("Vuelva a ingresar rut: ");
        scanf("%s", rut_act);
    }

    while (ptr != NULL) {
        if (strcmp(ptr->rut, rut_act) == 0) {
            if (ptr->primera != NULL && ptr->segunda == NULL && ptr->tercera == NULL) {
                printf("Ya posee la primera dosis\n");
                printf("Primera dosis vacunado el %d/%d/%d \n", ptr->primera->fechaDia, ptr->primera->fechaMes, ptr->primera->fechaAnno);
                printf("Tipo: %s\n", ptr->primera->tipo);

                dosi = (struct dosis *) malloc(sizeof ( struct dosis));
                printf("Ingrese fecha año de la vacunacion: ");
                scanf("%d", &dosi->fechaAnno);
                while (dosi->fechaAnno < 2018 || dosi->fechaAnno > 2021 || dosi->fechaAnno < ptr->primera->fechaAnno) {
                    printf("Año incorrecto!!\n");
                    printf("Ingrese nuevamente año de la vacunacion: ");
                    scanf("%d", &dosi->fechaAnno);
                }

                printf("Ingrese fecha N° del mes de la vacunacion: ");
                scanf("%d", &dosi->fechaMes);
                //Toma como inicio vacunación desde 01 hasta 12
                while (dosi->fechaMes < 1 || dosi->fechaMes > 12 || (dosi->fechaAnno == ptr->primera->fechaAnno && dosi->fechaMes < ptr->primera->fechaMes)) {
                    printf("Mes incorrecto!!\n");
                    printf("Ingrese nuevamente mes de la vacunacion: ");
                    scanf("%d", &dosi->fechaMes);
                }

                printf("Ingrese fecha N° del día de la vacunacion: ");
                scanf("%d", &dosi->fechaDia);
                //Toma como inicio vacunación desde 01 hasta 31 por mes
                while (dosi->fechaDia < 1 || dosi->fechaDia > 31 || (dosi->fechaAnno == ptr->primera->fechaAnno && dosi->fechaMes == ptr->primera->fechaMes && dosi->fechaDia <= ptr->primera->fechaDia)) {
                    printf("Día incorrecto!!\n");
                    printf("Ingrese nuevamente día de la vacunacion: ");
                    scanf("%d", &dosi->fechaDia);
                }
                //---------------------------------------------------------------------------
                printf("Ingrese tipo de la vacuna (Sinovac, Pfizer, AstraZeneca, Cansino, Janssen, Generium, Moderna, SinoPharm): ");
                scanf("%s", dosi->tipo);
                while (strcmp(dosi->tipo, s) != 0 && strcmp(dosi->tipo, p) != 0 && strcmp(dosi->tipo, a) != 0 && strcmp(dosi->tipo, c) != 0 && strcmp(dosi->tipo, j) != 0 && strcmp(dosi->tipo, g) != 0 && strcmp(dosi->tipo, m) != 0 && strcmp(dosi->tipo, sp) != 0) {
                    printf("Tipo incorrecto!!\n");
                    printf("Ingrese nuevamente tipo de la vacuna(Sinovac, Pfizer, AstraZeneca, Cansino, Janssen, Generium, Moderna, SinoPharm): ");
                    scanf("%s", dosi->tipo);
                }

                ptr->segunda = dosi;
                printf("Actualizado");

            } else if (ptr->primera != NULL && ptr->segunda != NULL && ptr->tercera == NULL) {
                printf("Ya posee la primera y segunda dosis\n");

                printf("Primera dosis vacunado el %d/%d/%d \n", ptr->primera->fechaDia, ptr->primera->fechaMes, ptr->primera->fechaAnno);
                printf("Tipo: %s\n", ptr->primera->tipo);

                printf("Segunda dosis vacunado el %d/%d/%d \n", ptr->segunda->fechaDia, ptr->segunda->fechaMes, ptr->segunda->fechaAnno);
                printf("Tipo: %s\n", ptr->segunda->tipo);

                dosi = (struct dosis *) malloc(sizeof ( struct dosis));
                printf("Ingrese fecha año de la vacunacion: ");
                scanf("%d", &dosi->fechaAnno);
                while (dosi->fechaAnno < 2018 || dosi->fechaAnno > 2021 || dosi->fechaAnno < ptr->segunda->fechaAnno) {
                    printf("Año incorrecto!!\n");
                    printf("Ingrese nuevamente año de la vacunacion: ");
                    scanf("%d", &dosi->fechaAnno);
                }

                printf("Ingrese fecha N° del mes de la vacunacion: ");
                scanf("%d", &dosi->fechaMes);
                //Toma como inicio vacunación desde 01 hasta 12
                while (dosi->fechaMes < 1 || dosi->fechaMes > 12 || (dosi->fechaAnno == ptr->segunda->fechaAnno && dosi->fechaMes < ptr->segunda->fechaMes)) {
                    printf("Mes incorrecto!!\n");
                    printf("Ingrese nuevamente mes de la vacunacion: ");
                    scanf("%d", &dosi->fechaMes);
                }

                printf("Ingrese fecha N° del día de la vacunacion: ");
                scanf("%d", &dosi->fechaDia);
                //Toma como inicio vacunación desde 01 hasta 30 por mes
                while (dosi->fechaDia < 1 || dosi->fechaDia > 30 || (dosi->fechaAnno == ptr->segunda->fechaAnno && dosi->fechaMes == ptr->segunda->fechaMes && dosi->fechaDia <= ptr->segunda->fechaDia)) {
                    printf("Día incorrecto!!\n");
                    printf("Ingrese nuevamente día de la vacunacion: ");
                    scanf("%d", &dosi->fechaDia);
                }
                //---------------------------------------------------------------------------
                printf("Ingrese tipo de la vacuna (Sinovac, Pfizer, AstraZeneca, Cansino, Janssen, Generium, Moderna, SinoPharm): ");
                scanf("%s", dosi->tipo);
                while (strcmp(dosi->tipo, s) != 0 && strcmp(dosi->tipo, p) != 0 && strcmp(dosi->tipo, a) != 0 && strcmp(dosi->tipo, c) != 0 && strcmp(dosi->tipo, j) != 0 && strcmp(dosi->tipo, g) != 0 && strcmp(dosi->tipo, m) != 0 && strcmp(dosi->tipo, sp) != 0) {
                    printf("Tipo incorrecto!!\n");
                    printf("Ingrese nuevamente tipo de la vacuna(Sinovac, Pfizer, AstraZeneca, Cansino, Janssen, Generium, Moderna, SinoPharm): ");
                    scanf("%s", dosi->tipo);
                }
                ptr->tercera = dosi;
                printf("Actualizado");
            } else {
                printf("Persona ya tiene todas las vacunas!!\n");
            }
            return;
        }
        ptr = ptr->enlace;

    }
    printf("Rut ingresado no encontrado!!\n");
}

//Funcion para mostrar vacunado primera dosis

void mostrar_primera_dosis(struct personas *ptr) {
    printf("Personas registradas Primera dosis: \n");
    while (ptr != NULL) {
        if (ptr->primera != NULL && ptr->segunda == NULL && ptr->tercera == NULL) {
            printf("Rut: %s\n", ptr->rut);
            printf("Nombre: %s\n", ptr->nombre);
            printf("Apellido: %s\n", ptr->apellido);
            if (strcmp(ptr->sexo, F) == 0) {
                printf("Sexo: Femenino\n");
            } else {
                printf("Sexo: Masculino\n");
            }
            //printf("%s\n", ptr->sexo);
            printf("Edad: %d\n", ptr->edad);
            if (ptr->primera != NULL) {

                printf("Primera dosis vacunado el %d/%d/%d \n", ptr->primera->fechaDia, ptr->primera->fechaMes, ptr->primera->fechaAnno);
                printf("Tipo: %s\n", ptr->primera->tipo);

            } else {
                printf("Sin Primera Vacuna\n");
            }

            if (ptr->segunda != NULL) {

                printf("Segunda dosis vacunado el %d/%d/%d \n", ptr->segunda->fechaDia, ptr->segunda->fechaMes, ptr->segunda->fechaAnno);
                printf("Tipo: %s\n", ptr->segunda->tipo);
            } else {
                printf("Sin Segunda Vacuna\n");
            }

            if (ptr->tercera != NULL) {

                printf("Tercera dosis vacunado el %d/%d/%d \n", ptr->tercera->fechaDia, ptr->tercera->fechaMes, ptr->tercera->fechaAnno);
                printf("Tipo: %s\n", ptr->tercera->tipo);
            } else {
                printf("Sin Tercera Vacuna\n");
            }
            printf("\n");
        }
        ptr = ptr->enlace;
    }
}

//Funcion para mostrar vacunado primera y segunda dosis

void mostrar_segunda_dosis(struct personas *ptr) {
    printf("Personas registradas Primera y Segunda dosis: \n");
    while (ptr != NULL) {
        if (ptr->primera != NULL && ptr->segunda != NULL && ptr->tercera == NULL) {
            printf("Rut: %s\n", ptr->rut);
            printf("Nombre: %s\n", ptr->nombre);
            printf("Apellido: %s\n", ptr->apellido);
            if (strcmp(ptr->sexo, F) == 0) {
                printf("Sexo: Femenino\n");
            } else {
                printf("Sexo: Masculino\n");
            }
            printf("Edad: %d\n", ptr->edad);
            if (ptr->primera != NULL) {
                printf("Primera dosis vacunado el %d/%d/%d \n", ptr->primera->fechaDia, ptr->primera->fechaMes, ptr->primera->fechaAnno);
                printf("Tipo: %s\n", ptr->primera->tipo);
            } else {
                printf("Sin Primera Vacuna\n");
            }
            if (ptr->segunda != NULL) {
                printf("Segunda dosis vacunado el %d/%d/%d \n", ptr->segunda->fechaDia, ptr->segunda->fechaMes, ptr->segunda->fechaAnno);
                printf("Tipo: %s\n", ptr->segunda->tipo);
            } else {
                printf("Sin Segunda Vacuna\n");
            }
            if (ptr->tercera != NULL) {
                printf("Tercera dosis vacunado el %d/%d/%d \n", ptr->tercera->fechaDia, ptr->tercera->fechaMes, ptr->tercera->fechaAnno);
                printf("Tipo: %s\n", ptr->tercera->tipo);
            } else {
                printf("Sin Tercera Vacuna\n");
            }
            printf("\n");
        }
        ptr = ptr->enlace;
    }
}

//Funcion para mostrar vacunado primera, segunda y tercera dosis

void mostrar_tercera_dosis(struct personas *ptr) {

    printf("Personas registradas Primera, Segunda y Tercera dosis: \n");
    while (ptr != NULL) {
        if (ptr->primera != NULL && ptr->segunda != NULL && ptr->tercera != NULL) {
            printf("Rut: %s\n", ptr->rut);
            printf("Nombre: %s\n", ptr->nombre);
            printf("Apellido: %s\n", ptr->apellido);
            if (strcmp(ptr->sexo, F) == 0) {
                printf("Sexo: Femenino\n");
            } else {
                printf("Sexo: Masculino\n");
            }
            //printf("%s\n", ptr->sexo);
            printf("Edad: %d\n", ptr->edad);
            if (ptr->primera != NULL) {

                printf("Primera dosis vacunado el %d/%d/%d \n", ptr->primera->fechaDia, ptr->primera->fechaMes, ptr->primera->fechaAnno);
                printf("Tipo: %s\n", ptr->primera->tipo);

            } else {
                printf("Sin Primera Vacuna\n");
            }

            if (ptr->segunda != NULL) {

                printf("Segunda dosis vacunado el %d/%d/%d \n", ptr->segunda->fechaDia, ptr->segunda->fechaMes, ptr->segunda->fechaAnno);
                printf("Tipo: %s\n", ptr->segunda->tipo);
            } else {
                printf("Sin Segunda Vacuna\n");
            }

            if (ptr->tercera != NULL) {

                printf("Tercera dosis vacunado el %d/%d/%d \n", ptr->tercera->fechaDia, ptr->tercera->fechaMes, ptr->tercera->fechaAnno);
                printf("Tipo: %s\n", ptr->tercera->tipo);
            } else {
                printf("Sin Tercera Vacuna\n");
            }
            printf("\n");
        }
        ptr = ptr->enlace;
    }
}

//Funcion para mostrar vacunado según dosis

void mostrar_dosis(struct personas *ptr) {

    if (ptr == NULL) {
        printf("No hay personas registradas...");
    } else {
        int opc;
        printf("Motrar según: \n");
        printf("1.- Primera Dosis \n");
        printf("2.- Primera y Segunda Dosis \n");
        printf("3.- Primera, Segunda y Tercera Dosis \n");
        printf("Ingrese opción: ");
        scanf("%d", &opc);
        if (opc == 1) {
            mostrar_primera_dosis(ptr);
        } else if (opc == 2) {
            mostrar_segunda_dosis(ptr);
        } else if (opc == 3) {
            mostrar_tercera_dosis(ptr);
        } else {
            printf("Opción incorrecta\n");
        }
    }
}

//Función para buscar según sexo

void buscar_sexo(struct personas *ptr) {
    if (ptr == NULL) {
        printf("No hay personas registradas...");
    } else {
        char sex[1];
        printf("Ingrese condición de sexo (F o M): ");
        scanf("%s", sex);
        *sex = toupper(*sex);
        while (strcmp(sex, F) != 0 && strcmp(sex, M) != 0) {
            printf("Sexo incorrecto!!\n");
            printf("Ingrese nuevamente sexo de la persona: ");
            scanf("%s", sex);
            *sex = toupper(*sex);
        }

        printf("Personas registradas: \n");
        while (ptr != NULL) {
            if (strcmp(sex, ptr->sexo) == 0) {
                printf("Rut: %s\n", ptr->rut);
                printf("Nombre: %s\n", ptr->nombre);
                printf("Apellido: %s\n", ptr->apellido);
                if (strcmp(ptr->sexo, F) == 0) {
                    printf("Sexo: Femenino\n");
                } else {
                    printf("Sexo: Masculino\n");
                }
                printf("Edad: %d\n", ptr->edad);
                if (ptr->primera != NULL) {
                    printf("Primera dosis vacunado el %d/%d/%d \n", ptr->primera->fechaDia, ptr->primera->fechaMes, ptr->primera->fechaAnno);
                    printf("Tipo: %s\n", ptr->primera->tipo);

                } else {
                    printf("Sin Primera Vacuna\n");
                }

                if (ptr->segunda != NULL) {
                    printf("Segunda dosis vacunado el %d/%d/%d \n", ptr->segunda->fechaDia, ptr->segunda->fechaMes, ptr->segunda->fechaAnno);
                    printf("Tipo: %s\n", ptr->segunda->tipo);
                } else {
                    printf("Sin Segunda Vacuna\n");
                }

                if (ptr->tercera != NULL) {
                    printf("Tercera dosis vacunado el %d/%d/%d \n", ptr->tercera->fechaDia, ptr->tercera->fechaMes, ptr->tercera->fechaAnno);
                    printf("Tipo: %s\n", ptr->tercera->tipo);
                } else {
                    printf("Sin Tercera Vacuna\n");
                }
                printf("\n");
            }
            ptr = ptr->enlace;
        }
    }
}

//Función para buscar según rut

void buscar_rut(struct personas *ptr) {

    if (ptr == NULL) {
        printf("No hay personas registradas...");
    } else {
        char rut_buscar[10];
        printf("Ingrese rut a buscar: ");
        scanf("%s", rut_buscar);
        while (strlen(rut_buscar) < 9 || strlen(rut_buscar) > 10) {
            printf("Rut incorrecto\n");
            printf("Vuelva a ingresar rut: ");
            scanf("%s", rut_buscar);
        }

        while (ptr != NULL) {
            if (strcmp(ptr->rut, rut_buscar) == 0) {
                printf("Rut: %s\n", ptr->rut);
                printf("Nombre: %s\n", ptr->nombre);
                printf("Apellido: %s\n", ptr->apellido);
                if (strcmp(ptr->sexo, F) == 0) {
                    printf("Sexo: Femenino\n");
                } else {
                    printf("Sexo: Masculino\n");
                }
                //printf("%s\n", ptr->sexo);
                printf("Edad: %d\n", ptr->edad);
                if (ptr->primera != NULL) {
                    printf("Primera dosis vacunado el %d/%d/%d \n", ptr->primera->fechaDia, ptr->primera->fechaMes, ptr->primera->fechaAnno);
                    printf("Tipo: %s\n", ptr->primera->tipo);

                } else {
                    printf("Sin Primera Vacuna\n");
                }

                if (ptr->segunda != NULL) {
                    printf("Segunda dosis vacunado el %d/%d/%d \n", ptr->segunda->fechaDia, ptr->segunda->fechaMes, ptr->segunda->fechaAnno);
                    printf("Tipo: %s\n", ptr->segunda->tipo);
                } else {
                    printf("Sin Segunda Vacuna\n");
                }

                if (ptr->tercera != NULL) {
                    printf("Tercera dosis vacunado el %d/%d/%d \n", ptr->tercera->fechaDia, ptr->tercera->fechaMes, ptr->tercera->fechaAnno);
                    printf("Tipo: %s\n", ptr->tercera->tipo);
                } else {
                    printf("Sin Tercera Vacuna\n");
                }
                return;
            }

            ptr = ptr->enlace;
        }

        printf("No se encontro Persona");
    }
}

//Función Principal

int main() {

    struct personas *inicio = NULL;
    int opcion;

    do {
        printf("\n\n                  Vacunacion Minsal                      \n");
        printf("-------------------------------------------------------------\n");
        printf("Opción = 1 ---> Ingresar una persona \n");
        printf("Opción = 2 ---> Actualizar vacunación \n");
        printf("Opción = 3 ---> Mostrar personas según dosis \n");
        printf("Opción = 4 ---> Buscar según sexo \n");
        printf("Opción = 5 ---> Buscar según rut \n");
        printf("Opción = 0 ---> Salir de la atención clientes \n");
        printf("Ingrese opción: ");
        scanf("%d", &opcion);
        if (opcion == 1) {
            inicio = ingresar_persona(inicio);
            fflush(stdin);
            getchar();
        } else if (opcion == 2) {
            actualizar_persona(inicio);
            fflush(stdin);
            getchar();
        } else if (opcion == 3) {
            mostrar_dosis(inicio);
            fflush(stdin);
            getchar();
        } else if (opcion == 4) {
            buscar_sexo(inicio);
            fflush(stdin);
            getchar();
        } else if (opcion == 5) {
            buscar_rut(inicio);
            fflush(stdin);
            getchar();
        } else {
            printf("Opción Salida/Incorrecta \n");
        }

    } while (opcion != 0);

    return (EXIT_SUCCESS);
}

