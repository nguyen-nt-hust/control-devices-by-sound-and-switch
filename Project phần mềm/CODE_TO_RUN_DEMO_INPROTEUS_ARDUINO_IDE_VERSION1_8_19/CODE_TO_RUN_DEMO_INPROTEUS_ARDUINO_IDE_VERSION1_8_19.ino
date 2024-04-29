     
      /*===================================================================================================================================*/
      /*================================================CONTROL DEVICE BY SOUND AND SWITCH=================================================*/
      /*===================================================================================================================================*/
      // CODE USE TU RUN IN PROTEUS HAVE A LITTLE DIFFERENT WITH CODE USE TO REAL CIRCUIT
      //BECAUSE IT DEPEND ON THE COMPONENTS OF CIRCUIT.
// rơ le 1 nối vào chân 12 arduino
#define relay1 12
// rơ le 2 nối vào chân 11                 
#define relay2 11
// chân 13 nối với cảm biến                                                                                    
#define Sensor 13  
  
// biến này để điều khiển tắt bật của rơ le 1                                          
int state1; 
// biến này để điều khiển tắt bật của rơ le 2                                                                                 
int state2;       
// biến lưu số lần thu được tín hiệu ví dụ vố tay 1 cái hoặc 2 cái                                                                 
int numberOftime;
// tín hiệu được đọc từ cảm biến là 0 nếu có âm thanh và là 1 nếu không có âm thanh               
int valueSensor;   
// khai báo timer theo kiểu luôn dương                                            
unsigned long timer;

      /*===================================================================================================================================*/
      /*==========================================================SETSUP FUNCTION==========================================================*/
      /*===================================================================================================================================*/
// hàm này có chức năng là để cài đặt, cái này chỉ dùng 1 vòng lặp rồi sẽ tới hàm void loop
void setup() {
  // cảm biến là tín hiệu vào
  pinMode(Sensor,INPUT);
  // rơ le 1 là tín hiệu ra                                  
  pinMode(relay1,OUTPUT);   
  // rơ le 1 là tín hiệu ra 
  pinMode(relay2,OUTPUT);
  // ban đầu đặt cho cái rơ le 1 đang bật cái này thích đặt đang tắt cg được nhưng đặt đang bật để kiểm tra có vào điện hay không                                                                               
  state1= 1; 
  // ban đầu đặt cho cái rơ le 2 đang bật cái này thích đặt đang tắt cg được nhưng đặt đang bật để kiểm tra có vào điện hay không               
  state2= 1;
  // khai báo timer                                                                                   
  timer=0; 
  // đặt ban đầu chân số 2 đang ở mức cao       
  digitalWrite(2, HIGH);
  // đặt ban đầu chân số 3 đang ở mức cao
  digitalWrite(3, HIGH); 
  // khai báo hàm ngắt gọi hàm changeRelay1 nếu công tắc của chân số 2 đổi chế độ từ low lên high
  attachInterrupt(0, changeRelay1, CHANGE); 
  attachInterrupt(1, changeRelay2, CHANGE);   
  // để kết nối với máy tính có thể in thông tin ra màn hình để sửa lỗi cho dễ dàng hơn                               
  Serial.begin(9600);
  }
      /*===================================================================================================================================*/
      /*============================================================LOOP FUNCTION==========================================================*/
      /*===================================================================================================================================*/
// hàm này lặp vô hạn lần nên chương trình chính viết ở đây
void loop() 
{
   //rơ le 1 sẽ được nhận giá trị của biến trạng thái state1 là 1/0 tức là on hoặc off
   digitalWrite(relay1,state1); 
   digitalWrite(relay2,state2);
   //đọc thông tin từ cảm biến sẽ băng 0 khi có tín hiệu âm thanh bằng 1 khi không có    
      valueSensor=digitalRead(Sensor);                                                                    
      // mặc định số  lần xuất hiện luôn là 0 tín hiệu
      numberOftime=0; 
       
      // nếu có tín hiệu                                 
      if(valueSensor==0)                                                                        
      {
      //timer start 
      timer=millis(); 
      numberOftime++; 
      delay(40);                
      while(millis()-timer<2000){ 
      valueSensor=digitalRead(Sensor);                                                 
      if(valueSensor==0){numberOftime++;delay(80);}}
      timer = millis();
      }
      if(numberOftime==1 ){
      state1 = !state1;
       delay(10);
      }
      // nếu vố tay 2 cái thì là bật tắt rơ le 2
      if(numberOftime ==2 ) 
      {
      state2 = !state2;
      delay(10);
      }
}
      /*===================================================================================================================================*/
      /*========================================================INTERRUP FUNCTION==========================================================*/
      /*===================================================================================================================================*/
// hàm ngắt để bật rơ le thứ nhất
void changeRelay1() 
{ 
  // vì thực tế công tắc nó bị nhiếu vì khoảng thời gian chuyển trạng thái dòng điện sẽ bắt tia lửa điện nên hàm ngắt bị gọi nhiều lần, sử dụng delay để bớt những tín hiệu nhiếu đó.
 

  // đổi trạng thái của biến 
  state1 = !state1; 
  delay(80);
}
// hàm ngắt để bật rơ le thứ hai
void changeRelay2()
{ 
  // hàm ngắt chỉ được gọi 1 lần khi đổi trạng thái từ thấp lên cao thế nên việc xảy ra nhiếu khiến cho biến trạng thái bị sai.
  state2 = !state2;
  delay(80);
}
      /*===================================================================================================================================*/
      /*============================================================END CODE===============================================================*/
      /*===================================================================================================================================*/
