#include <cstdio>
#include <cstring>

//���ϱ��
char * flag[]={
    "f l t",
    "f t l 50","f t l 40","f t l 30","f t l 20","f t l 10","f t l 0",
    "f t c",
    "f t r 10","f t r 20","f t r 30","f t r 40","f t r 50",
    "f r t",
    "f r t 30","f r t 20","f r t 10",
    "f g r t",
    "f r 0",
    "f g r b",
    "f r b 10","f r b 20","f r b 30",
    "f r b",
    "f b r 50","f b r 40","f b r 30","f b r 20","f b r 10",
    "f c b",
    "f b 0","f b l 10","f b l 20","f b l 30","f b l 40","f b l 50",
    "f l b",
    "f l b 30","f l b 20","f l b 10",
    "f g l b",
    "f l 0",
    "f g l t",
    "f l b 10","f l b 20","f l b 30",
    "f p l t","f p l b","f p r t","f p r c","f p r b",
    "f c",
    "ball",
};

char *line[]={
    "l l",
    "r l",
    "b l",
    "t l"
};

char *goal[]={
    "goal r",
    "goal l",
};
char *teammate[]={
    "teammate 1",
    "teammate 2",
    "teammate 3",
    "teammate 4",
    "teammate 5",
    "teammate 6",
    "teammate 7",
    "teammate 8",
    "teammate 9",
    "teammate 10",
    "teammate 11",

};

char *oppo[]={
  "opponent 1",
  "opponent 2",
  "opponent 3",
  "opponent 4",
  "opponent 5",
  "opponent 6",
  "opponent 7",
  "opponent 8",
  "opponent 9",
  "opponent 10",
  "opponent 11",

};


bool execute(char* strMsg);//��ȡÿһ����Ϣ
bool analyzeSeeMsg(char *strMsg);//����see��Ϣ
bool analyzeHearMsg(char *strMsg);//����hear��Ϣ
bool everySeeMsg(char *strMsg,int type);//����see��Ϣ��ÿһ��ObjectInfo
bool strinObjects(char *s,char ** v,int n);//�ж��ַ����Ƿ����ַ�������

using namespace std;
FILE *fp;

int main()
{
    fp=fopen("./in.txt","r");//��ȡ
    char msg[1001];
    fgets(msg,1000,fp);

    execute(msg);

    return 0;
}


bool execute(char* strMsg)
{
//��ȡ�ַ����е�ÿһ����Ϣ��Ȼ����н���
    char *str=strMsg;
    char *pre=strMsg;

    str++;
    while(*str!=0)
    {
        if(*str==')'&&
           (*(str+1)=='('&&
                   ((*(str+2)=='s')||(*(str+2)=='h')))
            ||(*(str+1)==0)
                       )
        {
            int f=0;
            if(*(str+1)==0) f=1;
            //*str='$';
            *(str+1)='\0';
            int l=strlen(pre);
            char tp[l];
            strcpy(tp,pre);

            if((*(pre+1)=='s')) analyzeSeeMsg(tp);
            else                analyzeHearMsg(tp);

            if(f==1) break;
            *(str+1)='(';
            pre=str+1;
            str++;
        }

    str++;
    }
    return true;
}

bool analyzeSeeMsg(char *strMsg)
{
    char *p=strMsg+5;
    while(*p!=' ') p++;
    *p='\0';

    printf("��%s����see ",strMsg+5);
    fp=fopen("./out.txt","a");
    fprintf(fp,"��%s����see ",strMsg+5);

    *p=' ';

    char *str=strMsg+1;
    while(*str!='(') str++;
    char *pre=str;
    str++;

    while(*str!=0)
    {
        if((*str==')'&&*(str+1)==' '&&*(str+2)=='(')||
           (*str==')'&&*(str+1)==')')
           )

        {
            *(str+1)='\0';
            int l=strlen(pre);
            char tp[l];
            strcpy(tp,pre);

            if(*(pre+2)=='t'||*(pre+2)=='o') everySeeMsg(tp,3);
            else if(*(pre+2)=='b')           everySeeMsg(tp,2);
            else                             everySeeMsg(tp,1);

            *(str+1)=' ';
            pre=str+2;
            str++;
        }

        str++;
    }

    printf("\n\n");
    return true;
}

//1��flag,2��ball,3��player
//����Ա����Ǻ��������з��������
bool everySeeMsg(char *strMsg,int type)
{
    fp=fopen("./out.txt","a");
    char *str=strMsg;
    char *name=strtok(str,")");
    name+=2;

    if(!strinObjects(name,teammate,11)&&!strinObjects(name,oppo,11)
       &&!strinObjects(name,line,4)&&!strinObjects(name,goal,2)
       &&!strinObjects(name,flag,53))
    {
        printf("\nInput error\n");
        return false;
    }

    char *distance=strtok(NULL," ");
    char *direction=strtok(NULL," ");
    if(type==1){
        direction[strlen(direction)-1]='\0';
    }
     printf("%s �����ҵ� Distance �� %s�� Direction�� %s��",
                name,distance,direction);
     fprintf(fp,"%s �����ҵ� Distance �� %s�� Direction�� %s��",
            name,distance,direction);
    if(type==1) return true;

    char *distChng=strtok(NULL," ");
    char *DirChng=strtok(NULL," ");
    if(type==2) DirChng[strlen(DirChng)-1]='\0';
    printf("\b,DistChng��%s��DirChng��%s��",distChng,DirChng);
    fprintf(fp,"\b��DistChng��%s��DirChng��%s��",distChng,DirChng);
    if(type==2) return true;

    char *bodyDir=strtok(NULL," ");
    char *hearDir=strtok(NULL," ");
    int l=strlen(hearDir);
    hearDir[l-1]='\0';
    printf("\b,����BodyDir�� %s��HeadDir �� %s��",bodyDir,hearDir);
    fprintf(fp,"\b,����BodyDir�� %s��HeadDir �� %s��",bodyDir,hearDir);

    return true;
}

bool analyzeHearMsg(char *strMsg)
{
    char *time,*sender,*msg;
    char space[]=" ";
    strtok(strMsg,space);
    time=strtok(NULL,space);
    sender=strtok(NULL,space);
    msg=strtok(NULL,")");

    printf("��%s���� hear ��%s���� ������%s;\n",time,sender,msg);

    fp=fopen("./out.txt","a");
    fprintf(fp,"��%s���� hear ��%s���� ������%s;\n",time,sender,msg);

    return true;
}

bool strinObjects(char *s,char ** v,int n)
{
    for(int i=0;i<n;i++)
    {
        if(strcmp(s,v[i])==0) return true;
    }
    return false;
}
