#pragma once

#define REGISTER_EXAMPLE(exampleClass) \
	namespace ___##exampleClass { \
		struct StaticBlock { \
			StaticBlock(){ add_example(new (exampleClass)); } \
		}; \
		static StaticBlock __instanciador; \
	} 


class IExample
{
public:

	virtual const char * getName() = 0;
	virtual const char * getDescription() = 0;
	virtual void init() = 0;
	virtual void render(float elapsedTime) = 0;
	virtual void close() = 0;
};

