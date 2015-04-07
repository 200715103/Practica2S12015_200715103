#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef unsigned long long UINT64;
/***Variable Global NodeLista* cabeza***/
struct NodeLista* cabeza;
/***Variable Global node root AVL***/
struct node *root = NULL;
/***Variable Global NodeLista* cola***/
struct NodeLista* cola;

int parametro;
int auxParam;
int datos = 1;
int datos2 = 1;
int datos3 = 1;
int datos4 = 1;

int largoArray;

struct NodeLista* roots;
clock_t inicio;
clock_t inicioAVL;
clock_t inicioBS;
clock_t inicioQS;
clock_t finals;
clock_t finalsAVL;
clock_t finalsBS;
clock_t finalsQS;

//int* arreglo;
//int* auxiliar;
int *auxiliar;
int *arreglo;

int *auxiliar2;



/****************************INICIO AVL**************************************/
struct node{
    int key;
    int height;
    struct node *left;
    struct node *right;
};

// A utility function to get maximum of two integers
int max(int a, int b);

// A utility function to get height of the tree
int height(struct node *N){
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b){
    return (a > b)? a : b;
}

/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct node* newNode(int key){
    struct node* node = (struct node*)
                        malloc(sizeof(struct node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct node *rightRotate(struct node *y){
    struct node *x = y->left;
    struct node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct node *leftRotate(struct node *x){
    struct node *y = x->right;
    struct node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(struct node *N){
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct node* insert(struct node* node, int key){

    /* 1.  Perform the normal BST rotation */
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    /* 2. Update height of this ancestor node */
    node->height = max(height(node->left), height(node->right)) + 1;

    /* 3. Get the balance factor of this ancestor node to check whether
       this node became unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;

}

/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
struct node * minValueNode(struct node* node){
    struct node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

/***Funcion preOrder***/
void preOrder(struct node *root){
    if(root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

/****Funcion inOrder AVL***/
void inOrder(struct node *root,FILE *ingreso, clock_t inicioAVL){

    if(root != NULL)
    {

        inOrder(root->left,ingreso,inicioAVL);
        printf("%d ", root->key);
        inOrder(root->right,ingreso,inicioAVL);
        clock_t aux_f = clock();
        //fprintf(ingreso, "hola %i", datos);
        fprintf(ingreso,"%f %i \n",((aux_f-inicioAVL)/(float)CLOCKS_PER_SEC),datos);
        datos++;
    }

}

/********************************FIN AVL*****************************************/





/************************INICIO METODOS********************************/
void BS(FILE *BSS)
{
    printf("\nIngresando a BS");
    printf("\nEsperando...\n");

int   c, d, e, swap;

printf("\nPasando datos...\n");
printf("\nParametro!!!!...%i\n",parametro);

clock_t inicio;
clock_t clkFinal;
inicio = clock();
for (c = 0 ; c < ( parametro - 1 ); c++)
  {
    for (d = 0 ; d < parametro - c - 1; d++)
    {
      if (auxiliar[d] > auxiliar[d+1]) /* For decreasing order use < */
      {
        swap       = auxiliar[d];
        auxiliar[d]   = auxiliar[d+1];
        auxiliar[d+1] = swap;
      }
    }
    clkFinal = clock();
    fprintf(BSS,"%f %i \n",((clkFinal-inicio)/(float)CLOCKS_PER_SEC),datos3);
    datos3++;
  }


}


void print_BS(){
int ii;
  for (ii=0; ii<parametro; ii++){
        printf("%d ", auxiliar[ii]);}
 printf("\nElementos ordenados Bubble Sort");
}


void quicksortArr(int *x, int first, int last, FILE *QSS){
    int pivot, j, temp, i;
    clock_t inicio;
    clock_t clkFinal;

    inicio = clock();
    if(first<last){
        pivot = first;
        i = first;
        j = last;

        while(i<j){
            while(x[i]<=x[pivot]&&i<last)
                i++;
            while(x[j]>x[pivot])
                j--;
            if(i<j){
                temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }
        temp = x[pivot];
        x[pivot] = x[j];
        x[j] = temp;

        quicksortArr(x, first, j-1,QSS);
        clkFinal = clock();
        fprintf(QSS,"%f %i \n",((clkFinal-inicio)/(float)CLOCKS_PER_SEC),datos4);
        datos4++;

        quicksortArr(x, j+1, last,QSS);
        clkFinal = clock();
        fprintf(QSS,"%f %i \n",((clkFinal-inicio)/(float)CLOCKS_PER_SEC),datos4);
        datos4++;

    }


}


void print_quicksortArr(){
 int ii;
   for (ii=1; ii<parametro+1;ii++){
        printf(" %d", auxiliar2[ii]);}
    printf("\nElementos ordenados Quick Sort");
}

void setArray(int x){
arreglo =(int*)malloc(x*sizeof (int ));
auxiliar =(int*)malloc(x*sizeof (int ));
auxiliar2 =(int*)malloc(x*sizeof (int ));
}

/********************************************************************************/
/***********************************MAIN*****************************************/
/********************************************************************************/
int main()
{

    int contador = 0;
    int tiempo = 0;
    clock_t aux_f;

    int valorArray;
    scanf("%i",&valorArray);
    setArray(valorArray);

//815660
//195090
//2000numeros

    FILE *file;
    file = fopen("C:\\195090.txt","r");

    FILE *INS;
    INS = fopen("C:\\Users\\julio\\Desktop\\Graficas\\Insert.dat","w");

    FILE *ingreso;
    ingreso = fopen("C:\\Users\\julio\\Desktop\\Graficas\\inOrdenAVL.dat","w");

    FILE *BSS;
    BSS = fopen("C:\\Users\\julio\\Desktop\\Graficas\\BSS.dat","w");

    FILE *QSS;
    QSS = fopen("C:\\Users\\julio\\Desktop\\Graficas\\QSS.dat","w");

    char singleLine[1000000];
    if (file == NULL){
        printf("Archivo no encontrado\n");
        return -1;

    }
    else{

    inicio = clock();
    while (!feof(file))
        {

            int i = 0;

            fgets(singleLine,1000000,file);
            //printf(singleLine);

            arreglo[i] = atoi(singleLine);
            auxiliar[contador] = arreglo[i];

            root = insert(root, arreglo[i]);
            aux_f = clock();
            fprintf(INS,"%f %i \n",((aux_f-inicio)/(float)CLOCKS_PER_SEC),datos2);
            contador++;
            parametro++;
            i++;
            datos2++;

        }
        fclose(INS);
    finals = clock();
    fclose(file);

    auxParam = parametro;



    }//fin else
    int iiii;
    for (iiii=0; iiii<parametro;iiii++){
        auxiliar2[iiii] = auxiliar[iiii];

	}


    /************InOrden AVL***************/
    /*inicioAVL = clock();
    if(ingreso!=NULL){
    inOrder(root, ingreso, inicioAVL);
    }
    else{
            printf("error");}
    finalsAVL = clock();
    fclose(ingreso);
    /************InOrden AVL***************/






	/************Ordenar BS***************/
    /*inicioBS = clock();
    BS(BSS);
    print_BS();
    finalsBS = clock();
    fclose(BSS);
    /************Ordenar BS***************/





    /************Ordenar QS***************/
    inicioQS = clock();
    quicksortArr(auxiliar2,0,parametro,QSS);
    print_quicksortArr(QSS);
    finalsQS = clock();
    fclose(QSS);
    /************Ordenar QS***************/





    printf("\nEl tiempo ingresando datos al AVL es: %f ",(float)((finals-inicio)/CLOCKS_PER_SEC));
    printf("\nEl tiempo recorrido InOrden del AVL es: %f ",(float)((finalsAVL-inicioAVL)/CLOCKS_PER_SEC));
    printf("\nEl tiempo ordenando Array BS es: %f ",(float)((finalsBS-inicioBS)/CLOCKS_PER_SEC));
    printf("\nEl tiempo ordenando Array QS es: %f ",(float)((finalsQS-inicioQS)/CLOCKS_PER_SEC));




    printf("\n**************************************************\n");
	printf("\n**************************************************\n");
    printf("valor primero %d , valor ultimo %d ", auxiliar[0], auxiliar[parametro-1]);
    printf("\n**************************************************\n");
	printf("\n**************************************************\n");
    printf("valor primero %d , valor ultimo %d ", auxiliar2[0], auxiliar2[parametro]);


    return 0;
}


/***********************************************************/
/*******************FIN MAIN********************************/
/************************************************************/


