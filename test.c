#include<stdio.h>
int main(void){
  int i,j;
  int total = 0;
  for(i=0; i<10; i++){
    for(j=0; j<10; j++){
      total += i*j;
    }
  }
  
  printf("%d", &total);
}
