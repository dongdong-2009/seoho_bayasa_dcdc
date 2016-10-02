#define __ANALOG_INOUT_H_
#include "math.h"
#include "main_def.h"

	float Output,RateValue;
	float Temp;
	unsigned int count;
	int Temp1;

void AO_Processing(Uint16 * count1)
{


//	25mA --> 0%  => 0
//	20mA --> 20% => 0.2
//	 4mA --> 84% => 0.84
//	0mA	 --> 100% 1
//

	Count20mA = (int)(SYS_CLK/2 * Tsamp * 0.2);
	Count4mA  = (int)(SYS_CLK/2 * Tsamp * 0.84);
	Count0mA  = (int)(SYS_CLK/2 * Tsamp * 1.00);
//#define Count20mA	3000
//#define Count4mA	11750
//#define Count0mA    14250 

	Temp= (float)AO1.P02_Adjustment_0mA *(Count20mA-Count0mA);
	switch (AO1.P01_Type ) //AO1.P00_Output_selection ) //   
	{
		case 0:		//Output= (Wrpm_det/(double)P.G01.P05_Rated_speed)*(double)P.G01.P03_Rated_frequency;
					//RateValue= (double)P.G01.P03_Rated_frequency;
					break;
		case 1:		//Output= Wrpm_det;				RateValue= (double)P.G01.P05_Rated_speed;
					break;

		case 2:		Output= Iinput_LPF_test;				RateValue= (float)100;//I_rate;
					break;
		case 3:		//Output= (sqrt(Vdss_ref*Vdss_ref+Vqss_ref*Vqss_ref)*SQRT2);
					//RateValue= (double)P.G01.P01_Rated_voltage;
					break;
		case 4:		//Output= Te;						RateValue= Te_rate;
					break;
		case 5:		//Output= Output_power_x10_kW;	RateValue= (double)G01.P00_Rated_power_x10_kW*100;
					break;
		case 6:		//Output= Vdc;					RateValue= (double)G01.P08_Supply_voltage*SQRT2;
					break;
		// Free Function Output
		case 7:	 	//Output= 0.0;					RateValue= 100.0;
					break;
		case 8:		count= (unsigned int)Count0mA-(unsigned int)(Temp);										break;
		case 9:		count= (unsigned int)Count4mA-(unsigned int)(Temp);										break;
		case 10:	count= (unsigned int)Count20mA-(unsigned int)(Temp);									break;
		default:	Output= 0.0; 	count= 0;	RateValue= 100.0;											break;
	}

	if ( AO1.P01_Type <= 7 )//AO1.P00_Output_selection <= 7 )
	{
		Temp= fabs(Output)/(RateValue*(float)AO1.P05_Max_output_x1000*1.e-2);

		if( AO1.P00_Output_selection == 1 ) //AO1.P01_Type == 1 ) // 4~20mA 출력
			Temp1 = Count4mA; // 4mA offset count
		else Temp1 = Count0mA; // 0~ 20mA 출력


		Temp= (Temp*(float)(Temp1-Count20mA));
		if(AO1.P06_Inversion== 1) // 0일 때 20mA
			Temp= Count20mA+Temp;
		else	Temp= Temp1-Temp;

		Temp= BOUND(Temp, Temp1, Count20mA);

		count = (Uint16) Temp;
	}
	* count1 = count;
}

unsigned Set_Verify_AnalogOutput_Online_Update_Parameter()
{
	// 아날로그 출력 선택
	// 선택 오류시 -> 사용 안함. 
//	if ((unsigned)par->ao.OUTPUT_SEL>=NUMBER_OF_ANALOG_OUT)
//		return	(unsigned)&par->ao.OUTPUT_SEL;
	
	// 0 -> 0 ~ 20mA
	// 1 -> 4 ~ 20mA
//	if ((unsigned)par->ao.OUTPUT_TYPE_SEL>=NUMBER_OF_ANALOG_OUTPUT_TYPE)
//		return	(unsigned)&par->ao.OUTPUT_TYPE_SEL;

	// 최대 출력 (at 20mA)
//	if ((unsigned)par->ao.MAX_OUT_percent_x10<1)	
//		return	(unsigned)&par->ao.MAX_OUT_percent_x10;	
			
	// 반전
//	if ((unsigned)par->ao.INVERSION_ENABLE>1)
//		return	(unsigned)&par->ao.INVERSION_ENABLE;	


	// Step 1 : 입력 -> Q13, 출력 -> mA
	// [(20mA - min_mA) / (max_% - 0_%)] ( x_% - 0_%) + min_mA
	// [(20mA - min_mA) / max_%] Input_% + min_mA
	// 0 ~ 20mA => min_mA = 0 mA
	// 4 ~ 20mA => min_mA = 4 mA
	// (20mA - min_mA) / (1.0e-2 x max_% x Q13) -> AO_Slope_Q13_2_mA
	// 100% -> Q13

	// 0, 4mA에서 각각 조정 값 -> p.u 
	// AO_RANGE_0mA_20mA 	: 	0 ~ 20mA
	// AO_RANGE_4mA_20mA	:	4 ~ 20mA
//	if (par->ao.OUTPUT_TYPE_SEL==AO_RANGE_0mA_20mA)
	if (AO1.P01_Type)
	{
		tmp_int=20;
		tmp_int2=AO1.P02_Adjustment_0mA;// par->ao.ADJUST_0mA_x10000;
	}
	else
	{
		tmp_int=16;
		tmp_int2=AO1.P03_Adjustment_4mA;// par->ao.ADJUST_4mA_x10000;
	}

	// tmp_int -> 20mA - 최소 전류
	// tmp_int2 -> 최소 전류에서 Duty_Ratio
//	AO_Slope_Q13_2_mA_f = tmp_int/((1.0e-3 * par->ao.MAX_OUT_percent_x10) * Q13_INTEGER_REF);
	AO_Slope_Q13_2_mA_f = tmp_int/(1.0e-3 * AO1.P05_Max_output_x1000);
	AO_Offset_Q13_2_mA = (20-tmp_int);		// 0 또는 4 상수 이므로 x1000을 하지 않는다

	// Step 2 : 입력 -> mA, 출력 -> Duty_Ratio
	// (Duty_20mA - Duty_min_mA)/(20mA - min_mA) (Input_mA - 20mA) + Duty_20mA
	// [(Duty_20mA - Duty_min_mA)/(20mA - min_mA)] x Input_mA + Duty_20mA - 20mA x [(Duty_20mA - Duty_min_mA)/(20mA - min_mA)]
	// AO_Slope_mA_2_Duty -> [(Duty_20mA - Duty_min_mA)/(20mA - min_mA)]
	// AO_Offset_mA_2_Duty -> Duty_20mA - 20mA x [(Duty_20mA - Duty_min_mA)/(20mA - min_mA)]

//	AO_Slope_mA_2_Duty_x10000_f = (float)(par->ao.ADJUST_20mA_x10000-tmp_int2)/tmp_int;
	AO_Slope_mA_2_Duty_x10000_f = (float)(AO1.P04_Adjustment_20mA)/tmp_int;
	AO_Offset_mA_2_Duty_x10000 = AO1.P04_Adjustment_20mA - (int)(20*AO_Slope_mA_2_Duty_x10000_f);

	// 출력 반전
	// slope x input_Q13 + min_mA
	// -> slope x input_Q13 + min_mA
	// -slope x input_mA + max_mA
	// -> -slope x input_mA + 20mA
	if (AO1.P06_Inversion)// (par->ao.INVERSION_ENABLE)
	{
		AO_Slope_Q13_2_mA_f *= -1;			// 기울기 반전
		AO_Offset_Q13_2_mA = 20;			// 20mA
	}
	return	0;
}

// 입력 -> Q13, 출력 -> Duty_Ratio -> PWM 폭
unsigned Analog_Out(int data, int data_ref)
{
	int	data1;	//data_Q13;

//	data_Q13 = (long)((qinv1(data_ref)>>5) * abs(data))>>13;	// (Q31/Q5)/Q13 -> Q13
	data1 = abs(data) / data_ref;	//(long)((qinv1(data_ref)>>5) * abs(data))>>13;	// (Q31/Q5)/Q13 -> Q13

	// tmp_float -> mA
	tmp_float = (AO_Slope_Q13_2_mA_f * data_Q13) + AO_Offset_Q13_2_mA;
	tmp_float = (AO_Slope_Q13_2_mA_f * data_Q13) + AO_Offset_Q13_2_mA;
	tmp_int = (int)(AO_Slope_mA_2_Duty_x10000_f * tmp_float) + AO_Offset_mA_2_Duty_x10000;

	Anaolg_Output_mA_x1000=(int)(1000*tmp_float);

	return	(int)((1.0e-4*tmp_int)*PWM_TMR_PERIOD);			// x10000 -> x1
}

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

//	if (AO1.OUTPUT_SEL>=AO1_0mA)						// Index = 8 ~ 10
		if (AO1.P00_Output_selection)						// Index = 8 ~ 10
		{
		tmp_float=1.0e-4*PWM_TMR_PERIOD;

		if (AO1.P00_Output_selection)					// 0mA 미세 조정
		{
			count = (int)(tmp_float * AO1.P02_Adjustment_0mA);	//eva->T1CMPR=(int)(tmp_float*par->ao.ADJUST_0mA_x10000);
			Anaolg_Output_mA_x1000=0;
		}
		else if (AO1.P00_Output_selection)				// 4mA 미세 조정
		{
			count = (int)(tmp_float * AO1.P03_Adjustment_4mA);	//eva->T1CMPR=(int)(tmp_float*par->ao.ADJUST_4mA_x10000);
			Anaolg_Output_mA_x1000=4000;
		}
		else if (AO1.P00_Output_selection)				// 20 mA 출력 미세조정
		{
			count = (int)(tmp_float * AO1.P04_Adjustment_20mA );	//eva->T1CMPR=(int)(tmp_float*par->ao.ADJUST_20mA_x10000);
			Anaolg_Output_mA_x1000=20000;
		}
	}
	else
	{
		if ( AO1.P00_Output_selection == AO1_FREQUENCY_OUT)
		{
//			#if __DC_2_DC_CONVERTER_
				tmp_int=0;
//			#else
//				tmp_int=DP.f_e;								// 출력 주파수
//			#endif
			tmp_int2=1;
		}
		else if (AO1.P00_Output_selection==AO1_MOTOR_SPEED)
		{
			tmp_int = 0;						// 모터 속도
			tmp_int2 = 1;
		}
		else if (AO1.P00_Output_selection==AO1_CURRENT)
		{
			tmp_int = Iinput_LPF_test;				// 상전류, 라인 전류 [mean]
			// 0.707 = 23167 / 32768
			tmp_int2 = 100;	//(long)(23167L*Nominal.Is_rated)>>15;
		}
		else if (AO1.P00_Output_selection==AO1_VOLTAGE)
		{
				tmp_int = 0;								// 모터 선간전압
/*			#if __PWM_CONVERTER_CODE_
				tmp_int = DP.Es_rms_LPF;					// 모터 선간전압
			#elif __DC_2_DC_CONVERTER_
				tmp_int=DP.V_DC_Out_LPF;
			#else
				tmp_int = DP.Vs_rms_LPF;					// 모터 선간전압
			#endif
*/
			// sqrt(3)/sqrt(2) = 1.2242 -> 20057/16384
			tmp_int2 = 1;	//(long)(20057L*Nominal.Vs_rated)>>13;
		}
		else if (AO1.P00_Output_selection==AO1_TORQUE)
		{
				tmp_int=0;
/*			#if __DC_2_DC_CONVERTER_
				tmp_int=0;
			#else
				tmp_int=Te_LPF;								// 출력 토크
			#endif
*/			tmp_int2 = 1;	//Nominal.Te_rated;
		}
		else if (AO1.P00_Output_selection==AO1_OUTPUT_POWER)
		{
				tmp_int = (int)(Power_out/100.);			// 라인 파워
				tmp_int2 = P_rate;
/*			#if __PWM_CONVERTER_CODE_
				tmp_int = DP.Re_Power_kW_x10_LPF;			// 라인 파워
				tmp_int2 = Drive_Rated_Power_kW_x10;
			#elif __DC_2_DC_CONVERTER_
				tmp_int = DP.Power_Out_kW_x10_LPF;			// 출력 파워
				tmp_int2 = Drive_Rated_Power_kW_x10;
			#else
				tmp_int = DP.Power_Out_kW_x10_LPF;			// 출력 파워
				tmp_int2 = Nominal.Rated_Power_kW_x10;
			#endif
*/		}
		else if (AO1.P00_Output_selection==AO1_DC_BUS_VOLTAGE)
		{
			tmp_int = Vdc_out_LPF;						// DC 버스 전압
			tmp_int2 = Vdc_set_user;
		}

//		#if (!__AUTO_TUNING_CODE_)
			else if (AO1.P00_Output_selection==AO1_FREE_FUNC_OUT)
			{
				// free function -> 아날로그 출력
//				flash_page=0;
//				port0000=flash_page;				// -> F00
				tmp_int= 0;	//(long)(*(int *)app.AnalogOut1_DP * flash->F00.parameter.config.scale_Q28L[SCALE_Q28L_INDEX_ANALOG_OUT1])>>15;	// Q28/Q13 -> Q13

				tmp_int2= 1;	//Q13_INTEGER_REF;
			}
//		#endif

//		eva->T1CMPR=Analog_Out(tmp_int,tmp_int2);
		count = Analog_Out(tmp_int,tmp_int2);
	}
}

