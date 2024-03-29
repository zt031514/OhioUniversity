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

#include "xsi.h"

struct XSI_INFO xsi_info;



int main(int argc, char **argv)
{
    xsi_init_design(argc, argv);
    xsi_register_info(&xsi_info);

    xsi_register_min_prec_unit(-12);
    work_m_00000000002753386619_1957175458_init();
    work_m_00000000001200445275_1463177816_init();
    work_m_00000000001327156335_3338709120_init();
    work_m_00000000004080725372_2138213552_init();
    work_m_00000000003785798644_2058220583_init();
    work_m_00000000002876722453_3671727229_init();
    work_m_00000000001674009297_3674772129_init();
    work_m_00000000002235117286_0186216794_init();
    work_m_00000000002876722453_1667814796_init();
    work_m_00000000002786515922_4024119534_init();
    work_m_00000000001003765542_3038601299_init();
    work_m_00000000001941701677_3543940968_init();
    work_m_00000000000075550974_0530982496_init();
    work_m_00000000002005466221_2452869721_init();
    work_m_00000000000447061482_3723422143_init();
    work_m_00000000001327156335_2739340622_init();
    work_m_00000000000051377102_1318657526_init();
    work_m_00000000001625123931_1391118421_init();
    work_m_00000000000433848866_1912994691_init();
    work_m_00000000004134447467_2073120511_init();


    xsi_register_tops("work_m_00000000000433848866_1912994691");
    xsi_register_tops("work_m_00000000004134447467_2073120511");


    return xsi_run_simulation(argc, argv);

}
