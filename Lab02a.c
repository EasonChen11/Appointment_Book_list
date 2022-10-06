//
// Created by yschen on 2022/10/6.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#define HOWMANY 100//how much of random number
#define filename_size 20
struct sc{
    int score;
    struct sc *next;
};
typedef struct sc scType;

void readfile_and_sorting(scType ** head,char *filename);

void random_data(char *filename);

void addScore_and_sorting(scType ** head, int score);

void printScore(scType *head);

void output_file(scType * head,char *filename);

int main(){
    char input_filename[filename_size],output_filename[filename_size];
    scType *A=NULL;
    random_data(input_filename);
    readfile_and_sorting(&A,input_filename);
    output_file(A,output_filename);
}

void output_file(scType * head,char *filename) {//put the data to txt
    printf("Please enter the file name to open:(example:./output.txt)");
    //fgets(filename, filename_size,stdin);
    scanf("%s",filename);//read output filename
    rewind(stdin);//clear
    assert(strlen(filename)<filename_size);//check the filename size legitimate
    printf("output file:%s\n",filename);
    FILE *output;
    if((output= fopen(filename,"w"))==NULL){//check file is legitimate
        fclose(output);
        printf("cancel\n");
        return;
    }
    scType *before;
    while (head){//read data before NULL
        fprintf(output,"%d ",head->score);//input to the file
        before=head;
        head=head->next;
        free(before);//free the memory
    }
    fclose(output);
    printf("finish\n");
}

void random_data(char *filename) {//create random numbers file
    printf("Please enter the file name to open:(example:./data.txt)");
    scanf("%s",filename);//input filename
    rewind(stdin);
    assert(strlen(filename)<filename_size);//check the filename size legitimate
    FILE *fp= fopen(filename,"w");
    if(fp==NULL){//check file is legitimate
        printf("cancel");
        return;
    }
    srand(time(0));
    int i=0;
    printf("random data:\n");
    while (i++ <HOWMANY){
        int k=rand()%HOWMANY;
        printf("%d ",k);
        fprintf(fp,"%d ",k);
    }//run HOWMANY times
    printf("\n");
    fprintf(fp,"\n");
    fclose(fp);
}

void readfile_and_sorting(scType ** head,char *filename) {//read numbers
    FILE *fp;
    if( (fp = fopen(filename,"r")) == NULL){//check open file legitimate
        fclose(fp);
        return;
    }
    printf("read file:%s\n",filename);
    int score;
    while ( fscanf(fp, "%d",&score)!=EOF){
        addScore_and_sorting(head,score);//add number in the link list
    }
    fclose(fp);
    printf("sorting:\n");
    printScore(*head);
}

void addScore_and_sorting(scType ** head, int score) {
    scType *save= (scType*)malloc(sizeof (scType));
    save->score=score;
    save->next=NULL;//create a node
    //printf("%d\n",save->score);
    if(*head==NULL){//first is NULL
        *head=save;
        return;
    }
    if(save->score < (*head)->score){//score is smallest
        save->next=*head;
        *head=save;
        return;
    }
    scType *now=(*head)->next,*before=*head;
    while (now){//find the node that score is bigger than score
        if(save->score < now->score){
            before->next=save;
            save->next=now;
            return;
        }
        before=now;
        now=now->next;
    }
    before->next=save;
}
void printScore(scType *head){
    while (head){
        printf("%d ",head->score);
        head=head->next;
    }
    printf("\n");
}