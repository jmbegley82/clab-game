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
#include "Types.h"
#include "Atom.h"
#include "Node.h"
#include "Integer.h"
#include "Float.h"
#include "String.h"
//#include "TestMachine.h"
#include "Video.h"
#include "Manager.h"
#include "Notype.h"
#include "Time.h"
#include "Clock.h"

//using jmb::common::Atom;
using jmb::common::Node;
//using jmb::common::Integer;
//using jmb::common::Float;
//using jmb::common::String;
//using jmb::common::TestMachine;
using jmb::common::Video;
using jmb::common::Manager;
//using jmb::common::Notype;
//using jmb::common::GetTimeInMsecAsDouble;
using jmb::common::Clock;
using jmb::common::Types::AddMapping;
using jmb::common::ClabInit;
using jmb::common::ClabGameInit;
using std::cout;
using std::endl;

void test0() {
	cout << ":::Version Variable Test - Clab:::" << endl;
	cout << "Clab reports version string:  " << jmb::common::ClabVersionString() << endl;
	cout << "Clab reports major version:   " << jmb::common::ClabVersionMajor() << endl;
	cout << "Clab reports minor version:   " << jmb::common::ClabVersionMinor() << endl;
	cout << "Linked using Clab major version:   " << CLAB_VERSION_MAJOR << endl;
	cout << "Linked using Clab minor version:   " << CLAB_VERSION_MINOR << endl;
	cout << endl;
}

void test1() {
	cout << ":::Version Variable Test - Clab-game:::" << endl;
	cout << "Clab-game reports version string:  " << jmb::common::ClabGameVersionString() << endl;
	cout << "Clab-game reports major version:   " << jmb::common::ClabGameVersionMajor() << endl;
	cout << "Clab-game reports minor version:   " << jmb::common::ClabGameVersionMinor() << endl;
	cout << "Linked using Clab-game major version:   " << CLAB_GAME_VERSION_MAJOR << endl;
	cout << "Linked using Clab-game minor version:   " << CLAB_GAME_VERSION_MINOR << endl;
	cout << endl;
}
void test9() {
	cout << ":::Test 9 from outer space:::" << endl;
	
	Manager root("root");
	//root.Command("Video VideoMgr");
	//root.Command("Event EventMgr");
	Video* v1 = (Video*)root.Dereference("VideoMgr");
	assert(v1 != NULL);
	cout << "VideoMgr reports a value of:  " << v1->GetValueAsStdString() << endl;
	root.Command("");
	root.Tick(0);
	root.Command("/VideoMgr/windowPosX=200");
	root.Command("");
	root.Tick(0);
	root.Tick(0);
	Clock clk;
	double time = clk.GetTime();
	double target = time + 100;
	double t_slice = 1000 / 120;
	double currentMsec = time;
	double prevMsec = currentMsec - t_slice;
	while(clk.GetTime() < target) {
		double delta = clk.GetTime() - prevMsec;
		while(delta < t_slice) {
			cout << "Debug main:  frame limiting..." << endl;
			jmb::common::SleepMsec(t_slice - delta);
			delta = clk.GetTime() - prevMsec;
		}
		root.Tick(delta);
		//root.Command("");
		cout << "Debug main:  " << clk.GetTime() << " " << delta << endl;
		prevMsec = currentMsec;
		jmb::common::SleepMsec(t_slice - (clk.GetTime() - prevMsec));
		currentMsec = clk.GetTime();
	}

	cout << endl << endl;
}

void testX() {
	cout << ":::Hypothetical situations:::" <<endl;
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
	cout << "The test begins...  now." << endl;
	ClabInit();
	ClabGameInit();
	cout << endl;

	test0();
	test1();
	test9();
	return 0;
}
