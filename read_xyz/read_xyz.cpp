/*
Title:
read_xyz

Description:
This demonstrates loading data from a .xyz file (text file) with values in the form, X Y Z. These could be vertices 
or any other 3 component data. Each line is parsed and read into a vector of Vec3d objects.

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
    
    std::ifstream file;
    std::vector<std::string> verts;
    
	MyApp(){
                
        std::ifstream myfilein ("/Users/rjduran/code/AlloProject/AlloSystem/allocore-apps/read_xyz/data.xyz");
        std::string line;                       // the line as a string
        std::vector<std::string> vals;          // components of each vertex in a line
        std::vector<Vec3d> verts;               // storage of vertices
        
        if (myfilein.is_open())
        {
            while ( getline (myfilein,line) )
            {
                //std::cout << line << std::endl;
                
                vals.clear();
                split(line, vals);
                
                verts.push_back( Vec3d(atof(vals[0].c_str()),
                                       atof(vals[1].c_str()),
                                       atof(vals[2].c_str())));
            }
            myfilein.close();
        } else std::cout << "Unable to open file";
        
        // print vertices
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
            
	virtual void onAnimate(double dt){}
    
	virtual void onDraw(Graphics& g, const Viewpoint& v){}

};

int main(){
	MyApp().start();

}
