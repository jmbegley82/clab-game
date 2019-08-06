/*
 *  Cel.cpp
 *  Test
 *
 *  Created by james on 7/14/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <cassert>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Log.h"
#include "StringManip.h"
#include "Cel.h"
#include "Node.h"
#include "Integer.h"
#include "Float.h"
#include "String.h"
//#include "TestMachine.h"
#include "ShadowInteger.h"
#include "Notype.h"

using std::string;

namespace jmb {
	
	namespace common {
		
		const char Cel::type = 0x7D;
		
		Cel::Cel() {
			Cel("");
			// why are the following lines necessary?
			_type = type;
			_img = NULL;
			_imgW = _imgH = 0;
		}
		
		Cel::Cel(string const& name) : Node(name) {
			_type = type;
			_img = NULL;
			_imgW = _imgH = 0;
			_Init();
		}

		Cel::Cel(const Atom* atm) : Node(atm) {
			assert(0); // this too seems unnecessary
			/*
			Cel(atm->identity);
			isEphemeral = true;
			char t = ((Atom*)atm)->GetType();
			if(t == Cel::type) {
				// only valid conversion is Cel to (Atom*)Cel
				Cel* nod = (Cel*)atm;
				for(int i=0; i<MAXOBJS; i++) {
					_children[i] = nod->_children[i];
				}
			}// else assert(t == Cel::type);
			*/
		}
		
		Cel::~Cel() {
			//*Log << "Cel::~Atom" << std::endl;
			if(!isEphemeral) _Purge();
		}

		Atom* Cel::CtorWrapper(string name) {
			return new Cel(name);
		}

		int Cel::Command(string const& cmd) {
			// TODO:  something meaningful
			return Node::Command(cmd);
		}

		string Cel::GetValueAsStdString() {
			//stringstream ss;
			//ss << "Cel " << identity << "@" << std::hex << this;
			//return ss.str();
			return string("Cel ") + identity + "@" + GetHexString(this)"
		}

		int Cel::_Procedure() {
			//Command("windowWidth -= 1");
			//_windowW--;
			//ShadowInteger* siWinW = (ShadowInteger*)Dereference("windowWidth");
			//*Log << "windowWidth deref test:  " << siWinW->GetValueAsStdString() << std::endl;
			return Node::_Procedure();
			//return 0;
		}

		Atom* Cel::_Interpret(Atom* atm) {
			//*Log << "Cel::_Interpret" << std::endl;
			//return Atom::_Interpret(atm);
			return new Cel(atm);
		}

		void* Cel::ReadAtom(const Atom* atm) {
			return (void*)this; //shrug
		}

		void Cel::Tick(int time) {
			// tick the ShadowIntegers
			for(int i=0; i<_childCount; i++) {
				_children[i]->Tick(time);
			}
			// observe updates
			if((_winX_SI)->wasUpdated ||
			   (_winY_SI)->wasUpdated ||
			   (_winW_SI)->wasUpdated ||
			   (_winH_SI)->wasUpdated) {
				*Log << "Debug:  " << _windowX << " " << _windowY << " " << _windowW << " " << _windowH << std::endl;
				// move window
				SDL_SetWindowPosition((SDL_Window*)_Window, _windowX, _windowY);
				// size window
				SDL_SetWindowSize((SDL_Window*)_Window, _windowW, _windowH);
				// unset wasUpdated for those
				(_winX_SI)->wasUpdated = false;
				(_winY_SI)->wasUpdated = false;
				(_winW_SI)->wasUpdated = false;
				(_winH_SI)->wasUpdated = false;
			}
			// (temporarily ignore buffer size updates)
			(_bufW_SI)->wasUpdated = false;
			(_bufH_SI)->wasUpdated = false;
			// observe window position changes
			SDL_GetWindowPosition((SDL_Window*)_Window, &_windowX, &_windowY);
			SDL_GetWindowSize((SDL_Window*)_Window, &_windowW, &_windowH);
			// draw buffer to screen
			SDL_UpdateWindowSurface((SDL_Window*)_Window);
			// blank buffer
		}

		void Cel::_Init() {
			_Window = _Renderer = _Buffer = NULL;
			*Log << "Cel::_Init:  starting" << std::endl;
			int ok = SDL_Init(SDL_INIT_VIDEO);// | SDL_INIT_AUDIO);
			if(ok != 0) {
				// error condition...
				*Log << "ERROR:  Could not initialize SDL:  " << SDL_GetError() <<std::endl;
			} else {
				*Log << "Cel::_Init:  SDL_Init succeeded" << std::endl;
				string id = GetValueAsStdString();
				_Window = (void*)SDL_CreateWindow(id.c_str(), _windowX, _windowY, _windowW, _windowH, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
				*Log << "Cel::_Init:  SDL_CreateWindow passed" << std::endl;

#if defined CLAB_PS3
				_Renderer = (void*)SDL_CreateRenderer((SDL_Window*)_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
#else
				_Renderer = (void*)SDL_CreateRenderer((SDL_Window*)_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
#endif //CLAB_*

				*Log << "Cel::_Init:  SDL_CreateRenderer passed" << std::endl;
				assert(_Window != NULL);
				*Log << "Cel::_Init:  _Window assertion passed" << std::endl;
				assert(_Renderer != NULL);
				*Log << "Cel::_Init:  _Renderer assertion passed" << std::endl;
				//TTF_Init();
				//ShadowInteger* siWinW = new ShadowInteger("windowWidth", &_windowW);
				//AddChild(siWinW);

				_winX_SI = new ShadowInteger("windowPosX", &_windowX);
				_winY_SI = new ShadowInteger("windowPosY", &_windowY);
				_winW_SI = new ShadowInteger("windowWidth", &_windowW);
				_winH_SI = new ShadowInteger("windowHeight", &_windowH);
				_bufW_SI = new ShadowInteger("bufferWidth", &_bufferW);
				_bufH_SI = new ShadowInteger("bufferHeight", &_bufferH);
				AddChild(_winX_SI);
				AddChild(_winY_SI);
				AddChild(_winW_SI);
				AddChild(_winH_SI);
				AddChild(_bufW_SI);
				AddChild(_bufH_SI);
			}
		}

	}
	
}
