/*
 *  Cel.h
 *  08/02/2019
 *  jmb
 */

#ifndef CEL_H
#define CEL_H

#include "Atom.h"
#include "Node.h"
#include "ShadowInteger.h"

namespace jmb {
	
	namespace common {
	
		class Cel : public Node {
		public:
			Cel();
			Cel(std::string const& name);
			Cel(const Atom* atm);
			virtual ~Cel();
			static Atom* CtorWrapper(std::string name);
			static const char type;
			//virtual Atom* Dereference(std::string const& name);
                        virtual int Command(std::string const& cmd);
                        virtual std::string GetValueAsStdString();
			//virtual int AddChild(Atom* atm);
			//virtual int DelChild(Atom* atm);
			//virtual int DelChild(std::string const& name);
			//virtual int FreeChild(Atom* atm);
			//virtual int OperatorEqu(Atom* atm);
			//virtual void* GetRawData();
			virtual void Tick(int time);
		protected:
			virtual int _Procedure();
			//virtual int _Declarate(std::string const& declarator,
			//			std::string const& subject);
			virtual Atom* _Interpret(Atom* atm);
			//unsigned int _GetChildIndex(std::string const& name);
			//unsigned int _GetChildIndex(Atom* atm);
			//Atom* _GetChild(std::string const& name);
			//void _DeleteByIndex(unsigned int idx);
			//void _MakeContiguous();
			//void _Purge();
			//Atom* _children[MAXOBJS];
			//int _childCount;
			//bool _mapThrough;
		private:
                        void* ReadAtom(const Atom* atm);
                        void _Init();
                        void* _img;  //SDL_Surface*

			ShadowInteger* _imgW_SI;
			ShadowInteger* _imgH_SI;

			int _imgW;
			int _imgH;
		};
	
	}

}

#endif //CEL_H
