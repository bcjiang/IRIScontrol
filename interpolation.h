#include <iostream>
#include<fstream>
#include<cmath>
using namespace std;

double find_motor(double roll_test,double pitch_test, double datapoint[48][3]){
	//double datapoint[48][3];
	
	//int x,y;
	//ifstream in("motor1.txt");
	//for(x=0;x<48;x++){
	//	for(y=0;y<3;y++){
	//		in>>datapoint[x][y];
	//		//cout<<datapoint[x][y];
	//	}
	//}
	//in.close();

	//double roll_test,pitch_test;
	//roll_test = 2;
	//pitch_test = 3;
	double dist[48];
	int short_index = 0;
	int shorter_index = 0;
	int shortest_index = 0;
	double short_dist = 10000;
	double shorter_dist = 10000;
	double shortest_dist = 10000;
	for(int i = 0; i<48; i++){
		dist[i] = sqrt(abs(pow(roll_test - datapoint[i][0],2) + pow(pitch_test - datapoint[i][1],2)));
		if(dist[i] < shortest_dist){
			short_dist = shorter_dist;
			short_index = shorter_index;
			shorter_dist = shortest_dist;
			shorter_index = shortest_index;
			shortest_dist = dist[i];
			shortest_index = i;
		}
		else{
			if(dist[i] < shorter_dist){
				short_dist = shorter_dist;
				short_index = shorter_index;
				shorter_dist = dist[i];
				shorter_index = i;
			}
			else{
				if(dist[i] < short_dist){
					short_dist = dist[i];
					short_index = i;
				}
			}
		}
	}
	
    double x1,x2,x3,y1,y2,y3,mu,lambda,output_value;
	x1 = datapoint[shorter_index][0] - datapoint[shortest_index][0];
	x2 = datapoint[short_index][0] - datapoint[shortest_index][0];
	y1 = datapoint[shorter_index][1] - datapoint[shortest_index][1];
	y2 = datapoint[short_index][1] - datapoint[shortest_index][1];
	x3 = roll_test - datapoint[shortest_index][0];
	y3 = pitch_test - datapoint[shortest_index][1];

	mu = (x2*y3 - x3*y2)/(x2*y1 - x1*y2);
	lambda = (x1*y3 - x3*y1)/(x1*y2 - x2*y1);
	
	output_value = datapoint[shortest_index][2] 
	               + mu * (datapoint[shorter_index][2] - datapoint[shortest_index][2])
				   + lambda * (datapoint[short_index][2] - datapoint[shortest_index][2]);
	
    return output_value;
}

