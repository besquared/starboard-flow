/*
 *  Sequential.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Sequential.h"

Query::Sequential::Sequential() : Query::Base::Base() {}

void Query::Sequential::Measures(set<string>& results) {
	aggregates->measure_names(results);
}

void Query::Sequential::Dimensions(set<string>& results) {
  for(size_t i = 0; i < pattern.size(); i++) {
    results.insert(pattern[i]->name);
    
    shared_ptr<Condition::Base> condition;
    for(size_t j = 0; j < pattern[i]->conditions.size(); j++) {
      results.insert(pattern[i]->conditions[j]->column);
    }
  }
}

// Get a set of dims we're instantiating and their values
void Query::Sequential::Instantiate(map<string, string>& results) {
  for(size_t i = 0; i < this->conditions->size(); i++) {
		shared_ptr<Condition::Base> condition = this->conditions->at(i);
		
		if(condition->type == Condition::Base::EQ) {
			shared_ptr<Condition::Eq> equals = 
			static_pointer_cast<Condition::Eq>(condition);
			
			if(equals->value != "?") results[condition->column] = equals->value;			
		}
	}  
}

void Query::Sequential::InstantiatedValues(vector<string>& results) {
  for(size_t i = 0; i < this->conditions->size(); i++) {
		shared_ptr<Condition::Base> condition = this->conditions->at(i);
		
		if(condition->type == Condition::Base::EQ) {
			shared_ptr<Condition::Eq> equals = 
			static_pointer_cast<Condition::Eq>(condition);
			
			if(equals->value != "?") results.push_back(equals->value);
		}
	}  
}

// Get a set of dims we're inquiring and their conditions
void Query::Sequential::Inquire(set<string>& dimensions, Conditions& conditions) {
  dimensions.insert(cluster_by.begin(), cluster_by.end());
  dimensions.insert(sequence_group_by.begin(), sequence_group_by.end());

  for(size_t i = 0; i < this->conditions->size(); i++) {
		shared_ptr<Condition::Base> condition = this->conditions->at(i);
		
		if(condition->type == Condition::Base::EQ) {
			shared_ptr<Condition::Eq> equals = 
			static_pointer_cast<Condition::Eq>(condition);
			
			if(equals->value == "?") {
				conditions.push_back(condition);
				dimensions.insert(condition->column);
			}
		} else {
			conditions.push_back(condition);
			dimensions.insert(condition->column);
		}
	}  
}

// Get a list of the dims we're instantiating and inquiring
void Query::Sequential::Dimensions(vector<string>& instantiated, vector<string>& inquired) {
  for(size_t i = 0; i < this->conditions->size(); i++) {
		shared_ptr<Condition::Base> condition = this->conditions->at(i);
		
		if(condition->type == Condition::Base::EQ) {
			shared_ptr<Condition::Eq> equals = 
			static_pointer_cast<Condition::Eq>(condition);
			
			if(equals->value == "?") {
				inquired.push_back(condition->column);
			} else {
				instantiated.push_back(condition->column);
			}
		} else {
			inquired.push_back(condition->column);
		}
	}  
}
