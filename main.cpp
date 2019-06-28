/* mbed Microcontroller Library
 * Copyright (c) 2018 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "stats_report.h"
#include "mbed_assert.h"

DigitalOut led1(LED1);

#define SLEEP_TIME                  500 // (msec)
#define PRINT_AFTER_N_LOOPS         20

void func6(int debugP, int param2)
{
	volatile int debug = debugP + param2;
	MBED_ASSERT(false);
	while (debug) ;
}

void func5(int debugP)
{
	func6(debugP, 777);
}

void func4(const char *str)
{
	printf("Hello! %s\n", str);
	func5(1);
}

void func3(float f)
{
	char buf[32];
	sprintf(buf, "%f", f);
	func4(buf);
}

void func2(int a, int b)
{
	func3((float)a / (float)b);
}

void func1()
{
	func2(1, 3);
}

// main() runs in its own thread in the OS
int main()
{
    SystemReport sys_state( SLEEP_TIME * PRINT_AFTER_N_LOOPS /* Loop delay time in ms */);

    int count = 0;
    while (true) {
        // Blink LED and wait 0.5 seconds
        led1 = !led1;
        wait_ms(SLEEP_TIME);

        if ((0 == count) || (PRINT_AFTER_N_LOOPS == count)) {
            func1();
            // Following the main thread wait, report on the current system status
            sys_state.report_state();
            count = 0;
        }
        ++count;
    }
}

