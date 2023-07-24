#ifndef MAIN_H
#define MAIN_H

#include "Arduino.h"
#include <string.h>
#include "../config.h"
#include "APP_Interrupts.h"
#include "Commands.h"
#include "CommandCallbacks.h"
#include "Communication.h"
#include "Regulation.h"
#include "Timers.h"
#include "TimingUtils.h"
#include "StateMachine.h"

void halt( void );

#endif