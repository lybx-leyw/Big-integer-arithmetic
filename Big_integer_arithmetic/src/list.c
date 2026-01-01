#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "main.h"
//1.链表辅助，添加数字
void addValueToEnd(Num* pnum, int value)
{	
	if ( value<0 ) {
		printf("[in addValueToEnd()]:\n"
	"Error:you cannot add a negative number to Num-end\n");
		return;
	}	
	//是否需要下一块数组
		//第一块或前一块满了时要再加一块
	if (  !pnum->endValue ||
			pnum->endValue->rightused >= BLOCK-1 ) {
			//1.添加新的块并赋值
		NumValue* pnumValue = 
			(NumValue*)malloc(1*sizeof(NumValue));
		pnumValue->value = (int*)malloc(sizeof(int)*BLOCK);
		pnumValue->value[0] = value;
		pnumValue->rightused= 0;
		pnumValue->leftused = 0;
		pnumValue->nextValue= NULL;
		pnumValue->lastValue= pnum->endValue;
			//2.调整链表连接
		if ( pnum->endValue )
			pnum->endValue->nextValue= pnumValue;
		else pnum->headValue= pnumValue;
		pnum->endValue		= pnumValue;
	} else {
	//不需要下一块数组
		pnum->endValue->value[ ++pnum->endValue->rightused ] 
			= value;
	} 
	//大数位数+1
	pnum->numLenth++;
}

void addValueToUnionEnd(UnionNum* pnum,int value)
{
	if ( value<0 ) {
		printf("[in addValueToUnionEnd()]:\n"
	"Error:you cannot add a negative number to Num-end\n");
	}
	//是否需要下一块数组
		//第一块或前一块满了时要再加一块
	if (  !pnum->endValue ||
			pnum->endValue->rightused == BLOCK-1 ) {
			//1.添加新的块并赋值
		UnionNumValue* pnumValue = 
			(UnionNumValue*)malloc(1*sizeof(UnionNumValue));
		pnumValue->value = (int*)malloc(sizeof(int)*BLOCK);
		if ( !pnumValue->value ) {
			return;
		}
		pnumValue->value[0]       = value;
		pnumValue->rightused	  = 0;
		pnumValue->leftused 	  = 0;
		pnumValue->nextValue	  = NULL;
		pnumValue->lastValue	  = pnum->endValue;
		pnumValue->digitsOfFirstBlock = UNION_SIZE;
			//2.调整链表连接
		if ( pnum->endValue )
			pnum->endValue->nextValue= pnumValue;
		else pnum->headValue= pnumValue;
		pnum->endValue		= pnumValue;
	} else {
	//不需要下一块数组
		pnum->endValue->value[++pnum->endValue->rightused] 
			= value;
	} 
	//大数块数+1
	pnum->numBlock++;
}
void addValueToUnionBegin(UnionNum* pnum,int value,
			int digits)
{
	if ( value<0 ) {
		printf("[in addValueToUnionBegin()]:\n"
	"Error:you cannot add a negative number to Num-begin\n");
	}
	//是否需要上一块数组
		//第一块或后一块满了时要再加一块
	if (  !pnum->headValue ||
			pnum->headValue->leftused <= 0 ) {
			//1.添加新的块并赋值
		UnionNumValue* pnumValue = 
			(UnionNumValue*)malloc(1*sizeof(UnionNumValue));
		pnumValue->value = (int*)malloc(sizeof(int)*BLOCK);
		if ( !pnumValue->value ) {
			return;
		}
		pnumValue->value[BLOCK-1] = value;
		pnumValue->rightused	  = BLOCK-1;
		pnumValue->leftused 	  = BLOCK-1;
		pnumValue->lastValue	  = NULL;
		pnumValue->nextValue= pnum->headValue;
		pnumValue->digitsOfFirstBlock = digits;
			//2.调整链表连接
		if ( pnum->headValue )
			pnum->headValue->lastValue= pnumValue;
		else pnum->endValue = pnumValue;
		pnum->headValue		= pnumValue;
	} else {
	//不需要下一块数组
		pnum->headValue->value[ --pnum->headValue->leftused ] 
			= value;
		pnum->headValue->digitsOfFirstBlock = digits;
	} 
	//大数块数+1
	pnum->numBlock++;
}

//2.链表辅助，清除链表
void freeNum(Num* pnum) 
{
	//检查
	if (!pnum || !pnum->headValue || !pnum->endValue) {
		printf("[in freeNum()]:\n"
	"Warning:you are freeing NULL point\n");
		return;
	}
    // 释放所有块
    while ( pnum->headValue ) {
        NumValue* p = pnum->headValue;
        int* q = p->value;
        pnum->headValue = pnum->headValue->nextValue;
        free( p );
        free( q );
    }
    // 清空Num结构
    pnum->endValue = NULL;
    pnum->numLenth = 0;
    pnum->sign	   = PLUS_SIGN;
}
void freeUnionNum(UnionNum* pnum) 
{
	//检查
	if ( !pnum ) {
		printf("[in freeUnionNum()]:\n"
	"Warning:you are freeing NULL point\n");
		return;
	}
    // 释放所有块
    while ( pnum->headValue ) {
        UnionNumValue* p = pnum->headValue;
        int* q = p->value;
        pnum->headValue = pnum->headValue->nextValue;
        free( p );
        free( q );
    }
    // 清空Num结构
    pnum->endValue = NULL;
    pnum->numBlock = 0;
    pnum->sign	   = PLUS_SIGN;
}

//3.链表辅助，清空前导0
void clear0(Num* pnum) 
{
	//检查
	if (!pnum || !pnum->headValue || !pnum->endValue) {
		printf("[in clear0()]:\n"
	"Warning:you are operating with a NULL point\n");
		return;
	}
	//创建索引
	NumValue* currentValue = pnum->headValue;
	int clrPoint = pnum->headValue->leftused;
	//逐块清空所有前导0
	while ( currentValue && 
		currentValue->value[clrPoint] == 0 )
	{	
		//若需要换块了
		if (clrPoint == currentValue->rightused){
			//若没有nextValue就不删了
			if ( !currentValue->nextValue ) {
				pnum->sign = PLUS_SIGN;
				return;
			}		
			//若有，调整链表连接
			pnum->headValue = currentValue->nextValue;
			currentValue->nextValue->lastValue = NULL;
			//释放原来链表
			NumValue* p = currentValue;
			int* q = currentValue->value;
			free( p );
			free( q );
			//创建新的索引
			currentValue = pnum->headValue;
			clrPoint = 0;
		} else {
		//若不用换块，更改leftused即可
			currentValue->leftused++;
			//更新索引
			clrPoint++;
		}
		pnum->numLenth -= 1;
	}
}
void clearUnion0(UnionNum* pnum) 
{
	//检查
	if (!pnum || !pnum->headValue || !pnum->endValue){
		printf("[in clearUnion0()]:\n"
	"Warning:you are operating with a NULL point\n");
		return;
	}
	//创建索引
	UnionNumValue* currentValue = pnum->headValue;
	int clrPoint = pnum->headValue->leftused;
	//逐块清空所有前导0
	while ( currentValue && 
		currentValue->value[clrPoint] == 0 )
	{	
		//若需要换块了
		if ( clrPoint == currentValue->rightused ) {
			//若没有nextValue就不删了
			if ( !currentValue->nextValue ) {
				pnum->sign = PLUS_SIGN;
				return;
			}		
			//若有，调整链表连接
			pnum->headValue = currentValue->nextValue;
			currentValue->nextValue->lastValue = NULL;
			//释放原来链表
			UnionNumValue* p = currentValue;
			int* q = currentValue->value;
			free( p );
			free( q );
			//创建新的索引
			currentValue = pnum->headValue;
			clrPoint = 0;
		} else {
		//若不用换块，更改leftused即可
			currentValue->leftused++;
			//更新索引
			clrPoint++;
		}
		pnum->numBlock -= 1;
	}
}

//4.链表辅助，打印链表
void printUnionNum(const UnionNum* pnum)
{
	//检查
	if ( !pnum || !pnum->headValue ) {
		printf("NULL");
		return;
	}
	//打印正负号
	switch( pnum->sign ) {
		case PLUS_SIGN :printf(" ");     break;
		case MINUS_SIGN:printf("-");     break;
		case WRONG_SIGN:printf("wrongNum?!??");	 
										 break;
	}
	//打印数值
		//创建索引
	UnionNumValue* currentValue = pnum->headValue;
	int prtPoint = pnum->headValue->leftused;
		//打印
	while ( currentValue ) {
			//报错
		if(currentValue->value[prtPoint]>9999) {
			printf("[in printUnionNum()]:\n"
		"Error:you should carry the UnionNum first\n");
		}
			//是不是第一块？
				//是，打印digitsOfFirstBlock位即可
		if (!currentValue->lastValue &&
				prtPoint == currentValue->leftused){
			printf("%0*d",currentValue->digitsOfFirstBlock,
				currentValue->value[prtPoint]);	
				//否则，打印UNION_SIZE位
		} else {
			printf(",%0*d",UNION_SIZE,
				currentValue->value[prtPoint]);
		} 
		prtPoint++;
		if ( prtPoint== currentValue->rightused+1 ) {
			prtPoint  = 0;
			currentValue = currentValue->nextValue;
		}
	}
	//打印位数
	printf(" (共%ld位)\n",pnum->numBlock*4-4+
		pnum->headValue->digitsOfFirstBlock);
}
void fprintUnionNum(const UnionNum* pnum, FILE* tp)
{
	//检查
	if ( !pnum || !pnum->headValue ) {
		fprintf(tp,"NULL");
		return;	
	}
	//打印正负号
	switch( pnum->sign ) {
		case PLUS_SIGN :fprintf(tp," ");     break;
		case MINUS_SIGN:fprintf(tp,"-");     break;
		case WRONG_SIGN:fprintf(tp,"wrongNum?!??");  
											 break;
	}
	//打印数值
		//创建索引
	UnionNumValue* currentValue = pnum->headValue;
	int prtPoint = pnum->headValue->leftused;
		//打印
	while ( currentValue ) {
			//是不是第一块？
				//是，打印digitsOfFirstBlock位即可
		if (!currentValue->lastValue &&
				prtPoint == currentValue->leftused){
			fprintf(tp,"%0*d",
				currentValue->digitsOfFirstBlock,
				currentValue->value[prtPoint]);	
				//否则，打印UNION_SIZE位
		} else {
			fprintf(tp,",%0*d",UNION_SIZE,
				currentValue->value[prtPoint]);
		} 
		prtPoint++;
		if ( prtPoint== currentValue->rightused+1 ) {
			prtPoint  = 0;
			currentValue = currentValue->nextValue;
		}
	}
	//打印位数
	fprintf(tp," (共%ld位)\n",pnum->numBlock*4-4+
		pnum->headValue->digitsOfFirstBlock);
}

//5.链表辅助，非法运算
UnionNum createWrongUnionNum(void)
{
	//创建错误Num:wrongNum?!??0000（共0位）
	UnionNum retNum = {0};
	retNum.sign 	= WRONG_SIGN;
	addValueToUnionEnd (&retNum, 0);
	retNum.numBlock = 0;
	return retNum;
}

//6.链表辅助，创建数字联合
UnionNum createvalueNum(int value)
{
	UnionNum retNum = {0};
	retNum.sign		= PLUS_SIGN;
	addValueToUnionEnd(&retNum,value);
	return retNum;
}

//7.链表辅助，联合链表
UnionNum createUnionNum(Num* pnum)
{	
	//检查
	if (!pnum ||!pnum->headValue||!pnum->endValue){
		printf("[in createUnionNum()]:\n"
	"Error:you are to create a NULL Union\n");
		return createWrongUnionNum();
	}
	//（0）创建需要返回的联合大数
	UnionNum retUnionNum = {0};
	retUnionNum.sign = pnum->sign;
	//（1）创建索引
	NumValue* currentValue = pnum->endValue;
	int ctuPoint = currentValue->rightused;
	//（2）读取UNION_SIZE(4)个数
	int realdigits = 0;
	while ( currentValue ) {
		int num = 0;
		for ( int i=0; i<UNION_SIZE; i++ ) {
			if ( !currentValue ) break;
		//先逆序放num里头，并读出位数
			num *= 10;
			num += currentValue->value[ctuPoint];
			realdigits++;
		//移位
			ctuPoint--;
			if ( ctuPoint == currentValue->leftused-1 ) {
				ctuPoint  = BLOCK-1;
				currentValue = currentValue->lastValue;
			}	
		}
		/*把num倒回来，读了几位就倒几位*/
		int rightvalue = 0;
		for ( int i=0; i<realdigits; i++ ) {
			rightvalue *= 10;
			if ( num ) {
				rightvalue += num%10;
				num /= 10;
			}
		}
		//把rightnum给到UnionNum
		if ( currentValue ) {
			realdigits = 0;
			addValueToUnionBegin(&retUnionNum,rightvalue,4);
		} else {
			addValueToUnionBegin(&retUnionNum,rightvalue,
				realdigits);
		} 
	}
	return retUnionNum;
}