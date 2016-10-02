
#define		PI				3.141592654
#define		PI_2			6.283185307
#define		SQRT2			1.414213562
#define		SQRT3			1.732050808
#define		INV_SQRT3		(1./SQRT3)

// - Status_Index
#define	STATE_POWER_ON			'Y'
#define	STATE_CALIBRATION		'Z'
#define	STATE_READY				'R'
#define	STATE_STOP				'S'
#define	STATE_ACCELERATING		'A'
#define	STATE_DECELERATING		'D'
#define	STATE_RUNNING			'O'
#define	STATE_TUNING			'T'
#define	STATE_FAULT				'F'

// Control_method
#define Double_Loop_VI			1
#define Single_Loop_V			2

//-- uart 
#define CMD_RUN					'R'
#define CMD_STOP				'S'
// #define CMD_RESET				'T'


// Àú¿ª ÇÊÅÍ
// y(k) = y(k-1) + (pole x Ts)(x(k) - y(k)) =>	y(k) += (pole x Ts) (x(k) - y(k))
// LPF_coeff = pole x Ts	: °ªÀÌ ÀÛÀ¸¹Ç·Î "int"ÇüÀ¸·Î ¼³Á¤ÇÑ´Ù.
#define	LPF(input,output,LPF_coeff,integrator)	integrator += (LPF_coeff * (input - integrator));\
													output = integrator
#define		BOUND_PI(x)		((x) - 2.*PI*(int)((x + PI)/(2.*PI)))
#define 	Under_Limit(var)	(var > 0) ? var : ((var < 0) ? 0 : var)
#define		BOUND(x,xmax,xmin)	(((x)>(xmax))?(xmax):((x)<(xmin))?(xmin): (x) )   

 	typedef struct {
		int PWM;
		int OVM;
	}	MODE;
	typedef struct {
		int GT1_ENA;
		int control;
	} FLAG; 
/////////////////////////////////////////////////////////////////////
#ifdef _CC_
	float Fsw = 0.;
	float PWM_TMR_PERIOD = 0.0;
	extern int PWM_frequency_x10_kHz = 0;
	float Tsamp = 0.0;
	float TBPHS_delay = 0.0;
	int vc_cnt1 = 0;
	int vc_cnt_set = 0;
	int On_delay = 0, Retry_delay = 0;
	long On_delay_cnt = 0, Retry_delay_cnt = 0;
	unsigned int Run_Stop	= 0;
	unsigned int Machine_state = 0;
/////////////////////////////////////////////////////////////////////
// Sensed Parameters 
	float Vdc_out = 0.0, Vdc_out_LPF = 0.0;
	float Voltage_Range = 0.0;
	float Ias = 0.0, Ias_LPF = 0.0;
	float Ibs = 0.0, Ibs_LPF = 0.0;
	float Ics = 0.0, Ics_LPF = 0.0;
	unsigned int Ias_offset = 0., Ibs_offset = 0., Ics_offset = 0.;
	float Vdc_input = 0.0;
	float Vdc_input_LPF = 0.0;
	float Iinput = 0.0, Iinput_LPF = 0.0, Iinput_LPF_integrator = 0.0, Iinput_LPF_test = 0.0;
	unsigned int Sens_time_Vin = 0;

	float INV_Vdc = 0.005;
	float Power_in = 0.0, Power_out = 0.0;
	float Temperature = 0.0;
	int	  Adc_Temperature = 0; 

// ADC Scale
	float I_scale = 0.0;
	float adc_scale_0 = 0.0;
	float adc_scale_1 = 0.0;
	float adc_scale_2 = 0.0;
	float adc_scale_3 = 0.0;
	float adc_scale_5 = 0.0;
	float adc_scale_7 = 0.0;
	float adc_scale_15 = 0.0; 
/////////////////////////////////////////////////////////////////////
// Voltage Control //f
    float Vdc_out_ref= 0.0, 	Vdc_set_user = 0.0;
	float Vdc_min = 0.0;
	float Vdc_Error = 0.0,		Vdc_Err_PI= 0.0;
	float Vdc_Err_I = 0.0,  	Vdc_Err_P = 0.0;
	float Vdc_Err_Anti =0.0, 	Vdc_Err_PI_be = 0.0;
	float N_SW = 3.0;
	// PI gain
	float Kp_Vdc = 0.0, Kp_Vdc_factor = 0.0;	// Àü¾ÐÁ¦¾î±â P gain
	float Ki_Vdc = 0.0, Ki_Vdc_factor = 0.0;	// Àü¾ÐÁ¦¾î±â I gain
	float Ka_Vdc = 0.0;
	float Wnv = 0.0, Fnv = 0.0;
	float Fnv_max = 0.0, Fnv_min = 0.0;
	float Dampv = 0.707;
	float Kp_Vchange = 0.0, Kp_V_max = 0., Kp_V_min = 0.;
	float Vdc_input_Comp = 0.0;
	float Vdc_input_Comp1 = 0., Vdc_input_Comp2 = 0., Vdc_input_Comp3 = 0, Vdc_input_Comp_m =0.;
	// Control Limit
	float Vdc_Err_I_MAX = 0.0;			// Àü¾Ð ÀûºÐ±â Ãâ·Â ÃÖ´ëÄ¡ 				
	float Vdc_Err_I_MIN = 0.0;			// Àü¾Ð ÀûºÐ±â Ãâ·Â ÃÖ¼ÒÄ¡
/////////////////////////////////////////////////////////////////////		
// Current Control //
	float Idc_ref = 0.0, Idc_ref_LPF = 0.0, Idc_ref_LPF_integrator = 0.;			// Àü·ù Áö·ÉÄ¡
	float Idc_Error_a = 0.0,	Idc_Err_PI_a = 0.0;
	float Idc_Err_I_a = 0.0,	Idc_Err_P_a = 0.0;
	float Idc_Err_Anti_a = 0.0,	Idc_Err_PI_be_a = 0.0;
	float Idc_Error_b = 0.0,	Idc_Err_PI_b = 0.0;
	float Idc_Err_I_b = 0.0,	Idc_Err_P_b = 0.0;
	float Idc_Err_Anti_b = 0.0,	Idc_Err_PI_be_b = 0.0;
	float Idc_Error_c = 0.0,	Idc_Err_PI_c = 0.0;
	float Idc_Err_I_c = 0.0,	Idc_Err_P_c = 0.0;
	float Idc_Err_Anti_c = 0.0,	Idc_Err_PI_be_c = 0.0;
	float dc_v_ramp = 0.0;
	// PI gain
	float Kp_Idc = 0.0, Kp_Idc_factor = 0.0;
	float Ki_Idc_T = 0.0, Ki_Idc_factor = 0.0;
	float Ka_Idc = 0.0;
	float Wnc = 0.0, Fnc = 0.0;
	float Dampi = 0.707;
	float Fnc_change = 0.0, Fnc_setting = 0.0, Fnc_max = 0.0, Fnc_min = 0.0;
	// Control Limit
	float Idc_Err_V_MAX = 0.0;
	float Idc_Err_V_MIN = 0.0;
/////////////////////////////////////////////////////////////////////
// Hardware Compenents //
	float Cin = 0.0;
	float Cout = 0.0;			// Ãâ·Â´Ü Ä¿ÆÐ½ÃÅÍ
	float La = 0.0;				// »ó ÀÎ´öÅÏ½º
	float R_L = 0.0;			// »ó ÀÎ´öÅÍ ÀúÇ×
	int	  Drive_Voltage = 0;
	int   IGBT_current = 0;
	// G1 Basic Control Setup[l]
	int   Control_method = 0;
	int   Supply_voltage = 0;
	int   Rated_frequency = 0;
	int P_rate = 0;
	unsigned int V_rate = 0;
	unsigned int V_rate_in = 0;
	unsigned int I_rate = 0;
	unsigned int I_rate_p = 0;
	unsigned int epwm_isr_num = 0;
/////////////////////////////////////////////////////////////////////
// Monitoring Parameter
	float Ias_mean_LPF_integrator = 0.0, Vdc_out_LPF_Integrator = 0.0;
	float Ibs_mean_LPF_integrator = 0.0, Ics_mean_LPF_integrator = 0.0;
	float Vdc_input_LPF_Integrator = 0.0, Power_in_LPF_Integrator = 0.0;
	int	  Monitor_LPF_inv_time_const = 0, MAX_TIME_SHARING_INDEX = 1;
	long tmp_long = 0;
	int	Monitor_Filter_TIME_CONST_ms_x10 = 1000;	// 100ms  ¸ð´ÏÅÍ ÇÊÅÍ ½ÃÁ¤¼ö
	int inv_Time_Const(int cycle,float Time_Const);
	float WT = 0.0;
/////////////////////////////////////////////////////////////////////
//  for RealDSP monitoring 
	int DRIVE_ENABLE = 0;
	int FAULT_RESET = 0;
	int FAULT_RESET_COMPLETE = 0;
////////////////////////////////////////////////////////////////////
    float OPEN_DUTY_A = 0.0;
	float OPEN_DUTY_B = 0.0;
	float OPEN_DUTY_C = 0.0;
// template parameters
	float tmp_float = 0.0;
	int	 tmp_int = 0;
	int	 tmp_int1 = 0;
	int	 tmp_int2 = 0;

	MODE	mode;
	FLAG	flag;
	// Function //
	void Gain_setting();
	void current_controller_1();
	void current_controller_2();
	void current_controller_3();
	void Voltage_controller();
	int	 Var_initialize(unsigned char, unsigned char);
	void Relay_setup();
	void Nop1();
	int  Temperature_Calculation(int  Adc_Temperature);
/////////////////////////////////////////////////////////////////////
#else
	extern float Fsw;
	extern float PWM_TMR_PERIOD;
	extern int PWM_frequency_x10_kHz;
	extern float Tsamp;
	extern float TBPHS_delay;
	extern int vc_cnt1;
	extern int vc_cnt_set;
	extern int On_delay, Retry_delay;
	extern long On_delay_cnt, Retry_delay_cnt;
	extern unsigned int Run_Stop;
	extern unsigned int Machine_state;
/////////////////////////////////////////////////////////////////////
// Sensed Parameters 
	extern float Vdc_out, Vdc_out_LPF;
	extern float Voltage_Range;
	extern float Ias, Ias_LPF;
	extern float Ibs, Ibs_LPF;
	extern float Ics, Ics_LPF;
	extern unsigned int Ias_offset, Ibs_offset, Ics_offset;
	extern float Vdc_input;
	extern float Vdc_input_LPF;
	extern float Iinput, Iinput_LPF, Iinput_LPF_integrator, Iinput_LPF_test;
	extern unsigned int Sens_time_Vin;
	extern float INV_Vdc;
	extern float Power_in, Power_out;
	extern float Temperature;
	extern int Adc_Temperature;
// ADC Scale
	extern float I_scale;
	extern float adc_scale_0;
	extern float adc_scale_1;
	extern float adc_scale_2;
	extern float adc_scale_3;
	extern float adc_scale_5;
	extern float adc_scale_7;
	extern float adc_scale_15;
/////////////////////////////////////////////////////////////////////
// Voltage Control //f
	extern float Vdc_out_ref, Vdc_set_user;
	extern float Vdc_min;
	extern float Vdc_Error,		Vdc_Err_PI;
	extern float Vdc_Err_I,  	Vdc_Err_P;
	extern float Vdc_Err_Anti, 	Vdc_Err_PI_be;
	extern float N_SW;	
	// PI gain
	extern float Kp_Vdc, Kp_Vdc_factor;			// Àü¾ÐÁ¦¾î±â P gain
	extern float Ki_Vdc, Ki_Vdc_factor;			// ü¾ÐÁ¦¾î±â I gain
	extern float Ka_Vdc;
	extern float Wnv, Fnv;
	extern float Fnv_max, Fnv_min;
	extern float Dampv;
	extern float Kp_Vchange, Kp_V_max, Kp_V_min;
	extern float Vdc_input_Comp;
	// Control Limit
	extern float Vdc_Err_I_MAX;			// Àü¾Ð ÀûÐ±â Ãâ·Â ÃÖ´ëÄ¡ 				
	extern float Vdc_Err_I_MIN;			// Àü¾Ð ÀûºÐâ Ãâ·Â ÃÖ¼ÒÄ¡
/////////////////////////////////////////////////////////////////////		
// Current Control //
	extern float Idc_ref, Idc_ref_LPF, Idc_ref_LPF_integrator;	// Àü·ù Áö·ÉÄ¡
	extern float Idc_Error_a,		Idc_Err_PI_a;
	extern float Idc_Err_I_a,		Idc_Err_P_a;
	extern float Idc_Err_Anti_a,	Idc_Err_PI_be_a;
	extern float Idc_Error_b,		Idc_Err_PI_b;
	extern float Idc_Err_I_b,		Idc_Err_P_b;
	extern float Idc_Err_Anti_b,	Idc_Err_PI_be_b;
	extern float Idc_Error_c,		Idc_Err_PI_c;
	extern float Idc_Err_I_c,		Idc_Err_P_c;
	extern float Idc_Err_Anti_c,	Idc_Err_PI_be_c;
	extern float dc_v_ramp;
	// PI gain
	extern float Kp_Idc, Kp_Idc_factor;
	extern float Ki_Idc_T, Ki_Idc_factor;
	extern float Ka_Idc;
	extern float Wnc, Fnc;
	extern float Dampi;
	extern float Fnc_change, Fnc_setting, Fnc_max, Fnc_min;
	// Control Limit
	extern float Idc_Err_V_MAX;
	extern float Idc_Err_V_MIN;
/////////////////////////////////////////////////////////////////////
// Hardware Compenents //
	extern float Cin;
	extern float Cout;			// Ãâ·Â´Ü Ä¿ÆÐ½ÃÅÍ
	extern float La;			// a»ó ÀÎ´öÅÏ½º
	extern float R_L;				// a»ó ÀÎ´öÅÍ ÀúÇ×
	extern int Drive_Voltage;
	extern int IGBT_current;
	extern int Supply_voltage;
	extern int Control_method;
	extern int Rated_frequency;
	extern int P_rate;
	extern unsigned int V_rate;
	extern unsigned int V_rate_in;
	extern unsigned int I_rate;
	extern unsigned int I_rate_p;
	extern unsigned int epwm_isr_num;
/////////////////////////////////////////////////////////////////////
// Monitoring Parameter
	extern float Ias_mean_LPF_integrator, Vdc_out_LPF_Integrator;
	extern float Ibs_mean_LPF_integrator, Ics_mean_LPF_integrator;
	extern float Vdc_input_LPF_Integrator;
	extern int	 Monitor_LPF_inv_time_const, MAX_TIME_SHARING_INDEX;
	extern long tmp_long;
	extern int	Monitor_Filter_TIME_CONST_ms_x10; // 100ms ¸ð´ÏÅÍ ÇÊÅÍ ½ÃÁ¤¼ö

	extern float WT;
	extern int inv_Time_Const(int cycle,float Time_Const);
	extern int Temperature_Calculation(int  Adc_Temperature);
/////////////////////////////////////////////////////////////////////
//  for RealDSP monitoring
	extern int DRIVE_ENABLE;
	extern int FAULT_RESET;
	extern int FAULT_RESET_COMPLETE;

	extern     	float OPEN_DUTY_A;
	extern		float OPEN_DUTY_B;
	extern 		float OPEN_DUTY_C;
// template parameters
	extern float tmp_float;
	extern int	 tmp_int;
	extern int	 tmp_int1;
	extern int	 tmp_int2;

	extern MODE  mode;
	extern FLAG  flag;

    // Function //
	extern void Gain_setting();
    extern void current_controller_1();
	extern void current_controller_2();
	extern void current_controller_3();
	extern void Voltage_controller();
	extern int Var_initialize(unsigned char, unsigned char);
	extern void Relay_setup();
	extern void Nop1();
#endif

