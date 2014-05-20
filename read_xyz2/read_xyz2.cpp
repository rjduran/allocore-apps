/*
Title:
read_xyz2

Description:
This demonstrates loading data from a .xyz file (text file) with values in the form, X Y Z. These could be vertices 
or any other 3 component data. Each line is parsed and read into a vector of Vec3d objects. This is a cleaned up 
version of read_xyz and uses a loadXYZ() method.

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
    
    std::vector<Vec3d> verts; // storage of vertices
    
	MyApp(){
        
        loadXYZ("/Users/rjduran/code/AlloProject/AlloSystem/allocore-apps/read_xyz2/data.xyz", verts);

        for (std::vector<Vec3d>::iterator it = verts.begin() ; it != verts.end(); ++it) {
            std::cout << *it << std::endl;
        }        
        
	}

    void split(const std::string& in, std::vector<std::string>& result){
        
        size_t pos = 0;
        size_t ndx = in.find(' ');
        
        while( true ){
            
            if( in[pos] != ' ' )
                result.push_back( in.substr(pos, ndx - pos) );
            
            if( ndx == std::string::npos ) break;
            pos = ndx+1;
            ndx = in.find(' ', pos);
        }
    }

    void loadXYZ(const std::string& xyzFile, std::vector<Vec3d>& v)
    {
        std::ifstream file(xyzFile);
        std::string line;
        std::vector<std::string> vals;
        
        if (file.is_open())
        {
            while ( getline (file,line) )
            {
                //std::cout << line << std::endl;
                
                vals.clear();
                split(line, vals);
                
                v.push_back( Vec3d(atof(vals[0].c_str()),
                                   atof(vals[1].c_str()),
                                   atof(vals[2].c_str())));
            }
            file.close();
        } else std::cout << "Unable to open file";
        
    }
            
	virtual void onAnimate(double dt){}
    
	virtual void onDraw(Graphics& g, const Viewpoint& v){}

};

int main(){
	MyApp().start();

}
