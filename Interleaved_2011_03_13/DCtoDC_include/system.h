// step 1. Set the system parameters
#define SYS_CLK					(float)150000000
#define Deadtime				(float)0.0
#define RUNN	1
#define STOP	0 

#define __MODBUS_COMMUNICATION_			1

 	typedef struct {
		float offset[16];
		float tmp[16];
		int conv_val[16];
		float tmp1[16];
	}	ADC;
#ifdef _SYSTEM_
	ADC	adc;
	unsigned int Device_Info = 0;
	unsigned int Software_Version = 0;
	unsigned int Software_Number = 0;
	unsigned int Run_Stop_meth = 0;
	unsigned int Run_Stop_Src = 0;
	unsigned int Ref_method = 0;
	unsigned int Local_Remote = 0;
	unsigned int Drive_Status = 0;
	unsigned int Run_Stop_Status=0;
	unsigned int State_Index = 0;
	void delay(int delay_cnt);
	void delay_long(long int delay_cnt);  
	void Init_dsc();
	void init_control_value();
	void Init_var();
	void Update_var();
	void calculateOffset();
#else
	extern ADC adc;
	extern unsigned int Device_Info;
	extern unsigned int Software_Version;
	extern unsigned int Software_Number;
	extern unsigned int Run_Stop_meth;
	extern unsigned int Run_Stop_Src;
	extern unsigned int Ref_method;
	extern unsigned int Local_Remote;
	extern unsigned int Drive_Status;
	extern unsigned int Run_Stop_Status;
	extern unsigned int State_Index;
	extern void delay(int delay_cnt);
	extern void delay_long(long int delay_cnt);
	extern void Init_dsc();
	extern void init_control_value();
	extern void Init_var();
	extern void Update_var();
	extern void Word_Write_data();
	extern void Word_Read_data();
	extern void Parameter_Initialization();
	extern void Write_Data_Registers_Offline();
	extern void Read_Data_Registers();
#endif

