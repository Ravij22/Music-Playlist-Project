#include <iostream>
#include <string.h>
#include <fstream>
#include <bits/stdc++.h>
#include <dos.h>

using namespace std;

struct node
{
    struct node *prev;
    char music[10];
    struct node *next;
};

int i=1;

struct node *first,*r;

void inserts(char s[])
{
    int flag=0;
    struct node *temp;
    struct node *p,*ptr;
    temp=(struct node*)malloc(sizeof(struct node));
    strcpy(temp->music,s);
    temp->prev=NULL;
    temp->next=NULL;
    if(first==NULL)
    {
        first = temp;
    }
    else
    {
        p=first;
    while(p!=NULL)
    {
        if(strcmp(s,p->music)<0)
        {
            if(p==first)
            {
                temp->prev=NULL;
                temp->next=p;
                p->prev=temp;
                first=temp;
            }
            else
            {
                temp->next=p;
                temp->prev=p->prev;
                p->prev->next=temp;
                p->prev=temp;
            }
            flag=1;
            break;
        }
        ptr=p;
        p=p->next;
    }
    if(flag==0)
    {
        temp->prev=ptr;
        ptr->next=temp;
        temp->next=NULL;
    }
}
}

void display()
{
    struct node *p;
    p=first;
    while(p!=NULL)
    {
        printf("%s\n",p->music);
        p=p->next;
    }
}

void del(char s[])
{
    struct node *p;
    p=first;
    int flag=0;
    if(p==NULL)
        printf("Playlist is empty");
    else
    {
        while(p!=NULL)
        {
            if(strcmp(s,p->music)==0)
            {
                if(p==first)
                {
                    p->next->prev=NULL;
                    first=p->next;
                }
                else if(p->next==NULL)
                {
                    p->prev->next=NULL;
                }
                else
                {
                    p->prev->next=p->next;
                    p->next->prev=p->prev;
                }
                flag=1;
                free(p);
                break;
            }
            if(flag==0)
            {
                printf("music not found!");
            }
        }
    }
}

void play_next()
{
    if(r->next==NULL)
        printf("Playlist Over");
    else
    {
        r=r->next;
        printf("-------------------\n");
        printf("Now Playing: %s",r->music);
        printf("\n-------------------");
    }
}

void play_prev()
{
    if(r->prev==NULL)
        printf("Playlist Over");
    else
    {
        r=r->prev;
        printf("-------------------\n");
        printf("Now Playing: %s",r->music);
        printf("\n-------------------");
    }
}

void play_first()
{
    printf("-------------------\n");
    printf("Now Playing: %s",first->next->music);
    printf("\n-------------------");
    r=first;
}

void play_specific(char s[])
{
    struct node *p;
    p=first;
    int c=0;
    while(p!=NULL)
    {
        if(strcmp(s,p->music)==0)
        {
            printf("-------------------\n");
            printf("Now Playing: %s",p->music);
            printf("\n-------------------");
            r=p;
            c=1;
            break;
        }
        p=p->next;
    }
    if(c==0)
    {
        printf("music not found!");
    }
}

void play_random()
{
    int k=0,j;
    struct node *p;
    p=first;
    while(p!=NULL)
    {
        p=p->next;
        ++k;
    }
    p=first;
    srand(time(0));
    j=(rand()%(k-1));
    for(int i=0;i<=j;++i)
    {
        p=p->next;
    }
    printf("-------------------\n");
    printf("Now Playing: %s",p->music);
    printf("\n-------------------");
}

int main()
{
    int choice,c,x=0;
    char str[20],pass[5];
    char s[20];
    fstream f;
    ofstream g("temp.txt",ios::out);
    printf("--------------------------WELCOME--------------------------\n");
    printf("\n1.Admin\n2.User\n");
    scanf("%d",&c);
    switch(c)
    {
        case 1: printf("Enter password:");
                scanf("%s",pass);
                if(strcmp(pass,"abcd")==0)
                {
                    printf("Access granted!");
                    system("cls");
                    char title[20];
                    while(1)
                    {
                    printf("\n1.Insert\n2.Delete\n3.Exit\n");
                    scanf("%d",&x);
                    switch(x)
                    {
                        case 1: {printf("\nEnter music name:");
                                cin>>s;
                                f.open("playlist.txt",ios::app);
                                f<<s<<"\n";
                                f.close();}
                                break;

                        case 2: {printf("\nmusic to be deleted:");
                                ++i;
                                cin>>s;
                                int flag=0;
                                f.open("playlist.txt",ios::in);
                                while(f.eof()==0)
                                {
                                    f.getline(title,20,'\n');
                                    if(strcmp(title,s)!=0)
                                    {
                                        g<<title<<"\n";
                                    }
                                    else
                                    {
                                        flag=1;
                                        cout<<"music has been deleted...\n";
                                    }
                                }
                                if(flag==0)
                                    printf("music not found!");
                                f.close();
                                g.close();
                                remove("playlist.txt");
                                rename("temp.txt","playlist.txt");}
                                break;

                        case 3: exit(0);
                    }
                    }
                }
                else
                    cout<<"Wrong password";
                break;

        case 2: system("cls");
                f.open("playlist.txt",ios::in);
                char word[20];
                f.seekg(0);
                while(f.eof()==0)
                {
                    f.getline(word,20,'\n');
                    inserts(word);
                }
                r=first->next;
                printf("--------------------------PLAYLIST--------------------------\n");
                printf("-------------------\n");
                printf("Now Playing: %s",r->music);
                printf("\n-------------------");
                while(1)
                {printf("\n1.Play next music\n2.Play previous music\n3.Play first music\n4.Play specific music\n5.Display list\n6.Play Random\n7.Exit\n");
                scanf("%d",&choice);
                switch(choice)
                {
                    case 1: play_next();
                            break;

                    case 2: play_prev();
                            break;

                    case 3: play_first();
                            break;

                    case 4: printf("\nEnter music name:");
                            cin>>str;
                            play_specific(str);
                            break;

                    case 5: printf("Playlist:");
                            display();
                            break;

                    case 6: play_random();
                            break;

                    case 7: exit(0);

                }
                }
                break;

    }
    return 0;
}
