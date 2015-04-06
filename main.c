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


struct NodeLista* roots;
clock_t inicio;
clock_t inicioBS;
clock_t inicioQS;
clock_t finals;
clock_t finalsBS;
clock_t finalsQS;

int arreglo [815660];
int auxiliar[815660];
int auxiliar2[815660];
float total;


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
void inOrder(struct node *root){
    if(root != NULL)
    {

        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

/********************************FIN AVL*****************************************/


/******************INICIO LISTA DOBLE ENLAZADA*************************/
struct NodeLista{
    int data;
    struct NodeLista* siguiente;
    struct NodeLista* anterior;
};

/***Crea Nuevo Nodo y retorna pointer a el mismo***/
struct NodeLista* GetNewNode(int x){
    /***Creacion de nuevoNodo y aloja el espacio en la memoria***/
    struct NodeLista* nuevoNodo = (struct NodeLista*)malloc(sizeof(struct NodeLista));
    nuevoNodo->data = x;
    nuevoNodo->anterior = NULL;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

void Bubblesort(){
    struct NodeLista *tmp, *current, *nextone;
    printf("Bubblesort: ");
    printf("\n");
    int  n, c, d;
    n=195090;
    printf("Procesando...");
    for (c = 0 ; c < ( n - 1 ); c++)
    {   current = cabeza;
        for (d = 0 ; d < n - c - 1; d++)
        {
            if (current->data > current->siguiente->data) /* For decreasing order use < */
                {
                    nextone = current->siguiente;
                    current->siguiente = nextone->siguiente;
                    nextone->siguiente = current;

                    if(current==cabeza)
                        {
                            cabeza = nextone;
                            current = nextone;

                        }
                    else
                        {
                            current = nextone;
                            tmp->siguiente = nextone;

                        }

                }
                tmp = current;
                current = current->siguiente;
        }
    }

  printf("Lista Ordenada con Bubble Sort:\n");
    while(tmp != NULL){
        printf("%d ", tmp -> data);
        tmp = tmp->siguiente;
    }
    printf("Lista Ordenada con Bubble Sort Al Final:\n");
}




void InsertAtHead(int x){
    struct NodeLista* nuevoNodo = GetNewNode(x);
    if(cabeza == NULL){
        cabeza = nuevoNodo;
        return;
    }

    cabeza->anterior = nuevoNodo;
    nuevoNodo->siguiente = cabeza;
    cabeza = nuevoNodo;
}

void InsertAtTail(int x){
    struct NodeLista* temp = cabeza;
    struct NodeLista* nuevoNodo = GetNewNode(x);
    if(cabeza == NULL){
            cabeza = nuevoNodo;
            return;
            }
    while(temp->siguiente != NULL)temp = temp->siguiente;

    temp->siguiente = nuevoNodo;
    nuevoNodo->anterior = temp;
}

void Print(){
    struct NodeLista* temp = cabeza;
    printf("Adelante: ");
    while(temp != NULL){
        printf("%d ", temp -> data);
        temp = temp->siguiente;
    }
    printf("\n");

}

void ReversePrint(){
    struct NodeLista* temp = cabeza;
    if(temp == NULL) return;

    while(temp->siguiente != NULL){
            temp = temp->siguiente;
    }
    printf("Reverse: ");
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->anterior;
    }
    printf("\n");
}
/*************************FIN LISTA DOBLE*********************************/



void BS()
{
    printf("\nIngresando a BS");
    printf("\nEsperando...\n");

int  n, c, d, e, swap;

printf("\nPasando datos...\n");

n = parametro;

for (c = 0 ; c < ( n - 1 ); c++)
  {
    for (d = 0 ; d < n - c - 1; d++)
    {
      if (auxiliar[d] > auxiliar[d+1]) /* For decreasing order use < */
      {
        swap       = auxiliar[d];
        auxiliar[d]   = auxiliar[d+1];
        auxiliar[d+1] = swap;
      }
    }
  }
printf("Sorted list in ascending order:\n");

  for ( e = 0 ; e < n ; e++ ){
     printf("%d, ", auxiliar[e]);}
printf("\nBubble Sort final");

}


void quicksortArr(int x[parametro], int first, int last){
    int pivot, j, temp, i;
    //inicioQS = clock();
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
        quicksortArr(x, first, j-1);
        quicksortArr(x, j+1, last);
    }
    //finalsQS = clock();
}


void print_quicksortArr(){
 int ii;
    printf("Elementos ordenados Quick Sort");
    for (ii=0; ii<auxParam;ii++){
        printf(" %d", auxiliar[ii]);}
}

/********************************************************************************/
/***********************************MAIN*****************************************/
/********************************************************************************/
int main()
{
    int contador = 0;
    int parametro = 0;
    FILE *file;
    file = fopen("C:\\815660.txt","r");

    char singleLine[1000000];
    if (file == NULL){
        return -1;

    }
    else{ inicio = clock();
    while (!feof(file))
        {
            int i = 0;


            fgets(singleLine,1000000,file);

            arreglo[i] = atoi(singleLine);
            auxiliar[contador] = arreglo[i];
            //printf(singleLine);
            //printf("\n*****\n");
            //printf("valor numerico\n%i",arreglo[i]);
            //printf("\n*****\n");
            root = insert(root, arreglo[i]);
            contador++;
            parametro++;


            i++;


        }
        fclose(file);
        finals = clock();
    auxParam = parametro;
    auxParam++;
    }//fin else


    //printf("\nInOrden en el arbol AVL \n");
    //inOrder(root);
    //printf("\nLo lograste leiste el arbol AVL \n");

    //printf("El tiempo ingresando al AVL es: %f ",(float)((finals-inicio)/CLOCKS_PER_SEC));

    int prueba1;
    int prueba2;
    int resultado;

    prueba1 = auxiliar[0];
    prueba2 = auxiliar[1];

    resultado = prueba1 + prueba2;

    printf("\nThe result of the operation adding First number %d and Second number %d from the array is Result: %d\n", prueba1, prueba2, resultado);

	printf("\n**************************************************\n");
	printf("\n**************************************************\n");
	/*printf("Ingresando valores del array a la lista\n");

    int iii;
	for( iii = 0; iii<195090; iii++){
        InsertAtTail(auxiliar[iii]);
	}
	//Print();*/
    int iiii;
	for (iiii=0; iiii<parametro;iiii++){
        auxiliar2[iiii] = auxiliar[iiii];

	}


	printf("\n**************************************************\n");
	printf("\n**************************************************\n");
    printf("valor primero %i , valor ultimo %i ", auxiliar[0], auxiliar[auxParam]);


    printf("\n**************************************************\n");
	printf("\n**************************************************\n");
    //inicioBS = clock();
    //BS();
    //Bubblesort();
    //finalsBS = clock();
    //printf("El tiempo ingresando Lista BS es: %f ",total[3]=(float)((finalsBS-inicioBS)/CLOCKS_PER_SEC));
    printf("\n**************************************************\n");
	printf("\n**************************************************\n");




    //printf("\nElemento primero auxiliar[0] = %i\n",auxiliar[0]);
    //printf("\nElemento ultimo auxiliar[parametro] = %i\n",auxiliar[auxParam]);
    inicioQS = clock();
    quicksortArr(auxiliar,0,parametro);
    print_quicksortArr();
    finalsQS = clock();




    printf("\nElemento primero auxiliar[0] = %d\n",auxiliar[0]);
    printf("\nElemento ultimo auxiliar[parametro] = %d\n",auxiliar[parametro]);


    printf("El tiempo ingresando Array QS es: %f ",total=(float)((finalsQS-inicioQS)/CLOCKS_PER_SEC));

    printf("\nParametro!!! = %d\n",parametro);
    printf("\nauxParam!!! = %d\n",auxParam);
    /*int algo;
    for (algo=0; algo<4; algo++){
    printf("\ntotal en posicion  QS!!! = %d\n",total[algo]);}*/
    printf("\ntotal en posicion  QS!!! = %d\n",total);

    return 0;
}


/***********************************************************/
/*******************FIN MAIN********************************/
/************************************************************/



