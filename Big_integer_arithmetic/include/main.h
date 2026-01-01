#ifndef __MAIN_HEAD__
#define __MAIN_HEAD__

#define BLOCK 2048
#define UNION_SIZE 4
#define __P1 998244353LL //119*2^23+1 //Type1
#define __P2 1004535809LL//479*2^21+1 //Type2
#define __P3 469762049LL //7*2^26+1   //Type3
//正负号
typedef enum {
	PLUS_SIGN  =  1,
	MINUS_SIGN = -1,
	WRONG_SIGN =  0
} SIGN;
//数值
typedef struct _num_value {
	int* value;//0~9的数字
	int rightused;
	int leftused;
	struct _num_value* nextValue;
	struct _num_value* lastValue;
} NumValue; 
typedef struct _union_num_value {
	int* value;//0~9999的数字
	int rightused;
	int leftused;
	int digitsOfFirstBlock;
	struct _union_num_value* nextValue;
	struct _union_num_value* lastValue;
} UnionNumValue; 
//数值和大小
typedef struct _number {
	SIGN sign;
	NumValue* headValue;
	NumValue* endValue;
	long long numLenth; 
} Num;
typedef struct _union_number {
	SIGN sign;
	UnionNumValue* headValue;
	UnionNumValue* endValue;
	long long numBlock; 
} UnionNum;
//大数点值表示
typedef struct _point_num_value {
	long long* value;
	int rightused;
	int leftused;
	struct _point_num_value* nextValue;
	struct _point_num_value* lastValue;
} PointValue; 
typedef struct _point_num {
	PointValue* headValue;
	PointValue* endValue;
	long long numPoint; 
} PointNum;

//链表辅助函数list.c
void addValueToEnd  ( Num* pnum, int value );
void addValueToUnionEnd(UnionNum* pnum,int value);
void addValueToUnionBegin(UnionNum* pnum,int value,
			int digits);
void freeNum ( Num* pnum );
void freeUnionNum(UnionNum* pnum);
void clear0  ( Num* pnum );
void clearUnion0(UnionNum* pnum);
void printUnionNum(const UnionNum* pnum);
void fprintUnionNum(const UnionNum* pnum, FILE* tp);
void printUnionNum(const UnionNum* pnum);
UnionNum createWrongUnionNum(void);
UnionNum createvalueNum(int value);
UnionNum createUnionNum(Num* pnum);
//Num交互函数num.c
Num getNum ( void );
Num fgetNum(FILE* fp);
int compareUnionNum(UnionNum* pnum_1, 
		UnionNum* pnum_2);
//核心运算main.c
UnionNum Unionadd(UnionNum* pnum_1,
		UnionNum* pnum_2);
UnionNum Unionsubtract(UnionNum* pnum_1,
		UnionNum* pnum_2);
UnionNum normalUnionmultiply(const UnionNum* pnum_1,
		const UnionNum* pnum_2);
UnionNum Karatsubamultiply(UnionNum* pnum_1,
		UnionNum* pnum_2);
long long getW(int cnt,int type);
PointNum Unionpow(long long w,
		long long n,int type);
long long gotopow
		(const PointNum* pnum,long long n);
		
UnionNum NTTmultiply( UnionNum* pnum_1,
		UnionNum* pnum_2 );
UnionNum Unionmultiply(UnionNum* pnum_1,
		UnionNum* pnum_2);
UnionNum Uniondivide(UnionNum* pnum_1, 
		UnionNum* pnum_2);
UnionNum normalUniondivide(UnionNum* pnum_1, 
		UnionNum* pnum_2);
UnionNum normalUniondivide(UnionNum* pnum_1, 
		UnionNum* pnum_2);
//为NTT专门增加的函数ntt.c
void addValueToPointEnd(PointNum* pnum,
		long long value);
void freePointNum(PointNum* pnum);
void printPoint( const PointNum* pnum );
#endif