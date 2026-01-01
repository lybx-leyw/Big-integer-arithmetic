#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include "main.h"

//add, subtract, multiply and divide
//addition, subtraction, multiplication, division
/**背景相关
	经实验：
	int最大表示数字为2147483647（10位）——32位
	long 最大表示数字为2147483647（10位）——32位
	long long 最大表示数字为9223372036854775807
		（19位）——64位
	unsigned long long 
		最大表示数字为18446744073709551615
		（20位）——64位
/**
大数运算实现：
	1.大数读取并储存
	2.大数加减乘除法运算
/**/

int main(int argc, const char *argv[]) 
{
	//改为UTF-8编码；
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	
	/*读数区*/
	//读入大数
	/**/
	FILE *fp = fopen("test\\Num_1shiwan.txt","r");
	FILE *vp = fopen("test\\Num_1shiwan.txt","r");
	if ( !fp || !vp ) {
		printf("[in main.c]:\n"
	"Error:the NumFile cannot be opened\n");
		return 1;
	}
	Num num_1 = fgetNum(fp);
	Num num_2 = fgetNum(vp);
	fclose(fp);
	fclose(vp);
	/**
	//输入大数并储存
	printf("请输入两个大数：\n");
		//用分层块状结构储存大数
	Num num_1 = getNum();
	Num num_2 = getNum();
	printf("\n");/**/
	//人机交互
	printf("您输入的数字位数为：\n");
	//printNum(&num_1);
	printf("第一个数：共%ld位\n",num_1.numLenth);
	//printNum(&num_2);
	printf("第二个数：共%ld位\n",num_2.numLenth);
	printf("\n");
	
	/*运算区*/
	//0.准备
		//0.1转化为万进制联合运算格式
	UnionNum unionNum_1 = createUnionNum(&num_1);
	UnionNum unionNum_2 = createUnionNum(&num_2);
	freeNum(&num_1);
	freeNum(&num_2);
	
/*0.1.5...........算法功能调适区-head...................*/
	/**											  
	NTTmultiply(&unionNum_1,&unionNum_2); 	
	/**/
	/**
	printf("%d\n",-7%6);
	PointNum pointNum = Unionpow(9999,49,1);	
	long long test_1 = gotopow(&pointNum,6);
	printf("%d\n",test_1);
	/**
	UnionNum test_1_5 = normalUniondivide(&unionNum_1,&unionNum_2);
	printf("测试1.5得到结果为：");	
	printUnionNum(&test_1_5);		
	/**
	UnionNum test_2 = NTTmultiply(&unionNum_1,&unionNum_2);
	printf("测试2得到结果为：");	
	printUnionNum(&test_2);		
	UnionNum test_2p = Unionmultiply(&unionNum_1,&unionNum_2);
	int is_correct = compareUnionNum(&test_2,&test_2p);
	printf("\n================test-result==============\n");
	if( is_correct==2 ) printf("\t\tcorrect!\n");
	else printf("\t\twrong!!!\n");
	printf("=================end-end=================\n");
	/**/
	
/*0.1.5...........算法功能调适区-end....................*/
	
		//0.2打开储存答案的文件
	FILE *tp = fopen("output\\answer.txt","w+");
	if ( tp == NULL ) {
		printf("[in main.c]:\n"
	"Error:the AnswerFile cannot be opened\n");
		return 1;
	}
		//0.3选择运算符号
	char operation[100];
	operation[0] = '/';
	printf("请输入您想要进行的运算：(+-*/)");
	scanf("%100s",&operation);
	while(operation[0]!='+'&& operation[0]!='-'
		&&operation[0]!='*'&&operation[0]!='/') {
		printf("非法运算，请重新输入:");	
		scanf("%100s",&operation);
	}
	printf("您将进行的运算是：%c\n",operation[0]);
	//1.运算
	if (operation[0] == '+') {
		//加
		UnionNum Add=
				Unionadd(&unionNum_1,&unionNum_2);
		fprintf(tp,"加法结果=");
		fprintUnionNum( &Add, tp );
		printf("加法结果：");
		printUnionNum(&Add);
	//	printf("共%ld位\n",Add.numBlock*4-4+
	//		Add.headValue->digitsOfFirstBlock);
		freeUnionNum( &Add );
		printf("加法运算完成\n");
	}
	else if (operation[0] == '-') {
		//减
		UnionNum Subtract=
				Unionsubtract(&unionNum_1, &unionNum_2);
		fprintf(tp,"减法结果=");
		fprintUnionNum( &Subtract, tp );
		printf("减法结果：");
		printUnionNum(&Subtract);
	//	printf("共%ld位\n",Subtract.numBlock*4-4+
	//		Subtract.headValue->digitsOfFirstBlock);
		freeUnionNum( &Subtract );
		printf("减法运算完成\n");
	}
	else if (operation[0] == '*') {
		//乘
		UnionNum Multiply=
				Unionmultiply(&unionNum_1, &unionNum_2);
	/*
		UnionNum Multiply__=
			normalUnionmultiply(&unionNum_1, &unionNum_2);
		printf("2==%d?\n",
			compareUnionNum(&Multiply,&Multiply__));
		printf("%d=%d??\n",
			Multiply.headValue->digitsOfFirstBlock,
		Multiply__.headValue->digitsOfFirstBlock);*/
	/*	fprintf(tp,"乘法结果=");*/
		fprintUnionNum( &Multiply, tp );
		printf("乘法结果：");
		printUnionNum(&Multiply);
	//	printf("共%ld位\n",Multiply.numBlock*4-4+
	//		Multiply.headValue->digitsOfFirstBlock);
		freeUnionNum( &Multiply );
		printf("乘法运算完成\n");
	}
	else {
		//除
		/**/
		UnionNum Divide= 
				Uniondivide(&unionNum_1,&unionNum_2);
		fprintf(tp,"除法结果=");
		fprintUnionNum(&Divide, tp);
		printf("除法结果：");
		printUnionNum(&Divide);
	//	printf("共%ld位\n",Divide.numBlock*4-4+
	//		Divide.headValue->digitsOfFirstBlock);
		freeUnionNum( &Divide );
		printf("除法运算完成\n");/**/
	}
	fclose(tp);
		//内存管理
	freeUnionNum(&unionNum_1);
	freeUnionNum(&unionNum_2);
	return 0;
}

//联合加法运算实现
UnionNum Unionadd(UnionNum* pnum_1,
		UnionNum* pnum_2)
{	
	//0.检查
	if ( !pnum_1 || !pnum_2 
		||!pnum_1->headValue||!pnum_1->endValue
		||!pnum_2->headValue||!pnum_2->endValue){
		printf("[in Unionadd()]:\n"
	"Error:you are to operation with NULL UnionNum\n");
		return createWrongUnionNum();
	}
	//1.异号相加相当于做减法
	if ( pnum_1->sign !=  pnum_2->sign ) {
		//浅拷贝就好
		UnionNum initNum_2 = *pnum_2;
		initNum_2.sign = (pnum_2->sign == PLUS_SIGN)?
				MINUS_SIGN : PLUS_SIGN ;
		return Unionsubtract( pnum_1, &initNum_2 );
	}
	//2.对位相加，加到answer上去，并完成10000进制
		//创建answerNum
	UnionNum answerNum = {0};
	answerNum.sign 		= pnum_1->sign;
		//逐位相加并进位
			//（1）创建索引和进位标志，
				//以长的数为主循环(current_1)
	UnionNumValue* current_1 =
			( pnum_1->numBlock > pnum_2->numBlock )?
			pnum_1->endValue:pnum_2->endValue;
	int point_1 = current_1->rightused;
	UnionNumValue* current_2 = 
			( pnum_1->numBlock > pnum_2->numBlock )?
			pnum_2->endValue:pnum_1->endValue;
	int point_2 = current_2->rightused;
	int carry = 0;
			//（2）逐位求和
	while ( 1 ) {
		int value = 0;
		if ( current_1 && current_2 ) {
			value = current_1->value[point_1]+
				current_2->value[point_2]+carry;
		} else if ( current_1 ) {
			value = current_1->value[point_1]+carry;
		} else break;
			//（3）万进制
		carry  = value/10000;
		value %= 10000; 
		addValueToUnionBegin (&answerNum,value,
				UNION_SIZE);
		 	//移位
		if( current_2 ) {
			point_2--;
			if ( point_2 == current_2->leftused-1 ) {
				point_2  = BLOCK-1;
				current_2 = current_2->lastValue;
			}
			point_1--;
			if ( point_1 == current_1->leftused-1 ) {
				point_1  = BLOCK-1;
				current_1 = current_1->lastValue;
			}	
		} else if( current_1 ) {
			point_1--;
			if ( point_1 == current_1->leftused-1 ) {
				point_1  = BLOCK-1;
				current_1 = current_1->lastValue;
			}	
		}
	} 
	//3.溢出的位数补足
	if ( carry ) addValueToUnionBegin(&answerNum,carry,
			UNION_SIZE); 
	//4.更新位数，清除前导零
	clearUnion0(&answerNum);
	int head = 
			answerNum.headValue->
		value[answerNum.headValue->leftused];
	if ( head==0 ) 
		answerNum.headValue->digitsOfFirstBlock=1;
	else {
		int realdigits = 0;
		for (head; head>0; head/=10) {
			realdigits++;
		}
		answerNum.headValue->digitsOfFirstBlock=realdigits;       
	}                
	return answerNum;
}
	
//联合减法运算实现
UnionNum Unionsubtract(UnionNum* pnum_1,
		UnionNum* pnum_2)
{
	//0.检查
	if ( !pnum_1 || !pnum_2 
		||!pnum_1->headValue||!pnum_1->endValue
		||!pnum_2->headValue||!pnum_2->endValue){
		printf("[in Unionsubtract()]:\n"
	"Error:you are to operation with NULL UnionNum\n");
		return createWrongUnionNum();
	}
	//1.异号相减相当于做加法
	if ( pnum_1->sign !=  pnum_2->sign ) {
		//只浅拷贝
		UnionNum initNum_2 = *pnum_2;
		initNum_2.sign = (pnum_2->sign == PLUS_SIGN)?
				MINUS_SIGN : PLUS_SIGN ;
		return Unionadd( pnum_1, &initNum_2 );
	}
	//2.创建浅拷贝副本，转化为大数减小数
		//创建answerNum
	UnionNum answerNum = {0};
	answerNum.sign 		= pnum_1->sign;
		//标准化
	clearUnion0(pnum_1);
	clearUnion0(pnum_2);
		//浅拷贝，转化为大数减小数
	UnionNum initNum_1;
	UnionNum initNum_2;	
	if ( compareUnionNum(pnum_1, pnum_2) ) {
		initNum_1 = *pnum_1;
		initNum_2 = *pnum_2;
	} else {
		//小数减大数则求其相反数，然后记得结果求相反数
		initNum_1 = *pnum_2;
		initNum_2 = *pnum_1;
		answerNum.sign = (pnum_2->sign == PLUS_SIGN)?
				MINUS_SIGN : PLUS_SIGN ;
	}
	//2.对位相减，减到answer上去，并完成10000进制
		//逐位作差并借位
			//（1）创建索引和借位标志
	UnionNumValue* current_1 = initNum_1.endValue;
	int point_1 = current_1->rightused;
	UnionNumValue* current_2 = initNum_2.endValue;
	int point_2 = current_2->rightused;
	int borrow  = 0;
			//（2）逐位求差
	while ( 1 ) {
		int value = 0;
		if ( current_2 ) {
			value = current_1->value[point_1]-
				current_2->value[point_2]-borrow;
		} else if ( current_1 ) {
			value = current_1->value[point_1]-borrow;
		} else break;
			//（3）借位处理
		borrow = 0;
		while ( value < 0 ) {
				value += 10000;
				borrow++;
		}
		addValueToUnionBegin (&answerNum,value,
				UNION_SIZE);
		    //移位
		if( current_2 ) {
			point_2--;
			if ( point_2 == current_2->leftused-1 ) {
				point_2  = BLOCK-1;
				current_2 = current_2->lastValue;
			}
			point_1--;
			if ( point_1 == current_1->leftused-1 ) {
				point_1  = BLOCK-1;
				current_1 = current_1->lastValue;
			}	
		} else if( current_1 ) {
			point_1--;
			if ( point_1 == current_1->leftused-1 ) {
				point_1  = BLOCK-1;
				current_1 = current_1->lastValue;
			}	
		}             
	}                         
	//3.清除前导0
	clearUnion0 ( &answerNum );
	//4.更新位数
	int head = 
			answerNum.headValue->
		value[answerNum.headValue->leftused];
	if ( head==0 ) 
		answerNum.headValue->digitsOfFirstBlock=1;
	else {
		int realdigits = 0;
		for (head; head>0; head/=10) {
			realdigits++;
	 	}
		answerNum.headValue->digitsOfFirstBlock=realdigits;
	}
	return answerNum;
}

//联合乘法运算实现
	//普通联合乘法运算实现
UnionNum normalUnionmultiply(const UnionNum* pnum_1,
		const UnionNum* pnum_2)
{
	//0.检查
	if ( !pnum_1 || !pnum_2 
		||!pnum_1->headValue||!pnum_1->endValue
		||!pnum_2->headValue||!pnum_2->endValue){
		printf("[in normalUnionmultiply()]:\n"
	"Error:you are to operation with NULL UnionNum\n");
		return createWrongUnionNum();
	}
	//1.创建anwerNum;
	UnionNum answerNum = {0};
	answerNum.sign 	    = PLUS_SIGN;
		//初始化为0
	addValueToUnionBegin(&answerNum, 0, 1);
	/*2.利用分配律，逐位作积
	i用于记录从右往左第几位,如第2位乘积要错i位*/
		//（1）创建索引
	UnionNumValue* current_1 = pnum_1->endValue;
	int point_1 = current_1->rightused;
	UnionNumValue* current_2 = pnum_2->endValue;
	int point_2 = current_2->rightused;
		//（2）逐位求积
	for ( int i=0; i<pnum_2->numBlock; i++ ) {
			//更新被乘数
		current_1 = pnum_1->endValue;
		point_1   = current_1->rightused;
				//创建积的储存地
		UnionNum midanswerNum = {0};
		midanswerNum.sign	  = PLUS_SIGN;
			//逐位相乘
				//快捷地——>遇到0直接跳过
		if ( current_2->value[point_2] == 0 ) {
		} else {
			while( current_1 ) {
				addValueToUnionBegin ( &midanswerNum, 
					current_1->value[point_1]*
					current_2->value[point_2],UNION_SIZE );
				//current_1移位
				point_1--;	//n（O2）
				if ( point_1 == current_1->leftused-1 ) {
					point_1  = BLOCK-1;
					current_1 = current_1->lastValue;
				}
			}
			//错位
			for ( int j=0; j<i; j++ ) {
				addValueToUnionEnd(&midanswerNum, 0);//n(O2/2)
			}
			//加入answer
			UnionNum oldanswer = answerNum;
			answerNum = Unionadd( &midanswerNum, &oldanswer );
				//n(O2)
			freeUnionNum( &oldanswer );
		}
		//current_2移位
		point_2--;
		if ( point_2 == current_2->leftused-1 ) {
			point_2  = BLOCK-1;
			current_2 = current_2->lastValue;
		}
		//释放midanswerNum
		freeUnionNum( & midanswerNum );
	}
	//3.清除前导0？前面有加法处理了，不需要，
	//4.处理正负号
	answerNum.sign 	    = pnum_1->sign*pnum_2->sign;
	//5.更新细小差异的位数? 不更新！加法中处理了
	return answerNum;
}	
	//卡拉楚巴递归乘法实现
UnionNum Karatsubamultiply( UnionNum* pnum_1,
		UnionNum* pnum_2 )
{
	//0.0检查
	if ( !pnum_1 || !pnum_2 
		||!pnum_1->headValue||!pnum_1->endValue
		||!pnum_2->headValue||!pnum_2->endValue){
		printf("[in Karatsubamultiply()]:\n"
	"Error:you are to operation with NULL UnionNum\n");
		return createWrongUnionNum();
	}
	//0.1递归结束判断
	if ( pnum_1->numBlock <= 122 ||
			pnum_2->numBlock <= 122 ) {
		return normalUnionmultiply( pnum_1,pnum_2 );
	} 
	//0.2若尚未结束递归，块数应补为一致	
		//前导0补齐两个大数
	while ( pnum_1->numBlock != pnum_2->numBlock )
	{
		if (pnum_1->numBlock >pnum_2->numBlock) {
			addValueToUnionBegin(pnum_2,0,UNION_SIZE);
		} else {
			addValueToUnionBegin(pnum_1,0,UNION_SIZE);
		}
	}
		//调整块数为偶数
	if ( pnum_1->numBlock%2 ) {
		addValueToUnionBegin(pnum_1,0,UNION_SIZE);
		addValueToUnionBegin(pnum_2,0,UNION_SIZE);
	}
	//0.3创建这两半的结构
	UnionNum headNum_1 = {0};
	headNum_1.sign	   = PLUS_SIGN;
	UnionNum endNum_1  = {0};
	endNum_1.sign	   = PLUS_SIGN;
	UnionNum headNum_2 = {0};
	headNum_2.sign	   = PLUS_SIGN; 
	UnionNum endNum_2  = {0};
	endNum_2.sign	   = PLUS_SIGN;
	//1.对半分大数
		//num_1
			//（1）制作索引指向大数中央
	UnionNumValue* current_1 = pnum_1->headValue;
	int point_1 = current_1->leftused;
			//（2）先加入前一半数	
	for ( int i=1; i<= pnum_1->numBlock/2; i++ ) {
		addValueToUnionEnd(&headNum_1,
			current_1->value[point_1]);
		point_1++;
		if ( point_1 == current_1->rightused+1 ) 
		{
			point_1  = 0;
			current_1 = current_1->nextValue;
		}
	}
			//继续构造另一半
	while ( current_1 ) {
		addValueToUnionEnd(&endNum_1,
			current_1->value[point_1]);
		point_1++;
		if ( point_1 == current_1->rightused+1 )
		{
			point_1  = 0;
			current_1 = current_1->nextValue;
		}	
	}
		//num_2
	UnionNumValue* current_2 = pnum_2->headValue;
	int point_2 = current_2->leftused;
	for ( int i=1; i<= pnum_2->numBlock/2; i++ ) 
	{	
		addValueToUnionEnd(&headNum_2,
			current_2->value[point_2]);
		point_2++;
		if ( point_2 == current_2->rightused+1 ) 
		{
			point_2  = 0;
			current_2 = current_2->nextValue;
		}	
	}
	while ( current_2 ) {
		addValueToUnionEnd(&endNum_2,
			current_2->value[point_2]);
		point_2++;
		if ( point_2 == current_2->rightused+1 ) 
		{
			point_2  = 0;
			current_2 = current_2->nextValue;
		}	
	}
	//2.得到P1;P2;P3
	UnionNum P1=Karatsubamultiply(&headNum_1,&headNum_2);
//		->补上2*（pnum_1->numBlock-pnum_1->numBlock/2）
//		个0
	UnionNum P2=Karatsubamultiply(&endNum_1, &endNum_2);
//		->不补0
	UnionNum Union_1=Unionadd(&headNum_1,&endNum_1);
	UnionNum Union_2=Unionadd(&headNum_2,&endNum_2);
	UnionNum P3_1=Karatsubamultiply(&Union_1, &Union_2);
	UnionNum P3_2=Unionsubtract(&P3_1,&P1);
	UnionNum P3  =Unionsubtract(&P3_2,&P2);
//		->补上（pnum_1->numBlock-pnum_1->numBlock/2）
//		个0
	freeUnionNum(&headNum_1);//没用的直接释放
	freeUnionNum(&headNum_2);
	freeUnionNum(&endNum_1);
	freeUnionNum(&endNum_2);
	freeUnionNum(&Union_1);
	freeUnionNum(&Union_2);
	freeUnionNum(&P3_1);
	freeUnionNum(&P3_2);//没用的直接释放
		//统一补0
	for (int i=0; 
		i<2*(pnum_1->numBlock-pnum_1->numBlock/2); i++)
	{
		addValueToUnionEnd(&P1, 0);
	}
	for (int i=0; 
		i<(pnum_1->numBlock-pnum_1->numBlock/2); i++)
	{
		addValueToUnionEnd(&P3, 0);
	}
	//3.得到乘法结果
		//创建anwerNum,组合P1，P2，P3
	UnionNum midanswerNum=Unionadd(&P1, &P2);
	UnionNum answerNum	 =Unionadd(&midanswerNum,&P3);
	//4.内存处理
	freeUnionNum(&P1);
	freeUnionNum(&P2);
	freeUnionNum(&P3);
	freeUnionNum(&midanswerNum);
	//5.清除前导0?不用，加法处理过了，处理正负号
	answerNum.sign	=	pnum_1->sign*pnum_2->sign;
				//PLUS_SIGN == 1; MINUS_SIGN == -1;
	//6.更新位数?不处理，加法处理过了
	return answerNum;
}
	//ntt算法准备
	//获得旋转因子w
long long getW( int cnt,int type )
{
    long long w;
    if (type == 1) {
        switch(cnt) {
            case 1 : w = 998244352; break;
            case 2 : w = 911660635; break;
            case 3 : w = 372528824; break;
            case 4 : w = 929031873; break;
            case 5 : w = 452798380; break;
            case 6 : w = 922799308; break;
            case 7 : w = 781712469; break;
            case 8 : w = 476477967; break;
            case 9 : w = 166035806; break;
            case 10: w = 258648936; break;
            case 11: w = 584193783; break;
            case 12: w = 63912897 ; break;
            case 13: w = 350007156; break;
            case 14: w = 666702199; break;
            case 15: w = 968855178; break;
            case 16: w = 629671588; break;
            case 17: w = 24514907 ; break;
            case 18: w = 996173970; break;
            case 19: w = 363395222; break;
            case 20: w = 565042129; break;
            case 21: w = 733596141; break;
            case 22: w = 267099868; break;
            case 23: w = 15311432 ; break;
            default:
                printf("[in getW()]:\n"
			"Error:the UnionNum is too big\n");
                return -1;
        }
    }
    else if (type == 2) {
        switch(cnt) {
            case 1 : w = 1004535808; break;
            case 2 : w = 468937024 ; break;
            case 3 : w = 656685699 ; break;
            case 4 : w = 57890220  ; break;
            case 5 : w = 592282277 ; break;
            case 6 : w = 245427426 ; break;
            case 7 : w = 269156881 ; break;
            case 8 : w = 511639174 ; break;
            case 9 : w = 73253838  ; break;
            case 10: w = 74414585  ; break;
            case 11: w = 62083582  ; break;
            case 12: w = 300363292 ; break;
            case 13: w = 512994875 ; break;
            case 14: w = 623254724 ; break;
            case 15: w = 50158183  ; break;
            case 16: w = 392028186 ; break;
            case 17: w = 343333310 ; break;
            case 18: w = 685348078 ; break;
            case 19: w = 47893549  ; break;
            case 20: w = 751788151 ; break;
            case 21: w = 784885054 ; break;
            default:
                printf("[in getW()]:\n"
			"Error:the UnionNum is too big\n");
                return -1;
        }
    }
    else if (type == 3) {
        switch(cnt) {
            case 1 : w = 469762048; break;
            case 2 : w = 459363891; break;
            case 3 : w = 254027301; break;
            case 4 : w = 85648277 ; break;
            case 5 : w = 354927432; break;
            case 6 : w = 135062810; break;
            case 7 : w = 410325208; break;
            case 8 : w = 320243704; break;
            case 9 : w = 108285730; break;
            case 10: w = 297432182; break;
            case 11: w = 102624483; break;
            case 12: w = 357669287; break;
            case 13: w = 296428742; break;
            case 14: w = 100454291; break;
            case 15: w = 25877761 ; break;
            case 16: w = 40000678 ; break;
            case 17: w = 30090675 ; break;
            case 18: w = 45096025 ; break;
            case 19: w = 18764942 ; break;
            case 20: w = 35800624 ; break;
            case 21: w = 17145600 ; break;
            case 22: w = 26535448 ; break;
            case 23: w = 42386121 ; break;
            case 24: w = 15311432 ; break;
            case 25: w = 43125115 ; break;
            case 26: w = 15311432 ; break;
            default:
                printf("[in getW()]:\n"
			"Error:the UnionNum is too big\n");
                return -1;
        }
    }
    else {
        printf("[in getW()]:\nError:unknown type\n");
        return -1;
    }
    
    return w;
}
	//获得模P域下w的n个幂并记录
		/*O(n2)*/
PointNum Unionpow(long long w,long long n,int type)
{
	//type选择与转换
	if( type!=1 && type!=2 && type!=3 ) {
		printf("[in Unionpow()]:\n"
	"Error:you can not put a wrong type\n");
	}
	long long P
		= (type==1)?__P1:(type==2)?__P2:__P3;
	if ( n<=0 ) {
		//0.临时的检查和报错策略
		while(1)
		printf("[in Unionpow()]:\n"
	"Error:the powwer cannot be a minus number\n");
	}
	//1.逐幂次迭代并记录
	PointNum PointNumw = {0};
		//1.1第1项为1
	long long answerint = 1;
		//1.2其他项
	for(long long i=0; i<n; i++) {
		addValueToPointEnd(&PointNumw,answerint);
		answerint = (w*answerint)%P;
	}
	return PointNumw;
}
	//快速检索找到w的对应次幂
long long gotopow(const PointNum* pnum,long long n)
{
	//0.检查
	if (!pnum || !pnum->headValue ||
	    !pnum->endValue) {
		printf("[in gotopow()]:\n"
	"Error:you cannot check with NULL PointNum\n");
		return -1;
	}
	if ( n>pnum->numPoint-1 || n<0 ) {
		printf("[in gotopow()]:\n"
	"Warning:your are to visit a NULL point\n");
		n %= pnum->numPoint;
		if(n<0) n+=pnum->numPoint;
	}
	//1.创建索引并移动
		//创建索引
	PointValue* currentValue = pnum->headValue;
	int gtpPoint = pnum->headValue->leftused;
		//移动
	for ( long long i=0; i<n; i++ ) {
		gtpPoint++;
		if ( gtpPoint== currentValue->rightused+1 ) {
			gtpPoint  = 0;
			currentValue = currentValue->nextValue;
		}
	}
	//2.返回目标值
	return currentValue->value[gtpPoint];
}
	//ntt工具——单点点值转化
long long PointI(const UnionNum* pnum,
		const PointNum* ppointNumw,
	const long long i,int type)/*i是指第i个点，pnum是需要转化的大数，
				ppointNumw是已经准备了的w的幂次*/
{
	//type选择与转换
	if( type!=1 && type!=2 && type!=3 ) {
		printf("[in Unionpow()]:\n"
	"Error:you can not put a wrong type\n");
	}
	long long P
		= (type==1)?__P1:(type==2)?__P2:__P3;
		//0.内部工具调用合法性检测
	if (!pnum || !pnum->headValue ||
	    !pnum->endValue) {
		printf("[in PointI()]:\n"
	"Error:you cannot create point with NULL UnionNum\n");
		return -1;
	}
	if (!ppointNumw || !ppointNumw->headValue ||
	    !ppointNumw->endValue) {
		printf("[in PointI()]:\n"
	"Error:you cannot create point with NULL PowwerNum\n");
		return -1;
	}
	if ( i>pnum->numBlock-1 || i<0 ) {
		printf("[in PointI()]:\n"
	"Warning:your are to visit a NULL point\n");
		return -1;
	}
		/*1.对位乘法并求和:
			每一位等于对应系数*pow(w,k中对应系数)，
					每一位的x=pow(w,项数)
					即a*w^h，h=(n-k)*i mod n*/
			//1.1创建索引
	UnionNumValue* currentValue = pnum->endValue;
	int point = currentValue->rightused;
			//2.2逐位相乘并相加,从最低次项开始
				/*f(x)=a0+a1x+a2x^2+...+anx^(n-1)*/
	long long ret = 0;
	for( long long k=0; k <= pnum->numBlock-1; k++ ) {
		long long a = 
			(long long)currentValue->value[point];
		long long h = 
			(k*i)%pnum->numBlock;/*i即是点的次序，
					也是点值对应的点的横坐标的w的对数*/
		long long w_h = a?gotopow(ppointNumw,h):0;//w^h
//		long long test=a*w_h;
//		printf("测试点2：正转换是否正确？\n");
//		printf("错误监测:"
//			"%d=9999?;w_h=%lld是否在表内?;"
//				"test=%lld>0???\n",a,w_h,test);
//		printf("现在的ret == %lld\n",ret);
	//	printf("w == %lld\n",gotopow(ppointNumw,1));
		ret += ((a*w_h)%P);
		ret %= P;
		printf("请核验：%lld>0?\n",ret);
			//移位
		point--;
		if ( point== currentValue->leftused-1 ) {
			point = BLOCK-1;
			currentValue = currentValue->lastValue;
		}
	}
		/*3.最终结果*/
	return ret;
}
	//获得模逆元
//获得模逆元
long long getInv(long long n, int type)
{
	//type选择与转换
	if( type!=1 && type!=2 && type!=3 ) {
		printf("[in Unionpow()]:\n"
	"Error:you can not put a wrong type\n");
	}
	long long P
		= (type==1)?__P1:(type==2)?__P2:__P3;
    //0.检查
    if ( n<0 ) {
        printf("[in getInv()]:\n"
    "Error:you cannot find an inv with a wrong n\n");
        return -1;
    }
    //1.得到结果
    /*根据费马小定理，n在__P域下的逆元为n^(p-2) mod__P*/
    long long inv_n=n;
    long long power = P-2;
    int flag=0;//除掉的倍数
    while(1) {
    	if(power & 0x01) {
    		inv_n*=n;
    		inv_n%=P;
    	    power--;
		}
		else{
    		flag++;	
    		power>>1;
		}
	}
	//还剩2^flag个n还没乘上;
	for( int i=0; i<flag; i++ ) {
    	n = (n*n)%P;
	}
	//乘上
	inv_n*=n;
    inv_n%=P;
    return inv_n;
}
	//单点点值逆转换
long long BlockI(const PointNum* pnum,
	const PointNum* ppointNumw,const long long i,
	int type)
{
	//type选择与转换
	if( type!=1 && type!=2 && type!=3 ) {
		printf("[in Unionpow()]:\n"
	"Error:you can not put a wrong type\n");
	}
	long long P
		= (type==1)?__P1:(type==2)?__P2:__P3;
	if (!ppointNumw || !ppointNumw->headValue ||
	    !ppointNumw->endValue) {
		printf("[in BlockI()]:\n"
	"Error:you cannot create point with NULL PowwerNum\n");
	}
	if (!pnum || !pnum->headValue ||
	    !pnum->endValue) {
		printf("[in BlockI()]:\n"
	"Error:you cannot create num with NULL PointNum\n");
		return -1;
	}
	if ( i>pnum->numPoint-1 || i<0 ) {
		printf("[in BlockI()]:\n"
	"Error:your are to get a invalid point\n");
		return -1;
	}	
		/*2.对位乘法并求和:
			每一位等于对应系数*pow(w,-k中对应系数)，
					每一位的x=pow(w,项数)
					即A*w^-h,同样,第k位幂次h为(ki) mod n*/
				/*也就是把正变换的w改为其模逆元即可*/
				/*f(x)=A0+A1x+A2x^2+...+Anx^(n-1)*/
				/*注意,与正变换不同的是,
						这里的点值本身就是从第一个点开始排的*/
			//2.1创建索引
	PointValue* currentValue = pnum->headValue;
	int point = currentValue->leftused;
			//2.2逐位相乘并相加
	long long ret = 0;
	for( long long k=0; k<=pnum->numPoint-1 ; k++ ) {
		long long A = currentValue->value[point];
		long long h = ((pnum->numPoint-k)*i)%pnum->numPoint;
			/*传入的i即是大数的位次,也是w模逆元的指标*/
		long long w_h = A?gotopow(ppointNumw,h)
				:0;//w^h
//		long long test=A*w_h;
//		printf("测试点4:A*w_h=%lld>0??\n,numPoint=%ll==32?"
//				,test,pnum->numPoint);
		ret += (A*w_h)%P;	
		ret %= P;
			//移位
		point++;
		if ( point == currentValue->rightused+1 ) {
			point  = 0;
			currentValue = currentValue->nextValue;
		}
	}
		/*3.最终结果的组装构建,
			结果还需要乘以n的模逆元,
		由于n没有像w那么好的性质,我们用函数穷举一下*/
	long long inv_n = getInv(pnum->numPoint,type);
	ret = (ret*inv_n)%P;
	return ret;
}
	//NTT乘法实现
UnionNum NTTmultiply( UnionNum* pnum_1,
		UnionNum* pnum_2 ) 
{
	//0.准备
		//0.0错误传入检查
	if ( !pnum_1 || !pnum_2 
		||!pnum_1->headValue||!pnum_1->endValue
		||!pnum_2->headValue||!pnum_2->endValue){
		printf("[in NTTmultiply()]:\n"
	"Error:you are to operation with NULL UnionNum\n");
		return createWrongUnionNum();
	}
		//0.1数字规模过大检查
	if ( pnum_1->numBlock>pow(2,20) ||
		 pnum_2->numBlock>pow(2,20) ){
		printf("[in NTTmultiply()]:\n"
	"Error:please divide far bigger UnionNum first\n");
		return createWrongUnionNum();
	}
		//0.2大数位数规范化——>调整为大于位数和的2的幂次倍
			//长度一致
	while ( pnum_1->numBlock != pnum_2->numBlock )
	{
		if (pnum_1->numBlock >pnum_2->numBlock) {
			addValueToUnionBegin(pnum_2,0,UNION_SIZE);
		} else {
			addValueToUnionBegin(pnum_1,0,UNION_SIZE);
		}
	}
			//2的幂次
				//声明
	int cnt = 0;
	long long t_numBlock = pnum_1->numBlock;
				//判断目标位数
	while ( t_numBlock>1 ) {
		if ( t_numBlock%2 ) 
			t_numBlock = t_numBlock/2+1;
		else 
			t_numBlock = t_numBlock/2;
		cnt++;
	}
	cnt++;/*实际位数应补到至少两倍,
		而显然9999*9999<10000*10000=100000000,
		因此,达到2n位已经够了*/	
				//补0
	while ( !(pnum_1->numBlock-(pow(2,cnt))>-0.0001&&
			pnum_1->numBlock-(pow(2,cnt))<0.0001) ) 
	{
		addValueToUnionBegin(pnum_1,0,UNION_SIZE);
		addValueToUnionBegin(pnum_2,0,UNION_SIZE);
	}
//	printf("测试点1：准备工作是否正确？\n");
//	printUnionNum(pnum_1);
//	printUnionNum(pnum_2);
//	printf("实际应有%.0f位\n",pow(2,cnt));
		//1.数论变换储存点值(多模组并行)
			//1.1旋转因子构造
	const long long w1 = getW(cnt,1);
	const long long w2 = getW(cnt,2);
	const long long w3 = getW(cnt,3);
			/*1.2采样点创建：外循环：逐点循环；
				  		  内循环：单点知x求模y*/
	PointNum pointNum_1 = Unionpow(w1,pnum_1->numBlock,1);
	PointNum pointNum_2 = Unionpow(w2,pnum_1->numBlock,2);
	PointNum pointNum_3 = Unionpow(w3,pnum_1->numBlock,3);
			//1.3对应位数幂次创建并构建点值表示
				//定义点值
	PointNum pointNum_1_ty1 = {0};
	PointNum pointNum_2_ty1 = {0};
	PointNum pointNum_1_ty2 = {0};
	PointNum pointNum_2_ty2 = {0};
	PointNum pointNum_1_ty3 = {0};
	PointNum pointNum_2_ty3 = {0};
	for ( long long i=0; i< pnum_1->numBlock; i++ ) {
				//创建并加入第i个点(逐点创建并加入)
		long long nextpoint_1_ty1 = PointI(pnum_1,
			&pointNum_1,i,1);
		long long nextpoint_2_ty1 = PointI(pnum_2,
			&pointNum_1,i,1);
		long long nextpoint_1_ty2 = PointI(pnum_1,
			&pointNum_2,i,2);
		long long nextpoint_2_ty2 = PointI(pnum_2,
			&pointNum_2,i,2);
		long long nextpoint_1_ty3 = PointI(pnum_1,
			&pointNum_3,i,3);
		long long nextpoint_2_ty3 = PointI(pnum_2,
			&pointNum_3,i,3);
		addValueToPointEnd(&pointNum_1_ty1,
				nextpoint_1_ty1);
		addValueToPointEnd(&pointNum_2_ty1,
				nextpoint_2_ty1);
		addValueToPointEnd(&pointNum_1_ty2,
				nextpoint_1_ty2);
		addValueToPointEnd(&pointNum_2_ty2,
				nextpoint_2_ty2);
		addValueToPointEnd(&pointNum_1_ty3,
				nextpoint_1_ty3);
		addValueToPointEnd(&pointNum_2_ty3,
				nextpoint_2_ty3);
	}/*注意这里的结果是低次在前的,
			也就是第一个数是第一个点的值,依次类推*/
//	printf("点值转换结果为：\n");
//	printPoint(&pointNum_1);
//	printPoint(&pointNum_2);
	//2.点值运算求出乘法结果
		//对位相乘
			//2.1创建索引
	PointValue* current_1 = pointNum_1_ty1.headValue;
	int point_1 = current_1->leftused;
	PointValue* current_2 = pointNum_2_ty1.headValue;
	int point_2 = current_2->leftused;
	PointValue* current_3 = pointNum_1_ty2.headValue;
	int point_3 = current_1->leftused;
	PointValue* current_4 = pointNum_2_ty2.headValue;
	int point_4 = current_2->leftused;
	PointValue* current_5 = pointNum_1_ty3.headValue;
	int point_5 = current_1->leftused;
	PointValue* current_6 = pointNum_2_ty3.headValue;
	int point_6 = current_2->leftused;
			//2.2逐位相乘
	PointNum answerPoint_1 = {0};
	PointNum answerPoint_2 = {0};
	PointNum answerPoint_3 = {0};
	for( long long i=0; i < pointNum_1.numPoint; i++ ) {
		long long answerpointValue_1 = 
			(current_1->value[point_1]*
			 current_2->value[point_2])%__P1;
		long long answerpointValue_2 = 
			(current_3->value[point_3]*
			 current_4->value[point_4])%__P2;
		long long answerpointValue_3 = 
			(current_5->value[point_5]*
			 current_6->value[point_6])%__P3;
//		printf("测试点3：逐位相乘是否正确？\n");
//		printf("%lld>0??\n",answerpointValue);
				//添加项
		addValueToPointEnd(&answerPoint_1,answerpointValue_1);
		addValueToPointEnd(&answerPoint_2,answerpointValue_2);
		addValueToPointEnd(&answerPoint_3,answerpointValue_3);
				//移位
		point_1++;
		if ( point_1== current_1->rightused+1 ) {
			point_1 = 0;
			current_1 = current_1->nextValue;
		}
		point_2++;
		if ( point_2== current_2->rightused+1 ) {
			point_2 = 0;
			current_2 = current_2->nextValue;
		}
		point_3++;
		if ( point_3== current_3->rightused+1 ) {
			point_3 = 0;
			current_3 = current_3->nextValue;
		}
		point_4++;
		if ( point_4== current_4->rightused+1 ) {
			point_4 = 0;
			current_4 = current_4->nextValue;
		}
		point_5++;
		if ( point_5== current_5->rightused+1 ) {
			point_5 = 0;
			current_5 = current_5->nextValue;
		}
		point_6++;
		if ( point_6== current_6->rightused+1 ) {
			point_6 = 0;
			current_6 = current_6->nextValue;
		}
	}/*这里没有改变点值的顺序,仍然是正序的*/
//	printf("点乘结果为：\n");
//	printPoint(&answerPoint);
//	freePointNum(&pointNum_1);
//	freePointNum(&pointNum_2);
		//CRD答案组合
	long long M1 = __P2*__P3;
	long long M2 = __P1*__P3;
	long long M3 = __P1*__P2;
	long long IM_1 = getInv(M1,1);
	long long IM_2 = getInv(M2,2);
	long long IM_3 = getInv(M3,3);
	//3.数论逆变换
	/*
	UnionNum answerNum = {0};
	answerNum.sign 	   = PLUS_SIGN;
		/*注意，这里是采用正序来构建结果的,
			也就是从大数的最高位开始构建结果,因此i
			需要从最高点开始取*/
/*	for ( long long i=answerPoint.numPoint-1; 
			i>=0; i-- ) {
			//创建并加入第i块的值
		long long numBlock = 
				BlockI(&answerPoint,&pointNum,i,1);
		addValueToUnionEnd(&answerNum,numBlock);
		printf("test_point:hr%lld,%lld\n",i,numBlock);
	}
	freePointNum(&pointNum);
	freePointNum(&answerPoint);
	//4.结果处理与输出
		/*最多进位两次*/
		//这只是临时策略，后续可改为更好的进位处理
		/*
	UnionNum t_answerNum = answerNum;
	UnionNum Num0 = createvalueNum(0);
	answerNum = Unionadd(&answerNum,&Num0);
	freeUnionNum(&t_answerNum);
	t_answerNum = answerNum;
	answerNum = Unionadd(&answerNum,&Num0);
	freeUnionNum(&t_answerNum);
	t_answerNum = answerNum;
	freeUnionNum(&Num0);
	answerNum.sign = pnum_1->sign*pnum_2->sign;
	printf("%llu\n",pnum_1->numBlock);
	printf("%llu\n",pnum_2->numBlock);
	return answerNum;*/
}
	//大数乘法集成式分流算法
UnionNum Unionmultiply( UnionNum* pnum_1,
		UnionNum* pnum_2 ) 
{
	//0.0检查
	if ( !pnum_1 || !pnum_2 
		||!pnum_1->headValue||!pnum_1->endValue
		||!pnum_2->headValue||!pnum_2->endValue){
		printf("[in Unionmultiply()]:\n"
	"Error:you are to operation with NULL UnionNum\n");
		return createWrongUnionNum();
	}
	UnionNum answerNum = Karatsubamultiply(pnum_1,
		pnum_2 );
	clearUnion0(pnum_1);
	clearUnion0(pnum_2);
	return answerNum;
}

//联合除法实现
	/*牛顿迭代法
	先将被除数视作缩小10的pnum_2->numBlock-1倍，
	以十进制为例，如
	1000000000000000000000->1.000000000000000000000，
	则倒数从小数点后一位开始*/
UnionNum Uniondivide(UnionNum* pnum_1, 
		UnionNum* pnum_2)
{
	//0.初始准备
		//0.0检查
	if ( !pnum_1 || !pnum_2 
		||!pnum_1->headValue||!pnum_1->endValue
		||!pnum_2->headValue||!pnum_2->endValue){
		printf("[in Uniondivide()]:\n"
	"Error:you are to operation with NULL UnionNum\n");
		return createWrongUnionNum();
	}
		//0.1规范化
	clearUnion0(pnum_1);
	clearUnion0(pnum_2);
		//0.2除数为0
	if ( pnum_2->numBlock==1 && 
			pnum_2->headValue->
			value[pnum_2->headValue->leftused]==0) 
	{
		printf("error:the number divided"
			   "can not be '0'\n");
		return createWrongUnionNum();	
	}
		//0.3快捷通道
			//(被除数小于除数时)
	if (!compareUnionNum(pnum_1, pnum_2))
	{
		UnionNum Num0 = createvalueNum(0);
		Num0.headValue->digitsOfFirstBlock = 1;
		return Num0;
	}/**/
			//(被除数等于除数时)
	if (compareUnionNum(pnum_1, pnum_2)==2) 
	{
		UnionNum Num1 = createvalueNum(1);
		Num1.headValue->digitsOfFirstBlock = 1;
		return Num1;
	}
		//0.4倒数初始化
	UnionNum downNum = {0};
	downNum.sign	 = PLUS_SIGN;
		//0.5辅助数字2，初始扩大倍数为pnum_2->numBlock
	UnionNum Num2 = {0};
	Num2.sign     = PLUS_SIGN;
	addValueToUnionEnd(&Num2,2);
	const int Blocks = pnum_2->numBlock;
	for(int i=0;i<pnum_2->numBlock;i++) {
		addValueToUnionEnd(&Num2,0);
	}
		//0.6变量声明
	long long digits = 0;//digits表示倒数最大保留位数
		//0.7符号处理逻辑
	const SIGN sign_1 = pnum_1->sign;
	const SIGN sign_2 = pnum_2->sign;
	pnum_1->sign = pnum_2->sign = PLUS_SIGN;
	//1.得到初始值（选取头一/两块）
	int value = 0;
	if( pnum_2->numBlock>=2 ) {
		//1.1若选两块，下一块不用换块
		if( pnum_2->headValue->leftused !=
			pnum_2->headValue->rightused )
			value = 10000*
				10000/(10000*(pnum_2->headValue->
				value[pnum_2->headValue->leftused])+
				pnum_2->headValue->
				value[pnum_2->headValue->leftused+1]
				+1);
		//1.2下一块要换块
		else
			value = 10000*
				10000/(10000*(pnum_2->headValue->
				value[pnum_2->headValue->leftused])+
				pnum_2->headValue->nextValue->
				value[pnum_2->headValue->nextValue
					->leftused]+1);
	} else {
		value = 
			10000/((pnum_2->headValue->
			value[pnum_2->headValue->leftused])+1);
	}		
	addValueToUnionEnd(&downNum,value);/*downNum现在 1位，
			与2差pnum_2块数位——一直要保持如此*/
	//2.迭代逼近：x1 = x0(2-ax0)
	while ( 1 ) {
			//2.1迭代算法x1 = x0(2-ax0)
				//a*x0
		UnionNum olddownNum = downNum;
		UnionNum mid1 = Unionmultiply(&downNum,pnum_2);
				//2-ax0,x0*(2-ax0)
		UnionNum mid2 = Unionsubtract(&Num2,&mid1);
		downNum	 	  = Unionmultiply(&mid2,&downNum);
		freeUnionNum(&mid1);
		freeUnionNum(&mid2);
			//2.2是否达到目标长度判断
				/*2.2.1未达到目标长度时，跳过后续,
					保证downNum与2差pnum_2块数位*/
		long long maxBlocks = pnum_1->numBlock+15;
		if ( downNum.numBlock+pnum_2->numBlock
				<=maxBlocks ) {
			while( Num2.numBlock-downNum.numBlock<Blocks ){
				addValueToUnionEnd(&Num2,0);
			}
			freeUnionNum(&olddownNum);
			continue;
		}	
				//2.2.2已达目标，舍去后面的位数
		if( !digits ) {
			digits = maxBlocks-Blocks;//downNum.numBlock?;
			UnionNum t_Num2 = Num2;
			Num2 = createvalueNum(2);
			freeUnionNum(&t_Num2);
			while( Num2.numBlock-digits<Blocks ){
				addValueToUnionEnd(&Num2,0);
			}
		}
					//新倒数
		UnionNum newdownNum = {0};
		newdownNum.sign     = PLUS_SIGN;
					//创建索引
		UnionNumValue* currentValue=downNum.headValue;
		int point = downNum.headValue->leftused;
					//构造新倒数
		for(int i =0;i<digits;i++){
			addValueToUnionEnd(
				&newdownNum,currentValue->value[point]);
					//移位
			point++;
			if (point==currentValue->rightused+1) 
			{
				point = 0;
				currentValue=currentValue->nextValue;
			}		
		}
					//把新倒数换给旧倒数
		freeUnionNum(&downNum);
		downNum = newdownNum;
	//	printUnionNum(&downNum);
	//	printf("\n");
				//3.精度判断（循环终止判断）
		int is_break = 0;
		switch(compareUnionNum(&olddownNum,&downNum)){
			case 2:
				is_break = 1;
				freeUnionNum(&olddownNum);
				break;
			case -1:
			case 1:
				while (1) {
					printf("[in Uniondivide()]:\n"
	"Error:there is something wrong with your code\n");	
				}
			default: 
				freeUnionNum(&olddownNum);
		}
		if (is_break) break;
	}
	//3.做乘法
	UnionNum answerNum = Unionmultiply(&downNum,pnum_1); 
	answerNum.sign	   = PLUS_SIGN;  
	clearUnion0(&answerNum);
	//4.保留整数
		//新答案
	UnionNum newanswerNum = {0};
	newanswerNum.sign     = PLUS_SIGN; 
			//索引
	UnionNumValue* currentValue=answerNum.headValue;
	int point = answerNum.headValue->leftused;
				//构造新答案
	for(int i = answerNum.numBlock-(digits+Blocks-1);
	/*这里其实就是减去Num2扩大的倍数，
					Num2.numBlock==digits+Blocks*/
			i>0;i--) {
		addValueToUnionEnd(
			&newanswerNum,currentValue->value[point]);
				//移位
		point++;
		if (point == currentValue->rightused+1) 
		{
			point  = 0;
			currentValue=currentValue->nextValue;
		}		
	}
	//5.结果检验
		/*|pnum_2| >  |pnum_1 - answer*pnum_2|,
		  |pnum_1| >= |answer*pnum_2|*/
	UnionNum mid1 = Unionmultiply(&newanswerNum,pnum_2);
			//结果调至偏大
	while (compareUnionNum(pnum_1,&mid1)==1) {
	//	static int j = 1;
	//	printf("调大：hr%d\n",j++);
				//answer++
		UnionNum t_newanswerNum = newanswerNum;
		UnionNum Num1 = createvalueNum(1);
		newanswerNum= 
			Unionadd(&newanswerNum,&Num1);
	//	printUnionNum(&newanswerNum);
		freeUnionNum(&t_newanswerNum);
				//mid1++
		UnionNum t_mid1 = mid1;
		mid1 = Unionadd(&mid1,pnum_2);
		freeUnionNum(&t_mid1);
		freeUnionNum(&Num1);
	}
			//结果调到合适
	while (compareUnionNum(pnum_1,&mid1)==0) {
	//	static int k = 1;
	//	printf("调小：hr%d\n",k++);
				//answer--
		UnionNum t_newanswerNum = newanswerNum;
		UnionNum Num1 = createvalueNum(1);
		newanswerNum= 
			Unionsubtract(&newanswerNum,&Num1);
	//	printUnionNum(&newanswerNum);
		freeUnionNum(&t_newanswerNum);
				//mid1--
		UnionNum t_mid1 = mid1;
		mid1 = Unionsubtract(&mid1,pnum_2);
		freeUnionNum(&t_mid1);
		freeUnionNum(&Num1);		
	}
	//6.把新答案换给旧答案
//	newanswerNum.headValue->digitsOfFirstBlock = 
//		answerNum.headValue->digitsOfFirstBlock;
	newanswerNum.sign = sign_1*sign_2;
	pnum_1->sign = sign_1;
	pnum_2->sign = sign_2;
	freeUnionNum(&answerNum);
	answerNum = newanswerNum;
	freeUnionNum(&Num2);
	//7.位数调整
	int head = 
			answerNum.headValue->
		value[answerNum.headValue->leftused];
	if ( head==0 ) 
		answerNum.headValue->digitsOfFirstBlock=1;
	else {
		int realdigits = 0;
		for (head; head>0; head/=10) {
			realdigits++;
		}
		answerNum.headValue->digitsOfFirstBlock=realdigits;       
	}                
	return answerNum;
}
	/*普通除法运算实现*/
UnionNum normalUniondivide(UnionNum* pnum_1, 
		UnionNum* pnum_2)
{
	//0.初始准备
		//0.0检查
	if ( !pnum_1 || !pnum_2 
		||!pnum_1->headValue||!pnum_1->endValue
		||!pnum_2->headValue||!pnum_2->endValue){
		printf("[in normalUniondivide()]:\n"
	"Error:you are to operation with NULL UnionNum\n");
		return createWrongUnionNum();
	}
		//0.1规范化
	clearUnion0(pnum_1);
	clearUnion0(pnum_2);
		//0.2除数为0
	if ( pnum_2->numBlock==1 && 
			pnum_2->headValue->
			value[pnum_2->headValue->leftused]==0) 
	{
		printf("[in normalUniondivide()]:\n"
	"error:the number divided cannot be '0'\n");
		return createWrongUnionNum();	
	}
		//0.3快捷通道
			//(被除数小于除数时)
	if (!compareUnionNum(pnum_1, pnum_2))
	{
		UnionNum Num0 = createvalueNum(0);
		Num0.headValue->digitsOfFirstBlock = 1;
		return Num0;
	}/**/
			//(被除数等于除数时)
	if (compareUnionNum(pnum_1, pnum_2)==2) 
	{
		UnionNum Num1 = createvalueNum(1);
		Num1.headValue->digitsOfFirstBlock = 1;
		return Num1;
	}
		//0.4.创建anwerNum;
	UnionNum answerNum	= createvalueNum(0);	
	answerNum.sign 	    = pnum_1->sign*pnum_2->sign;
		//0.5创建num_1的副本
	UnionNum initNum_1  = Unionadd(pnum_1,&answerNum);  
	initNum_1.sign		= PLUS_SIGN;
		/*1.从某一块开始逐块除以除数,
				直到被除数的最后一块*/
	for (int i = initNum_1.numBlock - pnum_2->numBlock; 
		i>=0; i--) 
	{
			//快捷通道
		if ( initNum_1.numBlock == 1 && 
				initNum_1.headValue->
				value[initNum_1.headValue->leftused]==0) {
			addValueToUnionEnd(&answerNum, 0);
			continue;			
		}
			//（1）试商
		int value = 
			(initNum_1.numBlock-pnum_2->numBlock==i)?
			initNum_1.headValue->
				value[initNum_1.headValue->leftused]/
			pnum_2->headValue->
				value[pnum_2->headValue->leftused]:
			initNum_1.headValue->
				value[initNum_1.headValue->leftused]*10000
			/pnum_2->headValue->
				value[pnum_2->headValue->leftused];	
			//（2）调整并确定最终商
		UnionNum toSubtract = {0};
		toSubtract.sign     = PLUS_SIGN;
				//相乘
		UnionNum QualityNum = createvalueNum(value);
		toSubtract = 
				normalUnionmultiply(pnum_2,&QualityNum);
		freeUnionNum(&QualityNum);
				//拷贝toSubtract
		UnionNum Num0 = createvalueNum(0);
		UnionNum inittoSubtract
				= Unionadd(&toSubtract,&Num0);
				//偏大调整		 
		while(1) 
		{
			 		//补0——不为0时才补0
			if ( value ) {
				for ( int k=0; k<i; k++ ) {
					addValueToUnionEnd( &toSubtract, 0 );
				}             
			}
					//调整
			if (!compareUnionNum(&toSubtract,&initNum_1)) {	
				UnionNum t_inittoSubtract = inittoSubtract;
				inittoSubtract = 
						Unionadd(&inittoSubtract,pnum_2);
				freeUnionNum(&t_inittoSubtract);
				freeUnionNum(&toSubtract);  
				toSubtract = Unionadd(&inittoSubtract,&Num0);
				value++;
			} else break;                                             	
		} 
				//精确调整
		while(1) 
		{
					//调整
			if (!compareUnionNum(&initNum_1,&toSubtract)) {
				UnionNum t_inittoSubtract = inittoSubtract;
				inittoSubtract = 
						Unionsubtract(&inittoSubtract,pnum_2);
				freeUnionNum(&t_inittoSubtract);
				freeUnionNum(&toSubtract);  
				toSubtract = Unionadd(&inittoSubtract,&Num0);
				value--;
			} else break;   
				 	//补0——不为0时才补0
			if ( value ) {
				for ( int k=0; k<i; k++ ) {
					addValueToUnionEnd( &toSubtract, 0 );
				}             
			}                                          	
		} 
		freeUnionNum(&inittoSubtract);  
		freeUnionNum(&Num0);
			//（3）加入answerNum                       
		addValueToUnionEnd(&answerNum,value);
			//（4）做差并调整新的被除数
		UnionNum oldNum_1 = initNum_1;
		initNum_1 = Unionsubtract(&initNum_1,&toSubtract);
		freeUnionNum(&toSubtract);
		freeUnionNum(&oldNum_1);
	}
	freeUnionNum(&initNum_1);
		//2.清除前导0
	clearUnion0( &answerNum );
		//3.更新位数
	int head = 
			answerNum.headValue->
		value[answerNum.headValue->leftused];
	if ( head==0 ) 
		answerNum.headValue->digitsOfFirstBlock=1;
	else {
		int realdigits = 0;
		for (head; head>0; head/=10) {
			realdigits++;
		}
		answerNum.headValue->digitsOfFirstBlock=realdigits;       
	}                
	return answerNum;
}