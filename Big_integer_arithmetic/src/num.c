#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "main.h"
//读取大数
Num getNum(void)
{
	//初始化Num
	Num retNum;
	retNum.numLenth = 0;
	retNum.headValue= NULL;
	retNum.endValue = NULL;
	retNum.sign 	= PLUS_SIGN;
	//读入Num
	while( 1 ) {
		int value = getchar();
		if (value=='\n' || value==EOF) break;
			//正负号不计入数组
		if ( value == '+' ) continue;
		if ( value == '-' ) {
			retNum.sign = MINUS_SIGN;  
			continue;
		}
		if (value != '+' && value !='-')
			value -= '0';	/*48->0; 49->1;...57->9
			->将非正负号的数字-48得到对应int类型的数值*/
		if ((value>9 || value <0) && value != '+' 
			&& value !='-') continue;
		addValueToEnd( &retNum, value );
	}
	//清除前导0 
	clear0( &retNum );
	//检查
	if (!retNum.headValue || !retNum.endValue) {
		printf("[in getNum()]:\n"
	"Warning:you cannot input NULL Num\n");
	}
	return retNum;
}
Num fgetNum(FILE* fp)
{
	//初始化Num
	Num retNum;
	retNum.numLenth = 0;
	retNum.headValue= NULL;
	retNum.endValue = NULL;
	retNum.sign 	= PLUS_SIGN;
	//读入Num
	while( 1 ) {
		int value = fgetc(fp);
		if (value=='\n' || value==EOF) break;
			//正负号不计入数组
		if ( value == '+' ) continue;
		if ( value == '-' ) {
			retNum.sign = MINUS_SIGN;  
			continue;
		}
		if (value != '+' && value !='-')
			value -= '0';	/*48->0; 49->1;...57->9
			->将非正负号的数字-48得到对应int类型的数值*/
		if ((value>9 || value <0) && value != '+' 
			&& value !='-') continue;
		addValueToEnd( &retNum, value );
	}
	//清除前导0 
	clear0( &retNum );
	//检查
	if (!retNum.headValue || !retNum.endValue) {
		printf("[in fgetNum()]:\n"
	"Warning:you cannot input NULL Num\n");
	}
	return retNum;
}

/*链表运算功能1.绝对值比大小
大于输出1，否则输出0，相等是2*/
int compareUnionNum(UnionNum* pnum_1, 
		UnionNum* pnum_2)
{
	//检查
	if ( !pnum_1 || !pnum_2 
		||!pnum_1->headValue||!pnum_1->endValue
		||!pnum_2->headValue||!pnum_2->endValue){
		printf("[in compareUnionNum()]:\n"
	"Error:you are to compare a NULL UnionNum\n");
		return -1;
	}
	if ( !pnum_1->headValue->
		value[pnum_1->headValue->leftused] 
	|| !pnum_2->headValue->
		value[pnum_2->headValue->leftused]  ) {
		clearUnion0(pnum_1);
		clearUnion0(pnum_2);
	}
	//直接从位数看出
	if(pnum_1->numBlock > pnum_2->numBlock) 
		return 1;
	if(pnum_1->numBlock < pnum_2->numBlock) 
		return 0;
	//从高位开始比较
		//创建索引
	UnionNumValue* current_1 = pnum_1->headValue;
	int point_1 = current_1->leftused;
	UnionNumValue* current_2 = pnum_2->headValue;
	int point_2 = current_2->leftused;
		//逐位比大小
	while ( current_1 ) {
			//比较
		if ( current_1->value[point_1]
		   > current_2->value[point_2] ) 
		    return 1;
		if ( current_1->value[point_1]
		   < current_2->value[point_2] ) 
		    return 0;
		    //移位
		point_1++;
		if ( point_1 == current_1->rightused+1 ) {
			point_1  = 0;
			current_1 = current_1->nextValue;
		}
		point_2++;
		if ( point_2 == current_2->rightused+1 ) {
			point_2  = 0;
			current_2 = current_2->nextValue;
		}
	}        
	//完全一致返回2
	return 2;
}