/*
Title:
osc_tester

Description:
This demonstrates using OSC in allocore with Max 6. There is basic send and receive commands and 
a small patch for recording nav().pos() data in a text file as X Y Z coordinates. 

Author:
RJ Duran, 2014, rjduranjr@gmail.com

*/

#include "allocore/io/al_App.hpp"

using namespace al;

class MyApp : public App, osc::PacketHandler {
public:

	double phase;
	
	osc::Send send;
	osc::Recv recv;

	float x, y, z;
	float val;

	MyApp(): 
		phase(0), 
		send(8000, "localhost"),
		recv(9000, "localhost")
	{

		lens().near(0.1).far(25).fovy(45);
		nav().pos(0,0,4);
		nav().quat().fromAxisAngle(0.*M_2PI, 0,1,0);
		initWindow(Window::Dim(0,0, 600,400), "osc_tester", 40);

		// Assign a handler to the receiver		
		recv.handler(*this);
		recv.timeout(1); // set receiver to block with timeout
		recv.start();

	}

	// Receive OSC messages and handle them here
	virtual void onMessage(osc::Message& m) {
		
		float flonum;
		int intnum;
		float x,y,z;

	    if (m.addressPattern() == "/foo") {
	      std::cout << "/foo\n";
	    
	    } else if (m.addressPattern() == "/flonum") {
	      // grab a float off the m (as an input stream)
	      m >> flonum;
	      std::cout << "/flonum " << flonum << std::endl;
	    
	    } else if (m.addressPattern() == "/intnum") {
	      m >> intnum;
	      std::cout << "/intnum " << intnum << std::endl;
	    
	    } else if (m.addressPattern() == "/flonums") {
	      m >> x >> y;
	      std::cout << "/flonums " << x << " " << y << std::endl;

	    } else if (m.addressPattern() == "/1/fader1") {
	      m >> flonum;
	      std::cout << "/1/fader1 " << flonum << std::endl;
	    
	    } else if (m.addressPattern() == "/buzz") {	     
	      m >> x >> y >> z;
		  std::cout << "/buzz " << x << " " << y <<  " " << z << std::endl;
	    
	    } else {
	      std::cout << "got a message\n";
	    }

  	}

	virtual void onAnimate(double dt){
		phase += dt;
		if(phase >= 1.) phase -= 1.;
		Vec3d& v = nav().pos();
        //printf("%f %f %f\n", v.x, v.y, v.z);
        send.send("/camera", float(v.x), float(v.y), float(v.z));
	}

	virtual void onDraw(Graphics& g, const Viewpoint& v){
		
		g.pushMatrix();
			Mesh& m = g.mesh();		
			m.reset();		
			m.primitive(g.TRIANGLES);
			int N = addSphere(m, 1, 32, 32);			
			for(int i=0; i<N; ++i){
				m.color(HSV(val, 0.5, al::fold(phase + i*0.5/N, 0.5)+0.5));
			}
			g.draw(m);
		g.popMatrix();
	}


	// This is called whenever a key is pressed.
	virtual void onKeyDown(const ViewpointWindow& w, const Keyboard& k){
	
		// Use a switch to do something when a particular key is pressed
		switch(k.key()){

		// For printable keys, we just use its character symbol:
		case 'j': 
			printf("send float\n");
			send.send("/flonum", 1.23f);
			break;
		
		case 'k': 
			printf("send int\n");
			send.send("/intnum", 3);
			break;
		
		case 'l': 
			printf("send string\n");
			send.send("/string", "something");
			break;
		
		}
	}

};


int main(){
	MyApp().start();
}
