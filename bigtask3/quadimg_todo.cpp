#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "QuadTreeNode.h"
// #include "QuadTree.h"
//#include "QuadTreeFunc.h"

void printImage(char *fileName, int width, color **a);
// color color;
 
// To get ppm image from jpeg file, please visit https://convertio.co/jpg-ppm/
 
void readImage(int p, char *inFile, char *outFile) // Note that width == height here
{
	FILE *f = fopen(inFile, "rb");
 
	char u[3]; // placehoder
	int width, height, max_value;
	fscanf(f, "%s%d%d%d%c", u, &width, &height, &max_value, &u[0]);
 
	int i;
	color **colors, **img;
	colors = (color **)malloc(height * sizeof(color *));
	img = (color **)malloc(height * sizeof(color *));
	for (i = 0; i < height; i++)
	{
		colors[i] = (color *)malloc(width * sizeof(color));
		img[i] = (color *)malloc(width * sizeof(color));
	}
	for (i = 0; i < height; i++)
		fread(colors[i], sizeof(color), width, f);
	fclose(f);
	QuadTreeNode *rt = new QuadTreeNode(colors, width, height);
	TreeExtend(rt,p);
	TreeToImage(rt, img);
	for(i=0;i<20;i++){
		Gauss(img,width);
	}
	printImage(outFile, width, img);
}

 
 
void printImage(char *fileName, int width, color **a) 
{
	FILE *f = fopen(fileName, "wb");
 
	fprintf(f, "P6\n");
	fprintf(f, "%d %d\n", width, width);
	fprintf(f, "255\n");
 
	int i;
	for (i = 0; i < width; i++)
		fwrite(a[i], sizeof(color), width, f);
 
	fclose(f);
}

int main()
{
	//int tolerance;
	//cout<<"please give the tolerance (from 0 to 100):"<<endl;
	//cin>>tolerance;
	int tolerance=10;
	char inFile[100];
	char outFile[100];
	strcpy(inFile,"a.ppm");
	strcpy(outFile,"result_tolerance10_gauss.ppm");
	readImage(tolerance, inFile, outFile);
	return 0;
}