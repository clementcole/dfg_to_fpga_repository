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
static const char *ng0 = "C:/Users/Kinaesthetic/Xilinx/dfg_to_fpga_repository-master/components/operators/arithmetic/integer/add_sub_n.vhd";
extern char *IEEE_P_2592010699;
extern char *IEEE_P_1242562249;

char *ieee_p_1242562249_sub_3273497107_1035706684(char *, char *, char *, char *, char *, char *);
unsigned char ieee_p_2592010699_sub_1744673427_503743352(char *, char *, unsigned int , unsigned int );


static void work_a_1087522490_0831356973_p_0(char *t0)
{
    char t3[16];
    char t14[16];
    char t27[16];
    char *t1;
    unsigned char t2;
    char *t4;
    char *t5;
    int t6;
    int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned char t11;
    char *t12;
    char *t13;
    char *t15;
    char *t16;
    char *t17;
    char *t18;
    int t19;
    int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned char t24;
    char *t25;
    char *t26;
    char *t28;
    char *t29;
    char *t30;
    char *t31;
    char *t32;
    char *t33;
    char *t34;
    char *t35;

LAB0:    xsi_set_current_line(36, ng0);
    t1 = (t0 + 992U);
    t2 = ieee_p_2592010699_sub_1744673427_503743352(IEEE_P_2592010699, t1, 0U, 0U);
    if (t2 != 0)
        goto LAB2;

LAB4:
LAB3:    t1 = (t0 + 3840);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(37, ng0);
    t4 = (t0 + 1192U);
    t5 = *((char **)t4);
    t6 = (32 - 1);
    t7 = (t6 - 31);
    t8 = (t7 * -1);
    t9 = (1U * t8);
    t10 = (0 + t9);
    t4 = (t5 + t10);
    t11 = *((unsigned char *)t4);
    t12 = (t0 + 1192U);
    t13 = *((char **)t12);
    t15 = ((IEEE_P_1242562249) + 3112);
    t16 = (t0 + 6716U);
    t12 = xsi_base_array_concat(t12, t14, t15, (char)99, t11, (char)97, t13, t16, (char)101);
    t17 = (t0 + 1352U);
    t18 = *((char **)t17);
    t19 = (32 - 1);
    t20 = (t19 - 31);
    t21 = (t20 * -1);
    t22 = (1U * t21);
    t23 = (0 + t22);
    t17 = (t18 + t23);
    t24 = *((unsigned char *)t17);
    t25 = (t0 + 1352U);
    t26 = *((char **)t25);
    t28 = ((IEEE_P_1242562249) + 3112);
    t29 = (t0 + 6732U);
    t25 = xsi_base_array_concat(t25, t27, t28, (char)99, t24, (char)97, t26, t29, (char)101);
    t30 = ieee_p_1242562249_sub_3273497107_1035706684(IEEE_P_1242562249, t3, t12, t14, t25, t27);
    t31 = (t0 + 3936);
    t32 = (t31 + 56U);
    t33 = *((char **)t32);
    t34 = (t33 + 56U);
    t35 = *((char **)t34);
    memcpy(t35, t30, 33U);
    xsi_driver_first_trans_fast(t31);
    goto LAB3;

}

static void work_a_1087522490_0831356973_p_1(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;

LAB0:    xsi_set_current_line(40, ng0);

LAB3:    t1 = (t0 + 1832U);
    t2 = *((char **)t1);
    t1 = (t0 + 4000);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memcpy(t6, t2, 33U);
    xsi_driver_first_trans_fast_port(t1);

LAB2:    t7 = (t0 + 3856);
    *((int *)t7) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}


extern void work_a_1087522490_0831356973_init()
{
	static char *pe[] = {(void *)work_a_1087522490_0831356973_p_0,(void *)work_a_1087522490_0831356973_p_1};
	xsi_register_didat("work_a_1087522490_0831356973", "isim/dfga_new_tb_isim_beh.exe.sim/work/a_1087522490_0831356973.didat");
	xsi_register_executes(pe);
}
