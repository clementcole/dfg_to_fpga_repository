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
static const char *ng0 = "C:/Users/Kinaesthetic/Xilinx/dfg_to_fpga_repository-master/components/operators/logical/srl_n.vhd";
extern char *IEEE_P_2592010699;
extern char *IEEE_P_1242562249;

int ieee_p_1242562249_sub_1657552908_1035706684(char *, char *, char *);
char *ieee_p_2592010699_sub_3293060193_503743352(char *, char *, char *, char *, unsigned char );
char *ieee_p_2592010699_sub_393209765_503743352(char *, char *, char *, char *);


static void work_a_3771916207_0831356973_p_0(char *t0)
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
    unsigned int t10;
    char *t11;
    char *t12;
    int t13;
    char *t14;
    char *t15;
    char *t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;

LAB0:    xsi_set_current_line(34, ng0);
    t1 = (t0 + 1032U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t4 = (t3 == (unsigned char)3);
    if (t4 != 0)
        goto LAB2;

LAB4:
LAB3:    t1 = (t0 + 3112);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(35, ng0);
    t1 = (t0 + 1192U);
    t7 = *((char **)t1);
    t1 = (t0 + 5304U);
    t8 = ieee_p_2592010699_sub_3293060193_503743352(IEEE_P_2592010699, t6, t7, t1, (unsigned char)0);
    t9 = (t6 + 12U);
    t10 = *((unsigned int *)t9);
    t10 = (t10 * 1U);
    t11 = (t0 + 1352U);
    t12 = *((char **)t11);
    t11 = (t0 + 5320U);
    t13 = ieee_p_1242562249_sub_1657552908_1035706684(IEEE_P_1242562249, t12, t11);
    t14 = xsi_vhdl_bitvec_srl(t14, t8, t10, t13);
    t15 = ieee_p_2592010699_sub_393209765_503743352(IEEE_P_2592010699, t5, t14, t6);
    t16 = (t0 + 3192);
    t17 = (t16 + 56U);
    t18 = *((char **)t17);
    t19 = (t18 + 56U);
    t20 = *((char **)t19);
    memcpy(t20, t15, 32U);
    xsi_driver_first_trans_fast_port(t16);
    goto LAB3;

}


extern void work_a_3771916207_0831356973_init()
{
	static char *pe[] = {(void *)work_a_3771916207_0831356973_p_0};
	xsi_register_didat("work_a_3771916207_0831356973", "isim/dfga_new_tb_isim_beh.exe.sim/work/a_3771916207_0831356973.didat");
	xsi_register_executes(pe);
}
