#include<iostream>
#include"candide3.h"

using std::cin;
using std::cout;



Candide3 can3;


void testIO(){
	char *path_read = "D:\\用户目录\\我的文档\\Visual Studio 2010\\Projects\\Candide3\\wfm\\candide3.wfm"; //You should define your own file path
	char *path_write = "D:\\用户目录\\我的文档\\Visual Studio 2010\\Projects\\Candide3\\wfm\\_candide3.wfm"; //You should define your own file path
	can3.readFile(path_read);
	can3.writeFile(path_write);
}


void testVertexFunc(){
	int n = can3.nVertices();
	M3DVector3f v;
	cout<<"vertex number = "<<n<<'\n';
	for(int i=0; i<n; ++i){
		can3.getVertex(i,v);
		cout<<"vertex "<<i<<" ("<<v[0]<<','<<v[1]<<','<<v[2]<<")\n";
	}
	cout<<'\n';
}


void testFaceFunc(){
	int n = can3.nFaces();
	M3DVector3i f;
	cout<<"face number = "<<n<<'\n';
	for(int i=0; i<n; ++i){
		can3.getFace(i,f);
		cout<<"face "<<i<<" ["<<f[0]<<','<<f[1]<<','<<f[2]<<"]\n";
	}
	cout<<'\n';
}


void testAUFunc(){
	int n = can3.nAUs();
	M3DVector3f incr;
	Unit u;
	cout<<"AU number = "<<n<<'\n';
	for(int i=0; i<n; ++i){
		can3.getAU(i,u);
		cout<<u.getName()<<'\n';
		cout<<"vertex number: "<<u.getNum()<<'\n';
		for(int j=0; j<u.getNum(); ++j){
			u.getIncr(j,incr);
			cout<<"vertex "<<u.getIndex(j)<<": increment = ("<<incr[0]<<','<<incr[1]<<','<<incr[2]<<")\n";
		}
		cout<<'\n';
	}
	cout<<'\n';
}


void testSUFunc(){
	int n = can3.nSUs();
	M3DVector3f incr;
	Unit u;
	cout<<"SU number = "<<n<<'\n';
	for(int i=0; i<n; ++i){
		can3.getSU(i,u);
		cout<<u.getName()<<'\n';
		cout<<"vertex number: "<<u.getNum()<<'\n';
		for(int j=0; j<u.getNum(); ++j){
			u.getIncr(j,incr);
			cout<<"vertex "<<u.getIndex(j)<<": increment = ("<<incr[0]<<','<<incr[1]<<','<<incr[2]<<")\n";
		}
		cout<<'\n';
	}
	cout<<'\n';
}


void testTexFunc(){
	int n = can3.nVertices();
	M3DVector2f t;
	cout<<"vertex number = "<<n<<'\n';
	for(int i=0; i<n; ++i){
		can3.getTexCoord(i,t[0],t[1]);
		cout<<"vertex "<<i<<" texture coordinate ("<<t[0]<<','<<t[1]<<")\n";
	}
	cout<<'\n';
}


void main(){
	int test;
	cout<<"1. testIO\n2. testVertexFunc\n3. testFaceFunc\n4. testAUFunc\n5. testSUFunc\n6. testTexFunc\nplease input test: ";
	while(cin>>test){
		switch(test){
		case 1: testIO(); break;
		case 2: testVertexFunc(); break;
		case 3:testFaceFunc(); break;
		case 4:testAUFunc(); break;
		case 5:testSUFunc(); break;
		case 6:testTexFunc(); break;
		default: return;
		}
		cout<<"\n1. testIO\n2. testVertexFunc\n3. testFaceFunc\n4. testAUFunc\n5. testSUFunc\n6. testTexFunc\nplease input test: ";
	}
}