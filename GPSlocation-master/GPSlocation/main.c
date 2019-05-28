//
//  main.c
//  GPSlocation
//
//  Created by 20161104570 on 17/6/22.
//  Copyright © 2017年 20161104570. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
int main()
{
    int i,year,n,a[10],b,month,day,hour,minute,second;
    double rate1;
    char c1[70];
    char c2[70];
    char lat[10];//纬度
    char lon[10];//经度
    char time[10];//时间
    char asl[5];//海拔
    char date[10];//从gps中提取的时间
    char rate[5];//速率
    char sat[5];//卫星
    char course[6];//航向
    char dir1[2];//经方向
    char dir2[2];//纬方向
    FILE *fp;
    FILE *fr;
    fp = fopen("//Users//a20161104570//Desktop//GPSlocation//GPS170510.log","r");
    fr = fopen("//Users//a20161104570//Desktop//GPSlocation//a.csv","w");
    printf("日期,时间,经度方向,经度,纬度方向,纬度,海拔,速率,航向,卫星数量\n");
    fprintf(fr,"日期,时间,经度方向,经度,纬度方向,纬度,海拔,速率,航向,卫星数量\n");
    if (fp == NULL)
    {
        printf("File open error !\n");
        return -1;
    }
    else
    {
        while(fscanf(fp,"%s %s",c1,c2)!=EOF)
        {
            //经度
            for(i=0;i<1;i++)
                dir1[i]=c1[i+37];
            for(i=0;i<9;i++)
                lon[i]=c1[i+27];
            //纬度
            for(i=0;i<1;i++)
                dir2[i]=c1[i+25];
            for(i=0;i<8;i++)
                lat[i]=c1[i+16];
            //时间
            for(i=0;i<6;i++)
                time[i]=c1[i+7];
            n=0;
            n=atoi(time);
            for(i=0;i<6;i++)
            {
                a[i]=n%10;
                n=n/10;
            }
            hour=a[5]*10+a[4]+8;
            minute=a[3]*10+a[2];
            second=a[1]*10+a[0];
            b=0;
            if(hour>=24)
            {
                b++;
                hour=hour-24;
            }
            //海拔
            for(i=0;i<4;i++)
                asl[i]=c2[i+43];
            //日期
            for(i=0;i<6;i++)
                date[i]=c1[i+51];
            n=0;
            n=atoi(date);
            for(i=0;i<6;i++)
            {
                a[i]=n%10;
                n=n/10;
            }
            year=a[1]*10+a[0]+2000;
            month=a[3]*10+a[2];
            day=a[5]*10+a[4];
            if(b!=0)
                day=day+1;
            if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
            {
                if(day>31)
                {
                    day=day-31;
                    month=month+1;
                }
            }
            if(month==4||month==6||month==9||month==11)
            {
                if(day>30)
                {
                    day=day-30;
                    month=month+1;
                }
            }
            if(month==2)
            {
                if((year%4==0&&year%100!=0)||year%400==0)
                {
                    if(day>29)
                    {
                        day=day-29;
                        month=month+1;
                    }
                }
                else
                {
                    if(day>28)
                    {
                        day=day-28;
                        month=month+1;
                    }
                }
            }
            if(month>12)
            {
                month=month-12;
                year=year+1;
            }
            //速率
            for(i=0;i<5;i++)
                rate[i]=c1[i+39];
            rate1=atoi(rate);
            rate1=rate1*1.852;
            //卫星数量
            for(i=0;i<2;i++)
                sat[i]=c2[i+39];
            
            //航向
            for(i=0;i<5;i++)
                course[i]=c1[i+45];
                course[5]='\0';
            //*******************************
            
            printf("%d年%d月%d日,",year,month,day);
            printf("%d时%d分%d秒,",hour,minute,second);
            printf("%s,",dir1);
            printf("%s,",lon);
            printf("%s,",dir2);
            printf("%s,",lat);
            printf("%s米,",asl);
            printf("%.2f公里／小时,",rate1);
            printf("航向:%s,",course);
            printf("%s颗\n",sat);
            
            fprintf(fr,"%d年%d月%d日,",year,month,day);
            fprintf(fr,"%d时%d分%d秒,",hour,minute,second);
            fprintf(fr,"%s,",dir1);
            fprintf(fr,"%s,",lon);
            fprintf(fr,"%s,",dir2);
            fprintf(fr,"%s,",lat);
            fprintf(fr,"%s米,",asl);
            fprintf(fr,"%.2f公里／小时,",rate1);
            fprintf(fr,"航向:%s,",course);
            fprintf(fr,"%s颗\n",sat);
        }
        fclose(fp);
        fclose(fr);
    }
    return 0;
}
