#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#define eps 0.0000001

void check (int countsystem, int count, ...){
    va_list args;
    va_start(args, count);
    double d, intpart, arr[100];
    int end, flag;

    for (int k = 0; k < count; k++){
        d = va_arg(args, double);
        printf ("%lf ", d);
        end = 0;
        arr[end++] = d;
        flag = 1;
        
        while (d > eps && flag){
            d *= countsystem;
            d = modf(d, &intpart);
            
            for (int i = 0; i < end; i++){
                
                if (fabs(d - arr[i]) < eps){
                    printf ("infinite\n");
                    flag = 0;
                    break;
                }
            }

            arr[end++] = d;
        }
        
        if(flag)
        	printf ("finite\n");
    }
}

int main(){
    int countsystem;
    printf ("Enter countsystem: ");
    scanf ("%d", &countsystem);
    check (countsystem, 5, 0.5, 0.1, 0.33, 0, 1);

    return 0;
}

