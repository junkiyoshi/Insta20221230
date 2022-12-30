#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int v_span = 1;
	int u_span = 30;
	int R = 230;
	int r = 50;

	ofMesh face, line;
	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	float noise_seed = ofRandom(1000);
	ofColor color;
	for (int v = 0; v <= 360; v += v_span) {

		bool flag = true;
		int u_start = ofMap(ofNoise(noise_seed, cos(v * DEG_TO_RAD) * 0.25, sin(v * DEG_TO_RAD) * 0.25, ofGetFrameNum() * 0.005), 0, 1, -360 * 2, 360 * 2);
		int next_u = ofMap(ofNoise(noise_seed, cos((v + v_span) * DEG_TO_RAD) * 0.25, sin((v + v_span) * DEG_TO_RAD) * 0.25, ofGetFrameNum() * 0.005), 0, 1, -360 * 2, 360 * 2);
		for (int u = u_start; u < u_start + 360; u += u_span) {

			if (flag) {

				face.addVertex(this->make_point(R, r, u, v));
				face.addVertex(this->make_point(R, r, u + u_span * 0.75, v));
				face.addVertex(this->make_point(R, r, next_u + u_span * 0.75, v + v_span));
				face.addVertex(this->make_point(R, r, next_u, v + v_span));

				line.addVertex(this->make_point(R, r, u, v));
				line.addVertex(this->make_point(R, r, u + u_span * 0.75, v));
				line.addVertex(this->make_point(R, r, next_u + u_span * 0.75, v + v_span));
				line.addVertex(this->make_point(R, r, next_u, v + v_span));

				color.setHsb(ofMap(u, u_start, u_start + 360, 0, 255), 255, 255);
				ofColor face_color = ofColor(color, 128);
				ofColor line_color = color;

				face.addColor(face_color);
				face.addColor(face_color);
				face.addColor(face_color);
				face.addColor(face_color);

				line.addColor(line_color);
				line.addColor(line_color);
				line.addColor(line_color);
				line.addColor(line_color);

				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3);
				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

				line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 4);
				line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 3);
			}

			next_u += u_span;
			flag = !flag;
		}
	}

	face.drawFaces();
	line.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}