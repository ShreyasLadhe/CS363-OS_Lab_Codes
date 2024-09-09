#include <stdio.h>

int main() {
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n]; 
    int *pArr = arr;

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", pArr + i);  
    }

    printf("The elements of the array are:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", *(pArr + i)); 
    }
    printf("\n");

    return 0;
}
