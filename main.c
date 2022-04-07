#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*�������ƣ�ʳ�ö��͹���ϵͳ(ѧ����)��
 *�����ܣ�ʵ��ѧ���˵Ķ��Ͳ�ѯ��ɾ�����ܡ�
 *�������ߣ�2002124W18�ź�Ȼ��2002124W19֣���塢2002124w20�ϳ�����2002124W16�����С� 
 *����ֹ������ࡢ���ߡ���һ����     ע��             ���书��           ����      �����Ϸ���Ӧ��
 * ע���������ı���ԭ����ֱ������qiafan.exe�ļ�,��Ҫֱ�ӱ������,������ȷ�����˱������ı��뷽ʽΪUTF-8
 */

typedef struct {
    char **str;
    size_t num;
}IString;

//���ڴ���ѧ������ѧ�Ŷ������ڡ����͵ص㡢����͹ݡ���Ʒ��
struct data
        {
    char name[10];
    char ID[20];
    char date[15];
    char pos[20];
    char rest[20];
    char dish[20];
        };

void showHeart();
int Split(char *src, char *delim, IString* istr);
void printScreen(char *showString);
void initScreen();
void saveStructure(struct data da);
struct data readStructure(char *date,char ID[10]);
void delStructure(char *date,char ID[20]);
void searchScreen();
void orderScreen();
void delScreen();

int main() {
    initScreen();
    return 0;
}

void showHeart()
{
	//���ϳ�������������ڽ���������������������������չʾ�� 
    float a,x,y;
    int n=0,m=0;
    char ch[4],str[4];
    for(y=1.2f; y>-1.0f; y-=0.1f)
    {
        for(x=-1.2f; x<1.5f; x+=0.05f)
        {
            a = x*x+y*y-1;
            switch(n%4)
            {
                case 0:strcpy(str,"��");break;
                case 1:strcpy(str,"��");break;
                case 2:strcpy(str,"��");break;
                case 3:strcpy(str,"��");break;
            }
            strcpy(ch,a*a*a-x*x*y*y*y<=0.0f?(m++,m%2==0?(n++,str):""):" ");
            printf("%s",ch);

        }
        printf("\n");
    }
}

int Split(char *src, char *delim, IString* istr)//���õĴ��룬����ʵ�ְ���ĳһ�ַ��ָ��ַ�������
{
    int i;
    char *str = NULL, *p = NULL;

    (*istr).num = 1;
    str = (char*)calloc(strlen(src)+1,sizeof(char));
    if (str == NULL) return 0;
    (*istr).str = (char**)calloc(1,sizeof(char *));
    if ((*istr).str == NULL) return 0;
    strcpy(str,src);

    p = strtok(str, delim);
    (*istr).str[0] = (char*)calloc(strlen(p)+1,sizeof(char));
    if ((*istr).str[0] == NULL) return 0;
    strcpy((*istr).str[0],p);
    for(i=1; (p = strtok(NULL, delim)); i++)
    {
        (*istr).num++;
        (*istr).str = (char**)realloc((*istr).str,(i+1)*sizeof(char *));
        if ((*istr).str == NULL) return 0;
        (*istr).str[i] = (char*)calloc(strlen(p)+1,sizeof(char));
        if ((*istr).str[0] == NULL) return 0;
        strcpy((*istr).str[i],p);
    }
    free(str);
    str = p = NULL;

    return 1;
}

void printScreen(char *showString)//����ΪҪ��ʾ������
{
	//������ʾ���棨������������·ֱ����һ��"*"�� �� 
    char str[511];

    printf("**************************************************\n");
    printf("%s",showString);
    printf("**************************************************\n");
}

void initScreen()
{
	//��ʾ�����档 
    int n = 0;
    showHeart();
    printScreen("��ӭ����ʳ�ö��͹���ϵͳ(ѧ����)��\n1.���ж���\n2.��ѯ����\n3.ɾ������\n4.�˳�ϵͳ\n���ڼ������������(1,2,3,4):\n");
    scanf("%d",&n);
    system("cls");
    switch(n)
    {
        case 1:orderScreen();break;
        case 2:searchScreen();break;
        case 3:delScreen();break;
        case 4:printScreen("�ټ�����ӭ�´�ʹ�ã�\n");exit(0);break;
        default:fflush(stdin);printf("�������˴���Ĵ��룬���������룡\n");initScreen();
    }
    fflush(stdin);
}

void saveStructure(struct data da)//����Ϊѧ����Ϣ�ṹ��
{
	//���ڽ�ѧ����Ϣ�������ļ����С� 
    char str[255]="";
    strcat(str,".\\data\\");
    strcat(str,da.date);
    strcat(str,".txt");
    FILE *fp = fopen(str,"a+");
    fprintf(fp,"%s %s %s %s %s\n",da.name,da.ID,da.pos,da.rest,da.dish);
    fclose(fp);
}

struct data readStructure(char *date,char ID[20])//����Ϊ���� ѧ��
{
	//���ڴ��ļ��ж�ȡѧ��������Ϣ�� 
    struct data da;
    int flag=0;
    IString istr;
    char buff[255];
    char str[255]="";
    strcat(str,".\\data\\");
    strcat(str,date);
    strcat(str,".txt");
    FILE *fp = fopen(str,"r");
    while(fgets(buff,255,fp)!=NULL)
    {
        Split(buff," ",&istr);
        strcpy(da.name,istr.str[0]);
        strcpy(da.ID,istr.str[1]);
        strcpy(da.pos,istr.str[2]);
        strcpy(da.rest,istr.str[3]);
        strcpy(da.dish, istr.str[4]);
        if(strcmp(da.ID,ID)==0)
        {
            flag=1;
            strcpy(da.date, date);
            break;
        }
    }
    fclose(fp);
    if(!flag)
    {
        strcpy(da.ID,"0");
        strcpy(da.date, "NOT FOUND");
    }
    return da;
}

void delStructure(char *date,char ID[20])//����Ϊ���� ѧ��
{
	//���ڴ��ļ���ɾ��ѧ��������Ϣ�� 
    char buff[255];
    struct data da;
    IString istr;
    char str[255]="";
    char strt[255]="";
    char c;
    int flag=0;
    strcat(str,".\\data\\");
    strcat(str,date);
    strcat(str,".txt");
    FILE *fp=fopen(str,"r");
    FILE *fpt=fopen(".\\data\\temp.txt","w");
    //���´������ڲ��Ҽ�¼
    while(fgets(buff,255,fp)!=NULL)
    {
        Split(buff," ",&istr);
        strcpy(da.name,istr.str[0]);
        strcpy(da.ID,istr.str[1]);
        strcpy(da.pos,istr.str[2]);
        strcpy(da.rest,istr.str[3]);
        strcpy(da.dish, istr.str[4]);
        if(strcmp(da.ID,ID)==0)
        {
            flag=1;
            strcat(strt,"�Ѳ鵽��¼:\n");
            strcat(strt,da.name);
            strcat(strt," ");
            strcat(strt,da.ID);
            strcat(strt," ");
            strcat(strt,da.date);
            strcat(strt," ");
            strcat(strt,da.pos);
            strcat(strt," ");
            strcat(strt,da.rest);
            strcat(strt," ");
            strcat(strt,da.dish);
            strcat(strt,"\nȷʵҪɾ����¼��(Y/N):\n");
            printScreen(strt);
            fflush(stdin);
            while(((c=getchar())!='Y')&&(c!='N'))
            {
                system("cls");
                printScreen("������Ĵ�������,������(Y/N)��\n");
                system("pause");
            }
            system("cls");
            if(c=='Y')
            {
                printScreen("ɾ���ɹ���\n");
                system("pause");
            }
            else if(c=='N')
            {
                printScreen("ɾ��ȡ����\n");
                fclose(fpt);
                fclose(fp);
                remove(".\\data\\temp.txt");
                system("pause");
                system("cls");
                initScreen();
            }
            continue;
        }
        fputs(buff,fpt);
    }
    system("cls");
    fclose(fpt);
    fclose(fp);
    if(flag)
    {
        remove(str);
        rename(".\\data\\temp.txt",str);
    }
    else
    {
        printScreen("δ��ѯ����¼������������ĸ�ʽ�Ƿ���ȷ��\n");
        system("pause");
        remove(".\\data\\temp.txt");
        system("cls");
        delScreen();
    }
    initScreen();
}

void searchScreen()
{
	//��ʾ��ѯ�������� �� 
    struct data da;
    char str[511]="";
    system("cls");
    printScreen("�����붩������(���磺2022-3-31):\n");
    scanf("%s",da.date);
    system("cls");
    printScreen("����������ѧ��(W�ô�д��ĸ��ʾ):\n");
    scanf("%s",da.ID);
    system("cls");
    da=readStructure(da.date,da.ID);
    if(strcmp(da.ID,"0")==0)
    {
        printScreen("δ��ѯ���������ݣ���������������Ϣ�Ƿ�����\n");
    }
    else
    {
        strcat(str,"��ѯ�����Ķ�����Ϣ���£�\n");
        strcat(str,da.name);
        strcat(str," ");
        strcat(str,da.ID);
        strcat(str," ");
        strcat(str,da.date);
        strcat(str," ");
        strcat(str,da.pos);
        strcat(str," ");
        strcat(str,da.rest);
        strcat(str," ");
        strcat(str,da.dish);
        strcat(str,"\n");
        printScreen(str);
    }
    system("pause");
    system("cls");
    initScreen();
}

void orderScreen()
{
	//��ʾ����ҳ�档 
    struct data da;
    char str[511]="";
    char c;
    system("cls");
    printScreen("��������������:\n");
    scanf("%s",da.name);
    system("cls");
    printScreen("����������ѧ��(W�ô�д��ĸ��ʾ):\n");
    scanf("%s",da.ID);
    system("cls");
    printScreen("�����붩������(���磺2022-3-31):\n");
    scanf("%s",da.date);
    system("cls");
    printScreen("��������������(��4��428):\n");
    scanf("%s",da.pos);
    system("cls");
    printScreen("�������������̼�(����Ŷ�¥������ʳ):\n");
    scanf("%s",da.rest);
    system("cls");
    printScreen("��������Ҫ���Ĳ�Ʒ:\n");
    scanf("%s",da.dish);
    system("cls");
    strcat(str,"���Ķ�����Ϣ���£���˶ԣ�\n");
    strcat(str,da.name);
    strcat(str," ");
    strcat(str,da.ID);
    strcat(str," ");
    strcat(str,da.date);
    strcat(str," ");
    strcat(str,da.pos);
    strcat(str," ");
    strcat(str,da.rest);
    strcat(str," ");
    strcat(str,da.dish);
    strcat(str,"\n");
    strcat(str,"�Ƿ񶩲�(Y/N)\n");
    printScreen(str);
    fflush(stdin);
    //���´��������ж���������Ƿ���ȷ
    while(((c=getchar())!='Y')&&(c!='N'))
    {
        system("cls");
        printScreen("������Ĵ�������,������(Y/N)��\n");
    }
    system("cls");
    //���´������ڽ��в�ͬѡ�����ת
    if(c=='Y')
    {
        saveStructure(da);
        printScreen("���ͳɹ���\n");
    }
    else if(c=='N')
    {
        printScreen("���������붩����Ϣ:��\n");
        system("pause");
        orderScreen();
    }
    system("pause");
    system("cls");
    initScreen();
}

void delScreen()
{
	//��ʾȡ���������档 
    struct data da;
    char str[511]="";
    system("cls");
    printScreen("�����붩������(���磺2022-3-31):\n");
    scanf("%s",da.date);
    system("cls");
    printScreen("����������ѧ��(W�ô�д��ĸ��ʾ):\n");
    scanf("%s",da.ID);
    system("cls");
    delStructure(da.date,da.ID);
}
