#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	// ���ô��ڴ�С������
	ofSetupOpenGL(640,480,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp()); // 6.2 ��̬�ڴ���䣺new 

}
