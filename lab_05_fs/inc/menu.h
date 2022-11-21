#ifndef _MENU_H
#define _MENU_H

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"
#include "struct_params.h"

#define BUFF_SIZE 8

void input_step_menu(int *step, int min, int max);

void print_menu(model_params *params);

#endif //_MENU_H
