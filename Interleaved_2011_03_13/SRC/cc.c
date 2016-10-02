#define _CC_


#include "main_def.h"
#include "math.h"


unsigned int delay_cnt = 0;

void Voltage_controller()
{
	test_led2_on;
	if(DRIVE_ENABLE)	// Drive_enable ÈÄ On_delay½Ã°£ ÈÄ µ¿ÀÛ
	{
		if(On_delay_cnt >= ((float)(On_delay/vc_cnt_set))/Tsamp)
		{
			Machine_state = RUNN;
		}
		else On_delay_cnt++;
	}
	else				// Drive_enable ÈÄ On_delay½Ã°£ ÈÄ µ¿ÀÛ
	{
		On_delay_cnt = 0;
		Machine_state = STOP;
	}

	//soft starting
	if(flag.control)
	{
		Vdc_min = Vdc_input;
		if		(Vdc_out_ref < Vdc_min)		 Vdc_out_ref = Vdc_min;

		if		(Vdc_out_ref < Vdc_set_user) Vdc_out_ref += Tsamp * vc_cnt_set * 200.0;
		else if (Vdc_out_ref > Vdc_set_user) Vdc_out_ref -= Tsamp * vc_cnt_set * 100.0;
		else								 Vdc_out_ref = Vdc_set_user;
	}
	else
	{
		Vdc_out_ref = Vdc_input;
	}

	Vdc_Error= Vdc_out_ref - Vdc_out;
	Vdc_Err_P = Vdc_Error * Kp_Vdc;
	Vdc_Err_I+= ((Vdc_Error - Vdc_Err_Anti)*Ki_Vdc);

	if ( Vdc_Err_I > Vdc_Err_I_MAX) Vdc_Err_I = Vdc_Err_I_MAX;
	if ( Vdc_Err_I < Vdc_Err_I_MIN) Vdc_Err_I = Vdc_Err_I_MIN;

	Vdc_Err_PI_be = Vdc_Err_P + Vdc_Err_I;

	if 		(Vdc_Err_PI_be > Vdc_Err_I_MAX) Vdc_Err_PI = Vdc_Err_I_MAX;
	else if (Vdc_Err_PI_be < Vdc_Err_I_MIN) Vdc_Err_PI = Vdc_Err_I_MIN;
	else 									Vdc_Err_PI = Vdc_Err_PI_be;

	if(Machine_state == RUNN)
	{
		Vdc_Err_Anti	= (Vdc_Err_PI_be - Vdc_Err_PI) * Ka_Vdc;
		Idc_ref			= Vdc_Err_PI / N_SW;
		if(DC_Build_Up_delay_cnt >= DC_Build_Up_delay_set/(Tsamp*vc_cnt_set)) UV_Check_Enable = 1;
		else DC_Build_Up_delay_cnt++;
	}
	else
	{
		DC_Build_Up_delay_cnt = 0;
		UV_Check_Enable = 0;
		init_control_value();
	}
	test_led2_off;
}

void current_controller_1()
{
	if(vc_cnt1 == vc_cnt_set)		{vc_cnt1 = 0;  Voltage_controller();	}
	++vc_cnt1; 
//	Voltage_controller();
	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;	    // SOC trigger for sequencer1 by software
	AdcRegs.ADCTRL2.bit.SOC_SEQ2 = 1;	    // SOC trigger for sequencer1 by software

	adc.conv_val[0] = (int)(AdcRegs.ADCRESULT0 >> 4) & 0x0FFF;	// Ias
	adc.conv_val[3] = (int)(AdcRegs.ADCRESULT3 >> 4) & 0x0FFF;	// Vdc_out
	Adc_Temperature = (int)(AdcRegs.ADCRESULT14>> 4) & 0x0FFF;	// Temperature
	adc.conv_val[15]= (int)(AdcRegs.ADCRESULT15>> 4) & 0x0FFF;	// Voltage Range

	adc.tmp[0] = (float)adc.conv_val[0]-Ias_offset;	// Ias;
	adc.tmp[3] = (float)adc.conv_val[3];			// Vdc_out
//	adc.tmp[15] = (float)adc.conv_val[15];

	ADCTMP0 = adc.tmp[0];
	ADCTMP3 = adc.tmp[3];
	ADCTMP5 = adc.tmp[5];
	ADCTMP15 = adc.tmp[15];

	Ias			= adc_scale_0  * adc.tmp[0];
	Iinput		= Ias + Ibs + Ics;
	Vdc_out 	= adc_scale_3 * adc.tmp[3];
	Voltage_Range = adc_scale_15 * adc.tmp[15];
	Temperature = 1e-1 * Temperature_Calculation(Adc_Temperature);	// ¿Âµµ ¼¾½Ì

	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;	    // SOC trigger for sequencer1 by software
	AdcRegs.ADCTRL2.bit.RST_SEQ2 = 1;	    // SOC trigger for sequencer1 by software

	epwm_isr_num = 1;
	if(!FaultInfo)
	{
		if((FaultInfo = fault_chk()) != 0) 
		{
			TripProc();
			Init_var();
		}
	}
	LPF(Vdc_input,Vdc_input_LPF,Monitor_LPF_inv_time_const,Vdc_input_LPF_Integrator);
	LPF(Iinput,Iinput_LPF,Monitor_LPF_inv_time_const,Iinput_LPF_integrator);
	LPF(Vdc_out,Vdc_out_LPF,Monitor_LPF_inv_time_const,Vdc_out_LPF_Integrator);

	LPF(Ias,Ias_LPF,Monitor_LPF_inv_time_const,Ias_mean_LPF_integrator);
	LPF(Idc_ref,Idc_ref_LPF,Monitor_LPF_inv_time_const,Idc_ref_LPF_integrator);
	
	Power_in = Vdc_input_LPF * Iinput_LPF;
	Power_out = 0.98 * Power_in;

	Idc_Error_a	 = Idc_ref - Ias;
	Idc_Err_P_a	 = Idc_Error_a * Kp_Idc;
	Idc_Err_I_a	 += (Idc_Error_a - Idc_Err_Anti_a) * Ki_Idc_T;

	Idc_Err_V_MAX = Vdc_out;
	Idc_Err_V_MIN = - Vdc_out;

	if		( Idc_Err_I_a > Idc_Err_V_MAX) Idc_Err_I_a = Idc_Err_V_MAX;
	else if ( Idc_Err_I_a < Idc_Err_V_MIN) Idc_Err_I_a = Idc_Err_V_MIN;

	Idc_Err_PI_be_a = Idc_Err_P_a +Idc_Err_I_a;

	if 		(Idc_Err_PI_be_a > Idc_Err_V_MAX)	Idc_Err_PI_a = Idc_Err_V_MAX;
	else if (Idc_Err_PI_be_a < Idc_Err_V_MIN)	Idc_Err_PI_a = Idc_Err_V_MIN;
	else 										Idc_Err_PI_a = Idc_Err_PI_be_a;

	Idc_Err_Anti_a = (Idc_Err_PI_be_a - Idc_Err_PI_a) * Ka_Idc;
}


void current_controller_2()
{
	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;	    // SOC trigger for sequencer1 by software
	AdcRegs.ADCTRL2.bit.SOC_SEQ2 = 1;	    // SOC trigger for sequencer1 by software

	adc.conv_val[1] = (int)(AdcRegs.ADCRESULT1 >> 4) & 0x0FFF;	// Ibs
	adc.conv_val[5] = (int)(AdcRegs.ADCRESULT5 >> 4) & 0x0FFF;	// Vdc_in

	adc.tmp[1] = (float)adc.conv_val[1]-Ibs_offset;        // Ibs;
	adc.tmp[5] = (float)adc.conv_val[5];		// AIN.V1

	ADCTMP1 = adc.tmp[1];
	Ibs = (adc_scale_1  * adc.tmp[1]);
	Vdc_input	= adc_scale_5 * adc.tmp[5];

	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;	    // SOC trigger for sequencer1 by software
	AdcRegs.ADCTRL2.bit.RST_SEQ2 = 1;	    // SOC trigger for sequencer1 by software

	epwm_isr_num = 2;
	if(!FaultInfo)
	{
		if((FaultInfo = fault_chk()) != 0) 
		{
			TripProc();
			Init_var();
		}
	}
	LPF(Ibs,Ibs_LPF,Monitor_LPF_inv_time_const,Ibs_mean_LPF_integrator);

	// b »ó Á¦¾î±â //
	Idc_Error_b	 = Idc_ref - Ibs;
	Idc_Err_P_b	 = Idc_Error_b * Kp_Idc;
	Idc_Err_I_b	 += (Idc_Error_b - Idc_Err_Anti_b) * Ki_Idc_T;

	Idc_Err_V_MAX = Vdc_out;
	Idc_Err_V_MIN = - Vdc_out;

	if ( Idc_Err_I_b > Idc_Err_V_MAX) Idc_Err_I_b = Idc_Err_V_MAX;
	if ( Idc_Err_I_b < Idc_Err_V_MIN) Idc_Err_I_b = Idc_Err_V_MIN;
	
	Idc_Err_PI_be_b = Idc_Err_P_b +Idc_Err_I_b;

	if		(Idc_Err_PI_be_b > Idc_Err_V_MAX)	Idc_Err_PI_b = Idc_Err_V_MAX;
	else if	(Idc_Err_PI_be_b < Idc_Err_V_MIN)	Idc_Err_PI_b = Idc_Err_V_MIN;
	else 										Idc_Err_PI_b = Idc_Err_PI_be_b;

	Idc_Err_Anti_b = (Idc_Err_PI_be_b - Idc_Err_PI_b) * Ka_Idc;
}

void current_controller_3()
{
	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;	    // SOC trigger for sequencer1 by software
	AdcRegs.ADCTRL2.bit.SOC_SEQ2 = 1;	    // SOC trigger for sequencer1 by software

	adc.conv_val[2] = (int)(AdcRegs.ADCRESULT2 >> 4) & 0x0FFF;	// Ics
	adc.tmp[2] = (float)adc.conv_val[2]-Ics_offset;        // Ics;

	ADCTMP2 = adc.tmp[2];

	Ics = (adc_scale_2  * adc.tmp[2]);

	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;	    // SOC trigger for sequencer1 by software
	AdcRegs.ADCTRL2.bit.RST_SEQ2 = 1;	    // SOC trigger for sequencer1 by software

	epwm_isr_num = 3;

	if(!FaultInfo)
	{
		if((FaultInfo = fault_chk()) != 0) 
		{
			TripProc();
			Init_var();
		}
	}
	LPF(Ics,Ics_LPF,Monitor_LPF_inv_time_const,Ics_mean_LPF_integrator);

	// c »ó Á¦¾î±â //
	Idc_Error_c	 = Idc_ref - Ics;
	Idc_Err_P_c	 = Idc_Error_c * Kp_Idc;
	Idc_Err_I_c	 += (Idc_Error_c - Idc_Err_Anti_c) * Ki_Idc_T;

	Idc_Err_V_MAX = Vdc_out;
	Idc_Err_V_MIN = - Vdc_out;

	if ( Idc_Err_I_c > Idc_Err_V_MAX) Idc_Err_I_c = Idc_Err_V_MAX;
	if ( Idc_Err_I_c < Idc_Err_V_MIN) Idc_Err_I_c = Idc_Err_V_MIN;

	Idc_Err_PI_be_c = Idc_Err_P_c +Idc_Err_I_c;

	if		(Idc_Err_PI_be_c > Idc_Err_V_MAX)	Idc_Err_PI_c = Idc_Err_V_MAX;
	else if	(Idc_Err_PI_be_c < Idc_Err_V_MIN)	Idc_Err_PI_c = Idc_Err_V_MIN;
	else										Idc_Err_PI_c = Idc_Err_PI_be_c;

	Idc_Err_Anti_c = (Idc_Err_PI_be_c - Idc_Err_PI_c) * Ka_Idc;
	dev_BackgroundDAC();
}

int Temperature_Calculation(int  Adc_Temperature)
{

	float C1, C2, R_NTC, B, Temp;
	// [5.5kW ~ 22kW]
	// Vi = 3.3V/3.7k = 0.891892V
	// Rm = 470 Ohm
	// Iref = 1.8976mA
	// R1=100k, R2=30k, R3=0.47k

	// T_25=298K, R_25=5.0 kOhm
	// T_100=373K, R_100=0.4933kOhm
	// B = (T_25 x T_100) ln (R_100/R_25) / (T_25 - T_100) = 3432.5477

	// ï¿½Âµï¿½ ï¿½ï¿½ï¿½ï¿½ È¸ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½â¿¡ ï¿½Æ·ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	// È¸ï¿½Î°ï¿½ ï¿½ï¿½ï¿½ï¿½Ç¾ï¿½ ï¿½ï¿½ï¿½ï¿½.
	// R_NTC^ = (R1+R2+R3)Vo/((R2/R1)(R1+R2)I-Vo)
	// Vo = (u/1024)3.28Vref
	// R_NTC = 400k R_NTC^/(400k-R_NTC^)		: 2 x 200kOhm ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½

	// R_NTC^ = (100+30+0.47) x (u/1024) x 3.28 / {(30/100)(100+30)1.8976-(u/1024)3.28}
	//        = 0.417912 u / (74.0064 - 3.203e-3 u) x 1.0e3 [Ohm]
	//        = C1 x u /(C2 - 3.203e-3 x u) x 1.0e3	
	// C1 = 0.417912		-> tmp_float1
	// C2 = 74.0064	-> tmp_float2
	// R_NTC = 400k R_NTC^ / (400k - R_NTC^)	

	C1=0.417912;
	C2=74.0064;
	R_NTC = 5.0;				// 5.0kOhm



//	B = 3433.;
	B = 3337.;
	// ADC valid bit: 10.9 bit -> 9 bitï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½Ø´ï¿½ 8/4096  
	Temp= (float)(Adc_Temperature>>3);
	Temp = (C1*2*Temp)/(C2-6.406e-3*Temp);		// 2 x 3.203e-3 -> 6.406e-3
	Temp = (400*Temp) / (400-Temp);				// R_NTC = 400 x R_NTC^ / (400 - R_NTC^)
	
	// tmp_int -> B + T1 ln(R2/R1)
	Temp = B + (298.* log(Temp/R_NTC));
	if (Temp<1)	Temp=1;
		
	// (B x T1)_x10 / [B + T1 ln(R2/R1)] -> (T_x10 - 2730) -> ï¿½Âµï¿½ [degC]		
	Temp = (B * 2980/Temp)-2730; 			// x10 : (25 + 273)k x 10 -> 2980
	
	// -25ï¿½ï¿½ ~ 150ï¿½ï¿½
	if 		(Temp > 1500.)	Temp = 1500.;
	else if (Temp < -250.)	Temp = -250.;
	return Temp;
}

