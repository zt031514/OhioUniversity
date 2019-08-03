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
static const char *ng0 = "C:/Users/aaa/Desktop/Projects/PuttingItAllTogether/oneBitALU.v";
static unsigned int ng1[] = {0U, 0U};
static unsigned int ng2[] = {1U, 0U};
static unsigned int ng3[] = {2U, 0U};
static unsigned int ng4[] = {3U, 0U};



static void Always_43_0(char *t0)
{
    char t9[8];
    char t43[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    int t6;
    char *t7;
    char *t8;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    char *t24;
    char *t25;
    char *t26;
    char *t27;
    char *t28;
    char *t29;
    unsigned int t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    int t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    char *t42;

LAB0:    t1 = (t0 + 4608U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(43, ng0);
    t2 = (t0 + 4928);
    *((int *)t2) = 1;
    t3 = (t0 + 4640);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(44, ng0);

LAB5:    xsi_set_current_line(48, ng0);
    t4 = (t0 + 1528U);
    t5 = *((char **)t4);

LAB6:    t4 = ((char*)((ng1)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 1, t4, 1);
    if (t6 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng2)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 1, t2, 1);
    if (t6 == 1)
        goto LAB9;

LAB10:
LAB11:    xsi_set_current_line(60, ng0);
    t2 = (t0 + 1688U);
    t3 = *((char **)t2);

LAB20:    t2 = ((char*)((ng1)));
    t6 = xsi_vlog_unsigned_case_compare(t3, 1, t2, 1);
    if (t6 == 1)
        goto LAB21;

LAB22:    t2 = ((char*)((ng2)));
    t6 = xsi_vlog_unsigned_case_compare(t3, 1, t2, 1);
    if (t6 == 1)
        goto LAB23;

LAB24:
LAB25:    xsi_set_current_line(72, ng0);
    t2 = (t0 + 2888);
    t4 = (t2 + 56U);
    t7 = *((char **)t4);
    t8 = (t0 + 3048);
    t15 = (t8 + 56U);
    t24 = *((char **)t15);
    t10 = *((unsigned int *)t7);
    t11 = *((unsigned int *)t24);
    t12 = (t10 & t11);
    *((unsigned int *)t9) = t12;
    t25 = (t7 + 4);
    t26 = (t24 + 4);
    t27 = (t9 + 4);
    t13 = *((unsigned int *)t25);
    t14 = *((unsigned int *)t26);
    t16 = (t13 | t14);
    *((unsigned int *)t27) = t16;
    t17 = *((unsigned int *)t27);
    t18 = (t17 != 0);
    if (t18 == 1)
        goto LAB34;

LAB35:
LAB36:    t42 = (t0 + 2408);
    xsi_vlogvar_assign_value(t42, t9, 0, 0, 1);
    xsi_set_current_line(75, ng0);
    t2 = (t0 + 2888);
    t4 = (t2 + 56U);
    t7 = *((char **)t4);
    t8 = (t0 + 3048);
    t15 = (t8 + 56U);
    t24 = *((char **)t15);
    t10 = *((unsigned int *)t7);
    t11 = *((unsigned int *)t24);
    t12 = (t10 | t11);
    *((unsigned int *)t9) = t12;
    t25 = (t7 + 4);
    t26 = (t24 + 4);
    t27 = (t9 + 4);
    t13 = *((unsigned int *)t25);
    t14 = *((unsigned int *)t26);
    t16 = (t13 | t14);
    *((unsigned int *)t27) = t16;
    t17 = *((unsigned int *)t27);
    t18 = (t17 != 0);
    if (t18 == 1)
        goto LAB37;

LAB38:
LAB39:    t42 = (t0 + 2568);
    xsi_vlogvar_assign_value(t42, t9, 0, 0, 1);
    xsi_set_current_line(80, ng0);
    t2 = (t0 + 2888);
    t4 = (t2 + 56U);
    t7 = *((char **)t4);
    t8 = (t0 + 3048);
    t15 = (t8 + 56U);
    t24 = *((char **)t15);
    memset(t9, 0, 8);
    xsi_vlog_unsigned_add(t9, 2, t7, 1, t24, 1);
    t25 = (t0 + 1368U);
    t26 = *((char **)t25);
    memset(t43, 0, 8);
    xsi_vlog_unsigned_add(t43, 2, t9, 2, t26, 1);
    t25 = (t0 + 3208);
    xsi_vlogvar_assign_value(t25, t43, 0, 0, 2);
    xsi_set_current_line(83, ng0);
    t2 = (t0 + 3208);
    t4 = (t2 + 56U);
    t7 = *((char **)t4);
    memset(t9, 0, 8);
    t8 = (t9 + 4);
    t15 = (t7 + 4);
    t10 = *((unsigned int *)t7);
    t11 = (t10 >> 0);
    t12 = (t11 & 1);
    *((unsigned int *)t9) = t12;
    t13 = *((unsigned int *)t15);
    t14 = (t13 >> 0);
    t16 = (t14 & 1);
    *((unsigned int *)t8) = t16;
    t24 = (t0 + 2728);
    xsi_vlogvar_assign_value(t24, t9, 0, 0, 1);
    xsi_set_current_line(84, ng0);
    t2 = (t0 + 3208);
    t4 = (t2 + 56U);
    t7 = *((char **)t4);
    memset(t9, 0, 8);
    t8 = (t9 + 4);
    t15 = (t7 + 4);
    t10 = *((unsigned int *)t7);
    t11 = (t10 >> 1);
    t12 = (t11 & 1);
    *((unsigned int *)t9) = t12;
    t13 = *((unsigned int *)t15);
    t14 = (t13 >> 1);
    t16 = (t14 & 1);
    *((unsigned int *)t8) = t16;
    t24 = (t0 + 3528);
    xsi_vlogvar_assign_value(t24, t9, 0, 0, 1);
    xsi_set_current_line(87, ng0);
    t2 = (t0 + 2728);
    t4 = (t2 + 56U);
    t7 = *((char **)t4);
    t8 = (t0 + 3688);
    xsi_vlogvar_assign_value(t8, t7, 0, 0, 1);
    xsi_set_current_line(90, ng0);
    t2 = (t0 + 2008U);
    t4 = *((char **)t2);

LAB40:    t2 = ((char*)((ng1)));
    t6 = xsi_vlog_unsigned_case_compare(t4, 2, t2, 2);
    if (t6 == 1)
        goto LAB41;

LAB42:    t2 = ((char*)((ng2)));
    t6 = xsi_vlog_unsigned_case_compare(t4, 2, t2, 2);
    if (t6 == 1)
        goto LAB43;

LAB44:    t2 = ((char*)((ng3)));
    t6 = xsi_vlog_unsigned_case_compare(t4, 2, t2, 2);
    if (t6 == 1)
        goto LAB45;

LAB46:    t2 = ((char*)((ng4)));
    t6 = xsi_vlog_unsigned_case_compare(t4, 2, t2, 2);
    if (t6 == 1)
        goto LAB47;

LAB48:
LAB49:    goto LAB2;

LAB7:    xsi_set_current_line(50, ng0);

LAB12:    xsi_set_current_line(51, ng0);
    t7 = (t0 + 1048U);
    t8 = *((char **)t7);
    t7 = (t0 + 2888);
    xsi_vlogvar_assign_value(t7, t8, 0, 0, 1);
    goto LAB11;

LAB9:    xsi_set_current_line(54, ng0);

LAB13:    xsi_set_current_line(55, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    memset(t9, 0, 8);
    t3 = (t4 + 4);
    t10 = *((unsigned int *)t3);
    t11 = (~(t10));
    t12 = *((unsigned int *)t4);
    t13 = (t12 & t11);
    t14 = (t13 & 1U);
    if (t14 != 0)
        goto LAB17;

LAB15:    if (*((unsigned int *)t3) == 0)
        goto LAB14;

LAB16:    t7 = (t9 + 4);
    *((unsigned int *)t9) = 1;
    *((unsigned int *)t7) = 1;

LAB17:    t8 = (t9 + 4);
    t15 = (t4 + 4);
    t16 = *((unsigned int *)t4);
    t17 = (~(t16));
    *((unsigned int *)t9) = t17;
    *((unsigned int *)t8) = 0;
    if (*((unsigned int *)t15) != 0)
        goto LAB19;

LAB18:    t22 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t22 & 1U);
    t23 = *((unsigned int *)t8);
    *((unsigned int *)t8) = (t23 & 1U);
    t24 = (t0 + 2888);
    xsi_vlogvar_assign_value(t24, t9, 0, 0, 1);
    goto LAB11;

LAB14:    *((unsigned int *)t9) = 1;
    goto LAB17;

LAB19:    t18 = *((unsigned int *)t9);
    t19 = *((unsigned int *)t15);
    *((unsigned int *)t9) = (t18 | t19);
    t20 = *((unsigned int *)t8);
    t21 = *((unsigned int *)t15);
    *((unsigned int *)t8) = (t20 | t21);
    goto LAB18;

LAB21:    xsi_set_current_line(62, ng0);

LAB26:    xsi_set_current_line(63, ng0);
    t4 = (t0 + 1208U);
    t7 = *((char **)t4);
    t4 = (t0 + 3048);
    xsi_vlogvar_assign_value(t4, t7, 0, 0, 1);
    goto LAB25;

LAB23:    xsi_set_current_line(66, ng0);

LAB27:    xsi_set_current_line(67, ng0);
    t4 = (t0 + 1208U);
    t7 = *((char **)t4);
    memset(t9, 0, 8);
    t4 = (t7 + 4);
    t10 = *((unsigned int *)t4);
    t11 = (~(t10));
    t12 = *((unsigned int *)t7);
    t13 = (t12 & t11);
    t14 = (t13 & 1U);
    if (t14 != 0)
        goto LAB31;

LAB29:    if (*((unsigned int *)t4) == 0)
        goto LAB28;

LAB30:    t8 = (t9 + 4);
    *((unsigned int *)t9) = 1;
    *((unsigned int *)t8) = 1;

LAB31:    t15 = (t9 + 4);
    t24 = (t7 + 4);
    t16 = *((unsigned int *)t7);
    t17 = (~(t16));
    *((unsigned int *)t9) = t17;
    *((unsigned int *)t15) = 0;
    if (*((unsigned int *)t24) != 0)
        goto LAB33;

LAB32:    t22 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t22 & 1U);
    t23 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t23 & 1U);
    t25 = (t0 + 3048);
    xsi_vlogvar_assign_value(t25, t9, 0, 0, 1);
    goto LAB25;

LAB28:    *((unsigned int *)t9) = 1;
    goto LAB31;

LAB33:    t18 = *((unsigned int *)t9);
    t19 = *((unsigned int *)t24);
    *((unsigned int *)t9) = (t18 | t19);
    t20 = *((unsigned int *)t15);
    t21 = *((unsigned int *)t24);
    *((unsigned int *)t15) = (t20 | t21);
    goto LAB32;

LAB34:    t19 = *((unsigned int *)t9);
    t20 = *((unsigned int *)t27);
    *((unsigned int *)t9) = (t19 | t20);
    t28 = (t7 + 4);
    t29 = (t24 + 4);
    t21 = *((unsigned int *)t7);
    t22 = (~(t21));
    t23 = *((unsigned int *)t28);
    t30 = (~(t23));
    t31 = *((unsigned int *)t24);
    t32 = (~(t31));
    t33 = *((unsigned int *)t29);
    t34 = (~(t33));
    t6 = (t22 & t30);
    t35 = (t32 & t34);
    t36 = (~(t6));
    t37 = (~(t35));
    t38 = *((unsigned int *)t27);
    *((unsigned int *)t27) = (t38 & t36);
    t39 = *((unsigned int *)t27);
    *((unsigned int *)t27) = (t39 & t37);
    t40 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t40 & t36);
    t41 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t41 & t37);
    goto LAB36;

LAB37:    t19 = *((unsigned int *)t9);
    t20 = *((unsigned int *)t27);
    *((unsigned int *)t9) = (t19 | t20);
    t28 = (t7 + 4);
    t29 = (t24 + 4);
    t21 = *((unsigned int *)t28);
    t22 = (~(t21));
    t23 = *((unsigned int *)t7);
    t6 = (t23 & t22);
    t30 = *((unsigned int *)t29);
    t31 = (~(t30));
    t32 = *((unsigned int *)t24);
    t35 = (t32 & t31);
    t33 = (~(t6));
    t34 = (~(t35));
    t36 = *((unsigned int *)t27);
    *((unsigned int *)t27) = (t36 & t33);
    t37 = *((unsigned int *)t27);
    *((unsigned int *)t27) = (t37 & t34);
    goto LAB39;

LAB41:    xsi_set_current_line(91, ng0);

LAB50:    xsi_set_current_line(92, ng0);
    t7 = (t0 + 2408);
    t8 = (t7 + 56U);
    t15 = *((char **)t8);
    t24 = (t0 + 3368);
    xsi_vlogvar_assign_value(t24, t15, 0, 0, 1);
    goto LAB49;

LAB43:    xsi_set_current_line(95, ng0);

LAB51:    xsi_set_current_line(96, ng0);
    t7 = (t0 + 2568);
    t8 = (t7 + 56U);
    t15 = *((char **)t8);
    t24 = (t0 + 3368);
    xsi_vlogvar_assign_value(t24, t15, 0, 0, 1);
    goto LAB49;

LAB45:    xsi_set_current_line(99, ng0);

LAB52:    xsi_set_current_line(100, ng0);
    t7 = (t0 + 2728);
    t8 = (t7 + 56U);
    t15 = *((char **)t8);
    t24 = (t0 + 3368);
    xsi_vlogvar_assign_value(t24, t15, 0, 0, 1);
    goto LAB49;

LAB47:    xsi_set_current_line(103, ng0);

LAB53:    xsi_set_current_line(104, ng0);
    t7 = (t0 + 1848U);
    t8 = *((char **)t7);
    t7 = (t0 + 3368);
    xsi_vlogvar_assign_value(t7, t8, 0, 0, 1);
    goto LAB49;

}


extern void work_m_00000000001003765542_3038601299_init()
{
	static char *pe[] = {(void *)Always_43_0};
	xsi_register_didat("work_m_00000000001003765542_3038601299", "isim/thirtyTwoBitALU_isim_beh.exe.sim/work/m_00000000001003765542_3038601299.didat");
	xsi_register_executes(pe);
}
