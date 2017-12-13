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
static const char *ng0 = "C:/Users/Kinaesthetic/Xilinx/dfg_to_fpga_repository-master/components/operators/arithmetic/integer/sra_n.vhd";
extern char *IEEE_P_1242562249;

int ieee_p_1242562249_sub_1657552908_1035706684(char *, char *, char *);
char *ieee_p_1242562249_sub_3064532541_1035706684(char *, char *, char *, char *, int );


static void work_a_2077739646_0831356973_p_0(char *t0)
{
    char t1[16];
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    int t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;

LAB0:    xsi_set_current_line(35, ng0);
    t2 = (t0 + 1192U);
    t3 = *((char **)t2);
    t2 = (t0 + 5388U);
    t4 = (t0 + 1352U);
    t5 = *((char **)t4);
    t4 = (t0 + 5404U);
    t6 = ieee_p_1242562249_sub_1657552908_1035706684(IEEE_P_1242562249, t5, t4);
    t7 = ieee_p_1242562249_sub_3064532541_1035706684(IEEE_P_1242562249, t1, t3, t2, t6);
    t8 = (t0 + 3192);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    t11 = (t10 + 56U);
    t12 = *((char **)t11);
    memcpy(t12, t7, 32U);
    xsi_driver_first_trans_fast_port(t8);
    t2 = (t0 + 3112);
    *((int *)t2) = 1;

LAB1:    return;
}


extern void work_a_2077739646_0831356973_init()
{
	static char *pe[] = {(void *)work_a_2077739646_0831356973_p_0};
	xsi_register_didat("work_a_2077739646_0831356973", "isim/dfga_new_tb_isim_beh.exe.sim/work/a_2077739646_0831356973.didat");
	xsi_register_executes(pe);
}
