#include<string.h>
#include<iostream>
using namespace std;

class TMDate
{
private:
int dayOfMonth;
int month;
int year;
int dayOfWeek;
int dayNumber;
int toDayNumber();
int isLeapYear(int y);
void fromDayNumber();
void isValidDate(const char *dateString,int *isValid,int *d,int *m,int *y);

public:
//constructor function
TMDate();
TMDate(const char *dateString);
TMDate(const TMDate &other);
TMDate & operator=(const TMDate &other);
virtual ~TMDate();

//non constructor function
int getDayOfMonth();
int getMonth();
int getYear();
int isLeapYear();
int getDayOfWeek();
void getDayOfWeekString(char *dayOfWeekString);
void getShortDayOfWeekString(char *shortDayOfWeekString);
void getMonthString(char *monthString);
void getShortMonthString(char *shortMonthString);

//operator function
TMDate & operator=(const char *dateString);
void operator+=(int days);
void operator-=(int days);
TMDate operator+(int days);
TMDate operator-(int days);
void operator++(int);
void operator--(int);
int operator<(const TMDate &other);
int operator>(const TMDate &other);
int operator<=(const TMDate &other);
int operator>=(const TMDate &other);
int operator==(const TMDate &other);
int operator!=(const TMDate &other);

};
TMDate::TMDate()
{
time_t x;
time(&x);
 struct tm *now;
now=localtime(&x);
this->dayOfMonth=now->tm_mday;
this->month=now->tm_mon+1;
this->year=now->tm_year+1900;
toDayNumber();
}
TMDate::TMDate(const char *dateString)
{
int isValid;
int d,m,y;
isValidDate(dateString,&isValid,&d,&m,&y);
if(isValid)
{
this->dayOfMonth=d;
this->month=m;
this->year=y;
this->toDayNumber();
}
else
{
this->dayNumber=0;
this->dayOfMonth=0;
this->month=0;
this->year=0;
}
}

TMDate::TMDate(const TMDate &other)
{
this->dayNumber=other.dayNumber;
this->dayOfMonth=other.dayOfMonth;
this->month=other.month;
this->year=other.year;
}

TMDate & TMDate::operator=(const TMDate &other)
{
this->dayNumber=other.dayNumber;
this->dayOfMonth=other.dayOfMonth;
this->month=other.month;
this->year=other.year;
return *this;
}
TMDate::~TMDate()
{
}
TMDate & TMDate::operator=(const char *dateString)
{
int isValid;
int d,m,y;
isValidDate(dateString,&isValid,&d,&m,&y);
if(isValid)
{
this->dayOfMonth=d;
this->month=m;
this->year=y;
this->toDayNumber();
}
else
{
this->dayNumber=0;
this->dayOfMonth=0;
this->month=0;
this->year=0;
}
return *this;
}

void TMDate::isValidDate(const char *dateString,int *isValid,int *d,int *m,int *y)
{
int dd,mm,yy;
char sep;
int sepIndex1,sepIndex2;
int mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};

*isValid=0;
if(dateString==NULL) return;
int x=strlen(dateString);
if(x<8 || x>10) return;
if(!(dateString[1]=='/' || dateString[2]=='/' || dateString[1]=='-' || dateString[2]=='-')) return;
if(dateString[1]=='/' || dateString[1]=='-') sepIndex1=1;
else sepIndex1=2;
sep=dateString[sepIndex1];
if(dateString[0]<48 || dateString[0]>57) return;
if(sepIndex1==2 && (dateString[1]<48 || dateString[1]>57 || dateString[1]<48 || dateString[1]>57)) return ;
if(sepIndex1==1)
{
dd=dateString[0]-48;
if(dd==0) return;
}
else
{
dd=((dateString[0]-48)*10)+(dateString[1]-48);
if(dd==0) return;
}
int i=sepIndex1+1;
if(!(dateString[i+1]==sep || dateString[i+2]==sep)) return;
if(dateString[i+1]==sep) sepIndex2=i+1;
else sepIndex2=i+2;
if(dateString[i]<48 || dateString[i]>57) return ;
if(sepIndex2==i+2 && (dateString[i+1]<48 || dateString[i+1]>57)) return;
if(sepIndex2==i+1) 
{
mm=dateString[i]-48;
}
else 
{
mm=((dateString[i]-48)*10)+(dateString[i+1]-48);
}
if(mm<1 || mm>12) return ;
i=sepIndex2+1;
yy=0;

int r=0;
while(r<=3)
{
if(dateString[i+r]<48 || dateString[i+r]>57) return;
yy=(yy*10)+(dateString[i+r]-48);
r++;
}
if(yy<1901) return;
if(yy%400==0) mth[1]=29;
else if(yy%100==0) mth[1]=28;
else if(yy%4==0) mth[1]=29;
else mth[1]=28;
if(dd<1 || dd>mth[mm-1]) return;
if(mm<1 || mm>12) return;
*d=dd;
*m=mm;
*y=yy;
*isValid=1;
}

int TMDate::toDayNumber()
{
int x=0;
int y=1901;
int m;
while(y<this->year)
{
if(isLeapYear(y)) x=x+366;
else x=x+365;
y++;
}
int mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
if(isLeapYear(this->year)) mth[1]=29;
m=0;
int ep=this->month-2;
while(m<=ep)
{
x=x+mth[m];
m++;
}
x=x+this->dayOfMonth;
this->dayNumber=x;
return dayNumber;
}
int TMDate::isLeapYear(int y)
{
if(y%400==0) return 1;
else if(y%100==0) return 0;
else if(y%4==0) return 1;
else return 0;
}
void TMDate::fromDayNumber()
{
if(this->dayNumber<=0)
{
this->dayOfMonth=0;
this->month=0;
this->year=0;
return ;
}
int x=this->dayNumber;
int d,m,y;
int daysInYear;
int daysInMonth;
y=1901;
while(1)
{
if(isLeapYear(y)) daysInYear=366;
else daysInYear=365;
if(x<=daysInYear) break;
x=x-daysInYear;
y=y+1;
}
int mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
if(isLeapYear(y)) mth[1]=29;
m=0;
while(1)
{
daysInMonth=mth[m];
if(x<=daysInMonth) break;
x=x-daysInMonth;
m++;
}
m++;
d=x;
//cout<<d<<" "<<m<<" "<<y<<endl;
this->dayOfMonth=d;
this->month=m;
this->year=y;
}
int TMDate::getDayOfMonth()
{
return this->dayOfMonth;
}
int TMDate::getMonth()
{
return this->month;
}
int TMDate::getYear()
{
return this->year;
}
ostream & operator<<(ostream &oo,TMDate &tmDate)
{
oo<<tmDate.getDayOfMonth()<<"/"<<tmDate.getMonth()<<"/"<<tmDate.getYear();
return oo;
}
void TMDate::getMonthString(char *monthString)
{
if(monthString==NULL)
{
*monthString='\0';
return;
}
if(this->month==1) strcpy(monthString,"January");
else if(this->month==2) strcpy(monthString,"February");
else if(this->month==3) strcpy(monthString,"March");
else if(this->month==4) strcpy(monthString,"April");
else if(this->month==5) strcpy(monthString,"May");
else if(this->month==6) strcpy(monthString,"June");
else if(this->month==7) strcpy(monthString,"July");
else if(this->month==8) strcpy(monthString,"August");
else if(this->month==9) strcpy(monthString,"September");
else if(this->month==10) strcpy(monthString,"October");
else if(this->month==11) strcpy(monthString,"November");
else if(this->month==12) strcpy(monthString,"December");
else *monthString='\0';
}
void TMDate::getShortMonthString(char *shortMonthString)
{
if(shortMonthString==NULL)
{
*shortMonthString='\0';
return;
}
if(this->month==1) strcpy(shortMonthString,"Jan");
else if(this->month==2) strcpy(shortMonthString,"Feb");
else if(this->month==3) strcpy(shortMonthString,"Mar");
else if(this->month==4) strcpy(shortMonthString,"Apr");
else if(this->month==5) strcpy(shortMonthString,"May");
else if(this->month==6) strcpy(shortMonthString,"Jun");
else if(this->month==7) strcpy(shortMonthString,"Jul");
else if(this->month==8) strcpy(shortMonthString,"Aug");
else if(this->month==9) strcpy(shortMonthString,"Sep");
else if(this->month==10) strcpy(shortMonthString,"Oct");
else if(this->month==11) strcpy(shortMonthString,"Nov");
else if(this->month==12) strcpy(shortMonthString,"Dec");
else *shortMonthString='\0';
}

int TMDate::getDayOfWeek()
{
if(this->dayNumber==0) return 0;
int dow=(this->dayNumber%7)+2;
dow=dow%7;
if(dow==0) return 7;
return dow;

/*	//or
int leftDays=this->dayNumber%7;
int dow=2+leftDays; 	//2 (Monday) as 1/1/1901 is Tue(3)
if(dow>7) dow=dow%7;
return dow;
*/
}
void TMDate::getDayOfWeekString(char *dayOfWeekString)
{
if(dayOfWeekString==NULL)
{
*dayOfWeekString='\0';
return;
}
int x=this->getDayOfWeek();
if(x==1) strcpy(dayOfWeekString,"Sunday");
else if(x==2) strcpy(dayOfWeekString,"Monday");
else if(x==3) strcpy(dayOfWeekString,"Tuesday");
else if(x==4) strcpy(dayOfWeekString,"Wednesday");
else if(x==5) strcpy(dayOfWeekString,"Thursday");
else if(x==6) strcpy(dayOfWeekString,"Friday");
else strcpy(dayOfWeekString,"Saturday");
}
void TMDate::getShortDayOfWeekString(char *shortDayOfWeekString)
{
if(shortDayOfWeekString==NULL)
{
*shortDayOfWeekString='\0';
return;
}
int x=this->getDayOfWeek();
if(x==1) strcpy(shortDayOfWeekString,"Sun");
else if(x==2) strcpy(shortDayOfWeekString,"Mon");
else if(x==3) strcpy(shortDayOfWeekString,"Tue");
else if(x==4) strcpy(shortDayOfWeekString,"Wed");
else if(x==5) strcpy(shortDayOfWeekString,"Thu");
else if(x==6) strcpy(shortDayOfWeekString,"Fri");
else strcpy(shortDayOfWeekString,"Sat");
}
void TMDate::operator+=(int days)
{
if(this->dayNumber==0) return ;
this->dayNumber+=days;
this->fromDayNumber();
}
void TMDate::operator-=(int days)
{
if(this->dayNumber==0 || this->dayNumber<=days) return ;

this->dayNumber-=days;
this->fromDayNumber();
}
TMDate TMDate::operator+(int days)
{
if(this->dayNumber==0) return TMDate("0/0/0000");
TMDate date;
date.dayNumber=this->dayNumber+days;
date.fromDayNumber();
return date;
}
TMDate TMDate::operator-(int days)
{
if(this->dayNumber==0) return TMDate("0/0/0000");
TMDate date;
date.dayNumber=this->dayNumber-days;
date.fromDayNumber();
return date;
}



int TMDate::isLeapYear()
{
return isLeapYear(this->year);
}
void TMDate::operator++(int)
{
this->dayNumber++;
this->fromDayNumber();
}
void TMDate::operator--(int)
{
this->dayNumber--;
this->fromDayNumber();
}

int TMDate::operator<(const TMDate &other)
{
return this->dayNumber<other.dayNumber;
}
int TMDate::operator>(const TMDate &other)
{
return this->dayNumber>other.dayNumber;
}
int TMDate::operator<=(const TMDate &other)
{
return this->dayNumber<=other.dayNumber;
}
int TMDate::operator>=(const TMDate &other)
{
return this->dayNumber>=other.dayNumber;
}
int TMDate::operator==(const TMDate &other)
{
return this->dayNumber==other.dayNumber;
}
int TMDate::operator!=(const TMDate &other)
{
return this->dayNumber!=other.dayNumber;
}

int main()
{
char a[11];
int b;
TMDate date1="3/12/1850";

for(int i=0;i<10;i++)
{
cout<<date1<<endl;
date1++;
}
TMDate date2("10/12/2020");
TMDate date3("1/2/2000");

date3=date2=date1;

cout<<date1<<endl;
cout<<date2<<endl;
cout<<date3<<endl;
return 0;
}