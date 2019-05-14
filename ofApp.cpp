﻿#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(3);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	auto radius = 20;
	auto span = 120;
	auto threshold = 120;

	vector<glm::vec2> locations;
	for (auto x = span * 0.5; x < ofGetWidth(); x += span) {

		for (auto y = span * 0.5; y < ofGetHeight(); y += span) {

			auto location = glm::vec2(
				x + ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -span * 0.5 + radius, span * 0.5 - radius),
				y + ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -span * 0.5 + radius, span * 0.5 - radius));
			locations.push_back(location);
		}
	}

	for (auto location : locations) {

		for (auto other : locations) {

			if (location == other) { continue; }

			auto distance = glm::distance(location, other);
			if (distance < threshold) {

				auto direction_rad = std::atan2(other.y - location.y, other.x - location.x);
				auto direction = direction_rad * RAD_TO_DEG;
				auto width = ofMap(distance, 0, threshold, 360, 0);

				ofNoFill();
				ofBeginShape();
				for (auto deg = direction - width * 0.5; deg <= direction + width * 0.5; deg++) {

					ofVertex(location.x + radius * cos(deg * DEG_TO_RAD), location.y + radius * sin(deg * DEG_TO_RAD));
				}
				ofEndShape();

				ofDrawLine(location + glm::vec2(radius * cos(direction * DEG_TO_RAD), radius * sin(direction * DEG_TO_RAD)), 
					other + glm::vec2(radius * cos((180 + direction) * DEG_TO_RAD), radius * sin((180 + direction) * DEG_TO_RAD)));
			}
		}

		ofFill();
		ofDrawCircle(location, radius * 0.65);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}