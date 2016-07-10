#include <stdio.h>

/*
	功能：
		判断文件是否存在
	参数：
		pFileName	[in]	文件名称
	返回值：
		true	文件存在
		false	文件不存在
	说明：
		无
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