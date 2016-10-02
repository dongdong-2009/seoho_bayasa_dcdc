#define _SYSTEM_

#include "main_def.h"

void Relay_setup()
{
    EALLOW;
	GpioCtrlRegs.GPBMUX1.bit.GPIO38 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO38 = 1;
	EDIS;
}

void Init_GPIO(void)
{
	EALLOW;
	GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO13 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;
	GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;
	EDIS;
}

void delay(int delay_cnt)
{
	while(delay_cnt--);
}

void delay_long(long int delay_cnt)
{
	while(delay_cnt--);
}

void LSPCLK_setup()
{
    EALLOW;
	SysCtrlRegs.LOSPCP.bit.LSPCLK = 1;			// SYSCLKOUT/2
    EDIS;
}


void Init_AD_converter()
{
	AdcRegs.ADCTRL3.bit.ADCBGRFDN = 0x3;
	delay(10000);
	AdcRegs.ADCTRL3.bit.ADCPWDN = 1;
	delay(10000);
	AdcRegs.ADCTRL1.bit.ACQ_PS = 8;
	AdcRegs.ADCTRL1.bit.CPS = 1;
	AdcRegs.ADCTRL3.bit.ADCCLKPS = 0;
	AdcRegs.ADCMAXCONV.all = 0x000F;
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;
	AdcRegs.ADCTRL1.bit.CONT_RUN = 0;		// Start-Stop mode
	AdcRegs.ADCCHSELSEQ1.all = 0x3210;
	AdcRegs.ADCCHSELSEQ2.all = 0x7654;
	AdcRegs.ADCCHSELSEQ3.all = 0xBA98;
	AdcRegs.ADCCHSELSEQ4.all = 0xFEDC;
}

int system_first_rst = 0;
Parameter_Initialization()
{
	int Drive_power= 0;
	if (GpioDataRegs.GPCDAT.bit.GPIO68) Drive_power+= 1;
	if (GpioDataRegs.GPCDAT.bit.GPIO67) Drive_power+= 2;
	if (GpioDataRegs.GPCDAT.bit.GPIO66) Drive_power+= 4;
	if (GpioDataRegs.GPCDAT.bit.GPIO65) Drive_power+= 8;
	if (GpioDataRegs.GPCDAT.bit.GPIO64) Drive_power+= 16;	
	
	switch ( Drive_power )
	{
		case 0:
			P_rate = 55;
			I_scale= 100.0/1.8;
			IGBT_current= 35.;
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 1:
			P_rate = 75;
			I_scale= 100.0/1.43;
			IGBT_current= 35.;
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break; 	
		case 2:
		 	P_rate = 110; 
			IGBT_current= 35.;
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 3: 
			P_rate = 150; 
			IGBT_current= 35.;
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 4: 
			P_rate = 185; 
			I_scale= 200.0/0.85;
			IGBT_current= 63.;
			V_rate= 415;
			I_rate= 350;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 380;
			break;
		case 5: // (110104 by HHH)  
			P_rate = 220;
			I_scale= 100.0/0.85;
			IGBT_current= 63;
			V_rate= 380;
			I_rate= 232;
			Rated_frequency= 60;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 380;
			break;
		case 6: 
			P_rate = 300;
			IGBT_current= 35.;
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 7: 
			P_rate = 370; 
			IGBT_current= 35.;
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 8: 
			P_rate = 450;
			IGBT_current= 35.;
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 9: 
			P_rate = 550;
			IGBT_current= 35.;
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 10: 
			P_rate = 750;
			IGBT_current= 35.; 	
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 11: 
			P_rate = 900; 
			IGBT_current= 35.;
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 12: 
			P_rate = 1100;
			IGBT_current= 35.;
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 13: 
			P_rate = 1320; 
			IGBT_current= 35.;
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 14: 
			P_rate = 1600; 
			IGBT_current= 35.;	
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 15: 
			P_rate = 2000;
			IGBT_current= 35.;
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 16: 
			P_rate = 2500;
			IGBT_current= 35.;
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 17: 
			P_rate = 3150;
			IGBT_current= 35.; 
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 18: 
			P_rate = 4000;
			IGBT_current= 35.;
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 19:
		 	P_rate = 5000; 
		 	IGBT_current= 35.;	
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 20: 
			P_rate = 5600; 
			IGBT_current= 35.;
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 21: 
			P_rate = 6300; 
			IGBT_current= 35.;
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 22: 
			P_rate = 7150; 
			IGBT_current= 35.;
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 23: 
			P_rate = 7800; 
			IGBT_current= 35.;
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 30: 
			P_rate = 22; 
			IGBT_current= 35.;
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
		case 31: 
			P_rate = 37; 
			IGBT_current= 35.;
			V_rate= 230.;
			I_rate= 55;
			Rated_frequency= 50;
			Control_method= 3;
			PWM_frequency_x10_kHz= 50;
			Supply_voltage= 230;
			break;
	}

	Device_Info = 22;
	Software_Version = 'A';
	Software_Number = 100;

	Control_method = Double_Loop_VI;

	Fsw = 5000.;
	Vdc_set_user = 660.;
	V_rate_in = 380;
	P_rate = 5000;	// x10 [kW]
	R_L = 0.001;		// x1 [mOhm]
	La  = 0.0008;	// x1 [H];
	Drive_Voltage = 400;
	Sens_time_Vin = 50;		// 50[mS]

	Kp_Vdc_factor = 100.;	// 100%
	Ki_Vdc_factor = 100.;	// 100%
	Kp_Idc_factor = 100.;	// 100%
	Ki_Idc_factor = 100.;	// 100%
	vc_cnt_set = 5.;
	Cin = 10200e-6;		// 6800uF 2series 3 parallel
	Cout = 30000e-6;	// 10000uF 2series 3 parallel

	Fnv = Fsw/100.;
	Fnc = 200.;

	OV_set = 780;	// 750		// Output Over Voltage Level
	UV_set = 540;	// 400		// Output Under Voltage Level

	OVin_set = 600;		// Input Over Voltage Level
	UVin_set = 250;		// Input Under Voltage Level
	I_rate = (int)((float)(P_rate)  *100/(380 * 1.414*0.9));
	OC_Trip = 200;
	Max_Con_cur = 95;
	Over_Load= 135;
	Over_Load_Time = 60	;	//100;	//Seconds
	OV_Time = 200;					//Seconds
	OV_Temp = 85.0;
	Fnv_max = Fnv*1.5;
	Fnv_min = Fnv*0.5;
	Fnc_max = Fnc*1.5;
	Fnc_min = Fnc*0.5;


	// Analog Output 관련 파라메타 초기화
	AO1.P00_Output_selection = 0;
	AO1.P01_Type = 2;
	AO1.P02_Adjustment_0mA = 0;
	AO1.P03_Adjustment_4mA = 0;
	AO1.P04_Adjustment_20mA = 0;
	AO1.P05_Max_output_x1000 = 100;
	AO1.P06_Inversion = 0;

	AO2.P00_Output_selection=0;			
	AO2.P01_Type=1;
	AO2.P02_Adjustment_0mA=0;
	AO2.P03_Adjustment_4mA=0;
	AO2.P04_Adjustment_20mA=0;
	AO2.P05_Max_output_x1000=100;
	AO2.P06_Inversion=0;	

}

void Init_var()
{
	int i = 0;	

	if(!system_first_rst)
	{
		for(i=0;i<16;i++)
		{
			adc.conv_val[i] = 0;
			adc.tmp[i] = 0.0;
		}
	system_first_rst = 1;
	}
	On_delay = 1;			// Drive_Enable 신호 발생 후 3초 딜레이 
	Retry_delay = 5;		// Fault 제거후 정상상태를 1초 동안 요지 하면 운전 복귀
	Machine_state = 0;
	I_rate_p = I_rate / N_SW;
	// current controller variables 
	// Drive_Voltage의 값 설정
	// Key_pad 설정 값에 의해서 Drive_Voltage의 값을 설정 하도록 했다. 
	// 2010_09_01, dbsgln
	nFLT2_OFF;

	// 拷 타  
	//   = pole x Ts
	//  Update 챨 => (MAX_TIME_SHARING_INDEX*Ts)
//	Vdc_set_user = 600.;

	Monitor_LPF_inv_time_const = (int)inv_Time_Const(MAX_TIME_SHARING_INDEX,(1.0e-4 * Monitor_Filter_TIME_CONST_ms_x10));

// 추가 
/*	for(i=0;i<Buf_MAX;i++)//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11111
	{
		Data_Registers[i]=0x0000;
		CAN_Registers[i]=0x0000;
		SCI_Registers[i]=0x0000;
	}
*/
// 추가 
// 500/4 * 1/0.714 * 3/4095
//	adc_scale_0 = 0.128256;	// A상 전류 scale
//	adc_scale_1 = 0.128256;	// B상 전류 scale
//	adc_scale_2 = 0.128256;	// C상 전류 scale
// 500/4 * 1/1.2837 * 3/4095 = 0.0713368\

//	adc_scale_0 = 0.0713368;	// B상 전류 scale	0.075
//	adc_scale_1 = 0.0713368;	// B 전류 scale
//	adc_scale_2 = 0.0713368;	// C상 전류 scale

// 500kW급 에서 전류형 CT 사용 
// Rm = 10[Ohm] 
// Ireal / 5000 * Rm = Idc_adc_in = Ireal / 500.;
// 
 
	adc_scale_0 = 0.3663;	//500.* 3.0/4095.
	adc_scale_1 = 0.3663;
	adc_scale_2 = 0.3663;

	adc_scale_3 = 0.221;	// 0.0225665 = 1./0.0032464 * 3./4095;	// 출력전압 (계산치 보다 크게 나와서 조절

	adc_scale_5 = 0.23618;		//	1./(0.0188 * 0.33) * 3./ 4095 // 입력전압

	adc_scale_15= 3./4095.;  	//온도 

// Fault Neglect Setting
// 해당 neglect 비트 가 1로 셋팅 된 fault는 무시 되며 Fault_check에서 확인 가능하다
	point.Fault_Neglect1.all = 0x0000;
	point.Fault_Neglect2.all = 0x0000;
	point.Fault_Neglect2.bit.UV_IN 	= 1;	// 입력 전압 UV 무시
	point.Fault_Neglect1.bit.UV		= 1;	// 출력 전압 UV 무시
	Gain_setting();
	init_control_value();
}

void init_control_value()
{
	Vdc_out_ref = Vdc_input;
	Vdc_Err_PI = 0.0;
	Vdc_Error = 0.0;
	Vdc_Err_I = 0.0;
	Vdc_Err_P = 0.0;
	Vdc_Err_Anti = 0.0;
	Vdc_Err_PI_be = 0.0; 
	Idc_Err_I_a = 0.0;		
	Idc_Err_P_a = 0.0;
	Idc_Err_Anti_a = 0.0;	
	Idc_Err_PI_be_a = 0.0;
	Idc_Err_PI_a = 0.0;	
	Idc_Err_I_b = 0.0;		
	Idc_Err_P_b = 0.0;
	Idc_Err_Anti_b = 0.0;	
	Idc_Err_PI_be_b = 0.0;
	Idc_Err_PI_b = 0.0;
	Idc_Err_I_c = 0.0;
	Idc_Err_P_c = 0.0;
	Idc_Err_Anti_c = 0.0;
	Idc_Err_PI_be_c = 0.0;
	Idc_Err_PI_c = 0.0;
	cmpa_A = 0.0;
	DUTY_A = 0.0;
	DUTY_OPEN = 0.0;
	cmpa_4A = 0.0;
	cmpa_B = 0.0;
	DUTY_B = 0.0;
	cmpa_C = 0.0;
	DUTY_C = 0.0;

	Vdc_Err_I_MAX = 1.5 * (float)I_rate;		// 전압 적분기 출력 최대치 				
	Vdc_Err_I_MIN = (-0.5) * (float)I_rate;		// 전압 적분기 출력 최소치
	flag.GT1_ENA = 0;
}

int inv_Time_Const (int cycle,float Time_Const)
{
	tmp_long = (long)(((cycle * (int)(Tsamp))/Time_Const));		// -> Q16
	if 		(tmp_long < 1	 )	tmp_long = 1;
	else if (tmp_long > 32767)	tmp_long = 32767;	

	return	(int)tmp_long;
}

void Init_dsc()
{
	Init_AD_converter();
	Init_var();
	calculateOffset();
	Gain_setting();
	// Switching frequency limit
	if		(Fsw >= 6500.) Fsw = 6500.;
	else if (Fsw <= 3500.) Fsw = 3500.;
	pwm_g1.sampling_mode = SAMPLING_TOP;
	Tsamp = 1.0/Fsw;
	TBPHS_delay = Tsamp*SYS_CLK/2.*240./360.;
	pwm_g1_setup(SYS_CLK, Deadtime);
}

void calculateOffset()
{
	Uint16 i;
	Uint32 	Ias_sum, Ibs_sum, Ics_sum;

	Ias_sum = 0, Ibs_sum = 0, Ics_sum = 0;

	for(i=0; i<4096; i++){

	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;	// Start of conversion trigger for SEQ1
	AdcRegs.ADCTRL2.bit.SOC_SEQ2 = 1;	// Start of conversion trigger for SEQ2
	DELAY_US(10);

	// Ias Current Sensing
	Ias_sum += ((long)AdcRegs.ADCRESULT0);

	// Ibs Current Sensing
	Ibs_sum += ((long)AdcRegs.ADCRESULT1);

	// Ics Current Sensing
	Ics_sum += ((long)AdcRegs.ADCRESULT2);

	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;	// 14    Restart sequencer 1
	AdcRegs.ADCTRL2.bit.RST_SEQ2 = 1;	// 14    Restart sequencer 2
	DELAY_US(1);
	}
	Ias_offset = ((unsigned int)(Ias_sum >> 12) >> 4);
	Ibs_offset = ((unsigned int)(Ibs_sum >> 12) >> 4);
	Ics_offset = ((unsigned int)(Ics_sum >> 12) >> 4);

	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;
	EPwm1Regs.ETSEL.bit.SOCAEN = 1;
	EPwm1Regs.ETSEL.bit.SOCASEL = 1;
	EPwm1Regs.ETPS.bit.SOCAPRD = 1;
}


void Gain_setting()
{
	// 전압제어기 개인 설정 Wnv 	: 자연 주파수
	//						Kp_Vdc 	: P-gain
	//						Ki_Vdc	: I-gain
	// 0 -> 디폴트
	// 전압 제어범위 : 400 ~ 600V -> 폭=200V
	// 디폴트 DC-링크 전압제어기 파라미터
	// Kp -> 50V 전압오차 -> 100 % 전류 (전격 전류 60A/3 각 상의 정격 전류
	// Ki -> 200V 전압오차 -> 10싸이클 동안 정격 전류로 적분완료
	//	Kp_Vdc = I_rate/50.;
	//	Ki_Vdc = I_rate/(200. * 10.0);

	Wnv = Fnv * 2. * 3.141592;
//	Fnc = 200.;
	Wnc = Fnc * 2. * 3.141592;
	Kp_Idc = 2. * 0.8 * Wnc * La * Kp_Idc_factor/100.;
	Ki_Idc_T = Wnc * La * Tsamp * Wnc * Ki_Idc_factor/100.;
//	Ki_Vdc = 10.0;
	Ka_Vdc = 0.0;

	if(Temperature < OV_Temp ) 	Over_Temp_Flag = 0;
	else						Over_Temp_Flag = 1;

	Temp_Retry = 40;
	Kp_Vdc = I_rate_p/(0.1*Vdc_set_user);
	Ki_Vdc = I_rate_p/(10.*5.*0.1*Vdc_set_user);
	Ka_Vdc = 0.0;
}

