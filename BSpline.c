#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <graphics.h>
#include <math.h>

void draw_coordinate()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    closegraph(); //bununla diger ekrani kapatabilirsin
    initwindow(820,820,"Coordinate System", 200,0);

    for(int i=0; i<41; i++)
    {
        setcolor(8);
        int x = 10 + (i*20);
        int y = 10 + (i*20);
        line(x,0,x,820);
        line(0,y,820,y);
    }

    setcolor(15);

    line(5,410,815,410);
    line(410,5,410,815);

    for(int i=0; i<41; i++)
    {
        int x = 10 + (i*20);
        int y = 10 + (i*20);
        line(x,406,x,414);
        line(406,y,414,y);
    }

    for(int i=1; i<21; i++)
    {
        char sayi[2];
        int x = 408 + (i*20);
        sprintf(sayi,"%d",i);
        settextstyle(2,0,5);
        outtextxy(x,417,sayi);
    }

    for(int i=20; i>0; i--)
    {
        char sayi[2];
        int y = 408 - (i*20);
        sprintf(sayi,"%d",i);
        settextstyle(2,0,5);
        outtextxy(417,y,sayi);
    }

    for(int i=20; i>0; i--)
    {
        char sayi[2];
        int x = 408 - (i*20);
        sprintf(sayi,"%d",i);
        settextstyle(2,0,5);
        outtextxy(x-6,413,"_");
        outtextxy(x,417,sayi);
    }

    for(int i=1; i<21; i++)
    {
        char sayi[2];
        int y = 408 + (i*20);
        sprintf(sayi,"%d",i);
        settextstyle(2,0,5);
        outtextxy(414,y-4,"_");
        outtextxy(420,y,sayi);
    }
}

//noktalar çemberin içinde mi kontrolü
//www.geeksforgeeks.org/minimum-enclosing-circle-set-1 faydalanılmıştır:
bool is_inside(float merkezi[2], int dizi[][2], float r,int satirrr)
{

    float x2=merkezi[0];
    float y2=merkezi[1];

    for(int i=0 ; i<satirrr-1 ; i++)
    {
        int x1=dizi[i][0];
        int y1=dizi[i][1];

        int mesafe = sqrt(pow((x2-x1),2)+pow((y2-y1),2));

        if (mesafe > ceil(r))
        {
            return false;
        }
    }

    return true;
}


void cember_ciz(float merkez[2], float yaricap)
{

    printf("\ncemberin merkezi {%.2f , %.2f} noktasi ve yaricapi= %f\n",merkez[0],merkez[1],yaricap);

    //cember cizimi
    setcolor(11);
    int a, b;
    a = 410 + (merkez[0]*20);
    b = 410 - (merkez[1]*20);
    circle(a,b,yaricap*20);

    //yaricap ciz
    setcolor(10);
    line(a,b,a+yaricap*20,b);

    //merkez noktasi
    setcolor(4);
    setlinestyle(0,0,NORM_WIDTH);
    for ( int radius = 1; radius <= 4 ; radius++)
    {
        circle(a,b,radius);
    }

    // ekrana merkez, yaricap yazdırma
    setcolor(15);
    settextstyle(8,0,1);
    char x_nokt[5], y_nokt[5], str[9];
    float xx = merkez[0];
    float yy = merkez[1];
    sprintf(x_nokt,"%.2f", xx);
    outtextxy(25,20,"X: ");
    outtextxy(52,20,x_nokt);
    sprintf(y_nokt,"%.2f", yy);
    outtextxy(25,45,"Y: ");
    outtextxy(52,45,y_nokt);
    sprintf(str,"%f",yaricap);
    outtextxy(25,70,"Yaricap: ");
    outtextxy(120,70,str);
}

void cember_hesapla(int satirr, int dizi[][2])
{

    float m1 = 0.0; //iki nokta arasi en uzak mesafe
    float m2 = 0.0; //iki nokta arasi diger en uzak mesafe
    float n1[2]; //birinci nokta
    float n2[2]; //ikinci nokta
    float n3[2]; // 3
    float n4[2]; // 4
    float temp = 0.0;

    for(int i=0 ; i<satirr-1 ; i++)
    {
        for(int j=1 ; j<satirr-1 ; j++)
        {

            int x1=dizi[i][0];
            int x2=dizi[j+1][0];
            int y1=dizi[i][1];
            int y2=dizi[j+1][1];

            temp = sqrt(pow((x2-x1),2)+pow((y2-y1),2));

            if(temp>m1)
            {
                if(temp>m2)
                {
                    m2=temp;
                    n1[0]=x1;
                    n1[1]=y1;
                    n2[0]=x2;
                    n2[1]=y2;
                }
                else
                {
                    m1=temp;
                    n3[0]=x1;
                    n3[1]=y1;
                    n4[0]=x2;
                    n4[1]=y2;
                }
            }
        }
    }


    float merkez[2], yaricap;
    yaricap = m2/2.0;
    merkez[0]=(n1[0]+n2[0])/2.0;
    merkez[1]=(n1[1]+n2[1])/2.0;

    bool flag = is_inside(merkez,dizi,yaricap,satirr);

    if(flag == true)
    {
        cember_ciz(merkez,yaricap);
    }
    else
    {
        if(n1[0]==n2[0] && n1[1]==n2[1])
        {
            merkez[0]=(n1[0]+n3[0]+n4[0])/3.0;
            merkez[1]=(n1[1]+n3[1]+n4[1])/3.0;
        }
        else if(n1[0]==n3[0] && n1[1]==n3[1])
        {
            merkez[0]=(n1[0]+n2[0]+n4[0])/3.0;
            merkez[1]=(n1[1]+n2[1]+n4[1])/3.0;
        }
        else if(n1[0]==n4[0] && n1[1]==n4[1])
        {
            merkez[0]=(n1[0]+n2[0]+n3[0])/3.0;
            merkez[1]=(n1[1]+n2[1]+n3[1])/3.0;
        }
        else if(n2[0]==n3[0] && n2[1]==n3[1])
        {
            merkez[0]=(n1[0]+n2[0]+n4[0])/3.0;
            merkez[1]=(n1[1]+n2[1]+n4[1])/3.0;
        }
        else if(n2[0]==n4[0] && n2[1]==n4[1])
        {
            merkez[0]=(n1[0]+n2[0]+n3[0])/3.0;
            merkez[1]=(n1[1]+n2[1]+n3[1])/3.0;
        }
        else if(n4[0]==n3[0] && n4[1]==n3[1])
        {
            merkez[0]=(n1[0]+n2[0]+n4[0])/3.0;
            merkez[1]=(n1[1]+n2[1]+n4[1])/3.0;
        }
        else
        {
            merkez[0]=(n1[0]+n2[0]+n3[0]+n4[0])/4.0;
            merkez[1]=(n1[1]+n2[1]+n3[1]+n4[1])/4.0;
        }

        float uzaklik[4];
        uzaklik[0] = sqrt(pow((n1[0]-merkez[0]),2) + pow((n1[1]-merkez[1]),2));
        uzaklik[1] = sqrt(pow((n2[0]-merkez[0]),2) + pow((n2[1]-merkez[1]),2));
        uzaklik[2] = sqrt(pow((n3[0]-merkez[0]),2) + pow((n3[1]-merkez[1]),2));
        uzaklik[3] = sqrt(pow((n4[0]-merkez[0]),2) + pow((n4[1]-merkez[1]),2));
        yaricap = uzaklik[0];

        for(int i=0; i<4; i++)
        {
            if(uzaklik[i]>yaricap)
            {
                yaricap = uzaklik[i];
            }
        }

        bool flag1 = is_inside(merkez,dizi,yaricap,satirr);
        if(flag1==true)
        {
            cember_ciz(merkez,yaricap);
        }
    }

}

int fact(int n)
{
    if(n==0)
        return 1;
    else
        return n*fact(n-1);
}

int comb(int n,int r)
{
    return (fact(n)/(fact(n-r)*fact(r)));
}

int main()
{
    // grafik çizimi ......
    draw_coordinate();

    //dosya okuma
    FILE *fp = fopen("koordinat.txt","r+");

    if(fp == NULL)
    {
        printf("dosya acilamadi");
        return 1;
    }

    // satir sayisini bulma
    int satir=1;
    char ch;
    while(!feof(fp))
    {
        ch=getc(fp);
        if(ch=='\n')
            satir++;
    }

    fseek(fp,0,SEEK_SET); //imleci başa aldık

    //noktaları diziye atama
    int dizi[satir][2];

    while(!feof(fp))
    {
        for(int i=0; i<satir; i++)
        {
            for(int j=0; j<2; j++)
            {
                fscanf(fp,"%d",&dizi[i][j]);
            }
        }
    }
    fclose(fp);

    setcolor(14);

    //x,y noktalarinin piksellerini bul
    int mtrs[satir][4];

    for(int i=0; i<satir; i++)
    {
        int x = dizi[i][0];
        int y = dizi[i][1];

        int a, b;
        a = 410 + (x*20);
        b = 410 - (y*20);

        mtrs[i][0] = x;
        mtrs[i][1] = y;
        mtrs[i][2] = a;
        mtrs[i][3] = b;

        //noktaları göster
        for ( int radius = 1; radius <= 3 ; radius++)
        {
            circle(a, b, radius);
        }
    }

    printf("\n");
    //noktaları cmd de yazdır
    for(int i=0; i<satir; i++)
    {
        printf("%d. nokta: {%d, %d}",i+1,mtrs[i][0], mtrs[i][1]);
        printf("\n");
    }

    //uzak nokta hesabı ve cember cizimi ............

    cember_hesapla(satir, dizi);

    int n=satir-1;

    //https://www.youtube.com/watch?v=hqONlh0YTeA&t=254s faydalanılmıştır:
    float tx,ty,t;
    for(t=0; t<=1; t=t+0.000001)
    {
        tx = 0;
        ty = 0;
        int a = 0;
        int b = 0;
        for(int i=0; i<=n; i++)
        {
            tx = tx + (comb(n,i) * pow(1-t,n-i) * pow(t,i) * dizi[i][0]);
            ty = ty + (comb(n,i) * pow(1-t,n-i) * pow(t,i) * dizi[i][1]);

        }
        a = 410 + (tx*20);
        b = 410 - (ty*20);
        putpixel(a,b,14);
    }

    getch();
    closegraph();

    return 0;
}







