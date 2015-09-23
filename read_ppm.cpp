// vim:ts=4:et:sw=4:fdm=marker:fdl=0
#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct ppm_img 
{/*{{{*/
    int format  ; // 0 - P2 / 1 - P3
    int width   ;
    int height  ;
    int max     ;
    int num_ch  ;
    int *pixel  ;
}ppm_img;/*}}}*/
ppm_img read_ppm(FILE *fp);
char *remove_heading_blank(char* str);
int   define_ppm_format(char *str);
void  alloc_ppm_pixel(int* pixel, int width, int height);

int main(int argc, char *argv[])
{
    FILE *fp_ppm;
    char str[500];
    ppm_img my_ppm_img;

    fp_ppm = fopen(argv[1],"r");
    my_ppm_img = read_ppm(fp_ppm);
    fclose(fp_ppm);
    return 0;
}
ppm_img read_ppm(FILE* fp)
{/*{{{*/
    ppm_img my_ppm_img;
    char str[500];
    int  width  ;
    int  height ;
    int  max    ;
    int *pixel  ;
    int  num_ch ;
    int  idx; // pixel read index
    int  ch ; // channel for-loop index

    //read format
    while(1)
    {
        fgets(str,500,fp);
        strcpy(str,remove_heading_blank(str));
        if(isspace(str[0])) // detect blank line
            continue;
        else if (str[0] == '#') // detect comment
            continue;
        else
        {
            my_ppm_img.format = define_ppm_format(str);
            break;
        }
    }
    //read width & height
    while(1)
    {
        fgets(str,500,fp);
        strcpy(str,remove_heading_blank(str));
        if(isspace(str[0]))// detect blank line
            continue;
        else if (str[0] == '#') // detect comment
            continue;
        else
        { 
            sscanf(str,"%d %d",&width,&height);      
            my_ppm_img.width = width ;
            my_ppm_img.height= height;
            break;
        }
    }
    //read max
    while(1)
    {
        fgets(str,500,fp);
        strcpy(str,remove_heading_blank(str));
        if(isspace(str[0])) // detect blank line
            continue;
        else if (str[0] == '#') // detect comment
            continue;
        else
        { 
            sscanf(str,"%d",&max);
            my_ppm_img.max = max;
            break;
        }
    }

    my_ppm_img.num_ch = (my_ppm_img.format ==0) ? 1 :
                        (my_ppm_img.format ==1) ? 3 : 0;
    num_ch = my_ppm_img.num_ch;

    pixel = (int *) calloc(width*height,sizeof(int));
    my_ppm_img.pixel = pixel;


    int bb=0;
    while (fgets(str,500,fp) != NULL)
    {
        strcpy(str,remove_heading_blank(str));
        if(isspace(str[0])) // detect blank line
            continue;
        else if (str[0] == '#') // detect comment
            continue;
        else
        { 
            bb++;
            if(num_ch ==0)
                break;
            else if (num_ch == 1)
            {
                ch = sscanf(str,"%d",(my_ppm_img.pixel)++);
                if (ch != 1)
                {
                    break;
                }
            }
            else if (num_ch == 3)
            {
                ch = sscanf(str,"%d %d %d",(my_ppm_img.pixel)+0
                                          ,(my_ppm_img.pixel)+1
                                          ,(my_ppm_img.pixel)+2);
                if (ch != 3)
                {
                    break;
                }
            }
        }
    }
    //printf("%d\n",my_ppm_img.num_ch);
    //printf("%d * %d = %d\n",my_ppm_img.width,my_ppm_img.height,my_ppm_img.width*my_ppm_img.height);
    //printf("%d\n",bb);


    return my_ppm_img;
}/*}}}*/
char *remove_heading_blank(char* str)
{/*{{{*/
    while(1)
    {
        if( isblank(*(str)))
            str++;
        else 
            break;
    }
    return str;
}/*}}}*/
int   define_ppm_format(char *str)
{/*{{{*/
    if( (str[0] == 'P') || (str[0] == 'p'))
    {
        if(str[1] == '2')
            return 0;
        else if (str [1] == '3')
            return 1;
        else
            return 2;
    }
    else
        return 2;
}/*}}}*/
void  alloc_ppm_pixel(int* pixel, int width, int height)
{/*{{{*/
}/*}}}*/
