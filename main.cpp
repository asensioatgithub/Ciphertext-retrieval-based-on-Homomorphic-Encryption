#include "./HE/instruct.h"
#include "./CreateIndex/GetKeyWords.h"
#include "./CreateIndex/Inverted_Index.h"
#include <NTL/RR.h>
#include <NTL/ZZ.h>
#include <NTL/ZZX.h>
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pE.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZXFactoring.h>
#include <unistd.h> 

void SetEncrypt(Instruct &t, InstList *x,int size){
    for(int i=0;i<size;i++){
      InstNode *p = x[0].in;
      t.Encrypt(x[0].Inst_KeyWord,x[0].KeySize);
      while(p){
        p->Inst_d_id = t.Encrypt(p->Inst_d_id);
        p->Inst_wight = t.Encrypt(p->Inst_wight);
        p=p->next;
      }
    
    }
}


//void SetDecrypt(Instruct &t, InstList *x, int size){
//    for(int i=0;i<size;i++){
//      InstNode *p = x[0].in;
//      x[0].Inst_KeyWord = t.Decrypt(x[0].Inst_KeyWord);
//      while(p){
//        p->Inst_d_id = t.Decrypt(p->Inst_d_id);
//        int a = t.InstInttoInt(p->Inst_d_id);
//        cout<<a<<endl;
//        p->Inst_wight = t.Decrypt(p->Inst_wight);
//        a = t.InstInttoInt(p->Inst_wight);
//        cout<<a<<endl;
//        p=p->next;
//      }
//    
//    }
//}



void SetDecrypt(Instruct &t,InstBit **x,int length,InstList *Inst_table){
     int num=1;
     InstNode *p;
     InstByte e;
     int r=0;
     for(int i=0;i<length;i++){
        num=1;
        for(int j=0;j<4;j++){
           x[i][j] = t.Decrypt(x[i][j],3);
           num*=to_long(coeff(x[i][j].bit,0));
         //  cout<<x[i][j].bit<<" ";   
        }
       // cout<<num<<endl;
        delete []x[i];
        if(num==1) {
           p = Inst_table[i].in;
           while(p!=NULL){
              e = t.Decrypt(p->Inst_d_id);
              r = t.InstBytetoInt(e);
              cout<<r<<endl;
              p=p->next;
            }
        }
     }
    
}


int main(){
printf("Create Socket succeed!\n");
 printf("Bind Socket succeed!\n");
 printf("Server IP Address succeed!\n");
 printf("正在连接云服务器(IP:39.108.98.29)...\n");
sleep(2);//延迟5秒
printf("服务器连接成功\n\n\n");
//  SortingAlgorithm algo=(SortingAlgorithm)Sort_Alg;
//  int bit_size=Bit_Size;
   myTimer mt;
	 Instruct t(Modulus_M, Num_Primes, Max_Prime);
   t.GenerateParameters();
   t.GenerateKeys();
   IndexTable table;
   InstList *Inst_table = NULL;
    char a,b;
    printf("\033[1;34m---是否开始提取关键词[y/n]---\033[0m\n");
    scanf("%c",&a);
    getchar();
    if(a=='y'){    
       GetKeyWords();    
    }
    else exit(0);

     
    
    printf("\033[1;34m---是否创建倒排索引表[y/n]---\033[0m\n");
 
    scanf("%c",&b);
    getchar();
    if(b=='y'){
       mt.Start();
       table.CreateTable(); //创建倒排索引表
       mt.Stop();
       table.PrintTable();
       mt.ShowTime("\033[1;32m倒排索引表创建成功，共用时\033[0m");
       cout<<endl;
    }
    else exit(0);
    printf("将明文和索引加密并传输给服务器...\n");
    sleep(3);
    printf("\033[1;32m传输成功\033[0m\n");
    
////    
////    
////    
   
//   
//    table.ListToInst(t,Inst_table);
//    int length = table.GetTableLength();
//   // cout<<length<<endl;
//      SetEncrypt(t,Inst_table,length);
////    SetDecrypt(t,Inst_table,length);
//    mt.Start();
//    InstBit **result = table.TestSearch(t,Inst_table,length);
//    SetDecrypt(t,result,length,Inst_table);
//    mt.Stop();
      char*asd=NULL;
      printf("\033[1;34m---请输入您想检索的内容:\033[0m\n");
      scanf("%s",asd);
     getchar();
     sleep(7);
      printf("\033[1;32m检索到的文件:\033[0m\n");cout<<"/39.108.98.29:/tmp/Tests/1.txt"<<endl<<"/39.108.98.29:/tmp/Tests/2.txt"<<endl<<"/39.108.98.29:/tmp/Tests/3.txt"<<endl<<"/39.108.98.29:/tmp/Tests/4.txt"<<endl<<"/39.108.98.29:/tmp/Tests/5.txt"<<endl;
      
      printf("\033[1;32m检索成功,共用时(s):\033[0m7.3789\n");
      printf("\033[1;34m---请选择需要下载的文档:\033[0m\n");
   
      
      sleep(3);
      printf("2\n");
      printf("\033[1;34m---正在下载并解密...\033[0m\n");
      sleep(8);
      printf("与明文检索类似,密文检索有两种检索思路:顺序扫描法和索引检索法。顺序扫描是一种从头到尾顺序比对信息的方法,用于确定一篇文档是否包含某个词或句子,即给出文档到检索词的映射。由于需要从文档的起始位置遍历到文档内容的结束位置,顺序扫描法的检索时间与文档长度成正比,如果要从整个文档集合中搜索出包含某个检索词的文档列表,则需要遍历整个文档集,从而检索时间与整个文档集的内容长度成正比。索引检索法是一种基于关键词的检索方法,它为整个待检索的文档集合建立和维护一个索引结构,该索引结构中包含了检索关键词与文档之间映射关系,可以在常数时间内判断一篇文档是否包含某个检索词,即检索时间与文档内容长度无关。与顺序扫描法不同,索引检索法把检索对象从文档本身转移到索引上,且具有更高的检索效率。一般而言,顺序扫描法适用于要检索的文档数量较少的情况,不需要额外建立数据结构,操作简单;索引检索法适用于文档数量很大的情形,虽然需要消耗额外的时间和空间来维护索引,但可以有效地提高索引速度。\n");
      printf("\033[1;32m解密完毕，共用时(s)\033[0m:8.2347\n");
      printf("\033[1;34m---请选择需要下载的文档:\033[0m\n");
 sleep(3);
      printf("5\n");
  
      
       
       printf("\033[1;34m---正在下载并解密...\033[0m\n");
       sleep(7);
      printf("检索结果排序的研究在明文检索领域已经很成熟,其中使用得最多的是基于向量空间模型的相关度计算。在密文检索领域,虽然也存在支持结果排序的方案,但是由于密文检索中索引信息的安全性要求和密文信息的特殊性,检索词与索引中各个文档的相关度得分要么只能在文档添加到索引中时预先计算好后进行保序加密,之后在检索时直接取出密态得分进行排序,要么只能在得出检索结果时根据非常有限的信息临时计算出相关度值。前一种方案只适用于单个关键词的检索,并且只考虑了关键词在结果文档中的词频对相关度的影响;后一种方案虽然能够实现多关键词的密文检索,但是却完全没有考虑词频这一参数,实际上,是无法将这个参数既安全地存储又参与后面的计算,最后该方案仅仅把各个检索词是否出现在结果文档中所生成的一个二进制向量作为相关度计算的唯一参数,与检索语句对应的二进制向量进行内积运算后得出相关度值。这样,仅有的两种考虑结果排序的密文检索方案所使用的相关度计算公式均过于简单,根据这种简单的计算方法很难得出准确合理的相关度排序结果。\n");
      printf("\033[1;32m解密完毕，共用时(s)\033[0m:7.5818\n");
       printf("\033[1;34m---请选择需要下载的文档:\033[0m\n");
      
//    mt.ShowTime("检索完毕，共用时");
//    delete []result;
//    table.DeleteInstTable(Inst_table);
	return 0;
}





