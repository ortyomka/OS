#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

void* myRealloc(void* ptr, size_t newSize)
{
  if (ptr == NULL)
  {
    return malloc(newSize);
  }
  if(!newSize)
  {
    free(ptr);
    return NULL;
  }

  void* newPtr = malloc(newSize * sizeof(ptr[0]));
  if(newPtr == NULL)
  {
    printf("Can't allocate memory\n");
    return ptr;
  }

  if(malloc_usable_size(newPtr) > malloc_usable_size(ptr))
  {
    memcpy(newPtr, ptr, malloc_usable_size(ptr));
  }
  else
  {
    memcpy(newPtr, ptr, malloc_usable_size(newPtr));
  }
  free(ptr);
  return newPtr;
}

int main()
{
  srand(time(NULL));

	// Allows user to specify the original array size, stored in variable n1.
	printf("Enter original array size:");
	int n1=0;
	scanf("%d",&n1);

  if(n1 < 1)
  {
    printf("Size can't be 0 or negative\n");
    return 1;
  }

	//Create a new array of n1 ints
	int* a1 = (int*)malloc(n1 * sizeof(int));
	int i;
	for(i=0; i<n1; i++){
		//Set each value in a1 to 100
		a1[i]=rand() % 100;

		//Print each element out (to make sure things look right)
		printf("%d ", a1[i]);
	}

	//User specifies the new array size, stored in variable n2.
	printf("\nEnter new array size: ");
	int n2=0;
	scanf("%d",&n2);

  if(n2 < 0)
  {
    printf("Size can't negative\n");
    free(a1);
    return 1;
  }

	//Dynamically change the array to size n2
	a1 = (int*)myRealloc((void*)a1, n2);
  if(a1 == NULL)
  {
    return 0;
  }
	//If the new array is a larger size, set all new members to 0. Reason: dont want to use uninitialized variables.

	for(int i = n1; i < n2; i++)
  {
    a1[i] = 0;
  }


	for(i=0; i<n2;i++){
		//Print each element out (to make sure things look right)
		printf("%d ",a1[i]);
	}
	printf("\n");

	//Done with array now, done with program :D
  free(a1);
  return 0;
}