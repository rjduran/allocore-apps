/*
Title:
write_xyz2

Description:
This demonstrates writing data with the format, X Y Z, into a .xyz file (text file). This version does so 
with a saveXYZ() method.

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
    
    std::vector<Vec3d> verts;
    int nVerts;

	MyApp(){
        
        nVerts = 5;
        // make some vertices
        for(int i = 0; i < nVerts; i++) {
            verts.push_back(Vec3d(i*i, (i+1)*i, (i+2)*i));
        }

        saveXYZ("/Users/rjduran/code/AlloProject/AlloSystem/allocore-apps/write_xyz2/data.xyz", verts);
	}

    void saveXYZ(const std::string& xyzFile, std::vector<Vec3d>& v)
    {
        std::ofstream file;
        file.open(xyzFile);
        
        for (std::vector<Vec3d>::iterator it = v.begin() ; it != v.end(); ++it) {
            file << float(it->x) << " " << float(it->y) << " " << float(it->z) << std::endl;
        }
        file.close();
    }
            
	virtual void onAnimate(double dt){}
    
	virtual void onDraw(Graphics& g, const Viewpoint& v){} 
    
};


int main(){
	MyApp().start();

}
