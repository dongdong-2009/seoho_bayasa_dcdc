//#include	<All_Header.h>
//#include	<All_Extern_Variables.h> 
#include "sci_bc.h"
#include "main_def.h"

void Read_Data_Registers(int Par_index)
{
	switch(Par_index)
	{
		case 200 :	Data_Registers[Par_index] = ( Device_Info			 	=	Data_Registers[Par_index]);	break;
		case 201 :	Data_Registers[Par_index] = ( Software_Number			=	Data_Registers[Par_index]);	break;
		case 202 :	Data_Registers[Par_index] = ( Software_Version			=	Data_Registers[Par_index]);	break; 
		case 280 :	Data_Registers[Par_index] = ( Run_Stop_Src				=	Data_Registers[Par_index]);	break;
		case 281 :	Data_Registers[Par_index] = ( Ref_method				=	Data_Registers[Par_index]);	break;

		case 2300:	Data_Registers[Par_index] = ( Local_Remote 				=	Data_Registers[Par_index]);	break;
		case 2306:	Data_Registers[Par_index] = ( Run_Stop					=	Data_Registers[Par_index]);	break;
		case 2484:	Data_Registers[Par_index] = ( FAULT_RESET				=	Data_Registers[Par_index]);	break;

		// Analog Output 
		case 940:	Data_Registers[Par_index] = ( AO1.P00_Output_selection	=	BOUND(Data_Registers[Par_index],ANALOG_OUT_NUM, 0.)	);	break;			
		case 941:	Data_Registers[Par_index] = ( AO1.P01_Type				= 	BOUND(Data_Registers[Par_index],OUT_TYPE_NUM, 0.)	);	break;
		case 942:	Data_Registers[Par_index] = ( AO1.P02_Adjustment_0mA	= 	BOUND(Data_Registers[Par_index],2000, 0.	)		);	break;	// 0~0.2 x10000 --> 0~2000
		case 943:	Data_Registers[Par_index] = ( AO1.P03_Adjustment_4mA	= 	BOUND(Data_Registers[Par_index],3000, 1500.	)	 	);	break;	// 0.15~0.3 x10000 --> 1500~3000
		case 944:	Data_Registers[Par_index] = ( AO1.P04_Adjustment_20mA	= 	BOUND(Data_Registers[Par_index],1000, 500. 	)		);	break;	// 0.5~1.0  x1000  --> 500~1000;	break;
		case 945:	Data_Registers[Par_index] = ( AO1.P05_Max_output_x1		=	BOUND(Data_Registers[Par_index],300, 0.		)		);	break;	// 0~300
		case 946:	Data_Registers[Par_index] = ( AO1.P06_Inversion			=	BOUND(Data_Registers[Par_index],1, 0.		)		);	break;	// 0 or 1

		case 947:	Data_Registers[Par_index] = ( AO2.P00_Output_selection	= 	BOUND(Data_Registers[Par_index],ANALOG_OUT_NUM, 0.) );	break;			
		case 948:	Data_Registers[Par_index] = ( AO2.P01_Type				=	BOUND(Data_Registers[Par_index],OUT_TYPE_NUM, 0.)	);	break;
		case 949:	Data_Registers[Par_index] = ( AO2.P02_Adjustment_0mA	= 	BOUND(Data_Registers[Par_index],2000, 0.	)		);	break;	// 0~0.2 x10000 --> 0~2000
		case 950:	Data_Registers[Par_index] = ( AO2.P03_Adjustment_4mA	= 	BOUND(Data_Registers[Par_index],3000, 1500.	)		);	break;	// 0.15~0.3 x10000 --> 1500~3000
		case 951:	Data_Registers[Par_index] = ( AO2.P04_Adjustment_20mA	= 	BOUND(Data_Registers[Par_index],1000, 500. 	)		);	break;	// 0.5~1.0  x1000  --> 500~1000;	break;
		case 952:	Data_Registers[Par_index] = ( AO2.P05_Max_output_x1		=	BOUND(Data_Registers[Par_index],300, 0.		)		);	break;	// 0~300
		case 953:	Data_Registers[Par_index] = ( AO2.P06_Inversion			=	BOUND(Data_Registers[Par_index],1, 0.		)		);	break;	// 0 or 1 

		case 1870:	Data_Registers[Par_index] = 1e-2 * ( Fsw		= 1e+2* (float)(BOUND(Data_Registers[Par_index], 65, 35))		);	break;	// 3500 ~ 6500kHz
		case 2301:	Data_Registers[Par_index] = ( Vdc_set_user		= 		(float)(BOUND(Data_Registers[Par_index], 700,600))		);	break;	// 600 ~ 700 V
		case 1872:	Data_Registers[Par_index] = ( V_rate			= 				BOUND(Data_Registers[Par_index], 460,210)		);	break;	// 210 ~ 460 V
		case 1873:	Data_Registers[Par_index] = ( P_rate			= 				BOUND(Data_Registers[Par_index], 5000, 2000	)	);	break;	// 200 ~ 500 kW
//		case 1874:	Data_Registers[Par_index] = 1e+4 * ( R_L		= 1e-4* (float)Data_Registers[Par_index]); break;//(float)(BOUND(Data_Registers[Par_index],200, 5)		)	);	break;	// 0.5 ~ 20mOhm
		case 1874:	R_L	= 1e-4 * Data_Registers[Par_index];			break;	// 0.5 ~ 20mOhm
		case 1875:	Data_Registers[Par_index] = 1e+4 * ( La			= 1e-4* (float)(BOUND(Data_Registers[Par_index],50, 4)	)		);	break;	// 0.4 ~ 5mH
		case 1876:	Data_Registers[Par_index] = 1e+1 * ( Sens_time_Vin=	1e-1*		BOUND(Data_Registers[Par_index],500,10	)		);	break;	// 1 ~ 50mS
		case 1877:	Data_Registers[Par_index] = 1e+1 * ( Kp_Vdc_factor= 1e-1*(float)BOUND(Data_Registers[Par_index],10000,0.)		);	break;	// 0~1000%
		case 1878:	Data_Registers[Par_index] = 1e+1 * ( Ki_Vdc_factor=	1e-1*(float)BOUND(Data_Registers[Par_index],10000,0.)		);	break;
		case 1879:	Data_Registers[Par_index] = 1e+1 * ( Kp_Idc_factor= 1e-1*(float)BOUND(Data_Registers[Par_index],10000,0.)		);	break;
		case 1880:	Data_Registers[Par_index] = 1e+1 * ( Ki_Idc_factor=	1e-1*(float)BOUND(Data_Registers[Par_index],10000,0.)		);	break;
		case 1881:	Data_Registers[Par_index] = ( vc_cnt_set		=				BOUND(Data_Registers[Par_index], 10, 1	)		);	break;	// 1~10 time
		case 1882:	Data_Registers[Par_index] = 1e+6 * ( Cin 		=	1e-6* (float)BOUND(Data_Registers[Par_index],35000, 0.)		);	break;	// 0~35000uF
		case 1883:	Data_Registers[Par_index] = 1e+6 * ( Cout		=	1e-6* (float)BOUND(Data_Registers[Par_index],35000, 0.)		);	break;	// 0~35000uF
		case 1884:	Data_Registers[Par_index] = 1e+1 * ( Fnv		=	1e-1* (float)BOUND(Data_Registers[Par_index], 10000, 0.)	);	break;	// 0~1000Hz
		case 1885:	Data_Registers[Par_index] = 1e+1 * ( Fnc		=	1e-1* (float)BOUND(Data_Registers[Par_index], 10000, 0.)	);	break;	// 0~1000Hz
		case 1886:	Data_Registers[Par_index] = ( OV_set			=				BOUND(Data_Registers[Par_index], 800, 0.	)	);	break;	// 0~800V
		case 1887:	Data_Registers[Par_index] = ( UV_set			= 				BOUND(Data_Registers[Par_index], 1000, 0.	)	);	break;	// 0~1000V
		case 1888:	Data_Registers[Par_index] = ( OVin_set			=				BOUND(Data_Registers[Par_index], 800, 0.	)	);	break;	// 0~800V
		case 1889:	Data_Registers[Par_index] = ( UVin_set			=				BOUND(Data_Registers[Par_index], 1000, 0.	)	);	break;	// 0~1000V
		case 1890:	Data_Registers[Par_index] = ( I_rate			=				BOUND(Data_Registers[Par_index], 1000, 0.	)	);	break;	// 0~1000A
		case 1891:	Data_Registers[Par_index] = 1e+1 * ( OC_Trip	=	1e-1* 		BOUND(Data_Registers[Par_index], 3500, 0.	)	);	break;	// 0~350%
		case 1892:	Data_Registers[Par_index] = 1e+1 * ( Max_Con_cur=	1e-1*		BOUND(Data_Registers[Par_index], 2500, 0.	)	);	break;	// 0~250%
		case 1893:	Data_Registers[Par_index] = 1e+1 * ( Over_Load	=	1e-1*		BOUND(Data_Registers[Par_index], 2500, 0.	)	);	break;	// 0~250%
		case 1894:	Data_Registers[Par_index] = 1e+1 * ( Over_Load_Time	= 1e-1*		BOUND(Data_Registers[Par_index], 3000, 0.	)	);	break;	// 0~300sec
		case 1895:	Data_Registers[Par_index] = 1e+1 * ( OV_Time	=	1e-1*		BOUND(Data_Registers[Par_index], 3000, 0.	)	);	break;	// 0~300sec
		case 1896:	Data_Registers[Par_index] = 1e+1 * ( OV_Temp	=	1e-1*		BOUND(Data_Registers[Par_index], 850, 200.	)	);	break;	// 20~85 deg

/*		case 1897:	Fnv_max=		1e-1*		Data_Registers[Par_index];	break;
		case 1898:	Fnv_min=		1e-1*		Data_Registers[Par_index];	break;
		case 1899:	Fnc_max=		1e-1*		Data_Registers[Par_index];	break;
		case 1900:	Fnc_min=		1e-1*		Data_Registers[Par_index];	break;
*/		
	}
}

void Write_Data_Registers_Online()
{
	Data_Registers[2270]=			Run_Stop_Status;

	Data_Registers[2300]=					Local_Remote;
	Data_Registers[2301]= 					(int)Vdc_set_user;
	Data_Registers[2306]=					Run_Stop;

	Data_Registers[2310]=		(int)Vdc_input_LPF;					// M1.0.0
	Data_Registers[2311]=		Under_Limit((int)Iinput_LPF);		// M1.0.1
	Data_Registers[2312]=					(int)Vdc_out_LPF;		// M1.0.2
	Data_Registers[2313]=		Under_Limit((int)Ias_LPF);			// M1.0.3
	Data_Registers[2314]=		Under_Limit((int)Ibs_LPF);			// M1.0.4
	Data_Registers[2315]= 		Under_Limit((int)Ics_LPF);			// M1.0.5
	Data_Registers[2316]=		Under_Limit((int)Idc_ref_LPF);		// M1.0.6
	Data_Registers[2317]=					(int)Vdc_Error;			// M1.0.7
	Data_Registers[2318]=		Under_Limit((int)(1e-2*Power_in));	// M1.0.8
	Data_Registers[2319]=		Under_Limit((int)(1e-2*Power_out));	// M1.0.9
	Data_Registers[2320]=		(int)Idc_Error_a;					// M1.0.10
	Data_Registers[2321]=		(int)Idc_Error_b;					// M1.0.11
	Data_Registers[2322]=		(int)Idc_Error_c;					// M1.0.12
	Data_Registers[2323]=		(int)(10.*Temperature);				// M1.0.13

	Data_Registers[2330]=		State_Index;

	Data_Registers[2340]=		255;								// M1.1.0
	Data_Registers[2341]=		255;								// M1.1.1
	Data_Registers[2342]=		255;								// M1.1.2
	Data_Registers[2343]=		255;								// M1.1.3
	Data_Registers[2344]=		Anaolg_Output_mA_x1;				// M1.1.4

	Data_Registers[2352]=		Run_Stop_Src;	// M1.2.2
	Data_Registers[2353]=		Ref_method;		// M1.2.3
	Data_Registers[2354]=		P_rate;			// M1.2.4
	Data_Registers[2355]=		Drive_Voltage;	// M1.2.5

	Data_Registers[1874]=		(int)(1e+4 * R_L);
	
	Data_Registers[2376]=		point.Fault1.all;
	Data_Registers[2377]=		point.Fault2.all;
	Data_Registers[2379]= 		Fault_count;
	Data_Registers[2484]=		FAULT_RESET;
	Data_Registers[2485]=		FAULT_RESET_COMPLETE;
	Data_Registers[1871]=		(int)(Vdc_set_user);

	// Analog Output ฐüทร Parameter back monitoring
	Data_Registers[940]= AO1.P00_Output_selection;
	Data_Registers[941]= AO1.P01_Type;
	Data_Registers[942]= AO1.P02_Adjustment_0mA;
	Data_Registers[943]= AO1.P03_Adjustment_4mA;
	Data_Registers[944]= AO1.P04_Adjustment_20mA;
	Data_Registers[945]= AO1.P05_Max_output_x1;
	Data_Registers[946]= AO1.P06_Inversion;
}

void Write_Data_Registers_Offline(int Par_index)
{
	switch(Par_index)
	{
		case 200 :	Data_Registers[Par_index]=Device_Info;				break;
		case 201 :	Data_Registers[Par_index]=Software_Number;			break;
		case 202 :	Data_Registers[Par_index]=Software_Version;			break; 
		case 280 :	Data_Registers[Par_index]=Run_Stop_Src;				break;
		case 281 :	Data_Registers[Par_index]=Ref_method;				break;

		case 940:	Data_Registers[Par_index]=AO1.P00_Output_selection; break;
		case 941:	Data_Registers[Par_index]=AO1.P01_Type; 			break;
		case 942:	Data_Registers[Par_index]=AO1.P02_Adjustment_0mA; 	break;
		case 943:	Data_Registers[Par_index]=AO1.P03_Adjustment_4mA; 	break;
		case 944:	Data_Registers[Par_index]=AO1.P04_Adjustment_20mA; 	break;
		case 945:	Data_Registers[Par_index]=AO1.P05_Max_output_x1;	break;
		case 946:	Data_Registers[Par_index]=AO1.P06_Inversion; 		break;
		case 947:	Data_Registers[Par_index]=AO2.P00_Output_selection; break;
		case 948:	Data_Registers[Par_index]=AO2.P01_Type; 			break;
		case 949:	Data_Registers[Par_index]=AO2.P02_Adjustment_0mA; 	break;
		case 950:	Data_Registers[Par_index]=AO2.P03_Adjustment_4mA; 	break;
		case 951:	Data_Registers[Par_index]=AO2.P04_Adjustment_20mA;	break;
		case 952:	Data_Registers[Par_index]=AO2.P05_Max_output_x1;	break;
		case 953:	Data_Registers[Par_index]=AO2.P06_Inversion; 		break;

		case 2351:	Data_Registers[Par_index]=Control_method;			break;
		case 2354:	Data_Registers[Par_index]=P_rate;					break;
		case 2355:	Data_Registers[Par_index]=Drive_Voltage;			break;

		case 1870:	Data_Registers[Par_index]=(int)(1e-2*Fsw);			break;	// kHz
		case 1871:	Data_Registers[Par_index]=(int)(Vdc_set_user);		break;	// kHz
		case 2301:	Data_Registers[Par_index]=(int)Vdc_set_user;		break;	// V
		case 1872:	Data_Registers[Par_index]=V_rate;					break;	// V
		case 1873:	Data_Registers[Par_index]=P_rate;					break;	// kW
		case 1874:	Data_Registers[Par_index]=(int)(1e+4*R_L);			break;	// mOhm
		case 1875:	Data_Registers[Par_index]=(int)(1e+4*La);			break;	// mH
		case 1876:	Data_Registers[Par_index]=10*Sens_time_Vin;			break;	// s
		case 1877:	Data_Registers[Par_index]=(int)(10.*Kp_Vdc_factor);	break;	// %
		case 1878:	Data_Registers[Par_index]=(int)(10.*Ki_Vdc_factor);	break;	// %
		case 1879:	Data_Registers[Par_index]=(int)(10.*Kp_Idc_factor);	break;	// %
		case 1880:	Data_Registers[Par_index]=(int)(10.*Ki_Idc_factor);	break; 	// %
		case 1881:	Data_Registers[Par_index]=vc_cnt_set;				break;	// 
		case 1882:	Data_Registers[Par_index]=(int)(1e+6*Cin);			break;	// uF
		case 1883:	Data_Registers[Par_index]=(int)(1e+6*Cout);			break;	// uF
		case 1884:	Data_Registers[Par_index]=(int)(10.*Fnv);			break;	// Hz
		case 1885:	Data_Registers[Par_index]=(int)(10.*Fnc);			break;	// Hz

		case 1886:	Data_Registers[Par_index]= OV_set; 					break;	// V
		case 1887:	Data_Registers[Par_index]= UV_set; 					break;	// V
		case 1888:	Data_Registers[Par_index]= OVin_set;				break;	// V
		case 1889:	Data_Registers[Par_index]= UVin_set;				break;	// V
		case 1890:	Data_Registers[Par_index]= I_rate;					break;	// A
		case 1891:	Data_Registers[Par_index]= 10 * OC_Trip;			break;	// %
		case 1892:	Data_Registers[Par_index]= 10 * Max_Con_cur;		break;	// %
		case 1893:	Data_Registers[Par_index]= 10 * Over_Load;			break;	// %
		case 1894:	Data_Registers[Par_index]= 10 * Over_Load_Time;		break;	// s
		case 1895:	Data_Registers[Par_index]= 10 * OV_Time;			break;	// s
		case 1896:	Data_Registers[Par_index]= 10 * OV_Temp;			break;	// C
		default:	Data_Registers[Par_index]=0;
	}
}

