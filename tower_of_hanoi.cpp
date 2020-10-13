#include<cstdlib>
#include<iostream>             
#include<vector>
#include<typeinfo>
#include<iomanip>
using namespace std;

vector<int> dsize(vector<int> t1int, vector<int> t2int, vector<int> t3int); //output vector indicating size of topmost disc
vector<string> convertstr(vector<int> t); //translates disc sizes into strings for output
bool iserr(int from,int to); //check for input validity
bool isillegal(int from, int to, vector<int> t1int, vector<int> t2int, vector<int> t3int); //check for illegal move
bool iswin(vector<int> t3int); //check for win condition

int main()
{
	int from,to; //integers for user input
	vector<int> numdisc(3); //track number of discs in each tower
	numdisc[0]=8; numdisc[1]=0; numdisc[2]=0; //initial number of discs on each tower
	vector<int> topsize(3); //record size of top disc for each tower
	int nummove = 0; //for counting number of moves made
	
	//initialize
	vector<int> t1int, t2int, t3int; //tower stacks disc size
	vector<string> t1str,t2str,t3str; //tower stacks string
	
	for(int i=0;i<8;i++)
	{
		t1int.push_back(i+1);
		t2int.push_back(0);
		t3int.push_back(0);
	}
	
//	//cheat code for checking approach to win condition
//	numdisc[0]=1; numdisc[1]=0; numdisc[2]=7;
//	for(int i=0;i<8;i++)
//	{
//		t1int[i] =0;
//		t3int[i]=i+1;
//	}
//	t1int[7]=1;
//	t3int[0]=0;
	
	//convert into string for output
	t1str = convertstr(t1int);
	t2str = convertstr(t2int);
	t3str = convertstr(t3int);
	
	//output initial arrangement
	for(int i=0;i<8;i++)
	{
		cout << setw(20) << t1str[i] << setw(20) <<t2str[i] << setw(20) << t3str[i] << endl;
	}
		
	cout << setw(20) << "       1        " << setw(20) << "       2       " << setw(20)<< "       3       " << endl;
	
	while(iswin(t3int)==false)
	{
		nummove++;
		cout << "Enter your move: "; 
		cin >>  from >> to;
			
		//check for invalid input. if there is an error, show message and prompt for input again
		while(iserr(from,to)==true || isillegal(from,to,t1int,t2int,t3int)==true)
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input or illegal move, please enter two integers between 1 and 3" << endl;
			cout << "Enter your move: " << endl;
			cin >>  from >> to;
		}
		
		topsize = dsize(t1int,t2int,t3int);
				
		//move disc on vectors
		if(from==1)
		{
			t1int[8-numdisc[0]]=0;
			numdisc[0]--;
		}
	
		if(from==2)
		{
			t2int[8-numdisc[1]]=0;
			numdisc[1]--;
		}
	
		if(from==3)
		{
			t3int[8-numdisc[2]]=0;
			numdisc[2]--;
		}
	
		if(to==1)
		{
			t1int[7-numdisc[0]]=topsize[from-1];
			numdisc[0]++;
		}
		
		if(to==2)
		{
			t2int[7-numdisc[1]]=topsize[from-1];
			numdisc[1]++;
		}
		
		if(to==3)
		{
			t3int[7-numdisc[2]]=topsize[from-1];
			numdisc[2]++;
		}
		
		//output updated vectors
		t1str = convertstr(t1int);
		t2str = convertstr(t2int);
		t3str = convertstr(t3int);
		
		for(int i=0;i<8;i++)
		{
			cout << setw(20) << t1str[i] << setw(20) <<t2str[i] << setw(20) << t3str[i] << endl;
		}
	
		cout << setw(20) << "       1       " << setw(20) << "       2       " << setw(20)<< "       3       " << endl;
	
	}
	
	cout << "You Won!"	<< endl;
	cout << "Number of moves made: " << nummove	<< endl;
		
	return 0;
}

//function to check for invalid inputs
bool iserr(int from, int to)
{
	bool err = true;
	if(from!=to && from <4 && from >0 && to >0 && to <4)
		err = false;	
	return err;
}

//function to output a vector of the size of the disc at the top
vector<int> dsize(vector<int> t1int, vector<int> t2int, vector<int> t3int)
{
	vector<int> dsize(3); //record size of top disc for each tower
	dsize[0] = 0;
	dsize[1] = 0;
	dsize[2] = 0;
	
	for(int i=0;i<8;i++)
	{
		if(t1int[i]!=0)
		{
			dsize[0] = t1int[i];
			break;
		}
	}
	
	for(int i=0;i<8;i++)
	{
		if(t2int[i]!=0)
		{
			dsize[1] = t2int[i];
			break;
		}
	}
	
	for(int i=0;i<8;i++)
	{
		if(t3int[i]!=0)
		{
			dsize[2] = t3int[i];
			break;
		}
	}
	
	return dsize;
}

//function to check for illegal move
bool isillegal(int from, int to, vector<int> t1int, vector<int> t2int, vector<int> t3int)
{
	bool illegal = false;
	vector<int> dsize(3); //record size of top disc for each tower
	
	for(int i=0;i<8;i++)
	{
		if(t1int[i]!=0)
		{
			dsize[0] = t1int[i];
			break;
		}
	}
	
	for(int i=0;i<8;i++)
	{
		if(t2int[i]!=0)
		{
			dsize[1] = t2int[i];
			break;
		}
	}
	
	for(int i=0;i<8;i++)
	{
		if(t3int[i]!=0)
		{
			dsize[2] = t3int[i];
			break;
		}
	}
	
	if(dsize[from-1]==0 || (dsize[from-1]>dsize[to-1] && dsize[to-1]!=0))
		illegal = true;
	
	return illegal; 
}

//function to populate string vectors
vector<string> convertstr(vector<int> t)
{
	vector<string> t_str(8);
	vector<string> disc(9);
	disc[0] = "                ";
	disc[1] = "       --       ";
	disc[2] = "      ----      ";
	disc[3] = "     ------     ";
	disc[4] = "    --------    ";
	disc[5] = "   ----------   ";
	disc[6] = "  ------------  ";
	disc[7] = " -------------- ";
	disc[8] = "----------------";
	
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<=8;j++)
		{
			if(t[i]==j)
				t_str[i]=disc[j];
		}	
	}
	
	return t_str;
}

//function to check for win condition
bool iswin(vector<int> t3int)
{
	bool win = false;
	if(t3int[0]!=0)
		win=true;
	return win;
}
