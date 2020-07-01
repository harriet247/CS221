
#include "stats.h"
#include <iostream>


double stats::checkSat(int xLoc,int yLoc,double currSat){
	//int acc=-1;
	if(xLoc>0&&yLoc>0){
		return sumSat[xLoc][yLoc-1]+sumSat[xLoc-1][yLoc]
		-sumSat[xLoc-1][yLoc-1]+currSat;
	
	}
	if(xLoc==0&&yLoc>0)
		return sumSat[xLoc][yLoc-1]+currSat;
	if(xLoc>0&&yLoc==0)
		return sumSat[xLoc-1][yLoc]+currSat;
	return currSat;
	//return -1;
}
double stats::checkLum(int xLoc,int yLoc,double currLum){
	//int acc=-1;
	if(xLoc>0&&yLoc>0){
		return sumLum[xLoc][yLoc-1]+sumLum[xLoc-1][yLoc]
		-sumLum[xLoc-1][yLoc-1]+currLum;
	
	}
	if(xLoc==0&&yLoc>0)
		return sumLum[xLoc][yLoc-1]+currLum;
	if(xLoc>0&&yLoc==0)
		return sumLum[xLoc-1][yLoc]+currLum;
	// if(xLoc==0&&yLoc==0)
		return currLum;
	// return -1;
}

double stats::checkSumY(int xLoc,int yLoc,double currHueY){
	//int acc=-1;
	
	if(xLoc>0&&yLoc>0){
		return sumHueY[xLoc][yLoc-1]+sumHueY[xLoc-1][yLoc]
		-sumHueY[xLoc-1][yLoc-1]+currHueY;
	
	}
	if(xLoc==0&&yLoc>0)
		return sumHueY[xLoc][yLoc-1]+currHueY;
	if(xLoc>0&&yLoc==0)
		return sumHueY[xLoc-1][yLoc]+currHueY;
	// if(xLoc==0&&yLoc==0)
		return currHueY;
	//return -1;
}
double stats::checkSumX(int xLoc,int yLoc,double currHueX){
	
	//int acc=-1;
	if(xLoc>0&&yLoc>0){
		return sumHueX[xLoc][yLoc-1]+sumHueX[xLoc-1][yLoc]
		-sumHueX[xLoc-1][yLoc-1]+currHueX;
	
	}
	if(xLoc==0&&yLoc>0)
		return sumHueX[xLoc][yLoc-1]+currHueX;
	if(xLoc>0&&yLoc==0)
		return sumHueX[xLoc-1][yLoc]+currHueX;
	// if(xLoc==0&&yLoc==0)
		return currHueX;
	//return -1;
}

stats::stats(PNG & im){
	int width=(int)im.width();
	int height=(int)im.height();

	//vector<vector<double>> sumHueX()
	// sumHueX=vector<vector<double>> temp(height,vector<double>(width,0)); 
	// sumHueY=vector<vector<double>> temp(height,vector<double>(width,0)); 
	// sumSat=vector<vector<double>> temp(height,vector<double>(width,0)); 
	// sumLum=vector<vector<double>> temp(height,vector<double>(width,0)); 
	// for(int x=0;x<=width;x++){
	// 	for(int y=0;y<=height;y++){

	// 	}
	//}
  sumHueX.resize(width, (vector<double>) height);
  sumHueY.resize(width, (vector<double>) height);
  sumSat.resize(width, (vector<double>) height);
  sumLum.resize(width, (vector<double>) height);
  hist.resize(width, vector<vector<int>> (height, vector<int>(36, 0)));
	// sumHueX.resize(height);
	// sumHueY.resize(height);
	// sumSat.resize(height);
	// sumLum.resize(height);
	for(int x=0;x<width;x++){

		// sumHueX[x].resize(width);
		// sumHueY[x].resize(width);
		// sumSat[x].resize(width);
		// sumLum[x].resize(width);
		for(int y=0;y<height;y++){

			HSLAPixel* curr=im.getPixel(x,y);
			double hueRadian=(curr->h)*PI/180;
			double hueX=cos(hueRadian);
			double hueY=sin(hueRadian);
			double currSat=curr->s;//s?
			double currLum=curr->l;
			double currHue=curr->h;
			int currK = currHue/ 10;

			//sumHueX and sumHueY
			sumHueX[x][y]=checkSumX(x,y,hueX);
			sumHueY[x][y]=checkSumY(x,y,hueY);

			//sumSat and sumLum
			sumSat[x][y]=checkSat(x,y,currSat);
			sumLum[x][y]=checkLum(x,y,currLum);

			//hist[i][j][k]
			//checkHist(x,y,currHue);
			//same cases for hist
			// hish[x][y][]
			if(x>0&&y>0){
			// 	sumHueX[x][y]=sumHueX[x][y-1]+sumHueX[x-1][y]
		 //                     -sumHueX[x-1][y-1]+hueX;
			// 	sumHueY[x][y]=sumHueY[x][y-1]+sumHueY[x-1][y]
		 //                     -sumHueY[x-1][y-1]+hueY;
		 //        sumSat[x][y]=sumSat[x][y-1]+sumSat[x-1][y]
		 //                     -sumSat[x-1][y-1]+currSat;
		 //        sumLum[x][y]=sumLum[x][y-1]+sumLum[x-1][y]
		 //                     -sumLum[x-1][y-1]+currLum;
		        for(int k=0;k<36;k++){
					hist[x][y][k]=hist[x-1][y][k]+hist[x][y-1][k]-hist[x-1][y-1][k];
					}             
				

			}
			if(x>0&&y==0){
			// 	sumHueX[x][y]=sumHueX[x-1][y]+hueX;
			// 	sumHueY[x][y]=sumHueY[x-1][y]+hueY;
		 //        sumSat[x][y]=sumSat[x-1][y]+currSat;
		 //        sumLum[x][y]=sumLum[x-1][y]+currLum;

				for (int k = 0; k < 36; k++){
					hist[x][y][k] = hist[x-1][y][k];
				}
			}
			if(x==0&&y>0){
			// 	sumHueX[x][y]=sumHueX[x][y-1]+hueX;
			// 	sumHueY[x][y]=sumHueY[x][y-1]+hueY;
		 //        sumSat[x][y]=sumSat[x][y-1]+currSat;
		 //        sumLum[x][y]=sumLum[x][y-1]+currLum;
				for(int k=0;k<36;k++){
					hist[x][y][k]=hist[x][y-1][k];
				}
			}
		
			hist[x][y][currK]++;
			

			// for(int k=0;k<36;k++){
			// 	hist[x][y][k]=checkHist(im,x,y,k);//int number 
				//hist[x][y][k]++;
			//}

			//int k=checkBin(x,y);



		}
	}
	
	
	
/* your code here */

}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){
	 return (lr.first-ul.first + 1) * (lr.second-ul.second + 1);

/* your code here */

}

HSLAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){
	long tolArea=rectArea(ul,lr);

	int xLoc1=ul.first;
	int yLoc1=ul.second;
	int xLoc2=lr.first;
	int yLoc2=lr.second;

	double tolX=sumHueX[xLoc2][yLoc2];
	double tolY=sumHueY[xLoc2][yLoc2];
	double tolSat=sumSat[xLoc2][yLoc2];
	double tolLum=sumLum[xLoc2][yLoc2];
	// double avgX=sumHueX[xLoc2][yLoc2]/tolArea;
	// double avgY=sumHueY[xLoc2][yLoc2]/tolArea;
	// double avgSat=sumSat[xLoc2][yLoc2]/tolArea;
	// double avgLum=sumLum[xLoc2][yLoc2]/tolArea;

	//!!! to compute the average and then convert from 
	//cartesian back to polar coordinates. 
	// For lum and sat, you just need to compute the average. For hueX and hueY, average each value first, but then compute the final average hue using:
	// atan2(averageHueY, averageHueX) * 180 / PI
	// Return the hue, sat, and lum as a HSLAPixel

	if(xLoc1>=1){
		// avgX=(sumHueX[xLoc2][yLoc2]-sumHueX[xLoc1-1][yLoc2])/tolArea;
		// avgY=(sumHueY[xLoc2][yLoc2]-sumHueY[xLoc1-1][yLoc2])/tolArea;
		// avgSat=(sumSat[xLoc2][yLoc2]-sumSat[xLoc1-1][yLoc2])/tolArea;
		// avgLum=(sumLum[xLoc2][yLoc2]-sumLum[xLoc1-1][yLoc2])/tolArea;
		tolSat -= sumSat[xLoc1-1][yLoc2];
    	tolLum -= sumLum[xLoc1-1][yLoc2];
    	tolX -= sumHueX[xLoc1-1][yLoc2];
    	tolY -= sumHueY[xLoc1-1][yLoc2];
		
	}
	if(yLoc1>=1){
		// avgX=(sumHueX[xLoc2][yLoc2]-sumHueX[xLoc2][yLoc1-1])/tolArea;
		// avgY=(sumHueY[xLoc2][yLoc2]-sumHueY[xLoc2][yLoc1-1])/tolArea;
		// avgSat=(sumSat[xLoc2][yLoc2]-sumSat[xLoc2][yLoc1-1])/tolArea;
		// avgLum=(sumLum[xLoc2][yLoc2]-sumLum[xLoc2][yLoc1-1])/tolArea;
		 tolSat -= sumSat[xLoc2][yLoc1-1];
         tolLum -= sumLum[xLoc2][yLoc1-1];
    	 tolX -= sumHueX[xLoc2][yLoc1-1];
    	 tolY -= sumHueY[xLoc2][yLoc1-1];
		
	}
	if(xLoc1>=1&&yLoc1>=1){
		// avgX=(sumHueX[xLoc2][yLoc2]+sumHueX[xLoc1-1][yLoc1-1])/tolArea;
		// avgY=(sumHueY[xLoc2][yLoc2]+sumHueY[xLoc1-1][yLoc1-1])/tolArea;
		// avgSat=(sumSat[xLoc2][yLoc2]+sumSat[xLoc1-1][yLoc1-1])/tolArea;
		// avgLum=(sumLum[xLoc2][yLoc2]+sumLum[xLoc1-1][yLoc1-1])/tolArea;
		tolSat += sumSat[xLoc1-1][yLoc1-1];
   		tolLum += sumLum[xLoc1-1][yLoc1-1];
    	tolX += sumHueX[xLoc1-1][yLoc1-1];
    	tolY += sumHueY[xLoc1-1][yLoc1-1];
		//h=atan2(avgY,avgX)*180/PI;
		
	}
		double h=atan2(tolY/tolArea,tolX/tolArea)*180/PI;
		if(h<0) h+=360;
		double a=1.0;
		HSLAPixel ret(h,tolSat/tolArea,tolLum/tolArea,a);

		return ret;
	// double avgX=(sumHueX[xLoc2][yLoc2]-sumHueX[xLoc1][yLoc1])/tolArea;
	// double avgY=(sumHueY[xLoc2][yLoc2]-sumHueY[xLoc1][yLoc1])/tolArea;
	
	
	// double s=(sumSat[xLoc2][yLoc2]-sumSat[xLoc1][yLoc1])/tolArea;
	// double l=(sumLum[xLoc2][yLoc2]-sumLum[xLoc1][yLoc1])/tolArea;
	// cout<<""<<avgY<<endl;
	// cout<<""<<avgX<<endl;
	//HSLAPixel *avgColor=new HSLAPixel(h,avgSat,avgLum);

	// avgColor->h=h;
	// avgColor->s=avgSat;
	// avgColor->l=avgLum;


/* your code here */
}

vector<int> stats::buildHist(pair<int,int> ul, pair<int,int> lr){
/* your code here */

	int xLoc1=ul.first;
	int yLoc1=ul.second;
	int xLoc2=lr.first;
	int yLoc2=lr.second;
	vector<int> curr(hist[xLoc2][yLoc2]);
	vector<int> temp;
	
	if(xLoc1>=1){
		temp=hist[xLoc1-1][yLoc2];
		for(int k =0;k<36;k++){
			curr[k]-=temp[k];
		}
	}
	if(yLoc1>=1){
		temp=hist[xLoc2][yLoc1-1];
		for(int k=0;k<36;k++){
			curr[k]-=temp[k];
		}

	}
	if(xLoc1>=1&&yLoc1>=1){
		temp=hist[xLoc1-1][yLoc1-1];
		for(int k=0;k<36;k++){
			curr[k]+=temp[k];
		}
	}

	return curr;
}

// takes a distribution and returns entropy
// partially implemented so as to avoid rounding issues.
double stats::entropy(vector<int> & distn,int area){

    double entropy = 0.;

/* your code here */

    for (int i = 0; i < 36; i++) {
        if (distn[i] > 0 ) 
            entropy += ((double) distn[i]/(double) area) 
                                    * log2((double) distn[i]/(double) area);
    }

    return  -1 * entropy;

}

double stats::entropy(pair<int,int> ul, pair<int,int> lr){
	vector<int> tempHist=buildHist(ul,lr);
	int tolArea=rectArea(ul,lr);
	// double entropy=0.;

	// for(int i =0;i<36;i++){
	// 	if(tempHist[i]>0){
	// 		entropy+=((double)tempHist[i]/tolArea)*log2((double)tempHist[i]/tolArea);
	// 	}
	// }

	// return -1*entropy;
	return entropy(tempHist,tolArea);
/* your code here */

}
