#include "img_deal.h"
#include "headfile.h"

extern Node head[10];
extern uint8 finded_time;
Node car_pre,light_pre;
uint8 get_img_car_err(double *light_ang,double *car_ang)
{
  Node *car,*light;
  int16_t temp;
  
  if(finded_time != 2)//�ҵ��������������ԣ����ش���
  {
    return 0;
  }
  
  //ȷ�����κ��ϴεĳ�������
  if(head[0].size>head[1].size)
  {
    light = &head[0];
    car = &head[1];
  }
  else
  {
    light = &head[1];
    car = &head[0];
  }
  
  //x = (double)(car->x - car_pre.x);
  
  //ƫ������
  arm_sub_q15((q15_t*)&light->x,\
              (q15_t*)&light_pre.x,\
                &temp,1);//dsp���������Ĳ�
 
  if(abs(temp) > 1)
  {
    light->x = light->x - temp;
    car->x = car->x - temp;
  }
  
  arm_sub_q15((q15_t*)&light->y,\
    (q15_t*)&light_pre.y,\
      &temp,1);//dsp���������Ĳ�   
  
  if(abs(temp) > 1)
  {
    light->y = light->y - temp;
    car->y = car->y - temp;
  }
  
  //����������
  *light_ang = atan2((double)(light->x-car->x),\
    (double)(light->y - car->y));
  *car_ang = atan2((double)(car->x - car_pre.x),\
                   (double)(car->y - car_pre.y));
  
  
  return 1;
}











