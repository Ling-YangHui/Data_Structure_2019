#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

  int time (int n) {
        int i=1;
		int j=0;
		int count = 0;
		while(i+j<=n){
 		 if(i>j)
 		 { 
        j++;
        } 
    else
        i++;
        count ++;
}
return count;
  }    
  
  int main()
  {
	printf("%d",time(8));
	return 0;
  }
