#include <stdio.h>

#define MAX_DISKS 10

int source[MAX_DISKS], auxiliary[MAX_DISKS], destination[MAX_DISKS];
int top[3] = {-1, -1, -1}; // Indices: 0 - source, 1 - auxiliary, 2 - destination

void push(int disk, int rod) {
    top[rod]++;
    if (rod == 0) source[top[rod]] = disk;
    else if (rod == 1) auxiliary[top[rod]] = disk;
    else if (rod == 2) destination[top[rod]] = disk;
}

int pop(int rod) {
    int disk = -1;
    if (top[rod] != -1) {
        if (rod == 0) disk = source[top[rod]];
        else if (rod == 1) disk = auxiliary[top[rod]];
        else if (rod == 2) disk = destination[top[rod]];
        top[rod]--;
    }
    return disk;
}

void printRods() {
    printf("Source:      ");
    for (int i = 0; i <= top[0]; i++) printf("%d ", source[i]);
    printf("\nAuxiliary:   ");
    for (int i = 0; i <= top[1]; i++) printf("%d ", auxiliary[i]);
    printf("\nDestination: ");
    for (int i = 0; i <= top[2]; i++) printf("%d ", destination[i]);
    printf("\n\n");
}

void towerOfHanoi(int n, int from_rod, int to_rod, int aux_rod) {
    if (n == 0) return;
    towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
    int disk = pop(from_rod);
    push(disk, to_rod);
    printf("Move disk %d from rod %c to rod %c\n", disk, 'A' + from_rod, 'A' + to_rod);
    printRods();
    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main() {
    int n;
    printf("Enter the number of disks: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX_DISKS) {
        printf("Please enter a number between 1 and %d.\n", MAX_DISKS);
        return 1;
    }

    for (int i = n; i >= 1; i--) {
        push(i, 0);
    }

    printRods();
    towerOfHanoi(n, 0, 2, 1); // Source to Destination using Auxiliary

    return 0;
}
