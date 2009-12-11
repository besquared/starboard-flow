/*
 *  Sequence.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Sequence.h"

/*
 * SELECT COUNT(*)
 * WHERE date > 20091019
 * CLUSTER BY user_id
 * SEQUENCE BY time ASCENDING
 * SEQUENCE GROUP BY x1.product (?)
 * CUBOID BY SUBSTRING(W, X) WITH
 *  W at name
 *  X at name
 *  Y at name
 *  Z at name
 * LEFT-MAXIMILITY (w1, x1) WITH
 *  w1.name = 'home' AND
 *  x1.name = 'product' AND
 *
 * sequence->clusters->push_back("user_id")
 * sequence->conditions->push_back("date", Condition::GT, "20091019")
 * sequence->aggregations->push_back("*", Aggregate::COUNT)
 *
 * sequence->push_back("W", "w1", "name", {'name' => 'home'})
 * sequence->push_back("X", "x1", "name", {'name' => 'product'})
 *
 * How we process this query
 *
 * Step 1
 *  materialize table for W (user_id | name => 'home', date > 20091019)
 *  materialize table for X (user_id | name => 'product', date > 20091019)
 *
 *  W (home)
 *  [u1], [2, 4, 6], [W-home, W-home, W-home]
 *  [u2], [7, 10, 12], [W-home, W-home, W-home]
 *
 *  X (product)
 *  [u1, red balloon], [1], [X-product]
 *  [u1, green balloon], [3], [X-product]
 *  [u2, blue balloon], [8], [X-product]
 *
 * Step 2
 *  Inner join W and X by the cluster and sequence group by dimensions by
 *   merging the lists of records and patterns simultaneously
 *
 *  W-X (home-product)
 *  [u1, red balloon], [1, 2, 4, 6], [X-product, W-home, W-home, W-home]
 *  [u1, green balloon], [2, 3, 4, 6], [W-home, X-product, W-home, W-home]
 *  [u2, blue balloon], [7, 8, 10, 12], [W-home, X-product, W-home, W-home]
 *
 * Step 3
 *  Scan the sequences in the list for the pattern (W, X)
 *    for each successful match (using some matching rule) we add
 *    that sequence of records to a new list, (left-maximality shown)
 *
 * [green balloon], [[2, 3], ...]
 * [blue balloon], [[7, 8], ...]
 */