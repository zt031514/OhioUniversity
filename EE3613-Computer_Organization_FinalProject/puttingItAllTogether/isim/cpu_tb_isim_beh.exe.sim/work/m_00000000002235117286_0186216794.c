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
static const char *ng0 = "C:/Users/aaa/Desktop/Projects/PuttingItAllTogether/SignExtension.v";
static int ng1[] = {16, 0};

static void NetReassign_30_1(char *);


static void Always_28_0(char *t0)
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

LAB2:    xsi_set_current_line(28, ng0);
    t2 = (t0 + 2936);
    *((int *)t2) = 1;
    t3 = (t0 + 2400);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(29, ng0);

LAB5:    xsi_set_current_line(30, ng0);
    t4 = (t0 + 1448);
    xsi_set_assignedflag(t4);
    t5 = (t0 + 4404);
    *((int *)t5) = 1;
    NetReassign_30_1(t0);
    goto LAB2;

}

static void NetReassign_30_1(char *t0)
{
    char t4[8];
    char t6[8];
    char t9[8];
    char *t1;
    char *t2;
    unsigned int t3;
    char *t5;
    char *t7;
    char *t8;
    char *t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;

LAB0:    t1 = (t0 + 2616U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(30, ng0);
    t3 = 0;
    t2 = (t0 + 1048U);
    t5 = *((char **)t2);
    t2 = ((char*)((ng1)));
    t7 = (t0 + 1048U);
    t8 = *((char **)t7);
    memset(t9, 0, 8);
    t7 = (t9 + 4);
    t10 = (t8 + 4);
    t11 = *((unsigned int *)t8);
    t12 = (t11 >> 15);
    t13 = (t12 & 1);
    *((unsigned int *)t9) = t13;
    t14 = *((unsigned int *)t10);
    t15 = (t14 >> 15);
    t16 = (t15 & 1);
    *((unsigned int *)t7) = t16;
    xsi_vlog_mul_concat(t6, 16, 1, t2, 1U, t9, 1);
    xsi_vlogtype_concat(t4, 32, 32, 2U, t6, 16, t5, 16);
    t17 = (t0 + 4404);
    if (*((int *)t17) > 0)
        goto LAB4;

LAB5:    if (t3 > 0)
        goto LAB6;

LAB7:    t20 = (t0 + 2952);
    *((int *)t20) = 0;

LAB8:
LAB1:    return;
LAB4:    t18 = (t0 + 1448);
    xsi_vlogvar_assignassignvalue(t18, t4, 0, 0, 0, 32, ((int*)(t17)));
    t3 = 1;
    goto LAB5;

LAB6:    t19 = (t0 + 2952);
    *((int *)t19) = 1;
    goto LAB8;

}


extern void work_m_00000000002235117286_0186216794_init()
{
	static char *pe[] = {(void *)Always_28_0,(void *)NetReassign_30_1};
	xsi_register_didat("work_m_00000000002235117286_0186216794", "isim/cpu_tb_isim_beh.exe.sim/work/m_00000000002235117286_0186216794.didat");
	xsi_register_executes(pe);
}
