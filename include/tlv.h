#ifndef _TLV_H_
#define _TLV_H_

#define LEN_TAG	 4	/*Tag最大长度*/


typedef char TTag[LEN_TAG]; /*Tag类型*/


/*Tag标签约束条件(最大长度为0时表示不做约束)*/
typedef struct
{
    TTag Tag;   /*标签*/
    int MinLen; /*最小长度*/
    int MaxLen; /*最大长度*/
} TTagRestriction;

typedef struct
{
    TTag Tag;
    int offset;
    int len;
    char Restriction;
    int iNesting;
} TTagList;

#define TLVERR_NONE			0
#define TLVERR_BASE			0
#define TLVERR_INVALIDTAG		(TLVERR_BASE-1)		/*非法Tag*/
#define TLVERR_INVALIDLENGTH		(TLVERR_BASE-2)		/*非法Length*/
#define TLVERR_DECODEFAIL		(TLVERR_BASE-3)		/*TLV解码失败*/
#define TLVERR_TAGNOTFOUND		(TLVERR_BASE-4)		/*Tag未找到*/
#define TLVERR_INVALIDTAGRESTRICTION	(TLVERR_BASE-5)		/*Tag约束非法*/

/**
@brief		TLV模块初始化

TR.Tag为全0时为约束集的结束标志
@param		TTagRestriction		TR[]	Tag约束集
@return		TLVERR_xxx
 */
extern int TLV_Init(const TTagRestriction TR[]);

/**
@brief		TLV解码

@param		char	*TLVStr		TLV串
@param		int		TLVStrLen	TLV串长
@return		TLVERR_xxx
*/
extern int TLV_Decode(const char *TLVStr, int TLVStrLen);

/**
@brief		取得值(Value)

@param		TTag	Tag			标签(Tag)
@param		char	*Value		值(Value)(输出)
@param		int		*Len		值长度(输出)
@param		int		Offset		匹配第Offset个相同标签
@return		TLVERR_xxx
 */
extern int TLV_GetValue(TTag Tag, char *Value, int *Len, int Offset);

/**
@brief		取得模板的值(Value)

@param		TTag	Tag			标签(模板Tag)
@param		int		*Offset		该模板的值在原TLV串的偏移
@param		int		*Len		值长度(输出)
@return		TLVERR_xxx
 */
extern int TLV_GetTemplate(TTag Tag, int *offset, int *len);



/**
@brief		获得长度(Length)

@param		char	*TLVStr		TLV串
@param		int		TLVStrLen	TLV串长
@param		int		*Len		长度串(输出)
@param		int		*LenLen		长度串长度(输出)
@return		TLVERR_xxx
 */
extern int TLV_GetLength(const unsigned char *TLVStr, int TLVStrLen, int *Len, int *LenLen);



/**
@brief		获得标签(Tag)

@param		(in)	char	*TLVStr		TLV串
@param		(in)	int		TLVStrLen	TLV串长
@param		(out)	TTag	pTag		Tag(输出)
@param		(out)	int		*TagLen		Tag串长
@return		TLVERR_xxx
 */
extern int TLV_GetTag(const char *TLVStr, int TLVStrLen, TTag pTag, int *TagLen);

/**
@brief		取得标签列表

@param		TTagList	TagList		标签列表(输出)
@param		int			*TagNum		标签数
@return		无
 */
extern void TLV_GetTagList(TTagList TagList[], int *TagNum);


/*
@brief		判断字节某位是否为1

@param		char	Byte	传入字节
@param		char	Bit		位(1-8)
@return		TRUE/FALSE
 */
extern int IsBitOn(char Byte, char Bit);

/**
@brief		TLV解码(不支持模板嵌套)

@param		char	*TLVStr		TLV串
@param		int		TLVStrLen	TLV串长
@return		TLVERR_xxx
 */
extern int TLV_Decode_Script(char *TLVStr, int TLVStrLen);
extern int TLV_GetChildren(TTag Tag, TTagList TagList[], int iNesting);
extern int TLV_GetParent(TTag Tag, TTag ParentTag);
typedef struct
{
    TTag Tag;  /**标签*/
    char cTagLen;/*标签长度*/
    char szLen[3]; /**数据长度*/
    char szData[256+1]; /*数据*/
} STTLV; 


void InitTLVPack(void);

int AddTlvToList(const STTLV *pstTlv);

int SetTlv(const char *epczTag, int enTagLen, int enFieldLen, const char *psData, STTLV *pstTlv);

int PackTLV(char *psPackBuffer, int *pnPackLen);






#endif
