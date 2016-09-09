#include <stdio.h>

char v[7] = {'X', 'X', 'X', ' ', 'O','O','O'};

int check1X(int pos)
{
    return (v[pos+1] == ' ' ? 1 : 0);
}

int check2X(int pos)
{
    return (v[pos+2] == ' ' ? 1 : 0);
}
int check1O(int pos)
{
    return (v[pos-1] == ' ' ? 1 : 0);
}
int check2O(int pos)
{
    return (v[pos-2] == ' ' ? 1 : 0);
}

int f(int atual, int ant)
{
    int i;
    if(v[atual] == 'X')
    {
        if(check1X(atual))
        {
            v[atual+1] = v[atual];
            v[atual] = ' ';
            for(i = 0; i<7; i++)
                if(i !=atual)
                    if(f(atual+1, atual))
                        return 1;
        }

        if(check2X(atual))
        {
            v[atual+2] = v[atual];
            v[atual] = ' ';
            for(i = 0; i<7; i++)
                if(i != atual)
                    if(f(atual+2,atual))
                        return 1;
        }
        v[ant] = 'X';
        v[atual] = ' ';
    }

    if(v[atual] == 'O')
    {
        if(check1X(atual))
        {
            v[atual-1] = v[atual];
            v[atual] = ' ';
            for(i = 0; i<7; i++)
                if(i !=atual)
                    if(f(atual-1, atual))
                        return 1;
        }

        if(check2X(atual))
        {
            v[atual-2] = v[atual];
            v[atual] = ' ';
            for(i = 0; i<7; i++)
                if(i != atual)
                    if(f(atual-2,atual))
                        return 1;
        }
        v[ant] = 'O';
        v[atual] = ' ';
    }

    else return;
}
main()
{
    f(1,0);
    printf("%c",v[0]);
}


