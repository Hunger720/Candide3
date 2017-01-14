#include "candide3.h"
#include <iostream>
#include <fstream>

using namespace std;



Candide3::Candide3():
	n_vertices(0), n_faces(0), n_SUs(0), n_AUs(0){
	vertices=NULL; faces=NULL; tex_coords=NULL;
	SUs=NULL; AUs=NULL;
};


Candide3::~Candide3(){
	clear();
}


void Candide3::clear(){
	n_vertices = 0;
	n_faces = 0;
	n_SUs = 0;
	n_AUs = 0;
	delete[] vertices;   vertices=NULL;
	delete[] faces;      faces=NULL;
	delete[] tex_coords; tex_coords=NULL;
	delete[] SUs;        SUs=NULL;
	delete[] AUs;        AUs=NULL;
}


bool Candide3::readFile(const char *path){
	int content = 0;            //数据的具体内容:1.顶点;2.平面;3.动态单元;4.静态单元;5.动态参数;6.静态参数;7.纹理数据;
	char line[50];
	char *title[] = {"# END OF FILE","# VERTEX LIST:","# FACE LIST:","# ANIMATION UNITS LIST:","# SHAPE UNITS LIST:",
					 "# TEXTURE:","# ANIMATION PARAMETERS:","# SHAPE PARAMETERS:","# ANIMATION PARAMETERS:"};

	string t0(title[0]),    //文件结束标识
		   t1(title[1]),    //顶点列表
		   t2(title[2]),    //平面列表
		   t3(title[3]),    //动态单元列表
		   t4(title[4]),    //静态单元列表
	       t5(title[5]),    //texture list
		   t6(title[6]),    //静态参数列表
	       t7(title[7]);    //动态参数列表

	ifstream file(path,ios::in);
	if(file){
		do{
			file.getline(line,50);
			if(!t1.compare(line))content = 1;  //读到顶点列表
			if(!t2.compare(line))content = 2;  //读到平面列表
			if(!t3.compare(line))content = 3;  //读到动态单元列表
			if(!t4.compare(line))content = 4;  //读到静态单元列表
			if(!t5.compare(line))content = 5;  //mark texture list
			if(!t6.compare(line))content = 6;  //读到静态参数列表
			if(!t7.compare(line))content = 7;  //读到动态参数列表

			switch (content){

			case 1:                           //读入顶点列表
				file >> line;
				n_vertices = atoi(line);
				vertices = new M3DVector3f[n_vertices];
				for(int i=0; i<n_vertices; ++i)
					for(int j=0; j<3; ++j){
						file >> line;
						vertices[i][j] = atof(line);
					}
				content = 0;
				break;

			case 2:                           //读入平面列表
				file >> line;
				n_faces = atoi(line);
				faces = new M3DVector3i[n_faces];
				for(int i=0; i<n_faces; ++i)
					for(int j=0; j<3; ++j){
						file >> line;
						faces[i][j] = atoi(line);
					}
				content = 0;
				break;

			case 3:{                           //读入动态单元列表
				int num, idx; 
				M3DVector3f incr;

				file >> line;
				n_AUs = atoi(line);
				AUs = new Unit[n_AUs];

				for(int i=0; i<n_AUs; ++i){
					do{
						file.getline(line,50);
					}while(line[0] != '#');
					AUs[i].setName(line);  //AU name
					while(!isdigit(line[0])) file>>line;
					num = atoi(line);
					AUs[i].setNum(num);    //AU num
					for(int j=0; j<num; ++j){
						file >> line;
						idx = atoi(line);
						AUs[i].setIndex(j,idx);   //AU index
						for(int k=0; k<3; ++k){
							file >> line;
							incr[k] = atof(line);
						}
						AUs[i].setIncr(j,incr);   //AU increment
					}
				}
				content = 0;
				break;}

			case 4:{                           //读入静态单元列表
				int num, idx; 
				M3DVector3f incr;

				file >> line;
				n_SUs = atoi(line);
				SUs = new Unit[n_SUs];

				for(int i=0; i<n_SUs; ++i){
					do{
						file.getline(line,50);
					}while(line[0] != '#');
					SUs[i].setName(line);  //SU name
					while(!isdigit(line[0])) file>>line;
					num = atoi(line);
					SUs[i].setNum(num);    //SU num
					for(int j=0; j<num; ++j){
						file >> line;
						idx = atoi(line);
						SUs[i].setIndex(j,idx);   //SU index
						for(int k=0; k<3; ++k){
							file >> line;
							incr[k] = atof(line);
						}
						SUs[i].setIncr(j,incr);   //SU increment
					}
				}
				content = 0;
				break;}

			case 5:  //read texture coordinates data
				tex_coords = new M3DVector2f[n_vertices];
				for(int i=0; i<n_vertices; ++i)
					for(int j=0; j<2; ++j){
						file >> line;
						tex_coords[i][j] = atof(line);
					}
				content = 0;
				break;

			case 6:
				content = 0;
				break;

			case 7:
				content = 0;
				break;

			default:;
			}
		}while(t0.compare(line));             //读到文件尾
		file.close();
		cout<<"Read Candide3 moedl from file "<<path<<" succeeded."<<endl;
		return true;
	}else{
		cerr<<"Read Candide3 moedl from file "<<path<<" failed!"<<endl;
		clear();
		return false;
	}
}


bool Candide3::writeFile(const char *path){
	M3DVector3f incr;
	ofstream file(path,ios::out);
	if(file){
		//写入Vertex数据
		file<<"# VERTEX LIST:"<<endl;
		file<<n_vertices<<endl;
		for(int i=0; i<n_vertices; ++i){
			file<<vertices[i][0]<<' '<<vertices[i][1]<<' '<<vertices[i][2]<<endl;
		}
		file<<endl<<endl;

		//写入Face数据
		file<<"# FACE LIST:"<<endl;
		file<<n_faces<<endl;
		for(int i=0; i<n_faces; ++i){
			file<<faces[i][0]<<' '<<faces[i][1]<<' '<<faces[i][2]<<endl;
		}
		file<<endl<<endl;

		//写入AU数据
		file<<"# ANIMATION UNITS LIST:\n";
		file<<n_AUs<<"\n\n";
		for(int i=0; i<n_AUs; ++i){
			file<<AUs[i].getName()<<'\n';
			file<<AUs[i].getNum()<<'\n';
			for(int j=0; j<AUs[i].getNum(); ++j){
				AUs[i].getIncr(j,incr);
				file<<AUs[i].getIndex(j)<<' '<<incr[0]<<' '<<incr[1]<<' '<<incr[2]<<'\n';
			}
			file<<'\n';
		}
		file<<'\n';

		//写入SU数据
		file<<"# SHAPE UNITS LIST:\n";
		file<<n_SUs<<"\n\n";
		for(int i=0; i<n_SUs; ++i){
			file<<SUs[i].getName()<<'\n';
			file<<SUs[i].getNum()<<'\n';
			for(int j=0; j<SUs[i].getNum(); ++j){
				SUs[i].getIncr(j,incr);
				file<<SUs[i].getIndex(j)<<' '<<incr[0]<<' '<<incr[1]<<' '<<incr[2]<<endl;
			}
			file<<endl;
		}

		//写入AP数据
		file<<"# ANIMATION PARAMETERS:\n";

		//写入SP数据
		file<<"# SHAPE PARAMETERS:\n";

		//写入纹理坐标数据
		file<<"# TEXTURE:\n";
		for(int i=0; i<n_vertices; ++i)
			file<<tex_coords[i][0]<<' '<<tex_coords[i][1]<<'\n';

		file<<"# END OF FILE";

		file.close();
		cout<<"Write Candide3 model to "<<path<<" succeeded."<<endl;
		return true;
	}else{
		cerr<<"Write Candide3 model to "<<path<<" failed!"<<endl;
		return false;
	}
}


void Candide3::copyVerticesData(int n_vertices, M3DVector3f *vertices){
	this->n_vertices = n_vertices;
	if(this->vertices!=NULL) delete[] this->vertices;
	this->vertices = new M3DVector3f[n_vertices];
	tex_coords = new M3DVector2f[n_vertices];
	for(int i=0; i<n_vertices; ++i){
		for(int j=0; j<3; ++j) this->vertices[i][j]=vertices[i][j];
		for(int j=0; j<2; ++j) tex_coords[i][j]=0.0f;
	}
}


void Candide3::copyFacesData(int n_faces, M3DVector3i *faces){
	this->n_faces = n_faces;
	if(this->faces!=NULL) delete[] this->faces;
	this->faces = new M3DVector3i[n_faces];
	for(int i=0; i<n_faces; ++i)
		for(int j=0; j<3; ++j) this->faces[i][j]=faces[i][j];
}


void Candide3::copySUsData(int n_SUs, Unit *SUs){
	this->n_SUs = n_SUs;
	if(this->SUs!=NULL) delete[] this->SUs;
	this->SUs = new Unit[n_SUs];
	for(int i=0; i<n_SUs; ++i) this->SUs[i]=SUs[i];
}


void Candide3::copyAUsData(int n_AUs, Unit *AUs){
	this->n_AUs = n_AUs;
	if(this->AUs!=NULL) delete[] this->AUs;
	this->AUs = new Unit[n_AUs];
	for(int i=0; i<n_AUs; ++i) this->AUs[i]=AUs[i];
}


void Candide3::getVertex(int idx, M3DVector3f &vertex)const{
	if(idx<n_vertices) for(int i=0; i<3; ++i) vertex[i]=vertices[idx][i];
	else{
		for(int i=0; i<3; ++i) vertex[i]=0.0f;
		cerr<<"vertex index out of range!\n";
	}
}


void Candide3::getFace(int idx, M3DVector3i &face)const{
	if(idx<n_faces) for(int i=0; i<3; ++i) face[i]=faces[idx][i];
	else{
		for(int i=0; i<3; ++i) face[i]=0;
		cerr<<"vertex index out of range!\n";
	}
}


void Candide3::getTexCoord(int i, float &x, float &y)const{
	if(i<n_vertices){
		x = tex_coords[i][0];
		y = tex_coords[i][1];
	}else{
		cerr<<"texture coordinate index out of range!\n";
		y = x = 0.0f;
	}
}


void Candide3::getSU(int i, Unit &su)const{
	if(i<n_SUs) su=SUs[i];
	else cerr<<"SU index out of range!\n";
}
Unit& Candide3::getSU(int i)const{
	if(i<n_SUs) return SUs[i];
	else { cerr<<"SU index out of range!\n"; return *new Unit;}
}


void Candide3::getAU(int i, Unit &au)const{
	if(i<n_AUs) au=AUs[i];
}
Unit& Candide3::getAU(int i)const{
	if(i<n_SUs) return AUs[i];
	else { cerr<<"AU index out of range!\n"; return *new Unit;}
}


void Candide3::setVertex(int idx, M3DVector3f vertex){
	if(idx<n_vertices) for(int i=0; i<3; ++i) vertices[idx][i] = vertex[i];
	else cerr<<"vertex index out of range!\n";
}


void Candide3::setFace(int idx, M3DVector3i face){
	if(idx<n_faces) for(int i=0;i<3; ++i) faces[idx][i] = face[i];
	else cerr<<"face index out of range!\n";
}


void Candide3::setTexCoord(int idx, float x, float y){
	if(idx<n_vertices){
		tex_coords[idx][0] = x;
		tex_coords[idx][1] = y;
	}else cerr<<"texture coordinate index out of range!\n";
}


void Candide3::setSU(int idx, Unit su){
	if(idx<n_SUs) SUs[idx]=su;
	else cerr<<"SU index out of arrange!\n";
}


void Candide3::setAU(int idx, Unit au){
	if(idx<n_AUs) AUs[idx]=au;
	else cerr<<"AU index out of arrange!\n";
}