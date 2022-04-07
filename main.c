#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*程序名称：食堂订餐管理系统(学生端)。
 *程序功能：实现学生端的订餐查询与删除功能。
 *程序作者：2002124W18张浩然、2002124W19郑子沐、2002124w20邢倡基、2002124W16高天行。 
 *程序分工：主编、主策、第一作者     注释             补充功能           监制      （与上方对应）
 * 注：由于中文编码原因，请直接运行qiafan.exe文件,不要直接编译代码,除非正确设置了编译器的编码方式为UTF-8
 */

typedef struct {
    char **str;
    size_t num;
}IString;

//用于储存学生姓名学号订餐日期、订餐地点、具体餐馆、菜品。
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
	//（邢倡基补充程序）用于将长春加油四字以心型在主界面展示。 
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
                case 0:strcpy(str,"长");break;
                case 1:strcpy(str,"春");break;
                case 2:strcpy(str,"加");break;
                case 3:strcpy(str,"油");break;
            }
            strcpy(ch,a*a*a-x*x*y*y*y<=0.0f?(m++,m%2==0?(n++,str):""):" ");
            printf("%s",ch);

        }
        printf("\n");
    }
}

int Split(char *src, char *delim, IString* istr)//引用的代码，用于实现按照某一字符分割字符串功能
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

void printScreen(char *showString)//参数为要显示的内容
{
	//美化显示界面（在输出数据上下分别添加一行"*"） 。 
    char str[511];

    printf("**************************************************\n");
    printf("%s",showString);
    printf("**************************************************\n");
}

void initScreen()
{
	//显示主界面。 
    int n = 0;
    showHeart();
    printScreen("欢迎来到食堂订餐管理系统(学生端)！\n1.进行订餐\n2.查询订单\n3.删除订单\n4.退出系统\n请在键盘上输入代号(1,2,3,4):\n");
    scanf("%d",&n);
    system("cls");
    switch(n)
    {
        case 1:orderScreen();break;
        case 2:searchScreen();break;
        case 3:delScreen();break;
        case 4:printScreen("再见，欢迎下次使用！\n");exit(0);break;
        default:fflush(stdin);printf("您输入了错误的代码，请重新输入！\n");initScreen();
    }
    fflush(stdin);
}

void saveStructure(struct data da)//参数为学生信息结构体
{
	//用于将学生信息保存在文件当中。 
    char str[255]="";
    strcat(str,".\\data\\");
    strcat(str,da.date);
    strcat(str,".txt");
    FILE *fp = fopen(str,"a+");
    fprintf(fp,"%s %s %s %s %s\n",da.name,da.ID,da.pos,da.rest,da.dish);
    fclose(fp);
}

struct data readStructure(char *date,char ID[20])//参数为日期 学号
{
	//用于从文件中读取学生订单信息。 
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

void delStructure(char *date,char ID[20])//参数为日期 学号
{
	//用于从文件中删除学生订单信息。 
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
    //以下代码用于查找记录
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
            strcat(strt,"已查到记录:\n");
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
            strcat(strt,"\n确实要删除记录吗(Y/N):\n");
            printScreen(strt);
            fflush(stdin);
            while(((c=getchar())!='Y')&&(c!='N'))
            {
                system("cls");
                printScreen("您输入的代码有误,请重试(Y/N)！\n");
                system("pause");
            }
            system("cls");
            if(c=='Y')
            {
                printScreen("删除成功！\n");
                system("pause");
            }
            else if(c=='N')
            {
                printScreen("删除取消！\n");
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
        printScreen("未查询到记录，请检查您输入的格式是否正确！\n");
        system("pause");
        remove(".\\data\\temp.txt");
        system("cls");
        delScreen();
    }
    initScreen();
}

void searchScreen()
{
	//显示查询订单界面 。 
    struct data da;
    char str[511]="";
    system("cls");
    printScreen("请输入订餐日期(例如：2022-3-31):\n");
    scanf("%s",da.date);
    system("cls");
    printScreen("请输入您的学号(W用大写字母表示):\n");
    scanf("%s",da.ID);
    system("cls");
    da=readStructure(da.date,da.ID);
    if(strcmp(da.ID,"0")==0)
    {
        printScreen("未查询到订餐数据，请检查您的输入信息是否有误！\n");
    }
    else
    {
        strcat(str,"查询到您的订餐信息如下：\n");
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
	//显示订餐页面。 
    struct data da;
    char str[511]="";
    char c;
    system("cls");
    printScreen("请输入您的姓名:\n");
    scanf("%s",da.name);
    system("cls");
    printScreen("请输入您的学号(W用大写字母表示):\n");
    scanf("%s",da.ID);
    system("cls");
    printScreen("请输入订餐日期(例如：2022-3-31):\n");
    scanf("%s",da.date);
    system("cls");
    printScreen("请输入您的宿舍(如4舍428):\n");
    scanf("%s",da.pos);
    system("cls");
    printScreen("请输入您订餐商家(如二号二楼西北美食):\n");
    scanf("%s",da.rest);
    system("cls");
    printScreen("请输入您要定的餐品:\n");
    scanf("%s",da.dish);
    system("cls");
    strcat(str,"您的订餐信息如下，请核对：\n");
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
    strcat(str,"是否订餐(Y/N)\n");
    printScreen(str);
    fflush(stdin);
    //以下代码用于判断输入代码是否正确
    while(((c=getchar())!='Y')&&(c!='N'))
    {
        system("cls");
        printScreen("您输入的代码有误,请重试(Y/N)！\n");
    }
    system("cls");
    //以下代码用于进行不同选择的跳转
    if(c=='Y')
    {
        saveStructure(da);
        printScreen("订餐成功！\n");
    }
    else if(c=='N')
    {
        printScreen("请重新输入订餐信息:！\n");
        system("pause");
        orderScreen();
    }
    system("pause");
    system("cls");
    initScreen();
}

void delScreen()
{
	//显示取消订单界面。 
    struct data da;
    char str[511]="";
    system("cls");
    printScreen("请输入订餐日期(例如：2022-3-31):\n");
    scanf("%s",da.date);
    system("cls");
    printScreen("请输入您的学号(W用大写字母表示):\n");
    scanf("%s",da.ID);
    system("cls");
    delStructure(da.date,da.ID);
}
