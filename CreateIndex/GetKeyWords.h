#ifndef INDEX_H_
#define INDEX_H_

#include "NLPIR.h"
#include "stdlib.h"
#include "stdio.h"
#include <dirent.h>
#include <string.h>     //strcat()
#include "time.h"       //clock() clock_t
#include<regex.h>
#include<memory.h>
#include <curses.h>
char *pattern1 = "([\u4e00-\u9fa5]+)([0-9].[0-9]+)";

char *join(char *a, char *b) {  
    char *c = (char *) malloc(strlen(a) + strlen(b) + 1); //局部变量，用malloc申请内存  
    if (c == NULL) exit (1);  
    char *tempc = c;                                      //把首地址存下来  
    while (*a != '\0') {  
        *c++ = *a++;  
    }  
    while ((*c++ = *b++) != '\0') {  
        ;                                                 //注意，此时指针c已经指向拼接之后的字符串的结尾'\0' !
    }    
    c=NULL;
    return tempc;                                         //返回值是局部malloc申请的指针变量，需在函数调用结束后free之  
} 

const char * const strtoberpl[] = {
  "/",
  "nr",
  "vn",
  "n_new",
  "vi",
  "n",
  "v"
};


const char *strrpl( char *s,const char *s1,const char*s2){
  char *ptr=NULL;
  while(ptr=strstr(s,s1)){
    memmove(ptr+strlen(s2),ptr+strlen(s1),strlen(ptr)-strlen(s1)+1);
    memcpy(ptr,&s2[0],strlen(s2));
  }
}


void KeyWordPrecess( const char *tempc ){
     int i=0; 
     for(;i<7;i++)
      strrpl((char *)tempc,strtoberpl[i],"");
     strrpl((char *)tempc,"#","\n");
}
//提取关键字
void GetKeyWords(){
//int main(){
   // bool NLPIR_Init(const char * sInitDirPath=0， int encoding=GBK_CODE,constchar*sLicenceCode=0);初始化函数
   // sDataPath：Data 文件夹的路径，为空字符串时从项目根目录下开始寻找，一般在使用的时候先把Data放到项目文件里，所以为空
   // encode：编码格式,默认为GBK编码的分词(0：GBK 1：UTF8 2：BIG5 3：GBK)
   
  if(!NLPIR_Init(0,1,0)){
    printf("ICTCLAS INI FAILED!\n");
    exit(0);
   }//else printf("ICTCLAS Success Init!\n");
   
   const char *sResult=NULL;//定义一个指针型字符数组
   clock_t  lStart,lEnd;
   long lTime=0;
	 double fTime=0.0;//Time cost 
	 
	 DIR * dir=NULL;
	 struct dirent * ptr = NULL;
	 
	 if((dir = opendir("Texts"))==NULL){
        printf("opendir failed!");
        exit(0);
    }//else printf("opendir succseed!\n");
	 
	 int i=0;
	 
	 FILE *fp=NULL;
	 if((fp=fopen("KeyWordList.txt","w")) == NULL ){
	    printf("不能打开文件KeyWordList.txt\n");
	    exit(0);
	 }//else printf("成功打开文件KeyWordList.txt\n");
	 lStart=clock();//Record the time
	 
	 char temp[20]="./Texts/";
   char *path=NULL;
   
	 while((ptr=readdir(dir))!= NULL){//顺序处理文本文件
	  if(strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0){
	    i++;
         path=join(temp,ptr->d_name);
	//    printf("%s\n",path);
        sResult=NLPIR_GetFileKeyWords(path,5,true);  
       // NLPIR_FileProcess(path,"./Texts/result.txt",0);
       // free(path);
       KeyWordPrecess(sResult);
     //   printf("%s\n",sResult);
      
      fputs(sResult,fp);
      fputs("\n",fp);
      
     }
   }
   
   
     lEnd=clock();//Record the time
	 lTime=lEnd-lStart;
	 fTime=(double)lTime/(double)CLOCKS_PER_SEC;//Time cost
    fclose(fp);
	 NLPIR_Exit();
   //************输出关键词表**************************************//
   
   FILE *fp1=NULL;
	 if((fp1=fopen("KeyWordList.txt","r")) == NULL ){
	    printf("不能打开文件KeyWordList.txt\n");
	    exit(0);
	 }//else printf("成功打开文件KeyWordList.txt\n");
   char errbuf1[1024];
   char match1[10];
   
   regex_t reg1;
   int err,nm = 11;
   regmatch_t pmatch1[nm];

   
   if(regcomp(&reg1,pattern1,REG_EXTENDED) < 0){ //编译正则表达式
     regerror(err,&reg1,errbuf1,sizeof(errbuf1));
     printf("err:%s\n",errbuf1);
   }
 
   char stringLine[100];  
   int wight=0;
   int line=0;
   
   while ((fgets(stringLine,100,fp1))!=NULL){
         line++;
         if(line%6==1)
         {
         printf("\033[1;34m明文文档：Tesxts/%d.txt\033[0m\n",line/6+1);
         printf(" －－－－－－－－－－－－\n");
         printf("|   关键词      |  权重 |\n");
         printf(" －－－－－－－－－－－－\n");
          } 
      //  box(stdscr,'|','-');
	    if(line%6==0) {
	       printf(" －－－－－－－－－－－－\n");
	      continue;//读取一行
	    }
         err = regexec(&reg1,stringLine,nm,pmatch1,0);
        if(err == REG_NOMATCH)
        {
          printf("no match\n");
          exit(-1);
        }
        else if(err)
        {
          regerror(err,&reg1,errbuf1,sizeof(errbuf1));
           printf("err:%s\n",errbuf1);
          exit(-1);
        }
      
        for(int i=1;i<20 && pmatch1[i].rm_so!=-1&&pmatch1[i+1].rm_so!=-1;i+=2)
        {  
          char *matchKey = new char[20];char *matchWight = new char[10];
          memset(matchKey,'\0',sizeof(matchKey));
           memset(matchWight,'\0',sizeof(matchWight)); 
          int len1 = pmatch1[i].rm_eo-pmatch1[i].rm_so;
          int len2 = pmatch1[i+1].rm_eo-pmatch1[i+1].rm_so;
     
          memcpy(matchKey,stringLine+pmatch1[i].rm_so,len1);
          memcpy(matchWight,stringLine+pmatch1[i+1].rm_so,len2);
       printf("|%-14s\t|%-6s\t|\n",matchKey,matchWight); 
      }  
         
   }
   //printf("\033[8;5Habcd\n");
   
    fclose(fp1);
    
//    initscr();
//    //clear();
//    move(10,20);
//    addstr("Hello, world");
//    move(LINES-1, 0); 
//    //refresh();
//    getch();
//    endwin();
  //************输出关键词表**************************************//   
   
   
   printf("\033[1;32m关键词提取成功，共处理文件数：%d  共耗时(s)：\033[0m%f\n\n\n",i,fTime);

	
   //退出程序并释放所有资源和NLPIR使用的缓存数据。
  

	}
	

	#endif /* INDEX_H_ */
