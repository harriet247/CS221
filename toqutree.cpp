
/**
 *
 * toqutree (pa3)
 * significant modification of a quadtree .
 * toqutree.cpp
 * This file will be used for grading.
 *
 */

#include "toqutree.h"

toqutree::Node::Node(pair<int,int> ctr, int dim, HSLAPixel a)
	:center(ctr),dimension(dim),avg(a),NW(NULL),NE(NULL),SE(NULL),SW(NULL)
	{}

toqutree::~toqutree(){
	clear(root);
}

toqutree::toqutree(const toqutree & other) {
	root = copy(other.root);
}


toqutree & toqutree::operator=(const toqutree & rhs){
	if (this != &rhs) {
		clear(root);
		root = copy(rhs.root);
	}
	return *this;
}

toqutree::toqutree(PNG & imIn, int k){ 

	root=buildTree(&imIn,k);

/* This constructor grabs the 2^k x 2^k sub-image centered */
/* in imIn and uses it to build a quadtree. It may assume  */
/* that imIn is large enough to contain an image of that size. */

/* your code here */

//NOTE: Traverse the pixels in the green square ,looking for the one which 
	//minimizes the average entropy (described below) over the 4 squares it determines
	//mni entropy --> upper left corner of the SE quadrant of the 4-way split
				//-->the center
		//considering that the edges of the square image wrap around to meet.
    //grab the sub-image
	


	//HSLAPixel * currAvg=imIn.getPixel();
//call the buildtree

}

int toqutree::size() {
/* your code here */
	return sizeHelper(root);
}

int toqutree::sizeHelper(Node * croot){
	if(croot==NULL) return 0;
	return sizeHelper(croot->SE)+sizeHelper(croot->SW)+sizeHelper(croot->NE)+sizeHelper(croot->NW)+1;
}

toqutree::Node * toqutree::buildTree(PNG * im, int k) {

/* your code here */

// Note that you will want to practice careful memory use
// In this function. We pass the dynamically allocated image
// via pointer so that it may be released after it is used .
// similarly, at each level of the tree you will want to 
// declare a dynamically allocated stats object, and free it
// once you've used it to choose a split point, and calculate
// an average.
	Node * curr;
	//stats currStat(imIn);
	//int xSplit=(2^(k-1))-1;
	unsigned int width=(unsigned int)pow(2,k);
	int xSplit=width-1;
	int ySplit=xSplit;
	if(k==0){
		HSLAPixel * temp=im->getPixel(0,0);
		pair<int,int> c(0,0);
		curr=new Node(c,k,*temp);
		temp=NULL;
		delete temp;
		//cout<<"reach 0"<<endl;
		// curr->center=c;
		// curr->dimension=k;
		// curr->avg=*temp;
	}
	//base case
	else{
		PNG *tempPNG=new PNG(width*2,width*2);

		for(unsigned int x=0;x<width;x++){
			for(unsigned int y=0;y<width;y++){
				HSLAPixel *fillP=im->getPixel(x,y);
				//HSLAPixel *currP=curr->getPixel(x,y);
				copyColor(tempPNG->getPixel(x,y),fillP);
				copyColor(tempPNG->getPixel(x+width,y),fillP);
				copyColor(tempPNG->getPixel(x,y+width),fillP);
				copyColor(tempPNG->getPixel(x+width,y+width),fillP);
			}
		}
		//dynamic allocation of stat
		stats *currStat=new stats(*tempPNG);
		//cout<<"reach stat"<<endl;
		pair<int,int> ul(0,0);
 		pair<int,int> lr(xSplit,ySplit);
		HSLAPixel tempAvg=currStat->getAvg(ul,lr);//avg
		//cout<<"Reach tempavg"<<endl;
		pair<int,int> tempCenter=getCenter(currStat,width);//center
		//cout<<"reach center"<<endl;
		
		//cout<<"reach 1"<<endl;
		//curr->dimension=k;
		//pair<int,int> tempCenter=curr->center;
		//wrap
		
		//cout<<"reach 2"<<endl;
		
		
		if(k==1){
			// pair<int,int> baseCenter(1,1);
			// curr->center=baseCenter;
			tempCenter.first=1;
			tempCenter.second=1;
			//cout<<"reach 3"<<endl;
		}
		curr=new Node(tempCenter,k,tempAvg);
		//4 children pngs
		//1)SE
		PNG *SE=new PNG(width/2,width/2);
		iterateNewPNG(tempPNG,SE,width,tempCenter.first,tempCenter.second);
		// //2)SW
		PNG *SW=new PNG(width/2,width/2);
		iterateNewPNG(tempPNG,SW,width,tempCenter.first+width/2,tempCenter.second);
		// //3)NE
		PNG *NE=new PNG(width/2,width/2);
		iterateNewPNG(tempPNG,NE,width,tempCenter.first,tempCenter.second+width/2);
		// //4)NW
		PNG *NW=new PNG(width/2,width/2);
		iterateNewPNG(tempPNG,NW,width,tempCenter.first+width/2,tempCenter.second+width/2);
		
		currStat=NULL;
		tempPNG=NULL;
		delete currStat;
		delete tempPNG;

		curr->SE=buildTree(SE,k-1);
		curr->SW=buildTree(SW,k-1);
		curr->NE=buildTree(NE,k-1);
		curr->NW=buildTree(NW,k-1);

		SE=NULL;
		SW=NULL;
		NE=NULL;
		NW=NULL;

		delete SE;
		delete SW;
		delete NE;
		delete NW;

	}

	return curr;

	// curr->center.first=xSplit;
	// curr->center.second=ySplit;
	//curr->dim=k;
	//need a stat to calculate the average
	//root=curr;

	//children set up 
	//look for the mim entropy 
	// pair<int,int> ul2(xSplit,ySplit);
	// long temp=currStat.entropy(ul2,ul2);
	// int xLoc=xSplit;
	// int yLoc=ySplit;
	// for(int x=xSplit;x<2^(k-1);x++){
	// 	for(int y=ySplit;y<2^(k-1);y++){
	// 		pair<int,int> lr2(x,y);
	// 		long curr=currStat.entropy(ul2,lr2);
	// 		if(curr<temp){
	// 			temp= curr;
	// 			xLoc=x;
	// 			yLoc=y;
	// 		}
	// 	}
	// }

}
void toqutree::iterateNewPNG(const PNG *fill,PNG*& dist,unsigned int width,int xLoc,int yLoc){
	//PNG *curr=PNG(width/2,width/2);
	for(unsigned int x=0;x<width/2;x++){
		for(unsigned int y=0;y<width/2;y++){
			copyColor(dist->getPixel(x,y),fill->getPixel(xLoc+x,yLoc+y));
		}
	}
	//return curr;
}


PNG toqutree::iterateAsistPNG(PNG * fill,unsigned int width,unsigned int height){
	// PNG *curr=new PNG(width*2,height*2);
	
	// return *curr;
}

pair<int,int> toqutree::getCenter(stats *stats,unsigned int width){
	//vector<int> currHist.resize(width/2);
	pair<int,int> temp;
    
    double tempMin=9999999999999.;
	for(unsigned int x=0;x<width/2;x++){
		for(unsigned int y=0;y<width/2;y++){
		    //上下左右都要加一遍
		    double tempSum=0.;
		    //1)SE
			tempSum+=stats->entropy(pair<int,int>(x+width/4,y+width/4),pair<int,int>(x+width/4+width/2,y+width/4+width/2));
			//cout<<"rse"<<endl;
			//2)SW
			//cout<<stats->entropy(pair<int,int>(x+width/4+width/2,y+width/4),pair<int,int>(x+width/4+width/2+width/2,y+width/4+width/2));
			tempSum+=stats->entropy(pair<int,int>(x+width/4+width/2,y+width/4),pair<int,int>(x+width/4+width/2+width/2,y+width/4+width/2));
			//cout<<"rsw"<<endl;
			//3)NE
			tempSum+=stats->entropy(pair<int,int>(x+width/4,y+width/4+width/2),pair<int,int>(x+width/4+width/2,y+width/4+width/2+width/2));
			//cout<<"rne"<<endl;
			//4)NW
			tempSum+=stats->entropy(pair<int,int>(x+width/4+width/2,y+width/4+width/2),pair<int,int>(x+width/4+width/2+width/2,y+width/4+width/2+width/2));
			//cout<<"r"<<endl;
			if(tempSum<tempMin){
				tempMin=tempSum;
				temp.first=x;
				temp.second=y;
			}
			//tempSum+=stats->entropy(pair<int,int>(x+width/4,y+width/4+width/2),pair<int,int>());
		}
	}
	//cout<<""<<temp.first<<endl;	cout<<""<<temp.second<<endl;

	return temp;
}

// double toqutree::findMin(double tempSum){

// }

void toqutree::copyColor(HSLAPixel * pixel, const HSLAPixel * other){
	pixel->h=other->h;
	pixel->s=other->s;
	pixel->l=other->l;
	pixel->a=other->a;
}

PNG toqutree::render(){

// My algorithm for this problem included a helper function
// that was analogous to Find in a BST, but it navigated the 
// quadtree, instead.

/* your code here */
	return renderHelper(root);

}

PNG toqutree::renderHelper(const Node * croot){
	//four cases
	unsigned int width=(unsigned int)pow(2,croot->dimension);
	unsigned int height=width;
	PNG temp(width,width);
	if(croot->NW==NULL){
		for(unsigned int x=0;x<width;x++){
			for(unsigned int y=0;y<height;y++){
				HSLAPixel currAvg=croot->avg;
				copyColor(temp.getPixel(x,y),&currAvg);
			}
		}
	}
	else{
		//1)SE
		PNG currSE=renderHelper(croot->SE);
		for(unsigned int x=0;x<width/2;x++){
			for(unsigned int y=0;y<height/2;y++){
				unsigned int distX=(croot->center.first+x )%width;
				unsigned int distY=(croot->center.second+y)%width;
				HSLAPixel * currSEP=currSE.getPixel(x,y);
				HSLAPixel * tempP=temp.getPixel(distX,distY);
				copyColor(tempP,currSEP);

			}
		}

		//2)SW
		PNG currSW=renderHelper(croot->SW);
		for(unsigned int x=0;x<width/2;x++){
			for(unsigned int y=0;y<height/2;y++){
				unsigned int distX=(croot->center.first+x +width/2)%width;
				unsigned int distY=(croot->center.second+y)%width;
				HSLAPixel * currSWP=currSW.getPixel(x,y);
				HSLAPixel * tempP=temp.getPixel(distX,distY);
				copyColor(tempP,currSWP);

			}
		}
		//3)NE
		PNG currNE=renderHelper(croot->NE);
		for(unsigned int x=0;x<width/2;x++){
			for(unsigned int y=0;y<height/2;y++){
				unsigned int distX=(croot->center.first+x )%width;
				unsigned int distY=(croot->center.second+y+width/2)%width;
				HSLAPixel * currNEP=currNE.getPixel(x,y);
				HSLAPixel * tempP=temp.getPixel(distX,distY);
				copyColor(tempP,currNEP);

			}
		}
		PNG currNW=renderHelper(croot->NW);
		for(unsigned int x=0;x<width/2;x++){
			for(unsigned int y=0;y<height/2;y++){
				unsigned int distX=(croot->center.first+x +width/2)%width;
				unsigned int distY=(croot->center.second+y+width/2)%width;
				HSLAPixel * currNWP=currNW.getPixel(x,y);
				HSLAPixel * tempP=temp.getPixel(distX,distY);
				copyColor(tempP,currNWP);

			}
		}
		//4)NW
	}
	return temp;
	

}

// PNG toqutree::renderLoopHelper(const PNG& fill, PNG* dist,int xLoc,int yLoc,unsigned int width){

// }

/* oops, i left the implementation of this one in the file! */
void toqutree::prune(double tol){

	//prune(root,tol);
	cout<<"helper start"<<endl;
	pruneHelper(root,tol);

}

void toqutree::pruneHelper(Node*& croot,double tol){
	//A node is pruned if all of the leaves in its subtree are
	// within tolerance of its average. 

	//return if null or have no children 
	cout<<"first start"<<endl;
	if(croot==NULL||(croot->NW==NULL&&croot->NE==NULL&&
		croot->SW==NULL&&croot->SE==NULL)) {
		cout<<"kong"<<endl;
		return;
	}
	cout<<"determine start"<<endl;
	if(determinePrune(croot,croot,tol)){
		cout<<"4 prune"<<endl;
		clear(croot->NW);
		clear(croot->NE);
		clear(croot->SW);
		clear(croot->SE);
		// croot->NW=NULL;

		// croot->NE=NULL;
		// croot->SW=NULL;
		// croot->SE=NULL;

	}
		cout<<"recur"<<endl;
		pruneHelper(croot->NW,tol);
		pruneHelper(croot->NE,tol);
		pruneHelper(croot->SW,tol);
		pruneHelper(croot->SE,tol);
	


}

bool toqutree::determinePrune(Node* croot,Node* child,double tol){
	//HSLAPixel currColor=croot->avg;
	// int nwPrune=determinePrune(croot->NW,tol,croot->avg);
	// int nePrune=determinePrune(croot->NE,tol,croot->avg);
	// int swPrune=determinePrune(croot->SW,tol,croot->avg);
	// int sePrune=determinePrune(croot->SE,tol,croot->avg);

	 cout<<"fist de"<<endl;
	if(child==NULL) {
		cout<<"base"<<endl;
		return true;

		}
	if(child->NW==NULL&&child->NE==NULL&&
		child->SW==NULL&&child->SE==NULL) {
		cout<<"no chil"<<endl;
		return (croot->avg.dist(child->avg)<=tol);
	}
	else {
		bool nwbool=0;
		bool nebool=0;
		bool swbool=0;
		bool sebool=0;
		if(child->NW!=NULL){
			nwbool=determinePrune(croot,child->NW,tol);
		}
		if(child->NE!=NULL){
			nebool=determinePrune(croot,child->NE,tol);
		}
		if(child->SW!=NULL){
			swbool=determinePrune(croot,child->SW,tol);
		
		}
		if(child->SE!=NULL){
			sebool=determinePrune(croot,child->SE,tol);
		}
		
		return nwbool&&nebool&&swbool&&sebool;
	//return -1;
}
}
/* called by destructor and assignment operator*/
void toqutree::clear(Node * & curr){
/* your code here */
	destroyAll(curr);
}

void toqutree::destroyAll(Node*& croot){
	if(croot==NULL) return ;
	else{

		destroyAll(croot->NW);
		destroyAll(croot->NE);
		destroyAll(croot->SW);
		destroyAll(croot->SE);
		
		croot=NULL;
		delete croot;
	}

}

/* done */
/* called by assignment operator and copy constructor */
toqutree::Node * toqutree::copy(const Node * other) {
	return copyHelper(other);
/* your code here */
}
toqutree::Node *toqutree::copyHelper(const Node* croot){
	if(croot==NULL){return NULL;
		
	}
	
		Node* dist=new Node(croot->center, croot->dimension,croot->avg);
		dist->NW=copyHelper(croot->NW);
		dist->NE=copyHelper(croot->NE);
		dist->SW=copyHelper(croot->SW);
		dist->SE=copyHelper(croot->SE);
		return dist;
	
}


