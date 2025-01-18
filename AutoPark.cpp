#include <Servo.h>
// پین‌های اتصال به ماژول
const int r_trigPin = 3; // پین Trig
const int r_echoPin = 4; // پین Echo
const int b_trigPin = 5; // پین Trig
const int b_echoPin = 6; // پین Echo
const int in1 = 8; // جهت 1 موتور
const int in2 = 7; // جهت 2 موتور
const int head1 = 9;

#define side_dis 10
#define back_dis 10
#define H_right 180
#define H_forward 90
#define H_left 0

Servo head;


void setup() {

	head.attach(head1);
	head.write(H_forward);  // زاویه 0 درجه برای سروو دوم

	// تنظیم پین‌ها
	pinMode(r_trigPin, OUTPUT);
	pinMode(r_echoPin, INPUT);
	pinMode(b_trigPin, OUTPUT);
	pinMode(b_echoPin, INPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	stopMotor();
	delay(5000);





	if (measureDistance(r_trigPin, r_echoPin) < side_dis)//اگر مانع بود بره جلو برسه به جا پارک
	{
		while (measureDistance(r_trigPin, r_echoPin) < side_dis)
		{
			forward();
		}
		stopMotor();
	}
	while (measureDistance(r_trigPin, r_echoPin) > side_dis)//جاپارک یافت شد! میریم برسیم به ماشین جلو
	{
		forward();
	}
	stopMotor();
	backward();//رسیدیم به ماشین جلو یکم ماشین رو میاریم عقب
	delay(300);
	stopMotor();
	head.write(H_right); //گردش فرمون به سمت راست
	delay(800);
	backward();
	delay(500);
	head.write(H_left); //گردش فرمون به سمت چپ
	delay(800);
	backward();
	delay(300);
	while (measureDistance(b_trigPin, b_echoPin) > back_dis)//وارد شدن به چاپارک با دنده عقب و زاویه 45
	{
		backward();
		delay(50);
	}
	stopMotor();
	head.write(H_forward);// فرمان صاف شود
	delay(500);
	forward();
	delay(100);
	stopMotor();
	//head.write(H_left); 

	//delay(800);
}

void loop() {


}

// تابع فاصله‌سنجی
float measureDistance(int trigPin, int echoPin)
{
	// ارسال سیگنال فراصوت
	delay(100);//وقفه برای جلوگیری از تداخل نویزی موتور ها
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

	// دریافت مدت زمان بازگشت سیگنال
	long duration = pulseIn(echoPin, HIGH);

	// محاسبه فاصله (بر حسب سانتی‌متر)
	float distance = duration * 0.034 / 2;

	return distance;
}
void forward()
{
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
}

// تابع برای چرخش موتور به عقب
void backward()
{
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
}

// تابع برای توقف موتور
void stopMotor() {
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
}