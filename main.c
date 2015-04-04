#include <stdio.h>
#include <stdlib.h>


/***prueba alternativa quicksort***/
/***void quicksort(int [10, int, int]);***/


/*****LISTA DOBLE ENLAZADA*******/
/*****struct NodeLista********/
struct NodeLista{
    int data;
    struct NodeLista* siguiente;
    struct NodeLista* anterior;

};

/***Variable Global NodeLista* cabeza***/
struct NodeLista* cabeza;

/***Crea Nuevo Nodo y retorna pointer a el mismo***/
struct NodeLista* GetNewNode(int x){
    /***Creacion de nuevoNodo y aloja el espacio en la memoria***/
    struct NodeLista* nuevoNodo = (struct NodeLista*)malloc(sizeof(struct NodeLista));
    nuevoNodo->data = x;
    nuevoNodo->anterior = NULL;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

void InsertAtHead(int x)
{
    struct NodeLista* nuevoNodo = GetNewNode(x);
    if(head == NULL){
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






int variableGlobal = 0;
void funcion(){
printf("prueba de funcion sin argumentos\n");
//printf("\a\a\a\a");
variableGlobal ++;
}

void tab(){
printf("\t");}

typedef struct
{
    char *name;
    char *email;
    int age;

} client;



struct node
{
    int key;
    int height;
    struct node *left;
    struct node *right;

};

// A utility function to get maximum of two integers
int max(int a, int b);

// A utility function to get height of the tree
int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct node* newNode(int key)
{
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
struct node *rightRotate(struct node *y)
{
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
struct node *leftRotate(struct node *x)
{
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
int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct node* insert(struct node* node, int key)
{
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
struct node * minValueNode(struct node* node)
{
    struct node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}


struct node* deleteNode(struct node* root, int key)
{
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


// A utility function to print preorder traversal of the tree.
// The function also prints height of every node
void preOrder(struct node *root)
{
    if(root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

/****Funcion inOrder AVL***/
void inOrder(struct node *root)
{
    if(root != NULL)
    {

        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}







int arreglo [2001];
int auxiliar[2001];

/********************************************************************************/
/***********************************MAIN*****************************************/
/********************************************************************************/
int main()
{

    int x[20], size, ii;

    printf("Ingrese tamanio de array: ");
    scanf("%d", &size);

    printf("Ingrese %d elementos: ", size);
    for(ii=0;ii<size;ii++){
        scanf("%d", &x[ii]);}

    quicksort(x,0,size-1);

    printf("Elementos ordenados");
    for (ii=0; ii<size;ii++){
        printf(" %d", x[ii]);}







    int contador = 0;
    int variable = 10;
    int * puntero = &variable;
    printf("\n\n%u\n",puntero);
    printf("%d\n",*puntero);
    *puntero = 50;

    printf("%u\n",puntero);
    printf("%d\n",*puntero);

    /****/
    struct node *root = NULL;
    FILE *file;
    file = fopen("C:\\2000numeros.txt","r");

    char singleLine[2001];
    if (file == NULL){
        return -1;

    }
    else{
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


        int a = arreglo[0];
        int b = arreglo[1];
        int c = arreglo[2];

        printf("\nvalor numerico en posicion 0\n%i",arreglo[0]);
        printf("\nvalor numerico en posicion 1\n%i",arreglo[1]);
        printf("\nvalor numerico en posicion 2\n%i",arreglo[2]);
        //int d = arreglo[0];
        //int e = arreglo[1];
        //int f = d+e;


        //printf("\n**********\n%i\n%i\n**********",singleLine[4],singleLine[0]);
        //printf(singleLine[1]);
        //printf(singleLine[2]);
        //printf(singleLine[3]);
        printf("\nLa suma de %i y %i es: %i ",a,b,c);
        //printf("\nLa suma de %i y %i es: %i ",d,e,f);



}
/*
    int arreglo [10];
    arreglo[0] = 1;

    int peaje;
    int tipo_vehiculo;
    printf("\nIntroduzca tipo de vehiculo: ");
    scanf("%d",&tipo_vehiculo);

    switch(tipo_vehiculo)
    {
    case 1:
        printf("Turismo\n");
        peaje = 500;
        printf("%d",peaje);
        break;

    case 2:
        printf("Autobus\n");
        peaje = 3000;
        printf("%i",peaje);

        break;

    case 3:
        printf("Motocicleta\n");
        peaje = 300;
        printf("%i",peaje);
        break;

    default:
        printf("Vehiculo no autorizado\n");


    }
    printf("\n*********************************\n");

    int contador = 0;
    while(contador<10)
        {
        printf("Hola mundo ciclo %d\n",contador);
        contador ++;
        }

    int i = 567;
    int *iPointer = &i;
    int **ipp = &iPointer;
    printf("%i\n", **ipp);

    client c1;
    c1.name = "John Doe";
    c1.email = "Jd@gmail.com";
    c1.age = 26;
    printf("%s\n",c1.name);

    variableGlobal +1;
    tab();
    funcion();
    printf("Hello world!\n");
    //printf(variableGlobal);*/




/*
    struct node *root = NULL;*/

  /* Constructing tree given in the above figure */
  /*root = insert(root, 10);
  root = insert(root, 20);
  root = insert(root, 30);
  root = insert(root, 40);
  root = insert(root, 50);
  root = insert(root, 25);
*/
  /* The constructed AVL Tree would be
            30
           /  \
         20   40
        /  \     \
       10  25    50
  */
/*
  printf("Pre order traversal of the constructed AVL tree is \n");
  preOrder(root);

*/

    printf("\nPreorden en el arbol AVL \n");
    preOrder(root);

    printf("\nInOrden en el arbol AVL \n");
    inOrder(root);

    printf("\n\n%d\n%d\n\n%d\n\n%d\n",auxiliar[0],auxiliar[1],auxiliar[24],auxiliar[151]);
    int prueba1;
    int prueba2;
    int resultado;

    prueba1 = auxiliar[0];
    prueba2 = auxiliar[1];

    resultado = prueba1 + prueba2;

    printf("The result of the operation adding First number %d and Second number %d from the array is Result: %d\n", prueba1, prueba2, resultado);

    /*int array[501], n, c, d, swap;
    int i, num;
    num = 501;
    c=501;
    n=501;*/
    /* Copying data from array 'a' to array 'b */
   /*for ( i = 0; i < num; i++) {
      array[i] = auxiliar[i];
   }


    for (c = 0 ; c < ( n - 1 ); c++)
    {
    for (d = 0 ; d < n - c - 1; d++)
    {
      if (array[d] > array[d+1]) /* For decreasing order use < */
     /* {
        swap       = array[d];
        array[d]   = array[d+1];
        array[d+1] = swap;
      }
    }
    }

  printf("Sorted list in ascending bubble sort order:\n");

  for ( c = 0 ; c < n ; c++ ){
     printf("%d\n", array[c]);}*/



    return 0;
}

void quicksort(int x[10], int first, int last){
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
        quicksort(x, first, j-1);
        quicksort(x, j+1, last);
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
