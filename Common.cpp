#include <stdio.h>

/*
	���ܣ�
		�ж��ļ��Ƿ����
	������
		pFileName	[in]	�ļ�����
	����ֵ��
		true	�ļ�����
		false	�ļ�������
	˵����
		��
*/
bool IsFileExist(const char *const pFileName)
{
	FILE *fp;
	bool nExist;

	fp=fopen(pFileName,"rb");
	if(fp==NULL)
		nExist=false;
	else
	{
		nExist=true;
		fclose(fp);
	}

	return nExist;
}