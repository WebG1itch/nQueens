//nQueens.cpp
#include <iostream>
#include <stack>
#include <sstream>
#include <vector>


bool checkPlacement(std::stack<std::vector<int> > * height, int n) { // checking to make sure the queen can be where it is
    if (height->size() > 1) {
        std::stack<std::vector<int> > checkStack(*height); // creating a temp stack to sort through and compare against
        checkStack.pop(); // removing first row because that's where we are already
        int pos;
        int diagL;
        int diagR;
        for (int i = 0; i < n; i++) { // getting the position of the queen to compare agains the other rows
            if(height->top().at(i) == 1) {
                pos = i;
                diagL = i - 1;
                diagR = i + 1;
                i = n;
            }
        }
        
        while (checkStack.size() > 0) { // checking each row one by one
            
            if (checkStack.top().at(pos) == 1) { // checking against column
                return false;
            }

            if (diagL >= 0) {
                if (checkStack.top().at(diagL) == 1) { // checking diagonally to the left
                    return false;
                }
            }

            if (diagR <= n - 1) {
                if (checkStack.top().at(diagR) == 1) { // checking diagonally to the right
                    return false;
                }
            }

            diagL -= 1;
            diagR += 1;
            checkStack.pop();

        } // while
    } // if
    return true;
}

void moveTopQueenOne(std::stack<std::vector<int> > * height, int n) { // moves the top queen over to the right one space
    int qPos;
    for (int findQ = 0; findQ < n; findQ++) { // gets queen's pos
        if (height->top().at(findQ) == 1) {
            if (findQ == n-1) {
                height->pop();
                moveTopQueenOne(height, n);
                return;
            }
        qPos = findQ; 
        }
    }
    height->top().at(qPos) = 0; // moves queen over one
    height->top().at(qPos + 1) = 1;
}

void placeQueen(std::stack<std::vector<int> > * height, int n) { // moves queen across current row and checks if it can be there
    int pos = 0;

    for (int queenPos = 0; queenPos < n; queenPos++) { // gets the queens position
        if (height->top().at(queenPos) == 1) {
            pos = queenPos;
            queenPos = n;
        }
    }

    while (!checkPlacement(height, n) && pos < n) { // runs checkPlacement to see if the queen is in the right place
        int qPos;
        for (int findQ = 0; findQ < n; findQ++) { // if the queen isn't in the right place it needs to move over one and run the check again
            if (height->top().at(findQ) == 1) {
                if (findQ == n-1) { // if the queen is already on the right edge, this row needs to be removed and the queen in the prev row needs to move
                    height->pop();
                    moveTopQueenOne(height, n);
                    return;
                }
            qPos = findQ; 
            }
        }
        height->top().at(qPos) = 0;
        height->top().at(qPos + 1) = 1;
        pos++;
    }
}

void createVector(std::stack<std::vector<int> > * height, int n) { // creates a vector of size n with a queen at the first spot
    std::vector<int> vec;
    for (int init = 0; init < n; init++) {
        vec.push_back(0);
    } // for
    vec.at(0) = 1;
    height->push(vec);
}

int defineN() { // this didn't end up working like I wanted. Still defines n though
  std::string input = ""; // ask user to define n
  std::cout << "Define n.\nn = ";
  std::cin >> input;

  int def; // converting the input to int
  std::stringstream convert(input);
  convert >> def;

  return def;
}

int main() {

    int n = defineN(); // define n
		if (n > 25) {
				std::cout << "To prevent total system hang, n should not be greater than 25. Do you want to bypass this? Y/N" << std:: endl;
				std::string input = "";
				std::cin >> input;
				if (input.compare("Y") != 0){
					n = 25;
				}		
		}
    bool solved = false;
    std::stack<std::vector<int> > * height = new std::stack<std::vector<int> >;

    while(!solved) {
        while(height->size() < n) { // runs until the stack is filled with n vectors
            
            // create a vector with a queen at 1
            createVector(height, n);

            // if there are rows below the vector, we must check the queens' placements
            placeQueen(height, n);
            
						// double-check the placement of the queen
            while (!checkPlacement(height, n)) {
                placeQueen(height, n);
            } 

        } // for
        solved = true;
    } // while

    while (height->size() > 0) { // prints out the solution board
        for(int vecPrint = 0; vecPrint < height->top().size(); vecPrint++) {
            if (height->top().at(vecPrint) == 1) {
                std::cout << 1 << " ";
            } else {
                std::cout << 0 << " ";
            }
        }
        std::cout << std::endl;
        height->pop();
    }
    std::cout << "Solution Found" << std::endl;
}
