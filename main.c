/*
Time Complexity: 
O(n) where 
n is the total number of characters in the file.
Space Complexity: 
O(l⋅c) where 
l is the number of lines and 
c is the maximum number of characters per line.
*/

#include <stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
    FILE *fp=fopen("main.txt","r");
    FILE *sp=fopen("file.i","w");
    FILE *df;
    if(fp==0 || sp==0)
    {
        printf("error in file opening\n");
        return 0;
    }
    char m[10],v[10],*d="#include",ch,*p,*q,h[20]="/usr/include/";
    int l=1,c=0,c1=0,i=0,a,j,k,r,r1,i1,o,n,n1,flag,z;
    while((ch=fgetc(fp))!=EOF)
    {
        c1++;
        if(ch=='\n')
        {
            if(c1>c)
            c=c1;
            c1=0;
            l++;
        }
    }
    char s[l][c+10];
    rewind(fp);
    
    while((fgets(s[i],c+10,fp))!=0)
    i++;    
    
    //header file inclusion//
    for(i=0;i<l;i++)
    {
        if(p=strstr(s[i],d))
        {
            p=p+9;
            strcat(h,p);
            
            for(j=0;h[j];j++);
            h[j-2]='\0';
        
            df=fopen(h,"r");
            while((ch=fgetc(df))!=EOF)
            fputc(ch,sp);
            h[13]='\0';
        }
    }
    d="#define";
   // macro replacement//
    for(i=0;i<l;i++)
    {
        if(p=strstr(s[i],d))
        {
            if(p=strchr(s[i],' '));
            {
              for(a=1,j=0;p[a]!=' ';j++,a++)
              m[j]=p[a];
              m[j]='\0';
            }
            if(p=strrchr(s[i],' '))
            {
              for(a=1,j=0;p[a];a++,j++)
              v[j]=p[a];
              v[j-1]='\0';
            }
            flag=1;
            r=strlen(m);
            r1=strlen(v);
        }
        if(flag==1)
        {
            for(i1=i+1;i1<l;i1++)
            {
                if((p=strstr(s[i1],m))!=NULL)
                {
                    o=strlen(p);
                    if(r<r1)        //replacing word which is bigger
                    {   
                        n1=r1-r;
                        
                        for(n=0,o++;n<n1;n++,o++)
                        {
                            z=o;
                            for(z;z;z--)
                            p[z]=p[z-1];
                        }
                        strncpy(p,v,r1);
                    }

                    if(r>=r1)     //replacing word is smaller or same
                    {
                        n1=r-r1;
                        for(n=0;n<n1;n++)
                        {
                            for(z=0;p[z];z++)
                            p[z]=p[z+1];
                        }
                        strncpy(p,v,r1);
                    }
                }
            }
            flag=0;
        }
    }
    
    d="//";
    //comment removal for single line//
    for(i=0;i<l;i++)
    {
        if(p=strstr(s[i],d))
        {
            for(j=0;p[j]!='\n';j++)
            p[j]=' ';
        }
    }
    
    d="/*";
    //comment removal for multiple lines//
    for(i=0,flag=0;i<l;i++)
    {
        if(p=strstr(s[i],d))
        {
            p[0]=' ';
            p[1]=' ';
            for(j=3;j;j++)
            {
                if((p[j]=='*') && (p[j+1]=='/'))
                    break;
                    
                if(p[j]=='\n')
                {
                    flag=1;
                    break;
                }
                p[j]=' ';
                
            }
            if(flag==0)
            {
                p[j]=' ';
                p[j+1]=' ';
            }
        }
        L1:
        if(flag==1)
        {
            i++;
            for(k=0;;k++)
            {
                if((s[i][k]=='*') && (s[i][k+1]=='/'))
                {
                    flag=0;
                    break;
                }
                if(s[i][k]=='\n')
                {
                    flag=1;
                    break;
                }
                s[i][k]=' ';
            }
            if(flag==0)
            {
                s[i][k]=' ';
                s[i][k+1]=' ';
            }
            if(flag==1)
            goto L1;
        }
    }
    d="main()";
    int ln=0;
    for(i=0;i<l;i++)
    {
        if((strstr(s[i],d))!=0)
        break;
        else
        s[i][0]=0;
    }
    for(i=0;i<l;i++)
    fprintf(sp,"%s",s[i]);
    return 0;
}
