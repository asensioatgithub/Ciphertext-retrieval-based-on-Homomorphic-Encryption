/****************************************************************************
 *
 * NLPIR/ICTCLAS Lexical Analysis System Copyright (c) 2000-2014
 *     Dr. Kevin Zhang (Hua-Ping Zhang)
 *     All rights reserved.
 *
 * This file is the confidential and proprietary property of 
 * Kevin Zhang and the possession or use of this file requires 
 * a written license from the author.
 * Filename: 
 * Abstract:
 *          NLPIR.h: definition of the NLPIR lexical analysis system API
 * Author:   Kevin Zhang 
 *          Email: pipy_zhang@msn.com kevinzhang@bit.edu.cn
 *			Weibo: http://weibo.com/drkevinzhang
 *			Homepage: http://ictclas.nlpir.org
 * Date:     2013-12-19
 *
 * Notes:
 *                
 ****************************************************************************/
#if !defined(__NLPIR_ICTCLAS_2014_H_INCLUDED__)
#define __NLPIR_ICTCLAS_2014_H_INCLUDED__

#ifdef OS_LINUX
	#define NLPIR_API extern "C" 
#else
#ifdef NLPIR_EXPORTS
#define NLPIR_API extern "C" __declspec(dllexport)
#else
#define NLPIR_API extern "C"  __declspec(dllimport)
#endif
#endif

//ÄÚ²¿¼æÈÝÊ¹ÓÃ

#ifdef NLPIR_INTERNAL_CALL
#define NLPIR_API 
#endif


//////////////////////////////////////////////////////////////////////////
//
//ÒÔÏÂ¶¨ÒåÎª¼æÈÝICTCLASÒÔÇ°µÄ°æ±¾
//
//////////////////////////////////////////////////////////////////////////
#define ICTCLAS_Init NLPIR_Init
#define ICTCLAS_Exit NLPIR_Exit
#define ICTCLAS_ImportUserDict  NLPIR_ImportUserDict
#define ICTCLAS_FileProcess NLPIR_FileProcess
#define ICTCLAS_ParagraphProcess  NLPIR_ParagraphProcess 
#define ICTCLAS_ParagraphProcessA  NLPIR_ParagraphProcessA 
#define ICTCLAS_GetParagraphProcessAWordCount   NLPIR_GetParagraphProcessAWordCount 
#define ICTCLAS_ParagraphProcessAW   NLPIR_ParagraphProcessAW 
#define ICTCLAS_AddUserWord  NLPIR_AddUserWord
#define ICTCLAS_SaveTheUsrDic  NLPIR_SaveTheUsrDic
#define ICTCLAS_DelUsrWord  NLPIR_DelUsrWord
#define ICTCLAS_GetUniProb  NLPIR_GetUniProb
#define ICTCLAS_IsWord  NLPIR_IsWord
#define ICTCLAS_SetPOSmap  NLPIR_SetPOSmap
#define CICTCLAS  CNLPIR
#define GetActiveICTCLAS GetActiveInstance 


#define POS_MAP_NUMBER 4 //add by qp 2008.11.25
#define ICT_POS_MAP_FIRST 1  //¼ÆËãËùÒ»¼¶±ê×¢¼¯
#define ICT_POS_MAP_SECOND 0 //¼ÆËãËù¶þ¼¶±ê×¢¼¯
#define PKU_POS_MAP_SECOND 2 //±±´ó¶þ¼¶±ê×¢¼¯
#define PKU_POS_MAP_FIRST 3	//±±´óÒ»¼¶±ê×¢¼¯
#define  POS_SIZE 40

struct result_t{
  int start; //start position,´ÊÓïÔÚÊäÈë¾ä×ÓÖÐµÄ¿ªÊ¼Î»ÖÃ
  int length; //length,´ÊÓïµÄ³¤¶È
  char  sPOS[POS_SIZE];//word type£¬´ÊÐÔIDÖµ£¬¿ÉÒÔ¿ìËÙµÄ»ñÈ¡´ÊÐÔ±í
  int	iPOS;//´ÊÐÔ±ê×¢µÄ±àºÅ
  int word_ID; //¸Ã´ÊµÄÄÚ²¿IDºÅ£¬Èç¹ûÊÇÎ´µÇÂ¼´Ê£¬Éè³É0»òÕß-1
  int word_type; //Çø·ÖÓÃ»§´Êµä;1£¬ÊÇÓÃ»§´ÊµäÖÐµÄ´Ê£»0£¬·ÇÓÃ»§´ÊµäÖÐµÄ´Ê
  int weight;//word weight,read weight
 };

#define GBK_CODE 0//Ä¬ÈÏÖ§³ÖGBK±àÂë
#define UTF8_CODE GBK_CODE+1//UTF8±àÂë
#define BIG5_CODE GBK_CODE+2//BIG5±àÂë
#define GBK_FANTI_CODE GBK_CODE+3//GBK±àÂë£¬ÀïÃæ°üº¬·±Ìå×Ö
#define UTF8_FANTI_CODE GBK_CODE+4//UTF8±àÂë

/*********************************************************************
 *
 *  Func Name  : Init
 *
 *  Description: Init NLPIR
 *               The function must be invoked before any operation listed as following
 *
 *  Parameters : const char * sInitDirPath=NULL
 *				 sDataPath:  Path where Data directory stored.
 *				 the default value is NULL, it indicates the initial directory is current working directory path
 *				 encode: encoding code;
 *				 sLicenseCode: license code for unlimited usage. common user ignore it
 *  Returns    : success or fail
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2013-6-8
 *********************************************************************/
NLPIR_API int NLPIR_Init(const char * sDataPath=0,int encode=GBK_CODE,const char*sLicenceCode=0);
/*********************************************************************
 *
 *  Func Name  : NLPIR_Exit
 *
 *  Description: Exist NLPIR and free related buffer
 *               Exit the program and free memory
 *				 The function must be invoked while you needn't any lexical anlysis
 *
 *  Parameters : None
 *
 *  Returns    : success or fail
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2002-8-6
 *********************************************************************/
NLPIR_API bool NLPIR_Exit();
/*********************************************************************
 *
 *  Func Name  : ParagraphProcessing
 *
 *  Description: Process a paragraph
 *    
 *
 *  Parameters : sParagraph: The source paragraph 
 *               
 *				 bPOStagged:Judge whether need POS tagging, 0 for no tag;default:1
 *				i.e.  ÕÅ»ªÆ½ÓÚ1978Äê3ÔÂ9ÈÕ³öÉúÓÚ½­Î÷Ê¡²¨ÑôÏØ¡£
 *					Result: ÕÅ»ªÆ½/nr  ÓÚ/p  1978Äê/t  3ÔÂ/t  9ÈÕ/t  ³öÉúÓÚ/v  ½­Î÷Ê¡/ns  ²¨ÑôÏØ/ns  ¡£/w   
 *  Returns    : the result buffer pointer 
 *
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2003-12-22
 *********************************************************************/
NLPIR_API const char * NLPIR_ParagraphProcess(const char *sParagraph,int bPOStagged=1);
/*********************************************************************
 *
 *  Func Name  : NLPIR_GetLastErrorMsg
 *
 *  Description: GetLastErrorMessage
 *    
 *
 *  Parameters : void
 *               
 *				  
 *  Returns    : the result buffer pointer 
 *
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2014-2-27
 *********************************************************************/
NLPIR_API const char * NLPIR_GetLastErrorMsg();
/*********************************************************************
 *
 *  Func Name  : ParagraphProcessingA
 *
 *  Description: Process a paragraph
 *    
 *
 *  Parameters : sParagraph: The source paragraph 
 *               pResultCount: pointer to result vector size
 *  Returns    : the pointer of result vector, it is managed by system,user cannot alloc and free it 
 *  Author     :  Kevin Zhang  
 *  History    : 
 *              1.create 2006-10-26
 *********************************************************************/
NLPIR_API const result_t * NLPIR_ParagraphProcessA(const char *sParagraph,int *pResultCount,bool bUserDict=true);

/*********************************************************************
 *
 *  Func Name  : NLPIR_GetParagraphProcessAWordCount
 *
 *  Description: Get ProcessAWordCount, API for C#
 *				 Get word count and it helps us prepare the proper size buffer for result_t vector
 *
 *  Parameters : sParagraph: The source paragraph 
 *               
 *  Returns    : result vector size 
 *  Author     :  Kevin Zhang  
 *  History    : 
 *              1.create 2007-3-15
 *********************************************************************/
NLPIR_API int NLPIR_GetParagraphProcessAWordCount(const char *sParagraph);
/*********************************************************************
 *
 *  Func Name  : NLPIR_ParagraphProcessAW
 *
 *  Description: Process a paragraph, API for C#
 *    
 *
 *  Parameters : sParagraph: The source paragraph 
 *               result_t * result: pointer to result vector size, it is allocated by the invoker
 *  Returns    : None 
 *  Author     :  
 *  History    : 
 *              1.create 2007-3-15
 *********************************************************************/
NLPIR_API void NLPIR_ParagraphProcessAW(int nCount,result_t * result);

/*********************************************************************
 *
 *  Func Name  : NLPIR_FileProcess
 *
 *  Description: Process a text file
 *    
 *
 *  Parameters : sSourceFilename: The source file name  
 *               sResultFilename: The result file name 
 *				 bPOStagged:Judge whether need POS tagging, 0 for no tag;default:1
 *  i.e. FileProcess("E:\\Sample\\Corpus_NewPOS\\199802_Org.txt","E:\\Sample\\Corpus_NewPOS\\199802_Org_cla.txt");
 *  Returns    : success: 
 *               fail: 
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2005-11-22
 *********************************************************************/
NLPIR_API double NLPIR_FileProcess(const char *sSourceFilename,const char *sResultFilename,int bPOStagged=1);

/*********************************************************************
 *
 *  Func Name  : ImportUserDict
 *
 *  Description: Import User-defined dictionary
 *  Parameters : 
 *				sFilename:Text filename for user dictionary 
 *				bOverwrite: true,  overwrite the existing dictionary 
 *						   false, add to  the existing dictionary 		
 *  Returns    : The  number of  lexical entry imported successfully
 *  Author     : Kevin Zhang
 *  History    : 
 *              1.create 2014-8-3
 *********************************************************************/
NLPIR_API unsigned int NLPIR_ImportUserDict(const char *sFilename,bool bOverwrite=true);

/*********************************************************************
 *
 *  Func Name  : NLPIR_ImportKeyBlackList
 *
 *  Description: Import keyword black list 
 *  Parameters : Text filename for user dictionary, each line for a stop keyword
 *  Returns    : The  number of  lexical entry imported successfully
 *  Author     : Kevin Zhang
 *  History    : 
 *              1.create 2014-6-26
 *********************************************************************/
NLPIR_API unsigned int NLPIR_ImportKeyBlackList(const char *sFilename);
/*********************************************************************
*
*  Func Name  : NLPIR_AddUserWord
*
*  Description: add a word to the user dictionary ,example:ÄãºÃ	
*													 i3s	n
*
*  Parameters : sFilename: file name
*               
*  Returns    : 1,true ; 0,false
*
*  Author     :   
*  History    : 
*              1.create 11:10:2008
*********************************************************************/
NLPIR_API int NLPIR_AddUserWord(const char *sWord);//add by qp 2008.11.10

/*********************************************************************
*
*  Func Name  : Save
*
*  Description: Save dictionary to file
*
*  Parameters :
*               
*  Returns    : 1,true; 2,false
*
*  Author     :   
*  History    : 
*              1.create 11:10:2008
*********************************************************************/
NLPIR_API int NLPIR_SaveTheUsrDic();

/*********************************************************************
*
*  Func Name  : NLPIR_DelUsrWord
*
*  Description: delete a word from the  user dictionary
*
*  Parameters : 
*  Returns    : -1, the word not exist in the user dictionary; else, the handle of the word deleted
*
*  Author     :   
*  History    : 
*              1.create 11:10:2008
*********************************************************************/
NLPIR_API int NLPIR_DelUsrWord(const char *sWord);

/*********************************************************************
*
*  Func Name  : NLPIR_GetUniProb
*
*  Description: Get Unigram Probability
*    
*
*  Parameters : sWord: input word 
*  Returns    : success: 
*               fail: 
*  Author     : Kevin Zhang  
*  History    : 
*              1.create 2005-11-22
*********************************************************************/
NLPIR_API double NLPIR_GetUniProb(const char *sWord);
/*********************************************************************
*
*  Func Name  : NLPIR_IsWord
*
*  Description: Judge whether the word is included in the core dictionary
*    
*
*  Parameters : sWord: input word 
*  Returns    : success: 
*               fail: 
*  Author     : Kevin Zhang  
*  History    : 
*              1.create 2005-11-22
*********************************************************************/
NLPIR_API int NLPIR_IsWord(const char *sWord);

/*********************************************************************
*
*  Func Name  : NLPIR_GetWordPOS
*
*  Description: Get the word Part-Of-Speech¡¡information
*    
*
*  Parameters : sWord: input word 
*
*  Returns    : success: 
*               fail: 
*  Author     : Kevin Zhang  
*  History    : 
*              1.create 2014-10-10
*********************************************************************/
NLPIR_API const char * NLPIR_GetWordPOS(const char *sWord);

/*********************************************************************
*
*  Func Name  : NLPIR_GetKeyWords
*
*  Description: Extract keyword from sLine
*
*  Parameters : sLine, the input paragraph 
				bArguOut,whether  the keyword weight output
				nMaxKeyLimt:maximum of key words, up to 50
*  Returns    : keywords list like:
*               "¿ÆÑ§·¢Õ¹¹Û ºê¹Û¾­¼Ã " or
				"¿ÆÑ§·¢Õ¹¹Û/23.80/12#ºê¹Û¾­¼Ã/12.20/1" with weight(ÐÅÏ¢ìØ¼ÓÉÏ´ÊÆµÐÅÏ¢)
*
*  Author     :   
*  History    : 
*              1.create 2012/11/12
*********************************************************************/
NLPIR_API const char * NLPIR_GetKeyWords(const char *sLine,int nMaxKeyLimit=50,bool bWeightOut=false);

/*********************************************************************
*
*  Func Name  : NLPIR_GetFileKeyWords
*
*  Description: Extract keyword from a text file
*
*  Parameters : sFilename, the input text file name 
				bArguOut,whether  the keyword weight output
				nMaxKeyLimt:maximum of key words, up to 50
*  Returns    : keywords list like:
*               "¿ÆÑ§·¢Õ¹¹Û ºê¹Û¾­¼Ã " or
				"¿ÆÑ§·¢Õ¹¹Û 23.80 ºê¹Û¾­¼Ã 12.20" with weight

*
*  Author     :   
*  History    : 
*              1.create 2012/11/12
*********************************************************************/
NLPIR_API const char * NLPIR_GetFileKeyWords(const char *sFilename,int nMaxKeyLimit=50,bool bWeightOut=false);
/*********************************************************************
*
*  Func Name  : NLPIR_GetNewWords
*
*  Description: Extract New words from sLine
*
*  Parameters : sLine, the input paragraph 
				bArguOut,whether  the keyword weight output
				nMaxKeyLimt:maximum of key words, up to 50
*  Returns    : new words list like:
*               "¿ÆÑ§·¢Õ¹¹Û ÅË¿ "or
				"¿ÆÑ§·¢Õ¹¹Û 23.80 ÅË¿ 12.20" with weight
*
*  Author     :   
*  History    : 
*              1.create  2012/11/12
*********************************************************************/
NLPIR_API const char * NLPIR_GetNewWords(const char *sLine,int nMaxKeyLimit=50,bool bWeightOut=false);

/*********************************************************************
*
*  Func Name  : NLPIR_GetFileNewWords
*
*  Description: Extract new words from a text file
*
*  Parameters : sFilename, the input text file name 
				bArguOut,whether  the keyword weight output
				nMaxKeyLimt:maximum of key words, up to 50
*  Returns    : keywords list like:
*               "¿ÆÑ§·¢Õ¹¹Û ºê¹Û¾­¼Ã " or
				"¿ÆÑ§·¢Õ¹¹Û 23.80 ºê¹Û¾­¼Ã 12.20" with weight

*
*  Author     :   
*  History    : 
*              1.create 2012/11/12
*********************************************************************/
NLPIR_API const char * NLPIR_GetFileNewWords(const char *sFilename,int nMaxKeyLimit=50,bool bWeightOut=false);
/*********************************************************************
*
*  Func Name  : NLPIR_FingerPrint
*
*  Description: Extract a finger print from the paragraph
*
*  Parameters :
*  Returns    : 0, failed; else, the finger print of the content
*
*  Author     :   
*  History    : 
*              1.create 11:10:2008
*********************************************************************/
NLPIR_API unsigned long NLPIR_FingerPrint(const char *sLine);

/*********************************************************************
*
*  Func Name  : NLPIR_SetPOSmap
*
*  Description: select which pos map will use
*
*  Parameters :nPOSmap, ICT_POS_MAP_FIRST  ¼ÆËãËùÒ»¼¶±ê×¢¼¯
						ICT_POS_MAP_SECOND  ¼ÆËãËù¶þ¼¶±ê×¢¼¯
						PKU_POS_MAP_SECOND   ±±´ó¶þ¼¶±ê×¢¼¯
						PKU_POS_MAP_FIRST 	  ±±´óÒ»¼¶±ê×¢¼¯
*  Returns    : 0, failed; else, success
*
*  Author     :   
*  History    : 
*              1.create 11:10:2008
*********************************************************************/
NLPIR_API int NLPIR_SetPOSmap(int nPOSmap);


/*********************************************************************
*
*  class CNLPIR
*   ÃèÊö£º
*		   NLPIR Àà£¬Ê¹ÓÃÖ®Ç°±ØÐëµ÷ÓÃNLPIR_Init(),ÍË³ö±ØÐëµ÷ÓÃNLPIR_Exit
*		   ÔÚÊ¹ÓÃ¹ý³ÌÖÐ¿ÉÒÔÊ¹ÓÃ¶à·ÝCNLPIR£¬Ö§³Ö¶àÏß³Ì·Ö´Ê´¦Àí
*			Ã¿¸öÏß³ÌÏÈµ÷ÓÃGetActiveInstance£¬»ñÈ¡´¦ÀíÀà£¬È»ºó£¬ÉèÖÃSetAvailable(false)ÐûÊ¾Ïß³ÌÖ÷È¨£¬
*			´¦ÀíÍê³Éºó£¬SetAvailable(true)ÊÍ·ÅÏß³ÌÖ÷È¨
*  History    : 
*              1.create 2005-11-10
*********************************************************************/
#ifdef OS_LINUX
class  CNLPIR {
#else
class  __declspec(dllexport) CNLPIR {
#endif
	public:
		CNLPIR();
		~CNLPIR();
		double FileProcess(const char *sSourceFilename,const char *sResultFilename,int bPOStagged=1);
		//Process a file£¬ÀàËÆÓÚCÏÂµÄNLPIR_FileProcess
		const char * ParagraphProcess(const char *sLine,int bPOStagged=1); 
		//Process a file£¬ÀàËÆÓÚCÏÂµÄNLPIR_ParagraphProcess
		const result_t * ParagraphProcessA(const char *sParagraph,int *pResultCount,bool bUserDict=true);
		//Process a file£¬ÀàËÆÓÚCÏÂµÄNLPIR_ParagraphProcessA

		void ParagraphProcessAW(int nCount,result_t * result);
		int GetParagraphProcessAWordCount(const char *sParagraph);

		const char * GetKeyWords(const char *sLine,int nMaxKeyLimit,bool bWeightOut);
		//»ñÈ¡¹Ø¼ü´Ê
		const char * GetFileKeyWords(const char *sFilename,int nMaxKeyLimit,bool bWeightOut);
		//´ÓÎÄ±¾ÎÄ¼þÖÐ»ñÈ¡¹Ø¼ü´Ê
		const char * GetNewWords(const char *sFilename,int nMaxKeyLimit,bool bWeightOut);
		//»ñÈ¡ÐÂ´Ê
		const char * GetFileNewWords(const char *sFilename,int nMaxKeyLimit,bool bWeightOut);
		//´ÓÎÄ±¾ÎÄ¼þÖÐ»ñÈ¡ÐÂ´Ê

		bool SetAvailable(bool bAvailable=true);//µ±Ç°Ïß³ÌÊÍ·Å¸ÃÀà£¬¿ÉÎªÏÂÒ»¸öÏß³ÌÊ¹ÓÃ
		bool IsAvailable();//ÅÐ¶Ïµ±Ç°·Ö´ÊÆ÷ÊÇ·ñ±»Ïß³ÌÕ¼ÓÃ
		unsigned int GetHandle()
		{
			return m_nHandle;
		}
private:
		unsigned int m_nHandle;//¸Ã³ÉÔ±×÷Îª¸ÃÀàµÄHandleÖµ£¬ÓÉÏµÍ³×Ô¶¯·ÖÅä£¬ÓÃ»§²»¿ÉÐÞ¸Ä
		bool m_bAvailable;//¸Ã³ÉÔ±×÷Îª¶àÏß³Ì¹²Ïí¿ØÖÆµÄ²ÎÊý£¬ÓÉÏµÍ³×Ô¶¯·ÖÅä£¬ÓÃ»§²»¿ÉÐÞ¸Ä
		int m_nThreadCount;//Thread Count
		bool m_bWriting;//writing  protection
};

/*********************************************************************
*
*  Func Name  : GetActiveInstance
*
*  Description: »ñÈ¡¿ÉÓÃµÄCNLPIRÀà£¬ÊÊÓÃÓÚ¶àÏß³Ì¿ª·¢£¬ÏÈ»ñÈ¡¿ÉÓÃµÄCNLP£¬ÔÙµ÷ÓÃÆäÖÐµÄ¹¦ÄÜ

*
*  Parameters : None
*  Returns    : CNLPIR*
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 1:10:2012
*********************************************************************/
NLPIR_API CNLPIR* GetActiveInstance();

/*********************************************************************
*
*  ÒÔÏÂº¯ÊýÎª2013°æ±¾×¨ÃÅÕë¶ÔÐÂ´Ê·¢ÏÖµÄ¹ý³Ì£¬Ò»°ã½¨ÒéÍÑ»úÊµÏÖ£¬²»ÒËÔÚÏß´¦Àí
*  ÐÂ´ÊÊ¶±ðÍê³Éºó£¬ÔÙ×Ô¶¯µ¼Èëµ½·Ö´ÊÏµÍ³ÖÐ£¬¼´¿ÉÍê³É
*  º¯ÊýÒÔNLPIR_NWI(New Word Identification)¿ªÍ·
*********************************************************************/
/*********************************************************************
*
*  Func Name  : NLPIR_NWI_Start
*
*  Description: Æô¶¯ÐÂ´ÊÊ¶±ð

*
*  Parameters : None
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2013/11/23
*********************************************************************/
NLPIR_API int NLPIR_NWI_Start();//New Word Indentification Start
/*********************************************************************
*
*  Func Name  : NLPIR_NWI_AddFile
*
*  Description: ÍùÐÂ´ÊÊ¶±ðÏµÍ³ÖÐÌí¼Ó´ýÊ¶±ðÐÂ´ÊµÄÎÄ±¾ÎÄ¼þ
*				ÐèÒªÔÚÔËÐÐNLPIR_NWI_Start()Ö®ºó£¬²ÅÓÐÐ§
*
*  Parameters : const char *sFilename£ºÎÄ¼þÃû
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 20132/11/23
*********************************************************************/
NLPIR_API int  NLPIR_NWI_AddFile(const char *sFilename);
/*********************************************************************
*
*  Func Name  : NLPIR_NWI_AddMem
*
*  Description: ÍùÐÂ´ÊÊ¶±ðÏµÍ³ÖÐÌí¼ÓÒ»¶Î´ýÊ¶±ðÐÂ´ÊµÄÄÚ´æ
*				ÐèÒªÔÚÔËÐÐNLPIR_NWI_Start()Ö®ºó£¬²ÅÓÐÐ§
*
*  Parameters : const char *sFilename£ºÎÄ¼þÃû
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2013/11/23
*********************************************************************/
NLPIR_API int NLPIR_NWI_AddMem(const char *sText);
/*********************************************************************
*
*  Func Name  : NLPIR_NWI_Complete
*
*  Description: ÐÂ´ÊÊ¶±ðÌí¼ÓÄÚÈÝ½áÊø
*				ÐèÒªÔÚÔËÐÐNLPIR_NWI_Start()Ö®ºó£¬²ÅÓÐÐ§
*
*  Parameters : None
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2013/11/23
*********************************************************************/
NLPIR_API int NLPIR_NWI_Complete();//ÐÂ´Ê
/*********************************************************************
*
*  Func Name  : NLPIR_NWI_GetResult
*
*  Description: »ñÈ¡ÐÂ´ÊÊ¶±ðµÄ½á¹û
*				ÐèÒªÔÚÔËÐÐNLPIR_NWI_Complete()Ö®ºó£¬²ÅÓÐÐ§
*
*  Parameters : bWeightOut£ºÊÇ·ñÐèÒªÊä³öÃ¿¸öÐÂ´ÊµÄÈ¨ÖØ²ÎÊý
*
*  Returns    : Êä³ö¸ñÊ½Îª
*				¡¾ÐÂ´Ê1¡¿ ¡¾È¨ÖØ1¡¿ ¡¾ÐÂ´Ê2¡¿ ¡¾È¨ÖØ2¡¿ ... 
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2013/11/23
*********************************************************************/
NLPIR_API const char * NLPIR_NWI_GetResult(bool bWeightOut=false);//Êä³öÐÂ´ÊÊ¶±ð½á¹û
/*********************************************************************
*
*  Func Name  : NLPIR_NWI_Result2UserDict
*
*  Description: ½«ÐÂ´ÊÊ¶±ð½á¹ûµ¼Èëµ½ÓÃ»§´ÊµäÖÐ
*				ÐèÒªÔÚÔËÐÐNLPIR_NWI_Complete()Ö®ºó£¬²ÅÓÐÐ§
*				Èç¹ûÐèÒª½«ÐÂ´Ê½á¹ûÓÀ¾Ã±£´æ£¬½¨ÒéÔÚÖ´ÐÐNLPIR_SaveTheUsrDic
*  Parameters : None
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2013/11/23
*********************************************************************/
NLPIR_API unsigned int  NLPIR_NWI_Result2UserDict();//ÐÂ´ÊÊ¶±ð½á¹û×ªÎªÓÃ»§´Êµä,·µ»ØÐÂ´Ê½á¹ûÊýÄ¿
/*********************************************************************
*
*  Func Name  : NLPIR_FinerSegment(const char *sLine)
*
*  Description: µ±Ç°µÄÇÐ·Ö½á¹û¹ý´óÊ±£¬Èç¡°ÖÐ»ªÈËÃñ¹²ºÍ¹ú¡±
*				ÐèÒªÖ´ÐÐ¸Ãº¯Êý£¬½«ÇÐ·Ö½á¹ûÏ¸·ÖÎª¡°ÖÐ»ª ÈËÃñ ¹²ºÍ¹ú¡±
*				Ï¸·ÖÁ£¶È×î´óÎªÈý¸öºº×Ö
*  Parameters : sLine:ÊäÈëµÄ×Ö·û´®
*  Returns    : ·µ»ØµÄÏ¸·Ö´®£¬Èç¹û²»ÄÜÏ¸·Ö£¬Ôò·µ»ØÎª¿Õ×Ö·û´®""
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2014/10/10
*********************************************************************/
NLPIR_API const char*  NLPIR_FinerSegment(const char *sLine);
/*********************************************************************
*
*  Func Name  : NLPIR_GetEngWordOrign(const char *sWord)
*
*  Description: »ñÈ¡¸÷ÀàÓ¢ÎÄµ¥´ÊµÄÔ­ÐÍ£¬¿¼ÂÇÁË¹ýÈ¥·Ö´Ê¡¢µ¥¸´ÊýµÈÇé¿ö
*  Parameters : sWord:ÊäÈëµÄµ¥´Ê
*  Returns    : ·µ»ØµÄ´ÊÔ­ÐÍÐÎÊ½
*               driven->drive   drives->drive   drove-->drive
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2014/12/11
*********************************************************************/
NLPIR_API const char*  NLPIR_GetEngWordOrign(const char *sWord);

/*********************************************************************
*
*  Func Name  : NLPIR_WordFreqStat(const char *sText)
*
*  Description: »ñÈ¡ÊäÈëÎÄ±¾µÄ´Ê£¬´ÊÐÔ£¬ÆµÍ³¼Æ½á¹û£¬°´ÕÕ´ÊÆµ´óÐ¡ÅÅÐò
*  Parameters : sWord:ÊäÈëµÄÎÄ±¾ÄÚÈÝ
*  Returns    : ·µ»ØµÄÊÇ´ÊÆµÍ³¼Æ½á¹ûÐÎÊ½ÈçÏÂ£º
*				ÕÅ»ªÆ½/nr/10#²©Ê¿/n/9#·Ö´Ê/n/8
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2014/12/11
*********************************************************************/
NLPIR_API const char*  NLPIR_WordFreqStat(const char *sText);
/*********************************************************************
*
*  Func Name  : NLPIR_FileWordFreqStat(const char *sFilename)
*
*  Description: »ñÈ¡ÊäÈëÎÄ±¾µÄ´Ê£¬´ÊÐÔ£¬ÆµÍ³¼Æ½á¹û£¬°´ÕÕ´ÊÆµ´óÐ¡ÅÅÐò
*  Parameters : sWord:ÊäÈëµÄÎÄ±¾ÄÚÈÝ
*  Returns    : ·µ»ØµÄÊÇ´ÊÆµÍ³¼Æ½á¹ûÐÎÊ½ÈçÏÂ£º
*				ÕÅ»ªÆ½/nr/10#²©Ê¿/n/9#·Ö´Ê/n/8
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2014/12/11
*********************************************************************/
NLPIR_API const char*  NLPIR_FileWordFreqStat(const char *sFilename);

#endif//#define __NLPIR_ICTCLAS_2014_H_INCLUDED__
