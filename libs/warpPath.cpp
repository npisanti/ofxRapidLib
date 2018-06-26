/**
 * @file warpPath.cpp
 * RapidLib
 * @author Michael Zbyszysnski
 * @date 13 Sep 2017
 *
 * @copyright Copyright © 2017 Goldsmiths. All rights reserved.
 */

#include "warpPath.h"

namespace rapidlib {

warpPath::warpPath() {};
warpPath::~warpPath() {};

void warpPath::add(int x, int y) {
    indices.insert(indices.begin(), std::make_pair(x, y));
};

} // end namespace
