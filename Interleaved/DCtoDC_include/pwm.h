#define PWM_BUF_DIR_HIGH	1
#define PWM_BUF_DIR_LOW		0

#define PWM_ACTIVE_HIGH		1
#define PWM_ACTIVE_LOW		0
#define PWM_ACTIVE_LOW_SIMULTANEOUS	5

#define SAMPLING_TOP		0x01
#define SAMPLING_BOTTOM		0x02
#define SAMPLING_BOTH		0x03

typedef struct {
	int op_state;
	int sampling_mode;
	int phase_duty_max_scaled;
	int phase_duty_half_scaled;
	int phase_duty_min_scaled;
	int phase_a_duty_scaled;
	int phase_b_duty_scaled;
	int phase_c_duty_scaled;
}	PWM;

#ifdef _PWM_
	float cmpa_A=0.0,	cmpa_B=0.0,	cmpa_C=0.0,	cmpa_4A = 0.0;
	int ADCTMP0 = 0,	ADCTMP1 = 0,	ADCTMP2 = 0;
	int ADCTMP3 = 0,	ADCTMP5 = 0,	ADCTMP15 = 0;

	float DUTY_OPEN = 0.0;
	float DUTY_A = 0.0,	DUTY_B = 0.0,	DUTY_C = 0.0;
	float Duty_L_MIN = 0.0,	Duty_L_MAX = 0.75;

	PWM	 pwm_g1;
	void pwm_buffer_setup();
	void pwm_g1_setup( double sys_clk, double dead_time);
#else
	extern float cmpa_A,	cmpa_B,	cmpa_C,	cmpa_4A;
	extern int	 ADCTMP0,	ADCTMP1,	ADCTMP2;
	extern int	 ADCTMP3,	ADCTMP5,	ADCTMP15;

	extern float DUTY_OPEN;
	extern float DUTY_A,	DUTY_B,		DUTY_C;
	extern float Duty_L_MIN,	Duty_L_MAX;

	extern PWM pwm_g1;
	extern void pwm_buffer_setup();
	void pwm_g1_setup( double sys_clk, double dead_time);
#endif
