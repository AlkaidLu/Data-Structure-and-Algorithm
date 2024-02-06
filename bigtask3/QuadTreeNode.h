#ifndef __QUADTREENODE_H__
#define __QUADTREENODE_H__
#ifndef NULL
#define NULL 0
#endif
#define _CRT_SECURE_NO_WARNINGS 
#include <cmath>
#include <iostream>
using namespace std;

struct Pos
{
    int x, y;
};
 
struct color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};
 
class QuadTreeNode
{
public:
    int depth;
    Pos position;
    QuadTreeNode *ru, *lu, *ld, *rd; // 1~4象限
    int height, width;
    color **rgbs;
    bool valid;
    
public:
    QuadTreeNode(color **r, int wd, int ht);
    // QuadTreeNode(QuadTreeNode *&qtn);
    QuadTreeNode(int posx, int posy, int wd, int ht);
    bool IsMakeNewNode(int Tolerance);
    void Fuzzify();
};


void TreeToImage(QuadTreeNode *rt, color **img);
void TreeExtend(QuadTreeNode *rt, int Tolerance);
void Gauss(color **img, int width);


void QuadTreeNode::Fuzzify(){
    
    int sumr=0, sumb = 0, sumg=0;
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j){
            sumr += ((int)rgbs[i][j].r);
            sumg +=((int)rgbs[i][j].g);
            sumb += ((int)rgbs[i][j].b);
        }
    int average_r=sumr / height / width;
    int average_g=sumg / height / width;
    int average_b=sumb / height / width;
 
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
        {
            rgbs[i][j].r = average_r;
            rgbs[i][j].g = average_g;
            rgbs[i][j].b = average_b;
        }
    valid = true;
}

bool QuadTreeNode::IsMakeNewNode(int Tolerance) // 是否要继续细化
{
    int sumr=0, sumb = 0, sumg=0;
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j){
            sumr += ((int)rgbs[i][j].r);
            sumg +=((int)rgbs[i][j].g);
            sumb += ((int)rgbs[i][j].b);
        }
    int average_r=sumr / height / width;
    int average_g=sumg / height / width;
    int average_b=sumb / height / width;
    long long sum = height * width;
    if(sum<=0)return true;
    long long s1, s2, s3 = 0, varr,varg, varb;
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j){
            s1 += pow((int)rgbs[i][j].r - average_r, 2);
            s2 += pow((int)rgbs[i][j].g - average_g, 2);
            s3 += pow((int)rgbs[i][j].b - average_b, 2);
        }
    varr= s1/sum;
    varg= s2/sum;
    varb= s3/sum;
    if (varr >= pow(Tolerance, 2)||varg >= pow(Tolerance, 2)||varb >= pow(Tolerance, 2))
        return false;
    return true;
}
QuadTreeNode::QuadTreeNode(int posx, int posy, int ht, int wd) 
: ru(NULL), lu(NULL), ld(NULL), rd(NULL), valid(false)
{
    position.x = posx;
    position.y = posy;
    depth=0;
    width = wd;
    height = ht;
    rgbs = (color **)malloc(height * sizeof(color *));
    for (int i = 0; i < height; i++)
        rgbs[i] = (color *)malloc(width * sizeof(color));
}
 
QuadTreeNode::QuadTreeNode(color **r, int wd, int ht) 
: ru(NULL), lu(NULL), ld(NULL), rd(NULL), valid(false)
{
    width = wd;
    height = ht;
    depth=0;
    position.x = 0;
    position.y = 0;
    rgbs = (color **)malloc(height * sizeof(color *));
    for (int i = 0; i < height; i++)
        rgbs[i] = (color *)malloc(width * sizeof(color));
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            rgbs[i][j] = r[i][j];
}


void TreeToImage(QuadTreeNode *rt, color **img)
{
    if (rt->valid)//看是否是深度最大的有效结点
    {
        for (int i = 0; i < rt->height; ++i)
            for (int j = 0; j < rt->width; ++j)
            {
                img[i + rt->position.x][j + rt->position.y].r = rt->rgbs[i][j].r;
                img[i + rt->position.x][j + rt->position.y].g = rt->rgbs[i][j].g;
                img[i + rt->position.x][j + rt->position.y].b = rt->rgbs[i][j].b;
            }
    }
    else//递归调用
    {
        TreeToImage(rt->ru, img);
        TreeToImage(rt->lu, img);
        TreeToImage(rt->ld, img);
        TreeToImage(rt->rd, img);
    }
}
 
void TreeExtend(QuadTreeNode *rt, int Tolerance)//模糊操作
{
    if (rt->IsMakeNewNode(Tolerance)|| rt->width < 10 || rt->height < 10)
    {
        rt->Fuzzify();
        return;
    }
    rt->valid = false;
    int midwidth = rt->width / 2;
    int midheight = rt->height / 2;
 
    // 1
    rt->ru = new QuadTreeNode(rt->position.x, rt->position.y, midheight, midwidth);
    rt->ru->valid = false;
    rt->ru->depth = rt->depth + 1;
    for (int i = 0; i < midheight; ++i)
        for (int j = 0; j < midwidth; ++j)
            rt->ru->rgbs[i][j] = rt->rgbs[i][j];
 
    // 2
    rt->lu = new QuadTreeNode(rt->position.x, rt->position.y + midwidth, midheight, rt->width - midwidth);
    rt->lu->valid = false;
    rt->lu->depth = rt->depth + 1;
    for (int i = 0; i < midheight; ++i)
        for (int j = 0; j < rt->width - midwidth; ++j)
            rt->lu->rgbs[i][j] = rt->rgbs[i][midwidth + j];
 
    // 3
    rt->ld = new QuadTreeNode(rt->position.x + midheight, rt->position.y, rt->height - midheight, midwidth);
    rt->ld->valid = false;
    rt->ld->depth = rt->depth + 1;
    for (int i = 0; i < rt->height - midheight; ++i)
        for (int j = 0; j < midwidth; ++j)
            rt->ld->rgbs[i][j] = rt->rgbs[midheight + i][j];
 
    // 4
    rt->rd = new QuadTreeNode(rt->position.x + midheight, rt->position.y + midwidth, rt->height - midheight, rt->width - midwidth);
    rt->rd->valid = false;
    rt->rd->depth = rt->depth + 1;
    for (int i = 0; i < rt->height - midheight; ++i)
        for (int j = 0; j < rt->width - midwidth; ++j)
            rt->rd->rgbs[i][j] = rt->rgbs[midheight + i][midwidth + j];
 
    // 递归扩展
    TreeExtend(rt->ru, Tolerance);
    TreeExtend(rt->lu, Tolerance);
    TreeExtend(rt->ld, Tolerance);
    TreeExtend(rt->rd, Tolerance);
}

void Gauss(color **img, int width)
{
    double coef[3][3] =  {{0.0453542, 0.0566406, 0.0453542},
                              {0.0566406, 0.0707355, 0.0566406},
                              {0.0453542, 0.0566406, 0.0453542}};
    for (int i = 1; i < width - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            double red = 0, green = 0, blue = 0;
            for (int k = -1; k <= 1; k++)
                for (int l = -1; l <= 1; l++)
                {
                    red += double(img[i + l][j + k].r) * coef[l + 1][k + 1]/0.4787147;
                    green += double(img[i + l][j + k].g) * coef[l + 1][k + 1]/0.4787147;
                    blue += double(img[i + l][j + k].b) * coef[l + 1][k + 1]/0.4787147;
                }
            img[i][j].r = red;
            img[i][j].g = green;
            img[i][j].b = blue;
        }
    }
}

#endif
 