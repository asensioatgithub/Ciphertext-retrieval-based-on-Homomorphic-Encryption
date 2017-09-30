#ifndef INVERTED_INDEX_H_
#define INVERTED_INDEX_H_

#include "stdio.h"
#include "stdlib.h"

#include "../HE/instruct.h"

struct IndexNode{
   int d_id;              //关键词所在文本ID
   int wight;             //关键词在该文本中的权值
   struct IndexNode *next = NULL;//指向下一个节点的指针
};


struct IndexList{
  char* KeyWord;   //关键词
  IndexNode *in=NULL;   //为每一个List初始化一个指向IndexNode的指针
  IndexNode *tail=NULL; //tail指向最后一个节点
  int size =0;    //记录每行索引表的长度
};


class IndexTable{

 private:
   int TableSize ;     //索引表的容量
   int length;
   IndexList * it = NULL;     //为table初始化一个指向IndexList的指针
   
   
 public:
 
   IndexTable();
   ~IndexTable(){
      IndexNode* p=NULL,*q=NULL;
      for(int i=0;i<length;i++){
         delete []it[i].KeyWord;
         p=it[i].in;
         while(p!=NULL){
            q=p;  //保存当前节点
            p=p->next;
            free(q);
         }
      }
      free(it);
   }
   
   int SearchKeyWord(char *k);  //检索关键词in是否在索引表中,如果存在便返回位置
   int GetTableLength();
   int GetListLength(int i);    //获取索引表i的长度
   void InsertWord(char *k,int id,int w);
   void CreateTable();
   void PrintTable();          //输出索引表 
   void ListToInst(Instruct &t,InstList *&Inst_table);
   void DeleteInstTable(InstList *&Inst_table);
   InstBit **TestSearch(Instruct &t,InstList *Inst_table,int length);
   IndexNode *NewNode(int id,int w);
   
};

#endif /* INVERTED_INDEX_H_ */
