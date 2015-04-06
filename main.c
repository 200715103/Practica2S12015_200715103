#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/***Variable Global NodeLista* cabeza***/
struct NodeLista* cabeza;
/***Variable Global node root AVL***/
struct node *root = NULL;
/***Variable Global NodeLista* cola***/
struct NodeLista* cola;

struct NodeLista* roots;
clock_t inicio;
clock_t inicioBS;
clock_t finals;
clock_t finalsBS;
int arreglo [2001];
int auxiliar[2001];
float total;

/***prueba alternativa quicksort***/
/***void quicksort(int [10, int, int]);***/


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
    n=560;

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
}


/***********************************************************/
void swap(int* a, int* b){
int t = *a;     *a = *b;    *b = t;
}

struct NodeLista *lastNode(struct NodeLista* roots){
    struct NodeLista *aux = roots;
    while(aux && aux->siguiente!=NULL){
        aux = aux->siguiente;}
    return aux;
}

struct NodeLista* partition(struct NodeLista *l, struct NodeLista *h){
    int x = h->data;

    struct NodeLista *i = l->anterior;
    struct NodeLista *j = l;
    for(*j; j != h; j = j->siguiente)
        {
            if(j->data <= x)
                {
                    i = (i == NULL)? l : i->siguiente;

                    swap(&(i->data), &(j->data));
                }
        }
        i = (i == NULL)? l : i->siguiente;
        swap(&(i->data), &(h->data));
        return i;
}

void _quickSort(struct NodeLista* l, struct NodeLista* h){
    if(h != NULL && l != h && l != h->siguiente)
        {
            struct NodeLista *p = partition(l, h);
            _quickSort(l, p->siguiente);
            _quickSort(p->siguiente, h);
        }
}

void quicksort(struct NodeLista *head){
    struct NodeLista *h = lastNode(head);
    _quickSort(head, h);
}


/***********************************************************/



void quicksortArr(int x[560], int first, int last){
    int pivot, j, temp, i;

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
    while(temp->siguiente != NULL) temp = temp->siguiente;
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


struct node* deleteNode(struct node* root, int key){
    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if ( key < root->key )
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if( key > root->key )
        root->right = deleteNode(root->right, key);

    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct node *temp = root->left ? root->left : root->right;

            // No child case
            if(temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of the non-empty child

            free(temp);
        }
        else
        {
            // node with two children: Get the inorder successor (smallest
            // in the right subtree)
            struct node* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
      return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = max(height(root->left), height(root->right)) + 1;

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether
    //  this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
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





/********************************************************************************/
/***********************************MAIN*****************************************/
/********************************************************************************/
int main()
{
    int contador = 0;

    FILE *file;
    file = fopen("C:\\500n.txt","r");

    char singleLine[2001];
    if (file == NULL){
        return -1;

    }
    else{ inicio = clock();
    while (!feof(file))
        {
            int i = 0;

            //int i = 0;
            fgets(singleLine,2001,file);

            arreglo[i] = atoi(singleLine);
            auxiliar[contador] = arreglo[i];
            printf(singleLine);
            printf("\n*****\n");
            printf("valor numerico\n%i",arreglo[i]);
            root = insert(root, arreglo[i]);
            contador++;

            printf("\n*****\n");
            i++;
            if(i==100){system("PAUSE");}

        }
        fclose(file);
        finals = clock();


        int a = arreglo[0];
        int b = arreglo[1];
        int c = arreglo[2];

        printf("\nvalor numerico en posicion 0\n%i",arreglo[0]);
        printf("\nvalor numerico en posicion 1\n%i",arreglo[1]);
        printf("\nvalor numerico en posicion 2\n%i",arreglo[2]);




        printf("\nLa suma de %i y %i es: %i ",a,b,c);




    }//fin else


    printf("\nInOrden en el arbol AVL \n");
    inOrder(root);

    printf("El tiempo ingresando al AVL es: %f ",(float)((finals-inicio)/CLOCKS_PER_SEC));

    int prueba1;
    int prueba2;
    int resultado;

    prueba1 = auxiliar[0];
    prueba2 = auxiliar[1];

    resultado = prueba1 + prueba2;

    printf("\nThe result of the operation adding First number %d and Second number %d from the array is Result: %d\n", prueba1, prueba2, resultado);

	printf("\n**************************************************\n");
	printf("\n**************************************************\n");
	printf("Ingresando valores del array a la lista\n");
    int iii;
	for( iii = 0; iii<560; iii++){
        InsertAtTail(auxiliar[iii]);
	}
	Print();


	printf("\n**************************************************\n");
	printf("\n**************************************************\n");
    printf("valor primero %i , valor ultimo %i ", auxiliar[0], auxiliar[559]);


    printf("\n**************************************************\n");
	printf("\n**************************************************\n");
    inicioBS = clock();
    Bubblesort();
    finalsBS = clock();
    printf("El tiempo ingresando Lista BS es: %f ",(float)((finalsBS-inicioBS)/CLOCKS_PER_SEC));
    printf("\n**************************************************\n");
	printf("\n**************************************************\n");


    int ii;

    printf("Elemento uno auxiliar[0] = %d\n",auxiliar[0]);
    quicksortArr(auxiliar,0,560);

    printf("Elementos ordenados Quick Sort");
    for (ii=1; ii<561;ii++){
        printf(" %d", auxiliar[ii]);}
    printf("\nElemento uno auxiliar[560] = %d\n",auxiliar[560]);

    return 0;
}


/***********************************************************/
/*******************FIN MAIN********************************/
/************************************************************/


/*****Metodo Quicksort******/
void quicksorts(int x[10], int first, int last){
    int pivot, j, temp, i;

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
        quicksorts(x, first, j-1);
        quicksorts(x, j+1, last);
    }
}

/*La funcion quicksort se llama pasando como primer argumento del array a[] y los indices que le delimitan 0 y n-1
(indice inferior y superior)*/

/************ quicksort(a,0,n-1)***************/

/*void quicksort(double a[], int primero, int ultimo){
    int i,j,central;
    double pivote;

    central = (primero+ultimo)/2;
    pivote = a[central];
    i = primero;
    j = ultimo;



    do{
        while (a[i]<pivote) i++;
        while (a[j]>pivote) j--;

        if(i<=j)
        {
            double tmp;
            tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++;
            j--;
        }
    }while(i<=j);

    if (primero < j)
        quicksort(a, primero, j);


    if (i < ultimo)
        quicksort(a,i,ultimo);

  }*/






