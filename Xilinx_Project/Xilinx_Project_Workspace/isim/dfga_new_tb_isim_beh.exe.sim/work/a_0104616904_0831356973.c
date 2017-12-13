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
static const char *ng0 = "C:/Users/Kinaesthetic/Xilinx/dfg_to_fpga_repository-master/components/operators/logical/nor_n.vhd";
extern char *IEEE_P_2592010699;

char *ieee_p_2592010699_sub_1735675855_503743352(char *, char *, char *, char *, char *, char *);
char *ieee_p_2592010699_sub_1837678034_503743352(char *, char *, char *, char *);


static void work_a_0104616904_0831356973_p_0(char *t0)
{
    char t5[16];
    char t6[16];
    char *t1;
    char *t2;
    unsigned char t3;
    unsigned char t4;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    unsigned char t15;
    char *t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;

LAB0:    xsi_set_current_line(31, ng0);
    t1 = (t0 + 1032U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t4 = (t3 == (unsigned char)3);
    if (t4 != 0)
        goto LAB2;

LAB4:
LAB3:    t1 = (t0 + 3272);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(32, ng0);
    t1 = (t0 + 1192U);
    t7 = *((char **)t1);
    t1 = (t0 + 5564U);
    t8 = (t0 + 1352U);
    t9 = *((char **)t8);
    t8 = (t0 + 5580U);
    t10 = ieee_p_2592010699_sub_1735675855_503743352(IEEE_P_2592010699, t6, t7, t1, t9, t8);
    t11 = ieee_p_2592010699_sub_1837678034_503743352(IEEE_P_2592010699, t5, t10, t6);
    t12 = (t5 + 12U);
    t13 = *((unsigned int *)t12);
    t14 = (1U * t13);
    t15 = (32U != t14);
    if (t15 == 1)
        goto LAB5;

LAB6:    t16 = (t0 + 3352);
    t17 = (t16 + 56U);
    t18 = *((char **)t17);
    t19 = (t18 + 56U);
    t20 = *((char **)t19);
    memcpy(t20, t11, 32U);
    xsi_driver_first_trans_fast_port(t16);
    goto LAB3;

LAB5:    xsi_size_not_matching(32U, t14, 0);
    goto LAB6;

}


extern void work_a_0104616904_0831356973_init()
{
	static char *pe[] = {(void *)work_a_0104616904_0831356973_p_0};
	xsi_register_didat("work_a_0104616904_0831356973", "isim/dfga_new_tb_isim_beh.exe.sim/work/a_0104616904_0831356973.didat");
	xsi_register_executes(pe);
}
