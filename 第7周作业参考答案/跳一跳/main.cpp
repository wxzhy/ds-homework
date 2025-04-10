#include <iostream>
#include <fstream>
using namespace std;

void ReadData(fstream& file_pointer, int* data)
{
	int i = 0, val;
	while(file_pointer.eof() == false){
		file_pointer>>val;
		if(val == 1 || val == 2 || val == 0){
			data[i] = val;
			i++;
		}else
			cout<<"invalid value: "<<val<<endl;
	}
	
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

int JumScore(int* data, int counter)
{
	int score = 0;
	bool first_center = false; 
	int center_counter = 0;
	for(int i = 0;i < counter;i++){
		if(data[i] == 1){
			score += data[i];
			center_counter = 0;
			cout<<"i: "<<i<<" score: "<<score<<endl; 
		} 
		else if(data[i] == 2){
			if(first_center == false){
				first_center = true;
				score += data[i];
				center_counter++;
				cout<<"i: "<<i<<" score: "<<score<<endl;
				continue;
			}
			if(data[i - 1] == 1){
				score += data[i];
				center_counter++;
				cout<<"i: "<<i<<" score: "<<score<<endl;
				continue;
			}
			score += data[i] + center_counter * data[i];
			center_counter++;
			cout<<"i: "<<i<<" score: "<<score<<endl;
		}else if(data[i] == 0)break;
		
	}
	return score;
}

int main()
{
	fstream dataFile;
//	dataFile.open("data.txt", ios::in);
//	dataFile.open("data1.txt", ios::in);
	dataFile.open("data2.txt", ios::in);
	if(!dataFile){
		cout<<"File open error!"<<endl;
		exit(0);
	}
	int val, num = 0;
	while(dataFile.eof() == false){
		dataFile>>val;
		num++;
	}
	cout<<"num: "<<num<<endl;
	dataFile.seekg(0, ios::beg);
	
	int* num_list = new int[num];
	ReadData(dataFile, num_list);
	PrintList(num_list, num);
    int score = JumScore(num_list, num);
    cout<<"score: "<<score<<endl; 
	///////////////////////////////////////////////////////////////
	delete[] num_list;

	dataFile.close();
	return 0;
}
