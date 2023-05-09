//references:https://www.geeksforgeeks.org/program-check-three-points-collinear/
#include<iostream>
#include<vector>
#include<array>
#include<stdlib.h>
#include<string.h>
#include<random>
#include<algorithm>
#include<unistd.h>

using namespace std;
int overlap_self(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4);
int intersection_of_lines(int x11,int y11,int x21,int y21,int x31,int y31,int x41,int y41);
int overlap_with_other(int x11,int y11,int x21,int y21,int x31,int y31,int x41,int y41);

int main(int argc , char* argv[]){
        // Creating streets...........................
       const char *streets_all[300] = {
        "Road A","Road B","Road C","Road D","Road E",
        "Road F","Road G","Road H","Road I","Road J",
        "Road K","Road L","Road M","Road N","Road O",
        "Rd AA","Rd AB","Rd AC","Rd AD","Rd AE",
        "Rd AF","Rd AG","Rd AH","Rd AI","Rd AJ",
        "Rd AK","Rd AL","Rd AM","Rd AN","Rd AO",
        "Rd AP","Rd AQ","Rd AR","Rd AS","Rd AT",
        "Rd AU","Rd AV","Rd AW","Rd AX","Rd AY",
        "place AA","place AB","place AC","place AD","place AE",
        "place AF","place AG","place AH","place AI","place AJ",
        "place AK","place AL","place AM","place AN","place AO",
        "place AP","place AQ","place AR","place AS","place AT",
        "place AU","place AV","place AW","place AX","place AY",        
        "Road P","Road Q","Road R","Road S","Road T",
        "Road U","Road V","Road W","Road X","Road Y",
        "Road AA","Road AB","Road AC","Road AD","Road AE",
        "Road AF","Road AG","Road AH","Road AI","Road AJ",
        "Road AK","Road AL","Road AM","Road AN","Road AO",
        "Road AP","Road AQ","Road AR","Road AS","Road AT",
        "Road AU","Road AV","Road AW","Road AX","Road AY"   
        "Street A","Street B","Street C","Street D","Street E",
        "Street F","Street G","Street H","Street I","Street J",
        "Street K","Street L","Street M","Street N","Street O",
        "Stree AA","Stree AB","Stree AC","Stree AD","Stree AE",
        "Stree AF","Stree AG","Stree AH","Stree AI","Stree AJ",
        "Stree AK","Stree AL","Stree AM","Stree AN","Stree AO",
        "Stree AP","Stree AQ","Stree AR","Stree AS","Stree AT",
        "Stree AU","Stree AV","Stree AW","Stree AX","Stree AY",
        "Stre AA","Stre AB","Stre AC","Stre AD","Stre AE",
        "Stre AF","Stre AG","Stre AH","Stre AI","Stre AJ",
        "Stre AK","Stre AL","Stre AM","Stre AN","Stre AO",
        "Stre AP","Stre AQ","Stre AR","Stre AS","Stre AT",
        "Stre AU","Stre AV","Stre AW","Stre AX","Stre AY",        
        "Street P","Street Q","Street R","Street S","Street T",
        "Street U","Street V","Street W","Street X","Street Y",
        "Street AA","Street AB","Street AC","Street AD","Street AE",
        "Street AF","Street AG","Street AH","Street AI","Street AJ",
        "Street AK","Street AL","Street AM","Street AN","Street AO",
        "Street AP","Street AQ","Street AR","Street AS","Street AT",
        "Street AU","Street AV","Street AW","Street AX","Street AY"};
        
    
 
        
        // initiatializing defaut value of streets...........................
        int def_s = 10;       //default streets//
        int def_n = 5;       // default  line assignment//
        int def_l = 5;       // default wait sec//
        int def_c = 20;      // default point -c to c// 

        for(int i = 0; i< argc; i++){
            
            if (strncmp("-s",argv[i],2)==0){
                def_s = atoi(argv[i+1]);//string to int
            }
            
            if (strncmp("-c",argv[i],2)==0){
                def_c = atoi(argv[i+1]);
        }            

            
            if (strncmp("-l",argv[i],2)==0){
                def_l = atoi(argv[i+1]);
            }
            
        
            if (strncmp("-n",argv[i],2)==0){
                def_n = atoi(argv[i+1]);
            }
        }

      
        
    while(true){
        // initializing flags so that if any error it is changes to 1
        int fg1 = 0;
        int count =0;
        int fg22 = 0;
        int fg2 =0;
        int fg3 = 0;
        int fg33 = 0;
        

        // Generatting random number of streets

        uniform_int_distribution<int> dis(2,def_s); //uniform distribution
        random_device rd1("/dev/urandom");  //creating object
        int num_street = dis(rd1); //creating random street
        

        
        vector <int> pts_db[num_street]; //Store steets in a array of vector

        //Generating random num of lines for each street.........

        for(int i=0; i<num_street;i++){

            uniform_int_distribution<int> dis(1,def_n); //uniform distribution
            random_device rd2("/dev/urandom"); // creating obj
            long unsigned int num_segs = dis(rd2); // creating random num of linesegs           
        
        
            //each lineseg has 4 coordinates say x1,x2,y1,y2 so...
            long unsigned int num_points = (num_segs+1)*2;           
            
            
            //Generating number of points randomly for each line segments
            while(pts_db[i].size() < num_points){
                //uniform distribution
                uniform_int_distribution<int> dis(-def_c,def_c);
                random_device rd3("/dev/urandom"); // creating obj
                int x = dis(rd3); //x1
                int y = dis(rd3); //y1                
                
                
                // storing points in the db
                if(pts_db[i].size()==0){
                    pts_db[i].push_back(x);//storing x
                    pts_db[i].push_back(y); //storing y
                    count = 0;
                }
        
                //putting condition check if points are between 1 and 4
                else if((pts_db[i].size()>1) && (pts_db[i].size()<4)){
                    int fa = pts_db[i].size();


                    // self loop if any
                    for(int m=0;m<(fa/2);m++){
                        int aa = 2*m;
                        int bb = (2*m)+1;

                        //comparing coordinates and checking if same then error dont push.............
                        if ((pts_db[i][aa]==x) && (pts_db[i][bb]==y)){
                        //if this loop is enterd then flag is 1    
                        fg1 = 1;
                        
                        }

                        // comparing streets with other streets

                        if(i>0){
                            int x1 = pts_db[i][fa-2]; //db points
                            int y1 = pts_db[i][fa-1]; //db points
                            int x2 = x; //new points
                            int y2 = y;  //new point

                            
                            for(int tt = 0; tt<i; tt++){
                                int vals = pts_db[tt].size();

                                // looping till vals/2-1 times 
                                for(int zz = 0;zz<((vals/2)-1);zz++){
                                    //taking all the points as x3,y3 x4,y4
                                    int x3 = pts_db[tt][2*zz];
                                    int y3 = pts_db[tt][(2*zz)+1];
                                    int x4 = pts_db[tt][(2*zz)+2];
                                    int y4 = pts_db[tt][(2*zz)+3];

                                    //checking overlap
                                    fg3= overlap_self(x1,y1,x2,y2,x3,y3,x4,y4);
                                    fg33 = fg3 + fg33; // adding flags to check error
                                   
                                }
                            }
                    
                        }

                        //if any flag is greater than 1 then dont pushback points..ignore the points
                        if((fg1==1) || (fg33>0)){
                            //resetting flags
                            fg1 =0;
                            fg33=0;
                            fg3=0;
                            //increasing tries
                            count =count +1;
                            
                            
                        }
                        else{
                            //points are ok now pushback
                            pts_db[i].push_back(x);
                            pts_db[i].push_back(y);
                            // resetting the tries
                            count=0;

                        }
    
                    }



                }
                else{
                    //if points are greater than 4
                    int mm = pts_db[i].size();
                    int x11 = pts_db[i][mm-2];
                    int y11 = pts_db[i][mm-1];
                    int x21 = x;
                    int y21 = y;
                
                    // Checking for self loop if any
                    for(int ll=0;ll<(mm/2);ll++){
                        int a = 2*ll;
                        int b = (2*ll)+1;

                        if ((pts_db[i][a]==x) && (pts_db[i][b]==y)){
                            //if points same then rais the flag
                            fg1 = 1;
                        } 

                    }
                    //  checking intersection with its own line
                    for(int ll = 0;ll<((mm/2)-1);ll++){
                        //picking 2 points from database
                        int x31 = pts_db[i][2*ll];
                        int y31 = pts_db[i][(2*ll)+1];
                        int x41 = pts_db[i][(2*ll)+2];
                        int y41 = pts_db[i][(2*ll)+3];
                        //now checking if intersection..........................

                        fg2= intersection_of_lines(x11,y11,x21,y21,x31,y31,x41,y41);
                        fg22 = fg2 + fg22; //checking all the error consitions
                    
        
                    }

            
                    if(i>0){
                        int x1 = pts_db[i][mm-2];
                        int y1 = pts_db[i][mm-1];
                        int x2 = x;
                        int y2 = y;
                        
                        for(int t = 0; t<i; t++){
                            int val = pts_db[t].size();

                            // looping til m/2-1 
                            for(int z = 0;z<((val/2)-1);z++){
                            
                                int x3 = pts_db[t][2*z];
                                int y3 = pts_db[t][(2*z)+1];
                                int x4 = pts_db[t][(2*z)+2];
                                int y4 = pts_db[t][(2*z)+3];
                                //checking overlap....................
                                fg3= overlap_self(x1,y1,x2,y2,x3,y3,x4,y4);
                                fg33 = fg3 + fg33;//adding flags
                                
                            }
                        }
                
                    }

                    

                    //checking if any falg is 1
                    if((fg1 ==1) || (fg22>0) ||(fg33>0)){
                        //resetting flags and not pushing back points
                        fg1  =0;
                        fg2 =0;
                        fg22 = 0;
                        fg33=0;
                        fg3=0;
                        //increasing number of tries
                        count = count +1;
                    }

                    else{
                            //points ok pushback in db
                            pts_db[i].push_back(x);
                            pts_db[i].push_back(y);
                            count = 0;  //resetting tries                    
                        }
                }
                //if tries>25 error
                if(count>25){
                    cerr<<"Error: greater than 25 tries"<<endl;
                    exit(1);
                }           

            }            
        }
            //formatting streets
            for(int i=0;i<num_street;i++){
                int r = pts_db[i].size();
                //add command
                cout<<"add "<<"\""<<streets_all[i]<<"\" "; 
                //printing steets
                for(int f=0;f<(r/2)-1;f++){
                    int z = pts_db[i][2*f];
                    int e = pts_db[i][(2*f)+1];
                    cout<<"("<<z<<","<<e<<") ";
                }
                cout<<"("<<pts_db[i][r-2]<<","<<pts_db[i][r-1]<<")";
                cout<<endl;
            }
            //printing gg
            cout<<"gg"<<endl;

            //rm street
            for(int i=0;i<num_street-1;i++){
                cout<<"rm "<<"\""<<streets_all[i]<<"\""<<endl;//rm street
            
            }
            //last street removal
            cout<<"rm "<<"\""<<streets_all[num_street-1]<<"\""<<endl;

            for(int i=0;i<num_street;i++){
                //emptying database of streets
                    pts_db[i].clear();                
                }

            
        sleep(def_l); //sleep for l seconds  
        
    }   

    
}
int overlap_self(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4){
    int area = x2*(y3-y4) + x3*(y4-y2) + x4*(y2-y3);
    float xden = ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
    float yden = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    if((area ==0) && ((xden == 0) && (yden == 0))){
             
            //line segemnt or not // colinear points.
            if(((x2<=min(x3,x4)) || (x2>=max(x3,x4)) || (y2<=min(y3,y4)) || (y2>=max(y3,y4))) &&
              ((x3<=min(x1,x2)) || (x3>=max(x1,x2)) || (y3<=min(y1,y2)) || (y3>=max(y1,y2))))
            {
                return 0;
            }  
            else{
		        
                return 1;
            }
        }
        else{
            return 0;
        }
} 

int overlap_with_other(int x11,int y11,int x21,int y21,int x31,int y31,int x41,int y41){
    int area = x21*(y31-y41) + x31*(y41-y21) + x41*(y21-y31);
    if(area ==0){
            // They are colinear. 
            // check if point is on line segemnt or not
            if(((x21<=min(x31,x41)) || (x21>=max(x31,x41)) || (y21<=min(y31,y41)) || (y21>=max(y31,y41))) &&
              ((x31<=min(x11,x21)) || (x31>=max(x11,x21)) || (y31<=min(y11,y21)) || (y31>=max(y11,y21))))
            {
                return 0;
            }  
            else{
                return 1;
            }
        }
        else{
            return 0;
        }
}  

int intersection_of_lines(int x11,int y11,int x21,int y21,int x31,int y31,int x41,int y41){   

    

    float xnum = ((x11 * y21 - y11 * x21) * (x31 - x41) - (x11 - x21) * (x31 * y41 - y31 * x41));
    float xden = ((x11 - x21) * (y31 - y41) - (y11 - y21) * (x31 - x41));

    float ynum = (x11 * y21 - y11 * x21) * (y31 - y41) - (y11 - y21) * (x31 * y41 - y31 * x41);
    float yden = (x11 - x21) * (y31 - y41) - (y11 - y21) * (x31 - x41);
	

    // This lines are not parallel 

     if ((xden != 0) && (yden != 0)){
         float xco  =xnum/xden;
         float yco  =ynum/yden;
        if((x41==x11)&&(y41==y11)){
            
            return 0;
        } 
        else{        

            //  Check whether they intersect or not

            if ((xco < max(min(x11, x21), min(x31, x41))) || (xco > min(max(x11, x21), max(x31, x41))) || 
               (yco < max(min(y11, y21), min(y31, y41))) || (yco > min(max(y11, y21), max(y31, y41))))
               {
                
                return 0;
            }

            else{              

                    // No overlap no parallel but they intersect
                    return 1;
            }
        }

    }
    // Either they are parallel or they overlap
    else{
        int aaa =overlap_with_other(x11,y11,x21,y21,x31,y31,x41,y41);
        return aaa;  
        }    

}


