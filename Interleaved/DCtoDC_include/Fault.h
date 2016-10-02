
// 파라미터 오류 코드 	: 1 ~ 799

#define TRIP_MOTOR_RPM_UNDER		1002
#define TRIP_POWER_FACTOR_UNDER		1001
#define TRIP_POWER_FACTOR_OVER		1000

#define TRIP_OVER_LOAD_TIME			201	// 11 RMS 값으로 입력하는 것으로 수정 
#define TRIP_OVER_CURRENT			301	// 11 RMS 값으로 입력하는 것으로 수정 

#define CODE_OVER_VOLTAGE_LEVEL		302	// 12 DC link Voltage OV1은 자동으로 계산 할 것   
#define TRIP_UNDER_VOLT				303	// 13 수정 
#define OVER_SPEED_FAULT			304	// 14 수정 
#define CODE_ETHERMAL_LEVEL			305	// 15 New 수정 
#define CODE_PRE_CHARGE_TIME		306	// 초기충전 시간 
#define CODE_I_MAX_COEFF			307	// 
#define CODE_OVER_CURRENT_TIME		308	// 
#define CODE_SPEED_DETECTION_ERROR	309 // Encoder Pulse Error

// input voltage error code
#define	ERR_OVER_VOLTAGE_IN			310
#define	ERR_UNDER_VOLTAGE_IN		311

#define ERR_IGBT_UH							811
#define ERR_IGBT_UL							812
#define ERR_IGBT_VH							813
#define ERR_IGBT_VL							814
#define ERR_IGBT_WH							815
#define ERR_IGBT_WL							816
#define ERR_IGBT_DB							817
#define ERR_IGBT_RESET						818

#define FAULT_DRIVER						819
#define FAULT_DB							820
#define FAULT_ZC							821

#define	ERR_OC0								821
#define	ERR_OC								822
#define	ERR_UC0								823
#define	ERR_OV0								824
#define	ERR_OV								825
#define	ERR_UV0								826
#define	ERR_UV								827
#define	ERR_OS0								828
#define	ERR_OS								829

#define	ERR_SUV								831	
#define	ERR_SOV								832
#define	ERR_SOC								833
#define ERR_OVER_CURRENT_U_PHASE			834 
#define ERR_OVER_CURRENT_V_PHASE			835 
#define ERR_OVER_CURRENT_W_PHASE			836
#define ERR_SPEED_DETECT					837	// bayasaa 2010/06/18
#define ERR_SENSORLESS						838 // bayasaa 2010/06/18

#define	ERR_NAME_PLATE_PAR_MISMATCH			841
#define	ERR_NAME_PLATE_PAR_MISMATCH0		842
#define	ERR_NAME_PLATE_PAR_MISMATCH1		843

#define	ERR_PM_Is							844
#define	ERR_GM_Is							845
#define	ERR_K_Damp_Is						846


#define	ERR_Tr_Over							851
#define	ERR_Tr_Under						852
#define	ERR_sigma_Under						853
#define	ERR_sigma_Over						854
#define	ERR_Ki_Is_Under						856
#define	ERR_Kp_Is_Over						857
#define	ERR_Kp_Is_Under						858

#define	ERR_EXCITATION_TIME					859

// SCI 
#define ERR_SCI_CMD_ADDR_GROUP_UNDER		861
#define ERR_SCI_CMD_ADDR_GROUP_OVER			862
#define ERR_SCI_CMD_ADDR_1ST_UNDER			863
#define ERR_SCI_CMD_ADDR_1ST_OVER			864
#define ERR_SCI_CMD_ADDR_2ND_UNDER			865
#define ERR_SCI_CMD_ADDR_2ND_OVER			867

// 오토튜닝 오류
#define	ERR_Req_Under						920
#define	ERR_Req_Over						921
#define	ERR_Leq_Under0						923
#define	ERR_Leq_Over0						924
#define	ERR_Rs_Under						925
#define	ERR_Rs_Over							926
#define	ERR_Ls_Over0						927
#define	ERR_Ls_Under0						928	
#define	ERR_Ls_Under1						929
#define	ERR_Ls_Over1						930
#define	ERR_Leq_Over1						931
#define	ERR_Rr_Over							932
#define	ERR_Rr_Under						933
#define	ERR_Jm_Under						934
#define	ERR_Jm_Over							945
#define	ERR_WRONG_INTERRUPT_CMD				950

// 하드웨어 프로텍션 (TMS320F240)
#define	ERR_PRECHARGING_FAIL				960		// 초기 충전 실패 
#define	ERR_PWM								961
#define	ERR_HOC								962
#define	ERR_HOV								963
#define	ERR_HUV								964
#define	ERR_OVER_HEAT						965

#define	ERR_EXT_TRIP						966

#define	ERR_PWM_CNT							971		// 스위칭 주기의 카운터 값 오류 

#define	ERR_INV_DISABLE						972		// 운전중 인버터 디스에이블 

#define Fault_Check_Enable	1													// 2010.05.12
	
//--------------------------------------//

// Fault 는 상위 bit->하위 bit 순으로 배치함 
// 외부인력 요청 (박병훈)
// Fault 1 Group
struct FAULT1_BITS	// bits   description 
{          
	Uint16	OC_A:				1;		// "F16 OC_A    "			; A상 과전류 : 소프트웨어 검출
	Uint16	U_Cap_OT:			1;		// "F15 U-Cap OT    "		; 부하 과열 : 하드웨어 보호
	Uint16	U_Cap_OV_H:			1;		// "F14 U-Cap OV    "		; 부하 과전압 : 하드웨어 보호
	Uint16	U_Cap_V_Sens:		1;		// "F13 U-Cap V_Sens"		; 전압센서
	Uint16	U_Cap_OV:			1;		// "F12 U-Cap OV    "		; 부하 과전압 : 소프트웨어 보호
	Uint16	Out_of_Ctrl:		1;		// "F11 Out_of_Ctrl "		; 제어 불능
	Uint16	Over_Speed:			1;		// "F10 Over_Speed  "		; 모터 과속 	
	Uint16	Low_Bus_Volt:		1;		// "F9 Low_Bus_Volt "		; 소프트웨어 저전압 (순시 비교)
	Uint16	Over_Volt_H:		1;		// "F8 Over_Volt [H]"		; 하드웨어 과전압
	Uint16	Over_Bus_Volt:		1;		// "F7 Over_Bus_Volt"		; 소프트웨어 과전압 (순시 비교)
	Uint16	Under_Current:		1;		// "F6 Under_Current"		; 저전류 : 결선 이상
	Uint16	Zero_Seq_I_H:		1;		// "F5 Zero_Seq_I[H]"		; 영상전류 -> 하드웨어 검출
	Uint16	Zero_Seq_I:			1;		// "F4 Zero_Seq_I   "		; 영상전류 -> 소프트웨어 검출
	Uint16	Over_Curr_H:		1;		// "F3 Over_Curr [H]"		; 하드웨어 과전류
	Uint16	Over_Current:		1;		// "F2 Over_Current "		; 소프트웨어 과전류 (순시 비교)
	Uint16	Over_Load:			1;		// "F1 Over_Load    "		; 소프트웨어 과부하 (시간 누적)
};

union FAULT1_REG 
{
   Uint16					all;
   struct	FAULT1_BITS		bit;
}; 

// Fault 2 Group
struct FAULT2_BITS	// bits   description 
{          
	Uint16	Line_OPEN:			1;		// "F32 Line_OPEN   "		; 라인 결상
	Uint16	Line_UV:			1;		// "F31 Line_UV     "		; 입력 라인 저전압
	Uint16	SyncComm_Err:		1;		// "F30 SyncComm_Err"	; 동기 통신 오류
	Uint16	Keypad_Error:		1;		// "F29 Keypad_Error"	; 키패드 통신 오류 
	Uint16	Motor_Lock:			1;		// "F28 Motor Lock  "	; 모터 구속
	Uint16	Open_Phase:			1;		// "F27 Open Phase  "	; 결상
	Uint16	No_Current:			1;		// "F26 No_Current  "	; 무전류 : 무결선 또는 게이트 드라이브 전원 이상
	Uint16	Ext_Fault:			1;		// "F25 Ext_Fault   "	; 외부 결함
	Uint16	GateDrv_Pwr:		1;		// "F24 GateDrv_Pwr "	; 게이트 구동전원 이상
	Uint16	Charging_Err:		1;		// "F23 Charging_Err"	; 초기 충전 실패
	Uint16	Device_Short:		1;		// "F22 Device_Short"	; 게이트 드라이브 오류
	Uint16	Over_Temp:			1;		// "F21 Over_Temp   "	; 방열판 과열
	Uint16	UV_IN:				1;		// "F20 UV_IN    "		; 입력 저전압 : 소프트웨어 검출
	Uint16	OV_IN:				1;		// "F19 OV_IN    "		; 입력 과전압 : 소프트웨어 검출
	Uint16	OC_C:				1;		// "F18 OC_C "			; C상 과전류 : 소프트웨어 검출
	Uint16	OC_B:				1;		// "F17 OC_B    "		; A상 과전류 : 소프트웨어 검출
};

union FAULT2_REG 
{
   Uint16					all;
   struct	FAULT2_BITS		bit;
};
// Fault 3 Group
struct FAULT3_BITS	// bits   description 
{
	Uint16	rsvd1:				9;		// bit . 1~9	"		; 
	Uint16	Master_Fault:		1;		// "F39 Master_Fault"		; 마스터 폴트
	Uint16	F_Logic2:			1;		// "F38 F_Logic 2   "		; 폴트로 정의되는 로직
	Uint16	F_Logic1:			1;		// "F37 F_Logic 1   "		; 폴트로 정의되는 로직
	Uint16	Profibus_Err:		1;		// "F36 Profibus_Err"		; 프로피버스 통신 오류
	Uint16	Line_Unbal:			1;		// "F35 Line_Unbal  "		; 라인 불평형
	Uint16	Line_Seq_Err:		1;		// "F34 Line_Seq_Err"		; 라인 시퀀스 오류
	Uint16	Line_OV:			1;		// "F33 Line_OV     "		; 라인 과전압
};

union FAULT3_REG 
{
   Uint16					all;
   struct	FAULT3_BITS		bit;
};


// Fault_Neglect 1 Group
struct FAULT_NEGLECT1_BITS	// bits   description 
{          
	Uint16	OC_A:				1;		// "F16 OC_A    "			; A상 과전류 : 소프트웨어 검출
	Uint16	U_Cap_OT:			1;		// "F15 U-Cap OT    "		; 부하 과열 : 하드웨어 보호
	Uint16	U_Cap_OV_H:			1;		// "F14 U-Cap OV    "		; 부하 과전압 : 하드웨어 보호
	Uint16	U_Cap_V_Sens:		1;		// "F13 U-Cap V_Sens"		; 전압센서
	Uint16	U_Cap_OV:			1;		// "F12 U-Cap OV    "		; 부하 과전압 : 소프트웨어 보호
	Uint16	Out_of_Ctrl:		1;		// "F11 Out_of_Ctrl "		; 제어 불능
	Uint16	Over_Speed:			1;		// "F10 Over_Speed  "		; 모터 과속 	
	Uint16	Low_Bus_Volt:		1;		// "F9 Low_Bus_Volt "		; 소프트웨어 저전압 (순시 비교)
	Uint16	Over_Volt_H:		1;		// "F8 Over_Volt [H]"		; 하드웨어 과전압
	Uint16	Over_Bus_Volt:		1;		// "F7 Over_Bus_Volt"		; 소프트웨어 과전압 (순시 비교)
	Uint16	Under_Current:		1;		// "F6 Under_Current"		; 저전류 : 결선 이상
	Uint16	Zero_Seq_I_H:		1;		// "F5 Zero_Seq_I[H]"		; 영상전류 -> 하드웨어 검출
	Uint16	Zero_Seq_I:			1;		// "F4 Zero_Seq_I   "		; 영상전류 -> 소프트웨어 검출
	Uint16	Over_Curr_H:		1;		// "F3 Over_Curr [H]"		; 하드웨어 과전류
	Uint16	Over_Current:		1;		// "F2 Over_Current "		; 소프트웨어 과전류 (순시 비교)
	Uint16	Over_Load:			1;		// "F1 Over_Load    "		; 소프트웨어 과부하 (시간 누적)
};


union FAULT_NEGLECT1_REG 
{
   Uint16							all;
   struct	FAULT_NEGLECT1_BITS		bit;
};  

// Fault_Neglect 2 Group
struct FAULT_NEGLECT2_BITS	// bits   description 
{          
	Uint16	Line_OPEN:			1;		// "F32 Line_OPEN   "		; 라인 결상
	Uint16	Line_UV:			1;		// "F31 Line_UV     "		; 입력 라인 저전압
	Uint16	SyncComm_Err:		1;		// "F30 SyncComm_Err"	; 동기 통신 오류
	Uint16	Keypad_Error:		1;		// "F29 Keypad_Error"	; 키패드 통신 오류 
	Uint16	Motor_Lock:			1;		// "F28 Motor Lock  "	; 모터 구속
	Uint16	Open_Phase:			1;		// "F27 Open Phase  "	; 결상
	Uint16	No_Current:			1;		// "F26 No_Current  "	; 무전류 : 무결선 또는 게이트 드라이브 전원 이상
	Uint16	Ext_Fault:			1;		// "F25 Ext_Fault   "	; 외부 결함
	Uint16	GateDrv_Pwr:		1;		// "F24 GateDrv_Pwr "	; 게이트 구동전원 이상
	Uint16	Charging_Err:		1;		// "F23 Charging_Err"	; 초기 충전 실패
	Uint16	Device_Short:		1;		// "F22 Device_Short"	; 게이트 드라이브 오류
	Uint16	Over_Temp:			1;		// "F21 Over_Temp   "	; 방열판 과열
	Uint16	UV_IN:				1;		// "F20 UV_IN    "		; 입력 저전압 : 소프트웨어 검출
	Uint16	OV_IN:				1;		// "F19 OV_IN    "		; 입력 과전압 : 소프트웨어 검출
	Uint16	OC_C:				1;		// "F18 OC_C "			; C상 과전류 : 소프트웨어 검출
	Uint16	OC_B:				1;		// "F17 OC_B    "		; A상 과전류 : 소프트웨어 검출
};

union FAULT_NEGLECT2_REG 
{
   Uint16							all;
   struct	FAULT_NEGLECT2_BITS		bit;
};

// Fault_Neglect 3 Group
struct FAULT_NEGLECT3_BITS	// bits   description 
{
	Uint16	rsvd1:				9;		// bit . 1~9	"		; 
	Uint16	Master_Fault:		1;		// "F39 Master_Fault"		; 마스터 폴트
	Uint16	F_Logic2:			1;		// "F38 F_Logic 2   "		; 폴트로 정의되는 로직
	Uint16	F_Logic1:			1;		// "F37 F_Logic 1   "		; 폴트로 정의되는 로직
	Uint16	Profibus_Err:		1;		// "F36 Profibus_Err"		; 프로피버스 통신 오류
	Uint16	Line_Unbal:			1;		// "F35 Line_Unbal  "		; 라인 불평형
	Uint16	Line_Seq_Err:		1;		// "F34 Line_Seq_Err"		; 라인 시퀀스 오류
	Uint16	Line_OV:			1;		// "F33 Line_OV     "		; 라인 과전압 
};

union FAULT_NEGLECT3_REG 
{
   Uint16							all;
   struct	FAULT_NEGLECT3_BITS		bit;
};

typedef volatile struct POINT_DEFINE
{
	union	FAULT1_REG				Fault1;
	union	FAULT2_REG				Fault2;
	union	FAULT3_REG				Fault3;
	union	FAULT_NEGLECT1_REG		Fault_Neglect1;
	union	FAULT_NEGLECT2_REG		Fault_Neglect2;
	union	FAULT_NEGLECT3_REG		Fault_Neglect3;
}POINT; 

#define nFLT2_ON				GpioDataRegs.GPASET.bit.GPIO13 = 1;
#define nFLT2_OFF				GpioDataRegs.GPACLEAR.bit.GPIO13 = 1; 

/*
struct TRIP_INFO_DEFINE {
	int		CODE;				// 1
	float	CURRENT;			// 5
	float	VDC;				// 6
	float	HZ;					// 7
	float	DATA;				// 4
	char 	TIME[30];			// 3
	char 	MSG[40];			// 2
};
*/
typedef struct 
{
	int		CODE;			// 
	float	CURRENT;		// 5
	float	VDC_IN;			// 6
	float	VDC_OUT;		// 7
	float	TEMP;
	float	DATA;			// 4
	char 	TIME;			// 3
}	TRIP_INFO_DEFINE;


//typedef struct TRIP_INFO_DEFINE TRIP_INFO;


#ifdef _FAULT_
	TRIP_INFO_DEFINE TRIP_INFO;
	POINT point;
	// for REALSYS MONITORING
	int Fault_count = 0;
	int Fault_State = 0;
	int flagcontroll = 0;
	int flagFOCC = 0;  
	int flagcontrol = 0;

	int flagFOC = 0;
	int flagGT1_ENA = 0;
	int flagGT2_ENA = 0;
	int flagPWM_CTR = 0;
	int flagvar_rst = 0;
	int flagadoffset_complete = 0;
	int flagencrst_complete = 0;
	int flagencrst_start = 0;
	int flagccseq = 0; 
/////////////////////////////////////////////////////////////////////
	// G5 Protection Setup
	unsigned int Curr_Lim	 = 145;		// P5.0
	unsigned int Max_Con_cur = 100;		// P5.7 
	unsigned int Over_Load	 = 135;		// P5.8
	unsigned int Over_Load_Time = 0;
	unsigned int OV_Time = 0;
	unsigned int OC_Trip	 = 220;		// P5.11
	unsigned int OV_Ltd_Fn	= 0;		// P5.13
	unsigned OV_Limit	= 580.;				// P5.14
	unsigned int OV_set = 0, UV_set = 0, OVin_set = 0, UVin_set = 0, OV_Temp = 0;
	unsigned int DC_Build_Up_delay_cnt = 0, DC_Build_Up_delay_set = 0, UV_Check_Enable = 0;
/////////////////////////////////////////////////////////////////////
	int first1 = 0;
	int FaultInfo = 0, Fault_Check = 0;
	int Fault_Data = 0;
	int Fault_Time = 0;
	int	Fault_ret = 0;
	float OL_TimeOver_Count = 0;
	int Over_Temp_Flag = 0;
	int Temp_Retry = 0;
	float MaxCon_Curr_Count = 0;
	float OverVoltCount = 0;
	float UnderVoltCount = 0;
	float OverVoltinCount = 0;
	float UnderVoltinCount = 0;
	float OverHeatCount = 0;
	int first = 0;

	int fault_chk();
	void Fault_Recording(int Fault_cnt);
	void TripProc(void);
	int CheckOverCurrent( );
	int CheckOverVolt( );
	int CheckUnderVolt( );
	int CheckOverVolt_in( );
	int CheckUnderVolt_in( );
	int CheckOverHeat( );
	int CheckFaultIGBT( );
	int CheckFaultDriver( );
	int CheckExtTrip( ); 

//int TripCode = 0;

//FAULT	fault;
#else
	extern	TRIP_INFO_DEFINE TRIP_INFO;
	extern 	POINT point;
// for REALSYS MONITORING
	extern int Fault_count;
	extern int Fault_State;
	extern int flagcontroll;
	extern int flagFOCC;  
	extern int flagcontrol;
	extern int faultOC_set;
	extern int flagFOC;
	extern int flagGT1_ENA;
	extern int flagGT2_ENA;
	extern int flagPWM_CTR;
	extern int flagvar_rst;
	extern int flagadoffset_complete;
	extern int flagencrst_complete;
	extern int flagencrst_start;
	extern int flagccseq; 
/////////////////////////////////////////////////////////////////////
	// G5 Protection Setup
	extern unsigned int Curr_Lim;		// P5.0
	extern unsigned int Max_Con_cur;	// P5.7 
	extern unsigned int Over_Load;		// P5.8
	extern unsigned int Over_Load_Time;
	extern unsigned int OV_Time;
	extern unsigned int OC_Trip;		// P5.11
	extern unsigned int OV_Ltd_Fn;		// P5.13
	extern float OV_Limit;				// P5.14
	extern unsigned int OV_set, UV_set, OVin_set, UVin_set, OV_Temp;
	extern unsigned int DC_Build_Up_delay_cnt, DC_Build_Up_delay_set, UV_Check_Enable;
/////////////////////////////////////////////////////////////////////


extern int FaultInfo, Fault_Check;
extern int Fault_Data;
extern int Fault_Time;
extern int Fault_ret;


extern int first1;
extern long OL_TimeOver_Count;
extern int Over_Temp_Flag;
extern int Temp_Retry;
extern float MaxCon_Curr_Count;
extern float OverVoltCount;
extern float UnderVoltCount;
extern float OverVoltinCount;
extern float UnderVoltinCount;
extern float OverHeatCount;

extern int first;

extern int fault_chk();
extern void Fault_Recording(int Fault_cnt);
extern void TripProc(void);
extern int CheckOverCurrent( );
extern int CheckOverVolt( );
extern int CheckUnderVolt( );
extern int CheckOverVolt_in( );
extern int CheckUnderVolt_in( );
extern int CheckOverHeat( );
extern int CheckFaultIGBT( );
extern int CheckFaultDriver( );
extern int CheckExtTrip( ); 

//extern int TripCode;
#endif




