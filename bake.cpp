#include <iostream>
#include <fstream>
using namespace std;

string scalingBuffer = "";
string bakingBuffer = "";
int baking_count = 0;
int bagel_baked = 0;
int baguette_baked = 0;
int no_request = 0;
int bakery_time = 0;
int scaling_work_time = 0;
int scaling_time = 0;
int baking_work_time = 0;
int baking_time = 0;
int rest_baking_time = 0;
bool getEnd;

// save output and send output to the next stage when clock arrives
int scaling_output = 9;
int mixing_output = 9;
int fermentation_output = 9;
int folding_output = 9;
int dividing_output = 9;
int rounding_output = 9;
int resting_output = 9;
int shaping_output = 9;
int profing_output = 9;
int baking_output = 9;
int cooling_output = 9;
int stocking_output = 9;

void scaling();
void Mixing(int bake);
void Fermentation(int bake);
void Folding(int bake);
void Dividing(int bake);
void Rounding(int bake);
void Resting(int bake);
void Shaping(int bake);
void Profing(int bake);
void Baking();
void Cooling(int bake);
void Stocking(int bake);

int main()
{
    //get input
    fstream f;
    f.open("trace1", ios::in);
    getEnd = true;
    if (f.is_open())
    {
        cout << "ok" << endl;
        string bake;
        while (getline(f, bake))
        {
            // wait for pipeline to end
            while (!getEnd)
            {
                continue;
            }
            getEnd = false;
            if (bake == "Bake-Bagel")
            {
                scalingBuffer.append("1");
                baking_count++;
                bagel_baked++;
            }else if (bake == "Bake-Baguette")
            {
                scalingBuffer.append("2");
                baking_count++;
                baguette_baked++;
            }else{
                scalingBuffer.append("0");
                no_request++;
            }
            scaling();
            bakery_time++;
        }
        f.close();
    }
    // send end message
    while (stocking_output!=8)
    {
        while (!getEnd)
        {
            continue;
        }
        getEnd = false;
        scalingBuffer.append("8");
        scaling();
        bakery_time++;
    }
    bakery_time--;
    
    
    //output formats
    printf("\nBaking count: %d\n", baking_count);
    printf(" - Bagel baked: %d\n", bagel_baked);
    printf(" - Baguette baked: %d\n", baguette_baked);
    printf("No request: %d\n", no_request);

    printf("\nHow many minutes to bake: %d\n", bakery_time);

    double performance = (double)(bagel_baked + baguette_baked)/(double)bakery_time;

    printf("\nPerformance (bakes/minutes): %.2f\n", performance);

    return 0;
}

void scaling(){
    // need a rest
    if (scaling_time == 1000)
    {
        scaling_work_time = -10;
        scaling_time = 0;
    }
    scaling_work_time++;
    // send output to next stage
    Mixing(scaling_output);
    // if not rest
    if (scaling_work_time > 0)
    {
        // get next command
        int b = (int)scalingBuffer[0]-48;
        scalingBuffer.erase(0,1);
        // if there are real work after empty commands, get rid of all empty commands
        // while (b == 0 && scalingBuffer.size() > 0)
        // {
        //     b = (int)bakingBuffer[0]-48;
        //     scalingBuffer.erase(0,1);
        // }
        scaling_output = b;
        if (b == 1 || b == 2)
        {
            scaling_time++;
        }
    }else{
        int b = (int)scalingBuffer[0]-48;
        if (b == 0)
        {
            scalingBuffer.erase(0,1);
            scaling_output = b;
        }else{
            scaling_output = 0;
        }
    }
}

void Mixing(int bake){ 
    Fermentation(mixing_output); 
    mixing_output = bake;
}

void Fermentation(int bake){ 
    Folding(fermentation_output);
    fermentation_output = bake; 
}

void Folding(int bake){ 
    Dividing(folding_output);
    folding_output = bake;
}

void Dividing(int bake){ 
    Rounding(dividing_output); 
    dividing_output = bake;
}

void Rounding(int bake){ 
    Resting(rounding_output); 
    rounding_output = bake;
}

void Resting(int bake){ 
    Shaping(resting_output);
    resting_output = bake; 
}

void Shaping(int bake){ 
    Profing(shaping_output); 
    shaping_output = bake;
}

void Profing(int bake){ 
    bakingBuffer.append(to_string(profing_output));
    Baking(); 
    profing_output = bake;
}

void Baking(){
    Cooling(baking_output);
    // still baking
    if ( rest_baking_time == 1)
    {
        rest_baking_time--;
        baking_time++;
        baking_output = 2;
        return;
    }
    // need a rest
    if (baking_time==10)
    {
        baking_work_time = -1;
        baking_time = 0;
        int c = (int)bakingBuffer[0]-48;
        // if end signal arrives when resting, send end to the next stage
        if (c == 8)
        {
            baking_output = 8;
            bakingBuffer.erase(0,1);
        }
        else{
            baking_output = 0;
        }
    }
    baking_work_time++;
    // need a new work to do
    if (baking_work_time > 0)
    {
        int b = 0;
        b = (int)bakingBuffer[0]-48;
        bakingBuffer.erase(0,1);
        // if get empty, just go after until find a job or the buffer is empty
        // while (b == 0 && bakingBuffer.size() > 0)
        // {
        //     b = (int)bakingBuffer[0]-48;
        //     bakingBuffer.erase(0,1);
        // }
        // if has a job to do, just do it
        if (b!=0 && b!=8 && b!=9)
        {
            rest_baking_time += b;
            rest_baking_time--;
            if (rest_baking_time == 0)
            {
                baking_time++;
                baking_output = b;
            }
        }else
        {
            baking_output = b;
        }
    } else {
        int b = (int)bakingBuffer[0]-48;
        if (b == 0)
        {
            bakingBuffer.erase(0,1);
        }
        baking_output = 0;
    }
}

void Cooling(int bake){ 
    Stocking(cooling_output); 
    cooling_output = bake;
}

void Stocking(int bake){ 
    stocking_output = bake;
    getEnd = true;
}