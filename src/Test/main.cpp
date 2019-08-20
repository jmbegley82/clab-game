/*
 *  main.cpp
 *  Test
 *
 *  Created by james on 7/14/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */


#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include "Clab.h"
#include "Clab-game.h"
#include "Log.h"
#include "Types.h"
#include "Atom.h"
#include "Node.h"
//#include "Integer.h"
//#include "Float.h"
//#include "String.h"
//#include "TestMachine.h"
//#include "Video.h"
#include "Manager.h"
//#include "Notype.h"
#include "Time.h"
#include "Clock.h"

using jmb::common::Log;
using jmb::common::Atom;
using jmb::common::Node;
//using jmb::common::Integer;
//using jmb::common::Float;
//using jmb::common::String;
//using jmb::common::TestMachine;
//using jmb::common::Video;
using jmb::common::Manager;
//using jmb::common::Notype;
//using jmb::common::GetTimeInMsecAsDouble;
using jmb::common::Clock;
using jmb::common::Types::AddMapping;
using jmb::common::ClabInit;
using jmb::common::ClabGameInit;
using std::endl;

#undef INFINITE

void test0() {
	*Log << ":::Version Variable Test - Clab:::" << endl;
	*Log << "Clab reports version string:  " << jmb::common::ClabVersionString() << endl;
	*Log << "Clab reports major version:   " << jmb::common::ClabVersionMajor() << endl;
	*Log << "Clab reports minor version:   " << jmb::common::ClabVersionMinor() << endl;
	*Log << "Linked using Clab major version:   " << CLAB_VERSION_MAJOR << endl;
	*Log << "Linked using Clab minor version:   " << CLAB_VERSION_MINOR << endl;
	*Log << endl;
}

void test1() {
	*Log << ":::Version Variable Test - Clab-game:::" << endl;
	*Log << "Clab-game reports version string:  " << jmb::common::ClabGameVersionString() << endl;
	*Log << "Clab-game reports major version:   " << jmb::common::ClabGameVersionMajor() << endl;
	*Log << "Clab-game reports minor version:   " << jmb::common::ClabGameVersionMinor() << endl;
	*Log << "Linked using Clab-game major version:   " << CLAB_GAME_VERSION_MAJOR << endl;
	*Log << "Linked using Clab-game minor version:   " << CLAB_GAME_VERSION_MINOR << endl;
	*Log << endl;
}
void test9() {
	*Log << ":::Test 9 from outer space:::" << endl;
	
	Manager root("root");
	//root.Command("Video VideoMgr");
	//root.Command("Event EventMgr");
	Atom* v1 = root.Dereference("VideoMgr");
	assert(v1 != NULL);
	*Log << "VideoMgr reports a value of:  " << v1->GetValueAsStdString() << endl;
	root.Command("");
	root.Tick(0);
	root.Command("/VideoMgr/windowPosX=200");
	root.Command("");
	root.Tick(0);
	root.Tick(0);
	Clock clk;
	double time = clk.GetTime();
	double target = time + 100;  // it works, don't waste time on it
	double t_slice = 1000 / 120;
	double currentMsec = time;
	double prevMsec = currentMsec - t_slice;
#ifdef INFINITE
	while(1) {
#else
	while(clk.GetTime() < target) {
#endif //INFINITE
		double delta = clk.GetTime() - prevMsec;
		while(delta < t_slice) {
			*Log << "Debug main:  frame limiting..." << endl;
			jmb::common::SleepMsec(t_slice - delta);
			delta = clk.GetTime() - prevMsec;
		}
		root.Tick(delta);
		//root.Command("");
		*Log << "Debug main:  " << clk.GetTime() << " " << delta << endl;
		prevMsec = currentMsec;
		jmb::common::SleepMsec(t_slice - (clk.GetTime() - prevMsec));
		currentMsec = clk.GetTime();
	}

	*Log << endl << endl;
}

void testX() {
	*Log << ":::Hypothetical situations:::" <<endl;
	bool this_code_is_usable = false;
	assert(this_code_is_usable); // none of this works!
	// Hierarchy:
	// (root)\
	//       |-VideoMgr
	//       |-AudioMgr
	//       |-InputMgr
	//       |-Cache
	//       | |-Images
	//       | |-Sounds
	//       | \-Objects
	//       |-EventMgr
	//       | |-TxtCache
	//       | \-Timer
	//       \-Log
	//

	Node root("root");
	root.Command("Video VideoMgr");
	root.Command("Audio AudioMgr");
	root.Command("Input InputMgr");
	root.Command("Event EventMgr");
	root.Command("Node  Cache");
	root.Command("Logger Log");
	// ...
	
	root.Command("EventMgr := initScript: Data/script.txt");
/*
	while(!root.erase_me) {
		root.tick();
	}
*/
}

int main(int argc, char** argv) {
	ClabInit();
	ClabGameInit();
	*Log << "The test begins...  now." << endl << endl;

	test0();
	test1();
	test9();
	return 0;
}
