/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "C:/Users/aaa/Desktop/Projects/PuttingItAllTogether/PCAdder.v";
static int ng1[] = {4, 0};

static void NetReassign_29_1(char *);


static void Always_27_0(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;

LAB0:    t1 = (t0 + 2368U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(27, ng0);
    t2 = (t0 + 2936);
    *((int *)t2) = 1;
    t3 = (t0 + 2400);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(28, ng0);

LAB5:    xsi_set_current_line(29, ng0);
    t4 = (t0 + 1448);
    xsi_set_assignedflag(t4);
    t5 = (t0 + 4384);
    *((int *)t5) = 1;
    NetReassign_29_1(t0);
    goto LAB2;

}

static void NetReassign_29_1(char *t0)
{
    char t5[8];
    char *t1;
    char *t2;
    unsigned int t3;
    char *t4;
    char *t6;
    char *t7;
    char *t8;
    char *t9;

LAB0:    t1 = (t0 + 2616U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(29, ng0);
    t3 = 0;
    t2 = (t0 + 1048U);
    t4 = *((char **)t2);
    t2 = ((char*)((ng1)));
    memset(t5, 0, 8);
    xsi_vlog_unsigned_add(t5, 32, t4, 32, t2, 32);
    t6 = (t0 + 4384);
    if (*((int *)t6) > 0)
        goto LAB4;

LAB5:    if (t3 > 0)
        goto LAB6;

LAB7:    t9 = (t0 + 2952);
    *((int *)t9) = 0;

LAB8:
LAB1:    return;
LAB4:    t7 = (t0 + 1448);
    xsi_vlogvar_assignassignvalue(t7, t5, 0, 0, 0, 32, ((int*)(t6)));
    t3 = 1;
    goto LAB5;

LAB6:    t8 = (t0 + 2952);
    *((int *)t8) = 1;
    goto LAB8;

}


extern void work_m_00000000001200445275_1463177816_init()
{
	static char *pe[] = {(void *)Always_27_0,(void *)NetReassign_29_1};
	xsi_register_didat("work_m_00000000001200445275_1463177816", "isim/cpu_tb_isim_beh.exe.sim/work/m_00000000001200445275_1463177816.didat");
	xsi_register_executes(pe);
}
