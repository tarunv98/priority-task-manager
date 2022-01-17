#include "./lib/fibonacciHeap.c"

int main(int argc, char **argv) {
  FHNODE *new_node, *min_node, *extracted_min, *node_to_be_decrease, *find_use;
  FIB_HEAP *heap, *h1, *h2;
  int operation_no, new_key, dec_key, ele, i, no_of_nodes;
  heap = (FIB_HEAP *)malloc(sizeof(FIB_HEAP));
  heap = NULL;
  while (1) {
    printf(" \n Operations \n 1. Initialise Task Heap \n 2. Add Tasks \n 3. Get top Task \n 4. Print all tasks \n 5. exit \n enter operation_no = ");
    scanf("%d", &operation_no);

    switch (operation_no) {
      case 1:
        heap = make_fib_heap();
        break;

      case 2:
        if (heap == NULL) {
          heap = make_fib_heap();
        }
        printf(" enter number of tasks to be inserted = ");
        scanf("%d", &no_of_nodes);
        for (i = 1; i <= no_of_nodes; i++) {
          insertion(heap);
        }
        break;

      case 3:
        if (heap == NULL)
          printf("Empty Task heap");
        else {
          extracted_min = extract_min(heap);
          getTask(extracted_min -> task_list);
        }
        break;

      case 4:
        print_heap(heap->min);
        break;

      case 5:
        free(new_node);
        free(heap);
        exit(0);

      default:
        printf("Invalid choice ");
    }
  }
}