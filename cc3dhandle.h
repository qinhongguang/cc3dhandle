#ifndef __CC3DHANDLE_H__
#define __CC3DHANDLE_H__


typedef struct {
	uint8_t intervene_ch_index;		//干预通道标志
	uint8_t input_index;		    //输入通道标志
	bool enable;					//0 or 1使能
	uint16_t threshold;				//1000 ~ 2000门限值
	//uint8_t gyro;					//0 ~ 8陀螺仪8个姿态
	uint8_t curve_index;			//0 ~ 255曲线标志
	float x_min;
	float x_max;
	uint16_t y_output;
	int16_t xy_output;
	uint8_t x_time;					//时间
	//uint8_t x_angle;					//角度

	uint8_t output_index;			//输出通道标志
	
} INTER_SET;

int16_t curve_b_y7_points(float inp, float x_min, float x_max, int16_t y_min, int16_t y_mid, int16_t y_max, int8_t *yp)；
void channelip_ophandle( uint16_t *channel_input,uint8_t x_angle,uint8_t gyro_date,float *x_date,uint8_t *zxy_date,int16_t *y_date,int8_t *yp,uint16_t *ch_return);

#endif

//bool test(uint16_t *ch, .... , int16_t *gyro_data, int16_t *ch_return)