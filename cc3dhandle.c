#include "cc3dhandle.h"

INTER_SET inter_setting;

//曲线输出方程
int16_t curve_b_y7_points(float inp, float x_min, float x_max, int16_t y_min, int16_t y_mid, int16_t y_max, int8_t *yp)
{
	uint8_t i = 0;
	float x[7];
	int16_t y[7];
	int16_t oup = 0;
	
	//x 轴做7等分
	int8_t xp[7] = {
		100 * 0 / 6,
		100 * 1 / 6,
		100 * 2 / 6,
		100 * 3 / 6,
		100 * 4 / 6,
		100 * 5 / 6,
		100 * 6 / 6
	};

	if (x_min <= x_max) {
		for (i = 0; i < 7; i++) {
			x[i] = (x_max - x_min) * (xp[i] - 0) / (100 - 0) + x_min;
		}
	}
	if ((y_min <= y_mid) && (y_mid <= y_max)) {
		for (i = 0; i < 7; i++) {
			if (yp[i] <= 50) {
				y[i] = ((y_mid - y_min) * (yp[i] - 0)) / (50 - 0)  + y_min;
			} else {
				y[i] = ((y_max - y_mid) * (yp[i] - 50)) / (100 - 50) + y_mid;
			}
		}
		if (inp < x[0]) {
			inp = x[0];
			oup = y[0];
		} else if ((inp >= x[0]) && (inp < x[1])) {
			oup = (y[1] - y[0]) * (inp - x[0]) / (x[1] - x[0]) + y[0];
		} else if ((inp >= x[1]) && (inp < x[2])) {
			oup = (y[2] - y[1]) * (inp - x[1]) / (x[2] - x[1]) + y[1];
		} else if ((inp >= x[2]) && (inp < x[3])) {
			oup = (y[3] - y[2]) * (inp - x[2]) / (x[3] - x[2]) + y[2];
		} else if ((inp >= x[3]) && (inp < x[4])) {
			oup = (y[4] - y[3]) * (inp - x[3]) / (x[4] - x[3]) + y[3];
		} else if ((inp >= x[4]) && (inp < x[5])) {
			oup = (y[5] - y[4]) * (inp - x[4]) / (x[5] - x[4]) + y[4];
		} else if ((inp >= x[5]) && (inp <= x[6])) {
			oup = (y[6] - y[5]) * (inp - x[5]) / (x[6] - x[5]) + y[5];
		} else if (inp > x[6]) {
			inp = x[6];
			oup = y[6];
		}
	} else {
		oup = inp;
	}
	return oup;
}
void channelip_ophandle( uint16_t *channel_input,uint8_t x_angle,uint8_t gyro_date,uint8_t *zxy_date,int16_t *y_date,int8_t *yp,uint16_t *ch_return)
{
	//判断干预是否使能
	if(inter_setting.enable){
		//判断输入通道数值是否大于干预门限
		if(channel_input[inter_setting.input_index - 1] > inter_setting.threshold){
			switch(gyro_date)
			{//zxy_date[0] == z,zxy_date[1] == x,zxy_date[2] == y,
				case 0x00:
					break;
				case 0x01:
					break;
				case 0x02:
					zxy_date[1] = 0 - zxy_date[1];
					break;
				case 0x03:
					zxy_date[2] = 0 - zxy_date[2];
					break;
				case 0x04:
					zxy_date[1] = 0 - zxy_date[1];
					zxy_date[2] = 0 - zxy_date[2];
					break;
				case 0x05:
					zxy_date[0] = 0 - zxy_date[0];
					break;
				case 0x06:
					zxy_date[0] = 0 - zxy_date[0];
					zxy_date[1] = 0 - zxy_date[1];
					break;
				case 0x07:
					zxy_date[0] = 0 - zxy_date[0];
					zxy_date[2] = 0 - zxy_date[2];
					break;
				case 0x08:
					zxy_date[0] = 0 - zxy_date[0];
					zxy_date[1] = 0 - zxy_date[1];
					zxy_date[2] = 0 - zxy_date[2];
					break;
			}
			if(!x_angle){
				if((inter_setting.x_time >= 3)&&(inter_setting.x_time <= 15)){
					//y_date[0] == min,y_date[1] == mid,y_date[2] == max,
					inter_setting.xy_output = curve_b_y7_points(inter_setting.x_time,inter_setting.x_min,inter_setting.x_max, y_date[0],y_date[1],y_date[2],yp);
				}
				
			}
			else if((&&(x_angle > 0)&&(x_angle <= 28)){
				inter_setting.xy_output = curve_b_y7_points(x_angle,inter_setting.x_min,inter_setting.x_max, y_date[0],y_date[1],y_date[2],yp);
			}
		}
		else{
			if(!inter_setting.output_index)
				ch_return[inter_setting.output_index - 1] = channel_input[inter_setting.input_index];
		}
	}
	else{
		if(!inter_setting.output_index){
			ch_return[inter_setting.output_index - 1] = channel_input[inter_setting.input_index];
		}
	}
}