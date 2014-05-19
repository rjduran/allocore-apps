/*
Title:
mesh_loader

Description:
This demonstrates loading several OBJ files within the App class. Adapted from
the modelshader example written by Graham Wakefield 2011. 

Author:
RJ Duran 2014

*/

#include "allocore/io/al_App.hpp"
#include "allocore/graphics/al_Mesh.hpp"
#include "allocore/graphics/al_Asset.hpp"

using namespace al;

// Axes centered at world origin (0,0,0)
struct Frame {
  Mesh mx, my, mz;
  Pose pose;

  Frame() {
    mx.primitive(Graphics::TRIANGLES);
    my.primitive(Graphics::TRIANGLES);
    mz.primitive(Graphics::TRIANGLES);
    addCube(mx);
    addCube(my);
    addCube(mz);
    mx.scale(1, 0.01, 0.01);
    my.scale(0.01, 1, 0.01);
    mz.scale(0.01, 0.01, 1);
    mx.color(1, 0, 0);
    my.color(0, 1, 0);
    mz.color(0, 0, 1);
    mx.translate(0.57, 0, 0);
    my.translate(0, 0.57, 0);
    mz.translate(0, 0, 0.57);
    mx.generateNormals();
    my.generateNormals();
    mz.generateNormals();
  }

  void onDraw(Graphics& g) {
    g.pushMatrix();
      g.translate(pose.pos());
      g.rotate(pose.quat());
      g.draw(mx);
      g.draw(my);
      g.draw(mz);
    g.popMatrix();
  }
};

class MyApp : public App{
public:

	int offset1, offset2;;

	Frame frame;
	
	Light light;
	Material material;

	bool lines_mode;	
	SearchPaths searchpath;
	
	int nMeshes;
	Mesh mesh[5];

	int currentMesh;

	
	MyApp(){

		offset1 = 20;
		offset2 = 4;

		lens().near(0.1).far(1000).fovy(45);

		nav().pos(0,offset2,offset1);
		nav().quat().fromAxisAngle(0.*M_2PI, 0,1,0);

		// Arguments: position/dimensions, title, frames/second
		initWindow(Window::Dim(0,0, 800,600), "mesh_player", 60);
		
		// place light right out in front of objects
		light.pos(0, 10, 10);

		lines_mode = true;

		currentMesh = 0;
		nMeshes = 5;
			
		searchpath.addAppPaths("/obj"); // looks in the current obj directory
		loadMesh("bunny0.obj", mesh[0]);
		loadMesh("bunny1.obj", mesh[1]);
		loadMesh("bunny2.obj", mesh[2]);
		loadMesh("bunny3.obj", mesh[3]);
		loadMesh("bunny4.obj", mesh[4]);

	}

	virtual void onAnimate(double dt){}

	virtual void onDraw(Graphics& g, const Viewpoint& v){

		material();
		light();
		
		frame.onDraw(g); 
			
		if(lines_mode) {		 	
		 	mesh[currentMesh].primitive(Graphics::LINES);					 			 	
		} else {		 				
			mesh[currentMesh].primitive(Graphics::TRIANGLES);									
		}
		
		//draw the solid objects
		g.pushMatrix();
			g.scale(0.25);					
			mesh[currentMesh].color(1,0.4,0);			
			g.draw(mesh[currentMesh]);		
		g.popMatrix();			
	}
	
	void loadMesh(std::string objFile, Mesh &m)
	{
		Vec3f scene_min, scene_max, scene_center;
		
		Scene *scene = 0;
		scene = Scene::import(searchpath.find(objFile).filepath());
		
		if(scene == 0)
		{
			std::cerr << "FAIL: your obj mesh did not load." << std::endl;
			exit(1);
		}
		else
		{
			scene->getBounds(scene_min, scene_max);
			scene_center = (scene_min + scene_max) / 2.f;
		}
		
		for(int i = 0; i < scene->meshes(); i++)
			scene->mesh(i, m);		
	}

	// This is called whenever a key is pressed.
	virtual void onKeyDown(const ViewpointWindow& w, const Keyboard& k){
	
		// Use a switch to do something when a particular key is pressed
		switch(k.key()){
		
		case 'l': 
			lines_mode = !lines_mode;					
			break;

		case '[':
		    if (currentMesh > 0) {
		      currentMesh--;
		    } 
		    else {
		      currentMesh = 0;
		    }
		    
		    printf("currentMesh: %d\n", currentMesh);		    
	    	break;
		
		case ']':
			if (currentMesh < nMeshes-1) {
			currentMesh++;
	    	} 
	    	else {
	      	currentMesh = nMeshes-1;
	    	}

	    	printf("currentMesh: %d\n", currentMesh);	    	
			break;
		
		// front
		case '1':
			nav().pos(0,offset2,offset1);
			nav().quat().fromAxisAngle(0.*M_2PI, 0,1,0);
			break;

		// camera positions
		// left
		case '2': 			
			nav().pos(-offset1,offset2,0);
			nav().quat().fromAxisAngle(0.75*M_2PI, 0,1,0);
			break;

		// right
		case '3': 
			nav().pos(offset1,offset2,0);
			nav().quat().fromAxisAngle(0.25*M_2PI, 0,1,0);			
			break;

		// back
		case '4': 
			nav().pos(0,offset2,-offset1);
			nav().quat().fromAxisAngle(0.5*M_2PI, 0,1,0);			
			break;

		// top	
		case '5': 
			nav().pos(0,offset1,0);
			nav().quat().fromAxisAngle(0.75*M_2PI, 1,0,0);			
			break;

		// bottom
		case '6': 
			nav().pos(0,-offset1,0);
			nav().quat().fromAxisAngle(0.25*M_2PI, 1,0,0);			
			break;

		// SE
		case '7': 
			nav().pos(-offset1,offset2,offset1);
			nav().quat().fromAxisAngle(0.875*M_2PI, 0,1,0);			
			break;

		// NE
		case '8': 
			nav().pos(-offset1,offset2,-offset1);
			nav().quat().fromAxisAngle(0.625*M_2PI, 0,1,0);			
			break;
		
		// NW
		case '9': 
			nav().pos(offset1,offset2,-offset1);
			nav().quat().fromAxisAngle(0.375*M_2PI, 0,1,0);			
			break;
		
		// SW
		case '0': 
			nav().pos(offset1,offset2,offset1);
			nav().quat().fromAxisAngle(0.125*M_2PI, 0,1,0);			
			break;

		}
	}		
};


int main(){
	MyApp().start();
}
