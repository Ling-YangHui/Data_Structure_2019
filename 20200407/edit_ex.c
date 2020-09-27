#include <stdio.h>
#include <string.h>

typedef struct edit
{
    int op;
    int pos;
    char str[520];
    int num;
}STK;
STK stack[100];
char data[520];
int top=-1;
int pushdata(int mode){
    int op=0,pos=0,num=0,k,i;
    char str[520]={0};
    scanf("%d",&op);
    if(op==1){
        scanf("%d",&pos);
        scanf("%s",str);
        num=strlen(str);
    }else if(op==2){
        scanf("%d",&pos);
        if(mode==1){
            scanf("%d",&num);
            for(i=pos,k=0;i<pos+num;i++,k++){
                str[k]=data[i];                
            }
            str[k]=0;
        }else if(mode==0){
            scanf("%s",str);
            num=strlen(str);
        }
    }else if(op==3){
    }else if(op==-1){
        return -1;
    }
    top++;
    stack[top].op=op;
    stack[top].num=num;
    stack[top].pos=pos;
    strcpy(stack[top].str,str);
    return 0;
}
void insert(char str[],int pos){
    int i,j,len=strlen(data),num=strlen(str);
    for(i=len;i>=pos;i--){
        data[i+num]=data[i];
    }
    for(i=pos,j=0;i<=pos+num-1;i++,j++){
        data[i]=str[j];
    }
}
void delete(int pos,int num){
    int i,len=strlen(data);
    if(pos+num>=len){
        num=len-pos;
    }
    for(i=pos;data[i]!=0;i++){
        data[i]=data[i+num];
    }
}
int main(){
    //FILE *OUT=fopen("1.txt","w");
    fgets(data,512,stdin);
    int n;
    scanf("%d",&n);
    while(n--){
        pushdata(0);
    }
    while(pushdata(1)!=-1){
        if(stack[top].op==1){
            insert(stack[top].str,stack[top].pos);
        }else if(stack[top].op==2){
            delete(stack[top].pos,stack[top].num);
        }
        if(stack[top].op==3){
                if(stack[top-1].op==1){
                    delete(stack[top-1].pos,stack[top-1].num);
                    //fprintf(OUT,"DEL:%s\n",data);
                    top-=2;
                }else if(stack[top-1].op==2){
                    insert(stack[top-1].str,stack[top-1].pos);
                    //fprintf(OUT,"INS:%s\n",data);
                    top-=2;
                }
        }
    }
    printf("%s",data);
    return 0;
}