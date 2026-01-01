#include <stdio.h>
#include <stdlib.h>
#include "main.h"
//1.点值辅助，添加点
void addValueToPointEnd(PointNum* pnum,
		long long value)
{
	if ( value<0 ) {
		printf("[in addValueToPointEnd()]:\n"
	"Error:you cannot add a negative number to Point-end\n");
		return;
	}	
	//模P域下的输入检验
	if ( value>=__P1 ) {
		printf("[in addValueToPointEnd()]:\n"
		"Error:the value need to mod p first\n");
		value %= __P1;
	}
	//是否需要下一块点
		//第一块或前一块满了时要再加一块
	if ( !pnum->endValue ||
		  pnum->endValue->rightused == BLOCK-1 ) {
			//1.添加新的块并赋值
		PointValue* ppointValue = 
			(PointValue*)malloc(1*sizeof(PointValue));
		ppointValue->value=(long long*)
				malloc(sizeof(long long)*BLOCK);
		ppointValue->value[0] 	  = value;
		ppointValue->rightused	  = 0;
		ppointValue->leftused 	  = 0;
		ppointValue->nextValue	  = NULL;
		ppointValue->lastValue	  = pnum->endValue;
			//2.调整链表连接
		if ( pnum->endValue )
			pnum->endValue->nextValue= ppointValue;
		else pnum->headValue= ppointValue;
		pnum->endValue		= ppointValue;
	} else {
	//不需要下一块数组
		pnum->endValue->
			value[++pnum->endValue->rightused] 
			= value;
	} 
	//大数点数+1
	pnum->numPoint++;
}
//2.点值辅助，清除点值
void freePointNum(PointNum* pnum) 
{
	//检查
	if ( !pnum ) {
		printf("[in freePointNum()]:\n"
	"Warning:you are freeing NULL point\n");
		return;
	}
    // 释放所有块
    while ( pnum->headValue ) {
        PointValue* p = pnum->headValue;
        long long* q = p->value;
        pnum->headValue = pnum->headValue->nextValue;
        free( p );
        free( q );
    }
    // 清空Num结构
    pnum->endValue = NULL;
    pnum->numPoint = 0;
}
//3.点值调适函数，打印点值
void printPoint(const PointNum* pnum)
{
	//检查
	if ( !pnum || !pnum->headValue ) {
		printf("NULL");
		return;
	}
	//创建索引
	PointValue* currentValue = pnum->headValue;
	int prtPoint = pnum->headValue->leftused;
	//打印
	int i = 1;
	while ( currentValue ) {
		printf("第%d个点:%ld\n",i++,
			currentValue->value[prtPoint]);
		prtPoint++;
		if ( prtPoint== currentValue->rightused+1 ) {
			prtPoint  = 0;
			currentValue = currentValue->nextValue;
		}
	}
}