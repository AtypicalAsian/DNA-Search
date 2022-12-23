//================================================
//Nicolas Nguyen
//September 2022 
//prj5.cpp
//This program searches a DNA string for occurences of any
//given fragment and return the first index of the matched fragment 
//It also reports overlap between fragments 
//================================================

#include<iostream> 
#include <cstring> 
using namespace std; 
const int size = 110; 

//=================== Function declarations ========================
int DNAsearch(char fragment[], char donor[], int sizef, int sized); 
void reverse(char fragment[]); 
bool overlap(char fragment[], int matched_indeces[], int match_head); 

//Main
int main ( void )
{
  //======================================== Variable declaration =========================================
  int n; 
  int i = 0; 
  char dummy; 
  char donorString[size]; 
  char fragmentString[size]; 
  int matched_indeces[size]; 
  for (int i=0; i<size; i++) //array to keep track of matched positions in the donor string
    matched_indeces[i] = 0;  //I initialized it to contain all 0's
  bool overlapped; 
  
  //======================================== Parsing input =================================================
  cin.get(donorString, size + 1); 
  cin.get(dummy);   
  cin >> n; 

while (n--) //Read in fragment, check it, print appropriate output, discard then move on to the next fragment until there's none left
    {
      cin.get(dummy);
      cin.get(fragmentString, size + 1);  

      int x = 0; 
      while(fragmentString[x])
      {
        cout << fragmentString[x];
        x++; 
      } 
      
      //============================ check forward match ======================================
      int forward; 
      forward = DNAsearch(fragmentString, donorString, strlen(fragmentString), strlen(donorString)); 

      //============================ check backward match ======================================
      int backward; 
      char fragment_r[size]; 
      reverse(fragmentString);   
      backward =  DNAsearch(fragmentString, donorString, strlen(fragmentString), strlen(donorString)); 

      cout << " is"; 

      //============================ compare 2 indices to find leftmost match ======================
      int leftmost_i = -1; 
      if ((forward!=-1)&&(backward!=-1))
        {
            if (forward<=backward) leftmost_i = forward; 
            else leftmost_i = backward; 
        }
      else if(forward == -1)  
        {
            if(backward==-1) leftmost_i = -1;
            else leftmost_i = backward; 
        }
      else if (backward == -1)
        {
            if(forward==-1) leftmost_i = -1;
            else leftmost_i = forward; 
        }

        if (leftmost_i == -1) cout << " not found" << endl;
        else
        {
        //============================ Check for overlap ====================== 
            overlapped = overlap(fragmentString, matched_indeces, leftmost_i); 
            if (overlapped)  cout << " found at index " << leftmost_i << " overlap" << endl; 
            else cout << " found at index " << leftmost_i << endl; 
        }
    }
  return 0; 
}

//================================== Function Definitions ==================================================
//==============================================================
// DNAsearch
// This function searches from left to right to determine 
// if a fragment is in the donor string
// PARAMETERS:
//      char fragment[]: the fragment char array
//      char donor[]: the donor DNA char array
//      int sizef: the length of the fragment array
//      int sized: the length of the donor DNA array

// RETURN VALUE:
//      match_head: the first index of the fragment in the donor string
//=============================================================
int DNAsearch(char fragment[], char donor[], int sizef, int sized)
{
   int match_head = -1; 
   for (int i = 0; i<sized; i++ )
    {
      int match_length = 0;
      if (fragment[0] == donor[i])
      { 
        for(int j = 0; j<sizef; j++)
        {
            if (fragment[j] == donor[i+j])
              match_length++; 
        }
        if (match_length == sizef)
        {
            match_head = i;
            break; 
        }
      }
    }
    return match_head; 
}

//==============================================================
// reverse
// This function reverses the fragment array
// PARAMETERS:
//      char fragment[]: the fragment char array
// RETURN VALUE:
//      NONE
//=============================================================
void reverse(char fragment[]) 
{
    int start = 0; 
    int end=strlen(fragment)-1;  
    while (start<end)
    {
        int x = fragment[start]; 
        fragment[start] = fragment[end]; 
        fragment[end] = x; 
        start++; end--; 
    }

}

//==============================================================
// overlap
// This function checks if a fragment overlaps with previously 
// matched fragments
// PARAMETERS:
//      char fragment[]: the fragment char array
//      int matched_indices: an array that keeps track of which 
//                 character have been matched in the donor DNA
//      int match_head: the first index of the fragment in the 
//                      donor string

// RETURN VALUE:
// overlap: true if overlap occured, false if otherwise
//=============================================================
bool overlap(char fragment[], int matched_indeces[], int match_head)
{
    bool overlap = false; 
    for (int i=match_head; i<(match_head+strlen(fragment)-1); i++)
        {
          if (matched_indeces[i] == 1) overlap = true; 
        }
    if(overlap);
    else overlap = false; 
    for (int i=match_head; i<(match_head+strlen(fragment)-1); i++)
        matched_indeces[i] = 1;

    return overlap; 
}
