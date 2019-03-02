#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct magazin
{
    char nume[40];
    int cant;
    float pret;
}MAG;

typedef struct cos
{
    char nume[40];
    int cant;
}COS;

void afisare_stoc_mag(MAG m[20])
{
    FILE *mag;
    int i, n=0;

    if((mag=fopen("magazin.in","rt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n","magazin.in");
        exit(1);
    }

    while(!feof(mag))
    {
        fscanf(mag, "%s %d %f", m[n].nume, &m[n].cant, &m[n].pret);
        n++;
    }

    fclose(mag);

    for(i=0; i<n-1; i++)
        printf("Produsul %s, cant %d la pretul %f\n", m[i].nume, m[i].cant, m[i].pret);
}

void afisare_cos(COS c[20])
{
    FILE *cos;
    int i, n;

    if((cos=fopen("cos.in","rb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "cos.in");
        exit(1);
    }

    fseek(cos,0L,2);
    n=ftell(cos)/sizeof(COS);
    fseek(cos,0L,0);

    for(i=1; i<=n; i++)
    {
        fread(&c[i],sizeof(COS),1,cos);
        printf("%s in cant de %d\n", c[i].nume, c[i].cant);
    }

    fclose(cos);
}

void stergere_produse(COS c[20])
{
    FILE *cos, *elim;
    int i, n, nr, k=0, j, ok=0;
    char v[20][20];

    if((cos=fopen("cos.in","rb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "cos.in");
        exit(1);
    }

    fseek(cos,0L,2);
    n=ftell(cos)/sizeof(COS);
    fseek(cos,0L,0);

    for(i=1; i<=n; i++)
        fread(&c[i],sizeof(COS),1,cos);

    fclose(cos);

    if((elim=fopen("ramase.txt","wt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "ramase.txt");
        exit(1);
    }

    printf("Cate produse vreti sa stergeti?\n");
    scanf("%d", &nr);

    for(i=1; i<=nr; i++)
    {
        printf("Introduceti numele produsului %d ce trebuie eliminat\n", i);
        fflush(stdin);
        gets(v[k]);
        k++;
    }

    for(i=1; i<=n; i++)
        {
            ok=0;

            for(j=0; j<k; j++)
                if(strcmp(c[i].nume,v[j])==0)
                    ok++;

            if(ok==0)
                fprintf(elim, "%s %d\n", c[i].nume, c[i].cant);

        }


        fclose(elim);

}

void schimba_cantitate(COS c[20])
{
    FILE *cos, *fis;
    int i, n;
    char r;

    if((cos=fopen("cos.in","rb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "cos.in");
        exit(1);
    }

    fseek(cos,0L,2);
    n=ftell(cos)/sizeof(COS);
    fseek(cos,0L,0);

    for(i=1; i<=n; i++)
        fread(&c[i],sizeof(COS),1,cos);

    fclose(cos);

    if((fis=fopen("nou.dat","wb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "nou.dat");
        exit(1);
    }

    for(i=1; i<=n; i++)
    {
        printf("Doroti sa modoficati cantitate produslui %s?\n", c[i].nume);
        fflush(stdin);
        scanf("%c", &r);
        if(r=='d')
        {
            int d;
            printf("Introduceti noua cantitate\n");
            scanf("%d", &d);
            c[i].cant=d;
            fwrite(&c[i],sizeof(COS),1,fis);
        }
        else fwrite(&c[i],sizeof(COS),1,fis);
    }
    fclose(fis);
    //int s;

    remove("cos.in");
    rename("nou.dat","cos.in");

    afisare_cos(c);

    /*if((fis=fopen("nou.dat","rb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "nou.dat");
        exit(1);
    }

    fseek(fis,0L,2);
    s=ftell(fis)/sizeof(COS);
    fseek(fis,0L,0);

    for(i=1; i<=s; i++)
    {
        fread(&c[i],sizeof(COS),1,fis);
        printf("%s in cant de %d\n", c[i].nume, c[i].cant);
    }

    fclose(fis);*/

}

void cost(COS c[20], MAG m[20])
{
    FILE *cos, *mag;
    int i, n=0, nr, j;
    float cost=0;

    if((cos=fopen("cos.in","rb"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "cos.in");
        exit(1);
    }

    fseek(cos,0L,2);
    nr=ftell(cos)/sizeof(COS);
    fseek(cos,0L,0);

    for(i=1; i<=nr; i++)
        fread(&c[i],sizeof(COS),1,cos);

    fclose(cos);

    if((mag=fopen("magazin.in","rt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "magazin.in");
        exit(1);
    }

    while(!feof(mag))
    {
        fscanf(mag, "%s %d %f", m[n].nume, &m[n].cant, &m[n].pret);
        n++;
    }

    fclose(mag);

    for(i=1; i<=nr; i++)
    {
        for(j=0; j<n-1; j++)
            if(strcmp(c[i].nume,m[j].nume)==0)
            {
                if(m[j].cant<c[i].cant)
                {
                    cost=cost+m[j].cant*m[j].pret;
                    c[i].cant=c[i].cant-m[j].cant;
                    m[j].cant=0;
                }
                if(m[j].cant==c[i].cant)
                {
                    cost=cost+c[i].cant*m[j].pret;
                    m[j].cant=0;
                    c[i].cant=0;
                }
                if(m[j].cant>c[i].cant)
                {
                    cost=cost+c[i].cant*m[j].pret;
                    m[j].cant=m[j].cant-c[i].cant;
                    c[i].cant=0;
                }
            }
    }

    printf("Costul cumparaturilor: %f\n", cost);

    printf("Lista de cumparaturi devine:\n");
    for(i=1; i<=nr; i++)
    printf("%s %d\n", c[i].nume, c[i].cant);

    printf("Stocul magazinului devine\n");
    for(i=0; i<n-1; i++)
        printf("%s %d %f\n", m[i].nume, m[i].cant, m[i].pret);


}

int main()
{
    FILE *mag, *cos;
    COS c[20];
    MAG m[20];
    int i, n, nr;

    printf("Introduceti numarul de produse din magazin\n");
    scanf("%d",&n);

    if((mag=fopen("magazin.in","wt"))==NULL)
    {
        printf("Fisierul %s nu poate fi deschis\n", "magazin.in");
        exit(1);
    }

    for(i=1; i<=n; i++)
    {
        printf("Introduceti numele produsului %d din magazin\n", i);
        fflush(stdin);
        gets(m[i].nume);

        printf("Introduceti cantitatea prodului %d din magazin\n", i);
        scanf("%d", &m[i].cant);

        printf("Introduceti pretul produsului %d din magazin\n", i);
        scanf("%f", &m[i].pret);

        fprintf(mag, "%s %d %f\n", m[i].nume, m[i].cant, m[i].pret);
    }

    fclose(mag);

    afisare_stoc_mag(m);

    if((cos=fopen("cos.in","wb"))==NULL)
    {
        printf("Fsierul %s nu poate fi deschis\n", "cos.in");
        exit(1);
    }

    printf("Introduceti numarul de cumparaturi din cos\n");
    scanf("%d", &nr);

    for(i=1; i<=nr; i++)
    {
        printf("Introduceti numele produsului %d din cos\n", i);
        fflush(stdin);
        gets(c[i].nume);

        printf("Introduceti cantitatea produsului %d din cos\n", i);
        scanf("%d", &c[i].cant);

        fwrite(&c[i],sizeof(COS),1,cos);
    }

    fclose(cos);

    afisare_cos(c);

    stergere_produse(c);

    schimba_cantitate(c);

    cost(c,m);

    return 0;
}
