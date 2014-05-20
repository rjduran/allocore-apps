/*
Title:
write_xyz

Description:
This demonstrates writing data with the format, X Y Z, into a .xyz file (text file).

This example uses fstream instead of the al_File classes.

Author:
RJ Duran, 2014, rjduranjr@gmail.com

*/

#include <string>
#include <fstream>

#include "allocore/io/al_App.hpp"

using namespace al;


class MyApp : public App{
public:

    std::ofstream myfile;
    std::vector<Vec3d> verts;
    int nVerts;

	MyApp(){
        
        nVerts = 5;
        // make some vertices
        for(int i = 0; i < nVerts; i++) {
            verts.push_back(Vec3d(i*i, (i+1)*i, (i+2)*i));
        }

        myfile.open ("/Users/rjduran/code/AlloProject/AlloSystem/allocore-apps/write_xyz/data.xyz");

        for (std::vector<Vec3d>::iterator it = verts.begin() ; it != verts.end(); ++it) {
            myfile << float(it->x) << " " << float(it->y) << " " << float(it->z) << std::endl;
            std::cout << *it << std::endl;
        }
        // myfileout << "1 2 3\n";
        // myfileout << "90 80 70\n";
        // myfileout << "1.1 2.2 3.3\n";
        
        myfile.close();
    
	}
            
	virtual void onAnimate(double dt){}
    
	virtual void onDraw(Graphics& g, const Viewpoint& v){}    
    
};


int main(){
	MyApp().start();

}
