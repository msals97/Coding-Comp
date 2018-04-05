#include <iostream>
 #include <stdlib.h>
 #include <cstdlib>
 
 using namespace std;
 
 int repeat()
 {
 int ch;
 cout<<"\n\nWANT TO TRY AGAIN?";
 cout<<"\tTO CONTINUE PRESS 1\n PRESS ANY OTHER KEY TO EXIT";
cin>>ch;
 if(ch==1)
 {
 return 1;
}
 else
 {
 return 0;
 }
}
int main()
 {
 int option;
 float x,y,h;
 float k1,k2,k=0;
 label:
 cout<<"PLEASE ENTER THE CORRESPONDING VALUES: ";
 cout<<endl<<"X= ";
 cin>>x;
 cout<<endl<<"Y= ";
 cin>>y;
cout<<endl<<"H= ";
 cin>>h;
 system("cls");
 cout<<"\nGIVEN DATA: ";
 cout<<"\nX= "<<x<<"\tY= "<<y<<"\tH= "<<h;
cout<<"\nForumala for Calculations: "<<endl;
 cout<<endl<<"FORMULA OF K1= hf[x0,y0]";
 cout<<endl<<"FORMULA OF K2= hf[x0+h,y0+k1]";
 cout<<endl;
 cout<<"\n*******CHOSE FORMAT OF THE FUNCTION*******";
 cout<<"\t\n1. f(x)= x + y";
 cout<<"\t\n2. f(x)= x * y";
 cout<<"\t\n3. f(x)= x2 + xy";
 cout<<"\nEnter Option: ";
 cin>>option;
switch(option)
 {
 case 1:
 k1=(float) h*(x+y); // KI CALCULATED
 cout<<endl<<"K1= "<<k1;
k2=h*(x+h+y+k1);
 cout<<endl<<"K2= "<<k2;
k=(k1+k2)/2;
 cout<<endl<<"AVERAGE K= "<<k;
if(repeat()==1)
 {
 system("cls");
 goto label;
 }
 else
 {
 exit(0);
 }
 break;
case 2:
 k1=(float) h*(x*y); // KI CALCULATED
 cout<<endl<<"K1= "<<k1;
 k2=h*((x+h)*(y+k1));
 cout<<endl<<"K2= "<<k2;
 k=(k1+k2)/2;
 cout<<endl<<"AVERAGE K= "<<k;
if(repeat()==1)
 {
 system("cls");
 goto label;
 }
 else
 {
 exit(0);
 }
break;
case 3:
k1=(float) h*((x*x)+(x*y)); // KI CALCULATED
 cout<<endl<<"K1= "<<k1;
 k2=x=(x+h);
 k2=h*((x*x)+((y+k1)*x));
cout<<endl<<"K2= "<<k2;
 k=(k1+k2)/2;
 cout<<endl<<"AVERAGE K= "<<k;
if(repeat()==1)
 {
 system("cls");
 goto label;
 }
 else
 {
 exit(0);
 }
 break;
default:
 cout<<endl<<"INCORRECT OPTION";
}//end switch
 }