/*
 *  SubwayFixture.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "SubwayFixture.h"

SubwayFixture::SubwayFixture(const string& path) : Fixture::Fixture(path) {
	this->LoadDimensions();
	this->LoadMeasures();
	this->LoadFragments();
}

SubwayFixture::~SubwayFixture() {
	vector<string> dimensions = this->GetDimensions();
	
	for(size_t i = 0; i < dimensions.size(); i++) {
		Dimension database(this->path, dimensions[i]);
		filesystem::remove(filesystem::path(database.Path()));
	}
	
	ShellFragment fragment(this->path);
	filesystem::remove(filesystem::path(fragment.Path()));
}

vector<string> SubwayFixture::GetDimensions() {
	vector<string> results;
	results.push_back("name");
	results.push_back("fare-group");
	results.push_back("card-id");
	results.push_back("day");
	results.push_back("station");
	results.push_back("district");
	results.push_back("action");
	return results;
}

vector< vector<string> > SubwayFixture::GetData() {
	vector<string> row;
	vector< vector<string> > results;
	
	row.push_back("swipe");
	row.push_back("regular");
	row.push_back("00000001");
	row.push_back("20091210");
	row.push_back("montgomery");
	row.push_back("financial");
	row.push_back("in");
	
	results.push_back(row);
	row.clear();
	
	row.push_back("swipe");
	row.push_back("regular");
	row.push_back("00000001");
	row.push_back("20091210");
	row.push_back("16th street");
	row.push_back("mission");
	row.push_back("out");
	
	results.push_back(row);
	row.clear();
	
	row.push_back("swipe");
	row.push_back("regular");
	row.push_back("00000001");
	row.push_back("20091210");
	row.push_back("16th street");
	row.push_back("mission");
	row.push_back("in");
	
	results.push_back(row);
	row.clear();
	
	row.push_back("swipe");
	row.push_back("regular");
	row.push_back("00000001");
	row.push_back("20091210");
	row.push_back("montgomery");
	row.push_back("financial");
	row.push_back("out");
	
	results.push_back(row);
	row.clear();
	
	row.push_back("swipe");
	row.push_back("senior");
	row.push_back("00000002");
	row.push_back("20091210");
	row.push_back("montgomery");
	row.push_back("financial");
	row.push_back("in");	
	
	results.push_back(row);
	row.clear();
	
	row.push_back("swipe");
	row.push_back("senior");
	row.push_back("00000002");
	row.push_back("20091210");
	row.push_back("16th street");
	row.push_back("mission");
	row.push_back("out");
	
	results.push_back(row);
	row.clear();
	
	return results;
}

void SubwayFixture::LoadDimensions() {
	Dimensions database(this->path);
	
	vector<string> dimensions = this->GetDimensions();
	vector< vector<string> > data = this->GetData();
	
	for(size_t row = 0; row < data.size(); row++) {
		map<string, string> datum;
		for(size_t column = 0; column < data[row].size(); column++) {
			datum[dimensions[column]] = data[row][column];
		}
		database.Insert(row + 1, datum);
	}
}

void SubwayFixture::LoadMeasures() {
	
}

void SubwayFixture::LoadFragments() {
	ShellFragments database(this->path);
	
	vector<string> dimensions = this->GetDimensions();
	vector< vector<string> > data = this->GetData();
	
	for(size_t row = 0; row < data.size(); row++) {
		map<string, string> datum;
		for(size_t column = 0; column < data[row].size(); column++) {
			datum[dimensions[column]] = data[row][column];
		}
		database.Insert(row + 1, datum);
	}	
}
