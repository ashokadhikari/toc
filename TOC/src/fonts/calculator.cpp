#include<iostream.h>
#include<iomanip.h>
#include<stdlib.h>
#include<dos.h>
#include<conio.h>
#include<math.h>
#include<stdio.h>
#include<graphics.h>
#define Pi 3.141592
#define f5(x) x*x-a
#define f1(x) 2*x
#define 	f2(x)     pow(x,4)
#define 	Y  9
#define f3(x) pow(x,2)
#define f_(x) 2*x
#define f(x) x*x
#define fr(x) sin(x)-5*x+2

double k;
void start();

///////  1).Base Class:-   \\\\\\\\\

   class Project
     {
       protected:
       double n[20];
       int u,v;
	long ans;
       public:
	 Project():ans(0)
	  {
	  /*  cout<<"Enter the value of 'X':";
	    cin>>ans; */

	  }
	long set();
	void root();
	double loga(double);
	double ln(double x);
	double checking(double);
	double fact(double);
	double raise(double,double);
	double x2(double);
	double x3(double);
	double sum();
	double average();
	double difference();
	double multiple();
	double division();

     };

      long Project::set()
      {

	cout<<"Enter the value of 'X':";
	    cin>>ans;
	return ans;
       }
/////  2).Derived Class 1 :- For Claculater: \\\\\\

   class Calculator:public Project
     {
       public:

	double e_x();
	double sine();
	double cosine();
	void tangent();
     };
 class Record:public Project
    {
    public:

/* 1 */    void show_menus();
};


void Record::show_menus(){
cout<<"what ru searching for?";
}
     /////////////// For Square Root \\\\\\\\\\\\\\
void Project::root()
{

	int  n=1000;
	float x0=1,e=.0005,y,z,x1,x2,a;
	cout<<"\n\n\tEnter the number for finding the square root \t";
	cin>>a;
	for(int i=0;i<=n;i++)
	{
		y=f5(x0);
		z=f1(x0);
		x1=x0-y/z;
		x2=x1-x0;
		if (x2<0)
		x2=x2*(-1);
		if(x2<e)
		break;
		if(x2>e)
		x0=x1;
	}
	cout<<"\n\n\tThe square root of "<<a<<" is "<<x1;
	getch();
}

    //////////////// For Log10 \\\\\\\\\\\\\\\\\\\\\\\\

   double Project::loga(double b)
   {

    double LOG10=0,c;

    c=ln(b);
    LOG10=c/2.30258509299404;
    return LOG10;

   }


    /////////////////// For Natural Log \\\\\\\\\\\\\\\\\\\\\\\\

double Project:: ln(double x)
{
	double lnX=0.000001,check;

	do{

		lnX=lnX-(exp(lnX)-x)/exp(lnX);
		check=checking(lnX);

	  }while(check!=0);
	return lnX;

}


  ////////////// Check Function \\\\\\\\\\\\\\\

double Project::checking(double x)
    {
	static double x1=0;
	double x2;
	 if(x1==0)
	   {
	     x1=x;
	     return 1;
	   }
	 else
	      {
		  x2=x1-x;
		  if(x2<0)
		    x2*=-1;
		    x1=x;
	       return x2;
	      }
    }

  ////////////////// For Raise to N Power \\\\\\\\\\\\\\

double Project::raise(double y,double i)
    {
	 ans=1;
	 for(int k=0;k<i;k++)
	    ans*=y;

       return ans;
    }


//////////////////// For Factorial \\\\\\\\\\\\\\\\\\\\\\
  double Project::fact(double x)
    {
       double fact=1;
	 for(int i=x;i>0;i--)
	   fact*=i;
       return fact;
    }

///////////////////// For X^2 \\\\\\\\\\\\\\\\\\\\\\\\\\


  double Project::x2(double x)
    {
    return x*x;
    }

////////////////////// For X^3 \\\\\\\\\\\\\\\\\\\\\\\\\\\
    double Project::x3(double x)
    {
    return x*x*x;
    }

////////////////////// For sum \\\\\\\\\\\\\\\\\\\\\\\\\\\
double Project::sum(){
	double D=0;
	cout<<"How many no  u want to add?";
	cin>>u;
	for(int i=0;i<u;i++){
	cout<<"Enter "<<i+1<<" no that u want to manipulate.";
	cin>>n[i];}
	for( i=0;i<u;i++)
	 D+=n[i];
	return D;
	}
////////////////////// For average \\\\\\\\\\\\\\\\\\\\\\\\\\\
double Project:: average(){
		      return(sum()/u);
}
////////////////////// For difference \\\\\\\\\\\\\\\\\\\\\\\\\\\
double Project::difference(){
		double l,s;
		cout<<"Enter two no to subtract.";
		cin>> l>>s;
		return(l-s);
}
////////////////////// For multiple \\\\\\\\\\\\\\\\\\\\\\\\\\\
double Project::multiple(){
	      double l,s;
	      cout<<"Enter two no to multiply.";
	      cin>>l>>s;
	      return(l*s);
	      }
////////////////////// For division \\\\\\\\\\\\\\\\\\\\\\\\\\\
double Project::division(){
		double l,s;
		cout<<"Enter two no to divide";
		cin>>l>>s;
		return(l/s);
		}

////////////// Members of the Derived Class 1 \\\\\\\\\\\\\\\\\\\\\\\\\\\\\

///////////// For e^x \\\\\\\\\\\\\\\\\\\\\\\\
 double Calculator::e_x()
    {

     int k=0;
     double e=0,test;

     do{
	 e+=raise(ans,k)/fact(k);
	 k++;
	 test=checking(e);
       }
       while(test!=0);
     return e;
    }

/////////////////// For sin x \\\\\\\\\\\\\\\\\\\\

 double Calculator::sine()
    {
       double y;
       double res=0;
       int counter=0;
       double check;
       double i=1;

	  y=(ans*Pi)/180;
	   if(ans%180!=0)
	      {
		do{
		    if(counter%2==0)
		      {
		      double d=pow(y,i);
		      res+=d/fact(i);
		      }
	   else{
		      double s=pow(y,i);
		      res-=s/fact(i); }
		      counter++;
		      i+=2;
	  check=checking(res);
		  }
	       while(check!=0);
	       }
	   else
	     res=0;

     return res;

    }

//////////////////// For Cos x \\\\\\\\\\\\\\\\\\\\

  double Calculator::cosine()
    {
       double y;
       double res=0;
       int counter=0;
       double check;
       double i=0;

	  y=(ans*Pi)/180;
	     if((ans%90==0&&ans%180!=0)&&ans!=0)
		res=0;
	     else
	       {
		 do{
	     if(counter%2!=0)
	      {
	       double s=pow(y,i);
	       res+=s/fact(i);
	      }
	     else
	      {
	       double d=pow(y,i);
	       res-=d/fact(i);
	      }
	       counter++;
	       i+=2;
	       check=checking(res);
	      }while(check!=0);
	  }

    return res;
  }

//////////////////// For Tan x \\\\\\\\\\\\\\\\\\\\\\\\\\

void Calculator::tangent()
  {
	double sin,cos;
	 sin=Calculator::sine();
	 cos=Calculator::cosine();
	  if(sin==0)
	   cout<<"0";
	  else if(cos==0)
	   cout<<" Valus are Undefined";
	  else
	   cout<<(sin/cos)*-1;
  }

/////////////////////Second Base Class\\\\\\\\\\\\\\\\\\\\\\\\\\

 void main()
{
	clrscr();

	    long k;
	    double b=0,s,j;
	    Calculator a;
	   // Na z;
	 int option,opt1;
	 int mode=DETECT,driver=VGAHI;
	 initgraph(&mode,&driver,"C:\\tc\\bgi");

	 start();
	 closegraph();
	 clrscr();
		highvideo();
		textcolor(BLACK);
		textbackground(3);


	int ch=0;
	int q,m;
	char name[30],faculty[15];



   do


	{

		clrscr();
		cout<<"\n****************************TRIBHUVAN UNIVERSITY*******************************";
		cout<<"\n*********************** INSTITUTE OF ENGINEERING ******************************";
		cout<<"\n******************** DEPARTMENT OF ELECTRICAL ENGINEERING *********************";
		cout<<"\n***************************** PULCHOWK CAMPUS **********************************";
		cout<<"*******************************************************************************"<<endl;
		cout<<"\n\t1. CALCULATOR";
		cout<<"\n\t\t\t\t2. DATA RECORDER";
		cout<<"\n\t\t\t\t\t\t\t\t3. EXIT";
		cout<<"\n\n\n\********************************************************************************";
		cout<<"\n\nEnter Your Option :---> ";
		cin>>opt1;



	switch(opt1)
	{

	case 1:

		do
		{
		clrscr();
		cout<<"\t\t\tDEPARTMENT OF ELECTRICAL ENGINEERING"<<endl;
		cout<<"*******************************************************************************"<<endl;
		cout<<"\n\t\t**Avialable Calculation options**  "<<endl;
		cout<<"\t\t*********************************"<<endl;
		cout<<"\t\tWhat would u like to perform ?"<<endl;
		cout<<"\t\t*********************************";
		cout<<"\n\t0. For Exit";
		cout<<"\t\t\t1. For Sin x";
		cout<<"\n\t2. For Cos x";
		cout<<"\t\t\t3. For tan x";
		cout<<"\n\t4. For E^x";
		cout<<"\t\t\t5. For X^n";
		cout<<"\n\t6. For X^2";
		cout<<"\t\t\t7. For X^3";
		cout<<"\n\t8. For Factorial of X!";
		cout<<"\t\t9. For Natural Log or ln,";
		cout<<"\n\t10.For Square Root";
		cout<<"\t\t11.For Log10";
		cout<<"\n\t12.For Sum";
		cout<<"\t\t\t13.For Average";
		cout<<"\n\t14.For Difference";
		cout<<"\t\t15.For Multiplexion";
		cout<<"\n\t16.For Division";
		cout<<"\n\n\n******************************************************************************"<<endl;
		cout<<"Enter your option --->";

		cin>>option;

		switch(option)
		{

			case 1:
				{
				 k=a.set();
				 cout<<"Sin"<<k<<" : "<<a.sine()<<endl;
				 cout<<endl<<"\n\tPress any key to go back....";
				 ch=getch();
				 if(ch=='\r')
				 clrscr();
				break; }
			case 2:
				 {
				 k=a.set();
				 cout<<"Cos"<<k<<" : "<< a.cosine()*-1<<endl;
				 cout<<endl<<"\n\tPress any key to go back....";
				 ch=getch();
				 if(ch=='\r')
				 clrscr();
				break;
				 }
		    case 3:
				 {
				 k=a.set();
				 cout<<"Tan"<<k<<" : ";a.tangent();
				 cout<<endl<<"\n\tPress any key to go back....";

				 ch=getch();
				 if(ch=='\r')
				 clrscr();
				break;
				  }
		     case 4:
				{
				 k=a.set();
				 cout<<"E^"<<k<<" : "<<a.e_x()<<endl;
				 cout<<endl<<"\n\tPress any key to go back....";

				 ch=getch();
				 if(ch=='\r')
				 clrscr();
				break;
				 }
		      case 5:
				 {
				 cout<<"Enter the value of X : ";
				cin>>s;
				cout<<"Enter the value of Power n : ";
				cin>>j;
				cout<<s<<"^"<<j<<" : "<<a.raise(s,j);
				cout<<endl<<"\n\tPress any key to go back....";

				ch=getch();
				 if(ch=='\r')
				 clrscr();
				break;
				 }
		     case 6:
				 {
				 cout<<"\nEnter the value of x :";
				 cin>>j;
				 cout<<j<<"^2 : "<<a.x2(j);
				 cout<<endl<<"\n\tPress any key to go back....";

				 ch=getch();
				 if(ch=='\r')
				 clrscr();
				break;
				 }
		    case 7:
				{
				cout<<"\nEnter the value of x :";
				cin>>j;
				cout<<j<<"^3 : "<<a.x3(j);
				cout<<endl<<"\n\tPress any key to go back....";
				ch=getch();
				 if(ch=='\r')
				 clrscr();
				break;
				 }
		    case 8:
				 {
				cout<<"Enter the value of X"<<"\t";
				cin>>b;
				cout<<b<<"! or "<<b<<" Factorial is : "<<a.fact(b)<<endl;
				cout<<endl<<"\n\tPress any key to go back....";

				ch=getch();
				 if(ch=='\r')
				  clrscr();
				break;
				  }

		   case 9:
				  {
				cout<<"Enter the value of X"<<"\t";
				cin>>b;
				cout<<"Ln "<<b<<" : "<<a.ln(b);
				cout<<endl<<"\n\tPress any key to go back....";

				ch=getch();
				 if(ch=='\r')
				 clrscr();

				break;
				  }
		  case 10:
				 {
				 a.root();
				 cout<<endl<<"\n\tPress any key to go back....";
				 ch=getch();
				 if(ch=='\r')
				 clrscr();
				 break;
				  }
		   case 11:
				 {
				 cout<<"\nEnter the value of X : ";
				 cin>>b;
				 cout<<"Log_10^"<<b<< " is "<<a.loga(b);
				 cout<<endl<<"\n\tPress any key to go back....";
				 ch=getch();
				 if(ch=='\r')
				 clrscr();
				 break;
					  }
		case 12:	 {
				k=a.sum();
				cout<<"The required sum is :"<<k;
				cout<<endl<<"\n\tPress any key to go back....";
				ch=getch();
				if(ch=='\r')
				clrscr();
				break;
				}
		case 13:	{
				k=a.average();
				cout<<"Required average is:"<<k;
				cout<<endl<<"\n\tPress any key to go back....";
				ch=getch();
				if(ch=='\r')
				clrscr();
				break;
				}
		case 14:        {
				k=a.difference();
				cout<<"Required difference is:"<<k;
				cout<<endl<<"\n\tPress any key to go back....";
				ch=getch();
				if(ch=='\r')
				clrscr();
				break;
				}
		case 15:	{
				k=a.multiple();
				cout<<"Required multiple is:"<<k;
				cout<<endl<<"\n\tPress any key to go back....";
				ch=getch();
				if(ch=='\r')
				clrscr();
				break;
				}
		case 16:	{
				k=a.division();
				cout<<"Required division is:"<<k;
				cout<<endl<<"\n\tPress any key to go back....";
				ch=getch();
				if(ch=='\r')
				clrscr();
				break;
				}
		case 0:
		  {
			break;
			   }
		     }
		}while(option!=0);
	break;


case 3:
	exit(1);
	}
}while(opt1!=3);

	getch();
}



void start()                      // Display Start-Up Animation
	{

	 setbkcolor(0);
	 settextstyle(8,0,3);
	 setcolor(6);
	 outtextxy(40,10,"DEPARTMENT OF ELECTRICAL ENGINEERING");
	 settextstyle(8,0,2);
	 setcolor(5);
	 outtextxy(220,390,"DUAL FUNCTIONING DATA RECORDER");
	 setcolor(1);
	 outtextxy(10,335,"By");
	 settextstyle(7,0,2);
	 setcolor(12);
	 outtextxy(10,370,"064BEL344 ");
	 outtextxy(10,390,"064BEL338 ");
	 outtextxy(10,410,"064BEL335 ");

	int c=1;float k=0;

	moveto(320,445);
	settextstyle(5,0,2);
	settextjustify(1,0);
	setcolor(2);
	outtext("Loading Please Wait...");

	for(int i=0;i<=360;i++)
	{

		for(int j=65;j>=45;j--)
		{
			arc(320,220,0,i,2*j);
			gotoxy(40,14);
			printf("%.0f %",(++k/76));

		}


		  setcolor(c++);
}

	gotoxy(40,14);
	printf("    ");

}
