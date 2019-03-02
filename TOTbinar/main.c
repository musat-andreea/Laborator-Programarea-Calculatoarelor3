#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elemente
{
    char num[40];
    char prenum[40];
    int v;
}PRS;

void afisare(PRS per[20])
{
    FILE *fis;
    int i,n;

    if((fis=fopen("pers.bin","rb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis", "pers.bin");
        exit(1);
    }

    fseek(fis,0L,2);
    n=ftell(fis)/sizeof(PRS);
    fseek(fis,0L,0);

    for(i=1; i<=n; i++)
    {
        fread(&per[i],sizeof(PRS),1,fis);
        printf("Persoana %s %s are %d ani\n", per[i].num, per[i].prenum, per[i].v);
    }

    fclose(fis);
}

void verifica_baga(PRS per[20], PRS c)
{
    FILE *fis;
    int i, n, ok=0;

    if((fis=fopen("pers.bin","rb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "pers.bin");
        exit(1);
    }

    fseek(fis,0L,2);
    n=ftell(fis)/sizeof(PRS);
    fseek(fis,0L,0);

    fclose(fis);

    if((fis=fopen("pers.bin","ab"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis!\n", "pers.bin");
        exit(1);
    }

    for(i=1; i<=n; i++)
        if(strcmp(per[i].num,c.num)==0 && strcmp(per[i].prenum,c.prenum)==0 && per[i].v==c.v)
            ok++;

    if(ok==0)
        fwrite(&c,sizeof(PRS),1,fis);
    else printf("Persoana este deja in fsier\n");

    fclose(fis);

    afisare(per);
}

void adauga(PRS per[20])
{
    FILE *fis;
    int i, n;

    if((fis=fopen("pers.bin","ab"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "pers.bin");
        exit(1);
    }

    printf("Cate elem vreti sa introduceti?\n");
    scanf("%d", &n);

    for(i=1; i<=n; i++)
    {
        printf("Introduceti numele persoanei %d\n", i);
        fflush(stdin);
        gets(per[i].num);

        printf("Introduceti prenumele persoanei %d\n",i);
        fflush(stdin);
        gets(per[i].prenum);

        printf("Introduceti varsta persoanei %d\n", i);
        scanf("%d", &per[i].v);

        fwrite(&per[i],sizeof(PRS),1,fis);
    }
    fclose(fis);
    afisare(per);
}

void medie_varsta(PRS per[20])
{
    FILE *fis;
    int i, n, s=0, max=0, j;
    float m;
    PRS aux;

    if((fis=fopen("pers.bin","rb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n","per.bin");
        exit(1);
    }

    fseek(fis,0L,2);
    n=ftell(fis)/sizeof(PRS);
    fseek(fis,0L,0);

    for(i=1; i<=n; i++)
        fread(&per[i],sizeof(PRS),1,fis);
    fclose(fis);

    for(i=1; i<=n; i++)
        s=s+per[i].v;
    m=(float)s/n;

    printf("Media varstelor este %f\n", m);

    for(i=1; i<=n; i++)
        if(per[i].v>max)
        max=per[i].v;

    printf("Cea/Cele mai varstnice persoane sunt:\n ");

    for(i=1; i<=n; i++)
        if(per[i].v==max)
            printf("%s %s %d\n", per[i].num, per[i].prenum, per[i].v);

    printf("Sortare descrescator dupa varsta\n");

    for(i=1; i<=n-1; i++)
        for(j=i+1; j<=n; j++)
            if(per[i].v<per[j].v)
    {
        aux=per[i];
        per[i]=per[j];
        per[j]=aux;
    }

    for(i=1; i<=n; i++)
        printf("%s %s %d\n", per[i].num, per[i].prenum, per[i].v);
}

void elimina(PRS per[20], char elimin[40])
{
    FILE *fis, *f;
    int i, n, ok=0;

    if((fis=fopen("pers.bin","rb"))==NULL)
    {
        printf("Fisierul %s nu poate fi eliminat\n", "pers.bin");
        exit(1);
    }

    fseek(fis,0L,2);
    n=ftell(fis)/sizeof(PRS);
    fseek(fis,0L,0);

    for(i=1; i<=n; i++)
        fread(&per[i],sizeof(PRS),1,fis);

    fclose(fis);

    if((f=fopen("nou.in","wb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "nou.in");
        exit(1);
    }


    for(i=1; i<=n; i++)
        if(strcmp(per[i].num,elimin)==0)
            ok++;
        else fwrite(&per[i],sizeof(PRS),1,f);

        fclose(f);
    if(ok==0)
        {
            printf("Numele nu exista in fisier\n");
        }

 remove("pers.bin");
            rename("nou.in","pers.bin");

            afisare(per);



}

void modif_altreila_nume(PRS per[20])
{
    FILE *fis;
    int i, n;
    char r, nou[40];

    if((fis=fopen("pers.bin","rb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "pers.bin");
        exit(1);
    }

    fseek(fis,0L,2);
    n=ftell(fis)/sizeof(PRS);
    fseek(fis,0L,0);

    for(i=1; i<=n; i++)
        fread(&per[i],sizeof(PRS),1,fis);

    for(i=1; i<=n; i++)
    {
        if(i==3)
        {
            printf("Doriti sa modificati numele %s", per[i].num);
            fflush(stdin);
            scanf("%c", &r);
            if(r=='d')
            {
                printf("Introduceti noul nume\n");
                fflush(stdin);
                gets(nou);
                strcpy(per[i].num,nou);
            }
        }
    }
    fclose(fis);
    //afisare(per);
    for(i=1; i<=n; i++)
        printf("%s %s %d\n", per[i].num, per[i].prenum, per[i].v);
}

void existenta(PRS per[20])
{
    FILE *fis;
    int i, n, ok=0;
    char cnume[40], cprenume[40];
    int cv;

    if((fis=fopen("pers.bin","rb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n","pers.bin");
        exit(1);
    }

    fseek(fis,0L,2);
    n=ftell(fis)/sizeof(PRS);
    fseek(fis,0L,0);

    for(i=1; i<=n; i++)
        fread(&per[i],sizeof(PRS),1,fis);

    fclose(fis);

    printf("Ce nume cautati?\n");
    fflush(stdin);
    gets(cnume);

    printf("Ce prenume cautati?\n");
    fflush(stdin);
    gets(cprenume);

    printf("Ce varsta cautati?\n");
    scanf("%d", &cv);

    for(i=1; i<=n; i++)
        if(strcmp(per[i].num,cnume)==0 && strcmp(per[i].prenum,cprenume)==0 && per[i].v==cv)
            ok++;

    if(ok==0)
        printf("Persoana cautata nu se afla in fisier\n");
    else printf("Persoana cautata se afla in fisier\n");

}

void separare(PRS per[20])
{
    FILE *fis, *tineri, *batrani;
    int i, n, t, b, j;
    PRS aux, hux;

    if((fis=fopen("pers.bin","rb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "pers.bin");
        exit(1);
    }

    fseek(fis,0L,2);
    n=ftell(fis)/sizeof(PRS);
    fseek(fis,0L,0);

    for(i=1; i<=n; i++)
        fread(&per[i],sizeof(PRS),1,fis);

    fclose(fis);

    if((tineri=fopen("tineri.dat","wb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "tineri.dat");
        exit(1);
    }

    if((batrani=fopen("batrani.dat","wb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "batrani.dat");
        exit(1);
    }

    for(i=1; i<=n; i++)
        if(per[i].v<=50)
            fwrite(&per[i],sizeof(PRS),1,tineri);
        else fwrite(&per[i],sizeof(PRS),1,batrani);

    fclose(tineri);
    fclose(batrani);

    if((tineri=fopen("tineri.dat","rb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "tineri.dat");
        exit(1);
    }

    fseek(tineri,0L,2);
    t=ftell(tineri)/sizeof(PRS);
    fseek(tineri,0L,0);

    for(i=1; i<=t; i++)
        fread(&per[i],sizeof(PRS),1,tineri);

    for(i=1; i<=t-1; i++)
        for(j=i+1; j<=t; j++)
            if(per[i].v>per[j].v)
            {
                aux=per[i];
                per[i]=per[j];
                per[j]=aux;
            }

    printf("Tinerii crescator\n");

    for(i=1; i<=t; i++)
        printf("%s %s %d\n",per[i].num, per[i].prenum, per[i].v);

    fclose(tineri);

    if((batrani=fopen("batrani.dat","rb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "batrani.dat");
        exit(1);
    }

    fseek(batrani,0L,2);
    b=ftell(batrani)/sizeof(PRS);
    fseek(batrani,0L,0);

    for(i=1; i<=b; i++)
        fread(&per[i],sizeof(PRS),1,batrani);

    for(i=1; i<=b-1; i++)
        for(j=i+1; j<=b; j++)
            if(per[i].v<per[j].v)
            {
                hux=per[i];
                per[i]=per[j];
                per[j]=hux;
            }
    printf("Batrani descrescator\n");

    for(i=1; i<=b; i++)
        printf("%s %s %d\n", per[i].num, per[i].prenum, per[i].v);

    fclose(batrani);

}

void sanufiecomun(PRS per[20])
{
    FILE *fis, *fisier;
    int i, n, j, ok=0;

    if((fis=fopen("pers.bin","rb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n","pers.bin");
        exit(1);
    }

    fseek(fis,0L,2);
    n=ftell(fis)/sizeof(PRS);
    fseek(fis,0L,0);

    for(i=1; i<=n; i++)
        fread(&per[i],sizeof(PRS),1,fis);

    fclose(fis);

    if((fisier=fopen("nou.bin","wb"))==NULL)
    {
        printf("Fisierul %s nu pote fi deschis\n", "nou.bin");
        exit(1);
    }

    for(i=1; i<=n; i++)
       {
           ok=0;

            for(j=i; j<=n; j++)
                if(strcmp(per[i].num,per[j].num)==0 && per[i].v==per[j].v)
                    ok++;

            if(ok==1)
                fwrite(&per[i],sizeof(PRS),1,fisier);
       }

    fclose(fisier);

    if((fisier=fopen("nou.bin","rb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n","nou.bin");
        exit(1);
    }

    int m;

    fseek(fisier,0L,2);
    m=ftell(fisier)/sizeof(PRS);
    fseek(fisier,0L,0);

    printf("\n");

    for(i=1; i<=m; i++)
    {
        fread(&per[i],sizeof(PRS),1,fisier);
        printf("%s %s %d\n", per[i].num, per[i].prenum, per[i].v);
    }

    fclose(fisier);
}

void cmimportanta(PRS per[20])
{
    FILE *fis;
    int i,n,j,k,ok;

    if((fis=fopen("pers.bin","rb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n","pers.bin");
        exit(1);
    }

    fseek(fis,0L,2);
    n=ftell(fis)/sizeof(PRS);
    fseek(fis,0L,0);

    for(i=1; i<=n; i++)
        fread(&per[i],sizeof(PRS),1,fis);


        fclose(fis);

    for(i=1; i<=n-1; i++)
    {
        ok=1;

        for(j=i+1; j<=n; j++)
          {

            for(k=i-1; k>=1; k--)
                if(strcmp(per[i].num,per[k].num)==0)
                    j=n;
                if(strcmp(per[i].num,per[j].num)==0)
                    ok++;
          }
        if(j!=n-1)
            printf("%s apare de %d ori\n",per[i].num, ok);
    }


}

void perscunumele(PRS per[20], char numele[20])
{
    FILE *fis;
    int i, n, k=0, j;
    char v[20][20], aux[20];

    if((fis=fopen("pers.bin","rb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "pers.bin");
        exit(1);
    }

    fseek(fis,0L,2);
    n=ftell(fis)/sizeof(PRS);
    fseek(fis,0L,0);

    for(i=1; i<=n; i++)
        fread(&per[i],sizeof(PRS),1,fis);

    fclose(fis);

    for(i=1; i<=n; i++)
        if(strcmp(per[i].num, numele)==0)
        {
            strcpy(v[k],per[i].prenum);
            k++;
        }

    for(i=0; i<k-1; i++)
        for(j=i+1; j<k; j++)
            if(strcmp(v[i],v[j])>0)
            {
                strcpy(aux,v[i]);
                strcpy(v[i],v[j]);
                strcpy(v[j],aux);
            }

    for(i=0; i<k; i++)
        printf("p: %s %s\n", numele, v[i]);

}

int main()
{
    FILE *fis;
    int i, n;
    PRS per[20];

    printf("Introduceti numarul de elemente\n");
    scanf("%d", &n);

    if((fis=fopen("pers.bin","wb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis","pers.bin");
        exit(1);
    }

    for(i=1; i<=n; i++)
    {
        printf("Introduceti numele persoanei %d\n", i);
        fflush(stdin);
        gets(per[i].num);

        printf("Introduceti prenumele persoanei %d\n", i);
        fflush(stdin);
        gets(per[i].prenum);

        printf("Introduceti varsta persoanei %d\n", i);
        scanf("%d", &per[i].v);

        fwrite(&per[i],sizeof(PRS),1,fis);
    }

    fclose(fis);

    afisare(per);

    PRS c;

    printf("Introduceti numele persoanei cautate\n");
    fflush(stdin);
    gets(c.num);

    printf("Introduceti Prenumele perosoanei cautate\n");
    fflush(stdin);
    gets(c.prenum);

    printf("Introduceti varsta persoanei cautate\n");
    scanf("%d", &c.v);

    verifica_baga(per,c);

    adauga(per);

    medie_varsta(per);

    char elimin[40];

    printf("Ce nume driti sa eleiminati din fisier\n");
    fflush(stdin);
    gets(elimin);

    elimina(per,elimin);

    modif_altreila_nume(per);

    existenta(per);

    separare(per);

    sanufiecomun(per);

    cmimportanta(per);

    char numele[40];

    printf("Ce nume vreti sa afisez?\n");
    fflush(stdin);
    gets(numele);

    perscunumele(per,numele);

    return 0;
}
