// Ian All
// 10-16-19
// Virtual Hard Drive


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

//SDISK CLASS AND DEFINITIONS ---------------------------------------------------------------------------------
class Sdisk{
public :
Sdisk(string diskname, int numberofblocks, int blocksize);
int getblock(int blocknumber, string& buffer);
int putblock(int blocknumber, string buffer);
int getnumberofblocks(); // accessor function
int getblocksize(); // accessor function
private :
string diskname;        // file name of software-disk
int numberofblocks;     // number of blocks on disk
int blocksize;          // block size in bytes
};

Sdisk::Sdisk(string diskname, int numberofblocks, int blocksize){
	ifstream infile(diskname.c_string);
	if(!infile.good()){
		this->diskname = diskname;
		this->numberofblocks = numberofblocks;
		this->blocksize = blocksize;
		
		infile.close();
		
		ofstream outfile(diskname.c_string);
		for(int i=1; i<=numberofblocks; i++){
			for(int i=1; i<=blocksize; i++){
				outfile<<"x";
			}
			outfile << endl;
		}
		outfile.close();
	}
	
	else{
		infile.close();
		return;
	}
	infile.close();
}

int Sdisk::getblock(int blocknumber, string& buffer){
	ifstream infile(diskname.c_string);
	if(!infile.good()){
		infile.close();
		return 0;
	}

	else{
		
		if(blocknumber <= this->blocksize){
			string grab;
			vector <string> holder;
			infile>>grab;
			while(infile.good()){
				holder.push_back(grab);
				infile>>grab;
			}
			infile.close();
			buffer = holder[blocknumber];
			return 1;
		}
		else{
			return 0;
		}
	
	}
}

int Sdisk::putblock(int blocknumber, string buffer){
	ifstream infile(diskname.c_string);
	
	if(!infile.good()){
		infile.close();
		return 0;
	}
	
	else{
		
		if( blocknumber <= this->blocksize){
			string grab;
			vector <string> holder;
			infile>>grab;
			while(infile.good()){
				holder.push_back(grab);
				infile>>grab;
			}
			infile.close();
			ofstream outfile(diskname.c_string);
			holder[blocknumber]=buffer;
			outfile<<holder[0]<<endl;
			for(int i=1; i<numberofblocks;i++){
				outfile<<holder[i]<<endl;
			}
			outfile.close();
			return 1;
		}
		
		else{
			return 0;
		}
	}
}

int Sdisk::getnumberofblocks(){ // accessor function
	return numberofblocks;
}
int Sdisk::getblocksize(){
	return blocksize;
}

//Filesys CLASS and DEFINITIONS ---------------------------------------------------------------------------

class Filesys: public Sdisk
{
public :
Filesys(string diskname, int numberofblocks, int blocksize);
int fsclose();
int fssynch();
int newfile(string file);
int rmfile(string file);
int getfirstblock(string file);
int addblock(string file, string block);
int delblock(string file, int blocknumber);
int readblock(string file, int blocknumber, string& buffer);
int writeblock(string file, int blocknumber, string buffer);
int nextblock(string file, int blocknumber);
private :
int rootsize;           // maximum number of entries in ROOT
int fatsize;            // number of blocks occupied by FAT
vector<string> filename;   // filenames in ROOT
vector<int> firstblock; // firstblocks in ROOT
vector<int> fat;             // FAT
};




int main()
{
  Sdisk disk1("test1.txt",16,32);
  string block1, block2, block3, block4;
  for (int i=1; i<=32; i++) block1=block1+"1";
  for (int i=1; i<=32; i++) block2=block2+"2";
  disk1.putblock(4,block1);
  disk1.getblock(4,block3);
  cout << "Should be 32 1s : ";
  cout << block3 << endl;
  disk1.putblock(8,block2);
  disk1.getblock(8,block4);
  cout << "Should be 32 2s : ";
  cout << block4 << endl;;
}
