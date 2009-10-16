#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	// initialize framerate
	ofSetFrameRate(30);
	ofSetBackgroundAuto(false);

	// set client's parent
	client.setParent(*this);
	
	// setup upd client
	client.setup("settings.xml");
	
	// start client
	client.start();
	
	// set the random seed
	ofSeedRandom(0);
	
	activeBallCount = 30;
	maxBalls = 100;
	bouncingBalls = new ball[maxBalls];
	
	for(int i=0; i<activeBallCount; i++){
		
		bouncingBalls[i].setParent(*this);
		bouncingBalls[i].x = ofRandom(0, client.mWidth);
		bouncingBalls[i].y = ofRandom(0, client.mHeight);
		bouncingBalls[i].xdir = ofRandom(-5,5);
		bouncingBalls[i].ydir = ofRandom(-5,5);
	}

}

//--------------------------------------------------------------
void testApp::update(){	
	client.update();
	if(client.bDrawNewFrame) {
		
		if (client.messageAvailable()) {
			string msg = client.getDataMessage();
			printf("Received: %s",msg.c_str());
		}
		
		// update ball positions
		for(int i=0; i<activeBallCount; i++){
			bouncingBalls[i].move();
			bouncingBalls[i].bounce();
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){

	if(client.bDrawNewFrame) {
		// do all of your drawing here 
		client.placeScreen();
		// clear the screen
		ofBackground(0, 0, 0);
		for(int i=0; i<activeBallCount; i++){
			//bouncingBalls[i].bounce();
			bouncingBalls[i].draw();
		}
		client.bDrawNewFrame = false;
		client.done();
	}

}
//--------------------------------------------------------------

void testApp::addBall(int x, int y){
	
	if(activeBallCount+1 < maxBalls){
		
		bouncingBalls[activeBallCount].setParent(*this);
		bouncingBalls[activeBallCount].x = x;
		bouncingBalls[activeBallCount].y = y;
		bouncingBalls[activeBallCount].xdir = ofRandom(-5,5);
		bouncingBalls[activeBallCount].ydir = ofRandom(-5,5);
		
		activeBallCount++;
	}
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){


}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	char msg[10];
	sprintf(msg, "%d,%d", x,y);
	client.broadcast(msg);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}
