#include<stdio.h>
int main(void){
  int i, j, n;
  int data[];
  char name_stk[10], name[10][10];
  
  printf("人数=");
  scanf("%d", &n);
  
  for(i=0; i<n; i++){
    scanf("%d", &data[i]);
    scanf("%s", name_stk);
    strcpy(name[i], name_stk);
  }
}
