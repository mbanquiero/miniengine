#pragma once

#include "resource.h"
#include "Example.h"
#include <graphics\RenderEngine.h>


#define MAX_EXAMPLES 200

void add_example(IExample * example);
void set_example(IExample * example);

extern CRenderEngine _engine;
