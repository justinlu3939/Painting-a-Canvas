#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//problems: line[0] == B and line[1] == P, input validation and out-bounds validation

void move(fstream& out, char direction, int distance)
{
    //just move the pointer of the file
    //remember: moving N is -51; moving S is 51; moving E is 1; moving W is -1
    if(direction == 'N')
    {
        for(int i = 0; i < distance; i++)
        {
            out.seekp(-51, ios::cur);
        }
    }
    else if(direction == 'E')
    {
        for(int i = 0; i < distance; i++)
        {
            out.seekp(1, ios::cur);
        }
    }
    else if(direction == 'S')
    {
        for(int i = 0; i < distance; i++)
        {
            out.seekp(51, ios::cur);
        }
    }
    else if(direction == 'W')
    {
        for(int i = 0; i < distance; i++)
        {
            out.seekp(-1, ios::cur);
        }
    }
}
void draw(fstream& out, char direction, int distance, bool bold)
{
    //remember to return back one space using seekp(1, ios::cur)
    if(direction == 'N')
    {
        for(int i = 0; i < distance; i++)
        {
            out.seekp(-51, ios::cur);
            if(bold)
            {
                out.put('#');
                out.seekp(-1, ios::cur);
                
            }
            else
            {
                if(out.peek() == '#')
                {
                    
                }
                else
                {
                    out.put('*');
                    out.seekp(-1, ios::cur);
                    
                }
            }
        }
    }
    else if(direction == 'E')
    {
        for(int i = 0; i < distance; i++)
        {
            out.seekp(1, ios::cur);
            if(bold)
            {
                out.put('#');
                out.seekp(-1, ios::cur);
            }
            else
            {
                if(out.peek() == '#')
                {
                    //do nothing
                }
                else
                {
                    out.put('*');
                    out.seekp(-1, ios::cur);
                }
            }
        }
    }
    else if(direction == 'S')
    {
        for(int i = 0; i < distance; i++)
        {
            out.seekp(51, ios::cur);
            if(bold)
            {
                out.put('#');
                out.seekp(-1, ios::cur);
            }
            else
            {
                if(out.peek() == '#')
                {

                }
                else
                {
                    out.put('*');
                    out.seekp(-1, ios::cur);
                }
            }
            
        }
    }
    else if(direction == 'W')
    {
        
        for(int i = 0; i < distance; i++)
        {
            out.seekp(-1, ios::cur);
            if(bold)
            {
                out.put('#');
                out.seekp(-1, ios::cur);
            }
            else
            {
                if(out.peek() == '#')
                {
                    //do nothing
                }
                else
                {
                    out.put('*');
                    out.seekp(-1, ios::cur);
                }
            }
        }
    }
}
void print(fstream& file)
{
    string line;
    //return to the beginning of the file
    file.seekg(0, ios::beg);
    while(getline(file, line))
    {
        cout << line << "\n";
    }
    cout << endl << endl;
    file.clear();
}

int main()
{
    /////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////          DO  NOT CHANGE CODE BELOW THIS               //////////////
    /////////////////////////////////////////////////////////////////////////////////////////

    ifstream infile("paint_base.txt");
    ofstream outfile("paint.txt", ios::binary);
    string c;
    if (infile)
        while (getline(infile, c))
            outfile << c << "\n";

    infile.close();
    outfile.close();

    /////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////          DO  NOT CHANGE CODE ABOVE THIS               //////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    
    string commandFile;
    char penStatus;
    char direction;
    int distance;
    bool bold;
    fstream file;
    
    cout << "Enter the name of the file: ";
    cin >> commandFile;
    
    //open the input command file
    infile.open(commandFile);
    
    //open the paint.txt file
    file.open("paint.txt", ios::out | ios::in | ios::ate | ios::binary);
    file.seekp(0);
    
    if(infile)
    {
        string line;
        while (getline(infile, line))
        {
                bold = false;
                penStatus = line[0];
                
                //string parshing
                unsigned long int comma = line.find(',');
                line = line.substr(comma + 1);
                direction = line[0];
    
                //string parshing
                comma = line.find(',');
                line = line.substr(comma + 1);
                
                //input validation
                
                if(!isdigit(penStatus) || !isalpha(direction) || !isdigit(line[0]) || (!isdigit(line[0]) && !isdigit(line[1])))
                {
                    continue;
                }
                
                if (isdigit(line[1])) //if it is a two digit number
                {
                    distance = (line[0]-'0') * 10 + (line[1]-'0');
                }
                else
                {
                    
                    distance = (line[0] - '0');
                }
                
                
                //revised edition to find B and P on command line
                comma = line.find(',');
                if(comma != -1)
                {
                    line = line.substr(comma+1);
                    if(line[0] == 'B' && penStatus == '2')
                    {
                        bold = true;
                    }
                    else if(line[0] == 'B' && penStatus == '1')
                    {
                        continue;
                    }
                }
                
                
                
                //check the distance and make sure that it is in bound
                //if it is out of bounds, break the program
                long int current = file.tellp();
                if(direction == 'N')
                {
                    if(current < distance * 51)
                    {
                        continue;
                    }
                }
                else if(direction == 'W')
                {
                    if(distance > current % 51)
                    {
                        continue;
                    }
                }
                else if(direction == 'E')
                {
                    if(distance + current % 51 >= 50)
                    {
                        continue;
                    }
                }
                else if(direction == 'S')
                {
                    if(current + distance * 51 >= 2550)
                    {
                        continue;
                    }
                }
                
                //start moving (move()) and drawing (draw())
                if(penStatus == '1') //pen is up
                {
                    move(file, direction, distance);
                }
                else if(penStatus == '2') //pen is down
                {
                    draw(file, direction, distance, bold);
                }
                
                //FIX:ME - corrected
                if(line[0] == 'P' || line[2] == 'P')
                {
                    file.flush();
                    long int bookmark = file.tellp();
                    print(file);
                    file.seekp(bookmark);
                }
        }
    }
    file.close();
    return 0;
}

