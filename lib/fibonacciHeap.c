// Operations on a Fibonacci heap in C

#include <math.h>
#include <stdbool.h>
#include "./linkedlist.c"

typedef struct FibonacciHeap {
  int key;
  LLNODE * task_list;
  int degree;
  struct FibonacciHeap *left_sibling;
  struct FibonacciHeap *right_sibling;
  struct FibonacciHeap *parent;
  struct FibonacciHeap *child;
  bool mark;
  bool visited;
} FHNODE;

typedef struct fibanocci_heap {
  int n;
  FHNODE *min;
  int phi;
  int degree;
} FIB_HEAP;

FIB_HEAP *make_fib_heap();
void insertion(FIB_HEAP *H);
FHNODE *extract_min(FIB_HEAP *H);
void consolidate(FIB_HEAP *H);
void fib_heap_link(FIB_HEAP *H, FHNODE *y, FHNODE *x);

// Printing the heap
void print_heap(FHNODE *n) {
  FHNODE *x;
  for (x = n;; x = x->right_sibling) {
    if (x->child == NULL) {
      printf("node with no child (%d) \n", x->key);
      printList(x->task_list);
    } else {
      printf("NODE(%d) with child (%d)\n", x->key, x->child->key);
      printList(x->task_list);
      print_heap(x->child);
    }
    if (x->right_sibling == n) {
      break;
    }
  }
}

FIB_HEAP *make_fib_heap() {
  FIB_HEAP *H;
  H = (FIB_HEAP *)malloc(sizeof(FIB_HEAP));
  H->n = 0;
  H->min = NULL;
  H->phi = 0;
  H->degree = 0;
  return H;
}

LLNODE * checkPriority(FHNODE * n, int val){
  FHNODE *x;
  if (n == NULL) return NULL;
  for (x = n;; x = x->right_sibling) {
    if (x->child == NULL) {
      if(val == x->key) {
        return x->task_list;
      }
    } else {
      if(val == x->key) {
        return x->task_list;
      }
      checkPriority(x->child, val);
    }
    if (x->right_sibling == n) {
      break;
    }
  }
  return NULL;
}

// Inserting nodes
void insertion(FIB_HEAP *H) {
  int val;
  printf("\nEnter Priority [(min) 1 to (max) 99]\n");
  scanf("%d", &val);
  val=100-val;

  LLNODE * temp = checkPriority(H->min, val);

  if(temp != NULL) {
    push(temp);
  } else {
    FHNODE * new = (FHNODE *)malloc(sizeof(FHNODE));
    new->key = val;
    new->degree = 0;
    new->mark = false;
    new->parent = NULL;
    new->child = NULL;
    new->visited = false;
    new->left_sibling = new;
    new->right_sibling = new;
    new->task_list = createLinkedList();
    push(new->task_list);

    if (H->min == NULL) {
      H->min = new;
    } else {
      H->min->left_sibling->right_sibling = new;
      new->right_sibling = H->min;
      new->left_sibling = H->min->left_sibling;
      H->min->left_sibling = new;
      if (new->key < H->min->key) {
        H->min = new;
      }
    }
  }

  (H->n)++;
}

// Calculate the degree
int cal_degree(int n) {
  int count = 0;
  while (n > 0) {
    n = n / 2;
    count++;
  }
  return count;
}

// Consolidate function
void consolidate(FIB_HEAP *H) {
  int degree, i, d;
  degree = cal_degree(H->n);
  FHNODE *A[degree], *x, *y, *z;
  for (i = 0; i <= degree; i++) {
    A[i] = NULL;
  }
  x = H->min;
  do {
    d = x->degree;
    while (A[d] != NULL) {
      y = A[d];
      if (x->key > y->key) {
        FHNODE *exchange_help;
        exchange_help = x;
        x = y;
        y = exchange_help;
      }
      if (y == H->min)
        H->min = x;
      fib_heap_link(H, y, x);
      if (y->right_sibling == x)
        H->min = x;
      A[d] = NULL;
      d++;
    }
    A[d] = x;
    x = x->right_sibling;
  } while (x != H->min);

  H->min = NULL;
  for (i = 0; i < degree; i++) {
    if (A[i] != NULL) {
      A[i]->left_sibling = A[i];
      A[i]->right_sibling = A[i];
      if (H->min == NULL) {
        H->min = A[i];
      } else {
        H->min->left_sibling->right_sibling = A[i];
        A[i]->right_sibling = H->min;
        A[i]->left_sibling = H->min->left_sibling;
        H->min->left_sibling = A[i];
        if (A[i]->key < H->min->key) {
          H->min = A[i];
        }
      }
      if (H->min == NULL) {
        H->min = A[i];
      } else if (A[i]->key < H->min->key) {
        H->min = A[i];
      }
    }
  }
}

// Linking
void fib_heap_link(FIB_HEAP *H, FHNODE *y, FHNODE *x) {
  y->right_sibling->left_sibling = y->left_sibling;
  y->left_sibling->right_sibling = y->right_sibling;

  if (x->right_sibling == x)
    H->min = x;

  y->left_sibling = y;
  y->right_sibling = y;
  y->parent = x;

  if (x->child == NULL) {
    x->child = y;
  }
  y->right_sibling = x->child;
  y->left_sibling = x->child->left_sibling;
  x->child->left_sibling->right_sibling = y;
  x->child->left_sibling = y;
  if ((y->key) < (x->child->key))
    x->child = y;

  (x->degree)++;
}

// Extract min
FHNODE *extract_min(FIB_HEAP *H) {
  if (H->min == NULL)
    printf("\n The heap is empty");
  else {
    FHNODE *temp = H->min;
    FHNODE *pntr;
    pntr = temp;
    FHNODE *x = NULL;
    if (temp->child != NULL) {
      x = temp->child;
      do {
        pntr = x->right_sibling;
        (H->min->left_sibling)->right_sibling = x;
        x->right_sibling = H->min;
        x->left_sibling = H->min->left_sibling;
        H->min->left_sibling = x;
        if (x->key < H->min->key)
          H->min = x;
        x->parent = NULL;
        x = pntr;
      } while (pntr != temp->child);
    }

    (temp->left_sibling)->right_sibling = temp->right_sibling;
    (temp->right_sibling)->left_sibling = temp->left_sibling;
    H->min = temp->right_sibling;

    if (temp == temp->right_sibling && temp->child == NULL)
      H->min = NULL;
    else {
      H->min = temp->right_sibling;
      consolidate(H);
    }
    H->n = H->n - 1;
    return temp;
  }
  return H->min;
}