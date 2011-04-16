#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include<stdio.h>
#include <string.h>
#include "common.h"

#ifdef WINDOWS
#   include <Windows.h>
#else
#   include <dirent.h>
#endif

#define TRUE 1
#define FALSE 0
#define MAX_RESULT 256

int copyFile(const char* srcFile, const char* destFile)
{
    FILE *srcFp;
    FILE *destFp;
    int ch=0;
    if((srcFp=fopen(srcFile, "rb"))==NULL)
    {
        printf("Can't open file %s", srcFile);
        return FALSE;
    }
    if((destFp=fopen(destFile, "wb+"))==NULL)
    {
        printf("Can't open file %s", destFile);
        return FALSE;
    }
    rewind(srcFp);
    ch = fgetc(srcFp);
    while(ch != EOF)
    {
        fputc(ch,destFp);
        ch = fgetc(srcFp);
    }
    fclose(srcFp);
    fclose(destFp);
    return TRUE;
}

#ifdef WINDOWS
char** enumFiles(const char *directory, int *count)
{
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;
    char result[MAX_RESULT][MAX_PATH];
    char **returnresult;
    char pattern[MAX_PATH];
    int i = 0, j;

    // 开始查找
    strcpy(pattern, directory);
    strcat(pattern, "\\*.*");
    hFind = FindFirstFile(pattern, &FindFileData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        *count = 0;
        return NULL;
    }
    else
    {
        do
        {
            strcpy(result[i++], FindFileData.cFileName);
        }
        while (FindNextFile(hFind, &FindFileData) != 0);
    }
    // 查找结束
    FindClose(hFind);

    // 复制到结果中
    returnresult = (char **)calloc(i, sizeof(char *));
    for (j = 0; j < i; j++)
    {
        returnresult[j] = (char *)calloc(MAX_PATH, sizeof(char));
        strcpy(returnresult[j], result[j]);
    }
    *count = i;
    return returnresult;
}
#else
char** enumFiles(const char *directory, int *count)
{
	//TODO 返回值
	struct dirent *ptr;
	DIR *dir;
	dir=opendir(directory);
	while((ptr=readdir(dir))!=NULL)
	{
		//跳过'.'和'..'两个目录
		if(ptr->d_name[0] == '.')
			continue;
		printf("%s\n",ptr->d_name);
	}
	closedir(dir);
	return NULL;
}
#endif

#endif // FILE_H_INCLUDED
