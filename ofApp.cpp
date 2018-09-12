#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	this->src.allocate(ofGetWidth(), ofGetHeight());
	this->dst.allocate(ofGetWidth(), ofGetHeight());

	this->shader.load("shader/shader.vert", "shader/shader.frag");

	ofSeedRandom(39);
	this->src.begin();
	ofClear(0);

	for (int i = 0; i < 50000; i++) {
		
		ofRandom(2) > 1 ? ofSetColor(255) : ofSetColor(128);
		ofDrawRectangle(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), 1, 1);
	}

	this->src.end();

	ofSetColor(255);
}
	
//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->dst.begin();
	ofClear(0);

	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniformTexture("tex", this->src.getTexture(), 1);

	this->src.draw(0, 0);
	this->shader.end();

	this->dst.end();

	this->dst.draw(0, 0);

	std::swap(this->dst, this->src);
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}