#pragma once

#include <string>
#include "math3d.h"

using std::string;



class Unit{  //静态单元和动态单元的数据结构

public:
	Unit():num(0) { index=NULL; incrs=NULL; }
	Unit(const Unit &unit):num(unit.num){
		name = unit.name;
		index = new int[num];
		incrs = new M3DVector3f[num];
		for(int i=0; i<num; ++i){
			index[i] = unit.index[i];
			for(int j=0; j<3; ++j) incrs[i][j]=unit.incrs[i][j];
		}
	}
	~Unit(){
		delete[] index; index=NULL;
		delete[] incrs; incrs=NULL;
		num = 0;
	}

	string getName()const { return name; }
	int  getNum()const            { return num; }
    int  getIndex(int n)const     { if(n<num) return index[n]; else return -1;}
	void getIncr(int n, M3DVector3f &incr)const {
		if(n<num) for(int i=0; i<3; ++i) incr[i]=incrs[n][i];
	}

	void setName(const char *name) { this->name = name; }
	void setNum(int n){
		num=n;
		if(index!=NULL)delete index; index=new int[num];
		if(incrs!=NULL)delete[] incrs; incrs=new M3DVector3f[num];
	}
	void setIndex(int n, int idx)  { if(n<num) index[n] = idx; }
	void setIncr(int n, const M3DVector3f incr){
		if(n<num) for(int i=0; i<3; ++i) incrs[n][i]=incr[i];
	}

	Unit& operator=(const Unit &unit){
		name = unit.name;
		this->setNum(unit.num);
		for(int i=0; i<num; ++i){
			index[i] = unit.index[i];
			for(int j=0; j<3; ++j) incrs[i][j]=unit.incrs[i][j];
		}
		return *this;
	}

private:
	int          num;             //每个单元的顶点的数目
	int          *index;          //顶点序号列表
	M3DVector3f  *incrs;          //每个顶点对应的增量
	string       name;           //Unit's name
};



class Candide3{

public:
	Candide3();
	~Candide3();
	void clear();      //清空模型对象的所有数据

	int nVertices()const {return n_vertices;}
	int nFaces()const    {return n_faces;};
	int nSUs()const      {return n_SUs;};
	int nAUs()const      {return n_AUs;};

	bool readFile(const char *path);                              //read a wfm file
	bool writeFile(const char *path);                             //write a wfm file
	void copyVerticesData(int n_vertices, M3DVector3f *vertices);  //bug: actually this initial the texture coordiantes data
	void copyFacesData(int n_faces, M3DVector3i *faces);
	void copySUsData(int n_SUs, Unit *SUs);
	void copyAUsData(int n_AUs, Unit *AUs);

	void  getVertex(int idx, M3DVector3f &vertex)const;
	void  getFace(int idx, M3DVector3i &face)const;
	void  getTexCoord(int i, float &x, float &y)const;
	void  getSU(int i, Unit &su)const;
	Unit& getSU(int i)const;
	void  getAU(int i, Unit &au)const;
	Unit& getAU(int i)const;

	void setVertex(int idx, M3DVector3f vertex);
	void setFace(int idx, M3DVector3i face);
	void setTexCoord(int idx, float x, float y);
	void setSU(int idx, Unit su);
	void setAU(int idx, Unit au);

private:
	int n_vertices;  //顶点数目
	int n_faces;     //三角形面数目
	int n_SUs;
	int n_AUs;
	M3DVector3f *vertices;    //指向顶点数组
	M3DVector3i *faces;       //指向三角形面数组
	M3DVector2f *tex_coords;  //指向二维纹理坐标数组
	Unit        *SUs;
	Unit        *AUs;
};