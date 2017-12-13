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
extern char *STD_STANDARD;
extern char *IEEE_P_2592010699;
extern char *IEEE_P_1242562249;

char *ieee_p_1242562249_sub_1547198987_1035706684(char *, char *, char *, char *, char *, char *);
char *ieee_p_1242562249_sub_1547270861_1035706684(char *, char *, char *, char *, char *, char *);
int ieee_p_1242562249_sub_1657552908_1035706684(char *, char *, char *);
char *ieee_p_1242562249_sub_180853171_1035706684(char *, char *, int , int );
int ieee_p_1242562249_sub_2271993008_1035706684(char *, char *, char *);
char *ieee_p_1242562249_sub_2563015576_1035706684(char *, char *, int , int );
char *ieee_p_2592010699_sub_1837678034_503743352(char *, char *, char *, char *);
unsigned char ieee_p_2592010699_sub_2507238156_503743352(char *, unsigned char , unsigned char );


void work_p_2431924499_sub_419251499_4141849106(char *t0, char *t1, char *t2, unsigned int t3, unsigned int t4, char *t5, double t6, int64 t7, char *t8, unsigned int t9, unsigned int t10)
{
    char t11[488];
    char t12[24];
    char t18[8];
    char t24[8];
    char t30[8];
    char t36[8];
    int64 t13;
    int64 t14;
    char *t15;
    char *t16;
    char *t17;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t25;
    char *t26;
    char *t27;
    char *t28;
    char *t29;
    char *t31;
    char *t32;
    char *t33;
    char *t34;
    char *t35;
    char *t37;
    char *t38;
    char *t39;
    char *t40;
    char *t41;
    char *t42;
    int64 t43;
    unsigned char t44;
    unsigned int t46;
    unsigned char t47;
    unsigned char t48;
    unsigned char t49;
    unsigned char t50;
    unsigned char t51;
    double t52;
    double t53;
    double t54;
    int64 t55;
    int64 t56;
    int64 t57;

LAB0:    t13 = (0.50000000000000000 * 1000000000000LL);
    t14 = (t13 / t6);
    t15 = (t11 + 4U);
    t16 = ((STD_STANDARD) + 576);
    t17 = (t15 + 88U);
    *((char **)t17) = t16;
    t19 = (t15 + 56U);
    *((char **)t19) = t18;
    *((int64 *)t18) = t14;
    t20 = (t15 + 80U);
    *((unsigned int *)t20) = 8U;
    t21 = (t11 + 124U);
    t22 = ((STD_STANDARD) + 576);
    t23 = (t21 + 88U);
    *((char **)t23) = t22;
    t25 = (t21 + 56U);
    *((char **)t25) = t24;
    xsi_type_set_default_value(t22, t24, 0);
    t26 = (t21 + 80U);
    *((unsigned int *)t26) = 8U;
    t27 = (t11 + 244U);
    t28 = ((STD_STANDARD) + 472);
    t29 = (t27 + 88U);
    *((char **)t29) = t28;
    t31 = (t27 + 56U);
    *((char **)t31) = t30;
    *((double *)t30) = 0.00000000000000000;
    t32 = (t27 + 80U);
    *((unsigned int *)t32) = 8U;
    t33 = (t11 + 364U);
    t34 = ((STD_STANDARD) + 576);
    t35 = (t33 + 88U);
    *((char **)t35) = t34;
    t37 = (t33 + 56U);
    *((char **)t37) = t36;
    *((int *)t36) = 0;
    t38 = (t33 + 80U);
    *((unsigned int *)t38) = 8U;
    t39 = (t12 + 4U);
    *((double *)t39) = t6;
    t40 = (t12 + 12U);
    *((int64 *)t40) = t7;
    t41 = (t15 + 56U);
    t42 = *((char **)t41);
    t43 = *((int64 *)t42);
    t44 = (t43 != 0);
    if (t44 == 0)
        goto LAB2;

LAB3:    t46 = (0 + t3);
    t16 = (t5 + 56U);
    t17 = *((char **)t16);
    t19 = (t17 + 56U);
    t20 = *((char **)t19);
    *((unsigned char *)t20) = (unsigned char)2;
    xsi_driver_first_trans_delta(t5, t46, 1, 0LL);

LAB4:
LAB5:    t16 = (t8 + 40U);
    t17 = *((char **)t16);
    t16 = (t17 + t10);
    t47 = *((unsigned char *)t16);
    t48 = (t47 == (unsigned char)3);
    if (t48 == 1)
        goto LAB11;

LAB12:    t17 = (t8 + 40U);
    t19 = *((char **)t17);
    t17 = (t19 + t10);
    t49 = *((unsigned char *)t17);
    t50 = (t49 == (unsigned char)7);
    t44 = t50;

LAB13:    if (t44 != 0)
        goto LAB8;

LAB10:
LAB9:    t46 = (0 + t3);
    t16 = (t5 + 56U);
    t17 = *((char **)t16);
    t19 = (t17 + 56U);
    t20 = *((char **)t19);
    *((unsigned char *)t20) = (unsigned char)2;
    xsi_driver_first_trans_delta(t5, t46, 1, 0LL);
    t13 = (1 * 1000000000000LL);
    t16 = (t27 + 56U);
    t17 = *((char **)t16);
    t52 = *((double *)t17);
    t53 = (t52 + 1.0000000000000000);
    t54 = (t53 / t6);
    t14 = (t13 * t54);
    t16 = (t33 + 56U);
    t19 = *((char **)t16);
    t43 = *((int64 *)t19);
    t55 = (t14 - t43);
    t16 = (t15 + 56U);
    t20 = *((char **)t16);
    t56 = *((int64 *)t20);
    t57 = (t55 - t56);
    t16 = (t21 + 56U);
    t22 = *((char **)t16);
    t16 = (t22 + 0);
    *((int64 *)t16) = t57;
    t16 = (t27 + 56U);
    t17 = *((char **)t16);
    t52 = *((double *)t17);
    t53 = (t52 + 1.0000000000000000);
    t16 = (t27 + 56U);
    t19 = *((char **)t16);
    t16 = (t19 + 0);
    *((double *)t16) = t53;
    t16 = (t33 + 56U);
    t17 = *((char **)t16);
    t13 = *((int64 *)t17);
    t16 = (t15 + 56U);
    t19 = *((char **)t16);
    t14 = *((int64 *)t19);
    t43 = (t13 + t14);
    t16 = (t21 + 56U);
    t20 = *((char **)t16);
    t55 = *((int64 *)t20);
    t56 = (t43 + t55);
    t16 = (t33 + 56U);
    t22 = *((char **)t16);
    t16 = (t22 + 0);
    *((int64 *)t16) = t56;
    goto LAB4;

LAB2:    t41 = (t0 + 10568);
    xsi_report(t41, 66U, (unsigned char)3);
    goto LAB3;

LAB6:;
LAB7:
LAB1:    return;
LAB8:    t19 = (t8 + 40U);
    t20 = *((char **)t19);
    t19 = (t20 + t10);
    t51 = *((unsigned char *)t19);
    t46 = (0 + t3);
    t20 = (t5 + 56U);
    t22 = *((char **)t20);
    t23 = (t22 + 56U);
    t25 = *((char **)t23);
    *((unsigned char *)t25) = t51;
    xsi_driver_first_trans_delta(t5, t46, 1, 0LL);
    goto LAB9;

LAB11:    t44 = (unsigned char)1;
    goto LAB13;

}

char *work_p_2431924499_sub_4097533137_4141849106(char *t1, char *t2, char *t3, char *t4)
{
    char t5[128];
    char t6[24];
    char t11[16];
    char t27[16];
    char t28[16];
    char *t0;
    char *t7;
    unsigned int t8;
    int t9;
    unsigned int t10;
    char *t12;
    unsigned int t13;
    char *t14;
    char *t15;
    int t16;
    unsigned int t17;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    unsigned char t25;
    char *t26;
    char *t29;
    int t30;
    int t31;
    char *t32;
    char *t33;
    char *t34;
    char *t35;
    char *t36;
    unsigned int t37;

LAB0:    t7 = (t4 + 12U);
    t8 = *((unsigned int *)t7);
    t9 = (0 - t8);
    t10 = (t9 * -1);
    t10 = (t10 + 1);
    t10 = (t10 * 1U);
    t12 = (t4 + 12U);
    t13 = *((unsigned int *)t12);
    t14 = (t11 + 0U);
    t15 = (t14 + 0U);
    *((unsigned int *)t15) = t13;
    t15 = (t14 + 4U);
    *((int *)t15) = 0;
    t15 = (t14 + 8U);
    *((int *)t15) = -1;
    t16 = (0 - t13);
    t17 = (t16 * -1);
    t17 = (t17 + 1);
    t15 = (t14 + 12U);
    *((unsigned int *)t15) = t17;
    t15 = (t5 + 4U);
    t18 = ((IEEE_P_2592010699) + 4024);
    t19 = (t15 + 88U);
    *((char **)t19) = t18;
    t20 = (char *)alloca(t10);
    t21 = (t15 + 56U);
    *((char **)t21) = t20;
    xsi_type_set_default_value(t18, t20, t11);
    t22 = (t15 + 64U);
    *((char **)t22) = t11;
    t23 = (t15 + 80U);
    *((unsigned int *)t23) = t10;
    t24 = (t6 + 4U);
    t25 = (t3 != 0);
    if (t25 == 1)
        goto LAB3;

LAB2:    t26 = (t6 + 12U);
    *((char **)t26) = t4;
    t29 = ieee_p_2592010699_sub_1837678034_503743352(IEEE_P_2592010699, t28, t3, t4);
    t30 = ieee_p_1242562249_sub_1657552908_1035706684(IEEE_P_1242562249, t29, t28);
    t31 = (t30 + 1);
    t32 = (t4 + 12U);
    t17 = *((unsigned int *)t32);
    t33 = ieee_p_1242562249_sub_180853171_1035706684(IEEE_P_1242562249, t27, t31, ((t17)));
    t34 = (t15 + 56U);
    t35 = *((char **)t34);
    t34 = (t35 + 0);
    t36 = (t27 + 12U);
    t37 = *((unsigned int *)t36);
    t37 = (t37 * 1U);
    memcpy(t34, t33, t37);
    t7 = (t15 + 56U);
    t12 = *((char **)t7);
    t7 = (t11 + 12U);
    t8 = *((unsigned int *)t7);
    t8 = (t8 * 1U);
    t0 = xsi_get_transient_memory(t8);
    memcpy(t0, t12, t8);
    t14 = (t11 + 0U);
    t9 = *((int *)t14);
    t18 = (t11 + 4U);
    t16 = *((int *)t18);
    t19 = (t11 + 8U);
    t30 = *((int *)t19);
    t21 = (t2 + 0U);
    t22 = (t21 + 0U);
    *((int *)t22) = t9;
    t22 = (t21 + 4U);
    *((int *)t22) = t16;
    t22 = (t21 + 8U);
    *((int *)t22) = t30;
    t31 = (t16 - t9);
    t10 = (t31 * t30);
    t10 = (t10 + 1);
    t22 = (t21 + 12U);
    *((unsigned int *)t22) = t10;

LAB1:    return t0;
LAB3:    *((char **)t24) = t3;
    goto LAB2;

LAB4:;
}

char *work_p_2431924499_sub_3525837213_4141849106(char *t1, char *t2, char *t3, char *t4)
{
    char t5[128];
    char t6[24];
    char t12[16];
    char t38[16];
    char *t0;
    char *t7;
    unsigned int t8;
    int t9;
    int t10;
    unsigned int t11;
    char *t13;
    unsigned int t14;
    int t15;
    char *t16;
    char *t17;
    int t18;
    unsigned int t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    unsigned char t27;
    char *t28;
    int t29;
    char *t30;
    int t31;
    char *t32;
    int t33;
    char *t34;
    int t35;
    int t36;
    int t37;
    char *t39;
    int t40;
    char *t41;
    int t42;
    int t43;
    char *t44;
    int t45;
    unsigned int t46;
    unsigned int t47;
    char *t48;
    unsigned char t49;
    char *t50;
    char *t51;
    char *t52;
    int t53;
    int t54;
    int t55;
    unsigned int t56;
    int t57;
    int t58;
    char *t59;
    int t60;
    char *t61;
    int t62;
    unsigned int t63;
    unsigned int t64;
    char *t65;
    char *t66;
    unsigned int t67;

LAB0:    t7 = (t4 + 12U);
    t8 = *((unsigned int *)t7);
    t9 = (t8 * 8);
    t10 = (0 - t9);
    t11 = (t10 * -1);
    t11 = (t11 + 1);
    t11 = (t11 * 1U);
    t13 = (t4 + 12U);
    t14 = *((unsigned int *)t13);
    t15 = (t14 * 8);
    t16 = (t12 + 0U);
    t17 = (t16 + 0U);
    *((int *)t17) = t15;
    t17 = (t16 + 4U);
    *((int *)t17) = 0;
    t17 = (t16 + 8U);
    *((int *)t17) = -1;
    t18 = (0 - t15);
    t19 = (t18 * -1);
    t19 = (t19 + 1);
    t17 = (t16 + 12U);
    *((unsigned int *)t17) = t19;
    t17 = (t5 + 4U);
    t20 = ((IEEE_P_2592010699) + 4024);
    t21 = (t17 + 88U);
    *((char **)t21) = t20;
    t22 = (char *)alloca(t11);
    t23 = (t17 + 56U);
    *((char **)t23) = t22;
    xsi_type_set_default_value(t20, t22, t12);
    t24 = (t17 + 64U);
    *((char **)t24) = t12;
    t25 = (t17 + 80U);
    *((unsigned int *)t25) = t11;
    t26 = (t6 + 4U);
    t27 = (t3 != 0);
    if (t27 == 1)
        goto LAB3;

LAB2:    t28 = (t6 + 12U);
    *((char **)t28) = t4;
    t30 = (t4 + 0U);
    t31 = *((int *)t30);
    t32 = (t4 + 4U);
    t33 = *((int *)t32);
    t34 = (t4 + 8U);
    t35 = *((int *)t34);
    if (t31 > t33)
        goto LAB8;

LAB9:    if (t35 == -1)
        goto LAB13;

LAB14:    t29 = t33;

LAB10:    t36 = 1;
    t37 = t29;

LAB4:    if (t36 <= t37)
        goto LAB5;

LAB7:    t7 = (t17 + 56U);
    t13 = *((char **)t7);
    t7 = (t12 + 12U);
    t8 = *((unsigned int *)t7);
    t8 = (t8 * 1U);
    t0 = xsi_get_transient_memory(t8);
    memcpy(t0, t13, t8);
    t16 = (t12 + 0U);
    t9 = *((int *)t16);
    t20 = (t12 + 4U);
    t10 = *((int *)t20);
    t21 = (t12 + 8U);
    t15 = *((int *)t21);
    t23 = (t2 + 0U);
    t24 = (t23 + 0U);
    *((int *)t24) = t9;
    t24 = (t23 + 4U);
    *((int *)t24) = t10;
    t24 = (t23 + 8U);
    *((int *)t24) = t15;
    t18 = (t10 - t9);
    t11 = (t18 * t15);
    t11 = (t11 + 1);
    t24 = (t23 + 12U);
    *((unsigned int *)t24) = t11;

LAB1:    return t0;
LAB3:    *((char **)t26) = t3;
    goto LAB2;

LAB5:    t39 = (t4 + 0U);
    t40 = *((int *)t39);
    t41 = (t4 + 8U);
    t42 = *((int *)t41);
    t43 = (t36 - t40);
    t19 = (t43 * t42);
    t44 = (t4 + 4U);
    t45 = *((int *)t44);
    xsi_vhdl_check_range_of_index(t40, t45, t42, t36);
    t46 = (1U * t19);
    t47 = (0 + t46);
    t48 = (t3 + t47);
    t49 = *((unsigned char *)t48);
    t50 = ieee_p_1242562249_sub_180853171_1035706684(IEEE_P_1242562249, t38, ((int)(t49)), 8);
    t51 = (t17 + 56U);
    t52 = *((char **)t51);
    t51 = (t12 + 0U);
    t53 = *((int *)t51);
    t54 = (t36 * 8);
    t55 = (t54 - 1);
    t56 = (t53 - t55);
    t57 = (t36 - 1);
    t58 = (t57 * 8);
    t59 = (t12 + 4U);
    t60 = *((int *)t59);
    t61 = (t12 + 8U);
    t62 = *((int *)t61);
    xsi_vhdl_check_range_of_slice(t53, t60, t62, t55, t58, -1);
    t63 = (t56 * 1U);
    t64 = (0 + t63);
    t65 = (t52 + t64);
    t66 = (t38 + 12U);
    t67 = *((unsigned int *)t66);
    t67 = (t67 * 1U);
    memcpy(t65, t50, t67);

LAB6:    if (t36 == t37)
        goto LAB7;

LAB15:    t9 = (t36 + 1);
    t36 = t9;
    goto LAB4;

LAB8:    if (t35 == 1)
        goto LAB11;

LAB12:    t29 = t31;
    goto LAB10;

LAB11:    t29 = t33;
    goto LAB10;

LAB13:    t29 = t31;
    goto LAB10;

LAB16:;
}

char *work_p_2431924499_sub_2096353530_4141849106(char *t1, char *t2, char *t3, char *t4)
{
    char t5[152];
    char t6[24];
    char t23[16];
    char *t0;
    int t7;
    char *t8;
    int t9;
    char *t10;
    int t11;
    char *t12;
    int t13;
    int t14;
    char *t15;
    int t16;
    char *t17;
    int t18;
    char *t19;
    int t20;
    int t21;
    unsigned int t22;
    int t24;
    char *t25;
    int t26;
    char *t27;
    int t28;
    char *t29;
    int t30;
    int t31;
    char *t32;
    int t33;
    char *t34;
    int t35;
    char *t36;
    int t37;
    char *t38;
    char *t39;
    int t40;
    unsigned int t41;
    char *t42;
    char *t43;
    char *t44;
    char *t45;
    char *t46;
    char *t47;
    char *t48;
    char *t49;
    char *t50;
    char *t51;
    int t52;
    char *t53;
    unsigned int t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    char *t58;
    unsigned char t59;
    char *t60;
    int t61;
    char *t62;
    int t63;
    char *t64;
    int t65;
    char *t66;
    int t67;
    int t68;
    int t69;
    char *t70;
    int t71;
    char *t72;
    int t73;
    int t74;
    unsigned int t75;
    char *t76;
    int t77;
    unsigned int t78;
    unsigned int t79;
    char *t80;
    unsigned char t81;
    char *t82;
    char *t83;
    int t84;
    int t85;
    char *t86;
    int t87;
    char *t88;
    int t89;
    int t90;
    int t91;
    char *t92;
    int t93;
    char *t94;
    int t95;
    int t96;
    unsigned int t97;
    char *t98;
    int t99;
    unsigned int t100;
    unsigned int t101;
    char *t102;

LAB0:    t8 = (t4 + 0U);
    t9 = *((int *)t8);
    t10 = (t4 + 4U);
    t11 = *((int *)t10);
    t12 = (t4 + 8U);
    t13 = *((int *)t12);
    if (t9 > t11)
        goto LAB2;

LAB3:    if (t13 == -1)
        goto LAB7;

LAB8:    t7 = t11;

LAB4:    t15 = (t4 + 0U);
    t16 = *((int *)t15);
    t17 = (t4 + 4U);
    t18 = *((int *)t17);
    t19 = (t4 + 8U);
    t20 = *((int *)t19);
    if (t16 > t18)
        goto LAB9;

LAB10:    if (t20 == -1)
        goto LAB14;

LAB15:    t14 = t16;

LAB11:    t21 = (t14 - t7);
    t22 = (t21 * -1);
    t22 = (t22 + 1);
    t22 = (t22 * 1U);
    t25 = (t4 + 0U);
    t26 = *((int *)t25);
    t27 = (t4 + 4U);
    t28 = *((int *)t27);
    t29 = (t4 + 8U);
    t30 = *((int *)t29);
    if (t26 > t28)
        goto LAB16;

LAB17:    if (t30 == -1)
        goto LAB21;

LAB22:    t24 = t28;

LAB18:    t32 = (t4 + 0U);
    t33 = *((int *)t32);
    t34 = (t4 + 4U);
    t35 = *((int *)t34);
    t36 = (t4 + 8U);
    t37 = *((int *)t36);
    if (t33 > t35)
        goto LAB23;

LAB24:    if (t37 == -1)
        goto LAB28;

LAB29:    t31 = t33;

LAB25:    t38 = (t23 + 0U);
    t39 = (t38 + 0U);
    *((int *)t39) = t24;
    t39 = (t38 + 4U);
    *((int *)t39) = t31;
    t39 = (t38 + 8U);
    *((int *)t39) = -1;
    t40 = (t31 - t24);
    t41 = (t40 * -1);
    t41 = (t41 + 1);
    t39 = (t38 + 12U);
    *((unsigned int *)t39) = t41;
    t39 = (t5 + 4U);
    t42 = ((STD_STANDARD) + 1008);
    t43 = (t39 + 88U);
    *((char **)t43) = t42;
    t44 = xsi_get_memory(t22);
    t45 = (t39 + 56U);
    *((char **)t45) = t44;
    xsi_type_set_default_value(t42, t44, t23);
    t46 = (t39 + 64U);
    *((char **)t46) = t23;
    t47 = (t39 + 80U);
    *((unsigned int *)t47) = t22;
    t48 = (t39 + 136U);
    *((char **)t48) = t44;
    t49 = (t39 + 124U);
    *((int *)t49) = 0;
    t50 = (t39 + 128U);
    t51 = (t23 + 12U);
    t41 = *((unsigned int *)t51);
    t52 = (t41 - 1);
    *((int *)t50) = t52;
    t53 = (t39 + 120U);
    t55 = (t22 > 2147483644);
    if (t55 == 1)
        goto LAB30;

LAB31:    t56 = (t22 + 3);
    t57 = (t56 / 16);
    t54 = t57;

LAB32:    *((unsigned int *)t53) = t54;
    t58 = (t6 + 4U);
    t59 = (t3 != 0);
    if (t59 == 1)
        goto LAB34;

LAB33:    t60 = (t6 + 12U);
    *((char **)t60) = t4;
    t62 = (t4 + 0U);
    t63 = *((int *)t62);
    t64 = (t4 + 4U);
    t65 = *((int *)t64);
    t66 = (t4 + 8U);
    t67 = *((int *)t66);
    if (t63 > t65)
        goto LAB39;

LAB40:    if (t67 == -1)
        goto LAB44;

LAB45:    t61 = t65;

LAB41:    t68 = 1;
    t69 = t61;

LAB35:    if (t68 <= t69)
        goto LAB36;

LAB38:    t8 = (t39 + 56U);
    t10 = *((char **)t8);
    t8 = (t23 + 12U);
    t22 = *((unsigned int *)t8);
    t22 = (t22 * 1U);
    t0 = xsi_get_transient_memory(t22);
    memcpy(t0, t10, t22);
    t12 = (t23 + 0U);
    t7 = *((int *)t12);
    t15 = (t23 + 4U);
    t9 = *((int *)t15);
    t17 = (t23 + 8U);
    t11 = *((int *)t17);
    t19 = (t2 + 0U);
    t25 = (t19 + 0U);
    *((int *)t25) = t7;
    t25 = (t19 + 4U);
    *((int *)t25) = t9;
    t25 = (t19 + 8U);
    *((int *)t25) = t11;
    t13 = (t9 - t7);
    t41 = (t13 * t11);
    t41 = (t41 + 1);
    t25 = (t19 + 12U);
    *((unsigned int *)t25) = t41;

LAB1:    t8 = (t39 + 80);
    t7 = *((int *)t8);
    t10 = (t39 + 136U);
    t12 = *((char **)t10);
    xsi_put_memory(t7, t12);
    return t0;
LAB2:    if (t13 == 1)
        goto LAB5;

LAB6:    t7 = t9;
    goto LAB4;

LAB5:    t7 = t11;
    goto LAB4;

LAB7:    t7 = t9;
    goto LAB4;

LAB9:    if (t20 == 1)
        goto LAB12;

LAB13:    t14 = t18;
    goto LAB11;

LAB12:    t14 = t16;
    goto LAB11;

LAB14:    t14 = t18;
    goto LAB11;

LAB16:    if (t30 == 1)
        goto LAB19;

LAB20:    t24 = t26;
    goto LAB18;

LAB19:    t24 = t28;
    goto LAB18;

LAB21:    t24 = t26;
    goto LAB18;

LAB23:    if (t37 == 1)
        goto LAB26;

LAB27:    t31 = t35;
    goto LAB25;

LAB26:    t31 = t33;
    goto LAB25;

LAB28:    t31 = t35;
    goto LAB25;

LAB30:    t54 = 2147483647;
    goto LAB32;

LAB34:    *((char **)t58) = t3;
    goto LAB33;

LAB36:    t70 = (t4 + 0U);
    t71 = *((int *)t70);
    t72 = (t4 + 8U);
    t73 = *((int *)t72);
    t74 = (t68 - t71);
    t75 = (t74 * t73);
    t76 = (t4 + 4U);
    t77 = *((int *)t76);
    xsi_vhdl_check_range_of_index(t71, t77, t73, t68);
    t78 = (1U * t75);
    t79 = (0 + t78);
    t80 = (t3 + t79);
    t81 = *((unsigned char *)t80);
    t82 = (t39 + 56U);
    t83 = *((char **)t82);
    t82 = (t4 + 0U);
    t85 = *((int *)t82);
    t86 = (t4 + 4U);
    t87 = *((int *)t86);
    t88 = (t4 + 8U);
    t89 = *((int *)t88);
    if (t85 > t87)
        goto LAB46;

LAB47:    if (t89 == -1)
        goto LAB51;

LAB52:    t84 = t87;

LAB48:    t90 = (t84 + 1);
    t91 = (t90 - t68);
    t92 = (t23 + 0U);
    t93 = *((int *)t92);
    t94 = (t23 + 8U);
    t95 = *((int *)t94);
    t96 = (t91 - t93);
    t97 = (t96 * t95);
    t98 = (t23 + 4U);
    t99 = *((int *)t98);
    xsi_vhdl_check_range_of_index(t93, t99, t95, t91);
    t100 = (1U * t97);
    t101 = (0 + t100);
    t102 = (t83 + t101);
    *((unsigned char *)t102) = t81;

LAB37:    if (t68 == t69)
        goto LAB38;

LAB53:    t7 = (t68 + 1);
    t68 = t7;
    goto LAB35;

LAB39:    if (t67 == 1)
        goto LAB42;

LAB43:    t61 = t63;
    goto LAB41;

LAB42:    t61 = t65;
    goto LAB41;

LAB44:    t61 = t63;
    goto LAB41;

LAB46:    if (t89 == 1)
        goto LAB49;

LAB50:    t84 = t85;
    goto LAB48;

LAB49:    t84 = t87;
    goto LAB48;

LAB51:    t84 = t85;
    goto LAB48;

LAB54:;
}

char *work_p_2431924499_sub_4231071090_4141849106(char *t1, char *t2, char *t3, char *t4)
{
    char t5[128];
    char t6[24];
    char t7[16];
    char t14[64];
    char *t0;
    char *t8;
    char *t9;
    int t10;
    unsigned int t11;
    char *t12;
    char *t13;
    char *t15;
    char *t16;
    char *t17;
    char *t18;
    unsigned char t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    unsigned int t27;
    int t28;
    int t29;
    int t30;

LAB0:    t8 = (t7 + 0U);
    t9 = (t8 + 0U);
    *((int *)t9) = 63;
    t9 = (t8 + 4U);
    *((int *)t9) = 0;
    t9 = (t8 + 8U);
    *((int *)t9) = -1;
    t10 = (0 - 63);
    t11 = (t10 * -1);
    t11 = (t11 + 1);
    t9 = (t8 + 12U);
    *((unsigned int *)t9) = t11;
    t9 = (t5 + 4U);
    t12 = ((IEEE_P_1242562249) + 3112);
    t13 = (t9 + 88U);
    *((char **)t13) = t12;
    t15 = (t9 + 56U);
    *((char **)t15) = t14;
    xsi_type_set_default_value(t12, t14, t7);
    t16 = (t9 + 64U);
    *((char **)t16) = t7;
    t17 = (t9 + 80U);
    *((unsigned int *)t17) = 64U;
    t18 = (t6 + 4U);
    t19 = (t3 != 0);
    if (t19 == 1)
        goto LAB3;

LAB2:    t20 = (t6 + 12U);
    *((char **)t20) = t4;
    t21 = (t7 + 12U);
    t11 = *((unsigned int *)t21);
    t11 = (t11 * 1U);
    t22 = xsi_get_transient_memory(t11);
    memset(t22, 0, t11);
    t23 = t22;
    memset(t23, (unsigned char)2, t11);
    t24 = (t9 + 56U);
    t25 = *((char **)t24);
    t24 = (t25 + 0);
    t26 = (t7 + 12U);
    t27 = *((unsigned int *)t26);
    t27 = (t27 * 1U);
    memcpy(t24, t22, t27);
    t8 = (t9 + 56U);
    t12 = *((char **)t8);
    t8 = (t7 + 12U);
    t11 = *((unsigned int *)t8);
    t11 = (t11 * 1U);
    t0 = xsi_get_transient_memory(t11);
    memcpy(t0, t12, t11);
    t13 = (t7 + 0U);
    t10 = *((int *)t13);
    t15 = (t7 + 4U);
    t28 = *((int *)t15);
    t16 = (t7 + 8U);
    t29 = *((int *)t16);
    t17 = (t2 + 0U);
    t21 = (t17 + 0U);
    *((int *)t21) = t10;
    t21 = (t17 + 4U);
    *((int *)t21) = t28;
    t21 = (t17 + 8U);
    *((int *)t21) = t29;
    t30 = (t28 - t10);
    t27 = (t30 * t29);
    t27 = (t27 + 1);
    t21 = (t17 + 12U);
    *((unsigned int *)t21) = t27;

LAB1:    return t0;
LAB3:    *((char **)t18) = t3;
    goto LAB2;

LAB4:;
}

char *work_p_2431924499_sub_3685960934_4141849106(char *t1, char *t2, char *t3, char *t4, char *t5, char *t6)
{
    char t7[488];
    char t8[40];
    char t11[16];
    char t26[16];
    char t49[16];
    char t65[8];
    char t119[16];
    char *t0;
    char *t9;
    unsigned int t10;
    char *t12;
    unsigned int t13;
    int t14;
    char *t15;
    char *t16;
    int t17;
    unsigned int t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t27;
    unsigned int t28;
    int t29;
    char *t30;
    char *t31;
    int t32;
    unsigned int t33;
    char *t34;
    char *t35;
    char *t36;
    char *t37;
    char *t38;
    char *t39;
    char *t40;
    int t41;
    unsigned int t42;
    char *t43;
    char *t44;
    char *t45;
    unsigned int t46;
    int t47;
    unsigned int t48;
    char *t50;
    unsigned int t51;
    char *t52;
    char *t53;
    int t54;
    unsigned int t55;
    char *t56;
    char *t57;
    char *t58;
    char *t59;
    char *t60;
    char *t61;
    char *t62;
    char *t63;
    char *t64;
    char *t66;
    char *t67;
    char *t68;
    unsigned char t69;
    char *t70;
    char *t71;
    unsigned char t72;
    char *t73;
    char *t74;
    int t75;
    int t76;
    int t77;
    char *t78;
    char *t79;
    int t80;
    char *t81;
    unsigned int t82;
    int t83;
    unsigned int t84;
    char *t85;
    int t86;
    char *t87;
    int t88;
    unsigned int t89;
    unsigned int t90;
    char *t91;
    char *t92;
    unsigned int t93;
    int t94;
    int t95;
    unsigned int t96;
    unsigned int t97;
    char *t98;
    char *t99;
    char *t100;
    int t101;
    char *t102;
    unsigned int t103;
    int t104;
    unsigned int t105;
    char *t106;
    int t107;
    char *t108;
    int t109;
    unsigned int t110;
    unsigned int t111;
    char *t112;
    char *t113;
    unsigned int t114;
    int t115;
    int t116;
    unsigned int t117;
    unsigned int t118;

LAB0:    t9 = (t4 + 12U);
    t10 = *((unsigned int *)t9);
    t10 = (t10 * 1U);
    t12 = (t4 + 12U);
    t13 = *((unsigned int *)t12);
    t14 = (t13 - 1);
    t15 = (t11 + 0U);
    t16 = (t15 + 0U);
    *((int *)t16) = t14;
    t16 = (t15 + 4U);
    *((int *)t16) = 0;
    t16 = (t15 + 8U);
    *((int *)t16) = -1;
    t17 = (0 - t14);
    t18 = (t17 * -1);
    t18 = (t18 + 1);
    t16 = (t15 + 12U);
    *((unsigned int *)t16) = t18;
    t16 = (t7 + 4U);
    t19 = ((IEEE_P_1242562249) + 3000);
    t20 = (t16 + 88U);
    *((char **)t20) = t19;
    t21 = (char *)alloca(t10);
    t22 = (t16 + 56U);
    *((char **)t22) = t21;
    memcpy(t21, t3, t10);
    t23 = (t16 + 64U);
    *((char **)t23) = t11;
    t24 = (t16 + 80U);
    *((unsigned int *)t24) = t10;
    t25 = (t6 + 12U);
    t18 = *((unsigned int *)t25);
    t18 = (t18 * 1U);
    t27 = (t6 + 12U);
    t28 = *((unsigned int *)t27);
    t29 = (t28 - 1);
    t30 = (t26 + 0U);
    t31 = (t30 + 0U);
    *((int *)t31) = t29;
    t31 = (t30 + 4U);
    *((int *)t31) = 0;
    t31 = (t30 + 8U);
    *((int *)t31) = -1;
    t32 = (0 - t29);
    t33 = (t32 * -1);
    t33 = (t33 + 1);
    t31 = (t30 + 12U);
    *((unsigned int *)t31) = t33;
    t31 = (t7 + 124U);
    t34 = ((IEEE_P_1242562249) + 3000);
    t35 = (t31 + 88U);
    *((char **)t35) = t34;
    t36 = (char *)alloca(t18);
    t37 = (t31 + 56U);
    *((char **)t37) = t36;
    memcpy(t36, t5, t18);
    t38 = (t31 + 64U);
    *((char **)t38) = t26;
    t39 = (t31 + 80U);
    *((unsigned int *)t39) = t18;
    t40 = (t6 + 12U);
    t33 = *((unsigned int *)t40);
    t41 = (0 - t33);
    t42 = (t41 * -1);
    t42 = (t42 + 1);
    t42 = (t42 * 1U);
    t43 = xsi_get_transient_memory(t42);
    memset(t43, 0, t42);
    t44 = t43;
    memset(t44, (unsigned char)2, t42);
    t45 = (t6 + 12U);
    t46 = *((unsigned int *)t45);
    t47 = (0 - t46);
    t48 = (t47 * -1);
    t48 = (t48 + 1);
    t48 = (t48 * 1U);
    t50 = (t6 + 12U);
    t51 = *((unsigned int *)t50);
    t52 = (t49 + 0U);
    t53 = (t52 + 0U);
    *((unsigned int *)t53) = t51;
    t53 = (t52 + 4U);
    *((int *)t53) = 0;
    t53 = (t52 + 8U);
    *((int *)t53) = -1;
    t54 = (0 - t51);
    t55 = (t54 * -1);
    t55 = (t55 + 1);
    t53 = (t52 + 12U);
    *((unsigned int *)t53) = t55;
    t53 = (t7 + 244U);
    t56 = ((IEEE_P_1242562249) + 3000);
    t57 = (t53 + 88U);
    *((char **)t57) = t56;
    t58 = (char *)alloca(t48);
    t59 = (t53 + 56U);
    *((char **)t59) = t58;
    memcpy(t58, t43, t48);
    t60 = (t53 + 64U);
    *((char **)t60) = t49;
    t61 = (t53 + 80U);
    *((unsigned int *)t61) = t48;
    t62 = (t7 + 364U);
    t63 = ((STD_STANDARD) + 384);
    t64 = (t62 + 88U);
    *((char **)t64) = t63;
    t66 = (t62 + 56U);
    *((char **)t66) = t65;
    *((int *)t65) = 0;
    t67 = (t62 + 80U);
    *((unsigned int *)t67) = 4U;
    t68 = (t8 + 4U);
    t69 = (t3 != 0);
    if (t69 == 1)
        goto LAB3;

LAB2:    t70 = (t8 + 12U);
    *((char **)t70) = t4;
    t71 = (t8 + 20U);
    t72 = (t5 != 0);
    if (t72 == 1)
        goto LAB5;

LAB4:    t73 = (t8 + 28U);
    *((char **)t73) = t6;
    t74 = (t6 + 12U);
    t55 = *((unsigned int *)t74);
    t75 = (t55 - 1);
    t76 = 0;
    t77 = t75;

LAB6:    if (t76 <= t77)
        goto LAB7;

LAB9:    t9 = (t16 + 56U);
    t12 = *((char **)t9);
    t9 = (t11 + 12U);
    t10 = *((unsigned int *)t9);
    t10 = (t10 * 1U);
    t0 = xsi_get_transient_memory(t10);
    memcpy(t0, t12, t10);
    t15 = (t11 + 0U);
    t14 = *((int *)t15);
    t19 = (t11 + 4U);
    t17 = *((int *)t19);
    t20 = (t11 + 8U);
    t29 = *((int *)t20);
    t22 = (t2 + 0U);
    t23 = (t22 + 0U);
    *((int *)t23) = t14;
    t23 = (t22 + 4U);
    *((int *)t23) = t17;
    t23 = (t22 + 8U);
    *((int *)t23) = t29;
    t32 = (t17 - t14);
    t13 = (t32 * t29);
    t13 = (t13 + 1);
    t23 = (t22 + 12U);
    *((unsigned int *)t23) = t13;

LAB1:    return t0;
LAB3:    *((char **)t68) = t3;
    goto LAB2;

LAB5:    *((char **)t71) = t5;
    goto LAB4;

LAB7:    t78 = (t53 + 56U);
    t79 = *((char **)t78);
    t78 = (t49 + 0U);
    t80 = *((int *)t78);
    t81 = (t6 + 12U);
    t82 = *((unsigned int *)t81);
    t83 = (t82 - 2);
    t84 = (t80 - t83);
    t85 = (t49 + 4U);
    t86 = *((int *)t85);
    t87 = (t49 + 8U);
    t88 = *((int *)t87);
    xsi_vhdl_check_range_of_slice(t80, t86, t88, t83, 0, -1);
    t89 = (t84 * 1U);
    t90 = (0 + t89);
    t91 = (t79 + t90);
    t92 = (t6 + 12U);
    t93 = *((unsigned int *)t92);
    t94 = (t93 - 2);
    t95 = (0 - t94);
    t96 = (t95 * -1);
    t96 = (t96 + 1);
    t97 = (1U * t96);
    t98 = xsi_get_transient_memory(t97);
    memcpy(t98, t91, t97);
    t99 = (t53 + 56U);
    t100 = *((char **)t99);
    t99 = (t49 + 0U);
    t101 = *((int *)t99);
    t102 = (t6 + 12U);
    t103 = *((unsigned int *)t102);
    t104 = (t103 - 1);
    t105 = (t101 - t104);
    t106 = (t49 + 4U);
    t107 = *((int *)t106);
    t108 = (t49 + 8U);
    t109 = *((int *)t108);
    xsi_vhdl_check_range_of_slice(t101, t107, t109, t104, 1, -1);
    t110 = (t105 * 1U);
    t111 = (0 + t110);
    t112 = (t100 + t111);
    t113 = (t6 + 12U);
    t114 = *((unsigned int *)t113);
    t115 = (t114 - 2);
    t116 = (0 - t115);
    t117 = (t116 * -1);
    t117 = (t117 + 1);
    t118 = (1U * t117);
    memcpy(t112, t98, t118);
    t9 = (t16 + 56U);
    t12 = *((char **)t9);
    t9 = (t4 + 12U);
    t10 = *((unsigned int *)t9);
    t14 = (t10 - 1);
    t15 = (t11 + 0U);
    t17 = *((int *)t15);
    t19 = (t11 + 8U);
    t29 = *((int *)t19);
    t32 = (t14 - t17);
    t13 = (t32 * t29);
    t20 = (t11 + 4U);
    t41 = *((int *)t20);
    xsi_vhdl_check_range_of_index(t17, t41, t29, t14);
    t18 = (1U * t13);
    t28 = (0 + t18);
    t22 = (t12 + t28);
    t69 = *((unsigned char *)t22);
    t23 = (t53 + 56U);
    t24 = *((char **)t23);
    t23 = (t49 + 0U);
    t47 = *((int *)t23);
    t25 = (t49 + 8U);
    t54 = *((int *)t25);
    t75 = (0 - t47);
    t33 = (t75 * t54);
    t42 = (1U * t33);
    t46 = (0 + t42);
    t27 = (t24 + t46);
    *((unsigned char *)t27) = t69;
    t9 = (t16 + 56U);
    t12 = *((char **)t9);
    t9 = (t11 + 0U);
    t14 = *((int *)t9);
    t15 = (t4 + 12U);
    t10 = *((unsigned int *)t15);
    t17 = (t10 - 2);
    t13 = (t14 - t17);
    t19 = (t11 + 4U);
    t29 = *((int *)t19);
    t20 = (t11 + 8U);
    t32 = *((int *)t20);
    xsi_vhdl_check_range_of_slice(t14, t29, t32, t17, 0, -1);
    t18 = (t13 * 1U);
    t28 = (0 + t18);
    t22 = (t12 + t28);
    t23 = (t4 + 12U);
    t33 = *((unsigned int *)t23);
    t41 = (t33 - 2);
    t47 = (0 - t41);
    t42 = (t47 * -1);
    t42 = (t42 + 1);
    t46 = (1U * t42);
    t24 = xsi_get_transient_memory(t46);
    memcpy(t24, t22, t46);
    t25 = (t16 + 56U);
    t27 = *((char **)t25);
    t25 = (t11 + 0U);
    t54 = *((int *)t25);
    t30 = (t4 + 12U);
    t48 = *((unsigned int *)t30);
    t75 = (t48 - 1);
    t51 = (t54 - t75);
    t34 = (t11 + 4U);
    t80 = *((int *)t34);
    t35 = (t11 + 8U);
    t83 = *((int *)t35);
    xsi_vhdl_check_range_of_slice(t54, t80, t83, t75, 1, -1);
    t55 = (t51 * 1U);
    t82 = (0 + t55);
    t37 = (t27 + t82);
    t38 = (t4 + 12U);
    t84 = *((unsigned int *)t38);
    t86 = (t84 - 2);
    t88 = (0 - t86);
    t89 = (t88 * -1);
    t89 = (t89 + 1);
    t90 = (1U * t89);
    memcpy(t37, t24, t90);
    t9 = (t53 + 56U);
    t12 = *((char **)t9);
    t9 = (t31 + 56U);
    t15 = *((char **)t9);
    t9 = ieee_p_1242562249_sub_1547270861_1035706684(IEEE_P_1242562249, t119, t12, t49, t15, t26);
    t19 = (t53 + 56U);
    t20 = *((char **)t19);
    t19 = (t20 + 0);
    t22 = (t119 + 12U);
    t10 = *((unsigned int *)t22);
    t13 = (1U * t10);
    memcpy(t19, t9, t13);
    t9 = (t53 + 56U);
    t12 = *((char **)t9);
    t9 = (t6 + 12U);
    t10 = *((unsigned int *)t9);
    t14 = (t10 - 1);
    t15 = (t49 + 0U);
    t17 = *((int *)t15);
    t19 = (t49 + 8U);
    t29 = *((int *)t19);
    t32 = (t14 - t17);
    t13 = (t32 * t29);
    t20 = (t49 + 4U);
    t41 = *((int *)t20);
    xsi_vhdl_check_range_of_index(t17, t41, t29, t14);
    t18 = (1U * t13);
    t28 = (0 + t18);
    t22 = (t12 + t28);
    t69 = *((unsigned char *)t22);
    t72 = (t69 == (unsigned char)3);
    if (t72 != 0)
        goto LAB10;

LAB12:    t9 = (t16 + 56U);
    t12 = *((char **)t9);
    t9 = (t11 + 0U);
    t14 = *((int *)t9);
    t15 = (t11 + 8U);
    t17 = *((int *)t15);
    t29 = (0 - t14);
    t10 = (t29 * t17);
    t13 = (1U * t10);
    t18 = (0 + t13);
    t19 = (t12 + t18);
    *((unsigned char *)t19) = (unsigned char)3;

LAB11:
LAB8:    if (t76 == t77)
        goto LAB9;

LAB13:    t14 = (t76 + 1);
    t76 = t14;
    goto LAB6;

LAB10:    t23 = (t16 + 56U);
    t24 = *((char **)t23);
    t23 = (t11 + 0U);
    t47 = *((int *)t23);
    t25 = (t11 + 8U);
    t54 = *((int *)t25);
    t75 = (0 - t47);
    t33 = (t75 * t54);
    t42 = (1U * t33);
    t46 = (0 + t42);
    t27 = (t24 + t46);
    *((unsigned char *)t27) = (unsigned char)2;
    t9 = (t53 + 56U);
    t12 = *((char **)t9);
    t9 = (t31 + 56U);
    t15 = *((char **)t9);
    t9 = ieee_p_1242562249_sub_1547198987_1035706684(IEEE_P_1242562249, t119, t12, t49, t15, t26);
    t19 = (t53 + 56U);
    t20 = *((char **)t19);
    t19 = (t20 + 0);
    t22 = (t119 + 12U);
    t10 = *((unsigned int *)t22);
    t13 = (1U * t10);
    memcpy(t19, t9, t13);
    goto LAB11;

LAB14:;
}

unsigned char work_p_2431924499_sub_1028826968_4141849106(char *t1, char *t2, char *t3)
{
    char t4[248];
    char t5[24];
    char t9[8];
    char t15[8];
    unsigned char t0;
    char *t6;
    char *t7;
    char *t8;
    char *t10;
    char *t11;
    char *t12;
    char *t13;
    char *t14;
    char *t16;
    char *t17;
    char *t18;
    unsigned char t19;
    char *t20;
    char *t21;
    unsigned int t22;
    char *t23;
    int t24;
    char *t25;
    int t26;
    int t27;
    unsigned int t28;
    char *t29;
    int t30;
    unsigned int t31;
    unsigned int t32;
    char *t33;
    unsigned char t34;
    char *t35;
    char *t36;

LAB0:    t6 = (t4 + 4U);
    t7 = ((STD_STANDARD) + 384);
    t8 = (t6 + 88U);
    *((char **)t8) = t7;
    t10 = (t6 + 56U);
    *((char **)t10) = t9;
    xsi_type_set_default_value(t7, t9, 0);
    t11 = (t6 + 80U);
    *((unsigned int *)t11) = 4U;
    t12 = (t4 + 124U);
    t13 = ((IEEE_P_2592010699) + 3320);
    t14 = (t12 + 88U);
    *((char **)t14) = t13;
    t16 = (t12 + 56U);
    *((char **)t16) = t15;
    xsi_type_set_default_value(t13, t15, 0);
    t17 = (t12 + 80U);
    *((unsigned int *)t17) = 1U;
    t18 = (t5 + 4U);
    t19 = (t2 != 0);
    if (t19 == 1)
        goto LAB3;

LAB2:    t20 = (t5 + 12U);
    *((char **)t20) = t3;
    t21 = (t3 + 12U);
    t22 = *((unsigned int *)t21);
    t23 = (t3 + 0U);
    t24 = *((int *)t23);
    t25 = (t3 + 8U);
    t26 = *((int *)t25);
    t27 = (t22 - t24);
    t28 = (t27 * t26);
    t29 = (t3 + 4U);
    t30 = *((int *)t29);
    xsi_vhdl_check_range_of_index(t24, t30, t26, t22);
    t31 = (1U * t28);
    t32 = (0 + t31);
    t33 = (t2 + t32);
    t34 = *((unsigned char *)t33);
    t35 = (t12 + 56U);
    t36 = *((char **)t35);
    t35 = (t36 + 0);
    *((unsigned char *)t35) = t34;
    t7 = (t12 + 56U);
    t8 = *((char **)t7);
    t19 = *((unsigned char *)t8);
    t0 = t19;

LAB1:    return t0;
LAB3:    *((char **)t18) = t2;
    goto LAB2;

LAB4:;
}

char *work_p_2431924499_sub_2208906615_4141849106(char *t1, char *t2, char *t3, char *t4)
{
    char t5[128];
    char t6[24];
    char t12[16];
    char *t0;
    char *t7;
    unsigned int t8;
    int t9;
    int t10;
    unsigned int t11;
    char *t13;
    unsigned int t14;
    int t15;
    char *t16;
    char *t17;
    int t18;
    unsigned int t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    unsigned char t27;
    char *t28;
    char *t29;
    int t30;
    char *t31;
    int t32;
    char *t33;
    int t34;
    unsigned int t35;
    unsigned int t36;
    char *t37;
    char *t38;
    char *t39;
    int t40;
    unsigned int t41;
    unsigned int t42;

LAB0:    t7 = (t4 + 12U);
    t8 = *((unsigned int *)t7);
    t9 = (t8 - 1);
    t10 = (0 - t9);
    t11 = (t10 * -1);
    t11 = (t11 + 1);
    t11 = (t11 * 1U);
    t13 = (t4 + 12U);
    t14 = *((unsigned int *)t13);
    t15 = (t14 - 1);
    t16 = (t12 + 0U);
    t17 = (t16 + 0U);
    *((int *)t17) = t15;
    t17 = (t16 + 4U);
    *((int *)t17) = 0;
    t17 = (t16 + 8U);
    *((int *)t17) = -1;
    t18 = (0 - t15);
    t19 = (t18 * -1);
    t19 = (t19 + 1);
    t17 = (t16 + 12U);
    *((unsigned int *)t17) = t19;
    t17 = (t5 + 4U);
    t20 = ((IEEE_P_2592010699) + 4024);
    t21 = (t17 + 88U);
    *((char **)t21) = t20;
    t22 = (char *)alloca(t11);
    t23 = (t17 + 56U);
    *((char **)t23) = t22;
    xsi_type_set_default_value(t20, t22, t12);
    t24 = (t17 + 64U);
    *((char **)t24) = t12;
    t25 = (t17 + 80U);
    *((unsigned int *)t25) = t11;
    t26 = (t6 + 4U);
    t27 = (t3 != 0);
    if (t27 == 1)
        goto LAB3;

LAB2:    t28 = (t6 + 12U);
    *((char **)t28) = t4;
    t29 = (t4 + 0U);
    t30 = *((int *)t29);
    t19 = (t30 - 22);
    t31 = (t4 + 4U);
    t32 = *((int *)t31);
    t33 = (t4 + 8U);
    t34 = *((int *)t33);
    xsi_vhdl_check_range_of_slice(t30, t32, t34, 22, 0, -1);
    t35 = (t19 * 1U);
    t36 = (0 + t35);
    t37 = (t3 + t36);
    t38 = (t17 + 56U);
    t39 = *((char **)t38);
    t38 = (t39 + 0);
    t40 = (0 - 22);
    t41 = (t40 * -1);
    t41 = (t41 + 1);
    t42 = (1U * t41);
    memcpy(t38, t37, t42);
    t7 = (t17 + 56U);
    t13 = *((char **)t7);
    t7 = (t12 + 12U);
    t8 = *((unsigned int *)t7);
    t8 = (t8 * 1U);
    t0 = xsi_get_transient_memory(t8);
    memcpy(t0, t13, t8);
    t16 = (t12 + 0U);
    t9 = *((int *)t16);
    t20 = (t12 + 4U);
    t10 = *((int *)t20);
    t21 = (t12 + 8U);
    t15 = *((int *)t21);
    t23 = (t2 + 0U);
    t24 = (t23 + 0U);
    *((int *)t24) = t9;
    t24 = (t23 + 4U);
    *((int *)t24) = t10;
    t24 = (t23 + 8U);
    *((int *)t24) = t15;
    t18 = (t10 - t9);
    t11 = (t18 * t15);
    t11 = (t11 + 1);
    t24 = (t23 + 12U);
    *((unsigned int *)t24) = t11;

LAB1:    return t0;
LAB3:    *((char **)t26) = t3;
    goto LAB2;

LAB4:;
}

char *work_p_2431924499_sub_2411749927_4141849106(char *t1, char *t2, char *t3, char *t4)
{
    char t5[128];
    char t6[24];
    char t7[16];
    char t14[8];
    char *t0;
    char *t8;
    char *t9;
    int t10;
    unsigned int t11;
    char *t12;
    char *t13;
    char *t15;
    char *t16;
    char *t17;
    char *t18;
    unsigned char t19;
    char *t20;
    char *t21;
    int t22;
    char *t23;
    int t24;
    char *t25;
    int t26;
    unsigned int t27;
    unsigned int t28;
    char *t29;
    char *t30;
    char *t31;
    int t32;
    unsigned int t33;
    unsigned int t34;

LAB0:    t8 = (t7 + 0U);
    t9 = (t8 + 0U);
    *((int *)t9) = 7;
    t9 = (t8 + 4U);
    *((int *)t9) = 0;
    t9 = (t8 + 8U);
    *((int *)t9) = -1;
    t10 = (0 - 7);
    t11 = (t10 * -1);
    t11 = (t11 + 1);
    t9 = (t8 + 12U);
    *((unsigned int *)t9) = t11;
    t9 = (t5 + 4U);
    t12 = ((IEEE_P_2592010699) + 4024);
    t13 = (t9 + 88U);
    *((char **)t13) = t12;
    t15 = (t9 + 56U);
    *((char **)t15) = t14;
    xsi_type_set_default_value(t12, t14, t7);
    t16 = (t9 + 64U);
    *((char **)t16) = t7;
    t17 = (t9 + 80U);
    *((unsigned int *)t17) = 8U;
    t18 = (t6 + 4U);
    t19 = (t3 != 0);
    if (t19 == 1)
        goto LAB3;

LAB2:    t20 = (t6 + 12U);
    *((char **)t20) = t4;
    t21 = (t4 + 0U);
    t22 = *((int *)t21);
    t11 = (t22 - 30);
    t23 = (t4 + 4U);
    t24 = *((int *)t23);
    t25 = (t4 + 8U);
    t26 = *((int *)t25);
    xsi_vhdl_check_range_of_slice(t22, t24, t26, 30, 23, -1);
    t27 = (t11 * 1U);
    t28 = (0 + t27);
    t29 = (t3 + t28);
    t30 = (t9 + 56U);
    t31 = *((char **)t30);
    t30 = (t31 + 0);
    t32 = (23 - 30);
    t33 = (t32 * -1);
    t33 = (t33 + 1);
    t34 = (1U * t33);
    memcpy(t30, t29, t34);
    t8 = (t9 + 56U);
    t12 = *((char **)t8);
    t8 = (t7 + 12U);
    t11 = *((unsigned int *)t8);
    t11 = (t11 * 1U);
    t0 = xsi_get_transient_memory(t11);
    memcpy(t0, t12, t11);
    t13 = (t7 + 0U);
    t10 = *((int *)t13);
    t15 = (t7 + 4U);
    t22 = *((int *)t15);
    t16 = (t7 + 8U);
    t24 = *((int *)t16);
    t17 = (t2 + 0U);
    t21 = (t17 + 0U);
    *((int *)t21) = t10;
    t21 = (t17 + 4U);
    *((int *)t21) = t22;
    t21 = (t17 + 8U);
    *((int *)t21) = t24;
    t26 = (t22 - t10);
    t27 = (t26 * t24);
    t27 = (t27 + 1);
    t21 = (t17 + 12U);
    *((unsigned int *)t21) = t27;

LAB1:    return t0;
LAB3:    *((char **)t18) = t3;
    goto LAB2;

LAB4:;
}

char *work_p_2431924499_sub_4001421352_4141849106(char *t1, char *t2, char *t3, char *t4, char *t5, char *t6)
{
    char t7[128];
    char t8[40];
    char t9[16];
    char t16[32];
    char t38[16];
    char t39[16];
    char t40[16];
    char *t0;
    char *t10;
    char *t11;
    int t12;
    unsigned int t13;
    char *t14;
    char *t15;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    unsigned char t21;
    char *t22;
    char *t23;
    unsigned char t24;
    char *t25;
    unsigned char t26;
    unsigned char t27;
    unsigned char t28;
    char *t29;
    char *t30;
    int t31;
    char *t32;
    int t33;
    int t34;
    unsigned int t35;
    unsigned int t36;
    char *t37;
    unsigned int t41;

LAB0:    t10 = (t9 + 0U);
    t11 = (t10 + 0U);
    *((int *)t11) = 31;
    t11 = (t10 + 4U);
    *((int *)t11) = 0;
    t11 = (t10 + 8U);
    *((int *)t11) = -1;
    t12 = (0 - 31);
    t13 = (t12 * -1);
    t13 = (t13 + 1);
    t11 = (t10 + 12U);
    *((unsigned int *)t11) = t13;
    t11 = (t7 + 4U);
    t14 = ((IEEE_P_2592010699) + 4024);
    t15 = (t11 + 88U);
    *((char **)t15) = t14;
    t17 = (t11 + 56U);
    *((char **)t17) = t16;
    xsi_type_set_default_value(t14, t16, t9);
    t18 = (t11 + 64U);
    *((char **)t18) = t9;
    t19 = (t11 + 80U);
    *((unsigned int *)t19) = 32U;
    t20 = (t8 + 4U);
    t21 = (t3 != 0);
    if (t21 == 1)
        goto LAB3;

LAB2:    t22 = (t8 + 12U);
    *((char **)t22) = t4;
    t23 = (t8 + 20U);
    t24 = (t5 != 0);
    if (t24 == 1)
        goto LAB5;

LAB4:    t25 = (t8 + 28U);
    *((char **)t25) = t6;
    t26 = work_p_2431924499_sub_1028826968_4141849106(t1, t3, t4);
    t27 = work_p_2431924499_sub_1028826968_4141849106(t1, t5, t6);
    t28 = ieee_p_2592010699_sub_2507238156_503743352(IEEE_P_2592010699, t26, t27);
    t29 = (t11 + 56U);
    t30 = *((char **)t29);
    t29 = (t9 + 0U);
    t31 = *((int *)t29);
    t32 = (t9 + 8U);
    t33 = *((int *)t32);
    t34 = (31 - t31);
    t13 = (t34 * t33);
    t35 = (1U * t13);
    t36 = (0 + t35);
    t37 = (t30 + t36);
    *((unsigned char *)t37) = t28;
    t10 = work_p_2431924499_sub_2411749927_4141849106(t1, t39, t3, t4);
    t12 = ieee_p_1242562249_sub_2271993008_1035706684(IEEE_P_1242562249, t10, t39);
    t14 = work_p_2431924499_sub_2411749927_4141849106(t1, t40, t5, t6);
    t31 = ieee_p_1242562249_sub_2271993008_1035706684(IEEE_P_1242562249, t14, t40);
    t33 = (t12 + t31);
    t15 = ieee_p_1242562249_sub_2563015576_1035706684(IEEE_P_1242562249, t38, t33, 8);
    t17 = (t11 + 56U);
    t18 = *((char **)t17);
    t17 = (t9 + 0U);
    t34 = *((int *)t17);
    t13 = (t34 - 30);
    t35 = (t13 * 1U);
    t36 = (0 + t35);
    t19 = (t18 + t36);
    t29 = (t38 + 12U);
    t41 = *((unsigned int *)t29);
    t41 = (t41 * 1U);
    memcpy(t19, t15, t41);
    t10 = work_p_2431924499_sub_2208906615_4141849106(t1, t39, t3, t4);
    t12 = ieee_p_1242562249_sub_1657552908_1035706684(IEEE_P_1242562249, t10, t39);
    t14 = work_p_2431924499_sub_2208906615_4141849106(t1, t40, t5, t6);
    t31 = ieee_p_1242562249_sub_1657552908_1035706684(IEEE_P_1242562249, t14, t40);
    t33 = (t12 * t31);
    t15 = ieee_p_1242562249_sub_2563015576_1035706684(IEEE_P_1242562249, t38, t33, 23);
    t17 = (t11 + 56U);
    t18 = *((char **)t17);
    t17 = (t9 + 0U);
    t34 = *((int *)t17);
    t13 = (t34 - 22);
    t35 = (t13 * 1U);
    t36 = (0 + t35);
    t19 = (t18 + t36);
    t29 = (t38 + 12U);
    t41 = *((unsigned int *)t29);
    t41 = (t41 * 1U);
    memcpy(t19, t15, t41);
    t10 = (t11 + 56U);
    t14 = *((char **)t10);
    t10 = (t9 + 12U);
    t13 = *((unsigned int *)t10);
    t13 = (t13 * 1U);
    t0 = xsi_get_transient_memory(t13);
    memcpy(t0, t14, t13);
    t15 = (t9 + 0U);
    t12 = *((int *)t15);
    t17 = (t9 + 4U);
    t31 = *((int *)t17);
    t18 = (t9 + 8U);
    t33 = *((int *)t18);
    t19 = (t2 + 0U);
    t29 = (t19 + 0U);
    *((int *)t29) = t12;
    t29 = (t19 + 4U);
    *((int *)t29) = t31;
    t29 = (t19 + 8U);
    *((int *)t29) = t33;
    t34 = (t31 - t12);
    t35 = (t34 * t33);
    t35 = (t35 + 1);
    t29 = (t19 + 12U);
    *((unsigned int *)t29) = t35;

LAB1:    return t0;
LAB3:    *((char **)t20) = t3;
    goto LAB2;

LAB5:    *((char **)t23) = t5;
    goto LAB4;

LAB6:;
}


extern void work_p_2431924499_init()
{
	static char *se[] = {(void *)work_p_2431924499_sub_419251499_4141849106,(void *)work_p_2431924499_sub_4097533137_4141849106,(void *)work_p_2431924499_sub_3525837213_4141849106,(void *)work_p_2431924499_sub_2096353530_4141849106,(void *)work_p_2431924499_sub_4231071090_4141849106,(void *)work_p_2431924499_sub_3685960934_4141849106,(void *)work_p_2431924499_sub_1028826968_4141849106,(void *)work_p_2431924499_sub_2208906615_4141849106,(void *)work_p_2431924499_sub_2411749927_4141849106,(void *)work_p_2431924499_sub_4001421352_4141849106};
	xsi_register_didat("work_p_2431924499", "isim/demux_tb_isim_beh.exe.sim/work/p_2431924499.didat");
	xsi_register_subprogram_executes(se);
}
