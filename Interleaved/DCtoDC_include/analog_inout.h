// 아날로그 출력 항목 선택
#define	ANALOG_OUT_NUM						11
#define	AO1_FREQUENCY_OUT					0
#define	AO1_MOTOR_SPEED						1
#define	AO1_CURRENT							2
#define	AO1_VOLTAGE							3
#define	AO1_TORQUE							4
#define	AO1_OUTPUT_POWER					5
#define	AO1_DC_BUS_VOLTAGE					6
#define	AO1_FREE_FUNC_OUT					7
#define	AO1_0mA								8
#define	AO1_4mA								9
#define	AO1_20mA							10

// 아날로그 출력 타입
#define	OUT_TYPE_NUM						2
#define	AO_RANGE_0mA_20mA					0
#define	AO_RANGE_4mA_20mA					1

	typedef	struct {
		int		P00_Output_selection;
		int		P01_Type;
		int		P02_Adjustment_0mA;
		int		P03_Adjustment_4mA;
		int		P04_Adjustment_20mA;
		int		P05_Max_output_x1;
		int		P06_Inversion;
	} ao1;

	typedef struct {
		int		P00_Output_selection;
		int		P01_Type;
		int		P02_Adjustment_0mA;
		int		P03_Adjustment_4mA;
		int		P04_Adjustment_20mA;
		int		P05_Max_output_x1;
		int		P06_Inversion;	
	} ao2;

#ifdef	__ANALOG_INOUT_H_
	ao1 AO1;
	ao2 AO2;
	int Count20mA = 0;
	int Count4mA = 0;
	int Count0mA = 0;
	// 아날로그 출력
	int		Anaolg_Output_mA_x1 = 0;
	unsigned int count=0;
	unsigned int count_20mA=0;
	unsigned int count_4mA =0;
	unsigned int count_0mA =0;
#else
	extern ao1 AO1;
	extern ao2 AO2;
	// 아날로그 출력
	extern	int		Anaolg_Output_mA_x1;
	extern unsigned int count;
	extern unsigned int count_20mA;
	extern unsigned int count_4mA;
	extern unsigned int count_0mA;
	extern void Analog_Output_Monitoring();
#endif

