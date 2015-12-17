#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>



using namespace std;

struct Struct_for_sym                  //The structure for the symbol and the symbol number
{
    int number;
    char x;
};
int main()

{
               
    string Many = "1234567890abcdefghijklmnopqrstuvwxyz"; //The characters are used in the password
    int L = Many.length();                                 // The length of the sring Many
//    int array_for_Many [L];
//    for(int i = 0; i < L; i++) array_for_Many[i] = i; //
//    for(int i = 0; i < L; i++) cout << array_for_Many[i] << " "<<endl;
    
    string password;                            //The declaration of the password
    cout<< "Please, enter the password:"<<endl;
    cin>>password;                              //Initialization of the password.
    vector <Struct_for_sym> A(1);               // Tne temporary vector of the symbol and the symbol's number
                   
    string temp_password ="";                    // the temporary string for comparison with the password
    char temp;                                   // the temporary value for insert character in the temporary password
   
    int k = 0;

        while (password != temp_password)       //comparing the password and the temporary password
        {
            A[k].x = Many[A[k].number];         //the symbol in the structure is taken from the set of all symblols
            A[k].number++;                      //the symbol number in the structure is taken from the set of all symblols
            
               // for(int j=0; j<A.size(); j++)    //output of the intermediate values
//                {
//                    cout<<j<<")"<<A[j].x<<" ";
//                }
//                cout<<endl;
          
            if(A[k].x == Many[L-1] && A[0].x == Many[L-1])     //if the A[k].x on the last symbol in the symbols set and A[0].x too
            {
                Struct_for_sym *c = new Struct_for_sym;        // The pointer of the new element of the vector
                A.push_back(*c);                               // The new element of the vector
                
                for(int l=0; l<A.size(); l++)                  //output of the intermediate values
                {
                    A[l].number = 0;
                    A[l].x = Many[A[l].number];
                }
                k++;
                cout<<"size "<<A.size()<<endl;
            }
      
            for(int p = k; p >= 0; p--)                     
            {
                if (A[p].x == Many[L-1] && A[0].x != Many[L-1])   //if the A[k].x on the last symbol in the symbols set and A[0].x is not yet.
                {
                    A[p].number = 0;
                    A[p].x = Many[A[p].number];
                    A[p-1].number++;
                    A[p-1].x = Many[A[p-1].number];    
                }
                for(int j=0; j<A.size(); j++)                   //Output of the intermediate values
                {
                    cout<<j<<")"<<A[j].x<<" ";
                }
                cout<<endl;
            }
            
            for(int s = 0; s < A.size(); s++)                  //All finding symbols are inserted in the temporary string temp_password.
            {
                temp = A[s].x;
                temp_password.insert(temp_password.end(),temp);
            }
                
  //          cout<<"The temporary password: "<<temp_password<<" "<<endl;

            if(temp_password == password)                     //Comparing of the temporary password with the password.
            {
                cout<<"The temporary password: "<<temp_password<<" "<<endl;
                cout<< "The password was found."<< endl;      //If the password is found the program will broken.
                break;
            }
            else
            {
                temp_password.clear();                       //Clearing of the temporary string/
            }      
        }   
    system("pause");
    return 0;
}
