#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <vector>
#include <ctime>
// testing git
bool merge_num (std::vector<int>& v, int bi, int ei);
bool game_over(const std::vector<int>& v);
void print_grid(const std::vector<int>& v);
void rotate_anti_clock (std::vector<int>& v);
void gentwo (std::vector<int>& v);
int main(){
    std::vector<int> vin;
    std::string input;
    std::string filename;
    
    std::cout << "please enter name of file" << std::endl;
    std::cin >> filename;
    
    std::ifstream infile;
    infile.open(filename.c_str());
    
    if(!infile.is_open()){
        std::cout<<"file not found, using default start configuration"<<std::endl;
        for (int i = 0; i<15 ; i++){
            vin.push_back(0);
        }
        vin.push_back(2);
    }
    else{
        int tmp;
        while(infile >> tmp){
            vin.push_back(tmp);
        }
    }
    int gameside = std::sqrt( vin.size() );
    print_grid (vin);
    std::vector<int> beforemove;
    while ( !( game_over(vin) ) ){
        beforemove = vin;
        std::cin>>input;
        if (input == "w" ){
            rotate_anti_clock(vin);
            for (int i = 0; i <gameside ; i++){
                merge_num(vin, i*gameside, i*gameside + gameside - 1 ) ;
            }
            rotate_anti_clock(vin);
            rotate_anti_clock(vin);
            rotate_anti_clock(vin);
        }
        
        if (input == "a" ){
            for (int i = 0; i <gameside ; i++){
                merge_num(vin, i*gameside, i*gameside + gameside - 1 ) ;
            }
        }
        
        if (input == "s" ){
            rotate_anti_clock(vin);
            rotate_anti_clock(vin);
            rotate_anti_clock(vin);
            for (int i = 0; i <gameside ; i++){
                merge_num(vin, i*gameside, i*gameside + gameside - 1 ) ;
            }
          
            rotate_anti_clock(vin);
        }
        
        if (input == "d" ){
            rotate_anti_clock(vin);
            rotate_anti_clock(vin);
            for (int i = 0; i <gameside ; i++){
                merge_num(vin, i*gameside, i*gameside + gameside - 1 ) ;
            }
            rotate_anti_clock(vin);
            rotate_anti_clock(vin);
        }
        if (vin != beforemove){
            gentwo(vin);
            print_grid (vin);
            std::cout<<std::endl;
        }
        }
    
    std::cout<<"Game Over"<<std::endl;
    return 0;
}

bool merge_num( std::vector<int>& in, int bi, int ei){
    std::vector<int> withoutzero, out;
    
    int gameside = std::sqrt( in.size() );
    for (int i = bi; i <= ei; i++){
        if (in[i] != 0 ){
            withoutzero.push_back( in[i] );
        }
    }
    if (withoutzero.size() != 0){
        for (int i = withoutzero.size() ;  i <= gameside ; i++ ){
            withoutzero.push_back(0);
        }
    }
    else{
        return true;
    }
    for (int i = 0 ; i<= gameside - 1; i++) {
        if (i == gameside - 1) {
            out.push_back( withoutzero[i] );
        }
        else{
            if (withoutzero[i] == withoutzero [i+1] ) {
                out.push_back( 2 * withoutzero[i] );
                for (int j = i+1 ; j < gameside - 1; j++) {
                    withoutzero[j] = withoutzero [j+1];
                }
                withoutzero[gameside-1] = 0;
            }
            else{
                out.push_back( withoutzero[i] );
            }
        }
    }
    int k = 0;
    for (int i = bi; i<= ei; i++) {
        if( in[i] != out[k] ){
            int j = 0;
            for (int i = bi; i<=ei; i++) {
                in[i] = out[j];
                j++;
            }
            return true;
        }
        k++;
    }
    return false;
}

bool game_over(const std::vector<int>& v){
    int gameside = std::sqrt(v.size());
    std::vector<int> test;
    test = v;
    for (int i = 0; i < 4; i++ ){
        for (int i = 0; i < gameside ; i++){
            if ( merge_num(test, i*gameside, i*gameside + gameside - 1 )==true) {
                return false;
            }
        }
        rotate_anti_clock(test);
    }
    return true;
}

void print_grid(const std::vector<int>& v){
    int side = std::sqrt(v.size());
    for ( int j = 0; j < side; j++){
        for (int i = j*side ; i < j*side + side; i++){
            std::cout<<v[i]<<"\t";
        }
        std::cout<<std::endl;
    }
}

void rotate_anti_clock (std::vector<int>& v){
    std::vector<int> store_vec;
    int side = std::sqrt (v.size() );
    int width = side - 1;
    for (int j = 0; j < side; j++) {
        for (int i = 0; i<side; i++) {
            store_vec.push_back( v[width - j + i*side] );
        }
    }
    v = store_vec;
}

void gentwo (std::vector<int>& v){
    std::vector<int> storezero, storevecnum;
    int k = 0;
    for(int i = 0; i <v.size(); i++){
        if (v[i]==0){
            storezero.push_back( v[i] );
            storevecnum.push_back( k );
        }
        k++;
    }
    if( storezero.size() != 0 ){
        srand((unsigned)time (NULL));
        int d =  ( rand()%storezero.size() ) ;
        int original_pos = storevecnum[d] ;
        v[ original_pos ] = 2;
    }
}
