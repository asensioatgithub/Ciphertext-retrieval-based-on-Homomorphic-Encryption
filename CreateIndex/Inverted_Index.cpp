#include "Inverted_Index.h"
#include "Convert.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"  //OVERFLOW
#include<sys/types.h>
#include<regex.h>
#include<memory.h>
#include<iostream>
using namespace std;

#define INIT_SIZE 10
#define PER_SIZE 5
char *pattern = "([\u4e00-\u9fa5]+)([0-9].[0-9]+)";


IndexTable::IndexTable(){
  
    it = (IndexList *) malloc(sizeof(IndexList)*INIT_SIZE); //
    if(!it) exit(OVERFLOW);           //
//    for(int i=0;i<INIT_SIZE;i++){
//       it[i].in=(IndexNode *) malloc(sizeof(IndexNode)); 
//       if(!(it[i].in)) exit(OVERFLOW); 
//    }
    TableSize=INIT_SIZE;
    length=0;
}


int IndexTable::GetTableLength(){
  return length;
}

int IndexTable::GetListLength(int i){
  return it[i].size;
}


int IndexTable::SearchKeyWord(char *k){
   if(length==0) return -1;
   IndexList *temp = it;
   int i=0;
   for(;i<length;i++){
     if(strcmp(temp[i].KeyWord,k)==0)  //k存在，返回位置
       return i;
   }
   return length;
}


void IndexTable::InsertWord(char *k,int id,int w){  
   
   IndexNode *newnode=NewNode(id,w); 
   int  index=SearchKeyWord(k);

   if(index==-1){     //为空表
      it[0].KeyWord = k; 
      it[0].in = newnode;
      it[0].tail=it[0].in;
      it[0].size++;

      
      length++;
   }       
   else if(index<length){ //k存在
      it[index].tail->next = newnode;
      it[index].tail=newnode;
      it[index].size++;
   }
   else{                 //k不存在
         if(index>=TableSize){  
            IndexList *newbase=(IndexList*)realloc(it,sizeof(IndexList)*(TableSize+PER_SIZE));
            if(!newbase)  exit(OVERFLOW); 
            it=newbase;//realloc()返回it原地址
            TableSize+=PER_SIZE;
         }
         it[index].KeyWord = k;
         it[index].in = newnode;
         it[index].tail = it[index].in;
         it[index].size++;
         length++;
      }
      
}


void IndexTable::CreateTable(){
   cout<<"正在创建倒排索引表．．．"<<endl;
   char errbuf[1024];
   char match[10];
   
   regex_t reg;
   int err,nm = 11;
   regmatch_t pmatch[nm];
   FILE *fp=NULL;
   
   if(regcomp(&reg,pattern,REG_EXTENDED) < 0){ //编译正则表达式
     regerror(err,&reg,errbuf,sizeof(errbuf));
     printf("err:%s\n",errbuf);
   }
   if((fp=fopen("KeyWordList.txt","r")) == NULL){
       printf("不能打开文件KeyWordList.txt\n");
       exit(0);
	 }
   char stringLine[100];  
   int wight=0;
   int line=0;
   while ((fgets(stringLine,100,fp))!=NULL){
	    if(++line%6==0) continue;//读取一行

     err = regexec(&reg,stringLine,nm,pmatch,0);
  //   printf("%s\n", stringLine); //输出
     if(err == REG_NOMATCH)
     {
       printf("no match\n");
       exit(-1);
     }
     else if(err)
     {
        regerror(err,&reg,errbuf,sizeof(errbuf));
        printf("err:%s\n",errbuf);
        exit(-1);
     }
     
    
     for(int i=1;i<10 && pmatch[i].rm_so!=-1&&pmatch[i+1].rm_so!=-1;i+=2)
     {  
        char *matchKey = new char[20];char *matchWight = new char[10];
        memset(matchKey,'\0',sizeof(matchKey));
        memset(matchWight,'\0',sizeof(matchWight)); 
        int len1 = pmatch[i].rm_eo-pmatch[i].rm_so;
        int len2 = pmatch[i+1].rm_eo-pmatch[i+1].rm_so;
     
          memcpy(matchKey,stringLine+pmatch[i].rm_so,len1);
         // cout<<matchKey<<endl;
          memcpy(matchWight,stringLine+pmatch[i+1].rm_so,len2);
         // cout<<matchWight<<endl;
          InsertWord(matchKey,line/6+1,(int)(atof(matchWight)*10));

      }     
   }
   
  
   fclose(fp); 

}



IndexNode *IndexTable::NewNode(int id,int w){
   IndexNode *node=(IndexNode *) malloc(sizeof(IndexNode));
   node->d_id=id;
   node->wight=w;
   node->next = NULL;
   return node;
}




//covert Index to InstInt
void IndexTable::ListToInst(Instruct &t,InstList *&Inst_table){
    Inst_table = new InstList[length];
    string str;
    unsigned char *s = NULL;
    unsigned char *as = NULL;
    int num=0; 
    IndexNode *p = NULL;
    InstNode * newnode=NULL;  
  
    for(int i=0;i<length;i++){
    
        str = Utf8ToGbk(it[i].KeyWord);
        num = str.size();
        //cout<<num<<endl;
        s = (unsigned char*)str.c_str();
        
        Inst_table[i].Inst_KeyWord = new InstByte[num];
   //     printf("索引%d:\n",i);
        t.KeytoInstByte(s,num,Inst_table[i].Inst_KeyWord);
        p = it[i].in;
        Inst_table[i].KeySize = num;
        while(p){
               newnode = new InstNode;  //开辟一个InstNode内存，地址赋给newnode
             //  cout<<"d_id:"<<p->d_id<<endl;
               newnode->Inst_d_id = t.InttoInstByte(p->d_id);
           //    cout<<"wight:"<<p->wight<<endl;
               newnode->Inst_wight = t.InttoInstByte(p->wight);
               if(Inst_table[i].in==NULL){   //表i为空
                  Inst_table[i].in = newnode;
                  Inst_table[i].tail = Inst_table[i].in;
               }else{   //表i不空，将新节点添加到末尾
                     Inst_table[i].tail->next = newnode;
                     Inst_table[i].tail = newnode;
                   }
               p=p->next;    
        }
    }
//printf("\n");
}



void IndexTable::PrintTable(){
   IndexNode *p = NULL;
   cout<<" －－－－－－－－    －－－－－－－－－－－－－－－－－－－－－－"<<endl;
   cout<<"|   关键词      |   |　　　　　明文文档ID　　　　         　　　|"<<endl;
   cout<<" －－－－－－－－    －－－－－－－－－－－－－－－－－－－－－－"<<endl;
   for(int i=0;i<length;i++){
     printf("|%-14s\t|--->",it[i].KeyWord);
     p=it[i].in;
     while(p!=NULL){
         printf("%d [%d]-> ",p->d_id,p->wight);
         p=p->next;
     }
      printf("\n－－－－－－－－\n");
   }
   
}

void IndexTable::DeleteInstTable(InstList *&Inst_table){
    InstNode *p=NULL;   
    InstNode *q=NULL;
    for(int i=0;i<length;i++){
       p=Inst_table[i].in;
       delete []Inst_table[i].Inst_KeyWord;
       while(p!=NULL){
          
          q=p;
          p=p->next;
          delete q;
         // q=NULL;
       }

    }
 
   delete []Inst_table;

}

InstBit **IndexTable::TestSearch(Instruct &t,InstList *Inst_table,int length){
     cout<<"---请输入您想检索的内容---"<<endl;
     char in[5];
     string str;
     unsigned char *s;
     
     scanf("%s",in);
     str = Utf8ToGbk(in);
     int num = str.size();
     InstByte *InstWord = new InstByte[num];
     s=(unsigned char *)str.c_str();
     //cout<<num<<endl;
     t.KeytoInstByte(s,num,InstWord);
     t.Encrypt(InstWord,num);
     
     return t.search(InstWord,Inst_table,length);
}


