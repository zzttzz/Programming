#ifndef _MINEMAP_H
#include<windef.h>
#include<atltypes.h>
enum STA
{
	back, lclicked, flaged, question,boom
};
struct block//������Ϣ
{
	int Num;//�ٸ�����
	BOOL isMine;//�ף�
	//BOOL discover;//�㿪��
	STA state;
	
};
class CMinemap
{
public:
	CMinemap();
	~CMinemap();
	int mx;//������
	int my;//������
	int nMine;//����
	block **Map;//������Ϣ����
	void LClick(int x, int y,CRect*);//�������
	void RClick(int x, int y);//�Ҽ�
	void OnLBD(int x, int y, CRect *);//�������
	void Create();//��ʼ��
	void Set(int x, int y, int nmine);
	void Set();
	BOOL iswin;
	BOOL isfail;
private:
	

public:
	int rMine;//ʣ������
	int nflag;//����
	int ctime;//ʱ��
};

#endif // !_MINEMAP_H
