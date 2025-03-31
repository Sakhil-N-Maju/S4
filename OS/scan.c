#include<stdio.h>
#include<stdlib.h>

void main() {
    int n, queue[100], head, direction, seek = 0, temp;
    int start, end;
    printf("Enter the start and end boundaries of the disk: ");
    scanf("%d %d", &start, &end);

    printf("Enter the number of elements in the queue: ");
    scanf("%d", &n);

    printf("Enter the queue elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &queue[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    queue[n] = start;
    queue[n+1] = end;
    n += 2;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (queue[i] > queue[j]) {
                temp = queue[i];
                queue[i] = queue[j];
                queue[j] = temp;
            }
        }
    }

    int index = 0;
    while (queue[index] < head && index < n) {
        index++;
    }

    if (direction == 1) {
        for (int i = index; i < n; i++) {
            seek += abs(head - queue[i]);
            printf("\nMove from %d to %d: Seek = %d\n", head, queue[i], abs(head - queue[i]));
            head = queue[i];
        }
        for (int i = index - 1; i >= 0; i--) {
            seek += abs(head - queue[i]);
            printf("\nMove from %d to %d: Seek = %d\n", head, queue[i], abs(head - queue[i]));
            head = queue[i];
        }
    } else {
        for (int i = index - 1; i >= 0; i--) {
            seek += abs(head - queue[i]);
            printf("\nMove from %d to %d: Seek = %d\n", head, queue[i], abs(head - queue[i]));
            head = queue[i];
        }
        for (int i = index; i < n; i++) {
            seek += abs(head - queue[i]);
            printf("\nMove from %d to %d: Seek = %d\n", head, queue[i], abs(head - queue[i]));
            head = queue[i];
        }
    }

    printf("\nTotal seek time: %d\n", seek);
}
