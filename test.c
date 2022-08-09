#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "exercises.c"


char msg[300];
int test_id = -1;


int success(){
  printf("SUCCESS\n");
  exit(0);
}

void err_msg(char* msg){
    //if(test_id!=-1) return;
    printf("   [FAILED] ");
    printf("%s\n",msg);
    //print_trace();
}

void ok_msg(char* msg){
    //if(test_id!=-1) return;
    printf ("   [OK] ");
    printf("%s\n",msg);
}

void info_msg(char* msg){
    //if(test_id!=-1) return;
    printf ("   [ INFO ] %s\n",msg);
}

int test_suite(int(*test)(), char* msg, int max_score, int id, int req_id){
    if(test_id==-1 || test_id==id){
        printf("\n%s\n", msg);
        int score=test();

        if(id==req_id && score == max_score) success();

        printf("   partial_score: %d/%d\n", score, max_score); 
        
        return score;
    }
    return 0;
}


/*************  TESTS  ******************/
int test_suma(){
    int* res = (int*) malloc(sizeof(int));

    int k;
    for(k=0;k<5;k++){
        int i=rand()%100;
        int j=rand()%100;
        sprintf(msg,"suma(%d,%d,res)",i,j);
        info_msg(msg);

        suma(i,j, res);
        if(*res!=i+j){
            sprintf (msg,"res==%d",*res);
            err_msg(msg);
            return 0;
        }
    }
    ok_msg("Funcion suma");
    return 10;  
}

int test_suma_n(){
    int* res = (int*) malloc(sizeof(int));
    int* a = (int*) malloc(sizeof(int)*10);
    
    int i; int m=rand()%10+1;
    int tot=0;
    sprintf(msg,"a=[");
    for(i=0; i<10; i++){
        a[i]=rand()%100;
        if(i>=10-m) tot +=a[i];
        sprintf(msg,"%.50s %d,",msg,a[i]);
    }
    sprintf(msg,"%.50s]",msg);
    info_msg(msg);

    sprintf(msg,"m=%d",m);
    info_msg(msg);

    info_msg("sumaNultimos(a, 10, m, res)");
    sumaNultimos(a, 10, m, res);

    if(tot!=*res){
        sprintf(msg,"deberia dar:%d, pero dio:%d",tot,*res);
        err_msg(msg);
        return 0;
    }

    ok_msg("sumaNultimos");
    return 10;
}

char nombre[30]; int edad;
int test_creaP(){
    Persona* p=crearPersona(nombre, "15489XXX-2", edad);
    sprintf(msg, "p=crearPersona(\"%s\", \"15489XXX-2\", %d)", nombre, edad);
    info_msg(msg);

    if(p==NULL){
        err_msg("p es NULL"); return 0;
    }

    if(strcmp(p->nombre,nombre)!=0){
        sprintf(msg,"p->nombre=%s",p->nombre);
        err_msg(msg);
        return 0;
    }

    if(p->edad!=edad){
        sprintf(msg,"p->edad=%d",p->edad);
        err_msg(msg);
        return 0;
    }

    ok_msg("crearPersona");
    return 10;
}

int test_creaV(){
    int size=rand()%10+1;
    sprintf(msg,"v=crearVector(%d)",size);
    info_msg(msg);
    Vector *v = crearVector(size);
    if(v ==NULL){
        err_msg("v es NULL"); return 0;
    }
    if(v->capacidad != size){
        err_msg("capcaidad no fue inicalizada correctamente"); return 0;
    }
    int i;
    for(i=0;i<size;i++){
        if(v->datos[i] != 0){
            err_msg("datos del vector deben ser inicializados en 0"); 
            return 0;
        }
    }

    ok_msg("crearVector");
    return 10;

}

int test_asignarObtenerValor(){
    int a=rand()%10, b=rand()%20, c=rand()%30;
    sprintf(msg,"Creando el vector (%d,%d,%d)",a,b,c);
    info_msg(msg);
    Vector *v = (Vector*)malloc(sizeof(Vector));
    v->datos = (int *)calloc(3, sizeof(int));
    v->capacidad = 3;
    asignarValor(v, 0, a);
    asignarValor(v, 1, b);
    asignarValor(v, 2, c);
    info_msg("Obteniendo el primer valor del vector: obtenerValor(v,0)");
    int val=obtenerValor(v,0);
    if(a!=val){
        sprintf(msg,"Valor obtenido no corresponde (%d)", val);
        err_msg(msg);
        return 0;
    }

    info_msg("Obteniendo el primer valor del vector: obtenerValor(v,2)");
    val=obtenerValor(v,2);
    if(c!=val){
        sprintf(msg,"Valor obtenido no corresponde (%d)", val);
        err_msg(msg);
        return 0;
    }

    ok_msg("AsignarValor");
    ok_msg("ObtenerValor");
    return 10;
}

int test_sumaV(){
    int a=rand()%10, b=rand()%20, c=rand()%30;
    int suma=a,sumb=b,sumc=c;
    sprintf(msg,"Creando el vector v1=(%d,%d,%d)",a,b,c);
    info_msg(msg);

    Vector *v1 = (Vector*)malloc(sizeof(Vector));
    v1->datos = (int *)calloc(3, sizeof(int));
    v1->capacidad = 3;

    v1->datos[0]=a; v1->datos[1]=b; v1->datos[2]=c;

    a=rand()%10; b=rand()%20; c=rand()%30;
    suma+=a; sumb+=b; sumc+=c;
    sprintf(msg,"Creando el vector v2=(%d,%d,%d)",a,b,c);
    info_msg(msg);
    Vector *v2 = (Vector*)malloc(sizeof(Vector));
    v2->datos = (int *)calloc(3, sizeof(int));
    v2->capacidad = 3;

    v2->datos[0]=a; v2->datos[1]=b; v2->datos[2]=c;

    info_msg("Creando vector v3 con 3 elementos");
    Vector *v3 = (Vector*)malloc(sizeof(Vector));
    v3->datos = (int *)calloc(3, sizeof(int));
    v3->capacidad = 3;

    sumaV(v1, v2, v3);
    info_msg("sumaV(v1, v2, v3)");
    if(suma!=v3->datos[0] || sumb!=v3->datos[1] || sumc!=v3->datos[2]){
        sprintf(msg,"Suma no correcta: (%d,%d,%d)",v3->datos[0],v3->datos[1],v3->datos[2]);
        err_msg(msg);
        return 0;
    }

    ok_msg("sumaV");
    return 10;

}

int test_sumaV2(){
    Vector *c = (Vector*)malloc(sizeof(Vector));
    c->datos = (int *)calloc(2, sizeof(int));
    c->capacidad = 2;
    int a1=rand()%10, a2=rand()%20, b1=rand()%30, b2=rand()%40;
    sprintf(msg,"a1=%d,a2=%d,b1=%d,b2=%d",a1,a2,b1,b2);
    info_msg(msg);
    sumaV2(a1,a2,b1,b2,c);

    if(c->datos[0]!=a1+b1 || c->datos[1]!=a2+b2){
        sprintf(msg,"suma incorrecta, c=(%d,%d)",c->datos[0],c->datos[1]);
        err_msg(msg);
        return 0;
    }

    ok_msg("sumaV2");
    return 10;
}


int main( int argc, char *argv[] ) {
    
    if(argc>1) test_id=atoi(argv[1]);
    srand(time(NULL));

    int total_score=0;
    total_score+=test_suite(test_suma, "Test Suma...", 10, 0, test_id);
    total_score+=test_suite(test_suma_n, "Test SumaNultimos...", 10, 0, test_id);
    strcpy(nombre,"Ignacio"); edad=38;
    total_score+=test_suite(test_creaP, "Test CreaPersona...", 10, 0, test_id);
    total_score+=test_suite(test_creaV, "Test CreaVector...", 10, 0, test_id);
    total_score+=test_suite(test_asignarObtenerValor, "Test AsignarValor, ObtenerValor...", 10, 0, test_id);
    total_score+=test_suite(test_sumaV, "Test Suma de vectores...", 10, 0, test_id);
    total_score+=test_suite(test_sumaV2, "Test Suma de vectores2...", 10, 0, test_id);


    if(argc==1)
      printf("\ntotal_score: %d/70\n", total_score);

    

    return 0;
}
