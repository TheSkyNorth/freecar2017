#include "headfile.h"
#include "data.h"
#include "math.h"

#define THRESHOLD 130


int dir[][2]=
{
  {-1,-1},{0,-1},
  {1,-1},{-1,0},
  {1,0},{-1,1},
  {0,1},{1,1}
};
Node head[10];
uint8 tempimage[ROW][COL]; //���ڴ������� ����ʱ����
uint8 binary_image[ROW][COL]; //��ֵ���������
uint16 light_num; //�������Ŀ

uint16 xmax,ymax,xmin,ymin;

/*

*COL     188//ͼ����  
*ROW     120//ͼ��߶�

*/


/*
*��������gray_binary
*����ֵ��0����1���ɹ�
*����:image ͼ������,binimage ��ֵ������
*���ߣ����
*����޸�ʱ�䣺2017.5.6
*/
/*
uint8 gray_binary(uint8 (*image)[ROW],uint8 (*binimage)[ROW])
{
   uint8 i,j;
   
   for(i=0;i<COL;i++)
   {
     for(j=0;j<ROW;j++)
     {
       if(image[i][j] > THRESHOLD)
       {
          binimage[i][j] = 1;
       }
       else
       {
          binimage[i][j] = 0;
       }
     
     }
   }
    
}
*/
uint8 gray_binary(uint8 *image,uint8 *binimage)
{
   uint32 i;
   
   for(i=0;i<COL*ROW;i++)
   {
     
     if(image[i]>THRESHOLD)
     {
        binimage[i] = 1;
     }
     else
     {
       binimage[i] = 0;
     }
     
   }
   
   return 1;    
}

/*
*��������find_size
*���ܣ�����һ��������ҵ��������������ͨ���������㣬ͳ����Щ�������Ŀ
*������i  ���x���꣬j   ���y����
*˵�������ڲ�����ȫ�ֱ�����find_position����ֻ�ɱ�����һ�Σ��ҵ��ú�image[][]���������ݽ���ȫ����0
*�ú�������������������
*����޸�ʱ�䣺2017-5-6
*/
void find_size(int i,int j){//������ͨ���С
    light_num++;
    if(i>xmax)xmax = i;
    if(i<xmin)xmin = i;
    
    if(j>ymax)ymax = j;
    if(j<ymin)ymin = j;
    
    tempimage[i][j]=0;
    if(i+1<ROW && tempimage[i+1][j]==1)//ע���������������ͳ�Ƶ�
        find_size(i+1,j);
    if(i-1>=0 && tempimage[i-1][j]==1)
        find_size(i-1,j);
    if(j+1<COL && tempimage[i][j+1]==1)
        find_size(i,j+1);
    if(j-1>=0 && tempimage[i][j-1]==1)
        find_size(i,j-1);
    if(i-1>0&&j-1>=0 && tempimage[i-1][j-1]==1)
        find_size(i,j-1);
    if(i+1<ROW&&j-1>=0 && tempimage[i+1][j-1]==1)
        find_size(i,j-1);
    if(i-1>0 && j+1<COL && tempimage[i-1][j+1]==1)
        find_size(i,j-1);
    if(i+1<ROW&&j+1<COL && tempimage[i+1][j+1]==1)
        find_size(i,j-1);
    
}

/*
*��������find_position
*���ܣ�������ֵ��ͼ���ҵ���ͨ��λ�ò��ҽ���һ�����λ�ü���С��������
*����޸�ʱ�䣺2017.5.6
*/
uint8 finded_time = 0;
void find_position(){
   // head=malloc(sizeof(Node));
  //head.next = NULL;
    uint16 i=0,j=0;
    
    finded_time = 0;
    memcpy((uint8*)tempimage,(uint8*)binary_image,ROW*COL);
    
    for(i=0;i<ROW;i++)
    {
        for(j=0;j<COL;j++)
        {
            if(tempimage[i][j]==1)
            {
                light_num=0;
                
                xmax = i;
                ymax = j;
                xmin = i;
                ymin = j;
                
                find_size(i,j);
                if(light_num > 3)
                {
                  head[finded_time].x=(xmax + xmin)/2;
                  head[finded_time].y=(ymax + ymin)/2;
                  head[finded_time].size = light_num;                
                  finded_time++;
                }
                /*
                newpos.x=i,newpos.y=j;
                newpos.size=light_num;
                Node* temp=&head;
                while(temp->next!=NULL) //�ҵ�����β��Ȼ����½ڵ�����ȥ
                    temp=temp->next;
                temp->next=&newpos;
                */
            }
        }
    }
    head[finded_time].size = 0;
}
/*
*��������fine_yes_no
*���ܣ�ȷ���Ƿ��ҵ�����
*����ֵ������1��ʾ�ҵ����㣬����0��ʾû���ҵ�����
*����޸�ʱ�䣺2017.5.6
*/
uint8 fine_yes_no()
{
  if((head[0].size ==0) || (finded_time != 2))
  {
    return 0;
  }
  else
  {
    return 1;
  }

}
/*
*��������find_fetch
*���ܣ���ȡ����
*/
void find_fetch()
{
   // Node* temp=&head;
   // while(temp->next!=NULL){
   //     temp=temp->next;
     //   printf("x %d  y %d   size %d\n",temp->x,temp->y,temp->size);
   // }
  uint8 i = 0;
  while(i<finded_time)
  {
    
    printf("i  %d x %d  y %d   size %d\n",i,head[i].x,head[i].y,head[i].size);
    i++;
  }
}
/*
void nrf_send_data(double dat)
{
  uint8 send_buff[32]={0};
  uint8 i =0;
  dat = dat/100;
  send_buff[0] = 0x00;
  for(i = 1;i<10;i++)
  {
    send_buff[i] = (int)dat%10;
    dat = dat * 10;
  }
  NRF_Send_Packet(send_buff);
  
}
*/
void nrf_send_data(double* dat)
{
  uint8 *p;
  uint8 i;
  uint8 send_buff[32]={0};
  
  p = (uint8 *)dat;
  
  send_buff[0] = 0x09;
  
  for(i = 1;i<9;i++)
  {
    send_buff[i] = *p;
    p++;
  }
  
  NRF_Send_Packet(send_buff);
}

/*
*����ɼ���ͼ���ҵ�����飬�����ҵ����Ĵ�С
*�õ���ȫ�ֱ�����image:�ɼ����ĻҶ�ͼ��binimage:��ֵ�����ͼ��tempimage:���ڴ������ݵ���ʱ����;
*/

void get_position_size()
{
  double image_angle;
  //��ֵ��
  gray_binary((uint8*)image,(uint8*)binary_image);
  //�ҵ������λ��
  find_position();
  if(fine_yes_no())
  {
   // find_fetch();
   // if(finded_time == 2)
    //{
      image_angle = get_image_angel(head[0],head[1]);
    //}
    //printf("%f\n",image_angle);
      
     nrf_send_data(&image_angle);//ͨ��nrf��������
  }
}

/*
*��������void get_image_angel(Node pointa,Node pointb)
*������pointa,ͼ���е�a���㣬pointb,ͼ���е�b����,angle ������ĽǶ�
*/
double get_image_angel(Node pointa,Node pointb)
{
  //����ʼ���ɳ�ָ��ƣ�Ҳ����:С->��������x,y��
  double angle=0;
  int x,y;

    if(pointa.size>pointb.size)
    {
      x = (int)(pointa.x) - (int)(pointb.x);
      y = (int)(pointa.y) - (int)(pointb.y);
    }
    else
    {
      x = (int)(pointb.x) - (int)(pointa.x);
      y = (int)(pointb.y) - (int)(pointa.y);
    }
    
    angle = atan2((double)x,(double)y) * (180 / PI)+180;  
    if(angle > 360)
    {
      x = 0;
    }
    if(angle>100)
    {
      x = 1;
    }
    return angle;
 
}

/*
*��������find_light_car
*����ֵ��0����1���ɹ�
*����:image ͼ�����飬width ͼ���ȣ�longth ͼ�񳤶�  
*/
uint8 find_light_car(uint8 *image,uint8 width,uint8 longth)
{
   uint8 i,j;
   
   for(i=0;i<width;i++)
   {
     for(j=0;j<longth;j++)
     {
      
     
     }
   }
   return 0;
    
}
