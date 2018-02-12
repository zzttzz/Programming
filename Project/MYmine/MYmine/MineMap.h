#ifndef _MINEMAP_H
#include<windef.h>
#include<atltypes.h>
enum STA
{
	back, lclicked, flaged, question,boom
};
struct block//格子信息
{
	int Num;//临格雷数
	BOOL isMine;//雷？
	//BOOL discover;//点开？
	STA state;
	
};
class CMinemap
{
public:
	CMinemap();
	~CMinemap();
	int mx;//雷区长
	int my;//雷区宽
	int nMine;//雷数
	block **Map;//格子信息索引
	void LClick(int x, int y,CRect*);//点击操作
	void RClick(int x, int y);//右键
	void OnLBD(int x, int y, CRect *);//左键按下
	void Create();//初始化
	void Set(int x, int y, int nmine);
	void Set();
	BOOL iswin;
	BOOL isfail;
private:
	

public:
	int rMine;//剩余雷数
	int nflag;//旗数
	int ctime;//时间
};

#endif // !_MINEMAP_H
