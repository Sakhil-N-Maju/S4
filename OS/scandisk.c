#include <stdio.h>
#include <stdlib.h>

void main() {
    int q[100], n, seek = 0, i, cur, j, m, cyl, loc;
    float avg;
    
    printf("Enter the no. of Cylinders: ");
    scanf("%d", &cyl);
    printf("Cylinders: 0 to %d\n", cyl - 1);
    
    printf("Enter the Queue Size: ");
    scanf("%d", &m);
    n = m + 1;
    
    printf("Enter the Queue: ");
    for (i = 1; i < n; i++) {
        scanf("%d", &q[i]);
    }
    
    printf("Enter Current Head Position: ");
    scanf("%d", &cur);
    q[0] = cur;
    
    for (i = 1; i < n; i++) {
        for (j = 0; j < n - i; j++) {
            if (q[j] > q[j + 1]) {
                int temp = q[j];
                q[j] = q[j + 1];
                q[j + 1] = temp;
            }
        }
    }
    
    printf("Displaying Requests in Order...\n");
    for (i = 0; i < n; i++) {
        printf("%d\t", q[i]);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        if (q[i] == cur) {
            loc = i;
            break;
        }
    }

    if (cur < q[0]) {
        printf("\nScanning towards left...then right\n");
        
        for (i = loc; i >= 0; i--) {
            printf("%d --> ", q[i]);
        }
        printf("0 --> ");
        for (i = loc + 1; i < n; i++) {
            printf("%d --> ", q[i]);
        }
        
        seek = cur + q[n - 1];
    } else {
        printf("\nScanning towards right...then left\n");
        
        for (i = loc; i < n; i++) {
            printf("%d --> ", q[i]);
        }
        printf("%d --> ", cyl - 1);
        for (i = loc - 1; i >= 0; i--) {
            printf("%d --> ", q[i]);
        }
        
        seek = 2 * (cyl - 1) - cur - q[0];
    }
    
    printf("\n\nTotal Seek Distance: %d\n", seek);
    
    avg = (float)seek / n;
    printf("Average Seek Distance: %.3f\n", avg);
}
