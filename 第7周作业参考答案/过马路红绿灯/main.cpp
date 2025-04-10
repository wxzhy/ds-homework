#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
#define MAXLENGTH 64
enum TRAFFICLIGHT {RED = 0, YELLOW, GREEN};

class TrafficLight
{
	int red, yellow, green;
	int status, time;		
public:
	TrafficLight(){status = -1, time = -1;}
	TrafficLight(int r, int y, int g, int s, int t):red(r), yellow(y), green(g), status(s), time(t){}
	TrafficLight(const TrafficLight& in):red(in.red), yellow(in.yellow), green(in.green), status(in.status), time(in.time){}
	TrafficLight& operator=(const TrafficLight& in)
	{
		red = in.red;
		yellow = in.yellow;
		green = in.green;
		status = in.status;
		time = in.time;
		return *this;
	}
	int GetStatus()
	{ 
		return status; 
	}
	void Print()
	{
		cout<<"initial status: "<<status<<" time: "<<time<<endl; 
	}
	int Waittime(int t)
	{
		cout<<"initial status: "<<status<<" time: "<<time<<" arrival time: "<<t<<endl;
		if(time >= t){//there is no status changing 
			if(status == 1){
				return time - t; 
			}else if(status == 2){
				return  time - t + red; //yellow have to stop 
			}else if(status == 3){
				return 0;
			}else{
				cout<<"status error"<<endl; 
				return -1;
			}
		}else{
			t -= time;
			int copy_status = status; 
//			copy_status = (copy_status + 1) % 3; //1 - red-0, 2 - yellow - 2, 3 - green- 1  
///////////////////////////////////////////////////////////////////////////////////////////////////
            // convert the status ////////////// 
			if(copy_status == 1) copy_status = 2;
			else if(copy_status == 2) copy_status = 1;
			else if(copy_status == 3) copy_status = 3; 
			else{
				cout<<"status error "<<endl;
				return -1;
			} 
			int light[3] = {red, green, yellow}; //the sequence is important!!!
			cout<<"after initial time status: "<<copy_status - 1<<" light[index] "<<light[copy_status - 1]<<" t: "<<t<<endl;
			while(light[copy_status - 1] < t){
				t -= light[copy_status - 1];
				copy_status = (copy_status + 1) % 3;
			}
			
			if(copy_status == 1){ // red 
				return light[copy_status - 1] - t; 
			}else if(copy_status == 3){ //yellow 
				return  light[copy_status - 1] - t + red; 
			}else if(copy_status == 2){ //green
				return 0;
			}else{
				cout<<"status error"<<endl; 
				return -1;
			}
		}

		return -1; 
	}
};

class Street{
	int id,passtime;
public:
	Street(){id = -1, passtime = 0;}
	Street(int i, int t):id(i), passtime(t){}
	Street(const Street& in):id(in.id), passtime(in.passtime){}
	Street& operator=(const Street& in)
	{
		id = in.id;
		passtime = in.passtime;
		return *this;
	}
	int GetId(){ return id;}
	void Print()
	{
		cout<<"id: "<<id<<" time: "<<passtime<<endl; 
	}
};
void ReadTrafficLight(fstream& file_pointer, int* data, int& street)
{
	int i = 0, val;
	char trafficlight[MAXLENGTH];
	
	if(file_pointer.getline(trafficlight, MAXLENGTH) == NULL) return; 
	
//	cout<<trafficlight<<endl;
	
	char* tokenPtr = strtok(trafficlight, " ");
	int counter = 0;
	while(tokenPtr != NULL){
//		cout<<tokenPtr<<endl;
		int val = atoi(tokenPtr);
		data[counter] = val;
		counter++;
//		cout<<"val: "<<val<<endl;
		tokenPtr = strtok(NULL, " ");
	}
	file_pointer>>street;
//	cout<<"street "<<street<<endl;
	
} 

void PrintList(int* data, int counter)
{
	cout<<"PrintList"<<endl; 
	int i = 0; 
	for(;i < counter;i++){
		cout<<data[i]<<" ";
	}
	cout<<endl;
}

void PrintStreet(Street* data, int counter)
{
	cout<<"PrintStreet"<<endl; 
	int i = 0; 
	for(;i < counter;i++){
		if(data[i].GetId() >= 0)data[i].Print();
	}
	cout<<endl;
}

void PrintTrafficLight(TrafficLight* data, int counter)
{
	cout<<"PrintTrafficLight"<<endl; 
	int i = 0; 
	for(;i < counter;i++){
		if(data[i].GetStatus() >= 0)data[i].Print();
	}
	cout<<endl;
}


void ReadStreetandTime(fstream& file_pointer,  Street* street_list, TrafficLight* trafficlight_list, int* traffic_list)
{
	
	char trafficlight[MAXLENGTH];
	int street_no = 0;
	int trafficlight_no = 0;
	while(file_pointer.eof() == false){
		if(file_pointer.getline(trafficlight, MAXLENGTH) == NULL) return;
//		cout<<trafficlight<<endl;
		char* tokenPtr = strtok(trafficlight, " ");

		if(tokenPtr != NULL){
			int val1 = atoi(tokenPtr);
			tokenPtr = strtok(NULL, " ");
			int val2 = atoi(tokenPtr);
			if(val1 == 0){
//				cout<<"street info: id"<<val1<<" time: "<<val2<<endl;	
				Street s(street_no, val2);
				street_list[street_no] = s;
				street_no++;
			}else{
				cout<<"traffic info "<<" ligth: "<<val1<<" time: "<<val2<<endl; 
				TrafficLight trlight(traffic_list[0], traffic_list[1], traffic_list[2], val1, val2);
				trafficlight_list[trafficlight_no] = trlight;
				trafficlight_no++;
			}
		}
	}
}

int ProcessStreetandTime(fstream& file_pointer,  int* traffic_list)
{
	int time = 0;
	char trafficlight[MAXLENGTH];
	int street_no = 0;
	int trafficlight_no = 0;
	while(file_pointer.eof() == false){
		if(file_pointer.getline(trafficlight, MAXLENGTH) == NULL) break;
		cout<<trafficlight<<endl;
		char* tokenPtr = strtok(trafficlight, " ");

		if(tokenPtr != NULL){
			int val1 = atoi(tokenPtr);
			tokenPtr = strtok(NULL, " ");
			int val2 = atoi(tokenPtr);
			if(val1 == 0){//street info
//				cout<<"street info: id"<<val1<<" time: "<<val2<<endl;	
				time += val2; 
			}else{
				cout<<"traffic info "<<" ligth: "<<val1<<" time: "<<val2<<endl; 
				TrafficLight trlight(traffic_list[0], traffic_list[1], traffic_list[2], val1, val2);
				int waittime = trlight.Waittime(time); 
				cout<<"waittime "<<waittime<<endl; 
				time += waittime;
			}
		}
	}
	return time;
}

int main()
{
	fstream dataFile;
	dataFile.open("data.txt", ios::in);
//	dataFile.open("data1.txt", ios::in);
//	dataFile.open("data2.txt", ios::in);
	if(!dataFile){
		cout<<"File open error!"<<endl;
		exit(0);
	}
	
	int* traffic_list = new int[3];
	int street_no;
	ReadTrafficLight(dataFile, traffic_list, street_no);
	cout<<"street no: "<<street_no<<endl;
	PrintList(traffic_list, 3);
	Street* street_list = new Street[street_no];
	TrafficLight* trafficlight_list = new TrafficLight[street_no];
//	ReadStreetandTime(dataFile, street_list, trafficlight_list, traffic_list);
//	PrintStreet(street_list, street_no);
//	PrintTrafficLight(trafficlight_list, street_no);
	
	int timecost = ProcessStreetandTime(dataFile, traffic_list);
	cout<<" time cost "<<timecost<<endl; 


	///////////////////////////////////////////////////////////////
	delete[] traffic_list;
	delete[] street_list; 
	delete[] trafficlight_list; 
	dataFile.close();
	return 0;
}
