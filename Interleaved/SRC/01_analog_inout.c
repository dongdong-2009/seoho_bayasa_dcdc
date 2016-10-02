#define __ANALOG_INOUT_H_
#include "math.h"
#include "main_def.h"

// 아날로그 출력 모니터링
void Analog_Output_Monitoring()
{
	// 아날로그 출력 항목 선택
	// NUMBER_OF_ANALOG_OUT			11
	// AO1_FREQUENCY_OUT			0		-> 출력 주파수
	// AO1_MOTOR_SPEED				1
	// AO1_CURRENT					2
	// AO1_VOLTAGE					3
	// AO1_TORQUE					4
	// AO1_OUTPUT_POWER				5
	// AO1_DC_BUS_VOLTAGE			6		-> DC 버스 전압
	// AO1_FREE_FUNC_OUT			7		-> Free Function
	// AO1_0mA						8
	// AO1_4mA						9
	// AO1_20mA						10

	count_0mA = (unsigned int)((PWM_TMR_PERIOD) * (1. - 1e-4*(float)(AO1.P02_Adjustment_0mA)));
	count_4mA = (unsigned int)((PWM_TMR_PERIOD) * (1. - 1e-4*(float)(AO1.P03_Adjustment_4mA)));
	count_20mA =(unsigned int)((PWM_TMR_PERIOD) * (1. - 1e-3*(float)(AO1.P04_Adjustment_20mA)));

	if (AO1.P00_Output_selection>=AO1_0mA)						// Index = 8 ~ 10
	{
		if (AO1.P00_Output_selection==AO1_0mA)					// 0mA 미세 조정
		{
			count = count_0mA;
			Anaolg_Output_mA_x1=0;
		}
		else if (AO1.P00_Output_selection==AO1_4mA)				// 4mA 미세 조정
		{
			count = count_4mA;
			Anaolg_Output_mA_x1=4;
		}
		else if (AO1.P00_Output_selection==AO1_20mA)				// 20 mA 출력 미세조정
		{
			count = count_20mA;
			Anaolg_Output_mA_x1=20;
		}
	}
	else
	{
		if ( AO1.P00_Output_selection == AO1_FREQUENCY_OUT)
		{
			tmp_float = 0.;
			tmp_float1= 1.;
		}
		else if (AO1.P00_Output_selection==AO1_MOTOR_SPEED)
		{
			tmp_float = 0.;
			tmp_float1= 1.;
		}
		else if (AO1.P00_Output_selection==AO1_CURRENT)
		{
			tmp_float = Iinput_LPF_test;
			tmp_float1= 1000.;
		}
		else if (AO1.P00_Output_selection==AO1_VOLTAGE)
		{
			tmp_float = 0.;
			tmp_float1= 1.;
		}
		else if (AO1.P00_Output_selection==AO1_TORQUE)
		{
			tmp_float = 0.;
			tmp_float1= 1.;
		}
		else if (AO1.P00_Output_selection==AO1_OUTPUT_POWER)
		{
			tmp_float = Power_out/100.;
			tmp_float1= P_rate;
		}
		else if (AO1.P00_Output_selection==AO1_DC_BUS_VOLTAGE)
		{
			tmp_float  = Vdc_out_LPF;						// DC 버스 전압
			tmp_float1 = Vdc_set_user;
		}

		else if (AO1.P00_Output_selection==AO1_FREE_FUNC_OUT)
		{
			tmp_float = 0.;
			tmp_float1= 1.;
		}
		if(!AO1.P06_Inversion)
		{
			if(AO1.P01_Type)
			{
				count = count_4mA - (float)(count_4mA-count_20mA)*tmp_float/tmp_float1*100./(float)AO1.P05_Max_output_x1;
				Anaolg_Output_mA_x1 = 4. + 16 * tmp_float/tmp_float1;
			}
			else
			{
				count = count_0mA - (float)(count_0mA-count_20mA)*tmp_float/tmp_float1*100./(float)AO1.P05_Max_output_x1;
				Anaolg_Output_mA_x1 = 20. * tmp_float/tmp_float1;
			}
		}
		else
		{
			if(AO1.P01_Type)
			{
				count = count_4mA - (float)(count_4mA-count_20mA)*(1.-tmp_float/tmp_float1*100./(float)AO1.P05_Max_output_x1);
				Anaolg_Output_mA_x1 = 4. + 16 * (1.-tmp_float/tmp_float1);
			}
			else
			{
				count = count_0mA - (float)(count_0mA-count_20mA)*(1.-tmp_float/tmp_float1*100./(float)AO1.P05_Max_output_x1);
				Anaolg_Output_mA_x1 = 20. * (1.-tmp_float/tmp_float1);
			}
		}
	}
}

