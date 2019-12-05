/*
	This file is part of cpp-ethereum.

	cpp-ethereum is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	cpp-ethereum is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/
/** @file Interface.cpp
 * @author Gav Wood <i@gavwood.com>
 * @date 2014
 */

#include "Interface.h"

#include <cpp-ethereum/libdevcore/Log.h>
#include <cpp-ethereum/libp2p/All.h>
#include "WhisperHost.h"
using namespace std;
using namespace dev;
using namespace dev::p2p;
using namespace dev::shh;

Interface::~Interface()
{
}