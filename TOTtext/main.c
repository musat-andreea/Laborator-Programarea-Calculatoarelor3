#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct informatii
{
    char nume[50];
    char prenume[50];
    int varsta;
}INFO;

void afisare(INFO a[20])
{
    FILE *f;
    int i, n=0;

    if((f=fopen("pers.in","rt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "pers.in");
        exit(1);
    }

    while(!feof(f))
    {
        fscanf(f, "%s %s %d", a[n].nume, a[n].prenume, &a[n].varsta);
        n++;
    }

    for(i=0; i<n-1; i++)
        printf("Persoana %s %s in varsta de %d ani\n", a[i].nume, a[i].prenume, a[i].varsta);

    fclose(f);
}

void verifica_adauga(INFO a[20], INFO d)
{
    FILE *f;
    int i, n=0, ok=0;

    if((f=fopen("pers.in","rt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "pers.in");
        exit(1);
    }

    while(!feof(f))
    {
        fscanf(f,"%s %s %d", a[n].nume, a[n].prenume, &a[n].varsta);
        n++;
    }

    fclose(f);

    for(i=0; i<n-1; i++)
    {
        if(strcmp(a[i].nume,d.nume)==0 && strcmp(a[i].prenume,d.prenume)==0 && a[i].varsta==d.varsta)
            ok++;
    }
    if(ok==0)
    {
        if((f=fopen("pers.in","at"))==NULL)
        {
            printf("Fisierul nu poate fi deschis\n");
            exit(1);
        }
        fprintf(f, "%s %s %d\n", d.nume, d.prenume, d.varsta);
        fclose(f);
    }else printf("Persoana cautata este deja in fisier\n");

    afisare(a);
}

float medie_varstnic(INFO a[20])
{
    FILE *f;
    int i, n=0, s=0;
    float med;

    if((f=fopen("pers.in","rt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis", "pers.in");
        exit(1);
    }

    while(!feof(f))
    {
        fscanf(f,"%s %s %d", a[n].nume, a[n].prenume, &a[n].varsta);
        n++;
    }

    fclose(f);

    for(i=0; i<n-1; i++)
        s=s+a[i].varsta;

    med=(float)s/(n-1);

    return med;

}

void cei_mai(INFO a[20])
{
    FILE *f;
    int i, n=0, min=100, max=0;

    if((f=fopen("pers.in","rt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "pers.in");
        exit(1);
    }

    while(!feof(f))
    {
        fscanf(f,"%s %s %d", a[n].nume, a[n].prenume, &a[n].varsta);
        n++;
    }

    for(i=0; i<n-1; i++)
        if(a[i].varsta>max)
            max=a[i].varsta;
    for(i=0; i<n-1; i++)
        if(a[i].varsta<min)
            min=a[i].varsta;

    printf("Cel/cei mai tiner/i sunt: ");

    for(i=0; i<n-1; i++)
    {
        if(a[i].varsta==min)
            printf("%s %s %d\n", a[i].nume, a[i].prenume, a[i].varsta);
    }

    printf("Cel/cei mai batran/i sunt: ");

    for(i=0; i<n-1; i++)
    {
        if(a[i].varsta==max)
            printf("%s %s %d\n", a[i].nume, a[i].prenume, a[i].varsta);
    }
    fclose(f);
}

void crescator_nume(INFO a[20])
{
    FILE *f;
    int i, n=0, j;
    INFO aux;

    if((f=fopen("pers.in","rt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "pers.in");
        exit(1);
    }

    while(!feof(f))
    {
        fscanf(f, "%s %s %d", a[n].nume, a[n].prenume, &a[n].varsta);
        n++;
    }

    for(i=0; i<n-2; i++)
        for(j=i+1; j<n-1; j++)
            if(strcmp(a[i].nume,a[j].nume)>0)
        {
            aux=a[i];
            a[i]=a[j];
            a[j]=aux;
        }
    fclose(f);

    printf("Crescator dupa nume:\n");

    for(i=0; i<n-1; i++)
        printf("%s %s %d\n", a[i].nume, a[i].prenume, a[i].varsta);
}

void desc_varsta(INFO a[20])
{
    FILE *f;
    int i, n=0, j;
    INFO aux;

    if((f=fopen("pers.in","rt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "pers.in");
        exit(1);
    }

    while(!feof(f))
    {
        fscanf(f,"%s %s %d", a[n].nume, a[n].prenume, &a[n].varsta);
        n++;
    }

    fclose(f);

    for(i=0; i<n-2; i++)
        for(j=i+1; j<n-1; j++)
            if(a[i].varsta<a[j].varsta)
    {
        aux=a[i];
        a[i]=a[j];
        a[j]=aux;
    }

    printf("Descrescator dupa varsta\n");

    for(i=0; i<n-1; i++)
        printf("%s %s %d\n", a[i].nume, a[i].prenume, a[i].varsta);
}

void elimina_ele(INFO a[20], char elimina[40])
{
    FILE *f, *cf;
    int i, n=0, ok=0;

    if((f=fopen("pers.in","rt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "pers.in");
        exit(1);
    }

    while(!feof(f))
    {
        fscanf(f, "%s %s %d", a[n].nume, a[n].prenume, &a[n].varsta);
        n++;
    }

    fclose(f);

    if((cf=fopen("copie.dat","wt"))==NULL)
                    {
                        printf("Fisierul %s nu poate fi creat\n", "copie.dat");
                        exit(1);
                    }

    for(i=0; i<n-1; i++)
        {
            if(strcmp(a[i].nume,elimina)==0)
                ok++;
            else{
                    fprintf(cf, "%s %s %d\n", a[i].nume, a[i].prenume, a[i].varsta);


            }
        }
        fclose(cf);

    if(ok==0)
        {
            printf("Nu exista numele in fisier\n");
            afisare(a);
        }
    else {
        remove("pers.in");
    rename("copie.dat","pers.in");
    afisare(a);
    }
}

void schimba_nume(INFO a[20])
{
    FILE *f;
    int i, n=0;
    char r;
    char modif[30];

    if((f=fopen("pers.in","r+t"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n","pers.in");
        exit(1);
    }

    while(!feof(f))
    {
        fscanf(f,"%s %s %d", a[n].nume, a[n].prenume, &a[n].varsta);
        n++;
    }

    for(i=0; i<n; i++)
    {
        if(i==2)
        {
            printf("Vrei sa modifici numele %s?\n", a[i].nume);
            fflush(stdin);
            scanf("%c", &r);
            if(r=='d')
            {
                printf("Introdu numele modificat\n");
                fflush(stdin);
                gets(modif);
                strcpy(a[i].nume,modif);
            }
        }
    }

fclose(f);
afisare(a);

}

void adauga(INFO a[20])
{
    FILE *f;
    int i,n;

    if((f=fopen("pers.in","at"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "pers.in");
        exit(1);
    }

    printf("Cate persoane vreti sa adaugati?\n");
    scanf("%d", &n);

    for(i=1; i<=n; i++)
    {
        printf("Introduceti numele:\n");
        fflush(stdin);
        gets(a[i].nume);

        printf("Introduceti prenumele:\n");
        fflush(stdin);
        gets(a[i].prenume);

        printf("Introduceti varsta:\n");
        scanf("%d",&a[i].varsta);

        fprintf(f, "%s %s %d\n", a[i].nume, a[i].prenume, a[i].varsta);
    }
    fclose(f);
    afisare(a);
}

void verifica_existenta(INFO a[20])
{
    FILE *f;
    int i, n=0, ok=0;
    INFO c;

    printf("Numele persoanei cautate\n");
    fflush(stdin);
    gets(c.nume);

    printf("Prenumele cautat\n");
    fflush(stdin);
    gets(c.prenume);

    printf("Varsta cautata\n");
    scanf("%d", &c.varsta);

    if((f=fopen("pers.in","rt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "pers.in");
        exit(1);
    }

    while(!feof(f))
    {
        fscanf(f, "%s %s %d", a[n].nume, a[n].prenume, &a[n].varsta);
        n++;
    }

    for(i=0; i<n-1; i++)
        if(strcmp(a[i].nume, c.nume)==0 && strcmp(a[i].prenume,c.prenume)==0 && a[i].varsta==c.varsta)
            ok++;

    if(ok==0)
        printf("nu\n");
    else printf("da\n");
    fclose(f);
}

/*int* vector_maimicca(INFO a[20])
{
    FILE *f;
    NR x;
    int i, n=0, m=0, k=1;//, v[20]

    if((f=fopen("pers.in","rt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "pers.in");
        exit(1);
    }

    while(!feof(f))
    {
        fscanf(f,"%s %s %d", a[n].nume, a[n].prenume, &a[n].varsta);
        n++;
    }

    fclose(f);

    for(i=0; i<n-1; i++)
        if(a[i].varsta<50)
        {
            x.m++;
            x.v[k]=i;
        }

    return x;
}*/

void impartire_fisiere(INFO a[20])
{
    FILE *f, *tineri, *batrani;
    int i, n=0, t=0, b=0;

    if((f=fopen("pers.in","rt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "pers.in");
        exit(1);
    }

    while(!feof(f))
    {
        fscanf(f,"%s %s %d", a[n].nume, a[n].prenume, &a[n].varsta);
        n++;
    }

    if((tineri=fopen("tineri.txt","wt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "tineri.txt");
        exit(1);
    }

    if((batrani=fopen("batrani.txt","wt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "batrani.txt");
        exit(1);
    }

    for(i=0; i<n-1; i++)
    {
        if(a[i].varsta<=50)
            fprintf(tineri,"%s %s %d\n", a[i].nume, a[i].prenume, a[i].varsta);
        if(a[i].varsta>50)
            fprintf(batrani,"%s %s %d\n", a[i].nume, a[i].prenume, a[i].varsta);
    }
    fclose(batrani);
    fclose(tineri);
    fclose(f);

afisare(a);
}

void creare_dif(INFO a[20])
{
    FILE *f, *fisier;
    int i, n=0, m=0, j;

    if((f=fopen("pers.in","rt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "pers.in");
        exit(1);
    }

    while(!feof(f))
    {
        fscanf(f, "%s %s %d", a[n].nume, a[n].prenume, &a[n].varsta);
        n++;
    }

    fclose(f);

    if((fisier=fopen("date.dat","wt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "date.dat");
        exit(1);
    }

    for(i=0; i<n-1; i++)
        {
            m=0;
            for(j=i; j<n-1; j++)
            {
                if(strcmp(a[i].nume,a[j].nume)==0 && a[i].varsta==a[j].varsta)
                    m++;
            }
            if(m==1)
                fprintf(fisier,"%s %s %d\n", a[i].nume, a[i].prenume, a[i].varsta);

        }

    fclose(fisier);
    fclose(f);

}

void IMPORTANT(INFO a[20])
{
    FILE *f;
    int i, n=0, k, ok, j, min=99;
    char nmin[30];

    if((f=fopen("pers.in","rt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "pers.in");
        exit(1);
    }

    while(!feof(f))
    {
        fscanf(f,"%s %s %d", a[n].nume, a[n].prenume, &a[n].varsta);
        n++;
    }

    for(i=0; i<n-2; i++)
    {
        ok=1;

        for(j=i+1; j<n-1; j++)
        {
            for(k=i-1; k>=0; k--)
                if(strcmp(a[i].nume,a[k].nume)==0)
                    j=n-1;
                if(strcmp(a[i].nume,a[j].nume)==0)
                    ok++;
        }
        if(j!=n)
            {
                printf("Numele %s apare de %d ori\n", a[i].nume, ok);
                if(ok<min)
                {
                    min=ok;
                    strcpy(nmin,a[i].nume);
                }
            }
    }

    printf("%s apare de cele mai putine ori, %d\n", nmin, min);
    fclose(f);
}

void afispers_cuacel_nume(INFO a[20], char cauta[40])
{
    FILE *f;
    int i, n=0, j, k=0;
    char aux[20];
    char v[20][20];

    if((f=fopen("pers.in","rt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "pers.in");
        exit(1);
    }

    while(!feof(f))
    {
        fscanf(f,"%s %s %d", a[n].nume, a[n].prenume, &a[n].varsta);
        n++;
    }

    fclose(f);

    for(i=0; i<n-1; i++)
    {
        if(strcmp(a[i].nume, cauta)==0)
        {
            strcpy(v[k],a[i].prenume);
            k++;
        }
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
        printf("%s %s\n", cauta, v[i]);
}

int main()
{
    FILE *f;
    int i, n;
    INFO a[20], d;

    printf("Introduceti numarul de persoane!\n");
    scanf("%d", &n);

    if((f=fopen("pers.in","wt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "pers.in");
        exit(1);
    }

    for(i=1; i<=n; i++)
    {
        printf("Introduceti numele pentru persoana %d\n", i);
        fflush(stdin);
        gets(a[i].nume);

        printf("Introduceti prenumele pentru persoana %d\n", i);
        fflush(stdin);
        gets(a[i].prenume);

        printf("Introduceti varsta pentru persoana %d\n", i);
        scanf("%d", &a[i].varsta);

        fprintf(f,"%s %s %d\n", a[i].nume, a[i].prenume, a[i].varsta);
    }

    fclose(f);

    afisare(a);

    printf("Introduceti numele cautat\n");
    fflush(stdin);
    gets(d.nume);

    printf("Introduceti prenumele cautat\n");
    fflush(stdin);
    gets(d.prenume);

    printf("Introduceti varsta cautat\n");
    fflush(stdin);
    scanf("%d", &d.varsta);

    verifica_adauga(a,d);

    float medie;

    medie=medie_varstnic(a);

    printf("Media varstelor %f\n", medie);

    cei_mai(a);

    crescator_nume(a);

    desc_varsta(a);

    char elimina[40];

    printf("Ce nume vreti sa eleminati?\n");
    fflush(stdin);
    gets(elimina);

    elimina_ele(a,elimina);

    schimba_nume(a);

    adauga(a);

    verifica_existenta(a);

    impartire_fisiere(a);

    creare_dif(a);

    IMPORTANT(a);

    char cauta[40];

    printf("Dupa ce nume vreti sa ordonati?\n");
    fflush(stdin);
    gets(cauta);

    afispers_cuacel_nume(a,cauta);

    return 0;
}
