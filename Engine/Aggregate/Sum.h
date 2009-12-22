/*
 *  Sum.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/2/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _sum_included_
#define _sum_included_

#include "Common.h"

#include "Table.h"
#include "Engine/Table.h"
#include "Aggregate/Base.h"

namespace Flow {
	namespace Aggregate {
		class Sum : public Base {		
		public:
			Sum(const string& measure);
			void Apply(Table& base);		
		};
	}
}

#endif